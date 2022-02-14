#include <cassert>
#include "monitor.h"
#include "light.h"
#include "controller.h"

Monitor::Monitor(sc_module_name name, char *outfile)
  : sc_module(name)
{
  assert(outfile != 0);
  out = new ofstream(outfile);
  assert(*out);

  previous_car_NS = false;
  previous_car_SN = false;
  previous_car_EW = false;
  previous_car_WE = false;

  SC_METHOD(monitor_method);
  dont_initialize();
  sensitive << light_NS_color;
  sensitive << light_SN_color;
  sensitive << light_EW_color;
  sensitive << light_WE_color;

  sensitive << en_axis_EW;
  sensitive << en_axis_NS;

  sensitive << NS_hasCars;
  sensitive << SN_hasCars;
  sensitive << EW_hasCars;
  sensitive << WE_hasCars;

  SC_METHOD(check_constraints_method);
  dont_initialize();
  sensitive << light_NS_color;
  sensitive << light_SN_color;
  sensitive << light_EW_color;
  sensitive << light_WE_color;

  sensitive << en_axis_EW;
  sensitive << en_axis_NS;

  sensitive << NS_hasCars;
  sensitive << SN_hasCars;
  sensitive << EW_hasCars;
  sensitive << WE_hasCars;

  *out<<"time,\ten_NS,\ten_EW,\ts_NS,\ts_SN,\ts_EW,\ts_WE,\tcol_NS,\tcol_SN,\tcol_EW,\tcol_WE"<<endl;
}

Monitor::~Monitor()
{
  delete out;
}

void Monitor::monitor_method()
{
  *out<<sc_time_stamp()<<",\t"<<en_axis_NS<<",\t"<<en_axis_EW;
  *out<<",\t"<<NS_hasCars<<",\t"<<SN_hasCars<<",\t"<<EW_hasCars<<",\t"<<WE_hasCars;
  *out<<",\t"<<light_NS_color<<",\t"<<light_SN_color<<",\t"<<light_EW_color<<",\t"<<light_WE_color<<endl;
}

void Monitor::safety_constraints()
{ 
  // they are allowed to both be 0 but never to be 1 at the same time
  assert(  !( (en_axis_EW == 1) && (en_axis_NS == 1) ) && "Both roads are enabled at the same time!");
  // NS can only be green when WE and EW are red
  if(light_NS_color == LIGHT_COLOR_GREEN){
    assert((light_WE_color == LIGHT_COLOR_RED) && (light_EW_color == LIGHT_COLOR_RED));
  }
  // SN can only be green when WE and EW are red
  if(light_SN_color == LIGHT_COLOR_GREEN){
    assert((light_WE_color == LIGHT_COLOR_RED) && (light_EW_color == LIGHT_COLOR_RED));
  }
  // EW can only be green when NS and SN are red
  if(light_EW_color == LIGHT_COLOR_GREEN){
    assert((light_SN_color == LIGHT_COLOR_RED) && (light_NS_color == LIGHT_COLOR_RED));
  }
  // WE can only be green when NS and SN are red
  if(light_WE_color == LIGHT_COLOR_GREEN){
    assert((light_SN_color == LIGHT_COLOR_RED) && (light_NS_color == LIGHT_COLOR_RED));
  }
}

void Monitor::crossing_arrival_constraints()
{
  // If a vehicle arrives at the crossing, it will eventually be granted the green light
  // if (en_axis_EW == true) { // currently the EW axis is enabled 
  //   if (NS_hasCars == true) { // but a car has arrived at NS
  //     counter_arriving ++;
  //     if (counter_arriving > (TIMEOUT_BEFORE_SWITCH) ) {
  //       std::cout << "Counter Arriving ";
  //       std::cout << counter_arriving;
  //       std::cout << "\n";
  //       counter_arriving = 0;
  //       assert(en_axis_NS == true && light_NS_color == LIGHT_COLOR_GREEN);
  //     }
  //   } else {
  //     counter_arriving = 0;
  //   }
  // }

  if (NS_hasCars) {
    if (en_axis_NS) { //if the axis is enabled the arriving car should immediatly get green
    //TODO: Modify when code is changed that arriving car a few second before timeout do not get green anymore
      assert(light_NS_color == LIGHT_COLOR_GREEN);
    } else {
      counter_arriving_NS ++;
      if (light_NS_color == LIGHT_COLOR_GREEN) {
        had_green_light_NS = true;
      }
      if (counter_arriving_NS > (15) ) {
        assert(had_green_light_NS);
        counter_arriving_NS = 0;
        had_green_light_NS = false;
      }
    }
  }
  
  if (SN_hasCars) {
    counter_arriving_SN ++;
    if (light_SN_color == LIGHT_COLOR_GREEN) {
      had_green_light_SN = true;
    }
    if (counter_arriving_SN > (15) ) {
      assert(had_green_light_SN);
      counter_arriving_SN = 0;
      had_green_light_SN = false;
    }
  }

  if (EW_hasCars) {
    if (en_axis_EW) {
      assert(light_EW_color == LIGHT_COLOR_GREEN);
    } else { 
      counter_arriving_EW ++;
      if (light_EW_color == LIGHT_COLOR_GREEN) {
        had_green_light_EW = true;   
      }
      if (counter_arriving_EW > (15) ) {
        assert(had_green_light_EW);
        counter_arriving_EW = 0;
        had_green_light_EW = false;
      }
    }
  }

  if (WE_hasCars) {
    counter_arriving_WE ++;
    if (light_WE_color == LIGHT_COLOR_GREEN) {
      had_green_light_WE = true;  
    }
    if (counter_arriving_WE > (15) ) {
      assert(had_green_light_WE);
      counter_arriving_WE = 0;
      had_green_light_WE = false;
    }
  }

}

void Monitor::independent_lights_constraints()
{
  // for all cases it has to be checked if a car has already been there,
  // and hence the lights are already green 
  // since the lights do not have to switch back to red immediately after a car has crossed

  if(en_axis_NS){
    previous_car_EW = false;
    previous_car_WE = false;

    // if the light NS is green, the light SN is red if there are no cars coming in the direction SN
    if(light_NS_color == LIGHT_COLOR_GREEN){
      previous_car_NS = true;                       // set flag to true if NS light became green before SN light was green
      if (SN_hasCars) {
        previous_car_SN = true;                     // a previous car for SN already has turned the SN-Light green
      } 
      if (!SN_hasCars && !previous_car_SN) {  
        assert(light_SN_color == LIGHT_COLOR_RED);
      }
    }

    // if the light SN is green, the light NS is red if there are no cars coming in the direction NS
    if(light_SN_color == LIGHT_COLOR_GREEN){
      previous_car_SN = true;                       // set flag to true if SN light became green before NS light was green
      if (NS_hasCars) {
        previous_car_NS = true;                     // a previous car for NS already has turned the NS-Light green
      } 
      if (!NS_hasCars && !previous_car_NS) {  
        assert(light_NS_color == LIGHT_COLOR_RED);
      }
    }
  }

  if(en_axis_EW){
    previous_car_NS = false;
    previous_car_SN = false;
    // if the light EW is green, the light WE is red if there are no cars coming in the direction WE
    if(light_EW_color == LIGHT_COLOR_GREEN){
      previous_car_EW = true;                       // set flag to true if EW light became green before WE light was green
      if (WE_hasCars) {
        previous_car_WE = true;                     // a previous car for WE already has turned the WE-Light green
      } 
      if (!WE_hasCars && !previous_car_WE) {  
        assert(light_WE_color == LIGHT_COLOR_RED);
      }
    }

    // if the light WE is green, the light EW is red if there are no cars coming in the direction EW
    if(light_WE_color == LIGHT_COLOR_GREEN){
      previous_car_WE = true;                       // set flag to true if WE light became green before EW light was green
      if (EW_hasCars) {
        previous_car_EW = true;                     // a previous car for EW already has turned the EW-Light green
      } 
      if (!EW_hasCars && !previous_car_EW) {  
        assert(light_EW_color == LIGHT_COLOR_RED);
      }
    }
  }
}

void Monitor::check_constraints_method()
{
  // check the constraints via assertions in here
  safety_constraints();
  //crossing_arrival_constraints();
  independent_lights_constraints();
}

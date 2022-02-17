#include <cassert>
#include "monitor.h"
#include "light.h"
#include "controller.h"
#include <stdio.h>

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

  prev_ns=false; now_ns=false; car_waiting_ns=false;
  prev_sn=false; now_sn=false; car_waiting_sn=false;
  prev_ew=false; now_ew=false; car_waiting_ew=false;
  prev_we=false; now_we=false; car_waiting_we=false;
  eventually_ns = 0;
  eventually_sn = 0;
  eventually_ew = 0;
  eventually_we = 0;

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

  SC_THREAD(check_constraints_method);
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

  *out<<"time,\t|en_NS,\ten_EW,\t|s_NS,\ts_SN,\ts_EW,\ts_WE,\t|c_NS,\tc_SN,\tc_EW,\tc_WE"<<endl;
  emoji[LIGHT_COLOR_GREEN] = "🟢";
  emoji[LIGHT_COLOR_RED] = "🔴";
  emoji_car[0] = "0";
  emoji_car[1] = "🚙";
  emoji_sens[0] = "❌";
  emoji_sens[1] = "✅";
}

Monitor::~Monitor()
{
  delete out;
}

void Monitor::monitor_method()
{
  *out<<sc_time_stamp()<<",\t|"<<emoji_sens[en_axis_NS]<<",\t"<<emoji_sens[en_axis_EW];
  *out<<",\t|"<<emoji_car[NS_hasCars]<<",\t"<<emoji_car[SN_hasCars]<<",\t"<<emoji_car[EW_hasCars]<<",\t"<<emoji_car[WE_hasCars];
  *out<<",\t|"<<emoji[light_NS_color]<<",\t"<<emoji[light_SN_color]<<",\t"<<emoji[light_EW_color]<<",\t"<<emoji[light_WE_color]<<endl;
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
  for(;;){
  // If a vehicle arrives at the crossing, it will eventually be granted the green light
  now_ns = NS_hasCars;
  now_sn = SN_hasCars;
  now_ew = EW_hasCars;
  now_we = WE_hasCars;

  if(!car_waiting_ns){
    if(now_ns > prev_ns){ // sensor just switched 0->1
      car_waiting_ns = true; // remember that there is a car waiting
    }
  } else {
    if(now_ns < prev_ns){ // sensor just switched 1->0
      car_waiting_ns = false; // forget that ther is a car waiting
    }
  }

  if(!car_waiting_sn){
    if(now_sn > prev_sn){ // sensor just switched 0->1
      car_waiting_sn = true; // remember that there is a car waiting
    }
  } else {
    if(now_sn < prev_sn){ // sensor just switched 1->0
      car_waiting_sn = false; // forget that ther is a car waiting
    }
  }

  if(!car_waiting_ew){
    if(now_ew > prev_ew){ // sensor just switched 0->1
      car_waiting_ew = true; // remember that there is a car waiting
    }
  } else {
    if(now_ew < prev_ew){ // sensor just switched 1->0
      car_waiting_ew = false; // forget that ther is a car waiting
    }
  }

  if(!car_waiting_we){
    if(now_we > prev_we){ // sensor just switched 0->1
      car_waiting_we = true; // remember that there is a car waiting
    }
  } else {
    if(now_we < prev_we){ // sensor just switched 1->0
      car_waiting_we = false; // forget that ther is a car waiting
    }
  }

  // check independence of lights
  // when axis is enabled and a new car arrives, the light should switch to green
  if(en_axis_NS){
    if(car_waiting_ns){
      assert(light_NS_color == LIGHT_COLOR_GREEN);
    }
    if(car_waiting_sn){
      assert(light_SN_color == LIGHT_COLOR_GREEN);
    }
  }
  if(en_axis_EW){
    if(car_waiting_ew){
      assert(light_EW_color == LIGHT_COLOR_GREEN);
    }
    if(car_waiting_we){
      assert(light_WE_color == LIGHT_COLOR_GREEN);
    }
  }

  // check if the wrong axis is enabled, a waiting car will eventually be granted green
  if(NS_hasCars && (light_NS_color == LIGHT_COLOR_RED))
    eventually_ns ++;
  else
    eventually_ns = 0;
  assert(eventually_ns < 13*TIMEOUT_BEFORE_SWITCH); // controller is 1Hz, monitor is 10Hz --> 1s = 10+3 monitor cycles

  if(SN_hasCars && (light_SN_color == LIGHT_COLOR_RED))
    eventually_sn ++;
  else
    eventually_sn = 0;
  assert(eventually_sn < 13*TIMEOUT_BEFORE_SWITCH);

  if(EW_hasCars && (light_EW_color == LIGHT_COLOR_RED))
    eventually_ew ++;
  else
    eventually_ew = 0;
  assert(eventually_ew < 13*TIMEOUT_BEFORE_SWITCH);

  if(WE_hasCars && (light_WE_color == LIGHT_COLOR_RED))
    eventually_we ++;
  else
    eventually_we = 0;
  assert(eventually_we < 13*TIMEOUT_BEFORE_SWITCH);


  prev_ns = now_ns;
  prev_sn = now_sn;
  prev_ew = now_ew;
  prev_we = now_we;
  
  wait(0.1, SC_SEC);
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
  crossing_arrival_constraints();
  independent_lights_constraints();
}

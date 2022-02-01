#include <cassert>
#include "monitor.h"
#include "light.h"

Monitor::Monitor(sc_module_name name, char *outfile)
  : sc_module(name)
{
  assert(outfile != 0);
  out = new ofstream(outfile);
  assert(*out);

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
  assert(  !( (en_axis_EW == 1) && (en_axis_NS == 1) ) );
  // NS can only be green when WE and EW are red
  if(light_NS_color == LIGHT_COLOR_GREEN)
    assert(light_WE_color == LIGHT_COLOR_RED && light_EW_color == LIGHT_COLOR_RED);
  // SN can only be green when WE and EW are red
  if(light_SN_color == LIGHT_COLOR_GREEN)
    assert(light_WE_color == LIGHT_COLOR_RED && light_EW_color == LIGHT_COLOR_RED);
  // EW can only be green when NS and SN are red
  if(light_EW_color == LIGHT_COLOR_GREEN)
    assert(light_SN_color == LIGHT_COLOR_RED && light_NS_color == LIGHT_COLOR_RED);
  // WE can only be green when NS and SN are red
  if(light_WE_color == LIGHT_COLOR_GREEN)
    assert(light_SN_color == LIGHT_COLOR_RED && light_NS_color == LIGHT_COLOR_RED);
}

void Monitor::crossing_arrival_constraints()
{
  // is there some public counter needed to show that a green light will eventually be granted?
}

void Monitor::independent_lights_constraints()
{
  // if the light NS is green, the light SN is red if there are no cars coming in the direction SN
  // @todo: this assertion does not make sense
  // given that there was a car waiting at SN, SN will turn green, 
  // if the car drives, there might be no more cars. 
  // but in this case, the stop light is not supposed to go back to red
  // it is allowed to stay green
  if(en_axis_NS){
    if(light_SN_color == LIGHT_COLOR_GREEN){
      if(!NS_hasCars){
        // assert(light_NS_color == LIGHT_COLOR_RED);
      }
    }
  }
}

void Monitor::check_constraints_method()
{
  // check the constraints via assertions in here
  safety_constraints();
  independent_lights_constraints();
  
}

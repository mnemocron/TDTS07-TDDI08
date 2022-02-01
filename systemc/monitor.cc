#include <cassert>
#include "monitor.h"

Monitor::Monitor(sc_module_name name, char *outfile)
  : sc_module(name)
{
  assert(outfile != 0);
  out = new ofstream(outfile);
  assert(*out);

  SC_METHOD(monitor_method);
  dont_initialize();
  // sensitive << quotient;

  SC_METHOD(check_constraints_method);
  dont_initialize();
  // sensitive << denominator;
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
}

Monitor::~Monitor()
{
  delete out;
}

void Monitor::monitor_method()
{
  double q = 0.0; // quotient->read();
  *out << "quotient(" << sc_time_stamp() << ") = " << q << endl;
}

void Monitor::safety_constraints()
{ 
  assert(en_axis_EW != en_axis_NS);
  // NS can only be green when WE and EW are red
  assert(light_NS_color == 255 && light_WE_color == 0 && light_EW_color == 0);
  // SN can only be green when WE and EW are red
  assert(light_SN_color == 255 && light_WE_color == 0 && light_EW_color == 0);
  // EW can only be green when NS and SN are red
  assert(light_EW_color == 255 && light_NS_color == 0 && light_SN_color == 0);
  // WE can only be green when NS and SN are red
  assert(light_WE_color == 255 && light_NS_color == 0 && light_SN_color == 0);
}

void Monitor::crossing_arrival_constraints()
{
  // is there some public counter needed to show that a green light will eventually be granted?
}

void Monitor::independent_lights_constraints()
{
  // if the light NS is green, the light SN is red if there are no cars coming in the direction SN
  assert(en_axis_NS && light_NS_color == 255 && light_SN_color == 0 && !SN_hasCars);
  assert(en_axis_NS && light_SN_color == 255 && light_NS_color == 0 && !NS_hasCars);
  assert(en_axis_EW && light_EW_color == 255 && light_WE_color == 0 && !WE_hasCars);
  assert(en_axis_EW && light_WE_color == 255 && light_EW_color == 0 && !EW_hasCars);
}

void Monitor::check_constraints_method()
{
  // check the constraints via assertions in here
  safety_constraints();
  independent_lights_constraints();
  
  
  // assert(denominator != 0);
}

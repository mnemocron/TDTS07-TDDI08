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
  //sensitive << light_NS_color;
  //sensitive << light_SN_color;
  //sensitive << light_EW_color;
  //sensitive << light_WE_color;
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

void Monitor::check_constraints_method()
{
  // check the constraints via assertions in here

  // EW can only be green when NS and SN are red
  //assert(light_EW_color == 1 && light_NS_color == 0 && light_SN_color == 0);
  // WE can only be green when NS and SN are red
  //assert(light_WE_color == 1 && light_NS_color == 0 && light_SN_color == 0);
  // NS can only be green when WE and EW are red
  //assert(light_NS_color == 1 && light_WE_color == 0 && light_EW_color == 0);
  // SN can only be green when WE and EW are red
  //assert(light_SN_color == 1 && light_WE_color == 0 && light_EW_color == 0);
  // assert(denominator != 0);
}

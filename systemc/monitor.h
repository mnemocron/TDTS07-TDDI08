#ifndef MONITOR_H
#define MONITOR_H

#include <systemc.h>
#include <fstream>

using std::ofstream;

SC_MODULE(Monitor) {
  sc_in<int> light_NS_color;
  sc_in<int> light_SN_color;
  sc_in<int> light_EW_color;
  sc_in<int> light_WE_color;

  SC_HAS_PROCESS(Monitor);
  Monitor(sc_module_name name, char *outfile);
  ~Monitor();

  void monitor_method();
  void check_constraints_method();

  ofstream *out;
};

#endif // MONITOR_H

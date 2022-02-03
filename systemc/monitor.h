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

  sc_in<bool> NS_hasCars;
  sc_in<bool> SN_hasCars;
  sc_in<bool> EW_hasCars;
  sc_in<bool> WE_hasCars;

  sc_in<bool> en_axis_NS;
  sc_in<bool> en_axis_EW;

  int counter_arriving;

  bool previous_car_NS;
  bool previous_car_SN;
  bool previous_car_EW;
  bool previous_car_WE;
  

  SC_HAS_PROCESS(Monitor);
  Monitor(sc_module_name name, char *outfile);
  ~Monitor();

  void monitor_method();
  void safety_constraints();
  void crossing_arrival_constraints();
  void independent_lights_constraints();
  void check_constraints_method();

  ofstream *out;
};

#endif // MONITOR_H

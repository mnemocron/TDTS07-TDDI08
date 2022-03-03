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

  sc_in<bool> car_waiting_NS;
  sc_in<bool> car_waiting_SN;
  sc_in<bool> car_waiting_EW;
  sc_in<bool> car_waiting_WE;

  int counter_arriving_NS;
  int counter_arriving_SN;
  int counter_arriving_EW;
  int counter_arriving_WE;

  bool had_green_light_NS;
  bool had_green_light_SN;
  bool had_green_light_EW;
  bool had_green_light_WE;

  bool previous_car_NS;
  bool previous_car_SN;
  bool previous_car_EW;
  bool previous_car_WE;
  
  // edge detection on sensor signals
  bool prev_ns, now_ns, car_waiting_ns;
  bool prev_sn, now_sn, car_waiting_sn;
  bool prev_ew, now_ew, car_waiting_ew;
  bool prev_we, now_we, car_waiting_we;
  int eventually_ns, eventually_sn, eventually_ew, eventually_we;

  SC_HAS_PROCESS(Monitor);
  Monitor(sc_module_name name, char *outfile);
  ~Monitor();

  void monitor_method();
  void safety_constraints();
  void crossing_arrival_constraints();
  void independent_lights_constraints();
  void check_constraints_method();

  ofstream *out;
  const char *emoji[256];  // for lights
  const char *emoji_car[2];
  const char *emoji_sens[2];
};

#endif // MONITOR_H

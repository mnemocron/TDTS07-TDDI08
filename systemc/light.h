#ifndef LIGHT_H
#define LIGHT_H

#include <systemc.h>

#define LIGHT_POS_NS 1
#define LIGHT_POS_SN 2
#define LIGHT_POS_WE 3
#define LIGHT_POS_EW 4

#define LIGHT_COLOR_RED   0
#define LIGHT_COLOR_GREEN 255

#define TIME_FOR_CROSSING 2  // in seconds

SC_MODULE(Light) {
  sc_in<bool> sensor;
  sc_in<bool> en_road;
  // sc_out<bool> haveCars;
  sc_out<int> color;
  sc_out<int> car_amount;

  int counter;

  SC_HAS_PROCESS(Light);
  Light(sc_module_name name);

  void loop();

};



#endif // LIGHT_H

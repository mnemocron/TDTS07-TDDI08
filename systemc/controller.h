#ifndef CONTROLLER_H
#define CONTROLLER_H

#define ROAD_DIRECTION_FREE 0
#define ROAD_DIRECTION_NS   127
#define ROAD_DIRECTION_EW   255

#define TIMEOUT_BEFORE_SWITCH 10 // in seconds

#define STATE_FREE 0
#define STATE_NS_AXIS 1
#define STATE_EW_AXIS 2

#include <systemc.h>

SC_MODULE(Controller) {
  sc_out<bool> en_axis_NS;
  sc_out<bool> en_axis_EW;
  sc_in<bool>  NS_hasCars;
  sc_in<bool>  SN_hasCars;
  sc_in<bool>  EW_hasCars;
  sc_in<bool>  WE_hasCars;

  int state_now, state_next;
  int counter;

  SC_HAS_PROCESS(Controller);
  Controller(sc_module_name name);

  void loop();
};

#endif // CONTROLLER_H

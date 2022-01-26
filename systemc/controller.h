#ifndef CONTROLLER_H
#define CONTROLLER_H

#define ROAD_DIRECTION_FREE 0
#define ROAD_DIRECTION_NS   127
#define ROAD_DIRECTION_EW   255

#define TIMEOUT_BEFORE_SWITCH 10 // in seconds

#include <systemc.h>

SC_MODULE(Controller) {
  sc_out<int>roadMutex;
  sc_out<int>mutexDirection;
  int counter;
  int queueLine;

  SC_HAS_PROCESS(Controller);
  Controller(sc_module_name name);

  void Controller::loop();
  int Controller::get_open_road_direction(int lightpos);
};

#endif // CONTROLLER_H

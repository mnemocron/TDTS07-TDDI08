#ifndef SENSOR_H
#define SENSOR_H

#include <systemc.h>
#include <fstream>

SC_MODULE(Sensor) {

  ifstream traffic;

  SC_HAS_PROCESS(Sensor);
  Sensor(sc_module_name name);

  void loop();

};

#endif // SENSOR_H

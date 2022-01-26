#ifndef SENSOR_H
#define SENSOR_H

#include <systemc.h>

SC_MODULE(Sensor) {

  SC_HAS_PROCESS(Sensor);
  Sensor(sc_module_name name);

};

#endif // SENSOR_H

#include "sensor.h"

Sensor::Sensor(sc_module_name name)
  : sc_module(name)
{

  //SC_METHOD(divide_method);
  dont_initialize();
}

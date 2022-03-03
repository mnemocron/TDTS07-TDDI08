#include "light.h"
#include <iostream>

Light::Light(sc_module_name name)
  : sc_module(name)
{
  color.initialize(LIGHT_COLOR_RED);

  SC_METHOD(loop);
  dont_initialize();
  sensitive << sensor << en_road;
}

void Light::loop()
{
  if(en_road->read() == true){
    if(sensor->read() == true || car_waiting->read() == true){
      color->write(LIGHT_COLOR_GREEN);
      car_waiting->write(false);
    }
  } else {
    if (sensor->read() == true) {
      car_waiting->write(true);
    }
    color->write(LIGHT_COLOR_RED);
  }
}

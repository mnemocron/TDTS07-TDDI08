#include "light.h"

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
    if(sensor->read() == true){
      // haveCars->write(true);
      color->write(LIGHT_COLOR_GREEN);
    }
  } else {
    // haveCars->write(false);
    color->write(LIGHT_COLOR_RED);
  }
}

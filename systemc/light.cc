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
  if(sensor->read() == true){
    // haveCars->write(true);
    if(en_road->read() == true){
      color->write(LIGHT_COLOR_GREEN);
    }
  } else {
    // haveCars->write(false);
    color->write(LIGHT_COLOR_RED);
  }
  // wait(1, SC_SEC);   // is this necessary, if it is triggered by sensitivity?
}

#include "light.h"

Light::Light(sc_module_name name, int lightpos)
  : sc_module(name)
{
  color.initialize(LIGHT_COLOR_RED);

  SC_METHOD(loop);
  dont_initialize();
}

void Light::loop()
{
  for(;;){
    wait(1, SC_SEC);
  }
}

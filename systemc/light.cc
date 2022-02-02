#include "light.h"

Light::Light(sc_module_name name)
  : sc_module(name)
{
  color.initialize(LIGHT_COLOR_RED);

  counter = 0;

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
      counter ++;
      std::cout << counter;
      std::cout << "\n";
      if (counter >= TIME_FOR_CROSSING) {
        std::cout << "CROSSED";
        std::cout << "\n";
        car_amount->write(car_amount->read() - 1);
        counter = 0;
      }
    }
  } else {
    // haveCars->write(false);
    color->write(LIGHT_COLOR_RED);
    counter = 0;
  }
}

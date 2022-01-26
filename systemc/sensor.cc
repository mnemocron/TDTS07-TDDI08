#include "sensor.h"

Sensor::Sensor(sc_module_name name)
  : sc_module(name)
{

  SC_METHOD(loop);
  dont_initialize();
}

void Sensor::loop()
{
  traffic.open("traffic_hardcoded.txt");
  if (traffic.is_open()) {
    std::string line;
    while (std::getline(traffic, line)) {
        // using printf() in all tests for consistency
        printf("%s", line.c_str());
    }
    traffic.close();
}
}


#include "sensor.h"
#include <iostream>

Sensor::Sensor(sc_module_name name, char *datafile)
  : sc_module(name)
{

  assert(datafile != 0);       // An input file should be given.

  sensor_in = new ifstream(datafile); // Open the input file.
  assert(*sensor_in);

  SC_THREAD(generate_stimuli);
  //dont_initialize();
}

Sensor::~Sensor()
{
  delete sensor_in;
}

void Sensor::generate_stimuli()
{
  int ns;
  int sn;
  int ew;
  int we;
  for (;;) {
    wait(1, SC_SEC);     // Generate new inputs every second.
    *sensor_in >> ns >> sn >> ew >> we; // Read from the input file.
    //std::cout << sc_time_stamp();
    // std::cout << ns;
    // std::cout << sn;
    // std::cout << ew;
    // std::cout << we;
    state_NS->write(ns);
    state_SN->write(sn);
    state_EW->write(ew);
    state_WE->write(we);
    nr_state_NS->write(nr_state_NS->read() + ns);
    nr_state_SN->write(nr_state_SN->read() + sn);
    nr_state_EW->write(nr_state_EW->read() + ew);
    nr_state_WE->write(nr_state_WE->read() + we);
    // std::cout << nr_state_NS;
    // std::cout << nr_state_SN;
    // std::cout << nr_state_EW;
    // std::cout << nr_state_WE;
  }

}

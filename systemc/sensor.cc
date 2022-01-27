#include "sensor.h"

Sensor::Sensor(sc_module_name name, char *datafile)
  : sc_module(name)
{

  assert(datafile != 0);       // An input file should be given.

  sensor_in = new ifstream(datafile); // Open the input file.
  assert(*sensor_in);

  SC_THREAD(generate_stimuli);
  state.initialize(NOT_WAITING);
}

/*Sensor::~Sensor()
{
  delete sensor_in;
};*/

void Sensor::generate_stimuli()
{
  /*if(state->read() == 0){
    if (counter > MAX_WAITING) {
      counter = 0;
    }

  } else {
    counter++;
  }*/
  int current;
  for (;;) {
    wait(1, SC_SEC);     // Generate new inputs every second.
    *sensor_in >> current; // Read from the input file.
    printf("%c", current);
    state->write(current);
  }

};


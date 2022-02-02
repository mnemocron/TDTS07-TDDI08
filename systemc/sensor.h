#ifndef SENSOR_H
#define SENSOR_H

#include <systemc.h>
#include <fstream>

using std::ifstream;

#define NOT_WAITING 0
#define WAITING 1

#define MAX_WAITING 10 // in seconds

SC_MODULE(Sensor) {
  sc_out<bool> state_NS;
  sc_out<bool> state_SN;
  sc_out<bool> state_EW;
  sc_out<bool> state_WE;

  sc_out<int> nr_state_NS;
  sc_out<int> nr_state_SN;
  sc_out<int> nr_state_EW;
  sc_out<int> nr_state_WE;

  int counter;

  SC_HAS_PROCESS(Sensor);
  Sensor(sc_module_name name, char *datafile);
  ~Sensor();

  void generate_stimuli();

  ifstream *sensor_in;

};

#endif // SENSOR_H

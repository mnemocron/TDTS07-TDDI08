#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <systemc.h>

SC_MODULE(Controller) {

  SC_HAS_PROCESS(Controller);
  Controller(sc_module_name name);

};

#endif // CONTROLLER_H

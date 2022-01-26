#ifndef LIGHT_H
#define LIGHT_H

#include <systemc.h>

SC_MODULE(Light) {

  SC_HAS_PROCESS(Light);
  Light(sc_module_name name);

};

#endif // LIGHT_H

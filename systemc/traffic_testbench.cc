#include <systemc.h>
#include "monitor.h"
#include "light.h"
#include "sensor.h"
#include "controller.h"

int sc_main(int argc, char **argv)
{
  // The command-line arguments are as follows:
  // 1. the simulation time (in seconds),
  // 2. the file with input data (see input.txt), and
  // 3. the file to write output data.
  assert(argc == 4);

  sc_time sim_time(atof(argv[1]), SC_SEC);
  char *infile = argv[2];
  char *outfile = argv[3];

  // Create channels.
  // sc_signal<int> numerator_sig;

  // Instantiate modules.
  // Divider divider("Divider");

  // Connect the channels to the ports.
  // divider(numerator_sig,denominator_sig,quotient_sig);

  // Start the simulation.
  sc_start(sim_time);

  return 0;
}

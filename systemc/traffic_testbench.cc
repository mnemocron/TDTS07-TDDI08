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
  sc_signal<bool> NS_hasCars;
  sc_signal<bool> SN_hasCars;
  sc_signal<bool> EW_hasCars;
  sc_signal<bool> WE_hasCars;
  sc_signal<bool> en_axis_NS;
  sc_signal<bool> en_axis_EW;
  sc_signal<int>  light_NS_color;
  sc_signal<int>  light_SN_color;
  sc_signal<int>  light_EW_color;
  sc_signal<int>  light_WE_color;
  sc_signal<bool>  sensor_NS;
  sc_signal<bool>  sensor_SN;
  sc_signal<bool>  sensor_EW;
  sc_signal<bool>  sensor_WE;
  sc_signal<int> state;

  // Instantiate modules.
  Light light_NS("Light_NS");
  Light light_SN("Light_SN");
  Light light_WE("Light_WE");
  Light light_EW("Light_EW");
  Controller coordinator("Light_Controller");
  Sensor sensor("Sensor", infile);
  Monitor monitor("Monitor", outfile);

  // Port MAP
  coordinator.en_axis_NS ( en_axis_NS );
  coordinator.en_axis_EW ( en_axis_EW );
  coordinator.NS_hasCars ( NS_hasCars );
  coordinator.SN_hasCars ( SN_hasCars );
  coordinator.EW_hasCars ( EW_hasCars );
  coordinator.WE_hasCars ( WE_hasCars );

  light_NS.en_road ( en_axis_NS );
  light_SN.en_road ( en_axis_NS );
  light_EW.en_road ( en_axis_EW );
  light_WE.en_road ( en_axis_EW );

  light_NS.haveCars ( NS_hasCars );
  light_SN.haveCars ( SN_hasCars );
  light_EW.haveCars ( EW_hasCars );
  light_WE.haveCars ( WE_hasCars );

  light_NS.color ( light_NS_color );
  light_SN.color ( light_SN_color );
  light_EW.color ( light_EW_color );
  light_WE.color ( light_WE_color );

  light_NS.sensor ( sensor_NS );
  light_SN.sensor ( sensor_SN );
  light_EW.sensor ( sensor_EW );
  light_WE.sensor ( sensor_WE );

  sensor.state ( state );

  monitor.light_NS_color(light_NS_color);
  monitor.light_SN_color(light_SN_color);
  monitor.light_EW_color(light_EW_color);
  monitor.light_WE_color(light_WE_color);

  // Start the simulation.
  sc_start(sim_time);

  return 0;
}

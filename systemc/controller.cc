#include "controller.h"

Controller::Controller(sc_module_name name)
  : sc_module(name)
{
  roadMutex.initialize(ROAD_DIRECTION_FREE);
  // mutexDirection.initialize(ROAD_DIRECTION_FREE);
  counter = 0;
  queueLine = 0;

  // SC_METHOD(divide_method);
  dont_initialize();
}

void Controller::loop()
{
  for(;;){
    if(roadMutex != ROAD_DIRECTION_FREE){
      if(queueLine > 0){
        counter++;
        if(counter > TIMEOUT_BEFORE_SWITCH){
          queueLine = 0;
          counter = 0;
          // revoke mutex from any light that has it
          roadMutex.write(ROAD_DIRECTION_FREE); 
        }
      }
    }
    wait(1, SC_SEC);
  }
}

int Controller::get_open_road_direction(int lightpos)
{
  if(roadMutex == ROAD_DIRECTION_FREE){
    if(lightpos == LIGHT_POS_NS || lightpos == LIGHT_POS_SN){
      roadMutex = ROAD_DIRECTION_NS;
    }
    if(lightpos == LIGHT_POS_EW || lightpos == LIGHT_POS_WE){
      roadMutex = ROAD_DIRECTION_EW;
    }
  }
  return 0;
}
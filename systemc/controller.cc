#include "controller.h"

Controller::Controller(sc_module_name name)
  : sc_module(name)
{
  en_axis_NS.initialize(false);
  en_axis_EW.initialize(false);

  state_now  = STATE_FREE;
  state_next = STATE_FREE;

  SC_METHOD(loop);
  dont_initialize();
}

void Controller::loop()
{
  for(;;){
    // Frage: Ist es im Moment auch umgestetzt, dass NS und SN, 
    // sowie EW und EW jeweils auch independently schalten?
    switch(state_now){
      case(STATE_FREE):
      // Frage: kann es hier passieren, dass auf einmal alle 4 Ampeln grün sind?
        if(NS_hasCars.read() == true || SN_hasCars.read() == true){
          state_next = STATE_NS_AXIS;
          en_axis_EW.write(false);
          en_axis_NS.write(true);
          counter = 0;
        }
        if(EW_hasCars.read() == true || EW_hasCars.read() == true){
          state_next = STATE_EW_AXIS;
          en_axis_EW.write(true);
          en_axis_NS.write(false);
          counter = 0;
        }
        break;

      case(STATE_NS_AXIS):
        if(EW_hasCars.read() == true || WE_hasCars.read() == true){
          counter ++;
          if(counter > TIMEOUT_BEFORE_SWITCH){
            counter = 0;
            state_next = STATE_EW_AXIS;
            en_axis_EW.write(true);
            en_axis_NS.write(false);
          }
        } else {
          if(NS_hasCars.read() == false && SN_hasCars.read() == false){
            state_next = STATE_FREE;
            en_axis_EW.write(false);
            en_axis_NS.write(false);
          }
        }
        break;

      case(STATE_EW_AXIS):
        if(NS_hasCars.read() == true || SN_hasCars.read() == true){
          counter ++;
          if(counter > TIMEOUT_BEFORE_SWITCH){
            counter = 0;
            state_next = STATE_NS_AXIS;
            en_axis_EW.write(false);
            en_axis_NS.write(true);
          }
        } else {
          if(EW_hasCars.read() == false && WE_hasCars.read() == false){
            state_next = STATE_FREE;
            en_axis_EW.write(false);
            en_axis_NS.write(false);
          }
        }
        break;
      default:
        state_next = STATE_FREE;
        break;
    }
    wait(1, SC_SEC);
    state_now = state_next;
  }
}


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
    switch(state_now){
      case(STATE_FREE):
        if(NS_hasCars.read() == true || SN_hasCars.read() == true){
          state_next = STATE_NS_AXIS;
          en_axis_EW.write(false);
          en_axis_NS.write(true);
          counter = 0;
        } else if(EW_hasCars.read() == true || EW_hasCars.read() == true){
          state_next = STATE_EW_AXIS;
          en_axis_EW.write(true);
          en_axis_NS.write(false);
          counter = 0;
        }
        break;

      case(STATE_NS_AXIS):
        // if the other axis has cars waiting
        if(EW_hasCars.read() == true || WE_hasCars.read() == true){
          counter ++; // start counting down before switching to other axis
          if(counter > TIMEOUT_BEFORE_SWITCH){
            counter = 0;
            state_next = STATE_EW_AXIS;
            en_axis_NS.write(false);        // turn red
            wait(TIMEOUT_DEADTIME, SC_SEC); // wait before allowing GREEN
            en_axis_EW.write(true);         // turn green
          }
        } else {
          // if no car is here, free up the road
          if(NS_hasCars.read() == false && SN_hasCars.read() == false){
            state_next = STATE_FREE;
            en_axis_EW.write(false);
            en_axis_NS.write(false);
          }
        }
        break;

      case(STATE_EW_AXIS):
        // if the other axis has cars waiting
        if(NS_hasCars.read() == true || SN_hasCars.read() == true){
          counter ++; // start counting down before switching to other axis
          if(counter > TIMEOUT_BEFORE_SWITCH){
            counter = 0;
            state_next = STATE_NS_AXIS;
            en_axis_EW.write(false);        // turn red
            wait(TIMEOUT_DEADTIME, SC_SEC); // wait before allowing GREEN
            en_axis_NS.write(true);         // turn green
          }
        } else {
          // if no car is here, free up the road
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


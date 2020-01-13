/* Project: DZ smoke machines 2020
   Author:  Job Heijlighen
   Date:    13-01-20
   Version: 1.0
*/

#include <lib_dmx.h> 

#define    DMX512     (0)    // (250 kbaud - 2 to 512 channels) Standard USITT DMX-512
#define    DMX1024    (1)    // (500 kbaud - 2 to 1024 channels) Completely non standard - TESTED ok
#define    DMX2048    (2)    // (1000 kbaud - 2 to 2048 channels) called by manufacturers DMX1000K, DMX 4x or DMX 1M ???
#define     trigger 4

bool trigger_state;
bool trigger_old;
bool set;

void setup()
{

  pinMode(trigger, INPUT);
  digitalWrite(trigger, HIGH);
  trigger_old = true;
  ArduinoDmx0.set_tx_address(1);
  ArduinoDmx0.set_tx_channels(100);
  ArduinoDmx0.init_tx(DMX512);
}

void loop()
{

  if (digitalRead(trigger) == LOW) {
    trigger_state = false;
  } else {
    trigger_state = true;
  }

  if (trigger_state != trigger_old) {
    set = true;
    trigger_old = trigger_state;
  }

  if (set && (trigger_state == false)) {
    ArduinoDmx0.TxBuffer[0] = 255;
    ArduinoDmx0.TxBuffer[1] = 255;
    ArduinoDmx0.TxBuffer[2] = 255;
    ArduinoDmx0.TxBuffer[3] = 255;
    set = false;
  } else if (set && (trigger_state == true)) {
    ArduinoDmx0.TxBuffer[0] = 0;
    ArduinoDmx0.TxBuffer[1] = 0;
    ArduinoDmx0.TxBuffer[2] = 0;
    ArduinoDmx0.TxBuffer[3] = 0;
    set = false;
  }


}  

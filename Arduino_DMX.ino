//************************************************************************************************************************
#include <lib_dmx.h>  // libreria DMX 4 universos   // deskontrol four universes DMX library  - www.deskontrol.net/blog

//*********************************************************************************************************
//                        New DMX modes *** EXPERIMENTAL ***
//*********************************************************************************************************
#define    DMX512     (0)    // (250 kbaud - 2 to 512 channels) Standard USITT DMX-512
#define    DMX1024    (1)    // (500 kbaud - 2 to 1024 channels) Completely non standard - TESTED ok
#define    DMX2048    (2)    // (1000 kbaud - 2 to 2048 channels) called by manufacturers DMX1000K, DMX 4x or DMX 1M ???
#define     trigger 4

bool trigger_state;
bool trigger_old;
bool set;

void setup()
{
  // configurar pines arduino del 2 al 13 como entradas con pullup, (cuando se pulsa el boton = 0 si no = 1)
  // configure arduino pins 2 to 13 as inputs with pullup, (button pressed = 0, button free = 1)
  pinMode(trigger, INPUT);           // pines como entradas
  // pins as inputs
  digitalWrite(trigger, HIGH);       // activar resistencias pullup internas
  // turn on pullup internal resistors
trigger_old =true;

  ArduinoDmx0.set_tx_address(1);      // poner aqui la direccion de inicio de DMX
  // put here DMX start address

  ArduinoDmx0.set_tx_channels(100);   // poner aqui el numero de canales a transmitir
  // put here the number of DMX channels to transmmit

  ArduinoDmx0.init_tx(DMX512);        // iniciar transmision universo 0, modo estandar DMX512
  // starts universe 0 as TX, standard mode DMX512
}  //end setup()

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


}  //end loop()


//************************************************************************************************************************

#include <Arduino.h>
#include "bus.h"

//simple script for manipulating the upd7220 graphics chip

void setup() {
  Serial.begin(115200);
  while(!Serial);
  delay(500);
  command_write(0x00); //reset command
  param_write(0x02); //no dram, non interlaced, graphics mode, only draw during sync
  param_write(38); //40 active display words per line - 2 (640 pixels)
  param_write(0x45); //hsync width (6 words) - 1 , and vsync width lower 3 bits (2)
  param_write(0x00); //hsync frontporch (1 word) - 1, and vsync width upper 2 bits
  param_write(0x02); //hsync back porch (3 words) - 1
  param_write(0x0A); //vsync front porch width (10 lines)
  param_write(0xE0); //active lines (480) lower 8 bits
  param_write(0x85); // active lines upper 2 bits + vertical back porch
  delay(40); //give it some time to think

  command_write(0x6F); //vsync command, let chip know it is the master gdc and not to look for an external vsync signal

  



  command_write(0x6B); //start the timing chain

  }

void loop() {
  Serial.println(status_read());
  delay(5);
}

#include "bus.h"
#include "pins.h"

void setup_bus(){
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);

  digitalWrite(d0, 0);
  digitalWrite(d1, 0);
  digitalWrite(d2, 0);
  digitalWrite(d3, 0);
  digitalWrite(d4, 0);
  digitalWrite(d5, 0);
  digitalWrite(d6, 0);
  digitalWrite(d7, 0);

  pinMode(ad0, OUTPUT);
  digitalWrite(ad0, 0);

  // write these high so we dont accidentally write to the bus
  pinMode(wr, OUTPUT);
  digitalWrite(wr, 1);
  pinMode(rd, OUTPUT);
  digitalWrite(rd, 1);
  pinMode(cs, OUTPUT);
  digitalWrite(cs, 1);
}

void bus_write(uint8_t data){
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);

  digitalWrite(d0, (data & 1) ? 1 : 0);
  digitalWrite(d1, (data & 2) ? 1 : 0);
  digitalWrite(d2, (data & 4) ? 1 : 0);
  digitalWrite(d3, (data & 8) ? 1 : 0);
  digitalWrite(d4, (data & 16) ? 1 : 0);
  digitalWrite(d5, (data & 32) ? 1 : 0);
  digitalWrite(d6, (data & 64) ? 1 : 0);
  digitalWrite(d7, (data & 128) ? 1 : 0);

  digitalWrite(cs, 0);
  digitalWrite(wr, 0);
  delay(1); //give the chip a chance to read the bus, in reality this is like 100x too long
  digitalWrite(cs, 1);
  digitalWrite(wr, 1);
}

uint8_t bus_read(){
  uint8_t data = 0;
  pinMode(d0, INPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
  pinMode(d5, INPUT);
  pinMode(d6, INPUT);
  pinMode(d7, INPUT);

  digitalWrite(cs, 0);
  digitalWrite(rd, 0);
  delay(1); //give the chip a chance to output its data, in reality this is like 100x too long

  if(digitalRead(d0) == 1)data |= 1;
  if(digitalRead(d1) == 1)data |= 2;
  if(digitalRead(d2) == 1)data |= 4;
  if(digitalRead(d3) == 1)data |= 8;
  if(digitalRead(d4) == 1)data |= 16;
  if(digitalRead(d5) == 1)data |= 32;
  if(digitalRead(d6) == 1)data |= 64;
  if(digitalRead(d7) == 1)data |= 128;

  digitalWrite(cs, 1);
  digitalWrite(rd, 1);

  return data;
}

uint8_t fifo_read(){
  digitalWrite(ad0,1);
  return bus_read();
}

uint8_t status_read(){
  digitalWrite(ad0,0);
  return bus_read();
}

void command_write(uint8_t data){
  digitalWrite(ad0,1);
  bus_write(data);
  
}

void param_write(uint8_t data){
  digitalWrite(ad0,0);
  bus_write(data);
}

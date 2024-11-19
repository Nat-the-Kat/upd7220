#pragma once
#include <Arduino.h>

void setup_bus();

void bus_write(uint8_t data);

uint8_t bus_read();

uint8_t fifo_read();

uint8_t status_read();

void command_write(uint8_t data);

void param_write(uint8_t data);


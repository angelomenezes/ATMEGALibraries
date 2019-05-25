/*
    MUX74HC595.cpp - Library developed for testing the 8bit Multiplexer 74HC595
    Created by Angelo G. Menezes, January 13, 2018.
    Released into the public domain
*/

#include "Arduino.h"
#include "MUX74HC595.h"

MUX74HC595::MUX74HC595(int cs_pin)
{
	_cs_pin = cs_pin;
}

// As I have daisy chained in my design 2 MUX, I'm sending 2 bytes via SPI to be interpreted
// by each device individually.

void MUX74HC595::writeMUX(byte analog_input, byte analog_output)
{	
    SPI.beginTransaction(SPISettings(100000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs_pin, LOW);
    SPI.transfer(analog_output); // The first byte is going to be propagated to the second device in the chain (analog output)
    SPI.transfer(analog_input); // The second byte is going to stay at the first device (analog input)
    digitalWrite(_cs_pin, HIGH);
    SPI.endTransaction;
}

void MUX74HC595::writeMUX_only_one(byte analog_output)
{   
    SPI.beginTransaction(SPISettings(100000000, MSBFIRST, SPI_MODE0));
    digitalWrite(_cs_pin, LOW);
    SPI.transfer(analog_output); // Send only one byte (for the case we have only one MUX)
    digitalWrite(_cs_pin, HIGH);
    SPI.endTransaction;
}


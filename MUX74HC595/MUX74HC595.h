/*
    MUX74HC595.cpp - Library developed for testing the 8bit Multiplexer 74HC595
    Created by Angelo G. Menezes, January 13, 2018.
    Released into the public domain
*/

#ifndef MUX74HC595_h
#define MUX74HC595_h


#include <SPI.h>
#include "Arduino.h"

class MUX74HC595
{
    public:
        MUX74HC595(int cs_pin);
        void writeMUX(byte analog_input, byte analog_output);
        void writeMUX_only_one(byte analog_output);
    private:
        int _cs_pin;
};

#endif
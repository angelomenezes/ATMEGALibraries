/*
    DAC7715.h - Library developed for testing the 12 bits Digital-to-Analog converter DAC7715
    Created by Angelo G. Menezes, January 13, 2018.
    Released into the public domain
*/

#ifndef DAC7715_h
#define DAC7715_h


#include <SPI.h>
#include "Arduino.h"

class DAC7715
{
    public:
        DAC7715(int cs_pin, int loadreg_pin, int loaddac_pin);
        void writeDAC(uint16_t valor_DAC, int dac_pin);
    private:
        int _cs_pin, _loadreg_pin, _loaddac_pin;
        uint16_t DAC_plus_REG;
        int low_byte, high_byte;
		int reg[4];
};

#endif
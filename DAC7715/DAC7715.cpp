/*
    DAC7715.cpp - Library developed for testing the 12 bits Digital-to-Analog converter DAC7715
    Created by Angelo G. Menezes, January 13, 2018.
    Released into the public domain
*/

#include "Arduino.h"
#include "DAC7715.h"

DAC7715::DAC7715(int cs_pin, int loadreg_pin, int loaddac_pin)
{
	_cs_pin = cs_pin;
	_loadreg_pin = loadreg_pin;
	_loaddac_pin = loaddac_pin;
    
    reg[0] = 0; // DAC output channel 1
	reg[1] = 16384; // DAC output channel 2
	reg[2] = 32768; // DAC output channel 3
	reg[3] = 49152; // DAC output channel 4
}

void DAC7715::writeDAC(uint16_t valor_DAC, int dac_pin){

    DAC_plus_REG = valor_DAC + reg[dac_pin];
    
    low_byte = lowByte(DAC_plus_REG);
    high_byte = highByte(DAC_plus_REG);

    digitalWrite(_cs_pin, LOW);
    SPI.beginTransaction(SPISettings(125000000, MSBFIRST, SPI_MODE3));
    SPI.transfer(high_byte);
    SPI.transfer(low_byte);
    SPI.endTransaction();
    digitalWrite(_cs_pin, HIGH);
        
    digitalWrite(_loadreg_pin, LOW);
    __asm__("nop\n\t");
    digitalWrite(_loadreg_pin, HIGH);

    //delayMicroseconds(500);
    //__asm__("nop\n\t");
        
    digitalWrite(_loaddac_pin, LOW);
    __asm__("nop\n\t");
    digitalWrite(_loaddac_pin, HIGH);  

}

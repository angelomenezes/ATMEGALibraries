/*
    ADC.cpp - Library developed for exploring all functionalities of the ADS1118
    Created by Angelo G. Menezes, January 13, 2018.
    Released into the public domain
*/

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define USE_SCK_PIN 50
#elif defined(__AVR_ATmega328P__)
#define USE_SCK_PIN 12
#endif

#include "Arduino.h"
#include "ADS1118.h"

ADS1118::ADS1118(int cs_pin)
{
	_cs_pin = cs_pin;
}

static uint16_t ADS1118::writeSPI16(uint16_t data_in, uint16_t pin_CS) {
    uint16_t data_out=0;
    //SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));
    // max clock speed is 4 MHz, but we'll use 2 MHz to be safe
    
    digitalWrite(pin_CS, LOW);
    //delayMicroseconds(1);
    data_out |= ((SPI.transfer((data_in>>8) & 0xFF)) << 8);
    data_out |=  (SPI.transfer( data_in     & 0xFF));
    //delayMicroseconds(1);
    digitalWrite(pin_CS, HIGH);
    SPI.endTransaction;
    //SPI.end();
    //delayMicroseconds(1);
    
    return data_out;
}



uint16_t ADS1118::readADC(uint8_t channel) {
    int16_t return_val;
    
    if (channel > 3) {
        return 0;
    }
    
    uint16_t config = ADS1118_CONFIG_SS_START_ON |  // turn on single shot mode
                      ADS1118_CONFIG_MODE_SINGLE |  // power down after sample
                      ADS1118_CONFIG_DR_128SPS   |  // 128 samples per sec (default)
                      ADS1118_CONFIG_TS_MODE_ADC |  // read ADC, not temp
                      ADS1118_CONFIG_PULL_UP_ON  |  // pull-ups on (default)
                      ADS1118_CONFIG_NOP_VALID   |  // this is valid data (default)
                      ADS1118_CONFIG_RESV;          // reserved bits must be set to 1
    
    config |= m_gain;
    
    switch (channel) {
        case(0):
            config |= ADS1118_CONFIG_MUX_SINGLE_0;
            break;
        case(1):
            config |= ADS1118_CONFIG_MUX_SINGLE_1;
            break;
        case(2):
            config |= ADS1118_CONFIG_MUX_SINGLE_2;
            break;
        case(3):
            config |= ADS1118_CONFIG_MUX_SINGLE_3;
            break;
    }
    
    writeSPI16(config, _cs_pin);
    
    // Set a timeout for 16 ms, twice what is required
    // Monitor DOUT/nDRDY after pulling CS low
    // nDRDY low indicates data is ready
    int i;
    //pinMode(_cs_pin, OUTPUT);
    //pinMode(12, INPUT);
    for (i=16; i>=0; i--) {
        int j;
        /*ATOMIC_BLOCK() {
            pinResetFast(_cs_pin);
            delayMicroseconds(1);       // at least 100 ns to meet t_CSDOD
            j = pinReadFast(12);
            pinSetFast(_cs_pin);
        }*/

        digitalWrite(_cs_pin, LOW);
        //delayMicroseconds(1);
        j = digitalRead(USE_SCK_PIN);
        digitalWrite(_cs_pin, HIGH);
        
        if (!j) {
            break;
        } else {
            delay(1);
        }
    }
    if (i<0) { //timeout
        return 0;
    }
    
    
    return_val = writeSPI16(config, _cs_pin);
    delayMicroseconds(2400);
    return return_val;
}


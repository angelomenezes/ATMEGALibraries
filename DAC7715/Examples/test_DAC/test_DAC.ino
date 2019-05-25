#include <DAC7715.h>

//-------------------   DAC VAR   -------------------

// LOAD_REG and LOAD_DAC pins are necessary for setting the right values for each
// register that corresponds to an output
// CS_DAC is the chip select pin 

const int LOADREG = A0;
const int LOADDACS = A1;
const int CS_DAC = A2;

//---------------------------------------------------------

DAC7715 DAC_(CS_DAC, LOADREG, LOADDACS);

void setup() {

  Serial.begin(9600);

  SPI.begin();
  
  pinMode(CS_DAC, OUTPUT);
  pinMode(LOADDACS, OUTPUT);
  pinMode(LOADREG, OUTPUT);

  digitalWrite(CS_DAC, HIGH);
  digitalWrite(LOADDACS, HIGH);
  digitalWrite(LOADREG, HIGH);

  // Since the DAC7715 is 12 bit, the output range can go from 0 to 4095.
  // This DAC specifically has 4 output pins, therefore we can write to their registers choosing from 0 to 3.
  
  DAC_.writeDAC(4095, 0);
  delay(50);
  DAC_.writeDAC(0, 1);
  delay(50);
  DAC_.writeDAC(4095, 2);
  delay(50);
  DAC_.writeDAC(0, 3);

}

void loop() {
  // put your main code here, to run repeatedly:

}

#include <MUX74HC595.h>

//---------------------   MUX VAR   -----------------------
// Each bit represents a output pin in the MUX
// In order to set them, you just sum the bytes specified below and pass them to the specific function.

#define K0 0b00000001
#define K1 0b00000010
#define K2 0b00000100
#define K3 0b00001000
#define K4 0b00010000
#define K5 0b00100000
#define K6 0b01000000
#define K7 0b10000000

// Chip Select - MUX
const int CS_MUX = 10;

// Class MUX
MUX74HC595 MUX(CS_MUX);

void setup() {

  Serial.begin(9600);
  SPI.begin();

  pinMode(CS_MUX, OUTPUT);
  digitalWrite(CS_MUX, HIGH);

  MUX.writeMUX_only_one(K0 + K1 + K3 + K7);

}

void loop() {
}


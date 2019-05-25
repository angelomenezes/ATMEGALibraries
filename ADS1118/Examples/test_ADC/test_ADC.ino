#include <ADS1118.h>

//-------------- Chip Select for the ADC ------------------

const int CS_ADC = 10;

//---------------------------------------------------------

int value_ADC_channel_0; // READ VALUE FROM ADC INPUT 0
int value_ADC_channel_1; // READ VALUE FROM ADC INPUT 1
int value_ADC_channel_2; // READ VALUE FROM ADC INPUT 2
int value_ADC_channel_3; // READ VALUE FROM ADC INPUT 3

float input_0; // INPUT 0 CONVERTED TO 5V
float input_1; // INPUT 1 CONVERTED TO 5V
float input_2; // INPUT 2 CONVERTED TO 5V
float input_3; // INPUT 3 CONVERTED TO 5V

// Class ADS1118
ADS1118 ADC_(CS_ADC);

void setup() {

  Serial.begin(9600);
  SPI.begin();
  
  pinMode(CS_ADC, OUTPUT);  
  digitalWrite(CS_ADC, HIGH);

}

void loop() {

  test_ADC();
  delay(1000);

}

void test_ADC()
{
  // FIRST, CHANNELS ARE READ - THE ADS1118 HAS 4 CHANNELS, YOU CAN SELECT THEM PASSING 0-3 IN THE "readADC" FUNCTION

  value_ADC_channel_0 = ADC_.readADC(0); 
  delay(100);
  value_ADC_channel_1 = ADC_.readADC(1);
  delay(100);
  value_ADC_channel_2 = ADC_.readADC(2);
  delay(100);
  value_ADC_channel_3 = ADC_.readADC(3);
  delay(100);


  // SECOND, DATA IS CONVERTED TO 5V FOR DEBUGGING PURPOSES (CONVERSION IS MADE ACCORDING TO PARAMETERS GIVEN ON THE DATASHEET)

  input_0 = (float)((int)value_ADC_channel_0) * ((float)6.144) / ((float)32768);
  input_1 = (float)((int)value_ADC_channel_1) * ((float)6.144) / ((float)32768);
  input_2 = (float)((int)value_ADC_channel_2) * ((float)6.144) / ((float)32768);
  input_3 = (float)((int)value_ADC_channel_3) * ((float)6.144) / ((float)32768);

  Serial.print("INPUT 0: ");
  Serial.println(input_0);
  Serial.print("INPUT 1: ");
  Serial.println(input_1);
  Serial.print("INPUT 2: ");
  Serial.println(input_2);
  Serial.print("INPUT 3: ");
  Serial.println(input_3);
}

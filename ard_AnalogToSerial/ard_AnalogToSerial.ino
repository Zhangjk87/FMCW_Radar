/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif



// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

const int arrSize = 200;
const int centerVal = 512;
unsigned long startTime;
unsigned long endTime;
unsigned long totalTime;
int crossing;
double frequency;

unsigned long values[arrSize];

int pos = 0;


const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

String output = "";

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  ADCSRA &= ~PS_128;
  ADCSRA |= PS_16;
}

void loop() {
  // read the analog in value:
  //sensorValue = analogRead(analogInPin);
  //Serial.println(pos);
  /*if(pos < arrSize)
  {
    output = output + String(pos) + ":" + String(sensorValue) +"\n";
    pos++;
  }
  else
  {
    Serial.println(output);
    output = "";
    pos = 0;
  }*/
  int i;
  crossing = 0;
  startTime = micros();
  for(i = 0; i < arrSize; i++) { 
    values[i] = analogRead(analogInPin);
  }
  endTime = micros();
  totalTime = endTime - startTime;

  boolean low = false;
  if(values[0] < centerVal) {
    low = true;
  }
  for(i = 1; i < arrSize; i++) {
    if(values[i] < centerVal && !low) {
      crossing++;
      low = true;
    }
    if(values[i] >= centerVal) {
      low = false;
    }
    //Serial.println(values[i]);
  }

  frequency = (1000 * (1.0 * crossing)) / (totalTime * 1.0);

  Serial.print("Total time: ");
  Serial.println(totalTime);  
  Serial.print("Crossings: ");
  Serial.println(crossing);
  Serial.print("Frequency: ");
  Serial.println(frequency);
  // map it to the range of the analog out:
  //outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);
  Serial.println("\n");
  // print the results to the serial monitor:
  //Serial.print("sensor = " );

  //Serial.print("\t output = ");
  //Serial.println(outputValue);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);
}

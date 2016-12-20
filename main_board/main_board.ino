/* How To Make Anything
 * Smart Pullup Bar
 * Main Board Code
 * Created 19 DEC 2016
 * 
 * Libraries Used
 * - Adafruit_ADS1015.h (Added)
 * - Wire.h (Standard)
 * 
 * 
 * 
 * ADS1115 Wiring
 * Vdd = 5V
 * Gnd = 0V
 * SCL = A5
 * SDA = A4
 * ADDR = GND (So address is 48)
 * ALRT = NC
 * A0 = Strain +
 * A1 = Strain -
 */

//Libraries
#include <Wire.h>
#include "./Adafruit_ADS1015.h"
//#include "./Libraries/Adafruit_ADS1X15/Adafruit_ADS1015.h"

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

void setup() {
  // put your setup code here, to run once:

  /* Pin List
   * Digital
   * - 0  = UART Rx
   * - 1  = UART Tx
   * - 13 = Debug LED
   * 
   * Analog
   * - A0 = Laser Detection
   * - A4 = I2C SDA
   * - A5 = I2C SCL
   */
  //Pin Declarations
  int debug = 13;
  
  pinMode(debug, OUTPUT);

  //Communications Serial Port
  Serial.begin(9600);
  Serial.println("Begin!");

  //ADS1115 Gain Control
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t results;

  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  //Read A0 and A1 on ADS1115 as differential
  results = ads.readADC_Differential_0_1();

  Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(results * multiplier); Serial.println("mV)");

  delay(1000);
}

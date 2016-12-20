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

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

//Global Variables
//loadcell values
int16_t loadcell0_zero;
int16_t loadcell1_zero;

//loadcell threshold
//if the loadcell values drift by the value below we will trigger pullup bar use == true
int16_t loadcell_compare = 10;

//counter display variables
int counter = 0;

/*
 * When the system is started the loadcell values need to be zeroed.
 * This corrects for inconsistancies and drift.
 */
void init_loadcell_values() {
  //Read A0 and A1 on ADS1115 as differential
  loadcell0_zero = ads.readADC_Differential_0_1(); 
  
  //Read A0 and A1 on ADS1115 as differential
  loadcell1_zero = ads.readADC_Differential_2_3();
}

/*
 * Funciton below checks to see if the pullup bar is in use
 */
int check_usage() {
  //initialize and allocate variables
  int16_t result0;
  int16_t result1;
  
  //read loadcells
  result0 = ads.readADC_Differential_0_1(); 
  result1 = ads.readADC_Differential_2_3();

  //Output Raw Difference
  //Serial.print(abs(loadcell0_zero) - abs(result0));Serial.print("\n");

  //return true if either zero - loadcell difference > compare
  if( (abs(loadcell0_zero) - abs(result0)) > loadcell_compare
   /*|| (abs(loadcell1_zero) - abs(result1)) > loadcell_compare*/) {

      return 1;
   }
   else {
      return 0;
   }

}


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

  //Initialize Loadcell values
  init_loadcell_values();
}

void loop() {
  //Test

  if(/*Write Pullup detection case*/) {
    if(/*Write pullup de detection case*/) {
       counter++; 
    }
  }

  
  Serial.write(counter);
}



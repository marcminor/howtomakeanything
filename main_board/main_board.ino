/* How To Make Anything
 * Smart Pullup Bar
 * Main Board Code
 * Created 19 DEC 2016
 * 
 * Libraries Used
 * - Adafruit_ADS1015.h (Added)
 * - Wire.h (Standard)
 */

//Libraries
#include <Wire.h>
#include "./Libraries/Adafruit_ADS1X15/Adafruit_ADS1015.h"

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

}

void loop() {
  // put your main code here, to run repeatedly:

}

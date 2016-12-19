# howtomakeanything
## Intro: Smart Pullup Bar
Designing a smart pullup bar that can detect that the victim is using the pullup bar and counts every time said user does a pullup.

#### Presence detection
The presense detector will be done with 1 or more load cells (similar to the ones found on weight scales) with the bar itself resting on the cells themselves. Eventually a firmware/software upgrade can be done to measure the quality of the pull up by analyzing impulse response.

The load cells will vary little in resistance so a wheatstone bridge and a differential amplifier plus differential ADC will be required. The accuracy of the weight will not matter for version one as only presence detection is needed.

#### Pullup detection
A red laser will be create a trip beam across the top of the bar. As a proper pullup is done, chin raised above the bar, the laser trip will be broken. 

To detect that the beam has been broken a red LED will be used as a sensor. When the laser hits the red LED the LED produces a voltage greater than 1V. This can be read in by a ADC pin and the resulting value can be used to determine the trip state.

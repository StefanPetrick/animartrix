/*
  ___        _            ___  ______ _____    _      
 / _ \      (_)          / _ \ | ___ \_   _|  (_)     
/ /_\ \_ __  _ _ __ ___ / /_\ \| |_/ / | |_ __ ___  __
|  _  | '_ \| | '_ ` _ \|  _  ||    /  | | '__| \ \/ /
| | | | | | | | | | | | | | | || |\ \  | | |  | |>  < 
\_| |_/_| |_|_|_| |_| |_\_| |_/\_| \_| \_/_|  |_/_/\_\

by Stefan Petrick 2023.

High quality LED animations for your next project.

This is a Shader and 5D Coordinate Mapper made for realtime 
rendering of generative animations & artistic dynamic visuals.

This is also a modular animation synthesizer with waveform 
generators, oscillators, filters, modulators, noise generators, 
compressors... and much more.

VO.42 beta version
 
This code is licenced under a Creative Commons Attribution 
License CC BY-NC 3.0

*/

#include <FastLED.h>
#include <ANIMartRIX.h>

#define num_x  16                       // how many LEDs are in one row?
#define num_y  16                       // how many rows?


CRGB leds[num_x * num_y];               // framebuffer

ANIMartRIX art(num_x, num_y, leds);

//******************************************************************************************************************


void setup() {
  
  // FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
  
  FastLED.addLeds<APA102, 11, 13, BGR, DATA_RATE_MHZ(12)>(leds, NUM_LEDS);   

  //FastLED.setMaxPowerInVoltsAndMilliamps( 5, 2000); // optional current limiting [5V, 2000mA] 

  Serial.begin(115200);                 // check serial monitor for current fps count
 
  art->render_polar_lookup_table((num_x / 2) - 0.5, (num_y / 2) - 0.5);          // precalculate all polar coordinates 
                                                                            // polar origin is set to matrix centre
  
}

//*******************************************************************************************************************

void loop() {
  
  //RGB_Blobs5();
  //RGB_Blobs4();
  //RGB_Blobs3();
  //RGB_Blobs2();
  //RGB_Blobs();
  //Polar_Waves();
  //Slow_Fade();
  //Zoom2();
  //Zoom();
  //Hot_Blob();
  //Spiralus2();
  //Spiralus();
  //Yves();
  //Scaledemo1();
  art->Lava1();
  //Caleido3();
  //Caleido2();
  //Caleido1();
  //Distance_Experiment();
  //Center_Field();
  //Waves();
  //Chasing_Spirals();
  //Rotating_Blob();
  //Rings();
  FastLED.show();
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report 
} 


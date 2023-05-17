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

#define num_x  30                       // how many LEDs are in one row?
#define num_y  30                       // how many rows?

#define NUM_LED (num_x * num_y)
CRGB leds[NUM_LED];               // framebuffer

bool serpentine = true;

ANIMartRIX art(num_x, num_y, leds, serpentine);

//******************************************************************************************************************


void setup() {
  
  // FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LED);
  
  FastLED.addLeds<APA102, 7, 14, BGR, DATA_RATE_MHZ(8)>(leds, NUM_LED);   

  FastLED.setMaxPowerInVoltsAndMilliamps( 5, 2000); // optional current limiting [5V, 2000mA] 

  Serial.begin(115200);                 // check serial monitor for current fps count
 
 // fill_rainbow(leds, NUM_LED, 0);
  fill_solid(leds, NUM_LED, CRGB::Green);
  FastLED.show();
}

//*******************************************************************************************************************

void loop() {
  //FastLED.clear();
  // art.RGB_Blobs5();
  // art.RGB_Blobs4();
  // art.RGB_Blobs3();
  // art.RGB_Blobs2();
  art.RGB_Blobs();
  // art.Polar_Waves();
  // art.Slow_Fade();
  // art.Zoom2();
  // art.Zoom();
  // art.Hot_Blob();
  // art.Spiralus2();
  // art.Spiralus();
  // art.Yves();
  // art.Scaledemo1();
  // art. art.Lava1();
  // art.Caleido3();
  // art.Caleido2();
  // art.Caleido1();
  // art.Distance_Experiment();
  // art.Center_Field();
  // art.Waves();
  // art.Chasing_Spirals();
  // art.Rotating_Blob();
  // art.Rings();
  FastLED.show();
  EVERY_N_MILLIS(500) art.report_performance();   // check serial monitor for report 
} 


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

#define num_x  16                       // how many LEDs are in one row?
#define num_y  16                       // how many rows?
#define NUM_LEDS ((num_x) * (num_y))


CRGB leds[num_x * num_y];               // framebuffer

float polar_theta[num_x][num_y];        // look-up table for polar angles
float distance[num_x][num_y];           // look-up table for polar distances

unsigned long a, b, c;                  // for time measurements

struct render_parameters {

  float center_x = (num_x / 2) - 0.5;   // center of the matrix
  float center_y = (num_y / 2) - 0.5;
  float dist, angle;                
  float scale_x = 0.1;                  // smaller values = zoom in
  float scale_y = 0.1;
  float scale_z = 0.1;       
  float offset_x, offset_y, offset_z;     
  float z;  
  float low_limit  = 0;                 // getting contrast by highering the black point
  float high_limit = 1;                                            
};

render_parameters animation;     // all animation parameters in one place

#define num_oscillators 10

struct oscillators {

  float master_speed;            // global transition speed
  float offset[num_oscillators]; // oscillators can be shifted by a time offset
  float ratio[num_oscillators];  // speed ratios for the individual oscillators                                  
};

oscillators timings;             // all speed settings in one place

struct modulators {  

  float linear[num_oscillators];        // returns 0 to FLT_MAX
  float radial[num_oscillators];        // returns 0 to 2*PI
  float directional[num_oscillators];   // returns -1 to 1
  float noise_angle[num_oscillators];   // returns 0 to 2*PI        
};

modulators move;                 // all oscillator based movers and shifters at one place

struct rgb {

  float red, green, blue;
};

rgb pixel;


typedef void (*Pattern)();
typedef Pattern PatternList[];
typedef struct {
  Pattern pattern;
  String name;
} PatternAndName;
typedef PatternAndName PatternAndNameList[];

int currentPattern = 0;

#include "animation_collection.h"

PatternAndNameList gPatterns = {
 { RGB_Blobs5, "RGB_Blobs5" },
 { RGB_Blobs4, "RGB_Blobs4" },
 { RGB_Blobs3, "RGB_Blobs3" },
 { RGB_Blobs2, "RGB_Blobs2" },
 { RGB_Blobs, "RGB_Blobs" },
 { Polar_Waves, "Polar_Waves" },
 { Slow_Fade, "Slow_Fade" },
//  { Zoom2, "Zoom2" },
 { Zoom, "Zoom" },
 { Hot_Blob, "Hot_Blob" },
 { Spiralus2, "Spiralus2" },
 { Spiralus, "Spiralus" },
 { Yves, "Yves" },
 { Scaledemo1, "Scaledemo1" },
 { Lava1, "Lava1" },
 { Caleido3, "Caleido3" },
 { Caleido2, "Caleido2" },
 { Caleido1, "Caleido1" },
 { Distance_Experiment, "Distance_Experiment" },
 { Center_Field, "Center_Field" },
 { Waves, "Waves" },
 { Chasing_Spirals, "Chasing_Spirals" },
 { Rotating_Blob, "Rotating_Blob" },
 { Rings, "Rings" },
};

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
int gPatternCount = ARRAY_SIZE(gPatterns);


//******************************************************************************************************************


void setup() {
  
  // FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
  
  FastLED.addLeds<APA102, 11, 13, BGR, DATA_RATE_MHZ(12)>(leds, NUM_LEDS);   

  //FastLED.setMaxPowerInVoltsAndMilliamps( 5, 2000); // optional current limiting [5V, 2000mA] 

  Serial.begin(115200);                 // check serial monitor for current fps count
 
  render_polar_lookup_table((num_x / 2) - 0.5, (num_y / 2) - 0.5);          // precalculate all polar coordinates 
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
  // Lava1();
  //Caleido3();
  //Caleido2();
  //Caleido1();
  //Distance_Experiment();
  //Center_Field();
  //Waves();
  //Chasing_Spirals();
  //Rotating_Blob();
  //Rings();
  EVERY_N_SECONDS(90) {
    currentPattern = random(1, (gPatternCount - 1));
//     autopgm++;
    // if (autopgm >= gPatternCount) autopgm = 1;
    Serial.print("Next Auto pattern: ");
    Serial.println(gPatterns[currentPattern].name);
  }

  gPatterns[currentPattern].pattern();
} 


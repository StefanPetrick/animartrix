// A 5D coordinate mapper by Stefan Petrick 2023 
//
// VO.3 preview version
// 
// This code is licenced under a Creative Commons Attribution 
// License CC BY-NC 3.0

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

#define num_oscillators 5

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



//******************************************************************************************************************


void setup() {

  Serial.begin(115200);                 // check serial monitor for current fps count
  
  // FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
  FastLED.addLeds<APA102, 11, 13, BGR, DATA_RATE_MHZ(12)>(leds, NUM_LEDS);    
 
  render_polar_lookup_table((num_x / 2) - 0.5, (num_y / 2) - 0.5);          // precalculate all polar coordinates 
                                                                            // polar origin is set to matrix centre
  
}

//*******************************************************************************************************************

void loop() {

  a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 0.1;         // higher values = faster transitions
  timings.ratio[1] = 0.03;
  timings.ratio[2] = 0.03;
  timings.ratio[3] = 0.03;
  timings.ratio[4] = 0.13;
  
  timings.offset[1] = 10;
  timings.offset[2] = 20;
  timings.offset[3] = 30;
  timings.offset[4] = 4;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = polar_theta[y][x] -  move.radial[0];
      animation.dist       = distance[y][x];
      animation.z          = move.linear[0];
      animation.low_limit  = -1;
      float show1          = render_value(animation);
      
      animation.angle      = polar_theta[x][y] + move.radial[1] + show1/512.0;
      animation.dist       = distance[y][x] * show1/255.0;
      animation.low_limit  = 0;
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2] + show1/512.0;
      animation.dist       = distance[y][x] * show1/220.0;
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[3] + show1/512.0;
      animation.dist       = distance[y][x] * show1/200.0;
      animation.z          = move.linear[3];
      float show4          = render_value(animation);

      // colormapping
      pixel.red   = show2;
      pixel.green = show3 / 3;
      pixel.blue  = show4 / 4;

      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()

  FastLED.show();

  c = micros(); // for time measurement in report_performance()
  
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
   
} 


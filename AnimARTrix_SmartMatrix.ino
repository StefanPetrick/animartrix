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

#ifdef ESP32
#define USE_SMARTMATRIX // Comment/remove this line to swap back to FastLED
#endif

#define num_x       32                       // how many LEDs are in one row?
#define num_y       32                       // how many rows?
// #define brightness 255                       // please be aware that reducing brightness also reduces color resolution, use only in emergency

#define radial_filter_radius 23.0;      // on 32x32, use 11 for 16x16

const uint16_t kMatrixWidth   = num_x;  // Set to the width of your display, must be a multiple of 8
const uint16_t kMatrixHeight  = num_y;  // Set to the height of your display

#ifdef USE_SMARTMATRIX
  #ifdef ESP32
    #include <MatrixHardware_ESP32_V0.h> // ESP32
  #else
    #include <MatrixHardware_Teensy4_ShieldV5.h>        // SmartLED Shield for Teensy 4 (V5)
  #endif

  #include <SmartMatrix.h>

  #define COLOR_DEPTH 24                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
  const uint8_t  kRefreshDepth  = 48;     // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
  const uint8_t  kDmaBufferRows = 4;      // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
  const uint8_t  kPanelType              = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
  const uint32_t kMatrixOptions          = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
  const uint8_t  kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

  SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
  SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
  rgb24 *buffer = backgroundLayer.backBuffer();
#else
  #define NUM_LEDS ((num_x) * (num_y))
  CRGB buffer[num_x * num_y];               // framebuffer
#endif

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

float show1, show2, show3, show4, show5, show6, show7, show8, show9, show0;


//******************************************************************************************************************


void setup() {
  

  Serial.begin(115200);                 // check serial monitor for current fps count
 
  render_polar_lookup_table((num_x / 2) - 0.5, (num_y / 2) - 0.5);          // precalculate all polar coordinates 

#ifdef USE_SMARTMATRIX                                                                            // polar origin is set to matrix centre
  matrix.addLayer(&backgroundLayer); 
  // matrix.setBrightness(brightness); 
  matrix.begin();
#else
  // FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
  FastLED.addLeds<APA102, 11, 13, BGR, DATA_RATE_MHZ(12)>(buffer, NUM_LEDS);   
  // FastLED.setMaxPowerInVoltsAndMilliamps( 5, 2000); // optional current limiting [5V, 2000mA] 
  // FastLED.setBrightness(brightness);
#endif
}

//*******************************************************************************************************************

void loop() {             


  //Module_Experiment10();   // HSV scroll (bad palette resolution)
  //Module_Experiment9();    // red stripes
  //Module_Experiment8();    // another ambilight...very nice
  //Module_Experiment7();    // slow ambilight ripples redish
  //Module_Experiment6();    // slower ripples red-yellow
  //Module_Experiment5();    // watery red ripples
  //Module_Experiment4();    // slow RGB middle zoom dist^2
  //Zoom2();
  //Module_Experiment3();   // inside out zoomed in
  //Module_Experiment2();   // stretched distance, fire colors
  //Module_Experiment1();   // inside out demo
  //Parametric_Water();     // slow blue ambientlight
  //Water();                // nice water simulation
  //Complex_Kaleido_6();    // red blue moire
  //Complex_Kaleido_5();    // interference pattern
  Complex_Kaleido_4();    // colorful slow mandala
  //Complex_Kaleido_3();
  //Complex_Kaleido_2();    // hypnotic smooth
  //Complex_Kaleido();
  //SM10();                 // like 9 but fire colors - slow
  //SM9();                  // polar domain warping
  //SM8();                  // careful: flashy rings
  //SM7();                  // wild rings
  //SM6();                  // red + blue, pretty and beautiful one, my favourite so far
  //SM5();                  // nice colorful roto blobs
  //SM4();                  // layer merge test
  //SM3();                  // cartesian domain warping
  //SM2();                  // roro zoom
  //SM1();                  // copy caleido
  //Big_Caleido();          // 5/6 Kaleido + rings
  //RGB_Blobs5();           // sqrtf dist
  //RGB_Blobs4();
  //RGB_Blobs3();
  //RGB_Blobs2();
  //RGB_Blobs();            // multi roto stuff
  //Polar_Waves();          // spiral waves
  //Slow_Fade();            // red big spiral 
  //Zoom();                 // boring
  //Hot_Blob();             // something firey, hot center
  //Spiralus2();            // slow
  //Spiralus();             // *2
  //Yves();                 // red warpings
  //Scaledemo1();           // *3 + ring red blue
  //Lava1();                // slow ambilight
  //Caleido3();             // roto
  //Caleido2();             // roto *2
  //Caleido1();             // star like
  //Distance_Experiment();  // big orange yellow smooth
  //Center_Field();         // boring green yello red
  //Waves();                // cool big red blue
  //Chasing_Spirals();      // slim
  //Rotating_Blob();        // 
  
  show_frame();
 
} 


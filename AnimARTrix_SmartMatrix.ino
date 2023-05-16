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

#include <MatrixHardware_ESP32_V0.h> // ESP32
// #include <MatrixHardware_Teensy4_ShieldV5.h>        // SmartLED Shield for Teensy 4 (V5)
#include <SmartMatrix.h>
#include <FastLED.h>

#define num_x       64                       // how many LEDs are in one row?
#define num_y       64                       // how many rows?
#define brightness 255                       // please be aware that reducing brightness also reduces color resolution, use only in emergency

#define radial_filter_radius 23.0;      // on 32x32, use 11 for 16x16

#define COLOR_DEPTH 24                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
const uint16_t kMatrixWidth   = num_x;  // Set to the width of your display, must be a multiple of 8
const uint16_t kMatrixHeight  = num_y;  // Set to the height of your display
const uint8_t  kRefreshDepth  = 48;     // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
const uint8_t  kDmaBufferRows = 4;      // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
const uint8_t  kPanelType              = SMARTMATRIX_HUB75_64ROW_MOD32SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
const uint32_t kMatrixOptions          = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint8_t  kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

//#define NUM_LEDS ((num_x) * (num_y))
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

float show1, show2, show3, show4, show5, show6, show7, show8, show9, show0;

//******************************************************************************************************************
typedef void (*Pattern)();
typedef Pattern PatternList[];
typedef struct {
  Pattern pattern;
  String name;
} PatternAndName;
typedef PatternAndName PatternAndNameList[];

int currentPattern = 0;

void   Module_Experiment10();
void   Module_Experiment9();
void   Module_Experiment8();
void   Module_Experiment7();
void   Module_Experiment6();
void   Module_Experiment5();
void   Module_Experiment4();
void   Zoom2();
void   Module_Experiment3();
void   Module_Experiment2();
void   Module_Experiment1();
void   Parametric_Water();
void   Water();
void   Complex_Kaleido_6();
void   Complex_Kaleido_5();
void    Complex_Kaleido_4();
void  Complex_Kaleido_3();
void   Complex_Kaleido_2();
void  Complex_Kaleido();
void   SM10();
void   SM9();
void   SM8();
void   SM7();
void   SM6();
void   SM5();
void   SM4();
void   SM3();
void   SM2();
void   SM1();
void   Big_Caleido();
void   RGB_Blobs5();
void  RGB_Blobs4();
void  RGB_Blobs3();
void  RGB_Blobs2();
void   RGB_Blobs();
void   Polar_Waves();
void   Slow_Fade();
void   Zoom();
void   Hot_Blob();
void   Spiralus2();
void   Spiralus();
void   Yves();
void   Scaledemo1();
void   Lava1();
void   Caleido3();
void   Caleido2();
void   Caleido1();
void   Distance_Experiment();
void   Center_Field();
void   Waves();
void   Chasing_Spirals();
void   Rotating_Blob();

PatternAndNameList gPatterns = {
{Module_Experiment10,"Module_Experiment10"},
{Module_Experiment9,"Module_Experiment9"},
{Module_Experiment8,"Module_Experiment8"},
{Module_Experiment7,"Module_Experiment7"},
{Module_Experiment6,"Module_Experiment6"},
{Module_Experiment5,"Module_Experiment5"},
{Module_Experiment4,"Module_Experiment4"},
{Zoom2, "Zoom2"}, 
{Module_Experiment3,"Module_Experiment3"},
{Module_Experiment2,"Module_Experiment2"},
{Module_Experiment1,"Module_Experiment1"},
{Parametric_Water,"Parametric_Water"},
{Water,"Water"},
{Complex_Kaleido_6,"Complex_Kaleido_6"},
{Complex_Kaleido_5,"Complex_Kaleido_5"},
{Complex_Kaleido_4,"Complex_Kaleido_4"},
{Complex_Kaleido_3, "Complex_Kaleido_3"},
{Complex_Kaleido_2,"Complex_Kaleido_2"},
{Complex_Kaleido, "Complex_Kaleido"},
{SM10,"SM10"},
{SM9,"SM9"},
{SM8,"SM8"},
// {SM7,"SM7"},
{SM6,"SM6"},
{SM5,"SM5"},
{SM4,"SM4"},
{SM3,"SM3"},
{SM2,"SM2"},
{SM1,"SM1"},
{Big_Caleido,"Big_Caleido"},
{RGB_Blobs5,"RGB_Blobs5"},
{RGB_Blobs4,"RGB_Blobs4"},
{RGB_Blobs3,"RGB_Blobs3"},
{RGB_Blobs2,"RGB_Blobs2"},
{RGB_Blobs,"RGB_Blobs"},
{Polar_Waves,"Polar_Waves"},
{Slow_Fade,"Slow_Fade"},
{Zoom,"Zoom"},
{Hot_Blob,"Hot_Blob"},
{Spiralus2,"Spiralus2"},
{Spiralus,"Spiralus"},
{Yves,"Yves"},
{Scaledemo1,"Scaledemo1"},
{Lava1,"Lava1"},
{Caleido3,"Caleido3"},
{Caleido2,"Caleido2"},
{Caleido1,"Caleido1"},
{Distance_Experiment,"Distance_Experiment"},
{Center_Field,"Center_Field"},
{Waves,"Waves"},
{Chasing_Spirals,"Chasing_Spirals"},
{Rotating_Blob,"Rotating_Blob"},
};

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
int gPatternCount = ARRAY_SIZE(gPatterns);



//******************************************************************************************************************


void setup() {
  
  // FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LEDS);
  // FastLED.addLeds<APA102, 11, 13, BGR, DATA_RATE_MHZ(12)>(leds, NUM_LEDS);   
  // FastLED.setMaxPowerInVoltsAndMilliamps( 5, 2000); // optional current limiting [5V, 2000mA] 

  Serial.begin(115200);                 // check serial monitor for current fps count
 
  render_polar_lookup_table((num_x / 2) - 0.5, (num_y / 2) - 0.5);          // precalculate all polar coordinates 
                                                                            // polar origin is set to matrix centre
  matrix.addLayer(&backgroundLayer); 
  matrix.setBrightness(brightness); 
  matrix.begin();
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
  // Complex_Kaleido_4();    // colorful slow mandala
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
  
  EVERY_N_SECONDS(90) {
    currentPattern = random(0, (gPatternCount - 1));
//     autopgm++;
    // if (autopgm >= gPatternCount) autopgm = 1;
    Serial.print("Next Auto pattern: ");
    Serial.println(gPatterns[currentPattern].name);
  }

  gPatterns[currentPattern].pattern();

  show_frame();
 
} 


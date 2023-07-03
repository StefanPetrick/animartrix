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

#include <MatrixHardware_Teensy4_ShieldV5.h>        // SmartLED Shield for Teensy 4 (V5)
#include <SmartMatrix.h>
#include <ANIMartRIX.h>

#define num_x       64                       // how many LEDs are in one row?
#define num_y       64                       // how many rows?
#define brightness 255                       // please be aware that reducing brightness also reduces color resolution, use only in emergency

#define radial_filter_radius 23.0;      // on 32x32, use 11 for 16x16

#define COLOR_DEPTH 24                  // Choose the color depth used for storing pixels in the layers: 24 or 48 (24 is good for most sketches - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24)
const uint16_t kMatrixWidth   = num_x;  // Set to the width of your display, must be a multiple of 8
const uint16_t kMatrixHeight  = num_y;  // Set to the height of your display
const uint8_t  kRefreshDepth  = 48;     // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
const uint8_t  kDmaBufferRows = 4;      // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
const uint8_t  kPanelType              = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https://github.com/pixelmatix/SmartMatrix/wiki
const uint32_t kMatrixOptions          = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint8_t  kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

class SmartMatrixANIMartRIX : public ANIMartRIX {
  rgb24* buffer;
  public:
  SmartMatrixANIMartRIX(int x, int y) {
    this->init(x, y, false);
  }
  void setBuffer(rgb24 *buffer) {
    this->buffer = buffer;
  }
  void setPixelColor(int x, int y, rgb pixel) {
    buffer[xy(x,y)] = rgb24(pixel.red, pixel.green, pixel.blue);
  }
  void setPixelColor(int index, rgb pixel) {
    buffer[index] = rgb24(pixel.red, pixel.green, pixel.blue);
  }
  void logOutput() {
    while(backgroundLayer.isSwapPending());
    b = micros();
  }

};
SmartMatrixANIMartRIX animatrix(num_x, num_y);

//******************************************************************************************************************


void setup() {
  
  Serial.begin(115200);                 // check serial monitor for current fps count
                                                                             // polar origin is set to matrix centre
  matrix.addLayer(&backgroundLayer); 
  matrix.setBrightness(brightness); 
  matrix.begin();
  animatrix.setBuffer(backgroundLayer.backBuffer());
}

//*******************************************************************************************************************

void loop() {             


  //animatrix.Module_Experiment10();   // HSV scroll (bad palette resolution)
  //animatrix.Module_Experiment9();    // red stripes
  //animatrix.Module_Experiment8();    // another ambilight...very nice
  //animatrix.Module_Experiment7();    // slow ambilight ripples redish
  //animatrix.Module_Experiment6();    // slower ripples red-yellow
  //animatrix.Module_Experiment5();    // watery red ripples
  //animatrix.Module_Experiment4();    // slow RGB middle zoom dist^2
  //animatrix.Zoom2();
  //animatrix.Module_Experiment3();   // inside out zoomed in
  //animatrix.Module_Experiment2();   // stretched distance, fire colors
  //animatrix.Module_Experiment1();   // inside out demo
  //animatrix.Parametric_Water();     // slow blue ambientlight
  //animatrix.Water();                // nice water simulation
  //animatrix.Complex_Kaleido_6();    // red blue moire
  //animatrix.Complex_Kaleido_5();    // interference pattern
  animatrix.Complex_Kaleido_4();    // colorful slow mandala
  //animatrix.Complex_Kaleido_3();
  //animatrix.Complex_Kaleido_2();    // hypnotic smooth
  //animatrix.Complex_Kaleido();
  //animatrix.SM10();                 // like 9 but fire colors - slow
  //animatrix.SM9();                  // polar domain warping
  //animatrix.SM8();                  // careful: flashy rings
  //animatrix.SM7();                  // wild rings
  //animatrix.SM6();                  // red + blue, pretty and beautiful one, my favourite so far
  //animatrix.SM5();                  // nice colorful roto blobs
  //animatrix.SM4();                  // layer merge test
  //animatrix.SM3();                  // cartesian domain warping
  //animatrix.SM2();                  // roro zoom
  //animatrix.SM1();                  // copy caleido
  //animatrix.Big_Caleido();          // 5/6 Kaleido + rings
  //animatrix.RGB_Blobs5();           // sqrtf dist
  //animatrix.RGB_Blobs4();
  //animatrix.RGB_Blobs3();
  //animatrix.RGB_Blobs2();
  //animatrix.RGB_Blobs();            // multi roto stuff
  //animatrix.Polar_Waves();          // spiral waves
  //animatrix.Slow_Fade();            // red big spiral 
  //animatrix.Zoom();                 // boring
  //animatrix.Hot_Blob();             // something firey, hot center
  //animatrix.Spiralus2();            // slow
  //animatrix.Spiralus();             // *2
  //animatrix.Yves();                 // red warpings
  //animatrix.Scaledemo1();           // *3 + ring red blue
  //animatrix.Lava1();                // slow ambilight
  //animatrix.Caleido3();             // roto
  //animatrix.Caleido2();             // roto *2
  //animatrix.Caleido1();             // star like
  //animatrix.Distance_Experiment();  // big orange yellow smooth
  //animatrix.Center_Field();         // boring green yello red
  //animatrix.Waves();                // cool big red blue
  //animatrix.Chasing_Spirals();      // slim
  //animatrix.Rotating_Blob();        // 
  
 
   backgroundLayer.swapBuffers(true);
   animatrix.logFrame();
   EVERY_N_MILLIS(500) animatrix.report_performance();   // check serial monitor for report 

} 


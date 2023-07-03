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

#include <functional>
#include <vector>
#include <MatrixHardware_Teensy4_ShieldV4Adapter.h> // Teensy 4 Adapter attached to SmartLED Shield for Teensy 3 (V4)
//#include <MatrixHardware_Teensy4_ShieldV5.h>        // SmartLED Shield for Teensy 4 (V5)
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
const uint8_t  kPanelType              = SM_PANELTYPE_HUB75_64ROW_MOD32SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https:github.com/pixelmatix/SmartMatrix/wiki
//const uint8_t  kPanelType              = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;   // Choose the configuration that matches your panels.  See more details in MatrixCommonHub75.h and the docs: https:github.com/pixelmatix/SmartMatrix/wiki
const uint32_t kMatrixOptions          = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https:github.com/pixelmatix/SmartMatrix/wiki
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
};
SmartMatrixANIMartRIX animatrix(num_x, num_y);

std::vector<std::function<void(void)>> gPatterns;

int gPatternCount = 0;

//******************************************************************************************************************


void setup() {
  
  Serial.begin(115200);                 // check serial monitor for current fps count
                                                                             // polar origin is set to matrix centre
  matrix.addLayer(&backgroundLayer); 
  matrix.setBrightness(brightness); 
  matrix.begin();
  animatrix.setBuffer(backgroundLayer.backBuffer());

  Serial.println("Adding patterns to list");

  // gPatterns.push_back(std::bind(&SmartMatrixANIMartRIX::Module_Experiment10, animatrix));   // HSV scroll (bad palette resolution)
  // gPatterns.push_back(std::bind(&ANIMartRIX::Module_Experiment9, animatrix));    // red stripes
  // gPatterns.push_back(std::bind(&ANIMartRIX::Module_Experiment8, animatrix));    // another ambilight...very nice
  // gPatterns.push_back(std::bind(&ANIMartRIX::Module_Experiment7, animatrix));    // slow ambilight ripples redish
  // gPatterns.push_back(std::bind(&ANIMartRIX::Module_Experiment6, animatrix));    // slower ripples red-yellow
  // gPatterns.push_back(std::bind(&ANIMartRIX::Module_Experiment5, animatrix));    // watery red ripples
  // gPatterns.push_back(std::bind(&ANIMartRIX::Module_Experiment4, animatrix));    // slow RGB middle zoom dist^2
  // gPatterns.push_back(std::bind(&ANIMartRIX::Zoom2, animatrix));
  // gPatterns.push_back(std::bind(&ANIMartRIX::Module_Experiment3, animatrix));   // inside out zoomed in
  // gPatterns.push_back(std::bind(&ANIMartRIX::Module_Experiment2, animatrix));   // stretched distance, fire colors
  // gPatterns.push_back(std::bind(&ANIMartRIX::Module_Experiment1, animatrix));   // inside out demo
  // gPatterns.push_back(std::bind(&ANIMartRIX::Parametric_Water, animatrix));     // slow blue ambientlight
  // gPatterns.push_back(std::bind(&ANIMartRIX::Water, animatrix));                // nice water simulation
  // gPatterns.push_back(std::bind(&ANIMartRIX::Complex_Kaleido_6, animatrix));    // red blue moire
  // gPatterns.push_back(std::bind(&ANIMartRIX::Complex_Kaleido_5, animatrix));    // interference pattern
  gPatterns.push_back(std::bind(&ANIMartRIX::Complex_Kaleido_4, animatrix));    // colorful slow mandala
  gPatterns.push_back(std::bind(&ANIMartRIX::Complex_Kaleido_3, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Complex_Kaleido_2, animatrix));    // hypnotic smooth
  gPatterns.push_back(std::bind(&ANIMartRIX::Complex_Kaleido, animatrix));
  // gPatterns.push_back(std::bind(&ANIMartRIX::SM10, animatrix));                 // like 9 but fire colors - slow
  // gPatterns.push_back(std::bind(&ANIMartRIX::SM9, animatrix));                  // polar domain warping
  // gPatterns.push_back(std::bind(&ANIMartRIX::SM8, animatrix));                  // careful: flashy rings
  // // gPatterns.push_back(std::bind(&ANIMartRIX::SM7, animatrix));                  // wild rings
  // gPatterns.push_back(std::bind(&ANIMartRIX::SM6, animatrix));                  // red + blue, pretty and beautiful one, my favourite so far
  // gPatterns.push_back(std::bind(&ANIMartRIX::SM5, animatrix));                  // nice colorful roto blobs
  // gPatterns.push_back(std::bind(&ANIMartRIX::SM4, animatrix));                  // layer merge test
  // gPatterns.push_back(std::bind(&ANIMartRIX::SM3, animatrix));                  // cartesian domain warping
  // gPatterns.push_back(std::bind(&ANIMartRIX::SM2, animatrix));                  // roro zoom
  // gPatterns.push_back(std::bind(&ANIMartRIX::SM1, animatrix));                  // copy caleido
  // gPatterns.push_back(std::bind(&ANIMartRIX::Big_Caleido, animatrix));          // 5/6 Kaleido + rings
  // gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs5, animatrix));           // sqrtf dist
  // gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs4, animatrix));
  // gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs3, animatrix));
  // gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs2, animatrix));
  // gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs, animatrix));            // multi roto stuff
  // gPatterns.push_back(std::bind(&ANIMartRIX::Polar_Waves, animatrix));          // spiral waves
  // gPatterns.push_back(std::bind(&ANIMartRIX::Slow_Fade, animatrix));            // red big spiral 
  // gPatterns.push_back(std::bind(&ANIMartRIX::Zoom, animatrix));                 // boring
  // gPatterns.push_back(std::bind(&ANIMartRIX::Hot_Blob, animatrix));             // something firey, hot center
  // gPatterns.push_back(std::bind(&ANIMartRIX::Spiralus2, animatrix));            // slow
  // gPatterns.push_back(std::bind(&ANIMartRIX::Spiralus, animatrix));             // *2
  // gPatterns.push_back(std::bind(&ANIMartRIX::Yves, animatrix));                 // red warpings
  // gPatterns.push_back(std::bind(&ANIMartRIX::Scaledemo1, animatrix));           // *3 + ring red blue
  gPatterns.push_back(std::bind(&ANIMartRIX::Lava1, animatrix));                // slow ambilight
  // gPatterns.push_back(std::bind(&ANIMartRIX::Caleido3, animatrix));             // roto
  // gPatterns.push_back(std::bind(&ANIMartRIX::Caleido2, animatrix));             // roto *2
  // gPatterns.push_back(std::bind(&ANIMartRIX::Caleido1, animatrix));             // star like
  // gPatterns.push_back(std::bind(&ANIMartRIX::Distance_Experiment, animatrix));  // big orange yellow smooth
  // gPatterns.push_back(std::bind(&ANIMartRIX::Center_Field, animatrix));         // boring green yello red
  // gPatterns.push_back(std::bind(&ANIMartRIX::Waves, animatrix));                // cool big red blue
  // gPatterns.push_back(std::bind(&ANIMartRIX::Chasing_Spirals, animatrix));      // slim
  // gPatterns.push_back(std::bind(&ANIMartRIX::Rotating_Blob, animatrix));        // 
  
  gPatternCount = gPatterns.size();

  Serial.println("Setup complete");

}

//*******************************************************************************************************************

void loop() {             


  
  // Automatic playback
  static int pattern = 0;
  gPatterns[pattern]();

  // animatrix.Lava1();

   backgroundLayer.swapBuffers(true);
   
  EVERY_N_MILLIS(500) {
    animatrix.report_performance();  // check serial monitor for report
  }

  EVERY_N_SECONDS( 10 ) { 
    pattern++;
    if(pattern >= gPatternCount) pattern = 0;
   } // change patterns periodically
   Serial.println("New pattern");
} 



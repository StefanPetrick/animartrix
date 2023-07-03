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

#include <FastLED.h>
#include <ANIMartRIX.h>

#include <TeensyDMX.h>

namespace teensydmx = ::qindesign::teensydmx;

#define num_x 30  // how many LEDs are in one row?
#define num_y 30  // how many rows?

#define NUM_LED (num_x * num_y)
CRGB leds[NUM_LED];  // framebuffer

bool serpentine = true;

// Create the DMX receiver on Serial1.
teensydmx::Receiver dmxRx{ Serial1 };


class FastLEDANIMartRIX : public ANIMartRIX {
  CRGB* leds;
public:
  FastLEDANIMartRIX(int x, int y, CRGB* leds, bool serpentine) {
    this->init(x, y, serpentine);
    this->leds = leds;
  }
  void setPixelColor(int x, int y, rgb pixel) {
    leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
  }
  void setPixelColor(int index, rgb pixel) {
    leds[index] = CRGB(pixel.red, pixel.green, pixel.blue);
  }
};
FastLEDANIMartRIX animatrix(num_x, num_y, leds, serpentine);


std::vector<std::function<void(void)>> gPatterns;

int gPatternCount = 0;

//******************************************************************************************************************


void setup() {

  // FastLED.addLeds<NEOPIXEL, 13>(leds, NUM_LED);

  FastLED.addLeds<APA102, 7, 14, BGR, DATA_RATE_MHZ(8)>(leds, NUM_LED);

  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);  // optional current limiting [5V, 2000mA]

  Serial.begin(115200);  // check serial monitor for current fps count

  // fill_rainbow(leds, NUM_LED, 0);
  fill_solid(leds, NUM_LED, CRGB::Green);
  FastLED.show();

  // Start the receiver
  dmxRx.begin();

  gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs5, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs5, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs4, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs3, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs2, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::RGB_Blobs, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Polar_Waves, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Slow_Fade, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Zoom2, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Zoom, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Hot_Blob, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Spiralus2, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Spiralus, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Yves, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Scaledemo1, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Lava1, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Caleido3, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Caleido2, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Caleido1, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Distance_Experiment, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Center_Field, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Waves, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Chasing_Spirals, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Rotating_Blob, animatrix));
  gPatterns.push_back(std::bind(&ANIMartRIX::Rings, animatrix));


  gPatternCount = gPatterns.size();
}

//*******************************************************************************************************************

void loop() {
  //FastLED.clear();
  int pattern = map(dmxRx.get(1), 0, 255, 0, (gPatternCount - 1));  // select pattern
  gPatterns[pattern]();

  uint8_t v = dmxRx.get(2);  // fetch speed
  float speedFactor = (float)map(v, 0, 255, 10, 100) / 10.0f;
  animatrix.setSpeedFactor(speedFactor);

  FastLED.show();
  EVERY_N_MILLIS(500)
  animatrix.report_performance();  // check serial monitor for report
}

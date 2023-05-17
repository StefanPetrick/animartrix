#ifdef USE_SMARTMATRIX
void get_ready() {  // wait until new buffer is ready, measure time

  a = micros(); 
  while(backgroundLayer.isSwapPending());
  b = micros(); 
}

void show_frame(){  // swap buffers, measure time, output current performance

  backgroundLayer.swapBuffers(false);  
  c = micros();                               // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report 
}

rgb24 setPixelColor(rgb pixel) {
  pixel = rgb_sanity_check(pixel);
  return rgb24(pixel.red, pixel.green, pixel.blue);
}

#else
void get_ready() {

  a = micros(); 
  // while(backgroundLayer.isSwapPending());
  b = micros(); 
}

void show_frame(){  // update LEDs, measure time, output current performance

  FastLED.show();
  c = micros();                               // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report 
}

CRGB setPixelColor(rgb pixel) {
  pixel = rgb_sanity_check(pixel);
  return CRGB(pixel.red, pixel.green, pixel.blue);
}
#endif

// Show the current framerate, rendered pixels per second,
// rendering time & time spend to push the data to the leds.
// in the serial monitor.

void report_performance() {
  
  float calc  = b - a;                         // waiting time
  float push  = c - b;                         // rendering time
  float total = c - a;                         // time per frame
  int fps  = 1000000 / total;                // frames per second
  int kpps = (fps * num_x * num_y) / 1000;   // kilopixel per second

  Serial.print(fps);                         Serial.print(" fps  ");
  Serial.print(kpps);                        Serial.print(" kpps @");
  Serial.print(num_x*num_y);                 Serial.print(" LEDs  ");  
  Serial.print(round(total));                Serial.print(" µs per frame  waiting: ");
  Serial.print(round((calc * 100) / total)); Serial.print("%  rendering: ");
  Serial.print(round((push * 100) / total)); Serial.print("%  (");
  Serial.print(round(calc));                 Serial.print(" + ");
  Serial.print(round(push));                 Serial.print(" µs)  ");
#ifndef ESP32  
  Serial.print("Core-temp: %f °C\n", tempmonGetTemp());
#else
  Serial.println("");
#endif
}

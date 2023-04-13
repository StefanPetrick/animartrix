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

/*
  get_ready(); 
  rgb24 *buffer = backgroundLayer.backBuffer();    
  
  
  buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));

*/      



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
  Serial.print(round(push));                 Serial.print(" µs)  Core-temp: ");
  Serial.print( tempmonGetTemp() );          Serial.println(" °C");
}

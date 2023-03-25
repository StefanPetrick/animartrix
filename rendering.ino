// Convert the 2 polar coordinates back to cartesian ones & also apply all 3d transitions.
// Calculate the noise value at this point based on the 5 dimensional manipulation of 
// the underlaying coordinates.

float render_value(render_parameters &animation) {

  // convert polar coordinates back to cartesian ones

  float newx = (animation.offset_x + animation.center_x - (cosf(animation.angle) * animation.dist)) * animation.scale_x;
  float newy = (animation.offset_y + animation.center_y - (sinf(animation.angle) * animation.dist)) * animation.scale_y;
  float newz = (animation.offset_z + animation.z) * animation.scale_z;

  // render noisevalue at this new cartesian point

  float raw_noise_field_value = pnoise(newx, newy, newz);
  
  // A) enhance histogram (improve contrast) by setting the black and white point (low & high_limit)
  // B) scale the result to a 0-255 range (assuming you want 8 bit color depth per rgb chanel)
  // Here happens the contrast boosting & the brightness mapping

  if (raw_noise_field_value < animation.low_limit)  raw_noise_field_value =  animation.low_limit;
  if (raw_noise_field_value > animation.high_limit) raw_noise_field_value = animation.high_limit;

  float scaled_noise_value = map(raw_noise_field_value, animation.low_limit, animation.high_limit, 0, 255);

  return scaled_noise_value;
}


// given a static polar origin we can precalculate 
// the polar coordinates

void render_polar_lookup_table(float cx, float cy) {

  for (int xx = 0; xx < num_x; xx++) {
    for (int yy = 0; yy < num_y; yy++) {

      float dx = xx - cx;
      float dy = yy - cy;

      distance[xx][yy]    = hypotf(dx, dy);
      polar_theta[xx][yy] = atan2f(dy, dx); 
    }
  }
}

/* ...too slow!

// float mapping maintaining 32 bit precision
// we keep values with high resolution for potential later usage

float map_float(float x, float in_min, float in_max, float out_min, float out_max) { 
  
  float result = (x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min;
  if (result < out_min) result = out_min;
  if( result > out_max) result = out_max;

  return result; 
}
*/

/* unnecessary bloat

// check result after colormapping and store the newly rendered rgb data

void write_pixel_to_framebuffer(int x, int y, rgb &pixel) {

      // assign the final color of this one pixel
      CRGB finalcolor = CRGB(pixel.red, pixel.green, pixel.blue);
     
      // write the rendered pixel into the framebutter
      leds[xy(x, y)] = finalcolor;
}
*/


// Avoid any possible color flicker by forcing the raw RGB values to be 0-255.
// This enables to play freely with random equations for the colormapping
// without causing flicker by accidentally missing the valid target range.

rgb rgb_sanity_check(rgb &pixel) {

      // rescue data if possible, return absolute value
      //if (pixel.red < 0)     pixel.red = fabsf(pixel.red);
      //if (pixel.green < 0) pixel.green = fabsf(pixel.green);
      //if (pixel.blue < 0)   pixel.blue = fabsf(pixel.blue);
      
      // discard everything above the valid 8 bit colordepth 0-255 range
      if (pixel.red   > 255)   pixel.red = 255;
      if (pixel.green > 255) pixel.green = 255;
      if (pixel.blue  > 255)  pixel.blue = 255;

      return pixel;
}


// find the right led index according to you LED matrix wiring

uint16_t xy(uint8_t x, uint8_t y) {
  if (y & 1)                             // check last bit
    return (y + 1) * num_x - 1 - x;      // reverse every second line for a serpentine lled layout
  else
    return y * num_x + x;                // use this equation only for a line by line layout
}                                        // remove the previous 3 lines of code in this case



// Show the current framerate, rendered pixels per second,
// rendering time & time spend to push the data to the leds.
// in the serial monitor.

void report_performance() {
  
  float calc  = b - a;                         // rendering time
  float push  = c - b;                         // time to initialize led update
  float total = c - a;                         // time per frame
  int fps  = 1000000 / total;                // frames per second
  int kpps = (fps * num_x * num_y) / 1000;   // kilopixel per second

  Serial.print(fps);                         Serial.print(" fps  ");
  Serial.print(kpps);                        Serial.print(" kpps @");
  Serial.print(num_x*num_y);                 Serial.print(" LEDs  ");  
  Serial.print(round(total));                Serial.print(" µs per frame  Rendering: ");
  Serial.print(round((calc * 100) / total)); Serial.print("%  Sending data: ");
  Serial.print(round((push * 100) / total)); Serial.print("%  (");
  Serial.print(round(calc));                 Serial.print(" + ");
  Serial.print(round(push));                 Serial.println(" µs) ");
}

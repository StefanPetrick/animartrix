
void Rotating_Blob() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 0.1;         // higher values = faster transitions
  timings.ratio[1] = 0.03;
  timings.ratio[2] = 0.03;
  timings.ratio[3] = 0.03;
  
  
  timings.offset[1] = 10;
  timings.offset[2] = 20;
  timings.offset[3] = 30;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = polar_theta[y][x] +  move.radial[0];
      animation.dist       = distance[y][x];
      animation.z          = move.linear[0];
      animation.low_limit  = -1;
      float show1          = render_value(animation);
      
      animation.angle      = polar_theta[x][y] - move.radial[1] + show1/512.0;
      animation.dist       = distance[y][x] * show1/255.0;
      animation.low_limit  = 0;
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] - move.radial[2] + show1/512.0;
      animation.dist       = distance[y][x] * show1/220.0;
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.angle      = polar_theta[x][y] - move.radial[3] + show1/512.0;
      animation.dist       = distance[y][x] * show1/200.0;
      animation.z          = move.linear[3];
      float show4          = render_value(animation);

      // colormapping
      pixel.red   = (show2+show4)/2;
      pixel.green = show3 / 6;
      pixel.blue  = 0;

      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()

  FastLED.show();

  c = micros(); // for time measurement in report_performance()
  
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report

}




void Chasing_Spirals() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 0.1;         // higher values = faster transitions
  timings.ratio[1] = 0.13;
  timings.ratio[2] = 0.16;
  
  timings.offset[1] = 10;
  timings.offset[2] = 20;
  timings.offset[3] = 30;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = 3 * polar_theta[y][x] +  move.radial[0] - distance[y][x]/3;
      animation.dist       = distance[y][x];
      animation.offset_x   = move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = 3 * polar_theta[y][x] +  move.radial[1] - distance[y][x]/3;
      animation.dist       = distance[y][x];
      animation.offset_x   = move.linear[1];
      float show2          = render_value(animation);

      animation.angle      = 3 * polar_theta[y][x] +  move.radial[2] - distance[y][x]/3;
      animation.dist       = distance[y][x];
      animation.offset_x   = move.linear[2];
      float show3          = render_value(animation);

      // colormapping
      float radius = 10;
      float radial_filter = (radius - distance[y][x]) / radius;

      pixel.red   = 3*show1 * radial_filter;
      pixel.green = show2 * radial_filter / 2;
      pixel.blue  = show3 * radial_filter / 4;

      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()

  FastLED.show();

  c = micros(); // for time measurement in report_performance()
  
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report

}
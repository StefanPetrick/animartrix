
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
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.offset_x   = 0;
      animation.offset_y   = 0;
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
      animation.scale_z    = 0.1;  
      animation.scale_y    = 0.1;
      animation.scale_x    = 0.1;
      animation.offset_x   = move.linear[0];
      animation.offset_y   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
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


void Rings() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 1;         // higher values = faster transitions
  timings.ratio[1] = 1.1;
  timings.ratio[2] = 1.2;
  
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = 5;
      animation.scale_x    = 0.2;
      animation.scale_y    = 0.2;
      animation.scale_z    = 1;
      animation.dist       = distance[y][x];
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      float show1          = render_value(animation);

       // describe and render animation layers
      animation.angle      = 10;
      
      animation.dist       = distance[y][x];
      animation.offset_y   = -move.linear[1];
      float show2          = render_value(animation);

       // describe and render animation layers
      animation.angle      = 12;
      
      animation.dist       = distance[y][x];
      animation.offset_y   = -move.linear[2];
      float show3          = render_value(animation);

      // colormapping
      pixel.red   = show1;
      pixel.green = show2 / 4;
      pixel.blue  = show3 / 4;

      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()

  FastLED.show();

  c = micros(); // for time measurement in report_performance()
  
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report

}

void Waves() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 2;         // higher values = faster transitions
  timings.ratio[1] = 2.1;
  timings.ratio[2] = 1.2;
  
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = polar_theta[y][x];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.scale_z    = 0.1;
      animation.dist       = distance[y][x];
      animation.offset_y   = 0;
      animation.offset_x   = 0;
      animation.z          = 2*distance[y][x] - move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[y][x];
      animation.dist       = distance[y][x];
      animation.z          = 2*distance[y][x] - move.linear[1];
      float show2          = render_value(animation);

  
      // colormapping
      pixel.red   = show1;
      pixel.green = 0;
      pixel.blue  = show2;

      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()

  FastLED.show();

  c = micros(); // for time measurement in report_performance()
  
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report

}

void Center_Field() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 1;         // higher values = faster transitions
  timings.ratio[1] = 1.1;
  timings.ratio[2] = 1.2;
  
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.dist       = 5*sqrtf(distance[y][x]);
      animation.offset_y   = move.linear[0];
      animation.offset_x   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.dist       = 4*sqrtf(distance[y][x]);
      animation.offset_y   = move.linear[0];
      animation.offset_x   = 0;
      animation.z          = 0;
      float show2          = render_value(animation);

     

  
      // colormapping
      pixel.red   = show1;
      pixel.green = show2;
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

void Distance_Experiment() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.01;    // speed ratios for the oscillators
  timings.ratio[0] = 0.2;         // higher values = faster transitions
  timings.ratio[1] = 0.13;
  timings.ratio[2] = 0.012;
  
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = powf(distance[y][x], 0.5);
      animation.angle      = polar_theta[x][y] + move.radial[0];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.offset_y   = move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.dist       = powf(distance[y][x], 0.6);
      animation.angle      = polar_theta[x][y] + move.noise_angle[2];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.offset_y   = move.linear[1];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show2          = render_value(animation);
      
      // colormapping
      pixel.red   = show1+show2;
      pixel.green = show2;
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


void Caleido1() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.003;    // speed ratios for the oscillators
  timings.ratio[0] = 0.02;         // higher values = faster transitions
  timings.ratio[1] = 0.03;
  timings.ratio[2] = 0.04;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.6;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = distance[x][y] * (2 + move.directional[0]) / 3;
      animation.angle      = 3 * polar_theta[x][y] + 3 * move.noise_angle[0] + move.radial[4];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.scale_z    = 0.1;
      animation.offset_y   = 2 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = move.linear[0];
      float show1          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[1]) / 3;
      animation.angle      = 4 * polar_theta[x][y] + 3 * move.noise_angle[1] + move.radial[4];
      animation.offset_x   = 2 * move.linear[1];
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[2]) / 3;
      animation.angle      = 5 * polar_theta[x][y] + 3 * move.noise_angle[2] + move.radial[4];
      animation.offset_y   = 2 * move.linear[2];
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[3]) / 3;
      animation.angle      = 4 * polar_theta[x][y] + 3 * move.noise_angle[3] + move.radial[4];
      animation.offset_x   = 2 * move.linear[3];
      animation.z          = move.linear[3];
      float show4          = render_value(animation);
      
      // colormapping
      pixel.red   = show1;
      pixel.green = show3 * distance[x][y] / 10;
      pixel.blue  = (show2 + show4) / 2;

      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show();
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report

}

void Caleido2() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.001;    // speed ratios for the oscillators
  timings.ratio[0] = 0.02;         // higher values = faster transitions
  timings.ratio[1] = 0.03;
  timings.ratio[2] = 0.04;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.6;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
  
      // describe and render animation layers
      animation.dist       = distance[x][y] * (2 + move.directional[0]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[0] + move.radial[4];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.scale_z    = 0.1;
      animation.offset_y   = 2 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = move.linear[0];
      float show1          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[1]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[1] + move.radial[4];
      animation.offset_x   = 2 * move.linear[1];
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[2]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[2] + move.radial[4];
      animation.offset_y   = 2 * move.linear[2];
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[3]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[3] + move.radial[4];
      animation.offset_x   = 2 * move.linear[3];
      animation.z          = move.linear[3];
      float show4          = render_value(animation);
      
      // colormapping
      pixel.red   = show1;
      pixel.green = show3 * distance[x][y] / 10;
      pixel.blue  = (show2 + show4) / 2;

      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show();
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report

}

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
      animation.angle      = polar_theta[x][y] +  move.radial[0];
      animation.dist       = distance[x][y];
      animation.z          = move.linear[0];
      animation.low_limit  = -1;
      float show1          = render_value(animation);
      
      animation.angle      = polar_theta[x][y] - move.radial[1] + show1/512.0;
      animation.dist       = distance[x][y] * show1/255.0;
      animation.low_limit  = 0;
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] - move.radial[2] + show1/512.0;
      animation.dist       = distance[x][y] * show1/220.0;
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.angle      = polar_theta[x][y] - move.radial[3] + show1/512.0;
      animation.dist       = distance[x][y] * show1/200.0;
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
      animation.angle      = 3 * polar_theta[x][y] +  move.radial[0] - distance[x][y]/3;
      animation.dist       = distance[x][y];
      animation.scale_z    = 0.1;  
      animation.scale_y    = 0.1;
      animation.scale_x    = 0.1;
      animation.offset_x   = move.linear[0];
      animation.offset_y   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.angle      = 3 * polar_theta[x][y] +  move.radial[1] - distance[x][y]/3;
      animation.dist       = distance[x][y];
      animation.offset_x   = move.linear[1];
      float show2          = render_value(animation);

      animation.angle      = 3 * polar_theta[x][y] +  move.radial[2] - distance[x][y]/3;
      animation.dist       = distance[x][y];
      animation.offset_x   = move.linear[2];
      float show3          = render_value(animation);

      // colormapping
      float radius = 10;
      float radial_filter = (radius - distance[x][y]) / radius;

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
      animation.dist       = distance[x][y];
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      float show1          = render_value(animation);

       // describe and render animation layers
      animation.angle      = 10;
      
      animation.dist       = distance[x][y];
      animation.offset_y   = -move.linear[1];
      float show2          = render_value(animation);

       // describe and render animation layers
      animation.angle      = 12;
      
      animation.dist       = distance[x][y];
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
      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.scale_z    = 0.1;
      animation.dist       = distance[x][y];
      animation.offset_y   = 0;
      animation.offset_x   = 0;
      animation.z          = 2*distance[x][y] - move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y];
      animation.dist       = distance[x][y];
      animation.z          = 2*distance[x][y] - move.linear[1];
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
      animation.dist       = 5*sqrtf(distance[x][y]);
      animation.offset_y   = move.linear[0];
      animation.offset_x   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.dist       = 4*sqrtf(distance[x][y]);
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
      animation.dist       = powf(distance[x][y], 0.5);
      animation.angle      = polar_theta[x][y] + move.radial[0];
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.scale_z    = 0.1;
      animation.offset_y   = move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.dist       = powf(distance[x][y], 0.6);
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

  timings.master_speed = 0.002;    // speed ratios for the oscillators
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

void Caleido3() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.004;    // speed ratios for the oscillators
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
      animation.scale_x    = 0.1;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.1;// + (move.directional[1] + 2)/100;
      animation.scale_z    = 0.1;
      animation.offset_y   = 2 * move.linear[0];
      animation.offset_x   = 2 * move.linear[1];
      animation.offset_z   = 0;
      animation.z          = move.linear[0];
      float show1          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[1]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[1] + move.radial[4];
      animation.offset_x   = 2 * move.linear[1];
      animation.offset_y   = show1 / 20.0;
      animation.z          = move.linear[1];
      float show2          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[2]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[2] + move.radial[4];
      animation.offset_y   = 2 * move.linear[2];
      animation.offset_x   = show2 / 20.0;
      animation.z          = move.linear[2];
      float show3          = render_value(animation);

      animation.dist       = distance[x][y] * (2 + move.directional[3]) / 3;
      animation.angle      = 2 * polar_theta[x][y] + 3 * move.noise_angle[3] + move.radial[4];
      animation.offset_x   = 2 * move.linear[3];
      animation.offset_y   = show3 / 20.0;
      animation.z          = move.linear[3];
      float show4          = render_value(animation);
      
      // colormapping
      float radius = 8;  // radial mask

      pixel.red   = show1 * (y+1) / num_y;
      pixel.green = show3 * distance[x][y] / 10;
      pixel.blue  = (show2 + show4) / 2;
      if (distance[x][y] > radius) {
        pixel.red = 0;
        pixel.green = 0;
        pixel.blue = 0;
      }

      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show();
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}

void Lava1() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.0015;    // speed ratios for the oscillators
  timings.ratio[0] = 4;         // higher values = faster transitions
  timings.ratio[1] = 1;
  timings.ratio[2] = 1;
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
      animation.dist       = distance[x][y] * 0.8;
      animation.angle      = polar_theta[x][y];
      animation.scale_x    = 0.15;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.12;// + (move.directional[1] + 2)/100;
      animation.scale_z    = 0.01;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 30;
      float show1          = render_value(animation);

      animation.offset_y   = -move.linear[1];
      animation.scale_x    = 0.15;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.12;// + (move.directional[1] + 2)/100;
      animation.offset_x   = show1 / 100;
      animation.offset_y   += show1/100;
     
      float show2          = render_value(animation);

      animation.offset_y   = -move.linear[2];
      animation.scale_x    = 0.15;// + (move.directional[0] + 2)/100;
      animation.scale_y    = 0.12;// + (move.directional[1] + 2)/100;
      animation.offset_x   = show2 / 100;
      animation.offset_y   += show2/100;
     
      float show3         = render_value(animation);

      // colormapping
      float linear = (y)/(num_y-1.f);  // radial mask

      pixel.red = linear*show2;
      pixel.green = 0.1*linear*(show2-show3);
      
      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show();
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report

}

void Scaledemo1() {

a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.00003;    // speed ratios for the oscillators
  timings.ratio[0] = 4;         // higher values = faster transitions
  timings.ratio[1] = 3.2;
  timings.ratio[2] = 10;
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
      animation.dist       = 0.3*distance[x][y] * 0.8;
      animation.angle      = 3*polar_theta[x][y] + move.radial[2];
      animation.scale_x    = 0.1 + (move.noise_angle[0])/10;
      animation.scale_y    = 0.1 + (move.noise_angle[1])/10;// + (move.directional[1] + 2)/100;
      animation.scale_z    = 0.01;
      animation.offset_y   = 0;
      animation.offset_x   = 0;
      animation.offset_z   = 100*move.linear[0];
      animation.z          = 30;
      float show1          = render_value(animation);

      animation.angle      = 3;
      float show2          = render_value(animation);

      float dist = (10-distance[x][y])/ 10;
      pixel.red = show1*dist;
      pixel.green = (show1-show2)*dist*0.3;
      pixel.blue = (show2-show1)*dist;

      if (distance[x][y] > 8) {
         pixel.red = 0;
         pixel.green = 0;
         pixel.blue = 0;

      }
      
      pixel = rgb_sanity_check(pixel);

      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report

}


void Yves() {

  a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.001;    // speed ratios for the oscillators
  timings.ratio[0] = 3;         // higher values = faster transitions
  timings.ratio[1] = 2;
  timings.ratio[2] = 1;
  timings.ratio[3] = 0.13;
  timings.ratio[4] = 0.15;
  timings.ratio[5] = 0.03;
  timings.ratio[6] = 0.025;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] ;
      animation.angle      = polar_theta[x][y] + 2*PI + move.noise_angle[5];
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.scale_z    = 0.08;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show1          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + 2*PI + move.noise_angle[6];;
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.scale_z    = 0.08;
      animation.offset_y   = -move.linear[1];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = 0;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + show1/100 + move.noise_angle[3] + move.noise_angle[4];
      animation.dist       = distance[x][y] + show2/50;
      animation.offset_y   = -move.linear[2];

      animation.offset_y   += show1/100;
      animation.offset_x   += show2/100;

      float show3          = render_value(animation);

      animation.offset_y   = 0;
      animation.offset_x   = 0;

      float show4          = render_value(animation);
      
     
      pixel.red   = show3;
      pixel.green = show3*show4/255;
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

void Spiralus() {

  a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.0011;    // speed ratios for the oscillators
  timings.ratio[0] = 1.5;         // higher values = faster transitions
  timings.ratio[1] = 2.3;
  timings.ratio[2] = 3;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.2;
  timings.ratio[5] = 0.03;
  timings.ratio[6] = 0.025;
  timings.ratio[7] = 0.021;
  timings.ratio[8] = 0.027;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] ;
      animation.angle      = 2*polar_theta[x][y] + move.noise_angle[5] + move.directional[3] * move.noise_angle[6]* animation.dist/10;
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.scale_z    = 0.02;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = move.linear[1];
      float show1          = render_value(animation);

      animation.angle      = 2*polar_theta[x][y] + move.noise_angle[7] + move.directional[5] * move.noise_angle[8]* animation.dist/10;
      animation.offset_y   = -move.linear[1];
      animation.z          = move.linear[2];
            
      float show2          = render_value(animation);

      animation.angle      = 2*polar_theta[x][y] + move.noise_angle[6] + move.directional[6] * move.noise_angle[7]* animation.dist/10;
      animation.offset_y   = move.linear[2];
      animation.z          = move.linear[0];
      float show3          = render_value(animation);
      
      
      float f =  (20-distance[x][y])/20;
     
      pixel.red   = f*(show1+show2);
      pixel.green = f*(show1-show2);
      pixel.blue  = f*(show3-show1);
      
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}

void Spiralus2() {

  a = micros();                   // for time measurement in report_performance()

  timings.master_speed = 0.0011;    // speed ratios for the oscillators
  timings.ratio[0] = 1.5;         // higher values = faster transitions
  timings.ratio[1] = 2.3;
  timings.ratio[2] = 3;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.2;
  timings.ratio[5] = 0.03;
  timings.ratio[6] = 0.025;
  timings.ratio[7] = 0.021;
  timings.ratio[8] = 0.027;
  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  
  calculate_oscillators(timings);     // get linear movers and oscillators going

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] ;
      animation.angle      = 2*polar_theta[x][y] + move.noise_angle[5] + move.directional[3] * move.noise_angle[6]* animation.dist/10;
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.scale_z    = 0.02;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = move.linear[1];
      float show1          = render_value(animation);

      animation.angle      = 3*polar_theta[x][y] + move.noise_angle[7] + move.directional[5] * move.noise_angle[8]* animation.dist/10;
      animation.offset_y   = -move.linear[1];
      animation.z          = move.linear[2];
            
      float show2          = render_value(animation);

      animation.angle      = 4*polar_theta[x][y] + move.noise_angle[6] + move.directional[6] * move.noise_angle[7]* animation.dist/10;
      animation.offset_y   = move.linear[2];
      animation.z          = move.linear[0];
      animation.dist       = distance[x][y] *0.8;
      float show3          = render_value(animation);
      
      
      float f =  (20-distance[x][y])/20;
     
      pixel.red   = f*(show1+show2);
      pixel.green = f*(show1-show2);
      pixel.blue  = f*(show3-show1);
      
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}


void Hot_Blob() { // nice one

  a = micros();                   

  run_default_oscillators();

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] ;
      animation.angle      = polar_theta[x][y];
      
      animation.scale_x    = 0.07 + move.directional[0]*0.002;
      animation.scale_y    = 0.07;
      
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      
      animation.z          = 0;
      animation.low_limit  = -1;
      float show1          = render_value(animation);

      animation.offset_y   = -move.linear[1];
      float show3          = render_value(animation);

      animation.offset_x   = show3/20;
      animation.offset_y   = -move.linear[0]/2 + show1/70;
      animation.low_limit  = 0;
      float show2          = render_value(animation);

      animation.offset_x   = show3/20;
      animation.offset_y   = -move.linear[0]/2 + show1/70;
      animation.z          = 100;
      float show4          = render_value(animation);

      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-animation.dist)/animation.dist;

      float linear = (y+1)/(num_y-1.f);
      
      pixel.red   = radial  * show2;
      pixel.green   = linear * radial* 0.3* (show2-show4);
      
      
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}

void Zoom() { // nice one

  a = micros();                   

  run_default_oscillators();
  timings.master_speed = 0.003;
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] * distance[x][y];
      animation.angle      = polar_theta[x][y];
      
      animation.scale_x    = 0.01;
      animation.scale_y    = 0.01;
      
      animation.offset_y   = -10*move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      
      animation.z          = 0;
      animation.low_limit  = 0;
      float show1          = render_value(animation);

    
      /*
      animation.offset_x   = 0;
      animation.offset_y   = -move.linear[0]/2;
      animation.low_limit  = 0;
      float show2          = render_value(animation);

     

      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];
      */
      float linear = (y+1)/(num_y-1.f);
      
      pixel.red   = show1*linear;
      pixel.green   = 0;
      
      
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}




void Slow_Fade() { // nice one

  a = micros();                   

  run_default_oscillators();
  timings.master_speed = 0.00005;
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = sqrtf(distance[x][y]) * 0.7 * (move.directional[0] + 1.5);
      animation.angle      = polar_theta[x][y] - move.radial[0] + distance[x][y] / 5;
      
      animation.scale_x    = 0.11;
      animation.scale_y    = 0.11;
      
      animation.offset_y   = -50 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      
      animation.z          = move.linear[0];
      animation.low_limit  = -0.1;
      animation.high_limit = 1;
      float show1          = render_value(animation);

      animation.dist       = animation.dist  * 1.1;
      animation.angle      += move.noise_angle[0] / 10;
      float show2          = render_value(animation);

      animation.dist       = animation.dist  * 1.1;
      animation.angle      += move.noise_angle[1] / 10;
      
      float show3          = render_value(animation);

      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];


    
      
      pixel.red    = radial * show1;
      pixel.green  = radial * (show1 - show2) / 6;
      pixel.blue   = radial * (show1 - show3) / 5;
      
      
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}

void Polar_Waves() { // nice one

  a = micros();                   

  timings.master_speed = 0.5;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] - animation.dist * 0.25 + move.radial[0];
      animation.z          = (animation.dist * 1.5)-10 * move.linear[0];
      animation.scale_x    = 0.15;
      animation.scale_y    = 0.15;
      animation.offset_x   = move.linear[0];
      
      float show1          = render_value(animation);
      animation.angle      = polar_theta[x][y] - animation.dist * 0.25 + move.radial[1];
      animation.z          = (animation.dist * 1.5)-10 * move.linear[1];
      animation.offset_x   = move.linear[1];

      float show2          = render_value(animation);
      animation.angle      = polar_theta[x][y] - animation.dist * 0.25 + move.radial[2];
      animation.z          = (animation.dist * 1.5)-10 * move.linear[2];
      animation.offset_x   = move.linear[2];

      float show3          = render_value(animation);

      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * show1;
      pixel.green  = radial * show2;
      pixel.blue   = radial * show3;
      
      
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}

void RGB_Blobs() { // nice one

  a = micros();                   

  timings.master_speed = 0.2;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3];
      animation.z          = (sqrtf(animation.dist));// - 10 * move.linear[0];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.offset_z   = 10;
      animation.offset_x   = 10*move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4];
      animation.offset_x   = 11*move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5];
      animation.offset_x   = 12*move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      

      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * show1;
      pixel.green  = radial * show2;
      pixel.blue   = radial * show3;
     
      
      
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}


void RGB_Blobs2() { // nice one

  a = micros();                   

  timings.master_speed = 0.12;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3] + move.noise_angle[1];
      animation.z          = (sqrtf(animation.dist));// - 10 * move.linear[0];
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.offset_z   = 10;
      animation.offset_x   = 10*move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4] + move.noise_angle[2];
      animation.offset_x   = 11*move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5]+ move.noise_angle[3];
      animation.offset_x   = 12*move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      
      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1-show3);
      pixel.green  = radial * (show2-show1);
      pixel.blue   = radial * (show3-show2);
     
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}

void RGB_Blobs3() { // nice one

  a = micros();                   

  timings.master_speed = 0.12;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] + move.noise_angle[4];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3] + move.noise_angle[1];
      animation.z          = (sqrtf(animation.dist));// - 10 * move.linear[0];
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = 10;
      animation.offset_x   = 10*move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4] + move.noise_angle[2];
      animation.offset_x   = 11*move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5]+ move.noise_angle[3];
      animation.offset_x   = 12*move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      
      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1+show3)*0.5 * animation.dist/5;
      pixel.green  = radial * (show2+show1)*0.5 * y/15;
      pixel.blue   = radial * (show3+show2)*0.5 * x/15;
     
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}

void RGB_Blobs4() { // nice one

  a = micros();                   

  timings.master_speed = 0.02;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] + move.noise_angle[4];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3] + move.noise_angle[1];
      animation.z          = 3+sqrtf(animation.dist);
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.offset_z   = 10;
      animation.offset_x   = 50 * move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4] + move.noise_angle[2];
      animation.offset_x   = 50 * move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5]+ move.noise_angle[3];
      animation.offset_x   = 50 * move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      
      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1+show3)*0.5 * animation.dist/5;
      pixel.green  = radial * (show2+show1)*0.5 * y/15;
      pixel.blue   = radial * (show3+show2)*0.5 * x/15;
     
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}

void RGB_Blobs5() { // nice one

  a = micros();                   

  timings.master_speed = 0.02;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] + move.noise_angle[4];
      animation.angle      = polar_theta[x][y] + move.radial[0] + move.noise_angle[0]+ move.noise_angle[3] + move.noise_angle[1];
      animation.z          = 3+sqrtf(animation.dist);
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.offset_z   = 10;
      animation.offset_x   = 50 * move.linear[0];
      float show1          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[1]+ move.noise_angle[1]+ move.noise_angle[4] + move.noise_angle[2];
      animation.offset_x   = 50 * move.linear[1];
      animation.offset_z   = 100;
      float show2          = render_value(animation);

      animation.angle      = polar_theta[x][y] + move.radial[2]+ move.noise_angle[2]+ move.noise_angle[5]+ move.noise_angle[3];
      animation.offset_x   = 50 * move.linear[2];
      animation.offset_z   = 300;
      float show3          = render_value(animation);
      
      float radius = 11;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1+show3)*0.5 * animation.dist/5;
      pixel.green  = radial * (show2+show1)*0.5 * y/15;
      pixel.blue   = radial * (show3+show2)*0.5 * x/15;
     
      pixel = rgb_sanity_check(pixel);
      leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
    }
  }
  b = micros(); // for time measurement in report_performance()
  FastLED.show(); 
  c = micros(); // for time measurement in report_performance()
  EVERY_N_MILLIS(500) report_performance();   // check serial monitor for report
}

void Rotating_Blob() {

  get_ready(); // for time measurement in report_performance() 


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
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      animation.offset_z   = 100;
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

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 
}




void Chasing_Spirals() {

  get_ready(); // for time measurement in report_performance() 


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
      float radius = radial_filter_radius;
      float radial_filter = (radius - distance[x][y]) / radius;

      pixel.red   = 3*show1 * radial_filter;
      pixel.green = show2 * radial_filter / 2;
      pixel.blue  = show3 * radial_filter / 4;

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 
}


void Rings() {

  get_ready(); // for time measurement in report_performance() 


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

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
  }
 
}
}

void Waves() {

  get_ready(); // for time measurement in report_performance() 
  

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

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 
}

void Center_Field() {

  get_ready(); // for time measurement in report_performance() 


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

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 

}

void Distance_Experiment() {


  get_ready(); // for time measurement in report_performance() 

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

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 

}


void Caleido1() {

  get_ready(); // for time measurement in report_performance() 


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

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 
}

void Caleido2() {

  get_ready(); // for time measurement in report_performance() 


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

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 
}

void Caleido3() {

  get_ready(); // for time measurement in report_performance() 


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
      float radius = radial_filter_radius;  // radial mask

      pixel.red   = show1 * (y+1) / num_y;
      pixel.green = show3 * distance[x][y] / 10;
      pixel.blue  = (show2 + show4) / 2;
      if (distance[x][y] > radius) {
        pixel.red = 0;
        pixel.green = 0;
        pixel.blue = 0;
      }

      pixel = rgb_sanity_check(pixel);

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));

    }
  }
 
}

void Lava1() {

  get_ready(); // for time measurement in report_performance() 


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

      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));

    }
  }
 
}

void Scaledemo1() {

  get_ready(); // for time measurement in report_performance() 
      

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

      float dist = 1;//(10-distance[x][y])/ 10;
      pixel.red = show1*dist;
      pixel.green = (show1-show2)*dist*0.3;
      pixel.blue = (show2-show1)*dist;

      if (distance[x][y] > 16) {
         pixel.red = 0;
         pixel.green = 0;
         pixel.blue = 0;

      }
      
      pixel = rgb_sanity_check(pixel);

      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
}


void Yves() {

  get_ready(); // for time measurement in report_performance() 
      

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
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
}

void Spiralus() {

  get_ready(); // for time measurement in report_performance() 
      

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
      
      float f =  1;
     
      pixel.red   = f*(show1+show2);
      pixel.green = f*(show1-show2);
      pixel.blue  = f*(show3-show1);
      
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 
}

void Spiralus2() {

  get_ready(); // for time measurement in report_performance() 
    

  timings.master_speed = 0.0015;    // speed ratios for the oscillators
  timings.ratio[0] = 1.5;         // higher values = faster transitions
  timings.ratio[1] = 2.3;
  timings.ratio[2] = 3;
  timings.ratio[3] = 0.05;
  timings.ratio[4] = 0.2;
  timings.ratio[5] = 0.05;
  timings.ratio[6] = 0.055;
  timings.ratio[7] = 0.06;
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
      animation.angle      = 5*polar_theta[x][y] + move.noise_angle[5] + move.directional[3] * move.noise_angle[6]* animation.dist/10;
      animation.scale_x    = 0.08;
      animation.scale_y    = 0.08;
      animation.scale_z    = 0.02;
      animation.offset_y   = -move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      animation.z          = move.linear[1];
      float show1          = render_value(animation);

      animation.angle      = 6*polar_theta[x][y] + move.noise_angle[7] + move.directional[5] * move.noise_angle[8]* animation.dist/10;
      animation.offset_y   = -move.linear[1];
      animation.z          = move.linear[2];
            
      float show2          = render_value(animation);

      animation.angle      = 6*polar_theta[x][y] + move.noise_angle[6] + move.directional[6] * move.noise_angle[7]* animation.dist/10;
      animation.offset_y   = move.linear[2];
      animation.z          = move.linear[0];
      animation.dist       = distance[x][y] *0.8;
      float show3          = render_value(animation);
      
      
      float f =  1;//(24-distance[x][y])/24;
     
      pixel.red   = f*(show1+show2);
      pixel.green = f*(show1-show2);
      pixel.blue  = f*(show3-show1);
      
      pixel = rgb_sanity_check(pixel);
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
}


void Hot_Blob() { // nice one

  get_ready(); // for time measurement in report_performance() 
                  

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

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-animation.dist)/animation.dist;

      float linear = (y+1)/(num_y-1.f);
      
      pixel.red   = radial  * show2;
      pixel.green   = linear * radial* 0.3* (show2-show4);
      
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 
}

void Zoom() { // nice one
  
  get_ready(); // for time measurement in report_performance()

  

  run_default_oscillators();
  timings.master_speed = 0.003;
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = (distance[x][y] * distance[x][y])/2;
      animation.angle      = polar_theta[x][y];
      
      animation.scale_x    = 0.005;
      animation.scale_y    = 0.005;
      
      animation.offset_y   = -10*move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0;
      
      animation.z          = 0;
      animation.low_limit  = 0;
      float show1          = render_value(animation);

  
      float linear = 1;//(y+1)/(num_y-1.f);
      
      pixel.red   = show1*linear;
      pixel.green   = 0;
      
      
      pixel = rgb_sanity_check(pixel);
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
}




void Slow_Fade() { // nice one

  get_ready(); // for time measurement in report_performance()

                    

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

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];


    
      
      pixel.red    = radial * show1;
      pixel.green  = radial * (show1 - show2) / 6;
      pixel.blue   = radial * (show1 - show3) / 5;
      
      
      pixel = rgb_sanity_check(pixel);
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
 
  
}

void Polar_Waves() { // nice one

  get_ready(); // for time measurement in report_performance()

  

                    

  timings.master_speed = 0.5;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = (distance[x][y]);
      animation.angle      = polar_theta[x][y] - animation.dist * 0.1 + move.radial[0];
      animation.z          = (animation.dist * 1.5)-10 * move.linear[0];
      animation.scale_x    = 0.15;
      animation.scale_y    = 0.15;
      animation.offset_x   = move.linear[0];
      
      float show1          = render_value(animation);
      animation.angle      = polar_theta[x][y] - animation.dist * 0.1 + move.radial[1];
      animation.z          = (animation.dist * 1.5)-10 * move.linear[1];
      animation.offset_x   = move.linear[1];

      float show2          = render_value(animation);
      animation.angle      = polar_theta[x][y] - animation.dist * 0.1 + move.radial[2];
      animation.z          = (animation.dist * 1.5)-10 * move.linear[2];
      animation.offset_x   = move.linear[2];

      float show3          = render_value(animation);

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * show1;
      pixel.green  = radial * show2;
      pixel.blue   = radial * show3;
      
      
      pixel = rgb_sanity_check(pixel);
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
  
}

void RGB_Blobs() { // nice one

  get_ready(); // for time measurement in report_performance() 
                       

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
      

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * show1;
      pixel.green  = radial * show2;
      pixel.blue   = radial * show3;
     
      
      
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
}


void RGB_Blobs2() { // nice one

  get_ready(); // for time measurement in report_performance() 
                      

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
      
      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1-show3);
      pixel.green  = radial * (show2-show1);
      pixel.blue   = radial * (show3-show2);
     
      pixel = rgb_sanity_check(pixel);
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
}

void RGB_Blobs3() { // nice one

  get_ready(); // for time measurement in report_performance()

                   

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
      
      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1+show3)*0.5 * animation.dist/5;
      pixel.green  = radial * (show2+show1)*0.5 * y/15;
      pixel.blue   = radial * (show3+show2)*0.5 * x/15;
     
      pixel = rgb_sanity_check(pixel);
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
}

void RGB_Blobs4() { // nice one

  get_ready(); // for time measurement in report_performance()

  

                     

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
      
      float radius = 23;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1+show3)*0.5 * animation.dist/5;
      pixel.green  = radial * (show2+show1)*0.5 * y/15;
      pixel.blue   = radial * (show3+show2)*0.5 * x/15;
     
      pixel = rgb_sanity_check(pixel);
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
}

void RGB_Blobs5() { // nice one

  get_ready(); // for time measurement in report_performance()

  

                   

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
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
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
      
      float radius = 23;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial * (show1+show3)*0.5 * animation.dist/5;
      pixel.green  = radial * (show2+show1)*0.5 * y/15;
      pixel.blue   = radial * (show3+show2)*0.5 * x/15;
     
      pixel = rgb_sanity_check(pixel);
   
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }

}

void Big_Caleido() { // nice one

  get_ready(); // for time measurement in report_performance()

                  

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
      
      animation.dist       = distance[x][y];
      animation.angle      = 5 * polar_theta[x][y] + 5*move.noise_angle[0] + animation.dist * 0.1;
      animation.z          = 5;
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
      animation.offset_z   = 50 * move.linear[0];
      animation.offset_x   = 50 * move.noise_angle[0];
      animation.offset_y   = 50 * move.noise_angle[1];
      float show1          = render_value(animation);

      animation.angle      =6 * polar_theta[x][y] + 5*move.noise_angle[1] + animation.dist * 0.15;
      animation.z          = 5;
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
      animation.offset_z   = 50 * move.linear[1];
      animation.offset_x   = 50 * move.noise_angle[1];
      animation.offset_y   = 50 * move.noise_angle[2];
      float show2          = render_value(animation);

      animation.angle      = 5;
      animation.z          = 5;
      animation.scale_x    = 0.10;
      animation.scale_y    = 0.10;
      animation.offset_z   = 10 * move.linear[2];
      animation.offset_x   = 10 * move.noise_angle[2];
      animation.offset_y   = 10 * move.noise_angle[3];
      float show3          = render_value(animation);

      animation.angle      = 15;
      animation.z          = 15;
      animation.scale_x    = 0.10;
      animation.scale_y    = 0.10;
      animation.offset_z   = 10 * move.linear[3];
      animation.offset_x   = 10 * move.noise_angle[3];
      animation.offset_y   = 10 * move.noise_angle[4];
      float show4          = render_value(animation);

      animation.angle      = 2;
      animation.z          = 15;
      animation.scale_x    = 0.15;
      animation.scale_y    = 0.15;
      animation.offset_z   = 10 * move.linear[4];
      animation.offset_x   = 10 * move.noise_angle[4];
      animation.offset_y   = 10 * move.noise_angle[5];
      float show5          = render_value(animation);

      
      pixel.red    = show1-show4;
      pixel.green  = show2-show5;
      pixel.blue   = show3-show2+show1;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  //show_frame();
}

void SM1() { // nice one

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.02;    // master speed

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.0031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x/2; x++) {
    for (int y = 0; y < num_y/2; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + 5*move.noise_angle[0];
      animation.z          = 5;
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.offset_z   = 50 * move.linear[0];
      animation.offset_x   = 150 * move.directional[0];
      animation.offset_y   = 150 * move.directional[1];
      float show1          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + 4*move.noise_angle[1];
      animation.z          = 15;
      animation.scale_x    = 0.15;
      animation.scale_y    = 0.15;
      animation.offset_z   = 50 * move.linear[1];
      animation.offset_x   = 150 * move.directional[1];
      animation.offset_y   = 150 * move.directional[2];
      float show2          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + 5*move.noise_angle[2];
      animation.z          = 25;
      animation.scale_x    = 0.1;
      animation.scale_y    = 0.1;
      animation.offset_z   = 50 * move.linear[2];
      animation.offset_x   = 150 * move.directional[2];
      animation.offset_y   = 150 * move.directional[3];
      float show3          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + 5*move.noise_angle[3];
      animation.z          = 35;
      animation.scale_x    = 0.15;
      animation.scale_y    = 0.15;
      animation.offset_z   = 50 * move.linear[3];
      animation.offset_x   = 150 * move.directional[3];
      animation.offset_y   = 150 * move.directional[4];
      float show4          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + 5*move.noise_angle[4];
      animation.z          = 45;
      animation.scale_x    = 0.2;
      animation.scale_y    = 0.2;
      animation.offset_z   = 50 * move.linear[4];
      animation.offset_x   = 150 * move.directional[4];
      animation.offset_y   = 150 * move.directional[5];
      float show5          = render_value(animation);

     

      pixel.red    = show1+show2;
      pixel.green  = show3+show4;
      pixel.blue   = show5;
     
      pixel = rgb_sanity_check(pixel);
      //leds[xy(x, y)] = CRGB(pixel.red, pixel.green, pixel.blue);
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));

      buffer[xy(31-x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
      buffer[xy(31-x, 31-y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
      buffer[xy(x, 31-y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  //show_frame();
}

void SM2() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.03;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] * (move.directional[0]);
      animation.angle      = polar_theta[x][y] + move.radial[0];
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 5 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show1          = render_value(animation);

      animation.dist       = distance[x][y]* move.directional[1];
      animation.angle      = polar_theta[x][y] + move.radial[1];
      animation.z          = 50;
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.offset_z   = 5 * move.linear[1];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show2          = render_value(animation);
      
      animation.dist       = distance[x][y]* move.directional[2];
      animation.angle      = polar_theta[x][y] + move.radial[2];
      animation.z          = 500;
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
      animation.offset_z   = 5 * move.linear[2];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show3          = render_value(animation);
     
     

      pixel.red    = show1;
      pixel.green  = show2;
      pixel.blue   = show3;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));

      
    }
  }
 //show_frame();
}

void SM3() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.02;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.offset_y   = -20 * move.linear[0];;
      animation.low_limit  = -1;
      animation.high_limit = 1;
      show1          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 500;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.offset_y   = -20 * move.linear[0];;
      animation.low_limit  = -1;
      animation.high_limit = 1;
      show2          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 50;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 0;
      animation.offset_x   = 500+show1/20;
      animation.offset_y   = -4 * move.linear[0] + show2/20;
      animation.low_limit  = 0;
      animation.high_limit = 1;
      show3          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 50;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 0;
      animation.offset_x   = 500+show1/18;
      animation.offset_y   = -4 * move.linear[0] + show2/18;
      animation.low_limit  = 0;
      animation.high_limit = 1;
      show4          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 50;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 0;
      animation.offset_x   = 500+show1/19;
      animation.offset_y   = -4 * move.linear[0] + show2/19;
      animation.low_limit  = 0.3;
      animation.high_limit = 1;
      show5          = render_value(animation);

      pixel.red    = show4;
      pixel.green  = show3;
      pixel.blue   = show5;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));

    }
  }
 
}

void SM4() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.02;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0036;
  timings.ratio[5] = 0.0039;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.offset_y   = -20 * move.linear[0];;
      animation.low_limit  = 0;
      animation.high_limit = 1;
      show1          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 500;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.offset_y   = -40 * move.linear[0];;
      animation.low_limit  = 0;
      animation.high_limit = 1;
      show2          = render_value(animation);

      pixel.red    = add(show2, show1);
      pixel.green  = 0;
      pixel.blue   = colordodge(show2, show1);
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));

    }
  }
 
}

void SM5() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.03;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0053;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0056;
  timings.ratio[5] = 0.0059;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = distance[x][y] * (move.directional[0]);
      animation.angle      = polar_theta[x][y] + move.radial[0];
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 5 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show1          = render_value(animation);

      animation.dist       = distance[x][y]* move.directional[1];
      animation.angle      = polar_theta[x][y] + move.radial[1];
      animation.z          = 50;
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.offset_z   = 5 * move.linear[1];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show2          = render_value(animation);
      
      animation.dist       = distance[x][y]* move.directional[2];
      animation.angle      = polar_theta[x][y] + move.radial[2];
      animation.z          = 500;
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
      animation.offset_z   = 5 * move.linear[2];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show3          = render_value(animation);

      animation.dist       = distance[x][y] * (move.directional[3]);
      animation.angle      = polar_theta[x][y] + move.radial[3];
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 5 * move.linear[3];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show4          = render_value(animation);

      animation.dist       = distance[x][y]* move.directional[4];
      animation.angle      = polar_theta[x][y] + move.radial[4];
      animation.z          = 50;
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.offset_z   = 5 * move.linear[4];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show5          = render_value(animation);
      
      animation.dist       = distance[x][y]* move.directional[5];
      animation.angle      = polar_theta[x][y] + move.radial[5];
      animation.z          = 500;
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
      animation.offset_z   = 5 * move.linear[5];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show6          = render_value(animation);

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];
     
      pixel.red    = radial * add(show1,show4);
      pixel.green  = radial * colordodge(show2,show5);
      pixel.blue   = radial * screen(show3,show6);
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}


void SM6() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.03;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0053;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0056;
  timings.ratio[5] = 0.0059;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 0.7; // zoom factor
      
      animation.dist       = distance[x][y] * (move.directional[0]) * s;
      animation.angle      = polar_theta[x][y] + move.radial[0];
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 5 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show1          = render_value(animation);

      animation.dist       = distance[x][y]* move.directional[1] * s;
      animation.angle      = polar_theta[x][y] + move.radial[1];
      animation.z          = 50;
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.offset_z   = 5 * move.linear[1];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show2          = render_value(animation);
      
      animation.dist       = distance[x][y]* move.directional[2] * s;
      animation.angle      = polar_theta[x][y] + move.radial[2];
      animation.z          = 500;
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
      animation.offset_z   = 5 * move.linear[2];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show3          = render_value(animation);

      animation.dist       = distance[x][y] * (move.directional[3]) * s;
      animation.angle      = polar_theta[x][y] + move.radial[3];
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 5 * move.linear[3];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show4          = render_value(animation);

      animation.dist       = distance[x][y]* move.directional[4] * s;
      animation.angle      = polar_theta[x][y] + move.radial[4];
      animation.z          = 50;
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.offset_z   = 5 * move.linear[4];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show5          = render_value(animation);
      
      animation.dist       = distance[x][y]* move.directional[5] * s;
      animation.angle      = polar_theta[x][y] + move.radial[5];
      animation.z          = 500;
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
      animation.offset_z   = 5 * move.linear[5];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      float show6          = render_value(animation);

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      show7 = screen(show1, show4);
      show8 = colordodge(show2, show5);
      show9 = screen(show3, show6);
     
      pixel.red    = radial * (show7 + show8);
      pixel.green  = 0;
      pixel.blue   = radial * show9;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}


void SM8() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.06;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0053;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0056;
  timings.ratio[5] = 0.01;    // original Reddit post had no radial movement!
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      //float s = 0.7; // zoom factor
      
      animation.dist       = distance[x][y];
      animation.angle      = 2;
      animation.z          = 5;
      animation.scale_x    = 0.15;
      animation.scale_y    = 0.15;
      animation.offset_z   = 0;
      animation.offset_y   = 50 * move.linear[0];
      animation.offset_x   = 0;
      animation.low_limit  = 0;
      float show1          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = 2;
      animation.z          = 150;
      animation.offset_x   = -50 * move.linear[0];     
      float show2          = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = 1;
      animation.z          = 550;
      animation.scale_x    = 0.15;
      animation.scale_y    = 0.15;
      animation.offset_x   = 0;
      animation.offset_y   = -50 * move.linear[1];
      float show4          = render_value(animation);      

      animation.dist       = distance[x][y];
      animation.angle      = 1;
      animation.z          = 1250;
      animation.scale_x    = 0.15;
      animation.scale_y    = 0.15;
      animation.offset_x   = 0;
      animation.offset_y   = 50 * move.linear[1];
      float show5          = render_value(animation);      
      
     

      //float radius = radial_filter_radius;   // radius of a radial brightness filter
      //float radial = (radius-distance[x][y])/distance[x][y];

      show3 = add(show1, show2);
      show6 = screen(show4, show5);
      //show9 = screen(show3, show6);
     
      pixel.red    = show3;
      pixel.green  = 0;
      pixel.blue   = show6;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}


void SM9() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.005;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0053;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0056;
  timings.ratio[5] = 0.0059;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_y   = -30 * move.linear[0];
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.low_limit  = -1;
      show1                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 50;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_y   = -30 * move.linear[1];
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.low_limit  = -1;
      show2                = render_value(animation);

      animation.dist       = distance[x][y];// + show1/64;
      animation.angle      = polar_theta[x][y] + 2 + (show1 / 255) * PI;
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_y   = -10 * move.linear[0];
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + 2 +(show2 / 255) * PI;;
      animation.z          = 5;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_y   = -20 * move.linear[0];
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.low_limit  = 0;
      show4                = render_value(animation);

      show5 = screen(show4, show3);
      show6 = colordodge(show5, show3);

      float linear1 = y / 32.f;
      float linear2 = (32-y) / 32.f;

      pixel.red    = show5 * linear1;
      pixel.green  = 0;
      pixel.blue   = show6 * linear2;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void SM10() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.006;    // 0.006

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0053;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0056;
  timings.ratio[5] = 0.0059;
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float scale = 0.6;
      
      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.09 * scale;
      animation.scale_y    = 0.09 * scale;
      animation.offset_y   = -30 * move.linear[0];
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.low_limit  = -1;
      show1                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y];
      animation.z          = 50;
      animation.scale_x    = 0.09 * scale;
      animation.scale_y    = 0.09 * scale;
      animation.offset_y   = -30 * move.linear[1];
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.low_limit  = -1;
      show2                = render_value(animation);

      animation.dist       = distance[x][y];// + show1/64;
      animation.angle      = polar_theta[x][y] + 2 + (show1 / 255) * PI;
      animation.z          = 5;
      animation.scale_x    = 0.09 * scale;
      animation.scale_y    = 0.09 * scale;
      animation.offset_y   = -10 * move.linear[0];
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + 2 +(show2 / 255) * PI;;
      animation.z          = 5;
      animation.scale_x    = 0.09 * scale;
      animation.scale_y    = 0.09 * scale;
      animation.offset_y   = -20 * move.linear[0];
      animation.offset_z   = 0;
      animation.offset_x   = 0;
      animation.low_limit  = 0;
      show4                = render_value(animation);

      show5 = screen(show4, show3);
      show6 = colordodge(show5, show3);

      //float linear1 = y / 32.f;
      //float linear2 = (32-y) / 32.f;

      pixel.red    = (show5+show6)/2;
      pixel.green  = (show5-50)+(show6/16);
      pixel.blue   = 0;//show6;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Complex_Kaleido() { 



  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.009;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0053;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0056;
  timings.ratio[5] = 0.0059;
  
  calculate_oscillators(timings); 

  //float size = 1.5;

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y];
      animation.angle      = 5 * polar_theta[x][y] + 10 * move.radial[0] + animation.dist /2;
      animation.z          = 5;
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.offset_z   = 0;
      animation.offset_x   = -30 * move.linear[0];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = -5 * polar_theta[x][y] + 12 * move.radial[1] + animation.dist /2;
      animation.z          = 500;
      animation.scale_x    = 0.07;
      animation.scale_y    = 0.07;
      animation.offset_z   = 0;
      animation.offset_x   = -30 * move.linear[1];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = -5 * polar_theta[x][y] + 12 * move.radial[2] + animation.dist /2;
      animation.z          = 500;
      animation.scale_x    = 0.05;
      animation.scale_y    = 0.05;
      animation.offset_z   = 0;
      animation.offset_x   = -40 * move.linear[2];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      
      animation.dist       = distance[x][y];
      animation.angle      = 5 * polar_theta[x][y] + 12 * move.radial[3] + animation.dist /2;
      animation.z          = 500;
      animation.scale_x    = 0.09;
      animation.scale_y    = 0.09;
      animation.offset_z   = 0;
      animation.offset_x   = -35 * move.linear[3];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show4                = render_value(animation);

      show5 = screen(show4, show3);
      show6 = colordodge(show2, show3);

      //float linear1 = y / 32.f;
      //float linear2 = (32-y) / 32.f;

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial*(show1+show2);
      pixel.green  = 0.3*radial*show6;//(radial*(show1))*0.3f;
      pixel.blue   = radial*show5;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Complex_Kaleido_2() { 



  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.009;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.0053;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.0056;
  timings.ratio[5] = 0.0059;
  
  calculate_oscillators(timings); 

  float size = 0.5;

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y];
      animation.angle      = 5 * polar_theta[x][y] + 10 * move.radial[0] + animation.dist /2;
      animation.z          = 5;
      animation.scale_x    = 0.07 * size;
      animation.scale_y    = 0.07 * size;
      animation.offset_z   = 0;
      animation.offset_x   = -30 * move.linear[0];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = -5 * polar_theta[x][y] + 12 * move.radial[1] + animation.dist /2;
      animation.z          = 500;
      animation.scale_x    = 0.07 * size;
      animation.scale_y    = 0.07 * size;
      animation.offset_z   = 0;
      animation.offset_x   = -30 * move.linear[1];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = -5 * polar_theta[x][y] + 12 * move.radial[2] + animation.dist /2;
      animation.z          = 500;
      animation.scale_x    = 0.05 * size;
      animation.scale_y    = 0.05 * size;
      animation.offset_z   = 0;
      animation.offset_x   = -40 * move.linear[2];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      
      animation.dist       = distance[x][y];
      animation.angle      = 5 * polar_theta[x][y] + 12 * move.radial[3] + animation.dist /2;
      animation.z          = 500;
      animation.scale_x    = 0.09 * size;
      animation.scale_y    = 0.09 * size;
      animation.offset_z   = 0;
      animation.offset_x   = -35 * move.linear[3];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show4                = render_value(animation);

      show5 = screen(show4, show3);
      show6 = colordodge(show2, show3);

      //float linear1 = y / 32.f;
      //float linear2 = (32-y) / 32.f;

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      pixel.red    = radial*(show1+show2);
      pixel.green  = 0.3*radial*show6;//(radial*(show1))*0.3f;
      pixel.blue   = radial*show5;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}


void Complex_Kaleido_3() { 



  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.001;    // master speed

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.037;
  timings.ratio[5] = 0.038;
  timings.ratio[5] = 0.041;
  
  calculate_oscillators(timings); 

  float size = 0.4 + move.directional[0]*0.1;

  float q = 2;

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y];
      animation.angle      = 5 * polar_theta[x][y] + 10 * move.radial[0] + animation.dist / (((move.directional[0] + 3)*2)) + move.noise_angle[0]*q;
      animation.z          = 5;
      animation.scale_x    = 0.08 * size * (move.directional[0]+1.5);
      animation.scale_y    = 0.07 * size;
      animation.offset_z   = -10 * move.linear[0];
      animation.offset_x   = -30 * move.linear[0];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = -5 * polar_theta[x][y] + 10 * move.radial[1] + animation.dist / (((move.directional[1] + 3)*2))+ move.noise_angle[1]*q;
      animation.z          = 500;
      animation.scale_x    = 0.07 * size * (move.directional[1]+1.1);
      animation.scale_y    = 0.07 * size * (move.directional[2]+1.3);;
      animation.offset_z   = -12 * move.linear[1];;
      animation.offset_x   = -31 * move.linear[1];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = -5 * polar_theta[x][y] + 12 * move.radial[2] + animation.dist /(((move.directional[3] + 3)*2))+ move.noise_angle[2]*q;
      animation.z          = 500;
      animation.scale_x    = 0.05 * size * (move.directional[3]+1.5);;
      animation.scale_y    = 0.05 * size * (move.directional[4]+1.5);;
      animation.offset_z   = -12 * move.linear[3];
      animation.offset_x   = -40 * move.linear[3];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      
      animation.dist       = distance[x][y];
      animation.angle      = 5 * polar_theta[x][y] + 12 * move.radial[3] + animation.dist /(((move.directional[5] + 3)*2))+ move.noise_angle[3]*q;
      animation.z          = 500;
      animation.scale_x    = 0.09 * size * (move.directional[5]+1.5);;;
      animation.scale_y    = 0.09 * size * (move.directional[6]+1.5);;;
      animation.offset_z   = 0;
      animation.offset_x   = -35 * move.linear[3];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show4                = render_value(animation);

      show5 = screen(show4, show3)-show2;
      show6 = colordodge(show4, show1);

      show7 = multiply(show1, show2);

      float linear1 = y / 32.f;
      //float linear2 = (32-y) / 32.f;

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];

      show7 = multiply(show1, show2) * linear1*2;
      show8 = subtract(show7, show5);

      //pixel.red    = radial*(show1+show2);
      pixel.green  = 0.2*show8;//(radial*(show1))*0.3f;
      pixel.blue   = show5 * radial;
      pixel.red    = (1*show1 + 1*show2) - show7/2;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Complex_Kaleido_4() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.01;    // master speed 0.01 in the video

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.037;
  timings.ratio[5] = 0.038;
  timings.ratio[6] = 0.041;
  
  calculate_oscillators(timings); 

  float size = 0.6;

  float q = 1;

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 1 +  move.directional[6]*0.3;

      animation.dist       = distance[x][y] * s;
      animation.angle      = 5 * polar_theta[x][y] + 1 * move.radial[0] - animation.dist / (3+move.directional[0]*0.5);
      animation.z          = 5;
      animation.scale_x    = 0.08 * size + (move.directional[0]*0.01);
      animation.scale_y    = 0.07 * size + (move.directional[1]*0.01);
      animation.offset_z   = -10 * move.linear[0];
      animation.offset_x   = 0;//-30 * move.linear[0];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = distance[x][y] * s;
      animation.angle      = 5 * polar_theta[x][y] + 1 * move.radial[1] + animation.dist / (3+move.directional[1]*0.5);
      animation.z          = 50;
      animation.scale_x    = 0.08 * size + (move.directional[1]*0.01);
      animation.scale_y    = 0.07 * size + (move.directional[2]*0.01);
      animation.offset_z   = -10 * move.linear[1];
      animation.offset_x   = 0;//-30 * move.linear[0];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = 1;
      animation.z          = 500;
      animation.scale_x    = 0.2 * size ;
      animation.scale_y    = 0.2 * size ;
      animation.offset_z   = 0;//-12 * move.linear[3];
      animation.offset_y   = +7 * move.linear[3] +  move.noise_angle[3];
      animation.offset_x   = 0;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      
      animation.dist       = distance[x][y];
      animation.angle      = 5 * polar_theta[x][y] + 12 * move.radial[3] + animation.dist /(((move.directional[5] + 3)*2))+ move.noise_angle[3]*q;
      animation.z          = 500;
      animation.scale_x    = 0.09 * size * (move.directional[5]+1.5);;;
      animation.scale_y    = 0.09 * size * (move.directional[6]+1.5);;;
      animation.offset_z   = 0;
      animation.offset_x   = -35 * move.linear[3];
      animation.offset_y   = 0;
      animation.low_limit  = 0;
      show4                = render_value(animation);

      //show5 = screen(show4, show3)-show2;
      //show6 = colordodge(show4, show1);

      //show7 = multiply(show1, show2);
      /*
      float linear1 = y / 32.f;
      float linear2 = (32-y) / 32.f;
      */

      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];
      /*
      show7 = multiply(show1, show2) * linear1*2;
      show8 = subtract(show7, show5);
      */

      show5 = ((show1 + show2)) - show3;
      if (show5>255) show5=255;
      if (show5<0) show5=0;

      show6 = colordodge(show1, show2);

      pixel.red    = show5 * radial;
      pixel.blue   = (64-show5-show3) * radial;
      pixel.green  = 0.5*(show6);
      //pixel.blue   = show5 * radial;
      //pixel.red    = (1*show1 + 1*show2) - show7/2;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Complex_Kaleido_5() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.01;    // master speed 

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.037;
  timings.ratio[5] = 0.0038;
  timings.ratio[6] = 0.041;
  
  calculate_oscillators(timings); 

  float size = 0.6;

  //float q = 1;

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 1 +  move.directional[6]*0.8;

      animation.dist       = distance[x][y] * s;
      animation.angle      = 10*move.radial[6] + 50 * move.directional[5] * polar_theta[x][y]  - animation.dist / 3;
      animation.z          = 5;
      animation.scale_x    = 0.08 * size ;
      animation.scale_y    = 0.07 * size ;
      animation.offset_z   = -10 * move.linear[0];
      animation.offset_x   = 0;
      animation.offset_y   = 0;
      animation.low_limit  = -0.5;
      show1                = render_value(animation);

     
      float radius = radial_filter_radius;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/distance[x][y];
     
      pixel.red    = show1 * radial;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Complex_Kaleido_6() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.01;    // master speed 

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.037;
  timings.ratio[5] = 0.0038;
  timings.ratio[6] = 0.041;
  
  calculate_oscillators(timings); 

  

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y];
      animation.angle      = 16 * polar_theta[x][y] + 16*move.radial[0];
      animation.z          = 5;
      animation.scale_x    = 0.06 ;
      animation.scale_y    = 0.06 ;
      animation.offset_z   = -10 * move.linear[0];
      animation.offset_y   = 10 * move.noise_angle[0];
      animation.offset_x   = 10 * move.noise_angle[4];
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = distance[x][y];
      animation.angle      = 16 * polar_theta[x][y] + 16*move.radial[1];
      animation.z          = 500;
      animation.scale_x    = 0.06 ;
      animation.scale_y    = 0.06 ;
      animation.offset_z   = -10 * move.linear[1];
      animation.offset_y   = 10 * move.noise_angle[1];
      animation.offset_x   = 10 * move.noise_angle[3];
      animation.low_limit  = 0;
      show2                = render_value(animation);

     
      //float radius = radial_filter_radius;   // radius of a radial brightness filter
      //float radial = (radius-distance[x][y])/distance[x][y];
     
      pixel.red    = show1;
      pixel.blue   = show2;
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Water() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.037;    // master speed 

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.031;
  timings.ratio[3] = 0.033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.037;
  timings.ratio[5] = 0.1;
  timings.ratio[6] = 0.41;
  
  calculate_oscillators(timings); 


  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y] + 4*sinf(move.directional[5]*PI+(float)x/2) + 4 * cosf(move.directional[6]*PI+float(y)/2);
      animation.angle      = 1 * polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.06 ;
      animation.scale_y    = 0.06 ;
      animation.offset_z   = -10 * move.linear[0];
      animation.offset_y   = 10;
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = (10+move.directional[0]) * sinf(-move.radial[5]+move.radial[0]+(distance[x][y] / (3)));
      animation.angle      = 1 * polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[0];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = (10+move.directional[1]) * sinf(-move.radial[5]+move.radial[1]+(distance[x][y] / (3)));
      animation.angle      = 1 * polar_theta[x][y];
      animation.z          = 500;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[1];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      animation.dist       = (10+move.directional[2]) * sinf(-move.radial[5]+move.radial[2]+(distance[x][y] / (3)));
      animation.angle      = 1 * polar_theta[x][y];
      animation.z          = 500;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[2];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show4                = render_value(animation);


      
     
      //float radius = radial_filter_radius;   // radius of a radial brightness filter
      //float radial = (radius-distance[x][y])/distance[x][y];
     
      //pixel.red    = show2;
      
      pixel.blue    = (0.7*show2+0.6*show3+0.5*show4);
      pixel.red     = pixel.blue-40;
      //pixel.red     = radial*show3;
      //pixel.green     = 0.9*radial*show4;
      
     
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Parametric_Water() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.003;    // master speed 

  timings.ratio[0] = 0.025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.027;
  timings.ratio[2] = 0.029;
  timings.ratio[3] = 0.033;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[4] = 0.037;
  timings.ratio[5] = 0.15;    // wave speed
  timings.ratio[6] = 0.41;
  
  calculate_oscillators(timings); 


  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 4;
      float f = 10 + 2* move.directional[0];

      animation.dist       = (f+move.directional[0]) * sinf(-move.radial[5]+move.radial[0]+(distance[x][y] / (s)));
      animation.angle      = 1 * polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[0];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = (f+move.directional[1]) * sinf(-move.radial[5]+move.radial[1]+(distance[x][y] / (s)));
      animation.angle      = 1 * polar_theta[x][y];
      animation.z          = 500;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[1];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      animation.dist       = (f+move.directional[2]) * sinf(-move.radial[5]+move.radial[2]+(distance[x][y] / (s)));
      animation.angle      = 1 * polar_theta[x][y];
      animation.z          = 5000;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[2];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show4                = render_value(animation);

      animation.dist       = (f+move.directional[3]) * sinf(-move.radial[5]+move.radial[3]+(distance[x][y] / (s)));
      animation.angle      = 1 * polar_theta[x][y];
      animation.z          = 2000;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[3];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show5                = render_value(animation);

      show6 = screen(show4, show5);
      show7 = screen(show2, show3);


      
     
      float radius = 40;   // radius of a radial brightness filter
      float radial = (radius-distance[x][y])/radius;
     
      //pixel.red    = show6;
      //pixel.blue = show7;
      
      pixel.blue    = (0.3*show6+0.7*show7)*radial;
      pixel.red     = pixel.blue-40;
      
      
     
     
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Module_Experiment1() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.03;    // master speed 

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.029;
  timings.ratio[3] = 0.033;           // speed ratios for the oscillators, higher values = faster transitions
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y] + 20 * move.directional[0];
      animation.angle      = move.noise_angle[0] + move.noise_angle[1] + polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[2];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      pixel.blue    = show1;
      
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Module_Experiment2() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.02;    // master speed 

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.029;
  timings.ratio[3] = 0.033;           // speed ratios for the oscillators, higher values = faster transitions
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y] - ( 16 + move.directional[0] * 16);
      animation.angle      = move.noise_angle[0] + move.noise_angle[1] + polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[2];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);
      
      pixel.red    = show1;
      pixel.green  = show1 - 80;
      pixel.blue   = show1 - 150;
      
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Module_Experiment3() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.01;    // master speed 

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.029;
  timings.ratio[3] = 0.033;           // speed ratios for the oscillators, higher values = faster transitions
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y] - (12 + move.directional[3]*4);
      animation.angle      = move.noise_angle[0] + move.noise_angle[1] + polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.1 ;
      animation.scale_y    = 0.1 ;
      animation.offset_z   = -10 ;
      animation.offset_y   = 20 * move.linear[2];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);
      
      pixel.red    = show1;
      pixel.green  = show1 - 80;
      pixel.blue   = show1 - 150;
      
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Zoom2() { // nice one
  
  get_ready(); // for time measurement in report_performance()

  

  run_default_oscillators();
  timings.master_speed = 0.003;
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      
      animation.dist       = (distance[x][y] * distance[x][y])/2;
      animation.angle      = polar_theta[x][y];
      
      animation.scale_x    = 0.005;
      animation.scale_y    = 0.005;
      
      animation.offset_y   = -10*move.linear[0];
      animation.offset_x   = 0;
      animation.offset_z   = 0.1*move.linear[0];
      
      animation.z          = 0;
      animation.low_limit  = 0;
      float show1          = render_value(animation);

  
      //float linear = 1;//(y+1)/(num_y-1.f);
      
      pixel.red   = show1;
      pixel.blue   = 40-show1;
      
      
      pixel = rgb_sanity_check(pixel);
      buffer[kMatrixWidth * y + x] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
  
}

void Module_Experiment4() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.031;    // master speed 

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.029;
  timings.ratio[3] = 0.033;
  timings.ratio[4] = 0.036;            // speed ratios for the oscillators, higher values = faster transitions
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 0.8;

      animation.dist       = (distance[x][y] * distance[x][y])*0.7;
      animation.angle      = polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.004 * s;
      animation.scale_y    = 0.003 * s;
      animation.offset_z   = 0.1*move.linear[2] ;
      animation.offset_y   = -20 * move.linear[2];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = (distance[x][y] * distance[x][y])*0.8;
      animation.angle      = polar_theta[x][y];
      animation.z          = 50;
      animation.scale_x    = 0.004 * s;
      animation.scale_y    = 0.003 * s;
      animation.offset_z   = 0.1*move.linear[3] ;
      animation.offset_y   = -20 * move.linear[3];
      animation.offset_x   = 100;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = (distance[x][y] * distance[x][y])*0.9;
      animation.angle      = polar_theta[x][y];
      animation.z          = 5000;
      animation.scale_x    = 0.004 * s;
      animation.scale_y    = 0.003 * s;
      animation.offset_z   = 0.1*move.linear[4] ;
      animation.offset_y   = -20 * move.linear[4];
      animation.offset_x   = 1000;
      animation.low_limit  = 0;
      show3                = render_value(animation);


      // overlapping color mapping
      /*
      float r = show1;
      float g = show2-show1;
      float b = show3-show1-show2;
      */      
      
      pixel.red    = show1-show2-show3;
      pixel.blue   = show2-show1-show3;
      pixel.green  = show3-show1-show2;
      //pixel.green  = b;
      //pixel.green  = show1 - 80;
      //pixel.blue   = show1 - 150;
      
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Module_Experiment5() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.031;    // master speed 

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.029;
  timings.ratio[3] = 0.33;
  timings.ratio[4] = 0.036;            // speed ratios for the oscillators, higher values = faster transitions
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 1.5;

      animation.dist       = distance[x][y] + sinf(0.5*distance[x][y]-move.radial[3]);
      animation.angle      = polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[0] ;
      animation.offset_y   = -20 * move.linear[0];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      
      
      pixel.red    = show1;
      
      
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Module_Experiment6() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.01;    // master speed 0.031

  float w = 0.7;

  timings.ratio[0] = 0.0025;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.0027;
  timings.ratio[2] = 0.029;
  timings.ratio[3] = 0.33*w;
  timings.ratio[4] = 0.36*w;            // speed ratios for the oscillators, higher values = faster transitions
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 0.8;

      animation.dist       = distance[x][y] + sinf(0.25*distance[x][y]-move.radial[3]);
      animation.angle      = polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[0] ;
      animation.offset_y   = -20 * move.linear[0];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = distance[x][y] + sinf(0.24*distance[x][y]-move.radial[4]);
      animation.angle      = polar_theta[x][y];
      animation.z          = 10;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[1] ;
      animation.offset_y   = -20 * move.linear[1];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      
      /*
      pixel.red    = show1;
      pixel.green  = show1 * 0.3;
      pixel.blue   = show2-show1;
      */

      pixel.red    = (show1 + show2);
      pixel.green  = ((show1 + show2)*0.6)-30;
      pixel.blue   = 0;
      
      
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Module_Experiment7() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.005;    // master speed 0.031

  float w = 0.3;

  timings.ratio[0] = 0.01;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.011;
  timings.ratio[2] = 0.029;
  timings.ratio[3] = 0.33*w;
  timings.ratio[4] = 0.36*w;            // speed ratios for the oscillators, higher values = faster transitions
  
  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 0.7;

      animation.dist       = 2+distance[x][y] + 2*sinf(0.25*distance[x][y]-move.radial[3]);
      animation.angle      = polar_theta[x][y];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 10*move.linear[0] ;
      animation.offset_y   = -20 * move.linear[0];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = 2+distance[x][y] + 2*sinf(0.24*distance[x][y]-move.radial[4]);
      animation.angle      = polar_theta[x][y];
      animation.z          = 10;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[1] ;
      animation.offset_y   = -20 * move.linear[1];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      
      /*
      pixel.red    = show1;
      pixel.green  = show1 * 0.3;
      pixel.blue   = show2-show1;
      */
      
      pixel.red    = (show1 + show2);
      pixel.green  = ((show1 + show2)*0.6)-50;
      pixel.blue   = 0;
      
      
      
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Module_Experiment8() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.01;    // master speed 0.031

  float w = 0.3;

  timings.ratio[0] = 0.01;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.011;
  timings.ratio[2] = 0.013;
  timings.ratio[3] = 0.33*w;
  timings.ratio[4] = 0.36*w;            // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[5] = 0.38*w; 
  timings.ratio[6] = 0.0003;  // master rotation

  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  

  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 0.4; // scale
      float r = 1.5; // scroll speed

      animation.dist       = 3+distance[x][y] + 3*sinf(0.25*distance[x][y]-move.radial[3]);
      animation.angle      = polar_theta[x][y] + move.noise_angle[0] + move.noise_angle[6];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 10*move.linear[0] ;
      animation.offset_y   = -5 * r * move.linear[0];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = 4+distance[x][y] + 4*sinf(0.24*distance[x][y]-move.radial[4]);
      animation.angle      = polar_theta[x][y] + move.noise_angle[1] + move.noise_angle[6];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[1] ;
      animation.offset_y   = -5 * r * move.linear[1];
      animation.offset_x   = 100;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = 5+distance[x][y] + 5*sinf(0.23*distance[x][y]-move.radial[5]);
      animation.angle      = polar_theta[x][y] + move.noise_angle[2] + move.noise_angle[6];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[2] ;
      animation.offset_y   = -5 * r * move.linear[2];
      animation.offset_x   = 1000;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      show4 = colordodge(show1, show2);

      float rad = sinf(PI/2+distance[x][y]/14); // better radial filter?!

      
      /*
      pixel.red    = show1;
      pixel.green  = show1 * 0.3;
      pixel.blue   = show2-show1;
      */
      
      pixel.red    = rad * ((show1 + show2) + show3);
      pixel.green  = (((show2 + show3)*0.8)-90)*rad;
      pixel.blue   = show4 * 0.2;
      
      
      
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Module_Experiment9() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.03;    // master speed 0.031

  float w = 0.3;

  timings.ratio[0] = 0.1;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.011;
  timings.ratio[2] = 0.013;
  timings.ratio[3] = 0.33*w;
  timings.ratio[4] = 0.36*w;            // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[5] = 0.38*w; 
  timings.ratio[6] = 0.0003;  

  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      animation.dist       = distance[x][y];
      animation.angle      = polar_theta[x][y] + move.radial[1];
      animation.z          = 5;
      animation.scale_x    = 0.001;
      animation.scale_y    = 0.1;
      animation.scale_z    = 0.1;
      animation.offset_y   = -10*move.linear[0];
      animation.offset_x   = 20;
      animation.offset_z   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      pixel.red    = 10*show1;
    
      pixel = rgb_sanity_check(pixel);
      
      buffer[xy(x, y)] = (rgb24)CRGB(CRGB(pixel.red, pixel.green, pixel.blue));
    }
  }
}

void Module_Experiment10() { 

  get_ready(); // for time measurement in report_performance()

  

  timings.master_speed = 0.01;    // master speed 0.031

  float w = 1;

  timings.ratio[0] = 0.01;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 0.011;
  timings.ratio[2] = 0.013;
  timings.ratio[3] = 0.33*w;
  timings.ratio[4] = 0.36*w;            // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[5] = 0.38*w; 
  timings.ratio[6] = 0.0003;  // master rotation

  timings.offset[0] = 0;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  

  calculate_oscillators(timings); 

  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {

      float s = 0.4; // scale
      float r = 1.5; // scroll speed

      animation.dist       = 3+distance[x][y] + 3*sinf(0.25*distance[x][y]-move.radial[3]);
      animation.angle      = polar_theta[x][y] + move.noise_angle[0] + move.noise_angle[6];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 10*move.linear[0] ;
      animation.offset_y   = -5 * r * move.linear[0];
      animation.offset_x   = 10;
      animation.low_limit  = 0;
      show1                = render_value(animation);

      animation.dist       = 4+distance[x][y] + 4*sinf(0.24*distance[x][y]-move.radial[4]);
      animation.angle      = polar_theta[x][y] + move.noise_angle[1] + move.noise_angle[6];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[1] ;
      animation.offset_y   = -5 * r * move.linear[1];
      animation.offset_x   = 100;
      animation.low_limit  = 0;
      show2                = render_value(animation);

      animation.dist       = 5+distance[x][y] + 5*sinf(0.23*distance[x][y]-move.radial[5]);
      animation.angle      = polar_theta[x][y] + move.noise_angle[2] + move.noise_angle[6];
      animation.z          = 5;
      animation.scale_x    = 0.1 * s;
      animation.scale_y    = 0.1 * s;
      animation.offset_z   = 0.1*move.linear[2] ;
      animation.offset_y   = -5 * r * move.linear[2];
      animation.offset_x   = 1000;
      animation.low_limit  = 0;
      show3                = render_value(animation);

      show4 = colordodge(show1, show2);

      float rad = sinf(PI/2+distance[x][y]/14); // better radial filter?!

      
      /*
      pixel.red    = show1;
      pixel.green  = show1 * 0.3;
      pixel.blue   = show2-show1;
      */
      
       CHSV(rad * ((show1 + show2) + show3), 255, 255);
      
      
      
      
      pixel = rgb_sanity_check(pixel);

      byte a = millis()/100;
      
      buffer[xy(x, y)] = (rgb24)CRGB( CHSV(((a + show1 + show2) + show3), 255, 255));
    }
  }
}


void calculate_oscillators(oscillators &timings) { 

  double runtime = millis() * timings.master_speed;  // global anaimation speed

  for (int i = 0; i < num_oscillators; i++) {
    
    move.linear[i]      = (runtime + timings.offset[i]) * timings.ratio[i];     // continously rising offsets, returns              0 to max_float
    
    move.radial[i]      = fmodf(move.linear[i], 2 * PI);                        // angle offsets for continous rotation, returns    0 to 2 * PI
    
    move.directional[i] = sinf(move.radial[i]);                                 // directional offsets or factors, returns         -1 to 1
    
    move.noise_angle[i] = PI * (1 + pnoise(move.linear[i], 0, 0));              // noise based angle offset, returns                0 to 2 * PI
    
  }
}


void run_default_oscillators(){

  timings.master_speed = 0.005;    // master speed

  timings.ratio[0] = 1;           // speed ratios for the oscillators, higher values = faster transitions
  timings.ratio[1] = 2;
  timings.ratio[2] = 3;
  timings.ratio[3] = 4;
  timings.ratio[4] = 5;
  timings.ratio[5] = 6;
  timings.ratio[6] = 7;
  timings.ratio[7] = 8;
  timings.ratio[8] = 9;
  timings.ratio[9] = 10;

  
  timings.offset[0] = 000;
  timings.offset[1] = 100;
  timings.offset[2] = 200;
  timings.offset[3] = 300;
  timings.offset[4] = 400;
  timings.offset[5] = 500;
  timings.offset[6] = 600;
  timings.offset[7] = 700;
  timings.offset[8] = 800;
  timings.offset[9] = 900;

  calculate_oscillators(timings);  
}





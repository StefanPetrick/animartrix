
void calculate_oscillators(oscillators &timings) {

  double runtime = millis() * timings.master_speed;  // global anaimation speed

  for (int i = 0; i < num_oscillators; i++) {
    
    move.linear[i]      = (runtime + timings.offset[i]) * timings.ratio[i];     // continously rising offsets, returns              0 to max_float
    
    move.radial[i]      = fmodf(move.linear[i], 2 * PI);                        // angle offsets for continous rotation, returns    0 to 2 * PI
    
    move.directional[i] = sinf(move.radial[i]);                                 // directional offsets or factors, returns         -1 to 1
    
    move.noise_angle[i] = PI * (1 + pnoise(move.linear[i], 0, 0));              // noise based angle offset, returns                0 to 2 * PI
    
  }
}



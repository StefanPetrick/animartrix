/*

Blend Mode ideas:

dynamic darken

Subtraction  a-b
Multiply     a * b/255
Color burn   255-((255-a)/b)

dynamic lighten

add          a+b
screen.      255-(255-a)(255-b)
color dodge. a/(255-b)


static darkening filter

linear_filter(height)    *y/(num_y-1)

radial_filter(radius)    dist/radius


to do:

fix move.linear / angular ratio, range & speed 
set up one call standard oscillators
set up one call "blank" template for shorter animation code
set up write_pixel(show1, show2, show3);

*/

void run_default_oscillators(){

  timings.master_speed = 0.01;    // master speed

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








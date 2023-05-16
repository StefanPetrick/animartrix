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

formating readme

idle light routine (>=min brightnes)

*/









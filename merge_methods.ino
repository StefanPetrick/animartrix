// Dynamic darkening methods:

float subtract(float &a, float&b) {

  return a - b;
}


float multiply(float &a, float&b) {

  return a * b / 255.f;
}


// makes low brightness darker
// sets the black point high = more contrast 
// animation.low_limit should be 0 for best results
float colorburn(float &a, float&b) {  

  return (1-((1-a/255.f) / (b/255.f)))*255.f;
}


// Dynamic brightening methods

float add(float &a, float&b) {

  return a + b;
}


// makes bright even brighter
// reduces contrast
float screen(float &a, float&b) {

  return (1 - (1 - a/255.f) * (1 - b/255.f))*255.f;
}


float colordodge(float &a, float&b) {  

  return (a/(255.f-b)) * 255.f;
}

void colorWipe() {
  int wait = arrayParameters[PAT_WIPE][0];
  uint32_t color = arrayParameters[PAT_WIPE][1];
  float bright = float(arrayParameters[PAT_WIPE][1]);
  int rainbow = arrayParameters[PAT_WIPE][2];
  int range = RAINBOW_RANGE;

  if(patternDelay != wait)
    patternDelay = wait;

  int colorStep = patternStep % range;
  int pixelStep = patternStep % pixelNumber;

  if(rainbow)
    color = ColorBright(Wheel((colorStep) % range), bright);
  strip.setPixelColor(pixelStep, color);

  strip.show();
  patternStep = (patternStep + 1) % (range * pixelNumber);
}

void light() {
  int wait = arrayParameters[PAT_LIGHT][0];
  uint32_t color = arrayParameters[PAT_LIGHT][1];
  float bright = float(arrayParameters[PAT_LIGHT][2]);

  if(patternDelay != wait)
    patternDelay = wait;
  for(int i = 0; i < pixelNumber; i++) {
    strip.setPixelColor(i, ColorBright(color, bright));
  }
  strip.show();
}

//void rainbow() {
//  int wait = arrayParameters[PAT_RAINBOW][0];
////  int range = arrayParameters[PAT_RAINBOW][1];
//  int bright = arrayParameters[PAT_RAINBOW][2];
//  
//  if(patternDelay != wait)
//    patternDelay = wait;
//  for(int i = 0; i < pixelNumber; i++) {
//    strip.setPixelColor(i, ColorBright(Wheel((i + patternStep) & 255), bright));
//  }
//  strip.show();
//  patternStep = (patternStep + 1) % 256;
//}

void colorFlat() {
  int wait = arrayParameters[PAT_FILL][0];
  uint32_t color = arrayParameters[PAT_FILL][1];
  float bright = float(arrayParameters[PAT_FILL][1]);
  int rainbow = arrayParameters[PAT_FILL][2];
  int range = RAINBOW_RANGE;
  
  if(patternDelay != wait)
    patternDelay = wait;
 
  for(int i = 0; i < pixelNumber; i++) {
    if(rainbow)
      color = ColorBright(Wheel((i + patternStep) % range), bright);
    strip.setPixelColor(i, color);
  }
  strip.show();
  patternStep = (patternStep + 1) % range;
}

void blink() {
  int wait = arrayParameters[PAT_BLINK][0];
  uint32_t color = arrayParameters[PAT_BLINK][1];
  float bright = float(arrayParameters[PAT_BLINK][1]);
  int lenght = arrayParameters[PAT_BLINK][2];
  int rainbow = arrayParameters[PAT_BLINK][3];
  int range = RAINBOW_RANGE;
  
  if(patternDelay != wait)
    patternDelay = wait;
    
  int patternCycle = range * lenght;
  int pixelCurrent = patternStep % lenght;
  int pixelNext = (pixelCurrent + 1 ) % lenght;
  int colorCurrent = patternStep % range;

  for(int i = 0; i < pixelNumber; i+=lenght) {
    strip.setPixelColor(i + pixelCurrent, strip.Color(0, 0, 0));
    if(rainbow)
      color = ColorBright(Wheel((i + colorCurrent) % range), bright);
    strip.setPixelColor(i + pixelNext, color);
  }
  strip.show();
  patternStep = (patternStep + 1) % patternCycle;
}

void police() {
  int wait = arrayParameters[PAT_POLICE][0];
  uint32_t color1 = arrayParameters[PAT_POLICE][1];
  uint32_t color2 = arrayParameters[PAT_POLICE][2];
    
  if(patternDelay != wait)
    patternDelay = wait;
  if(patternStep){
    for(int i = 0; i < pixelNumber; i+=2) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.setPixelColor(i + 1, color1);
    }
  } else {
    for(int i = 0; i < pixelNumber; i+=2) {
      strip.setPixelColor(i, color2 );
      strip.setPixelColor(i + 1, strip.Color(0, 0, 0));
    }
  }
  strip.show();
  patternStep = (patternStep + 1) % 2;
}

void snake() {
  int wait = arrayParameters[PAT_SNAKE][0];
  uint32_t color = arrayParameters[PAT_SNAKE][1];
  float bright = float(arrayParameters[PAT_SNAKE][1]);
  int number = arrayParameters[PAT_SNAKE][2];
  int lenght = arrayParameters[PAT_SNAKE][3];
  int rainbow = arrayParameters[PAT_SNAKE][4];
  int range = RAINBOW_RANGE;
    
  if(patternDelay != wait)
    patternDelay = wait;

  int segment = pixelNumber / number;
  float queue = 100.0 / float(lenght);
  
  for(int i = 0; i < pixelNumber; i+=segment) {
    strip.setPixelColor(i + patternStep % segment, strip.Color(0, 0, 0));
    for(int j = 1; j <= lenght; j++){
      if(rainbow){
        color = ColorBright(Wheel(((i + (j + patternStep) % segment) + patternStep) % range), bright);
      }
      strip.setPixelColor(i + (j + patternStep) % segment, ColorBright(color, float(j) * queue));
    }
  }
  strip.show();
  patternStep = (patternStep + 1) % (segment * range);
}

void firework(){
  int wait = arrayParameters[PAT_FIREWORK][0];
  uint32_t color = arrayParameters[PAT_FIREWORK][1];
  float bright = float(arrayParameters[PAT_FIREWORK][1]);
  int number = arrayParameters[PAT_FIREWORK][2];
  int radius = arrayParameters[PAT_FIREWORK][3];
  int rainbow = arrayParameters[PAT_FIREWORK][4];

    
  if(patternDelay != wait)
    patternDelay = wait;
  if(number > FIRE_NUMBER)
    number = FIRE_NUMBER;
  if(radius > FIRE_RADIUS)
    radius = FIRE_RADIUS;
  
  for(int i=0;i<number;i++){
    arrayfirework[patternStep][i] = random(pixelNumber);    
  }
  float queue = 100.0 / float(radius-1);
  int colorStep = round(float(patternStep) * 256.0 / float(radius));

  for(int i=0; i<radius;i++){
    for(int j=0; j<number;j++){
      int seed = arrayfirework[i][j];
      int currentStep = (radius -i + patternStep) % radius;
      if(rainbow)
        color = ColorBright(Wheel((i + j + colorStep) & 255), bright);

      for(int k=0; k<=currentStep;k++){
        strip.setPixelColor((seed + k) % pixelNumber, ColorBright(color, float(radius-1-currentStep) * queue));
        strip.setPixelColor((seed - k) % pixelNumber, ColorBright(color, float(radius-1-currentStep) * queue));
      }
    }
  }
  strip.show();
  patternStep = (patternStep + 1) % radius;
}

// Reduce existing brightness to set it between [0-100]
uint32_t ColorBright(uint32_t color, float bright) {
  float ratio = bright/100.0;
  uint8_t r = float((uint8_t)(color >> 16)) * ratio;
  uint8_t g = float((uint8_t)(color >> 8)) * ratio;
  uint8_t b = float((uint8_t)color) * ratio;
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

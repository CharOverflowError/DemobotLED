#include <FastLED.h>
#define NUM_LEDS 40
#define strip1pin 5
#define strip2pin 6

CRGBArray<NUM_LEDS> leds1;
CRGBArray<NUM_LEDS> leds2;

int dots[3];
int dirs[3];

int r;
int g;
int b;
int r_mod;
int g_mod;
int b_mod;

void setup() {
  FastLED.addLeds<NEOPIXEL, strip1pin>(leds1, NUM_LEDS);
  //FastLED.addLeds<NEOPIXEL, strip2pin>(leds2, NUM_LEDS); 

  dots = [0, 20, 39];
  dirs = [0, 0, 0];

  r_mod = random(-5, 5);
  g_mod = random(-5, 5);
  b_mod = random(-5, 5);
}
void loop() { 

  if (r == 255 || g == 255 || b == 255) {
    
    r = random(0, 150);
    g = random(0, 150);
    b = random(0, 150);

    r_mod = random(-5, 5);
    g_mod = random(-5, 5);
    b_mod = random(-5, 5);

  } else {
    r += r_mod;
    g += g_mod;
    b += b_mod;
  }
  
  for(int i=0; i < sizeof(dirs); i++) {
    int ran = random(0, 1);
    if (ran > 0.5) {
      dirs[i] = 1;
    } else {
      dirs[i] = -1;
    }
  }

  for(int i=0; i < sizeof(dots); i++) {
    //Detects end of array
    if (dots[i] == 0  && dirs[i] == -1) {
      dirs[i] == 1;
    } else if (dots[i] == 39 && dirs[i] == 1) {
      dirs[i] == -1;
    }

    //Detects collision
    if ((dots[i] + dirs[i]) == dots[max(0, i + dirs[i])]) {
      dirs[i] = -dirs[i];
    }

    //Reassign LEDs
    leds1[dots[i] + dirs[i]].setRGB(r, g, b);

  }

  FastLED.show();
  FastLED.delay(30);

}

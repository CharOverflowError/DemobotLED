#include "FastLED.h"

#define NUM_LEDS_LEFT 49
#define NUM_LEDS_RIGHT 47
#define MAIN_SIGNAL 11
#define LEFT_FRONT_SIGNAL 10
#define RIGHT_FRONT_SIGNAL 9
#define LEFT_BACK_SIGNAL 8
#define RIGHT_BACK_SIGNAL 7
#define RIGHT_LED_PIN 6
#define LEFT_LED_PIN 5

CRGB left_leds[NUM_LEDS_LEFT];
CRGB right_leds[NUM_LEDS_RIGHT];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, LEFT_LED_PIN>(left_leds, NUM_LEDS_LEFT);
  FastLED.addLeds<NEOPIXEL, RIGHT_LED_PIN>(right_leds, NUM_LEDS_RIGHT);
  Serial.begin(115200);
}

void loop() {
  FastLED.clear();
  
  // put your main code here, to run repeatedly:
  int main_pwm = round(getPulse(MAIN_SIGNAL)/50) * 50;
  switch (main_pwm) {    
    case 150: {
      double left_front_pwm = min(getPulse(LEFT_FRONT_SIGNAL), 500);
      double right_front_pwm = min(getPulse(RIGHT_FRONT_SIGNAL), 500);
      double left_back_pwm = min(getPulse(LEFT_BACK_SIGNAL), 500);
      double right_back_pwm = min(getPulse(RIGHT_BACK_SIGNAL), 500);
    
      double left_front_signal = ((left_front_pwm - 250) / 500);
      double right_front_signal = ((right_front_pwm - 250) / 500);
      double left_back_signal = ((left_back_pwm - 250) / 500);
      double right_back_signal = ((right_back_pwm - 250) / 500);

      // If robo-boy is going too fast
      if (abs(left_front_signal + left_back_signal) > .95 || abs(right_front_signal + right_back_signal) > .95) {
        for (int i=0; i < NUM_LEDS_LEFT - 1; i++) {
          left_leds[i] = CRGB::Green;
        }
        for (int i=0; i < NUM_LEDS_RIGHT - 1; i++) {
          right_leds[i] = CRGB::Black;
        }
        FastLED.show();
        delay(50);

        for (int i=0; i < NUM_LEDS_LEFT - 1; i++) {
          left_leds[i] = CRGB::Black;
        }
        for (int i=0; i < NUM_LEDS_RIGHT - 1; i++) {
          right_leds[i] = CRGB::Green;
        }
        FastLED.show();
        delay(50);
      } else {
        int light_left_front = floor(left_front_signal * NUM_LEDS_LEFT);
        int light_left_back = floor(left_back_signal * NUM_LEDS_LEFT + .5); 
        
        if (left_front_signal >= 0) {
          if (left_back_signal >=0) {
            for (int i=0; i < light_left_front + light_left_back - 1; i++) {
              left_leds[i] = CRGB::Red;
            }
          } else {
            for (int i=NUM_LEDS_LEFT-1; i >= (NUM_LEDS_LEFT - light_left_front); i--) {
              left_leds[i] = CRGB::Red;
            }
            for (int i=0; i < -light_left_back - 1; i++) {
              left_leds[i] = CRGB::Blue;
            }
          }
          
        } else {
          if (left_back_signal < 0) {
            for (int i=NUM_LEDS_LEFT-1; i >= NUM_LEDS_LEFT + light_left_front + light_left_back; i--) {
              left_leds[i] = CRGB::Blue;
            }
          } else {
            for (int i=NUM_LEDS_LEFT-1; i >= NUM_LEDS_LEFT + light_left_front; i--) {
              left_leds[i] = CRGB::Blue;
            }
            for (int i=0; i < light_left_back - 1; i++) {
              left_leds[i] = CRGB::Red;
            }
          }
        }
      
        int light_right_front = floor(right_front_signal * NUM_LEDS_RIGHT);
        int light_right_back = floor(right_back_signal * NUM_LEDS_RIGHT + .5);
          
        if (right_front_signal >= 0) {
          if (right_back_signal >=0) {
            for (int i=0; i < light_right_front + light_right_back - 1; i++) {
              right_leds[i] = CRGB::Red;
            }
          } else {
            for (int i=NUM_LEDS_RIGHT-1; i > NUM_LEDS_RIGHT - light_right_front; i--) {
              right_leds[i] = CRGB::Red;
            }
            for (int i=0; i < -light_right_back - 1; i++) {
              right_leds[i] = CRGB::Blue;
            }
          }
          
        } else {
          if (right_back_signal < 0) {
            for (int i=NUM_LEDS_RIGHT-1; i >= NUM_LEDS_RIGHT + light_right_front + light_right_back; i--) {
              right_leds[i] = CRGB::Blue;
            }
          } else {
            for (int i=0; i < light_right_back - 1; i++) {
              right_leds[i] = CRGB::Red;
            }
            for (int i=NUM_LEDS_RIGHT-1; i > NUM_LEDS_RIGHT + light_right_front; i--) {
              right_leds[i] = CRGB::Blue;
            }
          }
        }
  
        FastLED.show();
        delay(30);
      }
      break;
    }
      
    default:
      for (int i=0; i<NUM_LEDS_LEFT - 1; i++) {
        left_leds[i].setRGB(random8(), random8(), random8());
      }
      for (int i=0; i<NUM_LEDS_RIGHT - 1; i++) {
        right_leds[i].setRGB(random8(), random8(), random8());
      }

      FastLED.show();
      delay(30);
      break;
  }
}

double getPulse(int pin_num) {
  return pulseIn(pin_num, HIGH);    
}


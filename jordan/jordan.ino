#include <SPI.h>

#include <pixels.h>
#include <ws2812pixels.h>
#include <jperf_pixels.h>
#include <animator.h>
#include <Bounce2.h>

#include <avr/power.h>

// Neck is 23 on 3
WS2812Pixels neck = WS2812Pixels(23, 3);

// Left arm is 49 on 8
WS2812Pixels left = WS2812Pixels(33q, 8);

// Right arm is 49 on 10
WS2812Pixels right = WS2812Pixels(36, 10);

JPerfPixels pixels = JPerfPixels(neck, left, right);
Animator animator = Animator(pixels);

uint32_t start = millis();
uint32_t modeStart = 0;

Bounce bouncer = Bounce();

void setup() {
  clock_prescale_set(clock_div_1);

  pinMode(11, INPUT_PULLUP);
  bouncer.attach(11);

  animator.begin();
  animator.startAnimation(ANIM_JORDAN_START);

}

void loop() {
  uint32_t now = millis();

  if (bouncer.update()) {
    // Pin changed state
    if (bouncer.read()) {
      // It is a new press, so advance the mode...
      animName_t anim = animator.currentAnimation();
      if (anim != ANIM_JORDAN_END) {
        // Advance by one
        anim = (animName_t)((int)anim + 1);
        animator.startAnimation(anim);
      } else {
        animator.startAnimation(ANIM_JORDAN_START);
      }
    }
  }

  animator.loop();
}

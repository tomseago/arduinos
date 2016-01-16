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
WS2812Pixels left = WS2812Pixels(49, 8);

// Right arm is 49 on 10
WS2812Pixels right = WS2812Pixels(49, 10);

JPerfPixels pixels = JPerfPixels(neck, left, right);
Animator animator = Animator(pixels);

uint32_t start = millis();
uint32_t modeStart = 0;

Bounce bouncer = Bounce();

enum mode_t {
  MODE_START = 0
  , MODE_FEM
  , MODE_MASC
  
  , MODE_END
};

mode_t mode = MODE_START;

void setup() {
  clock_prescale_set(clock_div_1);

//  pinMode(13, OUTPUT);
//  digitalWrite(13, LOW);

  pinMode(11, INPUT_PULLUP);
  bouncer.attach(11);

  animator.timeScaleFactor = 200;
  animator.begin();
  animator.startAnimation(ANIM_JPERF_START);

}

void loop() {
  uint32_t now = millis();

  if (bouncer.update()) {
    // Pin changed state
    if (bouncer.read()) {
      // It is a new press, so advance the mode...
      if (mode != MODE_END) {
        mode = (mode_t)((int)mode + 1);

        // Update to right thing based on mode 
        switch(mode) {
          case MODE_FEM:
            animator.startAnimation(ANIM_JPERF_FBLOBS); // The proper start
//            animator.startAnimation(ANIM_JPERF_FSPOTS); // For testing
//            animator.startAnimation(ANIM_JORDAN_RUNWAY);
            modeStart = now;
            break;
            
          case MODE_MASC:
            animator.startAnimation(ANIM_JPERF_MBOUNCE); // The proper start
//            animator.startAnimation(ANIM_JPERF_MBOUNCE_END); // For testing
//            animator.startAnimation(ANIM_JORDAN_RUNWAY);
            modeStart = now;
            break;

          case MODE_END:
            animator.startAnimation(ANIM_JPERF_END);
            break;
        }
      } else {
        mode = MODE_START;
        animator.startAnimation(ANIM_JPERF_START);
      }
    }
  }
  
  uint32_t elapsed = now - modeStart;

  // We know the elapsed time is slow by about 20%, so correct it
  elapsed += (elapsed * 200) / 1000;

  // Check for elapsed time boundaries. Auto advance to a new anim mode
  // at these defined time boundaries
  animName_t anim = animator.currentAnimation();
  switch(mode) {
    case MODE_FEM:
      // Check from the end backwards
      if (elapsed > 172500) {
        if (anim != ANIM_JPERF_BREATH) {
          animator.startAnimation(ANIM_JPERF_BREATH);
        }      
      } else if (elapsed > 144000) {
        if (anim != ANIM_JPERF_FBLOBS) {
          animator.startAnimation(ANIM_JPERF_FBLOBS);
        }      
      } else if (elapsed > 81000) {
        if (anim != ANIM_JPERF_FSPOTS) {
          animator.startAnimation(ANIM_JPERF_FSPOTS);
        }      
      } else if (elapsed > 40000) {
        if (anim != ANIM_JPERF_FPULSES) {
          animator.startAnimation(ANIM_JPERF_FPULSES);
        }      
      } else if (elapsed > 31940) {
        if (anim != ANIM_JPERF_FSPARKLE) {
          animator.startAnimation(ANIM_JPERF_FSPARKLE);
        }       
      }
      break;
      
    case MODE_MASC:
      // Check from the end backwards
      if (elapsed > 127190) {
        if (anim != ANIM_JPERF_MBOUNCE_END) {
          animator.startAnimation(ANIM_JPERF_MBOUNCE_END);
        }    

      } else if (elapsed > 123540) { //123540
        if (anim != ANIM_JPERF_OFF) {
          animator.startAnimation(ANIM_JPERF_OFF);
        }      
      } else if (elapsed > 89800) {
        if (anim != ANIM_JPERF_MCLAP) {
          animator.startAnimation(ANIM_JPERF_MCLAP);
        }      
        
      } else if (elapsed > 87841) { // ok
        if (anim != ANIM_JPERF_OFF) {
          animator.startAnimation(ANIM_JPERF_OFF);
        }      
      } else if (elapsed > 83300) { // ok
        if (anim != ANIM_JPERF_MSPARKLE) {
          animator.startAnimation(ANIM_JPERF_MSPARKLE);
        }      
        
      } else if (elapsed > 51130) { // ok
        if (anim != ANIM_JPERF_MBOUNCE) {
          animator.startAnimation(ANIM_JPERF_MBOUNCE);
        }      
      } else if (elapsed > 49031) {
        if (anim != ANIM_JPERF_OFF) {
          animator.startAnimation(ANIM_JPERF_OFF);
        }      
      } else if (elapsed > 44750) {
        if (anim != ANIM_JPERF_MSNARE) {
          animator.startAnimation(ANIM_JPERF_MSNARE);
        }       
      } else if (elapsed > 32130) { // ok
        if (anim != ANIM_JPERF_MBOUNCE) {
          animator.startAnimation(ANIM_JPERF_MBOUNCE);
        }      
      } else if (elapsed > 27840) {
        if (anim != ANIM_JPERF_MSNARE) {
          animator.startAnimation(ANIM_JPERF_MSNARE);
        }       
      }
      break;  
  }

  animator.loop();

}

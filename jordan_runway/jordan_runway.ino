#include <SPI.h>

#include <pixels.h>
#include <ws2812pixels.h>
#include <two_channels.h>
#include <animator.h>
#include <anims.h>

#include <avr/power.h>

// Left shoulder is 48 on 8
WS2812Pixels left = WS2812Pixels(48, 8);

// Right shoulder is 48 on 10
WS2812Pixels right = WS2812Pixels(48, 10);

TwoChannels pixels = TwoChannels(left, right);
Animator animator = Animator(pixels);

uint32_t start = millis();

void setup() {
  clock_prescale_set(clock_div_1);

//  pinMode(13, OUTPUT);
//  digitalWrite(13, LOW);
  
  // put your setup code here, to run once:
  animator.begin();

  //animator.startAnimation(ANIM_SPARKLE);
  animator.startAnimation(ANIM_JORDAN_RUNWAY);
  
  //  pixels.setPixel(0, 0);
  //  pixels.send();
}

void loop() {
//  // put your main code here, to run repeatedly:
//  uint32_t now = millis();
//
//  uint32_t elapsed = now - start;
//
//  if ((elapsed / 1000) % 2) {
//    pixels.setAllPixels(255,255,255);
//  } else {
//    pixels.setAllPixels(0, 0, 0);
//  }
//
//  pixels.send();
  
  animator.loop();

//  Pixels& pixels = bike;
//  pixels.setAllPixels(255,0,0);
//  pixels.send();
//  delay(1000);
//  pixels.setAllPixels(0,255,0);
//  pixels.send();
//  delay(1000);
//  pixels.setAllPixels(0,0,255);
//  pixels.send();
//  delay(1000);
}

#include <SPI.h>

#include <pixels.h>
#include <ws2812pixels.h>
#include <animator.h>

#include <avr/power.h>

// Neck is 23 on 3
//WS2812Pixels pixels = WS2812Pixels(23, 3);

// Left arm is 49 on 8
//WS2812Pixels pixels = WS2812Pixels(49, 8);

// Right arm is 49 on 10
WS2812Pixels pixels = WS2812Pixels(49, 10);

Animator animator = Animator(pixels);
uint32_t start = millis();

void setup() {
  clock_prescale_set(clock_div_1);

//  pinMode(13, OUTPUT);
//  digitalWrite(13, LOW);
  
  // put your setup code here, to run once:
  animator.begin();
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

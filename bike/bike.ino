#include <SPI.h>

#include <pixels.h>
#include <ws2812pixels.h>
#include <bike_pixels.h>
#include <animator.h>

#include <avr/power.h>

// Front strip has 32 + 5 for scanner. All white draws 1.58amps, Typical is more like 0.8amps
WS2812Pixels front = WS2812Pixels(37, 3);


// Rear strip has 50. All white draws 2.14amps, 4.2a for both together.
WS2812Pixels left = WS2812Pixels(50, 4);
WS2812Pixels right = WS2812Pixels(50, 5);

BikePixels bike = BikePixels(front, left, right);

Animator animator = Animator(bike);
uint32_t start = millis();

void setup() {
  clock_prescale_set(clock_div_1);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
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

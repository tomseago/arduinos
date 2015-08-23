// This #include statement was automatically added by the Particle IDE.
#include "pixels.h"
#include "ws2801pixels.h"
#include "animator.h"

// to remove compile warning
#ifdef NOT_DEFINED_DUDE
#include "anims.h"

#include "anims_funcs.h"
#endif

// This #include statement was automatically added by the Particle IDE.
//#include "animator.h"

// This #include statement was automatically added by the Particle IDE.
//#include "cf-ws2801.h"

//Adafruit_WS2801 strip = Adafruit_WS2801(25);

WS2801Pixels pixels = WS2801Pixels(25);

Animator animator = Animator(pixels);

uint32_t start = millis();

SYSTEM_MODE(MANUAL);

void setup() {

    animator.begin();
    // Hopefully this clears any pixels we aren't addressing....
    pixels.send();
    
//   strip.begin();

//   // Update LED contents, to start they are all 'off'
//   strip.show();
  
  //RGB.control(true);
    // pixels.setPixel(0, 255, 0, 0);
    // pixels.setPixel(1, 255, 0, 0);
    // pixels.setPixel(2, 255, 0, 0);
    
    // pixels.setAllPixels(255, 255, 0, PF_LAST_FRAME);

    // pixels.setPixel(0, 0, 0, 255, PF_LAST_FRAME);
    // pixels.setPixel(1, 0, 255, 0, PF_LAST_FRAME);
    // pixels.setPixel(2, 0, 255, 0, PF_LAST_FRAME);

    // pixels.setPixel(0, 0, 255, 0, PF_NEXT_FRAME);
    // pixels.setPixel(1, 0, 255, 0, PF_NEXT_FRAME);
    // pixels.setPixel(2, 0, 255, 0, PF_NEXT_FRAME);

}

void loop() {
    animator.loop();
    uint32_t now = millis();
    
    // pixels.fadeIntoCurrent((now-start) << 8 / 1000);
    //pixels.send();
}

// void loop2() {
//     strip.setPixelColor(0, 0x00FF0000);
//     strip.setPixelColor(1, 0x0000ff00);
//     strip.setPixelColor(2, 0x000000ff);

//     strip.show();
// }

// void loop3() {
//   // Some example procedures showing how to display to the pixels
  
//   RGB.color(255,0,0);
//   colorWipe(Color(255, 0, 0), 50);
  
//   RGB.color(255, 255, 0);
//   colorWipe(Color(0, 255, 0), 50);

//   RGB.color(255, 255, 255);
//   colorWipe(Color(0, 0, 255), 50);

// //   RGB.color(0, 255, 0);
// //   rainbow(20);

// //   RGB.color(0, 0, 255);
// //   rainbowCycle(20);
// }

// void rainbow(uint8_t wait) {
//   int i, j;
   
//   for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
//     for (i=0; i < strip.numPixels(); i++) {
//       strip.setPixelColor(i, Wheel( (i + j) % 255));
//     }  
//     strip.show();   // write all the pixels out
//     delay(wait);
//   }
// }

// // Slightly different, this one makes the rainbow wheel equally distributed 
// // along the chain
// void rainbowCycle(uint8_t wait) {
//   int i, j;
  
//   for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
//     for (i=0; i < strip.numPixels(); i++) {
//       // tricky math! we use each pixel as a fraction of the full 96-color wheel
//       // (thats the i / strip.numPixels() part)
//       // Then add in j which makes the colors go around per pixel
//       // the % 96 is to make the wheel cycle around
//       strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
//     }  
//     strip.show();   // write all the pixels out
//     delay(wait);
//   }
// }

// // fill the dots one after the other with said color
// // good for testing purposes
// void colorWipe(uint32_t c, uint8_t wait) {
//   int i;
  
//   for (i=0; i < strip.numPixels(); i++) {
//       strip.setPixelColor(i, c);
//       strip.show();
//       delay(wait);
//   }
// }

// /* Helper functions */

// // Create a 24 bit color value from R,G,B
// uint32_t Color(byte r, byte g, byte b)
// {
//   uint32_t c;
//   c = r;
//   c <<= 8;
//   c |= g;
//   c <<= 8;
//   c |= b;
//   return c;
// }

// //Input a value 0 to 255 to get a color value.
// //The colours are a transition r - g -b - back to r
// uint32_t Wheel(byte WheelPos)
// {
//   if (WheelPos < 85) {
//   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//   } else if (WheelPos < 170) {
//   WheelPos -= 85;
//   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
//   } else {
//   WheelPos -= 170; 
//   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
//   }
// }

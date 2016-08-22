#ifndef _WS2812_PIXELS_H_
#define _WS2812_PIXELS_H_

#include "pixels.h"


#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

// 'type' flags for LED pixels (third parameter to constructor):
#define NEO_RGB     0x00 // Wired for RGB data order
#define NEO_GRB     0x01 // Wired for GRB data order
#define NEO_BRG     0x04
#define NEO_RBG     0x08 
  
#define NEO_COLMASK 0x01
#define NEO_KHZ800  0x02 // 800 KHz datastream
#define NEO_SPDMASK 0x02
// Trinket flash space is tight, v1 NeoPixels aren't handled by default.
// Remove the ifndef/endif to add support -- but code will be bigger.
// Conversely, can comment out the #defines to save space on other MCUs.
#ifndef __AVR_ATtiny85__
#define NEO_KHZ400  0x00 // 400 KHz datastream
#endif



class WS2812Pixels : public Pixels {
protected:
	int outputPin;
	uint32_t endTime;       // Latch timing reference
 	inline bool canShow(void) { return (micros() - endTime) >= 50L; }
 	uint8_t type;

    uint8_t rOffset;      
    uint8_t gOffset;      
    uint8_t bOffset;      

#ifdef __AVR__
 	volatile uint8_t
    	*port;         // Output PORT register
 	uint8_t
    	pinMask;       // Output PORT bitmask
#endif

    // Important to override this for current frame so that
    // the RGB ordering can be respected for DMA outputs
    virtual void setPixelInFrame(uint16_t which, uint8_t frame, uint8_t r, uint8_t g, uint8_t b, uint8_t flags);

public:
    WS2812Pixels(uint16_t numPixels, int outputPin, uint8_t type=NEO_GRB + NEO_KHZ800);

    virtual uint32_t send();

    virtual uint32_t getPixel(uint16_t which, uint8_t flags = PF_CURRENT_FRAME);
};

#endif // _WS2812_PIXELS_H_



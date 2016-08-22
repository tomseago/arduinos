#ifndef _BIKE_PIXELS_H_
#define _BIKE_PIXELS_H_

#include "pixels.h"
#include <SPI.h>

class BikePixels : public Pixels {

protected:
	Pixels& front;
	Pixels& left;
	Pixels& right;

	uint16_t numFront;

    void setPixelInFrame(uint16_t which, uint8_t frame, uint8_t r, uint8_t g, uint8_t b, uint8_t flags);

public:
    BikePixels(Pixels& front, Pixels& left, Pixels& right);

    virtual uint16_t getNumPixelsOnChannel(uint8_t channel);
    virtual uint8_t getNumChannels();

    uint32_t getPixel(uint16_t which, uint8_t flags = PF_CURRENT_FRAME);

    void setBrightness(uint8_t brightness);

    void copyNextToLast();
    void copyLastToCurrent();
    void swapNextAndLast();
    void fadeIntoCurrent(uint8_t distance);

    virtual uint32_t send();
};

#endif // _WS2801_PIXELS_H_



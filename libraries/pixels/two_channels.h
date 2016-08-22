#ifndef _TWO_CHANNELS_H_
#define _TWO_CHANNELS_H_

#include "pixels.h"
#include <SPI.h>

class TwoChannels : public Pixels {

protected:
	Pixels& chanA;
	Pixels& chanB;

	uint16_t numA;

    void setPixelInFrame(uint16_t which, uint8_t frame, uint8_t r, uint8_t g, uint8_t b, uint8_t flags);

public:
    TwoChannels(Pixels& chanA, Pixels& chanB);

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

#endif // _TWO_CHANNELS_H_



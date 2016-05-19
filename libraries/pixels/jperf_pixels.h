#ifndef _JPERF_PIXELS_H_
#define _JPERF_PIXELS_H_

#include "pixels.h"
#include <SPI.h>

#define JPERF_PIXELS_WRIST 8
#define JPERF_PIXELS_FOREARM 12
#define JPERF_PIXELS_ELBOW  13
#define JPERF_PIXELS_BICEP 16
#define JPERF_PIXELS_NECK 21



#define JPERF_BOUNDARY_WRIST_FOREARM (JPERF_PIXELS_WRIST)
#define JPERF_BOUNDARY_FOREARM_ELBOW (JPERF_PIXELS_WRIST + JPERF_PIXELS_FOREARM)
#define JPERF_BOUNDARY_ELBOW_BICEP (JPERF_PIXELS_WRIST + JPERF_PIXELS_FOREARM + JPERF_PIXELS_ELBOW)
#define JPERF_BOUNDARY_BICEP_NECK (JPERF_PIXELS_WRIST + JPERF_PIXELS_FOREARM + JPERF_PIXELS_ELBOW + JPERF_PIXELS_BICEP)
#define JPERF_BOUNDARY_NECK_LBICEP (JPERF_PIXELS_WRIST + JPERF_PIXELS_FOREARM + JPERF_PIXELS_ELBOW + JPERF_PIXELS_BICEP + JPERF_PIXELS_NECK)
#define JPERF_BOUNDARY_LBICEP_LELBOW (JPERF_PIXELS_WRIST + JPERF_PIXELS_FOREARM + JPERF_PIXELS_ELBOW + JPERF_PIXELS_BICEP + JPERF_PIXELS_NECK + JPERF_PIXELS_BICEP)
#define JPERF_BOUNDARY_LELBOW_LFOREARM (JPERF_PIXELS_WRIST + JPERF_PIXELS_FOREARM + JPERF_PIXELS_ELBOW + JPERF_PIXELS_BICEP + JPERF_PIXELS_NECK + JPERF_PIXELS_BICEP + JPERF_PIXELS_ELBOW)
#define JPERF_BOUNDARY_LFOREARM_LWRIST (JPERF_PIXELS_WRIST + JPERF_PIXELS_FOREARM + JPERF_PIXELS_ELBOW + JPERF_PIXELS_BICEP + JPERF_PIXELS_NECK + JPERF_PIXELS_BICEP + JPERF_PIXELS_ELBOW + JPERF_PIXELS_FOREARM)
#define JPERF_BOUNDARY_END (JPERF_BOUNDARY_LFOREARM_LWRIST + JPERF_PIXELS_WRIST)

#define JPERF_COUNT JPERF_BOUNDARY_END
#define JPERF_HCOUNT (JPERF_BOUNDARY_END/2)

class JPerfPixels : public Pixels {

protected:
	Pixels& neck;
	Pixels& left;
	Pixels& right;

    uint16_t numNeck;
    uint16_t numLeft;
    uint16_t numRight;

    virtual void setPixelInFrame(uint16_t which, uint8_t frame, uint8_t r, uint8_t g, uint8_t b, uint8_t flags);

    virtual int16_t actualPixelForIndex(int16_t which, uint8_t flags);

public:
    JPerfPixels(Pixels& neck, Pixels& left, Pixels& right);

    virtual uint16_t getNumPixelsOnChannel(uint8_t channel);
    virtual uint8_t getNumChannels();

    uint32_t getPixel(uint16_t which, uint8_t flags = PF_CURRENT_FRAME);

    void setBrightness(uint8_t brightness);

    void copyNextToLast();
    void copyLastToCurrent();
    void swapNextAndLast();
    void fadeIntoCurrent(uint8_t distance);

    virtual void send();
};

#endif // _JPERF_PIXELS_H_


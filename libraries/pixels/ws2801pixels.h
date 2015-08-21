#ifndef _WS2801_PIXELS_H_
#define _WS2801_PIXELS_H_

#include "pixels.h"
#include <SPI.h>

class WS2801Pixels : public Pixels {
public:
    WS2801Pixels(uint16_t numPixels);

    virtual void send();
};

#endif // _WS2801_PIXELS_H_



#ifndef _MT_HARNASS_H_
#define _MT_HARNASS_H_

#include <mt-neopixel.h>

// #include "mt-lpd" ... whatever

#define F_SASH  1
#define F_STRAP (1 << 1)

#define F_BOTH (F_SASH | F_STRAP)

class MTHarnass {

public:
    Adafruit_NeoPixel sash;

    MTHarnass(uint8_t sashPin);

    void begin();
    void loop();

    void solidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t flags);
};



#endif // _MT_HARNASS_H_
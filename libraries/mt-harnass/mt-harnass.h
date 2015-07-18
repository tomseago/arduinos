#ifndef _MT_HARNASS_H_
#define _MT_HARNASS_H_

#include <mt-neopixel.h>
#include <mtlpd8806.h>

// #include "mt-lpd" ... whatever

#define F_SASH  1
#define F_ARM (1 << 1)

#define F_BOTH (F_SASH | F_ARM)

class MTHarnass {

public:
    Adafruit_NeoPixel sash;
    LPD8806 arm;

    MTHarnass(uint8_t sashPin, uint8_t armPin);

    void begin();
    void loop();

    void solidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t flags);
};



#endif // _MT_HARNASS_H_

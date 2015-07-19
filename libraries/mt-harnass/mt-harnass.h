#ifndef _MT_HARNASS_H_
#define _MT_HARNASS_H_

#include <mt-neopixel.h>
#include <mtlpd8806.h>

// #include "mt-lpd" ... whatever

#define F_SASH  1
#define F_ARM (1 << 1)

#define F_BOTH (F_SASH | F_ARM)

enum animName_t {
	ANIM_NONE = 0

	, ANIM_ALL_BLINK = 1

};

// #define ANIM_NONE  0
// #define ANIM_BLINK 1

struct animParams_t {
	uint32_t currentFrame;
	uint32_t startedAt;

	uint32_t totalFrames;
	uint32_t frameLength;
};


class MTHarnass {

public:
    Adafruit_NeoPixel sash;
    LPD8806 arm;

    animParams_t animParams;
    uint8_t currentAnim;

    MTHarnass(uint8_t sashPin, uint8_t armPin);

    void begin();
    void loop();

    void solidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t flags);

    void startAnimation(animName_t animNum);

    void BLINK_setup();
    void BLINK_drawFrame();
};



#endif // _MT_HARNASS_H_

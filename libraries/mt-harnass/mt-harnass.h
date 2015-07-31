#ifndef _MT_HARNASS_H_
#define _MT_HARNASS_H_

#include <mt-neopixel.h>
#include <mtlpd8806.h>

// #include "mt-lpd" ... whatever

#define F_SASH  1
#define F_ARM (1 << 1)

#define F_BOTH (F_SASH | F_ARM)

#define ANIM_SIG(x) void x##_setup(); void x##_drawFrame();

#define SASH_COUNT  24
#define ARM_COUNT   32

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

enum animName_t {
	ANIM_NONE = 0

	, ANIM_ALL_BLINK 
	, ANIM_FLOOD 
	, ANIM_HRAINBOW 
	, ANIM_TRACER
	, ANIM_RAND_MOVER
	, ANIM_RAND_ALL
	, ANIM_RAND_BRIGHT
};

// #define ANIM_NONE  0
// #define ANIM_BLINK 1

struct animParams_t {
	uint32_t currentFrame;
	uint32_t startedAt;

	uint32_t totalFrames;
	uint32_t frameLength;
};


enum frame_t {
    FRAME_CURRENT = 0,
    FRAME_LAST,
    FRAME_NEXT
};

class MTHarnass {

public:
    Adafruit_NeoPixel sash;
    LPD8806 arm;

    animParams_t animParams;
    uint8_t currentAnim;

    uint32_t selectedColor;
    uint8_t sColPos;

    // Random for anim
    uint32_t animColor;
    uint32_t animReg;

    bool muted;

    // For animations to save selected color so it only saves
    // at start of anim
    uint32_t capturedColor;

    int32_t speedMultiplier = 0x0100; // Start at 1 * 256

    uint8_t lastFrame[ (SASH_COUNT + ARM_COUNT) * 3 ];
    uint8_t nextFrame[ (SASH_COUNT + ARM_COUNT) * 3 ];

    MTHarnass(uint8_t sashPin, uint8_t armPin);

    void begin();
    void loop();

    uint32_t colorWheel(uint8_t WheelPos);


    void changeColorPos(int8_t delta);

    void solidArm(uint32_t color);
    void solidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t flags);
    void h6Stripe(uint32_t color, uint8_t stripe, uint8_t flags);
    void setMappedPixelColor(int8_t pixelNum, uint32_t color, frame_t frame);
    void setPixelColor(bool isArm, uint8_t num, uint32_t color, frame_t frame);

    void startAnimation(animName_t animNum);

    // Give this sum value that is already multiplied by 256
    void changeSpeed(int16_t delta);
    void resetSpeed();
    void updateSpeed();

    void brightness(uint8_t val);
    void brighter(uint8_t val);
    void darker(uint8_t val);

    uint32_t adjustedFrameLength;

    // Overlay modes
    bool powerArmEnabled = true;

    bool powerArmIsOn = false;


    ANIM_SIG(BLINK);
    ANIM_SIG(FLOOD);
    ANIM_SIG(HRAINBOW);

    ANIM_SIG(TRACER);
    ANIM_SIG(RAND_MOVER);
    ANIM_SIG(RAND_ALL);
    ANIM_SIG(RAND_BRIGHT);

    ANIM_SIG(FLOOD_LINE);

    ANIM_SIG(BLUE_STEPS);
    // void BLINK_setup();
    // void BLINK_drawFrame();
};



#endif // _MT_HARNASS_H_

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <application.h>

#include "pixels.h"
#include "anims.h"

ANIMATION_ENUM

#define ANIM_FLAG_NONE               0
#define ANIM_FLAG_WANTS_FADES        1
#define ANIM_FLAG_MUTES_BASE         (1 << 1)
#define ANIM_FLAG_ADVANCE_ON_STOP    (1 << 2)

struct animParams_t {
	uint32_t currentFrame;
	uint32_t startedAt;
    uint32_t lastDrawAt;
    uint32_t elapsedSinceStart;
    uint32_t elapsedSinceLastDraw;
    uint32_t maxTime;

	uint32_t totalFrames;
	int32_t frameLength;

    uint8_t flags;
};


class Animator {
    Pixels& pixels;
    
    animParams_t animParams;
    animName_t currentAnim;
    
    uint32_t animColor;
    uint32_t animReg;

    uint32_t capturedColor;

    int32_t speedMultiplier = 0x0100; // Start at 1 * 256
    
    uint32_t lastFrameAt;

    uint32_t adjustedFrameLength;
    
    void updateSpeed();
    
    void nextAnimation();
    
public:
    Animator(Pixels& pix);

    void begin();
    void loop();
    
    uint32_t colorWheel(uint8_t WheelPos);

    void startAnimation(animName_t animNum);

    ANIMATION_SIGNATURES
};


#endif // #ifndef _ANIMATOR_H_



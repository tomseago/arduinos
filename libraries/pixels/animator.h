#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#define ANIMATE_SERVOS true

#include <Arduino.h>
// #include <application.h>

#include "pixels.h"

#if ANIMATE_SERVOS
#include "remote_servos.h"
#endif // ANIMATE_SERVOS

#include "anims.h"

ANIMATION_ENUM

#define ANIM_FLAG_NONE               0
#define ANIM_FLAG_WANTS_FADES        1
#define ANIM_FLAG_MUTES_BASE         (1 << 1)
#define ANIM_FLAG_ADVANCE_ON_STOP    (1 << 2)
#define ANIM_FLAG_SKIP_FIRST_FADE    (1 << 3)

// #define MAX_ANIMATION_TIME (60 * 60 * 1000)
#define DEFAULT_MAX_ANIMATION_TIME (60 * 60 * 1000) // 1 hour

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

    uint32_t maxAnimTime;
    
    void updateSpeed();
    
    void nextAnimation();
    
#if ANIMATE_SERVOS
    RemoteServos& servos;
#endif // ANIMATE_SERVOS

public:
    // Because the WS2812 code in particular turns of interrupts,
    // this timeScaleFactor can be set to something other than 1000
    // to scale the timing based on how slow millis is running.
    uint32_t timeScaleFactor;

    Animator(Pixels& pix,
#if ANIMATE_SERVOS
        RemoteServos& servos,
#endif // ANIMATE_SERVOS
        uint32_t maxAnimTime=DEFAULT_MAX_ANIMATION_TIME
        );

#if ANIMATE_SERVOS
    void setServos(RemoteServos& servos);
#endif // ANIMATE_SERVOS

    void begin();
    void loop();
    
    uint32_t colorWheel(uint8_t WheelPos);

    void startAnimation(animName_t animNum);
    animName_t currentAnimation();

    ANIMATION_SIGNATURES
};


#endif // #ifndef _ANIMATOR_H_



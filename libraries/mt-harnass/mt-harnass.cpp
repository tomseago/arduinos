
#include <mt-harnass.h>

#include <mtui.h>
extern MTUI ui;


#include "anims.h"


////////////

void writeDebugNums(uint32_t a, uint32_t b) {
    char buf[10];

    uView.setCursor(0, 0);
    sprintf(buf, "%d", a);
    uView.print(buf);

    uView.setCursor(0, 8);
    sprintf(buf, "%d", b);
    uView.print(buf);

    uView.display();
}

///////////

MTHarnass::MTHarnass(uint8_t sashPin, uint8_t armPin) 
    : sash(24, sashPin, NEO_GRB + NEO_KHZ800),
      arm(32, armPin, armPin+1)
{
    memset(&animParams, 0, sizeof(animParams_t));

    currentAnim = ANIM_NONE;
}

void MTHarnass::begin() {
    sash.begin();
    sash.setBrightness(128);

    //arm.updatePins(5);
    arm.begin();
    // TODO: Add brightness capability to LPD8806 library
    // arm.setBrightness(128);
}

void MTHarnass::loop() {

    if (animParams.totalFrames == 0 || animParams.frameLength == 0) {
        // Early out
        return;
    }

    // Which frame SHOULD we be on?
    uint32_t now = millis();

    uint32_t elapsedTime = millis() - animParams.startedAt;
    // Using millis so ignoring rollover. Gives us 70 days or so.

    uint32_t nextFrame = (elapsedTime / animParams.frameLength) % animParams.totalFrames;

    writeDebugNums(animParams.currentFrame, animParams.totalFrames);

    // TODO: Add a check to make sure we don't do this
    // for infinity?? Like only skip a couple of frames
    // and then move on.
    while(animParams.currentFrame != nextFrame) {

        switch(currentAnim) {
            case ANIM_ALL_BLINK:
                BLINK_drawFrame();
                break;
        }

        // Loop
        animParams.currentFrame++;

        // Rollover in a loop that continues in the same
        // direction.
        // TODO: Add the ability to reverse direction?
        if (animParams.currentFrame >= animParams.totalFrames) {
            animParams.currentFrame = 0;
        }
    }

    // Assume work was done
    sash.show();
    arm.show();
}

void MTHarnass::solidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t flags) {

    if (flags & F_SASH) {
        for(uint8_t i=0; i<sash.numPixels(); i++) {
            sash.setPixelColor(i, r, g, b);
        }
        sash.show();
    }

    if (flags & F_ARM) {
        for(uint8_t i=0; i<arm.numPixels(); i++) {
            arm.setPixelColor(i, r, g, b);
        }
        arm.show();
    }

}



void MTHarnass::startAnimation(animName_t animNum) {

    animParams.currentFrame = 0xffffffff;
    animParams.startedAt = millis();

    switch(animNum) {
        case ANIM_ALL_BLINK:
            BLINK_setup();
            BLINK_drawFrame();
            break;

        // Default is all off
        default:
            solidColor(0, 0, 0, F_BOTH);
            animParams.totalFrames = 0;
            break;
    }

    // Reset the animation
    currentAnim = animNum;
}


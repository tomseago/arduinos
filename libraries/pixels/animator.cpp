/**
 * This file is the animator class implementation. It brings
 * in both it's header and then includes the anims_funcs.h file
 * which has the actual implementations of animations in it.
 *
 * The anims_funcs.h file works in conjuction with the anims.h
 * file to determine which animations are available.
 */

#include "animator.h"
#include "rand.h"


Animator::Animator(Pixels& pix,
#if ANIMATE_SERVOS
        RemoteServos& servos, 
#endif // ANIMATE_SERVOS
        uint32_t maxAnimTime
    ) :

    pixels(pix),
    maxAnimTime(maxAnimTime)
#if ANIMATE_SERVOS
    , servos(servos)
#endif // ANIMATE_SERVOS
    {
        
}

void
Animator::begin() {
    pixels.setBrightness(255);
    
    startAnimation(ANIM_NONE);
}

uint32_t now;
bool updatedFrames;
uint32_t nextFrameNum;


void 
Animator::loop() {
    // if (muted) {
    //     solidColor(0,0,0,F_BOTH);
    //     sash.show();
    //     arm.show();
    //     return;
    // }

    now = millis();

    if ( /*!(overlayAnim && (overlayParams.flags & ANIM_FLAG_MUTES_BASE) ) &&*/
         (animParams.totalFrames != 0 && animParams.frameLength != 0) ) {
        // Which frame SHOULD we be on?

        animParams.elapsedSinceStart = now - animParams.startedAt;
        animParams.elapsedSinceLastDraw = now - animParams.lastDrawAt;
        
        // if (timeScaleFactor > 0) {
        //     uint32_t timeOffset = (animParams.elapsedSinceStart * timeScaleFactor) / 1000;
        //     animParams.elapsedSinceStart += timeOffset;
        //     animParams.elapsedSinceLastDraw += timeOffset;
        // }


        if (animParams.elapsedSinceStart > maxAnimTime || 
            (animParams.maxTime > 0 && animParams.elapsedSinceStart > animParams.maxTime )) {
            nextAnimation();
            loop();
            return;
        }

        // Using millis so ignoring rollover. Gives us 70 days or so.

        // If frameLength is > 0, then we figure out a number of
        // frames to advance to. If it is < 0 we just do "next frame"
        // and that is all

        if (animParams.frameLength > 0) {
            nextFrameNum = (animParams.elapsedSinceStart / adjustedFrameLength) % animParams.totalFrames;
        } else {
            nextFrameNum = animParams.currentFrame + 1;
            if (nextFrameNum >= animParams.totalFrames) {
                nextFrameNum = 0;
            }
        }

        //writeDebugNums(animParams.currentFrame, animParams.totalFrames);

        // TODO: Add a check to make sure we don't do this
        // for infinity?? Like only skip a couple of frames
        // and then move on.
        updatedFrames = false;
        while(animParams.currentFrame != nextFrameNum) {

            if (animParams.flags & ANIM_FLAG_WANTS_FADES) {
                // Move the next to last
                pixels.copyNextToLast();
#if ANIMATE_SERVOS
                servos.copyNextToLast();
#endif // #if ANIMATE_SERVOS
            }

            switch(currentAnim) {
                ANIMATION_DRAWS
            }

            // Loop
            animParams.currentFrame++;

            // Rollover in a loop that continues in the same
            // direction.
            // TODO: Add the ability to reverse direction?
            if (animParams.currentFrame >= animParams.totalFrames) {
                animParams.currentFrame = 0;
            }

            if (animParams.currentFrame == 1) {
                if (animParams.flags & (ANIM_FLAG_SKIP_FIRST_FADE) ) {
                    pixels.copyNextToLast();
#if ANIMATE_SERVOS
                    servos.copyNextToLast();
#endif // #if ANIMATE_SERVOS
                }
            }
            animParams.lastDrawAt = now;
            animParams.elapsedSinceLastDraw = 0;
            updatedFrames = true;
        }
        if (animParams.flags & ANIM_FLAG_WANTS_FADES) {
            if (updatedFrames) {
                // Since next was copied to last, just write out last
                pixels.copyLastToCurrent();

#if ANIMATE_SERVOS
                servos.copyLastToCurrent();
#endif // #if ANIMATE_SERVOS

                lastFrameAt = now;
            } else {
                // Interpolate between old frame time and now
                uint8_t distance = ((now - lastFrameAt) << 8) / adjustedFrameLength;
                pixels.fadeIntoCurrent( distance );

#if ANIMATE_SERVOS
                servos.fadeIntoCurrent(distance);
#endif // #if ANIMATE_SERVOS

            }
        }
    }

    //////////////////

    // Now do we overlay that with something???
    // if (overlayAnim) {
    //     doOverlay();
    // }

    // Set white front light
    // for(int i=32; i<37; i++) {
    //     pixels.setPixel(i, 0xffffff, PF_CURRENT_FRAME);
    // }

    // Assume work was done
    uint32_t txSpent = pixels.send();

    if (txSpent) {
        // Adjust all the "at" times to disappear a few ms. Like probably
        // about 3 or 4 on a big thing
        txSpent = txSpent / 1000;
        lastFrameAt -= txSpent;
        animParams.startedAt -= txSpent;
        animParams.lastDrawAt -= txSpent;
    }

#if ANIMATE_SERVOS
    servos.send();
#endif // #if ANIMATE_SERVOS

}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t
Animator::colorWheel(uint8_t WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
        return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void
Animator::startAnimation(animName_t animNum) {

    animParams.currentFrame = 0xffffffff;
    animParams.startedAt = millis();
    animParams.flags = 0;
    animParams.maxTime = 0;

    switch(animNum) {
        ANIMATIONS_BEGIN
        
        // Default is all off
        default:
            pixels.setAllPixels(0, 0, 0);
            animParams.totalFrames = 0;
            break;
    }

    // Reset the animation
    currentAnim = animNum;
    updateSpeed();

    if (animParams.flags & ANIM_FLAG_WANTS_FADES) {
        // Call draw once so that we get a frame to start with.

        // Then to make sure we start on the NEXT frame right away,
        // it is easiest to just pretend we have vaulted into the future
        // by 1 frame worth. That means frame 0 is drawn into next already
        // (and potentially some weird fade shit happened), but now
        // we will draw frame 1 copying 0 into place and stuff.
        animParams.startedAt -= adjustedFrameLength;
    }
}

animName_t 
Animator::currentAnimation() {
    return currentAnim;
}


void
Animator::updateSpeed() {
    adjustedFrameLength = (speedMultiplier * (animParams.frameLength << 8)) >> 16;
}

void
Animator::nextAnimation() {
    animName_t nextAnim = (animName_t)(currentAnim + 1);
    if (nextAnim == ANIM_LAST) {
        nextAnim = (animName_t)(ANIM_NONE + 1);
    }
    
    startAnimation(nextAnim);
}

#include "anims_funcs.h"

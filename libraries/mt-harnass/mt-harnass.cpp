
#include <mt-harnass.h>

#include <mtui.h>
extern MTUI ui;


#include "anims.h"

#define POWER_ARM_COLOR 0x808000
// #define POWER_ARM_COLOR 0x00ff00

////////////

void writeDebugNums(uint32_t a, uint32_t b) {
    char buf[10];

    uView.setCursor(40, 0);
    sprintf(buf, "%d", a);
    uView.print(buf);

    uView.setCursor(40, 8);
    sprintf(buf, "%d", b);
    uView.print(buf);

    uView.display();
}

///////////

MTHarnass::MTHarnass(uint8_t sashPin, uint8_t armPin) 
    : sash(SASH_COUNT, sashPin, NEO_GRB + NEO_KHZ800),
      arm(ARM_COUNT, armPin, armPin+1)
{
    memset(&animParams, 0, sizeof(animParams_t));

    currentAnim = ANIM_NONE;

    sColPos = 0;
    selectedColor = colorWheel(sColPos);
}

void MTHarnass::begin() {
    sash.begin();
    sash.setBrightness(128);

    //arm.updatePins(5);
    arm.begin();
    // TODO: Add brightness capability to LPD8806 library
    arm.setBrightness(10);
}

#define ANIM_DRAW(name) case ANIM_##name: name##_drawFrame(); break;

void MTHarnass::loop() {

    uint32_t now = millis();

    if (animParams.totalFrames != 0 && animParams.frameLength != 0) {
        // Which frame SHOULD we be on?

        uint32_t elapsedTime = now - animParams.startedAt;
        // Using millis so ignoring rollover. Gives us 70 days or so.

        uint32_t nextFrameTime = (elapsedTime / adjustedFrameLength) % animParams.totalFrames;

        writeDebugNums(animParams.currentFrame, animParams.totalFrames);

        // TODO: Add a check to make sure we don't do this
        // for infinity?? Like only skip a couple of frames
        // and then move on.
        bool updatedFrames = FALSE;
        while(animParams.currentFrame != nextFrameTime) {

            if (animParams.wantsFades) {
                // Move the next to last
                memcpy(lastFrame, nextFrame, sizeof(lastFrame));
            }

            switch(currentAnim) {
                case ANIM_ALL_BLINK:
                    BLINK_drawFrame();
                    break;

                ANIM_DRAW(FLOOD)
                ANIM_DRAW(HRAINBOW)
                ANIM_DRAW(TRACER)
                ANIM_DRAW(RAND_MOVER)
                ANIM_DRAW(RAND_ALL)
                ANIM_DRAW(RAND_BRIGHT)
            }

            // Loop
            animParams.currentFrame++;

            // Rollover in a loop that continues in the same
            // direction.
            // TODO: Add the ability to reverse direction?
            if (animParams.currentFrame >= animParams.totalFrames) {
                animParams.currentFrame = 0;
            }
            updatedFrames = TRUE;
        }
        if (animParams.wantsFades) {
            if (updatedFrames) {
                // Just write out the old one
                // TODO: memcpy eh???

                // Arm is before sash                
                for(int i=0, offset=0; i<ARM_COUNT; i++, offset += 3) {
                    arm.setPixelColor(i, lastFrame[offset], lastFrame[offset+1], lastFrame[offset+2]);
                }

                for(int i=0, offset=(ARM_COUNT*3); i<SASH_COUNT; i++, offset += 3) {
                    sash.setPixelColor(i, lastFrame[offset], lastFrame[offset+1], lastFrame[offset+2]);
                }
                lastFrameAt = now;
            } else {
                // Interpolate between old frame time and now

                uint16_t multi = ((now - lastFrameAt) << 8) / adjustedFrameLength;

                // Arm is before sash                
                for(int i=0, offset=0; i<ARM_COUNT; i++, offset += 3) {
                    arm.setPixelColor(i, 
                        lastFrame[offset] + ( ( (nextFrame[offset] - lastFrame[offset]) * multi ) >> 8 ),
                        lastFrame[offset+1] + ( ( (nextFrame[offset+1] - lastFrame[offset+1]) * multi ) >> 8 ),
                        lastFrame[offset+2] + ( ( (nextFrame[offset+2] - lastFrame[offset+2]) * multi ) >> 8 )

                        );
                }

                for(int i=0, offset=(ARM_COUNT*3); i<SASH_COUNT; i++, offset += 3) {
                    sash.setPixelColor(i, 
                        lastFrame[offset] + ( ( (nextFrame[offset] - lastFrame[offset]) * multi ) >> 8 ),
                        lastFrame[offset+1] + ( ( (nextFrame[offset+1] - lastFrame[offset+1]) * multi ) >> 8 ),
                        lastFrame[offset+2] + ( ( (nextFrame[offset+2] - lastFrame[offset+2]) * multi ) >> 8 )

                        );
                }

            }
        }
    }

    if (powerArmEnabled) {
        // Run the power arm animation inline here....
        uint32_t frame = (now / 60) & 0x01;

        switch(ui.regMomentary) {
            case 1: 
                if (ui.regC) {
                    solidArm(colorWheel(random(255)));
                } else {
                    solidArm(0x800000);
                }
                powerArmIsOn = true;
                break;

            case 2:
                if (ui.regC) {
                    solidArm(selectedColor);
                } else {
                    solidArm(0x008000);
                }
                powerArmIsOn = true;
                break;

            case 3:
                if (frame) {
                    solidArm(POWER_ARM_COLOR);
                    powerArmIsOn = true;
                } else {
                    solidArm(0);
                    powerArmIsOn = false;
                }
                break;

            default:
                if (powerArmIsOn) {
                    solidArm(0);
                    powerArmIsOn = false;
                }
                break;
        }

    } else {
        if (powerArmIsOn) {
            // Clear it
            solidArm(0);
            powerArmIsOn = false;
        }
    }

    // Assume work was done
    sash.show();
    arm.show();
}

void MTHarnass::solidArm(uint32_t color) {
    for(uint8_t i=0; i<arm.numPixels(); i++) {
        arm.setPixelColorRGB(i, color);
    }    
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

void MTHarnass::h6Stripe(uint32_t color, uint8_t stripe, uint8_t flags) {

    if (flags & F_SASH) {
        switch(stripe) {
            case 0:
                setPixelColor(FALSE, 0, color, flags);
                setPixelColor(FALSE, 1, color, flags);
                setPixelColor(FALSE, 2, color, flags);
                setPixelColor(FALSE, 3, color, flags);
                // sash.setPixelColor(0, color);
                // sash.setPixelColor(1, color);
                // sash.setPixelColor(2, color);
                // sash.setPixelColor(3, color);
                break;
            case 1:
                setPixelColor(FALSE, 4, color, flags);
                setPixelColor(FALSE, 5, color, flags);
                setPixelColor(FALSE, 6, color, flags);
                // sash.setPixelColor(4, color);
                // sash.setPixelColor(5, color);
                // sash.setPixelColor(6, color);
                break;
            case 2:
                setPixelColor(FALSE, 7, color, flags);
                setPixelColor(FALSE, 8, color, flags);
                setPixelColor(FALSE, 10, color, flags);
                setPixelColor(FALSE, 11, color, flags);
                // sash.setPixelColor(7, color);
                // sash.setPixelColor(8, color);
                // sash.setPixelColor(10, color);
                // sash.setPixelColor(11, color);
                break;
            case 3:
                setPixelColor(FALSE, 9, color, flags);
                setPixelColor(FALSE, 12, color, flags);
                setPixelColor(FALSE, 14, color, flags);
                setPixelColor(FALSE, 13, color, flags);
                // sash.setPixelColor(9, color);
                // sash.setPixelColor(12, color);
                // sash.setPixelColor(14, color);
                // sash.setPixelColor(13, color);
                break;
            case 4:
                setPixelColor(FALSE, 15, color, flags);
                setPixelColor(FALSE, 16, color, flags);
                setPixelColor(FALSE, 17, color, flags);
                setPixelColor(FALSE, 18, color, flags);
                setPixelColor(FALSE, 19, color, flags);
                // sash.setPixelColor(15, color);
                // sash.setPixelColor(16, color);
                // sash.setPixelColor(17, color);
                // sash.setPixelColor(18, color);
                // sash.setPixelColor(19, color);
                break;
            case 5:
                setPixelColor(FALSE, 20, color, flags);
                setPixelColor(FALSE, 21, color, flags);
                setPixelColor(FALSE, 22, color, flags);
                setPixelColor(FALSE, 23, color, flags);
                // sash.setPixelColor(20, color);
                // sash.setPixelColor(21, color);
                // sash.setPixelColor(22, color);
                // sash.setPixelColor(23, color);
                break;
        }
    }

    if (flags & F_ARM) {
        char low = 1 + ((5-stripe) * 5);
        char high = low + 5;
        if (low == 1) {
            low = 0;
        }
        if (high==31) {
            high = 32;
        }

        for(uint8_t i=low; i<high; i++) {
            setPixelColor(TRUE, i, color, flags);
            // arm.setPixelColorRGB(i, color);
        }
    }
}

// There are 56 pixels starting with 0 at the wrist and ending
// with 55 at the bottom of the sash. 32 is first pixel of sash.

// If the number is in the range of 56 to 111 it will be mapped in
// the opposite direction, so pixel 56 is the same as 54.
void MTHarnass::setMappedPixelColor(int8_t pixelNum, uint32_t color, uint8_t flags) {

    if (pixelNum < 0) {
        pixelNum += (SASH_COUNT + ARM_COUNT);
        pixelNum = (SASH_COUNT + ARM_COUNT) - pixelNum + 1;
    }

    if (pixelNum > (2 * (SASH_COUNT + ARM_COUNT) - 1)) return;

    if (pixelNum > (SASH_COUNT + ARM_COUNT - 1)) {
        pixelNum -= (SASH_COUNT + ARM_COUNT - 1);
        pixelNum = (SASH_COUNT + ARM_COUNT - 1) - pixelNum;
    }

    if (pixelNum < ARM_COUNT) {
        setPixelColor(TRUE, pixelNum, color, flags);
        // setArmPixel(pixelNum, color, frame);
        // arm.setPixelColorRGB(pixelNum, color);
    } else {
        setPixelColor(FALSE, pixelNum - ARM_COUNT, color, flags);
        // sash.setPixelColor(pixelNum - ARM_COUNT, color);
    }
}

void MTHarnass::setPixelColor(bool isArm, uint8_t num, uint32_t color, uint8_t flags) {   
    uint8_t *frameToSet = NULL;

    if (flags & F_LAST) {
        frameToSet = lastFrame;
    } else if (flags & F_NEXT) {
        frameToSet = nextFrame;
    } else {
        if (isArm) {
            arm.setPixelColorRGB(num, color);                
        } else {
            sash.setPixelColor(num, color);
        }
    }

    if (frameToSet) {
        if (!isArm) {
            num += ARM_COUNT;
        }

        num *= 3;
        frameToSet[num++] = (color >> 16) & 0xff;
        frameToSet[num++] = (color >>  8) & 0xff;
        frameToSet[num] = color & 0xff;
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t MTHarnass::colorWheel(uint8_t WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return sash.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return sash.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return sash.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void MTHarnass::changeColorPos(int8_t delta) {
    sColPos += delta;
    selectedColor = colorWheel(sColPos);
}



#define ANIM_START(name)  case ANIM_##name: name##_setup(); name##_drawFrame(); break;

void MTHarnass::startAnimation(animName_t animNum) {

    animParams.currentFrame = 0xffffffff;
    animParams.startedAt = millis();

    switch(animNum) {
        case ANIM_ALL_BLINK:
            BLINK_setup();
            BLINK_drawFrame();
            break;

        ANIM_START(FLOOD)
        ANIM_START(HRAINBOW)
        ANIM_START(TRACER)
        ANIM_START(RAND_MOVER)
        ANIM_START(RAND_ALL)
        ANIM_START(RAND_BRIGHT)

        // Default is all off
        default:
            solidColor(0, 0, 0, F_BOTH);
            animParams.totalFrames = 0;
            break;
    }

    // Reset the animation
    currentAnim = animNum;
    updateSpeed();
}

void MTHarnass::changeSpeed(int16_t delta) {
    speedMultiplier += delta;
    if (speedMultiplier < 0) {
        speedMultiplier = 1;
    }
    updateSpeed();
}

void MTHarnass::resetSpeed() {
    speedMultiplier = 0x0100;
    updateSpeed();
}

void MTHarnass::updateSpeed() {

    adjustedFrameLength = (speedMultiplier * (animParams.frameLength << 8)) >> 16;
}

// This isn't strictly needed since everything is public...
void MTHarnass::brightness(uint8_t val) {
    sash.setBrightness(val);
    arm.setBrightness(val);
}

void MTHarnass::brighter(uint8_t val) {
    int16_t brightness = sash.getBrightness();
    if (brightness < 255) {
        brightness += val;
        if (brightness > 255) brightness = 255;
    }

    sash.setBrightness(brightness);
    arm.setBrightness(brightness);
}


void MTHarnass::darker(uint8_t val) {
    int16_t brightness = sash.getBrightness();
    if (brightness > 0) {
        brightness -= val;
        if (brightness < 0) brightness = 0;
    }

    sash.setBrightness(brightness);
    arm.setBrightness(brightness);
}
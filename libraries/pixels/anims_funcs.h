
#ifndef _ANIM_FUNCS_H_
#define _ANIM_FUNCS_H_

// Want JPERF numbers
#include "jperf_pixels.h"

#define ANIM_START(name, frames, len, f_val) void Animator::name##_setup() { \
    animParams.totalFrames = frames; \
    animParams.frameLength = len; \
    animParams.flags = f_val; \
 }\
 void Animator::name##_drawFrame(){\
    switch(animParams.currentFrame) {\
    	default:

#define ANIM_FRAME(num) break; \
    	case num: 

#define ANIM_END break; } }

// Alternate version which just defines a function

#define ANIM_FSTART(name, frames, len, f_val) void Animator::name##_setup() { \
    animParams.totalFrames = frames; \
    animParams.frameLength = len; \
    animParams.flags = f_val; \
 }\
 void Animator::name##_drawFrame(){

#define ANIM_FEND }




uint32_t rainbow6_colors[] = {
	0xff0000, // Red
	0xff8000, // Orange
	0xffff00, // Yellow
	0x00ff00, // Green
	0x0000ff, // Blue
	0xff00ff, // Violet (magenta)
};

uint32_t rybRainbow[] = {
0xff0000,
0xff4000,
0xff8000,
0xffbf00,
0xffff00,
0x80d419,
0x00a833,
0x158466,
0x2a5f99,
0x55308c,
0x800080,
0xbf0040
};
#define RYB_RAINBOW_NUM_COLORS 12

/////////

ANIM_START(JORDAN_START, 2, 1000, ANIM_FLAG_WANTS_FADES)
    pixels.setBrightness(255);
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(0)
    pixels.setPixel(0, 0, 64, 0, PF_NEXT_FRAME);
    pixels.setPixel(JPERF_BOUNDARY_END-1, 0, 64, 0, PF_NEXT_FRAME);

ANIM_FRAME(1)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_END

/////////

ANIM_START(JORDAN_END, 2, 1000, ANIM_FLAG_WANTS_FADES)
    pixels.setBrightness(255);
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(0)
    pixels.setPixel(0, 64, 0, 0, PF_NEXT_FRAME);
    pixels.setPixel(JPERF_BOUNDARY_END-1, 64, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(1)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_END

/////////


void Animator::JORDAN_SPARKLE_setup() {
    animParams.totalFrames = 1600;
    animParams.frameLength = 40;
    animParams.flags = ANIM_FLAG_NONE; // No fades
    animParams.maxTime = 0; // Run forever
    animReg = 0;
    pixels.setBrightness(255);
}

// Below this number will start a fade. Smaller means
// less frequently
#define J_FADE_THRESH 2
// Amount to deduct from brightness each frame. Smaller means
// fade downs take longer
#define J_FADE_DOWN 100

// Random threshold for a pixel to sparkle. Smaller means pixels
// are less likely to sparkle
#define J_SPARKLE_THRESH 10

// #define SPARKLE_THE_PIXEL pixels.setPixel(i, 245, 218, 64);
#define SPARKLE_THE_PIXEL { \
    switch(rand(4)) { \
        case 0:\
            pixels.setPixel(i, 255, 255, 27); \
            break;\
        case 1:\
            pixels.setPixel(i, 64, 255, 218); \
            break;\
        case 2:\
            pixels.setPixel(i, 245, 218, 64); \
            break;\
        case 3:\
            pixels.setPixel(i, 255, 140, 140); \
            break;\
    }\
}


void Animator::JORDAN_SPARKLE_drawFrame() {

    // Left first
    uint8_t fadeVal;
    uint8_t startPixel;
    uint8_t maxPixel;

    fadeVal = animReg & 0x000000ff;
    startPixel = 0;
    maxPixel = pixels.getNumPixels();
    // if (!fadeVal && (rand(2000) < J_FADE_THRESH)) {
    //     // Do a fade anyway. IE. Start a burst
    //     fadeVal = 255;
    // }
    // if (fadeVal) {
    //     // Doing a fade down, so keep doing that
    //     fadeVal = (fadeVal > J_FADE_DOWN) ? (fadeVal - J_FADE_DOWN) : 0;
    //     animReg = (animReg & 0xffffff00) | fadeVal;

    //     for(int i=startPixel; i<maxPixel ; i++) {
    //         // pixels.setPixel(i, fadeVal, fadeVal, fadeVal);
    //         pixels.setPixel(i, 255, 255, 255);
    //     }
    // } else {
        // Regular sparkle
        for(int i=startPixel; i<maxPixel; i++) {

            // Pixels have a small chance of being lit up
            if (rand(5000) < J_SPARKLE_THRESH) {
                SPARKLE_THE_PIXEL
            } else {
                pixels.setPixel(i, 0, 0, 0);
            }
        }         
    // }
}

#define JREGION_LEFT_WRIST      (1 << 0)
#define JREGION_LEFT_FOREARM    (1 << 1)
#define JREGION_LEFT_ELBOW      (1 << 2)
#define JREGION_LEFT_BICEP      (1 << 3)

#define JREGION_RIGHT_WRIST     (1 << 4)
#define JREGION_RIGHT_FOREARM   (1 << 5)
#define JREGION_RIGHT_ELBOW     (1 << 6)
#define JREGION_RIGHT_BICEP     (1 << 7)

#define JREGION_NECK            (1 << 8)

#define JREGION_WRISTS      (JREGION_LEFT_WRIST | JREGION_RIGHT_WRIST)
#define JREGION_FOREARMS    (JREGION_LEFT_FOREARM | JREGION_RIGHT_FOREARM)
#define JREGION_ELBOWS      (JREGION_LEFT_ELBOW | JREGION_RIGHT_ELBOW)
#define JREGION_BICEPS      (JREGION_LEFT_BICEP | JREGION_RIGHT_BICEP)

uint16_t jordanRegions[] = {
    JREGION_WRISTS,
    JREGION_FOREARMS,
    JREGION_ELBOWS,
    JREGION_BICEPS,
    JREGION_NECK
};

uint16_t jordanSingleRegions[] = {
    JREGION_LEFT_WRIST   , 
    JREGION_LEFT_FOREARM , 
    JREGION_LEFT_ELBOW   , 
    JREGION_LEFT_BICEP   , 

    JREGION_NECK         , 

    JREGION_RIGHT_BICEP  , 
    JREGION_RIGHT_ELBOW  , 
    JREGION_RIGHT_FOREARM, 
    JREGION_RIGHT_WRIST  , 
};

void setJordan(Pixels& pixels, uint16_t region, uint32_t color, uint8_t flags) {

    if (region & JREGION_RIGHT_WRIST) {
        for(int i=0; i<JPERF_BOUNDARY_WRIST_FOREARM; i++) {
            pixels.setPixel(i, color, flags);
        }
    }

    if (region & JREGION_RIGHT_FOREARM) {
        for(int i=JPERF_BOUNDARY_WRIST_FOREARM; i<JPERF_BOUNDARY_FOREARM_ELBOW; i++) {
            pixels.setPixel(i, color, flags);
        }
    }

    if (region & JREGION_RIGHT_ELBOW) {
        for(int i=JPERF_BOUNDARY_FOREARM_ELBOW; i<JPERF_BOUNDARY_ELBOW_BICEP; i++) {
            pixels.setPixel(i, color, flags);
        }
    }


    if (region & JREGION_RIGHT_BICEP) {
        for(int i=JPERF_BOUNDARY_ELBOW_BICEP; i<JPERF_BOUNDARY_BICEP_NECK; i++) {
            pixels.setPixel(i, color, flags);
        }
    }


    if (region & JREGION_NECK) {
        for(int i=JPERF_BOUNDARY_BICEP_NECK; i<JPERF_BOUNDARY_NECK_LBICEP; i++) {
            pixels.setPixel(i, color, flags);
        }
    }


    if (region & JREGION_LEFT_BICEP) {
        for(int i=JPERF_BOUNDARY_NECK_LBICEP; i<JPERF_BOUNDARY_LBICEP_LELBOW; i++) {
            pixels.setPixel(i, color, flags);
        }
    }

    if (region & JREGION_LEFT_ELBOW) {
        for(int i=JPERF_BOUNDARY_LBICEP_LELBOW; i<JPERF_BOUNDARY_LELBOW_LFOREARM; i++) {
            pixels.setPixel(i, color, flags);
        }
    }

    if (region & JREGION_LEFT_FOREARM) {
        for(int i=JPERF_BOUNDARY_LELBOW_LFOREARM; i<JPERF_BOUNDARY_LFOREARM_LWRIST; i++) {
            pixels.setPixel(i, color, flags);
        }
    }


    if (region & JREGION_LEFT_WRIST) {
        for(int i=JPERF_BOUNDARY_LFOREARM_LWRIST; i<JPERF_BOUNDARY_END; i++) {
            pixels.setPixel(i, color, flags);
        }
    }    
}


void Animator::JORDAN_RAINBOW_setup() {
    animParams.totalFrames = 12;
    animParams.frameLength = 166;
    animParams.flags = ANIM_FLAG_WANTS_FADES;
    pixels.setBrightness(255);
}

void Animator::JORDAN_RAINBOW_drawFrame() {

    for(uint8_t i = 0; i<5; i++) {
        uint8_t rIx = (animParams.currentFrame + i) % RYB_RAINBOW_NUM_COLORS;

        setJordan(pixels, jordanRegions[i], rybRainbow[rIx], PF_NEXT_FRAME);
    }
}

/////////////

void Animator::JORDAN_TRACER_setup() {
    animParams.totalFrames = JPERF_HCOUNT + 1;
    animParams.frameLength = 200;
    animParams.flags = ANIM_FLAG_WANTS_FADES;

    pixels.setBrightness(128);
}

void Animator::JORDAN_TRACER_drawFrame() {

    if (animParams.currentFrame == 0) {
        animColor = colorWheel(rand(255));
    }
    pixels.setAllPixels(0, PF_NEXT_FRAME);

    pixels.setPixel(animParams.currentFrame, animColor, PF_NEXT_FRAME);
    pixels.setPixel(JPERF_COUNT - 1 - animParams.currentFrame, animColor, PF_NEXT_FRAME);

}

/////////////

void Animator::JORDAN_RAINBOW_CALM_setup() {
    animParams.totalFrames = 12;
    animParams.frameLength = 2000;
    animParams.flags = ANIM_FLAG_WANTS_FADES;

    pixels.setBrightness(32);
}

void Animator::JORDAN_RAINBOW_CALM_drawFrame() {

    for(uint8_t i = 0; i<9; i++) {
        uint8_t rIx = (animParams.currentFrame + i) % RYB_RAINBOW_NUM_COLORS;

        setJordan(pixels, jordanSingleRegions[i], rybRainbow[rIx], PF_NEXT_FRAME);
    }
}

/////////////

#define CUFF_STEP 16

void Animator::JORDAN_RED_CUFFS_setup() {
    animParams.totalFrames = 2 * (255 / CUFF_STEP);
    animParams.frameLength = 200;
    animParams.flags = ANIM_FLAG_WANTS_FADES;

    animReg = 0;

    pixels.setBrightness(96);
    pixels.setAllPixels(0, PF_NEXT_FRAME);
}

void Animator::JORDAN_RED_CUFFS_drawFrame() {

    if (animParams.currentFrame > animParams.totalFrames/2) {
        // We are decreasing
        animReg -= CUFF_STEP;
    } else {
        animReg += CUFF_STEP;
    }

    if ((int32_t)animReg > 255) {
        animReg = 255;
    }
    if ((int32_t)animReg < 0) {
        animReg = 0;
    }

    uint32_t color = animReg << 16;
    setJordan(pixels, JREGION_WRISTS, color, PF_NEXT_FRAME);
    setJordan(pixels, JREGION_NECK, color, PF_NEXT_FRAME);
}

/////////////

// So wasteful...
bool isBoy[JPERF_COUNT];

void Animator::JORDAN_BOY_GIRL_setup() {
    animParams.totalFrames = 10000;
    animParams.frameLength = 100;
    animParams.flags = ANIM_FLAG_WANTS_FADES;

    animReg = 0;
    pixels.setBrightness(32);

    for(int i=0; i<JPERF_COUNT; i++) {
        isBoy[i] = false;
    }
}

#define TO_CHANGE_RAND    300
#define TO_CHANGE_THRESH  4
void Animator::JORDAN_BOY_GIRL_drawFrame() {

    bool homogenous = true;
    for(int i=0; i<JPERF_COUNT; i++) {

        // Decide if we want to switch it
        if (animReg) {
            // Goal is to make all boys
            if (!isBoy[i]) {
                homogenous = false;
                if ( rand(TO_CHANGE_RAND) < TO_CHANGE_THRESH) {
                    isBoy[i] = true;
                }
            }
        } else {
            // Goal is to make all girls
            if (isBoy[i]) {
                homogenous = false;
                if ( rand(TO_CHANGE_RAND) < TO_CHANGE_THRESH) {
                    isBoy[i] = false;
                }
            }
        }

        // Render it
        if (isBoy[i]) {
            // pixels.setPixel(i, 145, 168, 209, PF_NEXT_FRAME);
            pixels.setPixel(i, 115, 149, 209, PF_NEXT_FRAME);
        } else {
            // pixels.setPixel(i, 247, 202, 201, PF_NEXT_FRAME);
            pixels.setPixel(i, 247, 148, 146, PF_NEXT_FRAME);
        }
    }

    if (homogenous) {
        // Opportunity to switch our goal
        if (rand(50) < 10) {
            animReg = !animReg;
        }
    }
}


/////////////

#define CUFF_STEP 16

#define MARDI_GRAS_GOLD   0x00B07E09
#define MARDI_GRAS_GREEN  0x00045716
#define MARDI_GRAS_PURPLE 0x002D0638

uint32_t mardiColors[] = {
    MARDI_GRAS_PURPLE,
    MARDI_GRAS_PURPLE,
    MARDI_GRAS_GOLD,
    MARDI_GRAS_GREEN,
    MARDI_GRAS_GREEN,
};
// uint32_t mardiColors[] = {
//     MARDI_GRAS_PURPLE,
//     MARDI_GRAS_PURPLE,
//     MARDI_GRAS_PURPLE,
//     MARDI_GRAS_GOLD,
//     MARDI_GRAS_GOLD,
//     MARDI_GRAS_GOLD,
//     MARDI_GRAS_GREEN,
//     MARDI_GRAS_GREEN,
//     MARDI_GRAS_GREEN,
// };

void Animator::JORDAN_MARDI_GRAS_setup() {
    animParams.totalFrames = 5;
    animParams.frameLength = 700;
    animParams.flags = ANIM_FLAG_WANTS_FADES;

    animReg = 0;

    pixels.setBrightness(128);
}

void Animator::JORDAN_MARDI_GRAS_drawFrame() {

    uint32_t first, second;
    animReg = animParams.currentFrame;

    for(uint8_t i=0; i<5; i++) {
        uint16_t region = i + animParams.currentFrame;
        if (region > 4) {
            region -= 5;
        }

        setJordan(pixels, jordanRegions[region], mardiColors[i], PF_NEXT_FRAME);
    }

    // if (animParams.currentFrame % 2) {
    //     first = MARDI_GRAS_PURPLE;
    //     second = MARDI_GRAS_GREEN;
    // } else {
    //     first = MARDI_GRAS_GREEN;
    //     second = MARDI_GRAS_PURPLE;
    // }
    // setJordan(pixels, JREGION_WRISTS, first, PF_CURRENT_FRAME);
    // setJordan(pixels, JREGION_ELBOWS, first, PF_CURRENT_FRAME);
    // setJordan(pixels, JREGION_FOREARMS, second, PF_CURRENT_FRAME);
    // setJordan(pixels, JREGION_BICEPS, second, PF_CURRENT_FRAME);

    //setJordan(pixels, JREGION_NECK, MARDI_GRAS_GOLD, PF_NEXT_FRAME);

}


// void Animator::FLOOD_setup() {
// 	animParams.totalFrames = pixels.getNumPixels();
// 	animParams.frameLength = 100;
// 	animParams.flags = ANIM_FLAG_WANTS_FADES;

// 	pixels.setAllPixels(0,0,0, PF_NEXT_FRAME);
// }

// void Animator::FLOOD_drawFrame() {
//     if (!animParams.currentFrame) {
// 	    animColor = colorWheel(random(255));
// 	    animReg = random(2);
//         animReg = 0;
//     }

// 	if (animParams.currentFrame < pixels.getNumPixels()) {
// 		// Add a bar
// 		pixels.setPixel(animReg ? 
// 		    (pixels.getNumPixels() - animParams.currentFrame - 1)
// 		    : animParams.currentFrame
// 		    , animColor, PF_NEXT_FRAME);
// 	} else {
// 	    // Remove a bar
// 		pixels.setPixel(animReg ? 
// 		    (pixels.getNumPixels() - animParams.currentFrame - 1)
// 		    : animParams.currentFrame
// 		    , 0, PF_NEXT_FRAME);

// // 		pixels.setPixel(animParams.currentFrame, 0, PF_NEXT_FRAME);
// 	}
// }



// void Animator::RAINBOW_setup() {
// 	animParams.totalFrames = pixels.getNumPixels();
// 	animParams.frameLength = 1000;
// 	animParams.flags = ANIM_FLAG_WANTS_FADES;

// 	// Color offset
// 	animColor = 0;
// }

// void Animator::RAINBOW_drawFrame() {

// 	char offset = animColor;
// 	for(int i=0; i<animParams.totalFrames; i+=4) {
// 	    uint32_t c = rainbow6_colors[offset++];
// 		if (offset >= 6) {
// 			offset = 0;
// 		}

// 	    pixels.setPixel(i, c, PF_NEXT_FRAME);
// 	    if (i+1 < animParams.totalFrames) {
// 	        pixels.setPixel(i+1, c, PF_NEXT_FRAME);
// 	    }
// 	    if (i+2 < animParams.totalFrames) {
// 	        pixels.setPixel(i+2, c, PF_NEXT_FRAME);
// 	    }
// 	    if (i+3 < animParams.totalFrames) {
// 	        pixels.setPixel(i+3, c, PF_NEXT_FRAME);
// 	    }

// 	}
	
// 	animColor++;
// 	if (animColor >= 6) {
// 		animColor = 0;
// 	}
// }

// /////////
// void Animator::BRIGHT_FO_setup() {
// 	animParams.totalFrames = 1600;
// 	animParams.frameLength = 10;
// 	animParams.flags = ANIM_FLAG_NONE;
// }

// void Animator::BRIGHT_FO_drawFrame() {

//     if (animParams.currentFrame == 0) {
//         // Setup a new color
//         animColor = random(255);
// 	   // animColor = colorWheel(random(255));

//         for(int i=0; i< pixels.getNumPixels(); i++) {
//             uint32_t c = colorWheel(animColor + random(16));
//             uint16_t r = (c >> 16) & 0x00ff;
//             uint16_t g = (c >>  8) & 0x00ff;
//             uint16_t b = (c      ) & 0x00ff;

//             uint16_t brightness = random(255);
//             r = (r * brightness) >> 8;
//             g = (g * brightness) >> 8;
//             b = (b * brightness) >> 8;
            
//             pixels.setPixel(i, r, g, b, PF_LAST_FRAME);
//         }
//         pixels.copyLastToCurrent();
//         return;
//     }
    
//     // next is some lesser portion of last
//     for(int i=0; i< pixels.getNumPixels(); i++) {
//         uint32_t factor = ((animParams.totalFrames - animParams.currentFrame) << 16) / animParams.totalFrames;
        
//         uint32_t c = pixels.getPixel(i, PF_LAST_FRAME);
//         uint32_t r = (c >> 16) & 0x00ff;
//         uint32_t g = (c >>  8) & 0x00ff;
//         uint32_t b = (c      ) & 0x00ff;

//         r = (r * factor) >> 15;
//         g = (g * factor) >> 15;
//         b = (b * factor) >> 15;
        
//         pixels.setPixel(i, r, g, b, PF_CURRENT_FRAME);
//     }

// }


// /////////
// void Animator::RANDO_FADE_setup() {
// 	animParams.totalFrames = 1600;
// 	animParams.frameLength = 10;
// 	animParams.flags = ANIM_FLAG_NONE;
// }

// void Animator::RANDO_FADE_drawFrame() {

//     if (animParams.currentFrame == 0) {
//         pixels.copyNextToLast();
        
//         // Setup new colors on next, and we will fade from last to next
//         for(int i=0; i< pixels.getNumPixels(); i++) {
//     	    animColor = colorWheel(random(255));

//             uint16_t r = (animColor >> 16) & 0x00ff;
//             uint16_t g = (animColor >>  8) & 0x00ff;
//             uint16_t b = (animColor      ) & 0x00ff;

//             uint16_t brightness = 128 + random(128);
//             r = (r * brightness) >> 8;
//             g = (g * brightness) >> 8;
//             b = (b * brightness) >> 8;
            
//             pixels.setPixel(i, r, g, b, PF_NEXT_FRAME);
//         }
//         return;
//     }
    
//     // next is some lesser portion of last
//     uint32_t factor = (animParams.currentFrame << 8) / animParams.totalFrames;
//     pixels.fadeIntoCurrent(factor);
// }


// /////////
// void Animator::SPARKLE_setup() {
// 	animParams.totalFrames = 1600;
// 	animParams.frameLength = 10;
// 	animParams.flags = ANIM_FLAG_NONE;
// 	animParams.maxTime = 30000;
// }

// void Animator::SPARKLE_drawFrame() {

//     // Setup new colors on next, and we will fade from last to next
//     for(int i=0; i< pixels.getNumPixels(); i++) {
        
//         // Pixels have a small chance of being lit up
//         if (random(1000) < 50) {
//             pixels.setPixel(i, 255, 255, 255);
//         } else {
//             pixels.setPixel(i, 0, 0, 0);
//         }
//     }
// }


// /////////
// ANIM_FSTART(WHITE, 2, 1000, ANIM_FLAG_NONE)

//     pixels.setAllPixels(255, 255, 255);

// ANIM_FEND



// /////////
// ANIM_FSTART(HALF_WHITE, 2, 1000, ANIM_FLAG_NONE)

//     for(int i=0; i<pixels.getNumPixels(); i += 2) {
//         pixels.setPixel(i, 255, 255, 255);
//         if (i+1 < pixels.getNumPixels()) {
//             pixels.setPixel(i+1, 0, 0, 0);
//         }
//     }

// ANIM_FEND


// /////////

// #define SCAN_COLOR 0x0000ff
// #define BLACK 0x000000

// #define ROBOT_PIXELS_HEART_START 10
// #define ROBOT_PIXELS_HEART_END 27

// #define ROBOT_HEART_BRIGHT 0xff0000
// #define ROBOT_HEART_DIM 0xff0000

// #define setHeart(color) { \
//     for(int i=ROBOT_PIXELS_HEART_START; i<ROBOT_PIXELS_HEART_END; i++) { \
//         pixels.setPixel(i, color, PF_NEXT_FRAME); \
//     } \
// }

// #define setEyes(color) { \
//     for(int i=0; i<10; i++) { \
//         pixels.setPixel(i, color, PF_NEXT_FRAME); \
//     } \
// }


// ANIM_START(ROBOTX, 10, 200, ANIM_FLAG_WANTS_FADES )
//     pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
//     servos.setServo(0, 0, PF_NEXT_FRAME);

// ANIM_FRAME(0)
//     pixels.setPixel(9, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);

//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

// ANIM_FRAME(1)
//     pixels.setPixel(animParams.currentFrame-1, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);
//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

// ANIM_FRAME(2)
//     pixels.setPixel(animParams.currentFrame-1, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);
//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

// ANIM_FRAME(3)
//     pixels.setPixel(animParams.currentFrame-1, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);
//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

// ANIM_FRAME(4)
//     pixels.setPixel(animParams.currentFrame-1, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);
//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

//     setHeart(ROBOT_HEART_BRIGHT)

// ANIM_FRAME(5)
//     pixels.setPixel(animParams.currentFrame-1, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);
//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

//     setHeart(ROBOT_HEART_DIM)

// ANIM_FRAME(6)
//     pixels.setPixel(animParams.currentFrame-1, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);
//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

// ANIM_FRAME(7)
//     pixels.setPixel(animParams.currentFrame-1, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);
//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

//     setHeart(ROBOT_HEART_BRIGHT)

// ANIM_FRAME(8)
//     pixels.setPixel(animParams.currentFrame-1, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);
//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

// ANIM_FRAME(9)
//     pixels.setPixel(animParams.currentFrame-1, 0, 0, 0, PF_NEXT_FRAME);
//     pixels.setPixel(animParams.currentFrame, SCAN_COLOR, PF_NEXT_FRAME);
//     servos.setServo(0, animParams.currentFrame * 10, PF_NEXT_FRAME);

//     setHeart(0x000000)


// ANIM_END


// /////////

// // void Animator::ROBOT_ONE_setup() {
// //     animParams.totalFrames = 1600;
// //     animParams.frameLength = 10;
// //     animParams.flags = ANIM_FLAG_NONE; // No fades
// //     animParams.maxTime = 0; // Run forever
// //     animReg = 0;
// // }

// // void Animator::ROBOT_ONE_drawFrame() {

// // }

// /////////

// #define HS_PUPIL 0x0080ff
// #define HS_PUPIL 0xff0000

// uint8_t heartDot(uint8_t ix) {
//     switch (ix) {
//         case 0:
//             return 26;

//         case 1:
//             return 12;

//         case 2:
//             return 13;

//         case 3:
//             return 16;

//         case 4:
//             return 24;

//         case 5:
//             return 18;
//     }

//     return 99;
// }

// void randomRainbowHeartDots(Pixels& pixels, uint8_t flags) {


//     setHeart(0);
//     if (rand(2)) {
//         pixels.setPixel(11, rainbow6_colors[rand(6)], flags);
//         pixels.setPixel(12, rainbow6_colors[rand(6)], flags);

//         pixels.setPixel(20, rainbow6_colors[rand(6)], flags);
//     } else {
//         pixels.setPixel(26, rainbow6_colors[rand(6)], flags);
//         pixels.setPixel(14, rainbow6_colors[rand(6)], flags);

//     }

//     // if (rand(2)) {
//     //     pixels.setPixel(11, rybRainbow[rand(RYB_RAINBOW_NUM_COLORS)], flags);
//     //     pixels.setPixel(12, rybRainbow[rand(RYB_RAINBOW_NUM_COLORS)], flags);

//     //     pixels.setPixel(20, rybRainbow[rand(RYB_RAINBOW_NUM_COLORS)], flags);
//     // } else {
//     //     pixels.setPixel(26, rybRainbow[rand(RYB_RAINBOW_NUM_COLORS)], flags);
//     //     pixels.setPixel(14, rybRainbow[rand(RYB_RAINBOW_NUM_COLORS)], flags);

//     // }


//     // for(int i=1; i<3; i++) {
//     //     uint8_t colorIx = rand(RYB_RAINBOW_NUM_COLORS);

//     //     pixels.setPixel(heartDot(i), rybRainbow[colorIx], flags);
//     // }
// }

// #define HS_EYE_WHITE 0x202020
// #define HS_EYE_PUPIL 0x800000


// #define SW_BASE 0x802020
// #define SW_SWELL_1 0xC00000
// #define SW_SWELL_2 0x800000

// void leftEyeOpen(Pixels& pixels, uint8_t flags) {
//     pixels.setPixel(5, HS_EYE_WHITE, flags);
//     pixels.setPixel(6, HS_EYE_WHITE, flags);
//     pixels.setPixel(7, HS_EYE_PUPIL, flags);
//     pixels.setPixel(8, HS_EYE_WHITE, flags);
//     pixels.setPixel(9, HS_EYE_WHITE, flags);
// }

// void rightEyeOpen(Pixels& pixels, uint8_t flags) {
//     pixels.setPixel(0, HS_EYE_WHITE, flags);
//     pixels.setPixel(1, HS_EYE_WHITE, flags);
//     pixels.setPixel(2, HS_EYE_PUPIL, flags);
//     pixels.setPixel(3, HS_EYE_WHITE, flags);
//     pixels.setPixel(4, HS_EYE_WHITE, flags);
// }

// ANIM_START(ROBOT_HEAD_SHRUGS, 9, 500, ANIM_FLAG_WANTS_FADES )
//     // pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
//     servos.setServo(0, 90, PF_NEXT_FRAME);
//     // setHeart(BLACK);
//     animParams.maxTime = 19010; // 4 cycles

//     // Used for heart fill
//     animColor = SW_BASE;

// ANIM_FRAME(0)
//     servos.setServo(0, 90, PF_NEXT_FRAME);
//     setEyes(HS_EYE_WHITE);
//     pixels.setPixel(2, HS_EYE_PUPIL, PF_NEXT_FRAME);
//     pixels.setPixel(7, HS_EYE_PUPIL, PF_NEXT_FRAME);
//     // randomRainbowHeartDots(pixels, PF_NEXT_FRAME);
//     setHeart(BLACK);

// ANIM_FRAME(1)
//     servos.setServo(0, 110, PF_NEXT_FRAME);
//     setEyes(HS_EYE_WHITE);
//     pixels.setPixel(1, HS_EYE_PUPIL, PF_NEXT_FRAME);
//     pixels.setPixel(6, HS_EYE_PUPIL, PF_NEXT_FRAME);

//     pixels.setPixel(11, animColor, PF_NEXT_FRAME);
//     pixels.setPixel(12, animColor, PF_NEXT_FRAME);

// // Pause 2 frames
// ANIM_FRAME(2)
//     pixels.setPixel(10, animColor, PF_NEXT_FRAME);
//     pixels.setPixel(13, animColor, PF_NEXT_FRAME);

// ANIM_FRAME(3)
//     pixels.setPixel(26, animColor, PF_NEXT_FRAME);
//     pixels.setPixel(14, animColor, PF_NEXT_FRAME);

// ANIM_FRAME(4)
//     servos.setServo(0, 90, PF_NEXT_FRAME);
//     setEyes(HS_EYE_WHITE);
//     pixels.setPixel(2, HS_EYE_PUPIL, PF_NEXT_FRAME);
//     pixels.setPixel(7, HS_EYE_PUPIL, PF_NEXT_FRAME);

//     pixels.setPixel(25, animColor, PF_NEXT_FRAME);
//     pixels.setPixel(15, animColor, PF_NEXT_FRAME);

// ANIM_FRAME(5)
//     servos.setServo(0, 70, PF_NEXT_FRAME);
//     setEyes(HS_EYE_WHITE);
//     pixels.setPixel(3, HS_EYE_PUPIL, PF_NEXT_FRAME);
//     pixels.setPixel(8, HS_EYE_PUPIL, PF_NEXT_FRAME);

//     pixels.setPixel(24, animColor, PF_NEXT_FRAME);
//     pixels.setPixel(16, animColor, PF_NEXT_FRAME);


// // Pause 2 frames
// ANIM_FRAME(6)
//     pixels.setPixel(23, animColor, PF_NEXT_FRAME);
//     pixels.setPixel(17, animColor, PF_NEXT_FRAME);

// ANIM_FRAME(7)
//     pixels.setPixel(22, animColor, PF_NEXT_FRAME);
//     pixels.setPixel(18, animColor, PF_NEXT_FRAME);

// // Back towards center
// ANIM_FRAME(8)
//     servos.setServo(0, 90, PF_NEXT_FRAME);
//     setEyes(HS_EYE_WHITE);
//     pixels.setPixel(3, HS_EYE_PUPIL, PF_NEXT_FRAME);
//     pixels.setPixel(8, HS_EYE_PUPIL, PF_NEXT_FRAME);

//     pixels.setPixel(21, animColor, PF_NEXT_FRAME);
//     pixels.setPixel(19, animColor, PF_NEXT_FRAME);
//     pixels.setPixel(20, animColor, PF_NEXT_FRAME);


// ANIM_END




// ////////


// ANIM_START(ROBOT_HEART_BEAT, 7, 143, ANIM_FLAG_WANTS_FADES )
//     // pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
//     // servos.setServo(0, 90, PF_NEXT_FRAME);
//     // setHeart(BLACK);
//     animParams.maxTime = 10000; 

// ANIM_FRAME(0)
//     servos.setServo(0, 90, PF_NEXT_FRAME);
//     setEyes(HS_EYE_WHITE);
//     pixels.setPixel(2, HS_EYE_PUPIL, PF_NEXT_FRAME);
//     pixels.setPixel(7, HS_EYE_PUPIL, PF_NEXT_FRAME);

//     // randomRainbowHeartDots(pixels, PF_NEXT_FRAME);
//     setHeart(SW_BASE);

// ANIM_FRAME(1)

// ANIM_FRAME(2)

// ANIM_FRAME(3)

// ANIM_FRAME(4)
//     setHeart(SW_SWELL_1);

//     if (rand(5) == 0) {
//         pixels.setPixel(0, BLACK, PF_NEXT_FRAME);
//         pixels.setPixel(1, BLACK, PF_NEXT_FRAME);
//         pixels.setPixel(2, BLACK, PF_NEXT_FRAME);
//         pixels.setPixel(3, BLACK, PF_NEXT_FRAME);
//         pixels.setPixel(4, BLACK, PF_NEXT_FRAME);
//     }


// ANIM_FRAME(5)
//     setHeart(SW_BASE);

//     setEyes(HS_EYE_WHITE);
//     pixels.setPixel(2, HS_EYE_PUPIL, PF_NEXT_FRAME);
//     pixels.setPixel(7, HS_EYE_PUPIL, PF_NEXT_FRAME);

// ANIM_FRAME(6)
//     setHeart(SW_SWELL_2);

// ANIM_END




// ANIM_START(ROBOT_SLEEP, 10, 1000, ANIM_FLAG_WANTS_FADES )
//     // pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
//     // servos.setServo(0, 90, PF_NEXT_FRAME);
//     // setHeart(BLACK);
//     animParams.maxTime = 9500; // 2 cycles

// ANIM_FRAME(0)
//     servos.setServo(0, 90, PF_NEXT_FRAME);
//     setEyes(HS_EYE_WHITE);
//     pixels.setPixel(2, HS_EYE_PUPIL, PF_NEXT_FRAME);
//     pixels.setPixel(7, HS_EYE_PUPIL, PF_NEXT_FRAME);

//     // randomRainbowHeartDots(pixels, PF_NEXT_FRAME);
//     setHeart(SW_BASE);

// ANIM_FRAME(1)
//     setEyes(0x050510);
//     setHeart(0x202040);

// ANIM_FRAME(2)
//     servos.setServo(0, 60, PF_NEXT_FRAME);
//     setEyes(BLACK);
//     setHeart(BLACK);

// ANIM_FRAME(3)

// ANIM_FRAME(4)

// ANIM_FRAME(5)

// ANIM_FRAME(6)

// ANIM_FRAME(7)

// ANIM_FRAME(8)

// ANIM_FRAME(9)
//     servos.setServo(0, 100, PF_NEXT_FRAME);

// ANIM_END




// ANIM_START(ROBOT_ONE_EYE_WAKE, 5, 800, ANIM_FLAG_WANTS_FADES )
//     // pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
//     // servos.setServo(0, 90, PF_NEXT_FRAME);
//     // setHeart(BLACK);
//     animParams.maxTime = 0; // 2 cycles

// ANIM_FRAME(0)
//     if (!rand(2)) {
//         rightEyeOpen(pixels, PF_NEXT_FRAME);
//     }

// ANIM_FRAME(1)
//     setEyes(BLACK);
//     setHeart(BLACK);

// ANIM_FRAME(2)

// ANIM_FRAME(3)

// ANIM_FRAME(4)
//     // Decide if we are done or not?
//     if (!rand(6)) {
//         animParams.maxTime = 10;
//     }

// ANIM_END



// void setHeartRow(Pixels& pixels, uint8_t row, uint32_t color, uint8_t flags) {
//     switch(row) {
//         case 6:
//             pixels.setPixel(20, color, flags);
//             break;

//         case 5:
//             pixels.setPixel(21, color, flags);
//             pixels.setPixel(19, color, flags);
//             break;

//         case 4:
//             pixels.setPixel(22, color, flags);
//             pixels.setPixel(18, color, flags);
//             break;
//         case 3:
//             pixels.setPixel(23, color, flags);
//             pixels.setPixel(17, color, flags);
//             break;

//         case 2:
//             pixels.setPixel(24, color, flags);
//             pixels.setPixel(11, color, flags);
//             pixels.setPixel(12, color, flags);
//             pixels.setPixel(16, color, flags);
//             break;
//         case 1:
//             pixels.setPixel(25, color, flags);
//             pixels.setPixel(10, color, flags);
//             pixels.setPixel(13, color, flags);
//             pixels.setPixel(15, color, flags);
//             break;

//         case 0:
//             pixels.setPixel(26, color, flags);
//             pixels.setPixel(14, color, flags);
//             break;
//     }
// }


// void Animator::ROBOT_RAINBOW_WAKE_FILL_setup() {
//     animParams.totalFrames = 7;
//     animParams.frameLength = 500;
//     animParams.flags = ANIM_FLAG_WANTS_FADES; // No fades
//     animParams.maxTime = 3750; // Run forever
//     animReg = 0;

//     servos.setServo(0, 60, PF_NEXT_FRAME);
//     setHeart(BLACK);
// }

// void Animator::ROBOT_RAINBOW_WAKE_FILL_drawFrame() {
//     if (animParams.currentFrame < 0 || animParams.currentFrame >= animParams.totalFrames) return;

//     for(int8_t i=0; i<=animParams.currentFrame; i++) {
//         setHeartRow(pixels, 6-i, rybRainbow[animParams.currentFrame - i], PF_NEXT_FRAME);
//     }
// }

// void Animator::ROBOT_RAINBOW_WAKE_ROT_setup() {
//     animParams.totalFrames = 1600;
//     animParams.frameLength = 200;
//     animParams.flags = ANIM_FLAG_WANTS_FADES; // No fades
//     animParams.maxTime = 10000; 

//     // servos.setServo(0, 100, PF_NEXT_FRAME);
//     // setHeart(BLACK);
//     setEyes(BLACK);
// }

// void Animator::ROBOT_RAINBOW_WAKE_ROT_drawFrame() {

//     if (animParams.currentFrame < 0 || animParams.currentFrame >= animParams.totalFrames) return;

//     for(int8_t i=0; i<7; i++) {
//         int8_t ix = ((animParams.currentFrame) % RYB_RAINBOW_NUM_COLORS) - i - 6;
//         if (ix < 0) {
//             ix += RYB_RAINBOW_NUM_COLORS;
//         }

//         setHeartRow(pixels, 6-i, rybRainbow[ix], PF_NEXT_FRAME);        
//     }

//     for(int8_t px=0; px<10; px++) {
//         int8_t cix = animParams.currentFrame + px;
//         while(cix >= RYB_RAINBOW_NUM_COLORS) {
//             cix -= RYB_RAINBOW_NUM_COLORS;
//         }

//         pixels.setPixel(px, rybRainbow[cix], PF_NEXT_FRAME);
//     }

//     if (animParams.currentFrame < 6) {
//         uint8_t pos = 100 - ((6-animParams.currentFrame) * 5);
//         servos.setServo(0, pos, PF_NEXT_FRAME);
//     }

//     // for(int8_t i=0; i<=animParams.currentFrame; i++) {
//     //     setHeartRow(pixels, 6-i, rybRainbow[animParams.currentFrame - i], PF_NEXT_FRAME);
//     // }
//     // setHeartRow(pixels, 6-animParams.currentFrame, rybRainbow[animParams.currentFrame], PF_NEXT_FRAME);
//     // setEyes(BLACK);
//     // pixels.setPixel(animParams.currentFrame, 0xff0000, PF_NEXT_FRAME);
// }

/*
/////////
void Animator::JORDAN_RUNWAY_setup() {
    animParams.totalFrames = 1600;
    animParams.frameLength = 10;
    animParams.flags = ANIM_FLAG_NONE; // No fades
    animParams.maxTime = 0; // Run forever
    animReg = 0;
}

#define J_FADE_THRESH 5
#define J_FADE_DOWN 50
#define J_SPARKLE_THRESH 10

// #define SPARKLE_THE_PIXEL pixels.setPixel(i, 245, 218, 64);
#define SPARKLE_THE_PIXEL { \
    switch(rand(4)) { \
        case 0:\
            pixels.setPixel(i, 255, 255, 27); \
            break;\
        case 1:\
            pixels.setPixel(i, 64, 255, 218); \
            break;\
        case 2:\
            pixels.setPixel(i, 245, 218, 64); \
            break;\
        case 3:\
            pixels.setPixel(i, 255, 140, 140); \
            break;\
    }\
}


void Animator::JORDAN_RUNWAY_drawFrame() {

    // Left first
    uint8_t fadeVal;
    uint8_t startPixel;
    uint8_t maxPixel;

    fadeVal = animReg & 0x000000ff;
    startPixel = 0;
    maxPixel = pixels.getNumPixelsOnChannel(0);
    if (!fadeVal && (rand(2000) < J_FADE_THRESH)) {
        // Do a fade anyway. IE. Start a burst
        fadeVal = 255;
    }
    if (fadeVal) {
        // Doing a fade down, so keep doing that
        fadeVal = (fadeVal > J_FADE_DOWN) ? (fadeVal - J_FADE_DOWN) : 0;
        animReg = (animReg & 0xffffff00) | fadeVal;

        for(int i=startPixel; i<maxPixel ; i++) {
            pixels.setPixel(i, 255, 255, 255);
        }
    } else {
        // Regular sparkle
        for(int i=startPixel; i<maxPixel; i++) {

            // Pixels have a small chance of being lit up
            if (rand(2000) < J_SPARKLE_THRESH) {
                SPARKLE_THE_PIXEL
            } else {
                pixels.setPixel(i, 0, 0, 0);
            }
        }         
    }

    // Right Side
    fadeVal = (animReg & 0x0000ff00) >> 8;
    startPixel = maxPixel;
    maxPixel = startPixel + pixels.getNumPixelsOnChannel(1);
    if (!fadeVal && (rand(2000) < J_FADE_THRESH)) {
        // Do a fade anyway. IE. Start a burst
        fadeVal = 255;
    }
    if (fadeVal) {
        // Doing a fade down, so keep doing that
        fadeVal = (fadeVal > J_FADE_DOWN) ? (fadeVal - J_FADE_DOWN) : 0;
        animReg = (animReg & 0xffff00ff) | (fadeVal<<8);

        for(int i=startPixel; i<maxPixel ; i++) {
            pixels.setPixel(i, 255, 255, 255);
        }
    } else {
        // Regular sparkle
        for(int i=startPixel; i<maxPixel; i++) {

            // Pixels have a small chance of being lit up
            if (rand(2000) < J_SPARKLE_THRESH) {
                SPARKLE_THE_PIXEL
            } else {
                pixels.setPixel(i, 0, 0, 0);
            }
        }         
    }    
}



uint32_t jperf_colors[] = {
    0x792C28, // Peach
    0xC16C06, // Yello
    0x6906ea, // Dark Purple
    0x276000, // Green
    0xBD2273, // Fuschia
    0x1A6Fff, // Blue
    // 0xAC73FC, // Light Purple
};
#define JP_NUM_COLORS 6
#define JP_BLOB_HSIZE 20

uint32_t jperf_Mcolors[] = {
    0xff0000, // Red
    0xff8000, // Orange
    0xffff00, // Yellow
    0x00ff00, // Green
    0x0000ff, // Blue
    0xff00ff, // Violet (magenta)
};


/////////
ANIM_START(JPERF_START, 2, 1000, ANIM_FLAG_WANTS_FADES)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(0)
    pixels.setPixel(0, 0, 64, 0, PF_NEXT_FRAME);
    pixels.setPixel(JPERF_BOUNDARY_END-1, 0, 64, 0, PF_NEXT_FRAME);

    // for(int i=0; i<JPERF_COUNT; i++) {
    //     int ix = (i * JP_NUM_COLORS) / JPERF_COUNT;
    //     pixels.setPixel(i, jperf_colors[ix], PF_NEXT_FRAME);
    // }

ANIM_FRAME(1)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_END


/////////



ANIM_START(JPERF_FBLOBS, 2, 1950, (ANIM_FLAG_WANTS_FADES | ANIM_FLAG_SKIP_FIRST_FADE) )
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(0)
// Pick a spot and a size
{
    int center = rand(JP_BLOB_HSIZE, JPERF_BOUNDARY_END - JP_BLOB_HSIZE);

    uint32_t color = jperf_colors[rand(JP_NUM_COLORS)];

    for(int i=0; i<JP_BLOB_HSIZE; i++) {
        uint32_t brightness = (255 / (i+1));

        uint16_t r = (((color & 0x00ff0000) >> 16) * brightness) >> 8;
        uint16_t g = (((color & 0x0000ff00) >>  8) * brightness) >> 8;
        uint16_t b = (((color & 0x000000ff)      ) * brightness) >> 8;

        pixels.setPixel(center + i, r, g, b, PF_NEXT_FRAME);
        pixels.setPixel(center - i, r, g, b, PF_NEXT_FRAME);
    }        
}

ANIM_FRAME(1)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_END


/////////
void Animator::JPERF_FSPARKLE_setup() {
    animParams.totalFrames = 1600;
    animParams.frameLength = 15;
    animParams.flags = ANIM_FLAG_NONE;
    animParams.maxTime = 300000;
}

void Animator::JPERF_FSPARKLE_drawFrame() {

    // Setup new colors on next, and we will fade from last to next

    for(int i=0; i< pixels.getNumPixels(); i++) {
        
        // Pixels have a small chance of being lit up
        if (rand(1000) < 200) {
            pixels.setPixel(i, jperf_colors[rand(JP_NUM_COLORS)]);
            // pixels.setPixel(i, 255, 255, 255);
        } else {
            pixels.setPixel(i, 0, 0, 0);
        }
    }
}


/////////
void Animator::JPERF_FPULSES_setup() {
    animParams.totalFrames = JPERF_BOUNDARY_END;
    animParams.frameLength = 4 * 1950 / JPERF_BOUNDARY_END;
    animParams.flags = ANIM_FLAG_WANTS_FADES;

}

void Animator::JPERF_FPULSES_drawFrame() {
    if (!animParams.currentFrame) {
        pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
        animColor = jperf_colors[rand(JP_NUM_COLORS)];

        animReg = rand(3);
    }

    uint16_t p = animParams.currentFrame;

    switch(animReg) {
        case 0:
            // Right to left
            pixels.setPixel(p, animColor, PF_NEXT_FRAME);
            break;

        case 1: 
            // Left to right
            pixels.setPixel(JPERF_BOUNDARY_END - p, animColor, PF_NEXT_FRAME);
            break;

        case 2:
            // Everything fade in
            {
            uint32_t brightness = p * (255 / JPERF_BOUNDARY_END);

            uint16_t r = (((animColor & 0x00ff0000) >> 16) * brightness) >> 8;
            uint16_t g = (((animColor & 0x0000ff00) >>  8) * brightness) >> 8;
            uint16_t b = (((animColor & 0x000000ff)      ) * brightness) >> 8;

            pixels.setAllPixels(r, g, b, PF_NEXT_FRAME);
        }
            break;

        case 3:
            // Roll around the arm

            // TODO: Implement this
            break;
    }
}


/////////
void Animator::JPERF_FSPOTS_setup() {
    animParams.totalFrames = 2;
    animParams.frameLength = 2 * 1950;
    animParams.flags = ANIM_FLAG_WANTS_FADES;
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
}

void Animator::JPERF_FSPOTS_drawFrame() {

    // Setup new colors on next, and we will fade from last to next

    int center = rand(JP_BLOB_HSIZE, JPERF_BOUNDARY_END - JP_BLOB_HSIZE);

    uint32_t color = jperf_colors[rand(JP_NUM_COLORS)];

    for(int i=0; i<JP_BLOB_HSIZE; i++) {
        uint32_t brightness = (255 / (i+1));

        uint16_t r = (((color & 0x00ff0000) >> 16) * brightness) >> 8;
        uint16_t g = (((color & 0x0000ff00) >>  8) * brightness) >> 8;
        uint16_t b = (((color & 0x000000ff)      ) * brightness) >> 8;

        pixels.setPixel(center + i, r, g, b, PF_NEXT_FRAME);
        pixels.setPixel(center - i, r, g, b, PF_NEXT_FRAME);
    }        

}

/////////
void Animator::JPERF_BREATH_setup() {
    animParams.totalFrames = 2;
    animParams.frameLength = 950;
    animParams.flags = ANIM_FLAG_WANTS_FADES;
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
    animReg = 0;
}

void Animator::JPERF_BREATH_drawFrame() {
    if (animParams.currentFrame == 0) {
        int start = animReg * 12;
        if (start > JPERF_HCOUNT) {
            start = JPERF_HCOUNT;
        }
        int end = JPERF_COUNT - start;

        animReg++;

        for(int i=start; i<end; i++) {
            pixels.setPixel(i, 255, 255, 255, PF_NEXT_FRAME);
        }
    } else {
        pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
    }
}



///////

/////////
ANIM_START(JPERF_MBOUNCE, 8, 267, ANIM_FLAG_WANTS_FADES )
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
    animReg = 0;

ANIM_FRAME(0)
    animColor = jperf_Mcolors[animReg % JP_NUM_COLORS];
    animReg++;

    pixels.setAllPixels(animColor, PF_NEXT_FRAME);

ANIM_FRAME(1)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(2)
    pixels.setAllPixels(animColor, PF_NEXT_FRAME);

ANIM_FRAME(3)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(4)
    pixels.setAllPixels(animColor, PF_NEXT_FRAME);

ANIM_FRAME(5)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(6)
    pixels.setAllPixels(animColor, PF_NEXT_FRAME);

ANIM_FRAME(7)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_END


/////////

ANIM_START(JPERF_MSNARE, 4, 133, ANIM_FLAG_NONE )
    pixels.setAllPixels(0, 0, 0);

ANIM_FRAME(0)
// Pick a spot and a size
{
    int center = rand(10, JPERF_BOUNDARY_END - 10);

    for(int i=0; i<5; i++) {
        pixels.setPixel(center + i, 255, 255, 255);
        pixels.setPixel(center - i, 255, 255, 255);
    }        
}

ANIM_FRAME(1)
    pixels.setAllPixels(0, 0, 0);

ANIM_END

/////////

ANIM_START(JPERF_OFF, 2, 267, ANIM_FLAG_NONE )
    pixels.setAllPixels(0, 0, 0);

ANIM_END


/////////
void Animator::JPERF_MSPARKLE_setup() {
    animParams.totalFrames = 1600;
    animParams.frameLength = 67;
    animParams.flags = ANIM_FLAG_NONE;
    animParams.maxTime = 300000;
}

void Animator::JPERF_MSPARKLE_drawFrame() {

    // Setup new colors on next, and we will fade from last to next

    for(int i=0; i< pixels.getNumPixels(); i++) {
        
        // Pixels have a small chance of being lit up
        if (rand(1000) < 10) {
            pixels.setPixel(i, jperf_Mcolors[rand(JP_NUM_COLORS)]);
            // pixels.setPixel(i, 255, 255, 255);
        } else {
            pixels.setPixel(i, 0, 0, 0);
        }
    }
}


/////////
ANIM_START(JPERF_MCLAP, 8, 267, ANIM_FLAG_WANTS_FADES )
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
    animReg = 0;

ANIM_FRAME(0)
    animColor = jperf_Mcolors[animReg % JP_NUM_COLORS];
    animReg++;

    pixels.setAllPixels(animColor, PF_NEXT_FRAME);

ANIM_FRAME(1)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(2)
    // pixels.setAllPixels(animColor, PF_NEXT_FRAME);

ANIM_FRAME(3)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(4)
    pixels.setAllPixels(animColor, PF_NEXT_FRAME);

ANIM_FRAME(5)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(6)
    // pixels.setAllPixels(animColor, PF_NEXT_FRAME);

ANIM_FRAME(7)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_END



/////////
ANIM_START(JPERF_MBOUNCE_END, 8, 267, ANIM_FLAG_WANTS_FADES )
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
    animReg = 0;

ANIM_FRAME(0)
    animColor = jperf_Mcolors[animReg % JP_NUM_COLORS];
    capturedColor = jperf_Mcolors[(animReg+1) % JP_NUM_COLORS];
    animReg++;

    for(int i=0; i<JPERF_COUNT; i++) {
        if (i < JPERF_BOUNDARY_ELBOW_BICEP || i >= JPERF_BOUNDARY_LBICEP_LELBOW) {
            pixels.setPixel(i, animColor, PF_NEXT_FRAME);
        } else {
            pixels.setPixel(i, capturedColor, PF_NEXT_FRAME);
        }
    }

ANIM_FRAME(1)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(2)
    for(int i=0; i<JPERF_COUNT; i++) {
        if (i < JPERF_BOUNDARY_ELBOW_BICEP || i >= JPERF_BOUNDARY_LBICEP_LELBOW) {
            pixels.setPixel(i, animColor, PF_NEXT_FRAME);
        } else {
            pixels.setPixel(i, capturedColor, PF_NEXT_FRAME);
        }
    }

ANIM_FRAME(3)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(4)
    for(int i=0; i<JPERF_COUNT; i++) {
        if (i < JPERF_BOUNDARY_ELBOW_BICEP || i >= JPERF_BOUNDARY_LBICEP_LELBOW) {
            pixels.setPixel(i, animColor, PF_NEXT_FRAME);
        } else {
            pixels.setPixel(i, capturedColor, PF_NEXT_FRAME);
        }
    }

ANIM_FRAME(5)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(6)
    for(int i=0; i<JPERF_COUNT; i++) {
        if (i < JPERF_BOUNDARY_ELBOW_BICEP || i >= JPERF_BOUNDARY_LBICEP_LELBOW) {
            pixels.setPixel(i, animColor, PF_NEXT_FRAME);
        } else {
            pixels.setPixel(i, capturedColor, PF_NEXT_FRAME);
        }
    }

ANIM_FRAME(7)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_END

/////////
ANIM_START(JPERF_END, 2, 5000, ANIM_FLAG_WANTS_FADES | ANIM_FLAG_SKIP_FIRST_FADE)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(0)
    // for(int i=0; i<40; i++) {
    //     pixels.setPixel(i, 128, 0, 128, PF_NEXT_FRAME);
    // }
    pixels.setPixel(0, 0, 0, 64, PF_NEXT_FRAME);
    pixels.setPixel(JPERF_BOUNDARY_END-1, 0, 0, 64, PF_NEXT_FRAME);

ANIM_FRAME(1)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);


ANIM_END
*/

#endif //  _ANIM_FUNCS_H_
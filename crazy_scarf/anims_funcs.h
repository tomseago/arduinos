
#ifndef _ANIM_FUNCS_H_
#define _ANIM_FUNCS_H_

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



void Animator::FLOOD_setup() {
	animParams.totalFrames = pixels.getNumPixels() * 2;
	animParams.frameLength = 100;
	animParams.flags = ANIM_FLAG_WANTS_FADES;

	pixels.setAllPixels(0,0,0, PF_NEXT_FRAME);
}

void Animator::FLOOD_drawFrame() {
    if (!animParams.currentFrame) {
	    animColor = colorWheel(random(255));
	    animReg = random(2);
    }

	if (animParams.currentFrame < pixels.getNumPixels()) {
		// Add a bar
		pixels.setPixel(animReg ? 
		    (pixels.getNumPixels() - animParams.currentFrame - 1)
		    : animParams.currentFrame
		    , animColor, PF_NEXT_FRAME);
	} else {
	    // Remove a bar
		pixels.setPixel(animReg ? 
		    (pixels.getNumPixels() - animParams.currentFrame - 1)
		    : animParams.currentFrame
		    , 0, PF_NEXT_FRAME);

// 		pixels.setPixel(animParams.currentFrame, 0, PF_NEXT_FRAME);
	}
}



void Animator::RAINBOW_setup() {
	animParams.totalFrames = pixels.getNumPixels();
	animParams.frameLength = 1000;
	animParams.flags = ANIM_FLAG_WANTS_FADES;

	// Color offset
	animColor = 0;
}

void Animator::RAINBOW_drawFrame() {

	char offset = animColor;
	for(int i=0; i<animParams.totalFrames; i+=4) {
	    uint32_t c = rainbow6_colors[offset++];
		if (offset >= 6) {
			offset = 0;
		}

	    pixels.setPixel(i, c, PF_NEXT_FRAME);
	    if (i+1 < animParams.totalFrames) {
	        pixels.setPixel(i+1, c, PF_NEXT_FRAME);
	    }
	    if (i+2 < animParams.totalFrames) {
	        pixels.setPixel(i+2, c, PF_NEXT_FRAME);
	    }
	    if (i+3 < animParams.totalFrames) {
	        pixels.setPixel(i+3, c, PF_NEXT_FRAME);
	    }

	}
	
	animColor++;
	if (animColor >= 6) {
		animColor = 0;
	}
}

/////////
void Animator::BRIGHT_FO_setup() {
	animParams.totalFrames = 1600;
	animParams.frameLength = 10;
	animParams.flags = ANIM_FLAG_NONE;
}

void Animator::BRIGHT_FO_drawFrame() {

    if (animParams.currentFrame == 0) {
        // Setup a new color
        animColor = random(255);
	   // animColor = colorWheel(random(255));

        for(int i=0; i< pixels.getNumPixels(); i++) {
            uint32_t c = colorWheel(animColor + random(16));
            uint16_t r = (c >> 16) & 0x00ff;
            uint16_t g = (c >>  8) & 0x00ff;
            uint16_t b = (c      ) & 0x00ff;

            uint16_t brightness = random(255);
            r = (r * brightness) >> 8;
            g = (g * brightness) >> 8;
            b = (b * brightness) >> 8;
            
            pixels.setPixel(i, r, g, b, PF_LAST_FRAME);
        }
        pixels.copyLastToCurrent();
        return;
    }
    
    // next is some lesser portion of last
    for(int i=0; i< pixels.getNumPixels(); i++) {
        uint32_t factor = ((animParams.totalFrames - animParams.currentFrame) << 16) / animParams.totalFrames;
        
        uint32_t c = pixels.getPixel(i, PF_LAST_FRAME);
        uint32_t r = (c >> 16) & 0x00ff;
        uint32_t g = (c >>  8) & 0x00ff;
        uint32_t b = (c      ) & 0x00ff;

        r = (r * factor) >> 16;
        g = (g * factor) >> 16;
        b = (b * factor) >> 16;
        
        pixels.setPixel(i, r, g, b, PF_CURRENT_FRAME);
    }

}


/////////
void Animator::RANDO_FADE_setup() {
	animParams.totalFrames = 1600;
	animParams.frameLength = 10;
	animParams.flags = ANIM_FLAG_NONE;
}

void Animator::RANDO_FADE_drawFrame() {

    if (animParams.currentFrame == 0) {
        pixels.copyNextToLast();
        
        // Setup new colors on next, and we will fade from last to next
        for(int i=0; i< pixels.getNumPixels(); i++) {
    	    animColor = colorWheel(random(255));

            uint16_t r = (animColor >> 16) & 0x00ff;
            uint16_t g = (animColor >>  8) & 0x00ff;
            uint16_t b = (animColor      ) & 0x00ff;

            uint16_t brightness = random(255);
            r = (r * brightness) >> 8;
            g = (g * brightness) >> 8;
            b = (b * brightness) >> 8;
            
            pixels.setPixel(i, r, g, b, PF_NEXT_FRAME);
        }
        return;
    }
    
    // next is some lesser portion of last
    uint32_t factor = (animParams.currentFrame << 8) / animParams.totalFrames;
    pixels.fadeIntoCurrent(factor);
}


/////////
void Animator::SPARKLE_setup() {
	animParams.totalFrames = 1600;
	animParams.frameLength = 10;
	animParams.flags = ANIM_FLAG_NONE;
	animParams.maxTime = 2000;
}

void Animator::SPARKLE_drawFrame() {

    // Setup new colors on next, and we will fade from last to next
    for(int i=0; i< pixels.getNumPixels(); i++) {
        
        // Pixels have a small chance of being lit up
        if (random(1000) < 50) {
            pixels.setPixel(i, 255, 255, 255);
        } else {
            pixels.setPixel(i, 0, 0, 0);
        }
    }
}

/////////
void Animator::FIND_A_PIXEL_setup() {
    animParams.totalFrames = 2;
    animParams.frameLength = 200;
    animParams.flags = ANIM_FLAG_WANTS_FADES;

    // Number of pixels we have done
    animReg = 0;
    // animParams.maxTime = 2000;

    // Start all off
    pixels.setAllPixels(0,0,0, PF_LAST_FRAME);
    pixels.setAllPixels(0,0,0, PF_NEXT_FRAME);
}

void Animator::FIND_A_PIXEL_drawFrame() {


    // A small random chance we turn on a new pixel / reset the whole
    // thing
    if (random(1000) > 250) {
        // No change
        return;
    }
    uint16_t np = pixels.getNumPixels();

    if (animReg >= np) {
        // Clear all before starting
        pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
        animReg = 0;
    }

    uint16_t pNum = random(np);
    uint16_t pEnd = pNum ? (pNum - 1) : (np-1);
    while(pixels.getPixel(pNum, PF_NEXT_FRAME) && pNum != pEnd) {
        pNum++;
        if (pNum == np) {
            pNum = 0;
        }
    }

    uint32_t color = colorWheel(random(255));
    pixels.setPixel(pNum, color, PF_NEXT_FRAME);

    animReg++;
}



/////////
void Animator::FIND_A_PIXEL_BPM_setup() {
    animParams.totalFrames = 2;
    // animParams.frameLength = 80; // This will do 25 pixels in 2000ms
    animParams.frameLength = 320; // This will do 25 pixels in 8s, so 4 measures
    animParams.flags = ANIM_FLAG_WANTS_FADES;

    // Number of pixels we have done
    animReg = 0;
    // animParams.maxTime = 2000;

    // Start all off
    pixels.setAllPixels(0,0,0, PF_LAST_FRAME);
    pixels.setAllPixels(0,0,0, PF_NEXT_FRAME);
    animColor = colorWheel(random(255));
}

void Animator::FIND_A_PIXEL_BPM_drawFrame() {


    uint16_t np = pixels.getNumPixels();

    if (animReg >= np) {
        // Clear all before starting
        pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);
        animReg = 0;
        animColor = colorWheel(random(255));
    }

    uint16_t pNum = random(np);
    uint16_t pEnd = pNum ? (pNum - 1) : (np-1);
    while(pixels.getPixel(pNum, PF_NEXT_FRAME) && pNum != pEnd) {
        pNum++;
        if (pNum == np) {
            pNum = 0;
        }
    }

    pixels.setPixel(pNum, animColor, PF_NEXT_FRAME);

    animReg++;
}

//////////
#define NP 25
#define MP 24
#define GDARK    0x741717
#define GNORM    0xEA2828
#define GBRIGHT  0xff0000

// #define BDARK    0x20ff20
#define BDARK    0x0D029B
#define BNORM    0x220FFF
#define BBRIGHT  0x0000ff
// #define BBRIGHT  0xD0ffD0

#define BLACK    0x000000



ANIM_START(BMGMB, 60, 800, ANIM_FLAG_WANTS_FADES)

ANIM_FRAME(0)
    pixels.setAllPixels(0, 0, 0, PF_NEXT_FRAME);

ANIM_FRAME(1)
    pixels.setPixel(0, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(2)
    pixels.setPixel(0, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(1, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(3)
    pixels.setPixel(1, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(2, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(4)
    pixels.setPixel(2, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(3, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(5)
    pixels.setPixel(3, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(4, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(6)
    pixels.setPixel(4, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(5, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(7)
    pixels.setPixel(5,  BBRIGHT, PF_NEXT_FRAME);

ANIM_FRAME(8)
    pixels.setPixel(5, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(9)
    pixels.setPixel(5, BBRIGHT, PF_NEXT_FRAME);

ANIM_FRAME(10)
    pixels.setPixel(5, BNORM, PF_NEXT_FRAME);


// Girl introduced
ANIM_FRAME(11)
    pixels.setPixel(MP-0, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(12)
    pixels.setPixel(MP-0, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-1, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(13)
    pixels.setPixel(MP-1, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-2, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(14)
    pixels.setPixel(MP-2, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-3, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(15)
    pixels.setPixel(MP-3, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-4, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(16)
    pixels.setPixel(MP-4, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-5, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(17)
    pixels.setPixel(MP-5, GBRIGHT, PF_NEXT_FRAME);

ANIM_FRAME(18)
    pixels.setPixel(MP-5, GDARK, PF_NEXT_FRAME);

ANIM_FRAME(19)
    pixels.setPixel(MP-5, GBRIGHT, PF_NEXT_FRAME);

ANIM_FRAME(20)
    pixels.setPixel(MP-5, GNORM, PF_NEXT_FRAME);


// Boy advances by 5 (from 5 to 10)
ANIM_FRAME(21)
    pixels.setPixel(5, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(6, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(22)
    pixels.setPixel(6, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(7, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(23)
    pixels.setPixel(7, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(8, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(24)
    pixels.setPixel(8, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(9, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(25)
    pixels.setPixel(9, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(10, BNORM, PF_NEXT_FRAME);

// Girl goes towards him as second blue enters
ANIM_FRAME(26)
    pixels.setPixel(MP-5, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-6, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(27)
    pixels.setPixel(MP-6, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-7, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(28)
    pixels.setPixel(MP-7, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-8, GNORM, PF_NEXT_FRAME);

    pixels.setPixel(MP-0, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(29)
    pixels.setPixel(MP-8, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-9, GNORM, PF_NEXT_FRAME);

    pixels.setPixel(MP-0, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-1, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(30)
    pixels.setPixel(MP-9, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-10, GNORM, PF_NEXT_FRAME);

    pixels.setPixel(MP-1, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-2, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(31)
    pixels.setPixel(MP-10, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-11, GNORM, PF_NEXT_FRAME);

    pixels.setPixel(MP-2, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-3, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(32)
    pixels.setPixel(MP-11, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-12, GNORM, PF_NEXT_FRAME);

    pixels.setPixel(MP-3, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-4, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(33)
    pixels.setPixel(MP-12, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-13, GNORM, PF_NEXT_FRAME);

    pixels.setPixel(MP-4, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(MP-5, BDARK, PF_NEXT_FRAME);


// Boy jumps girl, joins other boy
ANIM_FRAME(34)
    pixels.setPixel(10, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(12, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(35)
    pixels.setPixel(12, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(14, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(36)
    pixels.setPixel(14, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(16, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(37)
    pixels.setPixel(16, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(18, BNORM, PF_NEXT_FRAME);

ANIM_FRAME(38)
    pixels.setPixel(18, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(20, BNORM, PF_NEXT_FRAME);


// Boys advance back towards middle, girl leaves
ANIM_FRAME(39)
    pixels.setPixel(20, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(19, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(18, BDARK, PF_NEXT_FRAME);

    pixels.setPixel(11, BLACK, PF_NEXT_FRAME);
    pixels.setPixel( 9, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(40)
    pixels.setPixel(19, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(18, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(17, BDARK, PF_NEXT_FRAME);
    
    pixels.setPixel( 9, BLACK, PF_NEXT_FRAME);
    pixels.setPixel( 7, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(41)
    pixels.setPixel(18, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(17, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(16, BDARK, PF_NEXT_FRAME);
    
    pixels.setPixel( 7, BLACK, PF_NEXT_FRAME);
    pixels.setPixel( 5, GNORM, PF_NEXT_FRAME);

ANIM_FRAME(42)
    pixels.setPixel(17, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(16, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(15, BDARK, PF_NEXT_FRAME);

    pixels.setPixel( 5, BLACK, PF_NEXT_FRAME);
    pixels.setPixel( 3, GNORM, PF_NEXT_FRAME);
    
ANIM_FRAME(43)
    pixels.setPixel(16, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(15, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(14, BDARK, PF_NEXT_FRAME);

    pixels.setPixel( 3, BLACK, PF_NEXT_FRAME);
    pixels.setPixel( 1, GNORM, PF_NEXT_FRAME);
    
ANIM_FRAME(44)
    pixels.setPixel(15, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(14, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(13, BDARK, PF_NEXT_FRAME);

    pixels.setPixel( 1, BLACK, PF_NEXT_FRAME);

ANIM_FRAME(45)
    pixels.setPixel(14, BLACK, PF_NEXT_FRAME);
    pixels.setPixel(13, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(12, BDARK, PF_NEXT_FRAME);
    pixels.setPixel(11, BDARK, PF_NEXT_FRAME);
    


// Flood to ends
ANIM_FRAME(46)
    pixels.setPixel(15, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(14, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(10, BDARK, PF_NEXT_FRAME);
    pixels.setPixel( 9, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(47)
    pixels.setPixel(17, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(16, BNORM, PF_NEXT_FRAME);
    pixels.setPixel( 8, BDARK, PF_NEXT_FRAME);
    pixels.setPixel( 7, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(48)
    pixels.setPixel(19, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(18, BNORM, PF_NEXT_FRAME);
    pixels.setPixel( 6, BDARK, PF_NEXT_FRAME);
    pixels.setPixel( 5, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(49)
    pixels.setPixel(21, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(20, BNORM, PF_NEXT_FRAME);
    pixels.setPixel( 4, BDARK, PF_NEXT_FRAME);
    pixels.setPixel( 3, BDARK, PF_NEXT_FRAME);

ANIM_FRAME(50)
    pixels.setPixel(24, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(23, BNORM, PF_NEXT_FRAME);
    pixels.setPixel(22, BNORM, PF_NEXT_FRAME);
    pixels.setPixel( 2, BDARK, PF_NEXT_FRAME);
    pixels.setPixel( 1, BDARK, PF_NEXT_FRAME);
    pixels.setPixel( 0, BDARK, PF_NEXT_FRAME);

// Animate heart beat
ANIM_FRAME(56)
    // Red
    pixels.setAllPixels(255, 0, 0, PF_NEXT_FRAME);


ANIM_FRAME(58)
    // Pink
    pixels.setAllPixels(255, 0, 0, PF_NEXT_FRAME);


ANIM_FRAME(59)
    // Red
    pixels.setAllPixels(255, 0, 0, PF_NEXT_FRAME);


////
 
ANIM_END

#endif //  _ANIM_FUNCS_H_

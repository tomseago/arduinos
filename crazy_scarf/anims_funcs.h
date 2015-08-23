
#ifndef _ANIM_FUNCS_H_
#define _ANIM_FUNCS_H_

#define ANIM_START(name, frames, len, f_val) void MTHarnass::name##_setup() { \
    animParams.totalFrames = frames; \
    animParams.frameLength = len; \
    animParams.flags = f_val; \
 }\
 void MTHarnass::name##_drawFrame(){\
    switch(animParams.currentFrame) {\
    	default:

#define ANIM_FRAME(num) break; \
    	case num: 

#define ANIM_END break; } }

// Alternate version which just defines a function

#define ANIM_FSTART(name, frames, len, f_val) void MTHarnass::name##_setup() { \
    animParams.totalFrames = frames; \
    animParams.frameLength = len; \
    animParams.flags = f_val; \
 }\
 void MTHarnass::name##_drawFrame(){

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




#endif //  _ANIM_FUNCS_H_

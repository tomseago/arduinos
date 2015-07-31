#ifndef _ANIMS_H_
#define _ANIMS_H_

#define ANIM_START(name, frames, len) void MTHarnass::name##_setup() { \
    animParams.totalFrames = frames; \
    animParams.frameLength = len; \
 }\
 void MTHarnass::name##_drawFrame(){\
    switch(animParams.currentFrame) {\
    	default:

#define ANIM_FRAME(num) break; \
    	case num: 

#define ANIM_END break; } }

uint32_t rainbow6[] = {
	0xff0000, // Red
	0xff8000, // Orange
	0xffff00, // Yellow
	0x00ff00, // Green
	0x0000ff, // Blue
	0xff00ff, // Violet (magenta)
};

void MTHarnass::BLINK_setup() {
	animParams.totalFrames = 2;
	animParams.frameLength = 300;
}

void MTHarnass::BLINK_drawFrame() {

	switch(animParams.currentFrame) {
		case 0:
			solidColor(128, 0, 0, F_BOTH);
			break;

		case 1:
			solidColor(0,0,0,F_BOTH);
			break;
	}

	//h6Stripe(rainbow6[0], 0, F_BOTH);
}

void MTHarnass::HRAINBOW_setup() {
	animParams.totalFrames = 6;
	animParams.frameLength = 300;

	// Color offset
	animColor = 0;
}

void MTHarnass::HRAINBOW_drawFrame() {

	char offset = animColor;
	for(int i=0; i<6; i++) {
		h6Stripe(rainbow6[offset], i, F_BOTH);
		offset++;
		if (offset >= 6) {
			offset = 0;
		}
	}
	animColor++;
	if (animColor >= 6) {
		animColor = 0;
	}
}

void MTHarnass::RAND_MOVER_setup() {
	animParams.totalFrames = 2;
	animParams.frameLength = 50;

	animColor = selectedColor;
	capturedColor = selectedColor;
	animReg = 0;

	solidColor(0, 0, 0, F_BOTH);
}

void MTHarnass::RAND_MOVER_drawFrame() {


	int i = random(1024);

	if (i > 300) {
		// Let's move!

		// Which way though?
		bool dir = animReg & 0x0000FF00;
		uint8_t oldPos = animReg & 0x00ff;
		if (oldPos == 0) {
			// Only one direction
			dir = false;
		} else if (oldPos >= 55) {
			dir = true;
		} else {
			// Make it up!
			if (ui.regC) {
				if (random(1024) > 800) {
					// Change direction!
					dir = !dir;
				}
			}
		}

		int next = oldPos + (dir ? -1 : 1);

		// Turn off current before we move
		if (!ui.regB) {
			setMappedPixelColor((animReg & 0x00FF), 0);
		}
		animReg = next | ( dir << 8);
	}

	if (ui.regA) {
		animColor = colorWheel(random(255));
	}

	if (capturedColor != selectedColor) {
		capturedColor = selectedColor;
		animColor = selectedColor;
	}


	// TODO: Animate the color??
	setMappedPixelColor((animReg & 0x00FF), animColor);
}


void MTHarnass::TRACER_setup() {
	animParams.totalFrames = 112;
	animParams.frameLength = 300;

	solidColor(0,0,0, F_BOTH);
}

void MTHarnass::TRACER_drawFrame() {

	setMappedPixelColor(animParams.currentFrame - 1, 0);
	setMappedPixelColor(animParams.currentFrame, selectedColor);
}

void MTHarnass::RAND_ALL_setup() {
	animParams.totalFrames = 2;
	animParams.frameLength = 300;

	solidColor(0,0,0, F_BOTH);
}

void MTHarnass::RAND_ALL_drawFrame() {
	for(int i=0; i<56; i++) {
		setMappedPixelColor(i, colorWheel(random(255)));
	}

}


void MTHarnass::RAND_BRIGHT_setup() {
	animParams.totalFrames = 2;
	animParams.frameLength = 300;

	solidColor(0,0,0, F_BOTH);
}

void MTHarnass::RAND_BRIGHT_drawFrame() {
	for(int i=0; i<56; i++) {
		uint32_t c = selectedColor;

		uint16_t brightness = random(255);
		uint32_t r = (c >> 16) & 0xff;
		uint32_t g = (c >> 8) & 0xff;
		uint32_t b = (c ) & 0xff;

		r = (r * brightness) >> 8;
		g = (g * brightness) >> 8;
		b = (b * brightness) >> 8;

		c = (r<<16) + (g<<8) + b;
		setMappedPixelColor(i, c);
	}


	if (ui.regA) {
		selectedColor = colorWheel(random(255));
	}
}

//////////////////////////////////////////////////////

ANIM_START(FLOOD, 19, 50)
ANIM_FRAME(0)
	capturedColor = selectedColor;
	solidColor(0,0,0,F_BOTH);
	sash.setPixelColor(0, capturedColor);

ANIM_FRAME(1)
	sash.setPixelColor(1, capturedColor);

ANIM_FRAME(2)
	sash.setPixelColor(2, capturedColor);

ANIM_FRAME(3)
	sash.setPixelColor(3, capturedColor);

ANIM_FRAME(4)
	sash.setPixelColor(4, capturedColor);

ANIM_FRAME(5)
	sash.setPixelColor(5, capturedColor);
	sash.setPixelColor(6, capturedColor);

ANIM_FRAME(6)
	sash.setPixelColor(7, capturedColor);
	sash.setPixelColor(11, capturedColor);

ANIM_FRAME(7)
	sash.setPixelColor(8, capturedColor);
	sash.setPixelColor(10, capturedColor);

ANIM_FRAME(8)
	sash.setPixelColor(9, capturedColor);
	sash.setPixelColor(12, capturedColor);

ANIM_FRAME(9)
	sash.setPixelColor(14, capturedColor);
	sash.setPixelColor(13, capturedColor);

ANIM_FRAME(10)
	sash.setPixelColor(15, capturedColor);

ANIM_FRAME(11)
	sash.setPixelColor(16, capturedColor);
	sash.setPixelColor(17, capturedColor);
	sash.setPixelColor(18, capturedColor);

ANIM_FRAME(12)
	sash.setPixelColor(19, capturedColor);

ANIM_FRAME(13)
	sash.setPixelColor(20, capturedColor);

ANIM_FRAME(14)
	sash.setPixelColor(21, capturedColor);

ANIM_FRAME(15)
	sash.setPixelColor(22, capturedColor);

ANIM_FRAME(16)
	sash.setPixelColor(23, capturedColor);

ANIM_FRAME(17)
	sash.setPixelColor(24, capturedColor);


ANIM_END

//////////////////////////////////////////////////////

ANIM_START(FLOOD_LINE, 25, 100)

ANIM_FRAME(0)
	solidColor(0,0,0,F_BOTH);
	sash.setPixelColor(0, 0, 0, 255);

ANIM_FRAME(1)
	sash.setPixelColor(1, 0, 0, 255);

ANIM_FRAME(2)
	sash.setPixelColor(2, 0, 0, 255);

ANIM_FRAME(3)
	sash.setPixelColor(3, 0, 0, 255);

ANIM_FRAME(4)
	sash.setPixelColor(4, 0, 0, 255);

ANIM_FRAME(5)
	sash.setPixelColor(5, 0, 0, 255);

ANIM_FRAME(6)
	sash.setPixelColor(6, 0, 0, 255);

ANIM_FRAME(7)
	sash.setPixelColor(7, 0, 0, 255);

ANIM_FRAME(8)
	sash.setPixelColor(8, 0, 0, 255);

ANIM_FRAME(9)
	sash.setPixelColor(9, 0, 0, 255);

ANIM_FRAME(10)
	sash.setPixelColor(10, 0, 0, 255);

ANIM_FRAME(11)
	sash.setPixelColor(11, 0, 0, 255);

ANIM_FRAME(12)
	sash.setPixelColor(12, 0, 0, 255);

ANIM_FRAME(13)
	sash.setPixelColor(13, 0, 0, 255);

ANIM_FRAME(14)
	sash.setPixelColor(14, 0, 0, 255);

ANIM_FRAME(15)
	sash.setPixelColor(15, 0, 0, 255);

ANIM_FRAME(16)
	sash.setPixelColor(16, 0, 0, 255);

ANIM_FRAME(17)
	sash.setPixelColor(17, 0, 0, 255);

ANIM_FRAME(18)
	sash.setPixelColor(18, 0, 0, 255);

ANIM_FRAME(19)
	sash.setPixelColor(19, 0, 0, 255);

ANIM_FRAME(20)
	sash.setPixelColor(20, 0, 0, 255);

ANIM_FRAME(21)
	sash.setPixelColor(21, 0, 0, 255);

ANIM_FRAME(22)
	sash.setPixelColor(22, 0, 0, 255);

ANIM_FRAME(23)
	sash.setPixelColor(23, 0, 0, 255);

ANIM_FRAME(24)
	sash.setPixelColor(24, 0, 0, 255);


ANIM_END


//////////////////////////////////////////////////////

ANIM_START(BLUE_STEPS, 5, 400)
ANIM_FRAME(0)
	solidColor(0,0,0, F_BOTH);

ANIM_FRAME(1)
	solidColor(0,0,64, F_BOTH);

ANIM_FRAME(2)
	solidColor(0,0,128, F_BOTH);

ANIM_FRAME(3)
	solidColor(0,0,192, F_BOTH);

ANIM_FRAME(4)
	solidColor(0,0,255, F_BOTH);

ANIM_FRAME(5)
	solidColor(0,255,0, F_BOTH);

ANIM_END

/////////



/*
//////////////////////////////////////////////////////

ANIM_START(FLOOD, 25, 100)
ANIM_FRAME(0)
	solidColor(0,0,0,F_BOTH);

ANIM_FRAME(1)
ANIM_FRAME(2)
ANIM_FRAME(3)
ANIM_FRAME(4)
ANIM_FRAME(5)
ANIM_FRAME(6)
ANIM_FRAME(7)
ANIM_FRAME(8)
ANIM_FRAME(9)
ANIM_FRAME(10)
ANIM_FRAME(11)
ANIM_FRAME(12)
ANIM_FRAME(13)
ANIM_FRAME(14)
ANIM_FRAME(15)
ANIM_FRAME(16)
ANIM_FRAME(17)
ANIM_FRAME(18)
ANIM_FRAME(19)
ANIM_FRAME(20)
ANIM_FRAME(21)
ANIM_FRAME(22)
ANIM_FRAME(23)
ANIM_FRAME(24)
*/

/*

ANIM_START(FLOOD, 19, 50)
ANIM_FRAME(0)
	solidColor(0,0,0,F_BOTH);

ANIM_FRAME(1)
	sash.setPixelColor(0, 0, 0, 255);

ANIM_FRAME(2)
	sash.setPixelColor(1, 0, 0, 255);

ANIM_FRAME(3)
	sash.setPixelColor(2, 0, 0, 255);

ANIM_FRAME(4)
	sash.setPixelColor(3, 0, 0, 255);

ANIM_FRAME(5)
	sash.setPixelColor(4, 0, 0, 255);

ANIM_FRAME(6)
	sash.setPixelColor(5, 0, 0, 255);
	sash.setPixelColor(6, 0, 0, 255);

ANIM_FRAME(7)
	sash.setPixelColor(7, 0, 0, 255);
	sash.setPixelColor(11, 0, 0, 255);

ANIM_FRAME(8)
	sash.setPixelColor(8, 0, 0, 255);
	sash.setPixelColor(10, 0, 0, 255);

ANIM_FRAME(9)
	sash.setPixelColor(9, 0, 0, 255);
	sash.setPixelColor(12, 0, 0, 255);

ANIM_FRAME(10)
	sash.setPixelColor(14, 0, 0, 255);
	sash.setPixelColor(13, 0, 0, 255);

ANIM_FRAME(11)
	sash.setPixelColor(15, 0, 0, 255);

ANIM_FRAME(12)
	sash.setPixelColor(16, 0, 0, 255);
	sash.setPixelColor(17, 0, 0, 255);
	sash.setPixelColor(18, 0, 0, 255);

ANIM_FRAME(13)
	sash.setPixelColor(19, 0, 0, 255);
ANIM_FRAME(14)
	sash.setPixelColor(20, 0, 0, 255);
ANIM_FRAME(15)
	sash.setPixelColor(21, 0, 0, 255);
ANIM_FRAME(16)
	sash.setPixelColor(22, 0, 0, 255);
ANIM_FRAME(17)
	sash.setPixelColor(23, 0, 0, 255);
ANIM_FRAME(18)
	sash.setPixelColor(24, 0, 0, 255);

ANIM_END
*/
#endif _ANIMS_H_
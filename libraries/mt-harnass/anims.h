#ifndef _ANIMS_H_
#define _ANIMS_H_

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
}

#endif _ANIMS_H_
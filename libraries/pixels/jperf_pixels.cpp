#include "jperf_pixels.h"

JPerfPixels::JPerfPixels(Pixels& neck, Pixels& left, Pixels& right) :
	neck(neck), left(left), right(right), Pixels(0) {

	// Override the stored number of pixels so that things
	// do actually get set
	numNeck = neck.getNumPixels();
	numLeft = left.getNumPixels();
	numRight = right.getNumPixels();
	numPixels = numNeck + numLeft + numRight;
}

uint16_t 
JPerfPixels::getNumPixelsOnChannel(uint8_t channel) {
	switch(channel) {
		case 0:
			return numRight;

		case 1:
			return numNeck;

		case 2:
			return numLeft;
	}
	return 0;
}

uint8_t 
JPerfPixels::getNumChannels() {
    return 3;
}


int16_t
JPerfPixels::actualPixelForIndex(int16_t which, uint8_t flags) {
	int16_t actual = Pixels::actualPixelForIndex(which, flags);

	// Invert some of the arm bands

	if (actual >= JPERF_BOUNDARY_WRIST_FOREARM && actual < JPERF_BOUNDARY_FOREARM_ELBOW) {
		actual = JPERF_BOUNDARY_WRIST_FOREARM + (JPERF_BOUNDARY_FOREARM_ELBOW - actual) - 1;
	} else if (actual >= JPERF_BOUNDARY_ELBOW_BICEP && actual < JPERF_BOUNDARY_BICEP_NECK) {
		actual = JPERF_BOUNDARY_ELBOW_BICEP + (JPERF_BOUNDARY_BICEP_NECK - actual) - 1;

	} else if (actual >= JPERF_BOUNDARY_NECK_LBICEP && actual < JPERF_BOUNDARY_LBICEP_LELBOW) {
		actual = JPERF_BOUNDARY_NECK_LBICEP + (JPERF_BOUNDARY_LBICEP_LELBOW - actual) - 1;
	} else if (actual >= JPERF_BOUNDARY_LELBOW_LFOREARM && actual < JPERF_BOUNDARY_LFOREARM_LWRIST) {
		actual = JPERF_BOUNDARY_LELBOW_LFOREARM + (JPERF_BOUNDARY_LFOREARM_LWRIST - actual) - 1;
	}
	// } else if (actual >= JPERF_BOUNDARY_LBICEP_LELBOW && actual < JPERF_BOUNDARY_LELBOW_LFOREARM) {
	// 	actual = JPERF_BOUNDARY_LBICEP_LELBOW + (JPERF_BOUNDARY_LELBOW_LFOREARM - actual) - 1;
	// } else if (actual >= JPERF_BOUNDARY_LFOREARM_LWRIST) {
	// 	actual = JPERF_BOUNDARY_LFOREARM_LWRIST + (JPERF_BOUNDARY_END - actual) - 1;
	// }

	return actual;
}

void
JPerfPixels::setPixelInFrame(uint16_t which, uint8_t frame, uint8_t r, uint8_t g, uint8_t b, uint8_t flags) {

	// The mapping is right arm at the wrist, up to neck, down the
	// left arm. The arm bands are mapped curling into the body
	// at each level.

	uint16_t actual = which;

	// If actual is on the right side, invert it
	if (which < numRight) {
		actual = numRight - 1 - which;
	}

	// Now we actually set it
	if (actual < JPERF_BOUNDARY_BICEP_NECK) {
		right.setPixel(actual, r, g, b, flags);
	} else if (actual < JPERF_BOUNDARY_NECK_LBICEP) {
		actual -= JPERF_BOUNDARY_BICEP_NECK;
		neck.setPixel(actual, r, g, b, flags);
	} else {
		actual -= JPERF_BOUNDARY_NECK_LBICEP;
		left.setPixel(actual, r, g, b, flags);
	}

}

void 
JPerfPixels::setBrightness(uint8_t brightness) {
	neck.setBrightness(brightness);
	left.setBrightness(brightness);
	right.setBrightness(brightness);
}

uint32_t
JPerfPixels::getPixel(uint16_t which, uint8_t flags) {
	uint16_t actual = which;

	// TODO: This isn't right WRT the reversed arm bands,
	// but I'm not sure if we care (yet...)
	if (actual < JPERF_BOUNDARY_BICEP_NECK) {
		return right.getPixel(actual, flags);
	} else if (actual < JPERF_BOUNDARY_NECK_LBICEP) {
		actual -= JPERF_BOUNDARY_BICEP_NECK;
		return neck.getPixel(actual, flags);
	} else {
		actual -= JPERF_BOUNDARY_NECK_LBICEP;
		return left.getPixel(actual, flags);
	}

}

void
JPerfPixels::copyNextToLast() {
	neck.copyNextToLast();
	left.copyNextToLast();
	right.copyNextToLast();
}

void 
JPerfPixels::copyLastToCurrent() {
	neck.copyLastToCurrent();
	left.copyLastToCurrent();
	right.copyLastToCurrent();	
}

void 
JPerfPixels::swapNextAndLast() {
	neck.swapNextAndLast();
	left.swapNextAndLast();
	right.swapNextAndLast();	
}

void
JPerfPixels::fadeIntoCurrent(uint8_t distance) {
	neck.fadeIntoCurrent(distance);
	left.fadeIntoCurrent(distance);
	right.fadeIntoCurrent(distance);
}


uint32_t 
JPerfPixels::send() {
	return neck.send() + left.send() + right.send();	
}


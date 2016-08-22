#include "two_channels.h"

TwoChannels::TwoChannels(Pixels& chanA, Pixels& chanB) :
	chanA(chanA), chanB(chanB), Pixels(0) {

	// Override the stored number of pixels so that things
	// do actually get set
	numA = chanA.getNumPixels();
	numPixels = numA + chanB.getNumPixels();
}


uint16_t 
TwoChannels::getNumPixelsOnChannel(uint8_t channel) {
	switch(channel) {
		case 0:
			return numA;

		case 1:
			return numPixels - numA;
	}
	return 0;
}

uint8_t 
TwoChannels::getNumChannels() {
    return 2;
}

void
TwoChannels::setPixelInFrame(uint16_t which, uint8_t frame, uint8_t r, uint8_t g, uint8_t b, uint8_t flags) {

	// The bike implementation re-mapped the front here. We don't.

	uint16_t actual = which;

	if (which < numA) {
		chanA.setPixel(actual, r, g, b, flags);
	} else {
		actual -= numA;
		chanB.setPixel(actual, r, g, b, flags);
	}
}

void 
TwoChannels::setBrightness(uint8_t brightness) {
	chanA.setBrightness(brightness);
	chanB.setBrightness(brightness);
}

uint32_t
TwoChannels::getPixel(uint16_t which, uint8_t flags) {
	uint16_t actual = which;

	if (which < numA) {
		return chanA.getPixel(actual, flags);
	} else {
		actual -= numA;
		return chanB.getPixel(actual, flags);
	}
}

void
TwoChannels::copyNextToLast() {
	chanA.copyNextToLast();
	chanB.copyNextToLast();
}

void 
TwoChannels::copyLastToCurrent() {
	chanA.copyLastToCurrent();
	chanB.copyLastToCurrent();
}

void 
TwoChannels::swapNextAndLast() {
	chanA.swapNextAndLast();
	chanB.swapNextAndLast();
}

void
TwoChannels::fadeIntoCurrent(uint8_t distance) {
	chanA.fadeIntoCurrent(distance);
	chanB.fadeIntoCurrent(distance);
}


uint32_t 
TwoChannels::send() {
	return chanA.send() + chanB.send();
}


#include "bike_pixels.h"

BikePixels::BikePixels(Pixels& front, Pixels& left, Pixels& right) :
	front(front), left(left), right(right), Pixels(0) {

	// Override the stored number of pixels so that things
	// do actually get set
	numFront = front.getNumPixels();
	numPixels = numFront + left.getNumPixels();
}

uint16_t 
BikePixels::getNumPixelsOnChannel(uint8_t channel) {
	switch(channel) {
		case 0:
			return numFront;

		case 1:
			return left.getNumPixels();

		case 2:
			return right.getNumPixels();
	}
	return 0;
}

uint8_t 
BikePixels::getNumChannels() {
    return 3;
}

void
BikePixels::setPixelInFrame(uint16_t which, uint8_t frame, uint8_t r, uint8_t g, uint8_t b, uint8_t flags) {

	// The layout we will re-map to here is that the front is in
	// reverse order (i.e. pixel 0 is the last of the front) and
	// then writes to the rear that do not have the left or
	// right flag set will get written to both sides.

	uint16_t actual = which;

	if (which < numFront) {
		actual = numFront - 1 - which;

		front.setPixel(actual, r, g, b, flags);
	} else {
		actual -= numFront;
		if (!(flags & PF_LEFT)) {
			right.setPixel(actual, r, g, b, flags);
		}
		if (!(flags & PF_RIGHT)) {
			left.setPixel(actual, r, g, b, flags);			
		}
	}
}

void 
BikePixels::setBrightness(uint8_t brightness) {
	front.setBrightness(brightness);
	left.setBrightness(brightness);
	right.setBrightness(brightness);
}

uint32_t
BikePixels::getPixel(uint16_t which, uint8_t flags) {
	uint16_t actual = which;

	if (which < numFront) {
		actual = numFront - 1 - which;
		return front.getPixel(actual, flags);
	} else {
		actual -= numFront;
		if (flags & PF_RIGHT) {
			return right.getPixel(actual, flags);
		}
		return left.getPixel(actual, flags);
	}
}

void
BikePixels::copyNextToLast() {
	front.copyNextToLast();
	left.copyNextToLast();
	right.copyNextToLast();
}

void 
BikePixels::copyLastToCurrent() {
	front.copyLastToCurrent();
	left.copyLastToCurrent();
	right.copyLastToCurrent();	
}

void 
BikePixels::swapNextAndLast() {
	front.swapNextAndLast();
	left.swapNextAndLast();
	right.swapNextAndLast();	
}

void
BikePixels::fadeIntoCurrent(uint8_t distance) {
	front.fadeIntoCurrent(distance);
	left.fadeIntoCurrent(distance);
	right.fadeIntoCurrent(distance);
}


uint32_t 
BikePixels::send() {
	return front.send() + left.send() + right.send();	
}


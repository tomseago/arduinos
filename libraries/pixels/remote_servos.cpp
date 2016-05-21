#include "remote_servos.h"


RemoteServos::RemoteServos(uint8_t rxPin, uint8_t txPin, uint8_t numServos) : 
	// peer(rxPin, txPin), 
	numServos(numServos)
{

	// Allocate a frame buffer for the servos
	frames = (uint8_t*)calloc(3, numServos);

	// In case that went badly...
	if (!frames) {
		numServos = 0;
	} else {
		lastFrameIx = 1;
		nextFrameIx = 2;
	}
}

void
RemoteServos::begin() {

	// pinMode(dataPin, OUTPUT);
	// pinMode(clockPin, OUTPUT);


	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);

	// servo0.attach(9);

	// Serial.begin(19200);
	// // peer.begin(19200);

	// // Tell the other arduino that we are here
	// for(uint8_t i=0; i<20; i++) {
	// 	peer.write(0xff);
	// }

	// Serial.print("Servos Begin ");
	// Serial.print(numServos);
	// Serial.print("\n");
}

void
RemoteServos::setServoInFrame(uint8_t which, uint8_t frame, uint8_t value, uint8_t flags) {

	int ix = (which) + (frame * numServos);

	// Make sure it varies by enough
	// int diff = (int16_t)frames[ix] - (int16_t)value;
	// if (diff < 0) diff = -1 * diff;
	// if (diff < 20) return;

	frames[ix] = value >> 1;
}

uint8_t
RemoteServos::getNumServos() {
	return numServos;
}

uint8_t
RemoteServos::setServo(uint8_t which, uint8_t value, uint8_t flags) {
	if (!numServos) return 0;

	uint8_t frame = 0;
	if (flags & PF_LAST_FRAME) {
		frame = lastFrameIx;
	} else if (flags & PF_NEXT_FRAME) {
		frame = nextFrameIx;
	}

	// Don't support bounce or wrapping servo indexes so actual is which

	// No such thing as brightness of a servo

	// Might want to scale the servo output here in the future....

	setServoInFrame(which, frame, value, flags);

	return which;
}

void
RemoteServos::setAllServos(uint8_t value, uint8_t flags) {
	for(uint8_t i=0; i<numServos; i++) {
		setServo(i, value, flags);
	}
}

uint8_t
RemoteServos::getServo(uint8_t which, uint8_t flags) {
	if (which >= numServos) {
		return 0;
	}

	uint8_t frame = 0;
	if (flags & PF_LAST_FRAME) {
		frame = lastFrameIx;
	} else if (flags & PF_NEXT_FRAME) {
		frame = nextFrameIx;
	}

	int ix = (which) + (frame * numServos * 3);
	return frames[ix];
}


void 
RemoteServos::copyNextToLast() {
    memcpy(&frames[numServos * lastFrameIx], &frames[numServos * nextFrameIx], numServos);    
}

void 
RemoteServos::copyLastToCurrent() {
    memcpy(frames, frames + (lastFrameIx * numServos), numServos);    
}

void 
RemoteServos::swapNextAndLast() {
    uint8_t t = lastFrameIx;
    lastFrameIx = nextFrameIx;
    nextFrameIx = t;
}


void 
RemoteServos::fadeIntoCurrent(uint8_t distance) {
    int16_t nextOffset = nextFrameIx * numServos;
    int16_t lastOffset = lastFrameIx * numServos;
    
    int16_t len = numServos;
    for(int16_t currentOffset=0; currentOffset < len; nextOffset++, lastOffset++, currentOffset++) {
        uint32_t delta = frames[nextOffset] - frames[lastOffset];
        frames[currentOffset] = frames[lastOffset] + (uint8_t)((delta * distance) >> 8);
    }
}

void
RemoteServos::send() {

	// Always send "current". If using fades, then next and last
	// swap, but they get calculated into current via the fadeIntoCurrent
	// function. Current is always index 0, so we just directly index it

	// Serial.print("SEND\n");

	uint8_t out = frames[0];

	digitalWrite(8, (out >> 6) & 0x01);
	digitalWrite(7, (out >> 5) & 0x01);
	digitalWrite(6, (out >> 4) & 0x01);
	digitalWrite(5, (out >> 3) & 0x01);
	digitalWrite(4, (out >> 2) & 0x01);
	digitalWrite(3, (out >> 1) & 0x01);
	digitalWrite(2, (out     ) & 0x01);


	// for(uint8_t addr=0; addr<numServos; addr++) {
	// 	// shiftOut(dataPin, clockPin, MSBFIRST, addr);
	// 	// shiftOut(dataPin, clockPin, MSBFIRST, frames[addr]);

	// 	if (addr==0) {




	// 		// servo0.write(frames[addr] << 1);
	// 		// Serial.print(frames[addr], DEC);
	// 		// Serial.print("\n");
	// 	}
	// 	// peer.write(addr);
	// 	// peer.write(frames[addr]);

	// 	// Serial.print(addr, DEC);
	// 	// Serial.print(" = ");
	// 	// Serial.print(frames[addr], DEC);
	// 	// Serial.print(" [");
	// 	// Serial.print(frames[addr + numServos], DEC);
	// 	// Serial.print(", ");
	// 	// Serial.print(frames[addr + numServos], DEC);
	// 	// Serial.print("]\n");
	// }
	// Serial.print("\n");
}
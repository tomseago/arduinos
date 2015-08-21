#include "pixels.h"

Pixels::Pixels(uint16_t numPixels) : 
    numPixels(numPixels) {
    
    // Allocate our two frame buffers
    frames = (uint8_t*)calloc(3 * 3, numPixels);

    // This is our safety that keeps us from ever touching the buffers if
    // they don't exist.
    if (!frames) {
        numPixels = 0;
    } else {
        lastFrameIx = 1;
        nextFrameIx = 2;
    }
}

Pixels::~Pixels() {
    if (frames) free(frames);
}

void
Pixels::setPixelInFrame(uint16_t which, uint8_t frame, uint8_t r, uint8_t g, uint8_t b, uint8_t flags) {

    int ix = (which * 3) + (frame * numPixels * 3);
    
    // This assumes storage in rgb order, which may or may not be effecient for
    // sending if sending has a DMA structure about it. If so, the sub-class
    // can override this function and deal appropriately for "current frame"
    // which is all sending cares about and which is guaranteed to go through here.
    frames[ix++] = r;
    frames[ix++] = g;
    frames[ix  ] = b;
}

uint16_t 
Pixels::getNumPixels() {
    return numPixels;
}

void 
Pixels::setBrightness(uint8_t brightness) {
    this->brightness = brightness;
}

int16_t
Pixels::setPixel(int16_t which, uint32_t rgb, uint8_t flags){
    // TODO: See if arduino supports inlining this function in the header
    return setPixel(which, 
        (rgb >> 16) & 0x00ff,
        (rgb >>  8) & 0x00ff,
        (rgb      ) & 0x00ff,
        flags);
}

int16_t
Pixels::actualPixelForIndex(int16_t which, uint8_t flags) {
    int16_t actual = which;
    if (flags & PF_BOUNCE) {
        actual = which % ((numPixels * 2) - 1);
        if (actual > numPixels) {
            actual = (2 * numPixels) - 1 - actual;
        }
    } else {
        // Wrap mode
        while (actual < 0) {
            actual += numPixels;
        }
        actual = actual % numPixels;
    }
    
    if (actual < 0) {
        return 0;
    }
    if (actual >= numPixels) {
        return numPixels - 1;
    }

    return actual;
}

int16_t 
Pixels::setPixel(int16_t which, uint8_t r, uint8_t g, uint8_t b, uint8_t flags) {
    if (!numPixels) return 0;
    
    uint8_t frame = 0;
    if (flags & PF_LAST_FRAME) {
        frame = lastFrameIx;
    } else if (flags & PF_NEXT_FRAME) {
        frame = nextFrameIx;
    }
    
    int16_t actual = actualPixelForIndex(which, flags);
    
    if (brightness) {
        r = ((uint16_t)r * brightness) >> 8;
        g = ((uint16_t)g * brightness) >> 8;
        b = ((uint16_t)b * brightness) >> 8;
    }
    
    setPixelInFrame(actual, frame, r, g, b, flags);
    
    return actual;
}

void
Pixels::setAllPixels(uint8_t r, uint8_t g, uint8_t b, uint8_t flags) {
    for(int i=0; i<numPixels; i++) {
        setPixel(i, r, g, b, flags);
    }
}

uint32_t 
Pixels::getPixel(uint16_t which, uint8_t flags) {
    if (which > numPixels) {
        return 0;
    }    
    
    uint8_t frame = 0;
    if (flags & PF_LAST_FRAME) {
        frame = lastFrameIx;
    } else if (flags & PF_NEXT_FRAME) {
        frame = nextFrameIx;
    }
    
    int16_t actual = actualPixelForIndex(which, flags);

    int16_t offset = actual * 3 + (frame * numPixels * 3);
    uint32_t c = ((uint32_t)(frames[offset]) << 16) | ((uint32_t)(frames[offset+1]) << 8) | ((uint32_t)(frames[offset+2])    );
    
    // If we have a brightness set, we re-interpret on the way out here
    if (brightness) {
        uint8_t* c_ptr = (uint8_t*)(&c);
        c_ptr[0] = ((uint16_t)c_ptr[0] << 8) / brightness;
        c_ptr[1] = ((uint16_t)c_ptr[1] << 8) / brightness;
        c_ptr[2] = ((uint16_t)c_ptr[2] << 8) / brightness;
    }
    return c;
}

void 
Pixels::copyNextToLast() {
    memcpy(&frames[numPixels * lastFrameIx * 3], &frames[numPixels * nextFrameIx * 3], numPixels * 3);    
}

void 
Pixels::copyLastToCurrent() {
    memcpy(frames, frames + (lastFrameIx * numPixels  * 3), numPixels * 3);    
}

void 
Pixels::swapNextAndLast() {
    uint8_t t = lastFrameIx;
    lastFrameIx = nextFrameIx;
    nextFrameIx = t;
}


void 
Pixels::fadeIntoCurrent(uint8_t distance) {
    int16_t nextOffset = nextFrameIx * numPixels * 3;
    int16_t lastOffset = lastFrameIx * numPixels * 3;
    
    int16_t len = numPixels * 3;
    for(int16_t currentOffset=0; currentOffset < len - 2; nextOffset++, lastOffset++, currentOffset++) {
        uint32_t delta = frames[nextOffset] - frames[lastOffset];
        frames[currentOffset] = frames[lastOffset] + (uint8_t)((delta * distance) >> 8);
    }
}

uint32_t
Pixels::Color(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t c;
    c = r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b;
    return c;
}



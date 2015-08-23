#ifndef _PIXELS_H_
#define _PIXELS_H_

#define PF_CURRENT_FRAME    0
#define PF_LAST_FRAME       (1 << 1)
#define PF_NEXT_FRAME       (1 << 2)
#define PF_BOUNCE           (1 << 3)

#include "application.h"

class Pixels {
protected:
    uint16_t numPixels;
    uint8_t* frames;
    uint8_t lastFrameIx;
    uint8_t nextFrameIx;

    uint8_t brightness;
    
    void setPixelInFrame(uint16_t which, uint8_t frame, uint8_t r, uint8_t g, uint8_t b);
    
    int16_t actualPixelForIndex(int16_t which, uint8_t flags);
    
public:
    Pixels(uint16_t numPixels);
    ~Pixels();
    
    uint16_t getNumPixels();
    
    void setBrightness(uint8_t brightness);
    
    int16_t setPixel(int16_t which, uint32_t rgb, uint8_t flags = PF_CURRENT_FRAME);
    int16_t setPixel(int16_t which, uint8_t r, uint8_t g, uint8_t b, uint8_t flags = PF_CURRENT_FRAME);
    
    void setAllPixels(uint8_t r, uint8_t g, uint8_t b, uint8_t flags = PF_CURRENT_FRAME);
    
    uint32_t getPixel(uint16_t which, uint8_t flags = PF_CURRENT_FRAME);
    
    void copyNextToLast();
    void copyLastToCurrent();
    void swapNextAndLast();
    void fadeIntoCurrent(uint8_t distance);
    
    uint32_t Color(uint8_t r, uint8_t g, uint8_t b);


    virtual void send() = 0;
};

#endif // ifndef _PIXELS_H_




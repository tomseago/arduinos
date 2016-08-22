#include "ws2801pixels.h"

WS2801Pixels::WS2801Pixels(uint16_t numPixels) :
    Pixels(numPixels) {
    
    // Setup SPI
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    
#ifdef SPI_CLOCK_DIV256
    SPI.setClockDivider(SPI_CLOCK_DIV256); // 1MHz max, else flicker
#else
    SPI.setClockDivider(SPI_CLOCK_DIV128); // 1MHz max, else flicker
#endif
}

uint32_t
WS2801Pixels::send() {
    int16_t len = numPixels * 3;

    for(int16_t currentOffset=0; currentOffset < len; currentOffset++) {
        SPI.transfer(frames[currentOffset]);
    }
    
    // This "latches" the data into the pixels. I think the _actual_ delay necessary
    // is only 500ms though from the data sheet.
    delay(1); 

    // No offset
    return 0;
}
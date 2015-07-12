
#include <mt-harnass.h>
// #include <mt-ui.h>

// extern MTUI ui;


MTHarnass::MTHarnass(uint8_t sashPin) 
    : sash(2, sashPin, NEO_GRB + NEO_KHZ800) {

}

void MTHarnass::begin() {
    sash.begin();
}

void MTHarnass::loop() {
    // Animate!
}

void MTHarnass::solidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t flags) {

    if (flags & F_SASH) {
        for(uint8_t i=0; i<sash.numPixels(); i++) {
            sash.setPixelColor(i, r, g, b);
        }
        sash.show();
    }

}
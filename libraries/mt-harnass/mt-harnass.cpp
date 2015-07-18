
#include <mt-harnass.h>
// #include <mt-ui.h>

// extern MTUI ui;


MTHarnass::MTHarnass(uint8_t sashPin, uint8_t armPin) 
    : sash(24, sashPin, NEO_GRB + NEO_KHZ800),
      arm(32, armPin, armPin+1) {

}

void MTHarnass::begin() {
    sash.begin();
    sash.setBrightness(128);

    //arm.updatePins(5);
    arm.begin();
    // TODO: Add brightness capability to LPD8806 library
    // arm.setBrightness(128);
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

    if (flags & F_ARM) {
        for(uint8_t i=0; i<arm.numPixels(); i++) {
            arm.setPixelColor(i, r, g, b);
        }
        arm.show();
    }

}
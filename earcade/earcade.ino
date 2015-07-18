
#include <mtview.h>

#include <mtui.h>

#include <mt-neopixel.h>
#include <mtlpd8806.h>
#include <SPI.h>
#include <mt-harnass.h>

MTUI ui(A0);
MTHarnass harnass(5.

, 0);

void setup() {

  harnass.begin();
  ui.begin();
}

void loop() {
  ui.loop();
  harnass.loop();
}

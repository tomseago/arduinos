
#include <mtview.h>

#include <mtui.h>

#include <mt-neopixel.h>
#include <mt-harnass.h>

MTUI ui(A0);
MTHarnass harnass(6);

void setup() {

  ui.begin();
  harnass.begin();
}

void loop() {
  ui.loop();
  harnass.loop();
}

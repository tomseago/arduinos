// The libraries are needed for the LED driver code I'm using.
// They are not related to the brightness sensing
#include <SPI.h>
#include <pixels.h>
#include <ws2812pixels.h>

// This sets up the pixel library. Again, not directly
// related to brightness, but using this as an example of doing
// something with the value that is detected
WS2812Pixels row0 = WS2812Pixels(2, 6); // 2 pixels on pin 6
WS2812Pixels row1 = WS2812Pixels(2, 7); // 2 pixels on pin 6

// This value defines which pin will be used for the input. If
// you connect the potentiometer to a different pin, like A1, change
// this value to match
#define POT_PIN  A0


void setup() {

  // During setup we set the proper mode for the input pin
  // so that we can later use analog_read() with it.
  pinMode(POT_PIN, INPUT);

  // We set default brightness values for both rows here. Later
  // we will modify the row0 brightness, but not the row1
  // brightness so we can tell that things are working.
  row0.setBrightness(255);
  row1.setBrightness(255);
}

void loop() {

  // Read in the value from the potentiometer. The value read
  // will be between 0 and 1024. That's the resolution of the
  // built in analog to digital converter.
  int brightness = analogRead(A0);

  // Depending on how your pixel library works, you probably need
  // to scale the range from 0-1024 down to 0-255 instead. That's
  // easy to do by dividing by 4.
  brightness = brightness / 4;

  // Then we just set that value into the library. In this example
  // we have setup two rows of pixels that are independent, but
  // we only change the value of row0 so it can be seen in contrast
  // to the other row.

  // Because of the way the brightness is encoded inside the library,
  // a brightness of 0 is the same as a brightness of 255. Thus
  // we add 1 to make sure that a 0 value never occurs, or else
  // when the knob is turned all the way down the lights suddenly
  // return to full brightness.
  row0.setBrightness(brightness+1);

  // The rest of this is just some simple animation code for funsies.
  // Note that depending on how your animations work, the brightness
  // is only set above. So if the animation does an internal loop,
  // the 3 lines used to read, scale, and then set the brightness
  // would need to be inside the animation loop itself.

  // For example, the way the following animation is written, the
  // brightness will only be changed immediately before the red
  // value is shown. If you move the knob while the delays between
  // setting the colors is happening (which is most of the time),
  // the color won't change immediately.
  
  // Set all pixels to red
  row0.setAllPixels(255, 0, 0);
  row1.setAllPixels(255, 0, 0);
  row0.send();
  row1.send();

  // Put the computer to sleep for 0.5 second.
  delay(500);
  
  // Set all pixels to yellow
  row0.setAllPixels(255, 255, 0);
  row1.setAllPixels(255, 255, 0);
  row0.send();
  row1.send();
  
  // Put the computer to sleep for 0.5 second.
  delay(500);

  // Set all pixels to purple
  row0.setAllPixels(255, 0, 255);
  row1.setAllPixels(255, 0, 255);
  row0.send();
  row1.send();
  
  // Put the computer to sleep for 0.5 second.
  delay(500);
}

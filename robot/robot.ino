#include <SoftwareSerial.h>

//#include <Servo.h>

// Needed to cause inclusion of SPI code used for pixels
#include <SPI.h>

#include <pixels.h>
#include <ws2812pixels.h>
#include <two_channels.h>
#include <animator.h>

//#define START_ANGLE 80
//#define END_ANGLE 100

// 21 pixels for max 500ma, typical about 200ma
WS2812Pixels eyes = WS2812Pixels(10, 12);
WS2812Pixels heart = WS2812Pixels(17, 13);

TwoChannels pixels = TwoChannels(eyes, heart);

RemoteServos servos(9, 10, 1);

Animator animator = Animator(pixels, servos);
uint32_t start = millis();

////////////////
// Test Code

void setupXX() {
  Serial.begin(19200);
  Serial.print("Setup\n");

  servos.begin();
}

void loopXX() {
  servos.setServo(0, 90, PF_CURRENT_FRAME);
  servos.send();
  delay(20000);
  return;

  // 130 - 50 works without head, but seems to much with the head
  
  servos.setServo(0, 120, PF_CURRENT_FRAME);
  servos.send();
  delay(2000);

  servos.setServo(0, 80, PF_CURRENT_FRAME);
  servos.send();
  delay(1000);

  servos.setServo(0, 60, PF_CURRENT_FRAME);
  servos.send();
  delay(2000);

  servos.setServo(0, 100, PF_CURRENT_FRAME);
  servos.send();
  delay(1000);

}
//
/////////////////


void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  Serial.print("Setup\n");
  servos.begin();

  animator.begin();
  animator.startAnimation(ANIM_ROBOT_HEAD_SHRUGS);
//  animator.startAnimation(ANIM_ROBOT_HEART_BEAT);

//  animator.startAnimation(ANIM_ROBOT_RAINBOW_WAKE_FILL);

}

void loop() {
  animator.loop();
}

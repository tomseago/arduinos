#include <Servo.h>

Servo left;
Servo right;

#define START_ANGLE 80
#define END_ANGLE 100

// Left
// 50 upper limit
// 90 lower limit
//
// Right
// 110 lower
// 70 upper


void setup() {
  // put your setup code here, to run once:
  left.attach(9);
  
  right.attach(10);

  left.write(0);
  right.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:

  left.write(40);
  right.write(100);

  delay(2000);
  

  left.write(100);
  right.write(50);

  delay(1000);
}

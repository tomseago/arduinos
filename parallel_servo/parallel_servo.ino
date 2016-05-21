#include <Servo.h>

Servo servo;

void setup() {

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

  servo.attach(9);

  Serial.begin(19200);
}

void loop() {

  // Read a byte
  uint8_t in = (digitalRead(2) << 6) + 
     (digitalRead(3) << 5) +
     (digitalRead(4) << 4) +
     (digitalRead(5) << 3) +
     (digitalRead(6) << 2) +
     (digitalRead(7) << 1) +
     (digitalRead(8)     );

  Serial.print(in, DEC);
  Serial.print("\n");
  
  servo.write(in << 1);
  
  delay(1);
}

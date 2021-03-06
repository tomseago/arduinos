#include <SoftwareSerial.h>

#include <Servo.h>
#include <SPI.h>

#define RX_PIN 1
//#define DATA_PIN 5

Servo servoA;
Servo servoB;

byte num_ffs = 0;
bool hadData = false;

///////
#include <pixels.h>
#include <ws2812pixels.h>
#include <two_channels.h>
#include <animator.h>

WS2812Pixels eyes = WS2812Pixels(11, 10);

RemoteServos servos(9, 10, 1);

Animator animator = Animator(eyes, servos);

///////

//#define BUFFER_SIZE 10
//volatile uint8_t input[BUFFER_SIZE];
//volatile uint8_t inStart = 0;
//volatile uint8_t inEnd = 0;
//volatile uint8_t inAvail = 0;
//volatile uint8_t inProcessByte = 0;
//volatile uint8_t bitsNeeded = 8;
//volatile uint32_t lastReadAt = 0;
//
//void shiftISR() {
//
//  uint32_t now = millis();
//  if (now - lastReadAt > 500) {
//    // After 500ms since last read, reset everything
//    inStart = 0;
//    inEnd = 0;
//    inAvail = 0;
//    inProcessByte = 0;
//    bitsNeeded = 8;
//  }
//  lastReadAt = now;
//  
//  inProcessByte = inProcessByte << 1;
//  if (digitalRead(DATA_PIN) == HIGH) {
//    inProcessByte |= 1;
//  }
//
//  bitsNeeded--;
//  if (bitsNeeded == 0) {
//    // Write into the end
//    input[inEnd] = inProcessByte;
//    inEnd++;
//    inAvail++;
//    if (inEnd == BUFFER_SIZE) {
//      inEnd = 0;
//    }
//
//    // Did we just roll over?
//    if (inEnd == inStart) {
//      // Oops, move the end back by one
//      if (inEnd==0) {
//        inEnd = BUFFER_SIZE - 1;
//      } else {
//        inEnd--;
//      }
//      inAvail--;
//    }
//
//    // Reset for next byte
//    bitsNeeded = 8;
//    inProcessByte = 0;
//  }
//}
//
//uint8_t readByte() {
//  if ((!inAvail) || inEnd == inStart) return 0;
//
//  uint8_t out = input[inStart];
//  inStart++;
//  inAvail--;
//
//  if (inStart == BUFFER_SIZE) {
//    inStart = 0;
//  }
//
//  return out;
//}

//////////
void setup() {
  servos.begin();
  animator.begin();
  animator.startAnimation(ANIM_ROBOT);
}

void loop() {
  // put your main code here, to run repeatedly:

  animator.loop();
}
///////////
//
//SoftwareSerial peer =  SoftwareSerial(2, 5);
//
//void setupZZ() {
//  servoA.attach(9);
//  servoB.attach(10);
//
////  pinMode(CLOCK_PIN, INPUT);
////  pinMode(DATA_PIN, INPUT);
//
//  pinMode(13, OUTPUT);
//  digitalWrite(13, HIGH);
//
//  //Serial.begin(19200); 
//
//  peer.begin(19200);
//  
////  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), shiftISR, RISING);
//}
//
//void loopX() {
//  servoA.write(45);
//  digitalWrite(13, LOW);
//  delay(1000);
//
//  servoA.write(135);
//  digitalWrite(13, HIGH);
//  delay(1000);
//}
//
//
//#define WAITING_FOR_PREAMBLE 0
//#define NEED_ADDRESS 1
//#define NEED_VALUE 2
//
//uint8_t state = WAITING_FOR_PREAMBLE;
//uint8_t currentAddress = 0xff;
//
//
//void loop() {  
//  if (peer.available() == 0) return;
//
//  uint8_t c = peer.read();
//
//  switch(state) {
//    case WAITING_FOR_PREAMBLE:
//      digitalWrite(13, HIGH);
//      if (c == 0xff) {
////        Serial.print("Got 0xff\n");
//        num_ffs++;
//        if (num_ffs >= 5) {
//          hadData = false;
//          state = NEED_ADDRESS;
//        }
//      } else {
////        Serial.print("Non-FF ");
////        Serial.print(c, HEX);
////        Serial.print("\n");
//      }
//      break;
//
//    case NEED_ADDRESS:
//      digitalWrite(13, LOW);
//      if (c == 0xff) {
//        if (hadData) {
////          Serial.print("0xff address resets us\n");
//          state = WAITING_FOR_PREAMBLE;
//        } else {
////          Serial.print("Ignoring extra 0xff\n");
//        }
//      } else if (c>1) {
////        Serial.print("Bad address. Ignoring\n");
//      } else {
//        // Is a good address
//        currentAddress = c;
//        state = NEED_VALUE;
//      }
//      break;
//
//    case NEED_VALUE:
//      // All values are valid. No reset on 0xff
//      if (currentAddress == 0) {
//        servoA.write(c);
//      } else if (currentAddress == 1) {
//        servoB.write(c);
//      }
////      Serial.print(currentAddress, DEC);
////      Serial.print(" = ");
////      Serial.print(c, DEC);
////      Serial.print("\n");
//
//      state = NEED_ADDRESS;
//      break;
//  }
//}

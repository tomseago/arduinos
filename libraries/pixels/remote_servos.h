#ifndef _REMOTE_SERVO_H_
#define _REMOTE_SERVO_H_

#include <Arduino.h>
//#include "application.h"

// #include <SoftwareSerial.h>
// #include <Servo.h>

// Need flag values from pixels.h
#include "pixels.h"

class RemoteServos {
protected:
	uint8_t numServos;
	uint8_t* frames;
	uint8_t lastFrameIx;
	uint8_t nextFrameIx;

	virtual void setServoInFrame(uint8_t which, uint8_t frame, uint8_t value, uint8_t flags);

	// SoftwareSerial peer;

	// Servo servo0;

public:
	RemoteServos(uint8_t rxPin, uint8_t txPin, uint8_t numServos);
	void begin();

	virtual uint8_t getNumServos();

	uint8_t setServo(uint8_t which, uint8_t value, uint8_t flags);
	void setAllServos(uint8_t value, uint8_t flags);

	virtual uint8_t getServo(uint8_t which, uint8_t flags);

	virtual void copyNextToLast();
    virtual void copyLastToCurrent();
    virtual void swapNextAndLast();
    virtual void fadeIntoCurrent(uint8_t distance);

    virtual void send();

};
#endif // _REMOTE_SERVO_H_

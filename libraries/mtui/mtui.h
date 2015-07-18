#ifndef _MTUI_H_
#define _MTUI_H_

#include <mtview.h>

#include <avr/pgmspace.h>


class MTUI {

public:
    MTUI(uint8_t pin);
    void begin();
    void end();

    void loop();

private:
    uint8_t pin;

    uint16_t refOne;
    uint16_t refTwo;
    uint16_t refThree;
    uint8_t setupState;

    int lastPinVal;
    int lastRefVal;
    uint8_t debounceCount;
    uint8_t lastButton;
    uint8_t registeredButton;

    void showDebug();

    void registerButton();
    void resetSetupState();
    void renderSetupState();

    void singleClick();

    void menuMove(bool down);
    void menuSelect(bool into);

    void navigateTo(uint8_t menu);
    void pushCrumb(uint8_t crumb, uint8_t cursor);
    uint16_t popCrumb();

    uint8_t menuNum;
    uint8_t menuCursor;

    uint16_t breadcrumbs[10];
    uint8_t bcLen;

    void renderMenu();
    void printMenuItem(int8_t menuIx);

};

#endif // #ifndef _MTUI_H_
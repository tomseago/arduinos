#ifndef _MTUI_H_
#define _MTUI_H_

#include <mtview.h>

#include <avr/pgmspace.h>

enum inputMode_t {
    MODE_SETUP_ONE = 0,
    MODE_SETUP_TWO,
    MODE_SETUP_THREE,
    MODE_SETUP_FOUR,

    MODE_COMMAND,

    MODE_MENU,
    MODE_COLOR_SELECT,
    MODE_REGISTERS,
    MODE_BRIGHTNESS
};

enum commandMode_t {
    COMMAND_MODE_NORMAL = 0,
    COMMAND_MODE_BRIGHTNESS,
    COMMAND_MODE_ANIMATION
};

class MTUI {

public:
    MTUI(uint8_t pin);
    void begin();
    void end();

    void loop();

    inputMode_t inputMode;

    // Registers for animation use
    uint8_t regMomentary = 0;
    bool regA = false;
    bool regB = false;
    bool regC = false;

    // Will stay at bottom of screen until overwritten
    char msg[20];

    void setMsg(const char* str);

private:
    uint8_t pin;

    uint16_t refOne;
    uint16_t refTwo;
    uint16_t refThree;

    int lastPinVal;
    int lastRefVal;
    uint8_t lastButton;
    int32_t lastButtonStart;

    uint32_t command;
    bool returnToCommand;

    // For registers
    bool inShiftMode;

    void showDebug();

    void registerButton();

    void resetSetupState();

    commandMode_t commandMode;
    void doCommand();
    void doNormalCommand();
    void doBrightnessCommand();
    void doAnimationCommand();

    void menuMove(bool down);
    void menuSelect(bool into);

    void navigateTo(uint8_t menu);
    void pushCrumb(uint8_t crumb, uint8_t cursor);
    uint16_t popCrumb();

    uint8_t menuNum;
    uint8_t menuCursor;

    uint16_t breadcrumbs[10];
    uint8_t bcLen;

    void render();
    void renderSetupState();
    void renderCommand();
    void renderMenu();
    void printMenuItem(int8_t menuIx);
    void renderColorSelect();
    void renderRegisters();

    void renderBrightness();
 
};

#endif // #ifndef _MTUI_H_

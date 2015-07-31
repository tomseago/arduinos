
#include <mtui.h>

#include <mt-harnass.h>
extern MTHarnass harnass;

#include "stdio.h"
#include "string.h"



#define MENU_TOP    0
#define MENU_COLORS 1
#define MENU_ANIMS  2
#define MENU_SPEED  3

// This is actually number plus 1 :(
uint8_t const menuMax[] = { 6, 13, 8, 5 };

#define SETUP_STATE_ONE   1
#define SETUP_STATE_TWO   2
#define SETUP_STATE_THREE 3
#define SETUP_STATE_FOUR  4
#define SETUP_STATE_COMPLETE 10

MTUI::MTUI(uint8_t pin) 
    : pin(pin), registeredButton(0), setupState(SETUP_STATE_ONE),
    refOne(500), refTwo(500), refThree(500),
    inputMode(MODE_MENU) {

}

void MTUI::begin() {
    uView.begin();

    pinMode(pin, INPUT);
    pinMode(pin+1, INPUT);

    resetSetupState();
    renderSetupState();
    uView.display();
}

void MTUI::end() {
    uView.end();
}

void MTUI::loop() {
    
    // Input section
    int refVal = analogRead(pin+1);

    int pinVal = analogRead(pin);
    int delta = refVal - pinVal;
    lastPinVal = pinVal;
    lastRefVal = refVal;

    uint8_t button = 0;
    if (delta < refOne) {
        button = 1;
    } else if (delta < refTwo) {
        button = 2;
    } else if (delta < refThree) {
        button = 3;
    } else if (delta < 501) {
        button = 4;
    }    
    

    

    if (button == lastButton) {
        debounceCount++;

        if (debounceCount == 20) {
            registerButton();
        }
        // TODO: Long button presses????

        // For now, just bail 
        //showDebug();
        return;
    }

    // A new button has just been pressed
    lastButton = button;
    debounceCount = 0;

    //showDebug();
}

void MTUI::showDebug() {
    // Debug pin voltage
    uView.setCursor(0,0);
    char buf[10];
    sprintf(buf, "%.3d %3d", lastPinVal, lastRefVal - lastPinVal);
    uView.print(buf);
    uView.display();    
}


void MTUI::registerButton() {
    if (lastButton == registeredButton) {
        // We already did this button. We require a debounced 0
        // button be registered (or at least a debounced something
        // else) before we take action
        return;
    }

    switch(setupState) {
        case SETUP_STATE_ONE:
            if (lastButton == 1) {
                refOne = (lastRefVal - lastPinVal) + 10;
                setupState = SETUP_STATE_TWO;
            }
            break;

        case SETUP_STATE_TWO:
            if (lastButton == 0) break;
            if (lastButton != 2) {
                // Button 1 wasn't really button 1, so reset and start over
                resetSetupState();
                break;
            }
            refTwo = (lastRefVal - lastPinVal);
            refOne -= 10;
            refOne = refOne + ((refTwo - refOne)/2);
            refTwo += 10;
            setupState = SETUP_STATE_THREE;
            break;

        case SETUP_STATE_THREE:
            if (lastButton == 0) break;
            if (lastButton != 3) {
                // Button 1 || 2 wasn't really button 1 || 2, so reset and start over
                resetSetupState();
                break;
            }
            refThree = (lastRefVal - lastPinVal);
            refTwo -= 10;
            refTwo = refTwo + ((refThree - refTwo)/2);
            refThree += 10;
            setupState = SETUP_STATE_FOUR;
            break;

        case SETUP_STATE_FOUR:
            if (lastButton == 0) break;
            if (lastButton != 4) {
                // Button 1 || 2 wasn't really button 1 || 2, so reset and start over
                resetSetupState();
                break;
            }
            {
              int d = (lastRefVal - lastPinVal);
              refThree -= 10;
              refThree = refThree + ((d - refThree)/2);
            }
            setupState = SETUP_STATE_COMPLETE;

            harnass.startAnimation(ANIM_RAND_BRIGHT);

            render();
            break;



        case SETUP_STATE_COMPLETE:
            // Take action using lastButton because it is new
            singleClick();
            break;
    }

    if (setupState != SETUP_STATE_COMPLETE) {
        renderSetupState();
    }

    // TODO: Long press stuff?????

    uView.display();

    // Store the registered button for future
    registeredButton = lastButton;
}

void MTUI::resetSetupState() {
    refOne = refTwo = refThree = 500;
    setupState = SETUP_STATE_ONE;
}

void MTUI::renderSetupState() {
    uView.clear(PAGE);

    uView.setCursor(0,0);
    uView.print("<BTN SETUP>");
    uView.setCursor(12,12);

    harnass.solidColor(0, 64, 64, F_SASH);
    switch(setupState) {
        case SETUP_STATE_ONE:
            uView.print("1");
            harnass.solidColor(255, 0, 0, F_ARM);
            break;
        case SETUP_STATE_TWO:
            uView.print("2");
            harnass.solidColor(0, 255, 0, F_ARM);
            break;
        case SETUP_STATE_THREE:
            uView.print("3");
            harnass.solidColor(0, 0, 255, F_ARM);
            break;
        case SETUP_STATE_FOUR:
            uView.print("4");
            harnass.solidColor(255, 255, 255, F_ARM);
            break;
    }
    
    uView.setCursor(0,20);
    char buf[12];
    sprintf(buf, "%.3d %.3d", refOne, refTwo);
    uView.print(buf);
    sprintf(buf, "%.3d", refThree);
    uView.setCursor(0,28);
    uView.print(buf);
}


void MTUI::singleClick() {

    // if (showHandler) {
    //     // We are in show interactive mode, so let it handle
    //     // the click. It is required to un-set interactive mode
    //     // when it is done
    //     showHandler->handleSingleClick(lastButton);
    //     return;
    // }

    switch(inputMode) {
        case MODE_MENU:
            // Menu mode
            switch(lastButton) {
            case 1: // closest to thumb
                // up
                menuMove(false);
                break;

            case 2:
                // down
                menuMove(true);
                break;

            case 3: 
                // select / right
                menuSelect(true);
                break;

            case 4: // furthest from thumb
                // back / left
                menuSelect(false);
                break;
            }
            break; // MODE_MENU

        case MODE_COLOR_SELECT:
            switch(lastButton) {
                case 1:
                    harnass.changeColorPos(32);
                    break;
                case 2:
                    harnass.changeColorPos(-32);
                    break;
                case 3:
                    harnass.changeColorPos(2);
                    break;
                case 4:
                    inputMode = MODE_MENU;
                    break;
            }
            break; // MODE_COLOR_SELECT

        case MODE_BRIGHTNESS:
            switch(lastButton) {
                case 1:
                    harnass.brighter(32);
                    break;
                case 2:
                    harnass.darker(32);
                    break;
                case 3:
                    harnass.muted = !harnass.muted;
                    break;
                case 4:
                    inputMode = MODE_MENU;
                    break;
            }
            break; // MODE_BRIGHTNESS

        case MODE_REGISTERS:
            if (!inShiftMode) {
                // No shift
                if (lastButton < 4) {
                    regMomentary = lastButton;
                } else {
                    inShiftMode = true;
                }
            } else {
                // Shift
                switch(lastButton) {
                    case 1:
                        // harnass.solidColor(128,0,0,F_ARM);
                        regA = !regA;
                        break;
                    case 2:
                        // harnass.solidColor(0,128,0,F_ARM);
                        regB = !regB;
                        break;
                    case 3:
                        // harnass.solidColor(0,0,128,F_ARM);
                        regC = !regC;
                        break;
                    case 4:
                        // Out of register mode
                        inputMode = MODE_MENU;
                        break;
                }
                if (lastButton > 0) {
                    inShiftMode = false;
                }
            }
            break; // MODE_REGISTERS
    }

    render();
}

void MTUI::menuMove(bool down) {
    if (down) {
        if (menuCursor < menuMax[menuNum]-1) {
            menuCursor++;
        }
    } else {
        if (menuCursor > 0) {
            menuCursor--;
        }
    }
}


void MTUI::menuSelect(bool into) {
    if (into) {
        switch(menuNum) {
        case MENU_TOP:
            switch(menuCursor) {
            case 0:
                inputMode = MODE_REGISTERS;
                renderRegisters();
                break;

            case 1:
                inputMode = MODE_COLOR_SELECT;
                renderColorSelect();
                break;

            case 2:
                navigateTo(MENU_ANIMS);
                break;

            case 3:
                navigateTo(MENU_SPEED);
                break;

            case 4:
                navigateTo(MENU_COLORS);
                break;

            case 5:
                inputMode = MODE_BRIGHTNESS;
                renderBrightness();
                break;
            }
            break;

        case MENU_ANIMS:
            switch(menuCursor) {
            case 0:
                harnass.startAnimation(ANIM_NONE);
                break;

            case 1:
                harnass.startAnimation(ANIM_ALL_BLINK);
                break;

            case 2:
                harnass.startAnimation(ANIM_FLOOD);
                break;

            case 3:
                harnass.startAnimation(ANIM_HRAINBOW);
                break;

            case 4:
                harnass.startAnimation(ANIM_TRACER);
                break;

            case 5:
                harnass.startAnimation(ANIM_RAND_MOVER);
                break;

            case 6:
                harnass.startAnimation(ANIM_RAND_ALL);
                break;

            case 7:
                harnass.startAnimation(ANIM_RAND_BRIGHT);
                break;


            }
            break;

        case MENU_COLORS:
            harnass.startAnimation(ANIM_NONE);

            switch(menuCursor) {
            case 0: // Red
                harnass.solidColor(255, 0, 0, F_BOTH);
                break;

            case 1: // Orange
                harnass.solidColor(255, 128, 0, F_BOTH);
                break;

            case 2: // Yellow
                harnass.solidColor(255, 255, 0, F_BOTH);
                break;

            case 3: // Neon Green
                harnass.solidColor(128, 255, 0, F_BOTH);
                break;

            case 4: // Green
                harnass.solidColor(0, 255, 0, F_BOTH);
                break;

            case 5: // Pale Green
                harnass.solidColor(0, 255, 128, F_BOTH);
                break;

            case 6: // Cyan
                harnass.solidColor(0, 255, 255, F_BOTH);
                break;

            case 7: // Sky Blue
                harnass.solidColor(0, 128, 255, F_BOTH);
                break;

            case 8: // Blue
                harnass.solidColor(0, 0, 255, F_BOTH);
                break;

            case 9: // Purple
                harnass.solidColor(128, 0, 255, F_BOTH);
                break;

            case 10: // Magenta
                harnass.solidColor(255, 0, 255, F_BOTH);
                break;

            case 11: // White
                harnass.solidColor(255, 255, 255, F_BOTH);
                break;

            case 12: // Black
                harnass.solidColor(0, 0, 0, F_BOTH);
                break;
            }
            break;

        case MENU_SPEED:
            switch(menuCursor) {
            case 0:
                harnass.resetSpeed();
                break;

            case 1:
                harnass.changeSpeed(-80);
                break;

            case 2:
                harnass.changeSpeed(80);
                break;

            case 3:
                harnass.changeSpeed(-25);
                break;

            case 4:
                harnass.changeSpeed(25);
                break;

            }
            break;
        }

    } else {
        if (bcLen > 0) {
            uint16_t c = popCrumb();
            menuNum = c >> 8 & 0x00ff;
            menuCursor = c & 0x00ff;
        } else {
            // On top menu reset to beginning item
            menuCursor = 0;
        }
    }
}

void MTUI::navigateTo(uint8_t menu) {
    pushCrumb(menuNum, menuCursor);
    menuCursor = 0;
    menuNum = menu;    
}

void MTUI::pushCrumb(uint8_t crumb, uint8_t pos) {
    breadcrumbs[bcLen] = (crumb<<8) + pos;
    bcLen++;
}

uint16_t MTUI::popCrumb() {
    if (bcLen==0) return 0;

    bcLen--;
    return breadcrumbs[bcLen];
}


void MTUI::render() {

    switch(inputMode) {
        case MODE_MENU:
            renderMenu();
            break;

        case MODE_COLOR_SELECT:
            renderColorSelect();
            break;

        case MODE_REGISTERS:
            renderRegisters();
            break;

        case MODE_BRIGHTNESS:
            renderBrightness();
            break;
    }
}

void MTUI::renderMenu() {
    uView.clear(PAGE);

    uView.setCursor(0,0);
    switch(menuNum) {
        case MENU_TOP:
            uView.print("TOP");
            break;

        case MENU_COLORS:
            uView.print("Colors");
            break;

        case MENU_ANIMS:
            uView.print("Anims");
            break;

        case MENU_SPEED:
            uView.print("Speed");
            break;
    }

    uView.setCursor(  6,  9 );
    printMenuItem(menuCursor - 2);

    uView.setCursor(  4, 18 );
    printMenuItem(menuCursor - 1);
    

    uView.setCursor(  0, 27 );
    printMenuItem(menuCursor);
    

    uView.setCursor(  4, 36 );
    printMenuItem(menuCursor + 1);
    

    uView.setCursor(  6, 45 );
    printMenuItem(menuCursor + 2);


}

void MTUI::printMenuItem(int8_t menuIx) {
    switch(menuNum) {
    case MENU_TOP:
        switch(menuIx) {

        case 0:
            uView.print(">Registers");
            break;

        case 1:
            uView.print(">Color");
            break;

        case 2:
            uView.print("Animations");
            break;

        case 3:
            uView.print("Speed");
            break;

        case 4:
            uView.print("Colors");
            break;

        case 5:
            uView.print(">Brightness");
            break;
        }
        break;

    case MENU_ANIMS: 
        switch(menuIx) {
        case 0:
            uView.print("All Off");
            break;

        case 1:
            uView.print("All Blink");
            break;

        case 2:
            uView.print("Flood");
            break;

        case 3:
            uView.print("H Rainbow");
            break;

        case 4:
            uView.print("Tracer");
            break;

        case 5:
            uView.print("Rand Mover");
            break;

        case 6:
            uView.print("Rand All");
            break;

        case 7:
            uView.print("Rand Bright");
            break;
        }
        break;

    case MENU_COLORS:
        switch(menuIx) {
        case 0:
            uView.print("Red");
            break;

        case 1:
            uView.print("Orange");
            break;

        case 2:
            uView.print("Yellow");
            break;

        case 3:
            uView.print("N Green");
            break;

        case 4:
            uView.print("Green");
            break;

        case 5:
            uView.print("P Green");
            break;
        case 6:
            uView.print("Cyan");
            break;

        case 7:
            uView.print("S Blue");
            break;

        case 8:
            uView.print("Blue");
            break;

        case 9:
            uView.print("Purple");
            break;

        case 10:
            uView.print("Magenta");
            break;

        case 11:
            uView.print("White");
            break;

        case 12:
            uView.print("Black");
            break;
        }
        break;// END MENU_COLORS

        case MENU_SPEED: 
            switch(menuIx) {
            case 0:
                uView.print("Reset");
                break;

            case 1:
                uView.print("++FASTER");
                break;

            case 2:
                uView.print("--SLOWER");
                break;

            case 3:
                uView.print("fast");
                break;

            case 4:
                uView.print("slower");
                break;
            }
            break; // END MENU_SPEED

    }




}



void MTUI::renderColorSelect() {
    uView.clear(PAGE);

    uView.setCursor(0,0);

    char buf[10];

    sprintf(buf, "R: %.3d", (harnass.selectedColor >> 16) & 0xff);
    uView.setCursor(0,0); uView.print(buf);

    sprintf(buf, "G: %.3d", (harnass.selectedColor >> 8) & 0xff);
    uView.setCursor(0,10); uView.print(buf);
    
    sprintf(buf, "B: %.3d", (harnass.selectedColor     ) & 0xff);
    uView.setCursor(0,20); uView.print(buf);
    

    uView.display();

}

void MTUI::renderRegisters() {
    uView.clear(PAGE);

    uView.setCursor(0,0);

    char buf[10];

    uView.setCursor(0,0); uView.print("Registers");

    sprintf(buf, "%d", regMomentary);
    uView.setCursor(0,20); uView.print(buf);

    if (regA) {
        uView.setCursor(8, 28); uView.print("A");
    }
    if (regB) {
        uView.setCursor(18, 28); uView.print("B");
    }
    if (regC) {
        uView.setCursor(28, 28); uView.print("C");
    }

    uView.display();

}

void MTUI::renderBrightness() {
    uView.clear(PAGE);


    char buf[10];

    uView.setCursor(0,0); uView.print("Brightness");

    sprintf(buf, "%d", harnass.sash.getBrightness());
    uView.setCursor(0,20); uView.print(buf);
}
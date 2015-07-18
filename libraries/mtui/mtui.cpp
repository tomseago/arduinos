
#include <mtui.h>

#include <mt-harnass.h>
extern MTHarnass harnass;

#include "stdio.h"
#include "string.h"

#define MENU_TOP    0
#define MENU_COLORS 1

uint8_t const menuMax[] = { 4, 11 };

#define SETUP_STATE_ONE   1
#define SETUP_STATE_TWO   2
#define SETUP_STATE_THREE 3
#define SETUP_STATE_FOUR  4
#define SETUP_STATE_COMPLETE 10

MTUI::MTUI(uint8_t pin) 
    : pin(pin), registeredButton(0), setupState(SETUP_STATE_ONE),
    refOne(500), refTwo(500), refThree(500) {

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
        showDebug();
        return;
    }

    // A new button has just been pressed
    lastButton = button;
    debounceCount = 0;

    showDebug();
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
            renderMenu();
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
    uView.print("[ BTN SETUP ]");
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

    renderMenu();
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
                navigateTo(MENU_COLORS);
                break;
            }
            break;

        case MENU_COLORS:
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
            }
            break;
        }
    } else {
        if (bcLen > 0) {
            uint16_t c = popCrumb();
            menuNum = c >> 8 & 0x00ff;
            menuCursor = c & 0x00ff;
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
            uView.print("Colors");
            break;

        case 1:
            uView.print("Slow Shows");
            break;

        case 2:
            uView.print("Fast Shows");
            break;

        case 3:
            uView.print("Settings");
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
        }
        break;

    }

}
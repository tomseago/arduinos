
#include <mtui.h>

#include <mt-harnass.h>
extern MTHarnass harnass;

#define MENU_TOP    0
#define MENU_COLORS 1

uint8_t const menuMax[] = { 4, 11 };

MTUI::MTUI(uint8_t pin) 
    : pin(pin) {

}

void MTUI::begin() {
    uView.begin();

    pinMode(pin, INPUT);

    renderMenu();
    uView.display();
}

void MTUI::end() {
    uView.end();
}

void MTUI::loop() {
    
    // Input section
    int pinVal = analogRead(pin);
    int delta = pinVal - lastPinVal;
    lastPinVal = pinVal;

    if (delta < 1 || delta > 1) {
        // The pin is still transitioning, so do nothing
        return;
    }

    // TODO: Should we handle non user input to animate the display
    // or disable things? Maybe that happens through other methods.

    // Turn the value into a button number

    // Measured divisions are:
    // 930
    //    910 - break
    // 890
    //    870 - break
    // 850
    //    820 - break
    // 785
    //    750 - break

    uint8_t button = 0;
    if (pinVal > 910) {
        button = 1;
    } else if (pinVal > 870) {
        button = 2;
    } else if (pinVal > 820) {
        button = 3;
    } else if (pinVal > 750) {
        button = 4;
    }    

    if (button == lastButton) {
        debounceCount++;

        if (debounceCount == 5) {
            singleClick();
            uView.display();
        }
        // TODO: Long button presses????

        // For now, just bail 
        return;
    }

    // A new button has just been pressed
    lastButton = button;
    debounceCount = 0;


    //singleClick();

    //uView.display();
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
            menuNum = popCrumb();
        }
    }
}

void MTUI::navigateTo(uint8_t menu) {
    pushCrumb(menuNum);
    menuCursor = 0;
    menuNum = menu;    
}

void MTUI::pushCrumb(uint8_t crumb) {
    breadcrumbs[bcLen] = crumb;
    bcLen++;
}

uint8_t MTUI::popCrumb() {
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
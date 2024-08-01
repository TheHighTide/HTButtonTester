#include <coreinit/thread.h>
#include <coreinit/time.h>

#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>

#include <vpad/input.h>
#include <padscore/kpad.h>
#include <padscore/wpad.h>

#include "htconsole.h"

#define joystick_threshhold 0.5f

typedef enum {
    JOYSTICK_CENTERED,
    JOYSTICK_UP,
    JOYSTICK_DOWN,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT
} JoystickDirection;

void CheckJoystickInput(KPADVec2D stick, JoystickDirection *lastDirection, const char *stickName) {
    float x = stick.x;
    float y = stick.y;
    JoystickDirection currentDirection = JOYSTICK_CENTERED;

    // Determine the dominant direction
    if (fabs(x) > joystick_threshhold || fabs(y) > joystick_threshhold) {
        if (fabs(x) > fabs(y)) {
            if (x > joystick_threshhold) {
                currentDirection = JOYSTICK_RIGHT;
            } else if (x < -joystick_threshhold) {
                currentDirection = JOYSTICK_LEFT;
            }
        } else {
            if (y > joystick_threshhold) {
                currentDirection = JOYSTICK_UP;
            } else if (y < -joystick_threshhold) {
                currentDirection = JOYSTICK_DOWN;
            }
        }
    }

    // Print the direction only if it has changed
    if (currentDirection != *lastDirection) {
        *lastDirection = currentDirection;
        switch (currentDirection) {
            case JOYSTICK_UP:
                WHBLogPrintf("Pro %s STICK UP", stickName);
                break;
            case JOYSTICK_DOWN:
                WHBLogPrintf("Pro %s STICK DOWN", stickName);
                break;
            case JOYSTICK_LEFT:
                WHBLogPrintf("Pro %s STICK LEFT", stickName);
                break;
            case JOYSTICK_RIGHT:
                WHBLogPrintf("Pro %s STICK RIGHT", stickName);
                break;
        }
        WHBLogConsoleDraw(); // Update the console output
    }
}

int main(int argc, char **argv)
{
    WHBProcInit();
    WPADInit();
    KPADInit();
    WHBLogConsoleInit();

    WPADEnableURCC(1);

    WHBLogPrintf("Welcome to HighTide's Button Tester for WiiU!"); // Welcome the user to the program because I'm nice
    WHBLogPrintf("Version 2.1"); // Print the version number to the screen
    WHBLogPrintf("Important News: This button tester now supports all types of compatable");
    WHBLogPrintf("controllers for the WiiU and Wii! INCLUDING PRO CONTROLLERS!");
    WHBLogPrintf("Add Supported controllers:");
    WHBLogPrintf("1. WiiU Gamepad");
    WHBLogPrintf("2. Wii Controller");
    WHBLogPrintf("3. Wii Controller + Nunchuk");
    WHBLogPrintf("4. Wii Controller + Classic Controller");
    WHBLogPrintf("5. Wii/WiiU Pro Controller");
    WHBLogPrintf("Send me a donation over at https://ko-fi.com/thehightide");
    WHBLogPrintf("Press PLUS and MINUS on the Gamepad to start the button test!");
    WHBLogPrintf("Press ZL/ZR/A to toggle into advanced mode");
    
    int passedTests = 0; // This will always be 0 until the user passes some tests
    bool isInTest = false;
    bool isInAdvancedMode = false;
    bool hasJustReturned = false;
    bool hasPrintedProLeftStick[4] = { false, false, false, false };
    bool hasPrintedProRightStick[4] = { false, false, false, false };
    JoystickDirection lastLeftDirection = JOYSTICK_CENTERED;
    JoystickDirection lastRightDirection = JOYSTICK_CENTERED;

    while(WHBProcIsRunning()) {
        VPADStatus vpad;
        VPADRead(0, &vpad, 1, NULL);
        KPADStatus kpad;
        KPADReadEx(0, &kpad, 1, NULL);

        if (isInAdvancedMode) {
            ClearLog();
            KPADVec2D proLStick = kpad.pro.leftStick;
            KPADVec2D proRStick = kpad.pro.rightStick;
            VPADVec2D gamepadLStick = vpad.leftStick;
            VPADVec2D gamepadRStick = vpad.rightStick;
            WHBLogPrintf("You are now in advanced mode!");
            WHBLogPrintf("Press \"PLUS\" to return to basic mode!");
            WHBLogPrintf("-----------------------------------------");
            WHBLogPrintf("                                         ");
            WHBLogPrintf("Gamepad: ");
            WHBLogPrintf("Left Joystick X: %f, Y: %f", gamepadLStick.x, gamepadLStick.y);
            WHBLogPrintf("Right Joystick X: %f, Y: %f", gamepadRStick.x, gamepadRStick.y);
            WHBLogPrintf("-----------------------------------------");
            WHBLogPrintf("                                         ");
            WHBLogPrintf("Pro Controller");
            WHBLogPrintf("Left Joystick X: %f, Y: %f", proLStick.x, proLStick.y);
            WHBLogPrintf("Right Joystick X: %f, Y: %f", proRStick.x, proRStick.y);
            WHBLogPrintf("");
            WHBLogPrintf("");
            WHBLogPrintf("");
            WHBLogPrintf("");

            if ((kpad.pro.trigger & WPAD_PRO_BUTTON_PLUS) || (vpad.trigger & VPAD_BUTTON_PLUS)) {
                isInAdvancedMode = false;
                hasJustReturned = true;
                ClearLog();
                WHBLogPrintf("Successfully returned to basic mode!");
            }
        }
        else {
            // WiiU Gamepad
            if (vpad.trigger & VPAD_BUTTON_A) WHBLogPrintf("Gamepad A");
            if (vpad.trigger & VPAD_BUTTON_B) WHBLogPrintf("Gamepad B");
            if (vpad.trigger & VPAD_BUTTON_X) WHBLogPrintf("Gamepad X");
            if (vpad.trigger & VPAD_BUTTON_Y) WHBLogPrintf("Gamepad Y");
            if (vpad.trigger & VPAD_BUTTON_PLUS) WHBLogPrintf("Gamepad PLUS");
            if (vpad.trigger & VPAD_BUTTON_MINUS) WHBLogPrintf("Gamepad MINUS");
            if (vpad.trigger & VPAD_BUTTON_LEFT) WHBLogPrintf("Gamepad DPAD LEFT");
            if (vpad.trigger & VPAD_BUTTON_RIGHT) WHBLogPrintf("Gamepad DPAD RIGHT");
            if (vpad.trigger & VPAD_BUTTON_UP) WHBLogPrintf("Gamepad DPAD UP");
            if (vpad.trigger & VPAD_BUTTON_DOWN) WHBLogPrintf("Gamepad DPAD DOWN");
            if (vpad.trigger & VPAD_BUTTON_ZL) WHBLogPrintf("Gamepad ZL");
            if (vpad.trigger & VPAD_BUTTON_ZR) WHBLogPrintf("Gamepad ZR");
            if (vpad.trigger & VPAD_BUTTON_L) WHBLogPrintf("Gamepad L");
            if (vpad.trigger & VPAD_BUTTON_R) WHBLogPrintf("Gamepad R");
            if (vpad.trigger & VPAD_BUTTON_STICK_L) WHBLogPrintf("Gamepad LEFT STICK PUSH");
            if (vpad.trigger & VPAD_BUTTON_STICK_R) WHBLogPrintf("Gamepad RIGHT STICK PUSH");
            if (vpad.trigger & VPAD_BUTTON_TV) WHBLogPrintf("Gamepad TV");
            if (vpad.trigger & VPAD_STICK_L_EMULATION_DOWN) WHBLogPrintf("Gamepad LEFT STICK DOWN");
            if (vpad.trigger & VPAD_STICK_L_EMULATION_LEFT) WHBLogPrintf("Gamepad LEFT STICK LEFT");
            if (vpad.trigger & VPAD_STICK_L_EMULATION_UP) WHBLogPrintf("Gamepad LEFT STICK UP");
            if (vpad.trigger & VPAD_STICK_L_EMULATION_RIGHT) WHBLogPrintf("Gamepad LEFT STICK RIGHT");
            if (vpad.trigger & VPAD_STICK_R_EMULATION_DOWN) WHBLogPrintf("Gamepad RIGHT STICK DOWN");
            if (vpad.trigger & VPAD_STICK_R_EMULATION_LEFT) WHBLogPrintf("Gamepad RIGHT STICK LEFT");
            if (vpad.trigger & VPAD_STICK_R_EMULATION_UP) WHBLogPrintf("Gamepad RIGHT STICK UP");
            if (vpad.trigger & VPAD_STICK_R_EMULATION_RIGHT) WHBLogPrintf("Gamepad RIGHT STICK RIGHT");

            // Wii Controller
            if (kpad.trigger & WPAD_BUTTON_1) WHBLogPrintf("Wii 1");
            if (kpad.trigger & WPAD_BUTTON_2) WHBLogPrintf("Wii 2");
            if (kpad.trigger & WPAD_BUTTON_A) WHBLogPrintf("Wii A");
            if (kpad.trigger & WPAD_BUTTON_B) WHBLogPrintf("Wii B");
            if (kpad.trigger & WPAD_BUTTON_C) WHBLogPrintf("Wii C");
            if (kpad.trigger & WPAD_BUTTON_DOWN) WHBLogPrintf("Wii DPAD DOWN");
            if (kpad.trigger & WPAD_BUTTON_LEFT) WHBLogPrintf("Wii DPAD LEFT");
            if (kpad.trigger & WPAD_BUTTON_MINUS) WHBLogPrintf("Wii MINUS");
            if (kpad.trigger & WPAD_BUTTON_PLUS) WHBLogPrintf("Wii PLUS");
            if (kpad.trigger & WPAD_BUTTON_RIGHT) WHBLogPrintf("Wii DPAD RIGHT");
            if (kpad.trigger & WPAD_BUTTON_UP) WHBLogPrintf("Wii DPAD UP");
            if (kpad.trigger & WPAD_BUTTON_Z) WHBLogPrintf("Wii Z");

            // Wii Controller + Nunchuk
            if (kpad.trigger & WPAD_NUNCHUK_BUTTON_C) WHBLogPrintf("Nunchuk C");
            if (kpad.trigger & WPAD_NUNCHUK_BUTTON_Z) WHBLogPrintf("Nunchuk Z");
            if (kpad.trigger & WPAD_NUNCHUK_STICK_EMULATION_DOWN) WHBLogPrintf("Nunchuk STICK DOWN");
            if (kpad.trigger & WPAD_NUNCHUK_STICK_EMULATION_LEFT) WHBLogPrintf("Nunchuk STICK LEFT");
            if (kpad.trigger & WPAD_NUNCHUK_STICK_EMULATION_UP) WHBLogPrintf("Nunchuk STICK UP");
            if (kpad.trigger & WPAD_NUNCHUK_STICK_EMULATION_RIGHT) WHBLogPrintf("Nunchuk STICK RIGHT");

            // Wii Controller + Classic Controller
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_A) WHBLogPrintf("Classic A");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_B) WHBLogPrintf("Classic B");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_DOWN) WHBLogPrintf("Classic DPAD DOWN");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_L) WHBLogPrintf("Classic L");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_LEFT) WHBLogPrintf("Classic DPAD LEFT");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_MINUS) WHBLogPrintf("Classic MINUS");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_PLUS) WHBLogPrintf("Classic PLUS");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_R) WHBLogPrintf("Classic R");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_RIGHT) WHBLogPrintf("Classic DPAD RIGHT");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_UP) WHBLogPrintf("Classic DPAD UP");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_X) WHBLogPrintf("Classic X");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_ZL) WHBLogPrintf("Classic ZL");
            if (kpad.trigger & WPAD_CLASSIC_BUTTON_ZR) WHBLogPrintf("Classic ZR");
            if (kpad.trigger & WPAD_CLASSIC_STICK_L_EMULATION_DOWN) WHBLogPrintf("Classic LEFT STICK DOWN");
            if (kpad.trigger & WPAD_CLASSIC_STICK_L_EMULATION_LEFT) WHBLogPrintf("Classic LEFT STICK LEFT");
            if (kpad.trigger & WPAD_CLASSIC_STICK_L_EMULATION_UP) WHBLogPrintf("Classic LEFT STICK UP");
            if (kpad.trigger & WPAD_CLASSIC_STICK_L_EMULATION_RIGHT) WHBLogPrintf("Classic LEFT STICK RIGHT");
            if (kpad.trigger & WPAD_CLASSIC_STICK_R_EMULATION_DOWN) WHBLogPrintf("Classic RIGHT STICK DOWN");
            if (kpad.trigger & WPAD_CLASSIC_STICK_R_EMULATION_LEFT) WHBLogPrintf("Classic RIGHT STICK LEFT");
            if (kpad.trigger & WPAD_CLASSIC_STICK_R_EMULATION_UP) WHBLogPrintf("Classic RIGHT STICK UP");
            if (kpad.trigger & WPAD_CLASSIC_STICK_R_EMULATION_RIGHT) WHBLogPrintf("Classic RIGHT STICK RIGHT");

            // Wii Pro Controller
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_A) WHBLogPrintf("Pro B");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_B) WHBLogPrintf("Pro A");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_DOWN) WHBLogPrintf("Pro DPAD DOWN");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_LEFT) WHBLogPrintf("Pro DPAD LEFT");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_MINUS) WHBLogPrintf("Pro MINUS");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_PLUS) WHBLogPrintf("Pro PLUS");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_RIGHT) WHBLogPrintf("Pro DPAD RIGHT");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_STICK_L) WHBLogPrintf("Pro LEFT STICK PUSH");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_STICK_R) WHBLogPrintf("Pro RIGHT STICK PUSH");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_UP) WHBLogPrintf("Pro DPAD UP");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_X) WHBLogPrintf("Pro Y");
            if (kpad.pro.trigger & WPAD_PRO_BUTTON_Y) WHBLogPrintf("Pro X");
            if (kpad.pro.trigger & WPAD_PRO_TRIGGER_L) WHBLogPrintf("Pro L");
            if (kpad.pro.trigger & WPAD_PRO_TRIGGER_R) WHBLogPrintf("Pro R");
            if (kpad.pro.trigger & WPAD_PRO_TRIGGER_ZL) WHBLogPrintf("Pro ZL");
            if (kpad.pro.trigger & WPAD_PRO_TRIGGER_ZR) WHBLogPrintf("Pro ZR");

            CheckJoystickInput(kpad.pro.leftStick, &lastLeftDirection, "LEFT");
            CheckJoystickInput(kpad.pro.rightStick, &lastRightDirection, "RIGHT");
            
            if (hasJustReturned) {
                WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");
                WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");WHBLogPrintf("");
                hasJustReturned = false;
            }

            if ((kpad.pro.hold & WPAD_PRO_TRIGGER_ZL) || (vpad.hold & VPAD_BUTTON_ZL)) {
                if ((kpad.pro.hold & WPAD_PRO_TRIGGER_ZR) || (vpad.hold & VPAD_BUTTON_ZR)) {
                    if ((kpad.pro.hold & WPAD_PRO_BUTTON_B) || (vpad.hold & VPAD_BUTTON_A)) {
                        isInAdvancedMode = true;
                        ClearLog();
                    }
                }
            }
        }

        WHBLogConsoleDraw();
        OSSleepTicks(OSMillisecondsToTicks(50));
    }   

    WHBLogPrintf("Exiting... good bye.");

    WHBLogConsoleDraw();
    OSSleepTicks(OSMillisecondsToTicks(1000));

    WHBLogConsoleFree();
    WHBProcShutdown();

    return 0;
}

#include <coreinit/thread.h>
#include <coreinit/time.h>

#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>

#include <vpad/input.h>
#include <padscore/kpad.h>

#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    enum AXIS_NUM {
        left_joy_x = 0,
        left_joy_y = 1,
        left_trigger = 2,
        right_joy_x = 3,
        right_joy_y = 4,
        right_trigger = 5,
		left_wiiu_joy_x = 0,
        left_wiiu_joy_y = 1,
        right_wiiu_joy_x = 2,
        right_wiiu_joy_y = 3,
		wiimote_joy_x = 0,
        wiimote_joy_y = 1
    };

    WHBProcInit();
    WHBLogConsoleInit();   

    WHBLogPrintf("Welcome to HighTide's Button Tester for WiiU!"); // Welcome the user to the program because I'm nice
    WHBLogPrintf("Version 2.0"); // Print the version number to the screen
    WHBLogPrintf("Important News: This button tester now supports all types of compatable");
    WHBLogPrintf("controllers for the WiiU and Wii!");
    WHBLogPrintf("Add Supported controllers:");
    WHBLogPrintf("1. WiiU Gamepad");
    WHBLogPrintf("2. Wii Controller");
    WHBLogPrintf("3. Wii Controller + Nunchuk");
    WHBLogPrintf("4. Wii Controller + Classic Controller");
    WHBLogPrintf("5. Wii Pro Controller");
    WHBLogPrintf("Send me a donation over at https://ko-fi.com/thehightide");
    WHBLogPrintf("Press PLUS and MINUS on the Gamepad to start the button test!");
    
    int passedTests = 0; // This will always be 0 until the user passes some tests
    bool isInTest = false;

    while(WHBProcIsRunning()) {
        VPADStatus vpad;
        VPADRead(0, &vpad, 1, NULL);
        KPADStatus kpad;
        KPADReadEx(0, &kpad, 1, NULL); 

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
        if (kpad.trigger & WPAD_PRO_BUTTON_A) WHBLogPrintf("Pro A");
        if (kpad.trigger & WPAD_PRO_BUTTON_B) WHBLogPrintf("Pro B");
        if (kpad.trigger & WPAD_PRO_BUTTON_DOWN) WHBLogPrintf("Pro DPAD DOWN");
        if (kpad.trigger & WPAD_PRO_BUTTON_LEFT) WHBLogPrintf("Pro DPAD LEFT");
        if (kpad.trigger & WPAD_PRO_BUTTON_MINUS) WHBLogPrintf("Pro MINUS");
        if (kpad.trigger & WPAD_PRO_BUTTON_PLUS) WHBLogPrintf("Pro PLUS");
        if (kpad.trigger & WPAD_PRO_BUTTON_RIGHT) WHBLogPrintf("Pro DPAD RIGHT");
        if (kpad.trigger & WPAD_PRO_BUTTON_STICK_L) WHBLogPrintf("Pro LEFT STICK PUSH");
        if (kpad.trigger & WPAD_PRO_BUTTON_STICK_R) WHBLogPrintf("Pro RIGHT STICK PUSH");
        if (kpad.trigger & WPAD_PRO_BUTTON_UP) WHBLogPrintf("Pro DPAD UP");
        if (kpad.trigger & WPAD_PRO_BUTTON_X) WHBLogPrintf("Pro X");
        if (kpad.trigger & WPAD_PRO_BUTTON_Y) WHBLogPrintf("Pro Y");
        if (kpad.trigger & WPAD_PRO_STICK_L_EMULATION_DOWN) WHBLogPrintf("Pro LEFT STICK DOWN");
        if (kpad.trigger & WPAD_PRO_STICK_L_EMULATION_LEFT) WHBLogPrintf("Pro LEFT STICK LEFT");
        if (kpad.trigger & WPAD_PRO_STICK_L_EMULATION_UP) WHBLogPrintf("Pro LEFT STICK UP");
        if (kpad.trigger & WPAD_PRO_STICK_L_EMULATION_RIGHT) WHBLogPrintf("Pro LEFT STICK RIGHT");
        if (kpad.trigger & WPAD_PRO_STICK_R_EMULATION_DOWN) WHBLogPrintf("Pro RIGHT STICK DOWN");
        if (kpad.trigger & WPAD_PRO_STICK_R_EMULATION_LEFT) WHBLogPrintf("Pro RIGHT STICK LEFT");
        if (kpad.trigger & WPAD_PRO_STICK_R_EMULATION_UP) WHBLogPrintf("Pro RIGHT STICK UP");
        if (kpad.trigger & WPAD_PRO_STICK_R_EMULATION_RIGHT) WHBLogPrintf("Pro RIGHT STICK RIGHT");
        if (kpad.trigger & WPAD_PRO_TRIGGER_L) WHBLogPrintf("Pro L");
        if (kpad.trigger & WPAD_PRO_TRIGGER_R) WHBLogPrintf("Pro R");
        if (kpad.trigger & WPAD_PRO_TRIGGER_ZL) WHBLogPrintf("Pro ZL");
        if (kpad.trigger & WPAD_PRO_TRIGGER_ZR) WHBLogPrintf("Pro ZR");

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

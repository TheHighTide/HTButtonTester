#include <coreinit/thread.h>
#include <coreinit/time.h>

#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>

#include <vpad/input.h>

int
main(int argc, char **argv)
{
   WHBProcInit();
   WHBLogConsoleInit();

   while(WHBProcIsRunning()) {
      VPADStatus vpad;
      VPADRead(0, &vpad, 1, NULL);

      if (vpad.trigger == VPAD_BUTTON_A){
         WHBLogPrintf("A");
      }
      if (vpad.trigger == VPAD_BUTTON_B){
         WHBLogPrintf("B");
      }
      if (vpad.trigger == VPAD_BUTTON_X){
         WHBLogPrintf("X");
      }
      if (vpad.trigger == VPAD_BUTTON_Y){
         WHBLogPrintf("Y");
      }
      if (vpad.trigger == VPAD_BUTTON_PLUS){
         WHBLogPrintf("PLUS");
      }
      if (vpad.trigger == VPAD_BUTTON_MINUS){
         WHBLogPrintf("MINUS");
      }
      if (vpad.trigger == VPAD_BUTTON_LEFT){
         WHBLogPrintf("DPAD LEFT");
      }
      if (vpad.trigger == VPAD_BUTTON_RIGHT){
         WHBLogPrintf("DPAD RIGHT");
      }
      if (vpad.trigger == VPAD_BUTTON_UP){
         WHBLogPrintf("DPAD UP");
      }
      if (vpad.trigger == VPAD_BUTTON_DOWN){
         WHBLogPrintf("DPAD DOWN");
      }
      if (vpad.trigger == VPAD_BUTTON_ZL){
         WHBLogPrintf("ZL");
      }
      if (vpad.trigger == VPAD_BUTTON_ZR){
         WHBLogPrintf("ZR");
      }
      if (vpad.trigger == VPAD_BUTTON_L){
         WHBLogPrintf("L");
      }
      if (vpad.trigger == VPAD_BUTTON_R){
         WHBLogPrintf("R");
      }
      if (vpad.trigger == VPAD_BUTTON_STICK_L){
         WHBLogPrintf("LEFT STICK DOWN");
      }
      if (vpad.trigger == VPAD_BUTTON_STICK_R){
         WHBLogPrintf("RIGHT STICK DOWN");
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
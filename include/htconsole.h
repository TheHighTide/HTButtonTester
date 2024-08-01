#pragma once

#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>

void ClearLog() {
    for (int i = 0; i < 50; i++) {
        WHBLogPrintf("\n");
    }
}

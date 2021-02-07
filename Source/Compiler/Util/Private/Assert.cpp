//
// Created by ASUS on 03/02/2021.
//

#include "Assert.h"

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

void DebugBreakOrExit()
{
    if (IsDebuggerPresent() != FALSE)
    {
        DebugBreak();
    }
    else
    {
        exit(1);
    }
}
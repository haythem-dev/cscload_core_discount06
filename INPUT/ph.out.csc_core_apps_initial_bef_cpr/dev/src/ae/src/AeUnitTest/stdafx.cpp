// pch.cpp: source file corresponding to the pre-compiled header

#include "stdafx.h"

// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.

int AllgBitleisteN(Bitleiste a, int n)
{
    if (n > 15)
    {
        n = 15;
    }
    else if (n < 0)
    {
        n = 0;
    }
    int test = (int)(a >> (15 - n)) % 2;
    return (int)(a >> (15 - n)) % 2;
}

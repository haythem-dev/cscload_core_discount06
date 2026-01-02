#pragma once

#include "SessionUtil.h"

class FixtureBase
{
protected:
    SessionUtil _session;

public:
    FixtureBase(const short branchno);
};


/*
 * pxconstants.hpp
 *
 *  Created on: 22.01.2016
 *  Author: sebastian.barth
 */

#ifndef PXCONSTANTS_INC
#define PXCONSTANTS_INC

#include <money.hpp>
#include <date.hpp>
#include <time.hpp>
#include <clock.hpp>

class pxConstants
{
public:
    static const nMoney mZero;

    static const double dZero;

    static const nDate NullDate;

    static const nTime NullTime;

    static const nClock NullClock;

    static const short CalcFrom;

    static const short ApplyTo;
};

#endif // PXCONSTANTS_INC

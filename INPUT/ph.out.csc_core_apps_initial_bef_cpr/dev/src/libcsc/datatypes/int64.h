/*
 * int64.h
 *
 *  Created on: 23.11.2021
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_INT64_H
#define GUARD_LIBCSC_INT64_H

#include <libbasar_definitions.h>
#include <datatypes/property.hpp>
#include <datatypes/propertystate.h>
#include <iostream>

namespace libcsc
{
    typedef libcsc::Property<basar::Int64> Int64;
} // end namespace libcsc

#endif // GUARD_LIBCSC_INT64_H

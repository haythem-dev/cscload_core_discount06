/*
 * ibtrequestexception.cpp
 *
 *  Created on: 15.10.2015
 *  Author: sebastian.barth
 */

#include "ibtrequestexception.h"

namespace libcsc {
namespace exceptions {

IbtRequestException::IbtRequestException(basar::ExceptInfo const& sInfo)
    : CSCExceptionBase(sInfo, "IbtRequestException")
{
}

IbtRequestException::~IbtRequestException()
{
}

} // end namespace exceptions
} // end namespace libcsc

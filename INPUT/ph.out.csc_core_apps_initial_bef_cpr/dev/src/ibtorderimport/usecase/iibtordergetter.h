#ifndef GUARD_IBTORDERIMPORT_USECASE_IIOBTORDERGETTER_H
#define GUARD_IBTORDERIMPORT_USECASE_IIOBTORDERGETTER_H

//-------------------------------------------------------------------------------------------------//
#include <ibt/ibtrequest/iibtrequestptr.h>
#include "domainmodule/ipxorderptr.h"

namespace ibtorderimport {
namespace useCase {

//-------------------------------------------------------------------------------------------------//

class IIbtOrderGetter
{
public:
	virtual ~IIbtOrderGetter() {};

	virtual domMod::IPxOrderPtr getOrder(libcsc::ibt::IIbtRequestPtr) = 0;
	
	virtual void				save() = 0;
};

//-------------------------------------------------------------------------------------------------//

} // namespace usecase
} // namespace ibtorderimport

//-------------------------------------------------------------------------------------------------//

#endif // GUARD_IBTORDERIMPORT_USECASE_IIOBTORDERGETTER_H

//-------------------------------------------------------------------------------------------------//

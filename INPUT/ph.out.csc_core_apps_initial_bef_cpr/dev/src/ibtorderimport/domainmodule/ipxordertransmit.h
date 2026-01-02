#ifndef GUARD_IBTORDERIMPORT_DOMMOD_IPXORDERTRANSMIT_H
#define GUARD_IBTORDERIMPORT_DOMMOD_IPXORDERTRANSMIT_H

#include <persistence/connectionptr.h>
#include "pxorder.hpp"
#include "tourutil.hpp"

#include <ibt/ibtrequest/iibtrequestptr.h>

//-------------------------------------------------------------------------------------------------//

namespace ibtorderimport {
namespace domMod {

//-------------------------------------------------------------------------------------------------//

class IPxOrderTransmit
{
public:
	virtual ~IPxOrderTransmit() {};

	// returns existing / new created order to which ibt positions are added
	virtual ::pxOrder *     OrderType(const nString& type, const nString& number,
										const int kommityp = cDEFAULT,
										const int bookingtyp = cDEFAULT,
										const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN,
										const short options = 0,
										const nString& desiredTour = "",
										const nDate desiredTourDate = TourUtil::getNullDate()) = 0;

	// returns existing / new created order to which ibt positions are added FOR FRANCE
	virtual ::pxOrder*		OrderTypeNS(const nString& type, const nString& number, const short BranchNo, 
										const int kommityp = cDEFAULT, const int bookingtyp = cDEFAULT, 
										const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN, const short options = 0,
										const nString& desiredTour = "",
										const nDate desiredTourDate = TourUtil::getNullDate()) = 0;

	// check, if customer is locked for AE in branch "vz"
	virtual bool			isCustomerLocked(const libcsc::ibt::IIbtRequestPtr) = 0;
	
	// get session
	virtual	::pxSession*    Session() = 0;

	virtual int             End() = 0;
};

//-------------------------------------------------------------------------------------------------//

} // namespace domMod
} // namespace ibtorderimport

//-------------------------------------------------------------------------------------------------//

#endif // GUARD_IBTORDERIMPORT_DOMMOD_IPXORDERTRANSMIT_H

//-------------------------------------------------------------------------------------------------//

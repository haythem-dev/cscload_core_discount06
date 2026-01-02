#ifndef GUARD_IBTORDERIMPORT_DOMMOD_PXORDERTRANSMIT_H
#define GUARD_IBTORDERIMPORT_DOMMOD_PXORDERTRANSMIT_H

//-----------------------------------------------------------------------------------------

#include "ipxordertransmit.h"
#include "pxvbpxordertransmitptr.h"

#include "pxsessioninitialization.h"

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace domMod {

//-----------------------------------------------------------------------------------------

class PxOrderTransmit : public IPxOrderTransmit
{
public:
	PxOrderTransmit(pxSessionInitialization, const log4cplus::Logger& logger);
	virtual ~PxOrderTransmit();

	void			injectCscDbConnection(libcsc::persistence::ConnectionPtr);
	void			prepareSession();

	virtual ::pxOrder *     OrderType(const nString& type, const nString& number,
										const int kommityp = cDEFAULT,
										const int bookingtyp = cDEFAULT,
										const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN,
										const short options = 0,
										const nString& desiredTour = "",
										const nDate desiredTourDate = TourUtil::getNullDate());

	virtual ::pxOrder*		OrderTypeNS(const nString& type, const nString& number, const short BranchNo, 
										const int kommityp = cDEFAULT, const int bookingtyp = cDEFAULT, 
										const OriginTypeEnum batchschreiben = cORTYPE_UNKNOWN, const short options = 0,
										const nString& desiredTour = "",
										const nDate desiredTourDate = TourUtil::getNullDate());

	virtual bool			isCustomerLocked(const libcsc::ibt::IIbtRequestPtr);

	virtual	::pxSession*    Session();

	virtual int             End();

private:
	PxOrderTransmit( const PxOrderTransmit& );
	PxOrderTransmit& operator=( const PxOrderTransmit& );

	const log4cplus::Logger&		getLogger();


	const log4cplus::Logger&								m_Logger;
	pxVbPxOrderTransmitPtr									m_pxVbPxOrderTransmit;
};

//-----------------------------------------------------------------------------------------

} // namespace domMod
} // namespace ibtorderimport

//-----------------------------------------------------------------------------------------

#endif // GUARD_IBTORDERIMPORT_DOMMOD_PXORDERTRANSMIT_H

//-----------------------------------------------------------------------------------------

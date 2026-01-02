#ifndef GUARD_IBTORDERIMPORT_USECASE_IBTORDERMANAGER_H
#define GUARD_IBTORDERIMPORT_USECASE_IBTORDERMANAGER_H

#include "iibtordergetter.h"
#include "domainmodule/ipxordertransmitptr.h"

namespace log4cplus {
	class Logger;
}

namespace ibtorderimport {
namespace useCase {

class IbtOrderManager : public IIbtOrderGetter
{
public:
	IbtOrderManager(const log4cplus::Logger& logger);
	virtual ~IbtOrderManager();

	virtual domMod::IPxOrderPtr		getOrder(libcsc::ibt::IIbtRequestPtr);
	
	void							injectPxOrderTransmit(domMod::IPxOrderTransmitPtr);
	domMod::IPxOrderTransmitPtr		getPxOrderTransmit();

	virtual void					save();

private:
	IbtOrderManager( const IbtOrderManager& );
	IbtOrderManager& operator=( const IbtOrderManager& );

	const log4cplus::Logger&		getLogger();

	const log4cplus::Logger&		m_Logger;
	domMod::IPxOrderTransmitPtr		m_PxOrderTransmit;
};

} // namespace useCase
} // namespace ibtorderimport

#endif // GUARD_IBTORDERIMPORT_USECASE_IBTORDERMANAGER_H

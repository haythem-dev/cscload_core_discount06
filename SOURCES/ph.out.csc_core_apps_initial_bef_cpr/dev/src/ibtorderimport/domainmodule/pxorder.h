#ifndef GUARD_IBTORDERIMPORT_DOMMOD_PXORDER_H
#define GUARD_IBTORDERIMPORT_DOMMOD_PXORDER_H

//-----------------------------------------------------------------------------------------

#include "ipxorder.h"
#include <pxorder.hpp>


//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace domMod {

//-----------------------------------------------------------------------------------------

class PxOrder : public IPxOrder
{
public:
	PxOrder(const log4cplus::Logger& logger, ::pxOrder* );
	virtual ~PxOrder();

	virtual bool isBatchWriting() const;
	virtual void activateBatchWriting();
	virtual void determineIbtComment();
	virtual void setOriginBranchNo(const basar::Int16);
	virtual basar::Int32 getOrderNo();

	virtual IPxOrderItemPtr addPosition(const libcsc::ibt::IIbtRequestPtr);
	virtual void setOrderType(libcsc::ibt::IIbtRequestPtr);
	virtual void setPaymentTerm(basar::VarString const&);
	virtual void markAsNewSuivra();

private:
	PxOrder( const PxOrder& );
	PxOrder& operator=( const PxOrder& );

	IPxOrderItemPtr createNewOrderItem(const libcsc::ibt::IIbtRequestPtr);
	void			addPositionRemark(const libcsc::ibt::IIbtRequestPtr, IPxOrderItemPtr);
	void			addPositionDiscounts(const libcsc::ibt::IIbtRequestPtr, IPxOrderItemPtr);
	void			copyTourDataFromOrigPos(const libcsc::ibt::IIbtRequestPtr, IPxOrderItemPtr);

	const log4cplus::Logger&		getLogger();

	const log4cplus::Logger&					m_Logger;
	::pxOrder*									m_pxOrder;
};

//-----------------------------------------------------------------------------------------

} // namespace domMod
} // namespace ibtorderimport

//-----------------------------------------------------------------------------------------

#endif // GUARD_IBTORDERIMPORT_DOMMOD_PXORDER_H

//-----------------------------------------------------------------------------------------

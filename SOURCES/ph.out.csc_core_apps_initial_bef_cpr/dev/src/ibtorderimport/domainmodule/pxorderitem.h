#ifndef GUARD_IBTORDERIMPORT_DOMMOD_PXORDERITEM_H
#define GUARD_IBTORDERIMPORT_DOMMOD_PXORDERITEM_H

//-----------------------------------------------------------------------------------------

#include "ipxorderitem.h"

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace domMod {

//-----------------------------------------------------------------------------------------

class PxOrderItem : public IPxOrderItem
{
public:
	PxOrderItem(const log4cplus::Logger& logger, ::pxOrderItem* );
	virtual ~PxOrderItem();

	virtual void			setRemark(basar::VarString );
	virtual void			setQtyBooked(basar::Int32);
	virtual void			markAsNonPharmosBatch();
	virtual void			setCustomerOrderReference(basar::VarString );
	virtual void			setArticleCodeProperties(basar::Int16, basar::VarString );
	virtual void			setIbtType(basar::Int16);
	virtual	void		    setTourIdIbt(nString );
    virtual void			setIbtTourWeekDay(basar::Int16 );
	virtual bool			isCompleteOrderedQtyConfirmed();
	
	virtual ::pxOrderItem *	getPxVbOrderItem();

private:
	PxOrderItem( const PxOrderItem& );
	PxOrderItem& operator=( const PxOrderItem& );

	const log4cplus::Logger&		getLogger();

	const log4cplus::Logger&		m_Logger;
	::pxOrderItem*					m_pxItem;
};

//-----------------------------------------------------------------------------------------

} // namespace domMod
} // namespace ibtorderimport

//-----------------------------------------------------------------------------------------

#endif // GUARD_IBTORDERIMPORT_DOMMOD_PXORDERITEM_H

//-----------------------------------------------------------------------------------------

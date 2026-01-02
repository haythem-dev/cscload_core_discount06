#ifndef GUARD_IBTORDERIMPORT_DOMMOD_IPXORDERITEM_H
#define GUARD_IBTORDERIMPORT_DOMMOD_IPXORDERITEM_H

#include <libbasar_definitions.h>
#include <pxitem.hpp>

//-------------------------------------------------------------------------------------------------//

namespace ibtorderimport {
namespace domMod {


//-------------------------------------------------------------------------------------------------//

class IPxOrderItem
{
public:
	virtual ~IPxOrderItem() {};

	virtual void			setRemark(basar::VarString ) = 0;
	virtual void			setQtyBooked(basar::Int32) = 0;
	virtual void			markAsNonPharmosBatch() = 0;
	virtual void			setCustomerOrderReference(basar::VarString ) = 0;
	virtual void			setArticleCodeProperties(basar::Int16, basar::VarString ) = 0;
	virtual void			setIbtType(basar::Int16) = 0;
	virtual	void		    setTourIdIbt(nString ) = 0;
    virtual void			setIbtTourWeekDay(basar::Int16) = 0;
	virtual bool			isCompleteOrderedQtyConfirmed() = 0;
             

	virtual ::pxOrderItem *	getPxVbOrderItem() = 0;

};

//-------------------------------------------------------------------------------------------------//

} // namespace domMod
} // namespace ibtorderimport

//-------------------------------------------------------------------------------------------------//

#endif // GUARD_IBTORDERIMPORT_DOMMOD_IPXORDERITEM_H

//-------------------------------------------------------------------------------------------------//

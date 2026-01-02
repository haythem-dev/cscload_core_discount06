#ifndef GUARD_LIBCSC_STOCKBOOKING_CUSTOMER_STOCKRESERVED_MAPPER_BASE_H
#define GUARD_LIBCSC_STOCKBOOKING_CUSTOMER_STOCKRESERVED_MAPPER_BASE_H

#include <libbasar_definitions.h>
#include "customerstockreservedptr.h"

namespace libcsc {
namespace stockbooking {

class CustomerStockReservedMapperBase
{
public:
	CustomerStockReservedMapperBase(CustomerStockReservedPtr customerStockReserved);

	void			map();
protected:
	virtual ~CustomerStockReservedMapperBase();

	virtual void	doMap() = 0;

	void setBranchNo( const basar::Int16& branchNo );
	void setCustomerNo(const basar::Int32& customerNo);
	void setArticleNo(const basar::Int32& articleNo );
	void setReservedQty(const basar::Int32& reservedQty );
	void setDateFrom(const basar::Int32& dateFrom );
	void setTimeFrom(const basar::Int32& timeFrom );
	void setDateTo(const basar::Int32& dateTo );
	void setTimeTo(const basar::Int32& timeto );
	void setKdAuftragNr(const basar::Int32& kdAuftragNr);
	void setReservType(const basar::Int16& reservType);

private:
	CustomerStockReservedPtr m_CustomerStockReserved;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_CUSTOMER_STOCKRESERVED_MAPPER_BASE_H

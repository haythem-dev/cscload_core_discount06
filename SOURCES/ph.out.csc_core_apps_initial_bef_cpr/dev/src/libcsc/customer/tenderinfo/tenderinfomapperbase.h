#ifndef GUARD_LIBCSC_CUSTOMER_TENDERINFOMAPPERBASE_H
#define GUARD_LIBCSC_CUSTOMER_TENDERINFOMAPPERBASE_H

#include <customer/tenderinfo/tenderinfoptr.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class TenderInfoMapperBase
{
public:
	TenderInfoMapperBase(TenderInfoPtr tenderInfo);

	void map();

protected:
	virtual ~TenderInfoMapperBase();
    
	virtual void doMap() = 0;
    
	void setBranchNo(const basar::Int16 branchNo);
	void setCustomerNo(const basar::Int32 customerNo);
	void setTenderNo(const basar::Int32 tenderNo);
	void setContractNo(const basar::VarString& contractNo);
	void setValidFromDate(const basar::Date& validFromDate);
	void setValidToDate(const basar::Date& validToDate);
	void setChainNo(const basar::Int32 chainNo);
	
	void setArticleNo(const basar::Int32 articleNo);
	void setTenderQuantity(const basar::Int32 tenderQuantity);
	void setFreeTenderQuantity(const basar::Int32 freeTenderQuantity);
	void setDeliveredTenderQuantity(const basar::Int32 deliveredTenderQuantity);
	void setReturnedTenderQuantity(const basar::Int32 returnedTenderQuantity);

private:
	TenderInfoPtr   m_TenderInfo;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_TENDERINFOMAPPERBASE_H

#ifndef GUARD_LIBCSC_CUSTOMER_TENDERINFO_H
#define GUARD_LIBCSC_CUSTOMER_TENDERINFO_H

#include <customer/tenderinfo/itenderinfo.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <datatypes/date.h>

namespace libcsc {
namespace customer {

class TenderInfo : public ITenderInfo
{
    // because of OR mapping
    friend class TenderInfoMapperBase;

public:
	TenderInfo();
    virtual ~TenderInfo();

	virtual basar::Int16			getBranchNo() const;
	virtual basar::Int32			getCustomerNo() const;
	virtual basar::Int32			getTenderNo() const;
	virtual const basar::VarString&	getContractNo() const;
	virtual const basar::Date&		getValidFromDate() const;
	virtual const basar::Date&		getValidToDate() const;
	virtual basar::Int32			getChainNo() const;

	virtual basar::Int32			getArticleNo() const;
	virtual basar::Int32			getTenderQuantity() const;
	virtual basar::Int32			getFreeTenderQuantity() const;
	virtual basar::Int32			getDeliveredTenderQuantity() const;
	virtual basar::Int32			getReturnedTenderQuantity() const;

private:
    libcsc::Int16		m_BranchNo;
	libcsc::Int32		m_CustomerNo;
	libcsc::Int32		m_TenderNo;
	libcsc::VarString	m_ContractNo;
	libcsc::Date		m_ValidFromDate;
	libcsc::Date		m_ValidToDate;
	libcsc::Int32		m_ChainNo;

	libcsc::Int32		m_ArticleNo;
	libcsc::Int32		m_TenderQuantity;
	libcsc::Int32		m_FreeTenderQuantity;
	libcsc::Int32		m_DeliveredTenderQuantity;
	libcsc::Int32		m_ReturnedTenderQuantity;

};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_TENDERINFO_H

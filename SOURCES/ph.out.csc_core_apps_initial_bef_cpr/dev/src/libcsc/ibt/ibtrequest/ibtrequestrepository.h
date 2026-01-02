#ifndef GUARD_LIBCSC_IBT_IBTREQUEST_REPOSITORY_H
#define GUARD_LIBCSC_IBT_IBTREQUEST_REPOSITORY_H

#include <ibt/ibtrequest/iibtrequestrepository.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <ibt/ibtrequest/ibtrequestptr.h>
#include <ibt/ibtrequest/discount/ibtrequestdiscountptr.h>
#include <ibt/ibtrequest/remark/ibtrequestremarkptr.h>
#include <boost/enable_shared_from_this.hpp>

namespace libcsc
{
namespace ibt
{
class IbtRequestRepository : public IIbtRequestRepository,
							 public boost::enable_shared_from_this<IbtRequestRepository>
{
public:
	IbtRequestRepository();
    virtual ~IbtRequestRepository();

    void injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory );
	void injectAccessor( persistence::IAccessorPtr accessor );

	virtual void reset();

	virtual IIbtRequestPtr findIbtRequestByKey( const IbtRequestKey & key );
	virtual IIbtRequestPtr findIbtRequestById( const basar::Int32 id );

	virtual void reloadIbtRequest( IIbtRequestPtr iibtRequest );
	virtual IIbtRequestCollectionPtr findByPattern( const basar::Int16 branchNo, const IbtRequestProcessingStateEnum state );

	virtual void saveIbtRequest( IIbtRequestPtr iibtRequest );
	virtual void deleteIbtRequest( IIbtRequestPtr iibtRequest );

	virtual IIbtRequestPtr createRequest( const IbtRequestKey & key );
	virtual IIbtRequestDiscountPtr createRequestDiscount( IbtRequestPtr ibtRequest, const IbtRequestDiscountTypeEnum discountType, const basar::Int16 paymentTargetNo ) const;
	virtual IIbtRequestRemarkPtr createRequestRemark( IbtRequestPtr ibtRequest, const IbtRequestRemarkLevelEnum remarkLevel, const OrderRemarkTypeEnum remarkType ) const;

private:
	void reloadIbtRequest( IbtRequestPtr ibtRequest );
	void saveIbtRequest( IbtRequestPtr ibtRequest );
	void setIbtRequestDiscountsSerial( IbtRequestPtr ibtRequest );
	void setIbtRequestRemarksSerial( IbtRequestPtr ibtRequest );
	void saveIbtRequestDiscounts( IbtRequestPtr ibtRequest );
	void saveIbtRequestRemarks( IbtRequestPtr ibtRequest );
	void deleteIbtRequest( IbtRequestPtr ibtRequest );
	void deleteIbtRequestDiscounts( IbtRequestPtr ibtRequest );
	void deleteIbtRequestRemarks( IbtRequestPtr ibtRequest );
	IbtRequestPtr createRequest();
	IbtRequestDiscountPtr createRequestDiscount() const;
	IbtRequestRemarkPtr createRequestRemark() const;

    persistence::ITransactionFactoryPtr		m_TransactionFactory;
    persistence::IAccessorPtr				m_Accessor;

	mutable IbtRequestCollection			m_IbtRequests;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUEST_REPOSITORY_H

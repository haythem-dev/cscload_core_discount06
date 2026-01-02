#ifndef GUARD_LIBCSC_IBT_IBTRESPONSE_REPOSITORY_H
#define GUARD_LIBCSC_IBT_IBTRESPONSE_REPOSITORY_H

#include <ibt/ibtresponse/iibtresponserepository.h>
#include <ibt/ibtresponse/ibtresponseptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>

namespace libcsc
{
namespace ibt
{
class IbtResponseRepository : public IIbtResponseRepository
{
public:
	IbtResponseRepository();
    virtual ~IbtResponseRepository();

    void injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory );
    void injectAccessor( persistence::IAccessorPtr accessor );

	virtual IIbtResponsePtr findIbtResponse( const basar::Int32 ibtOrderNo, const basar::Int32 ibtPosNo );

	virtual IIbtResponsePtr createResponse( const basar::Int32 ibtRequestId );
	virtual void saveIbtResponse( IIbtResponsePtr ibtResponse );

private:
	void saveIbtResponse( IbtResponsePtr ibtResponse );

    persistence::ITransactionFactoryPtr		m_TransactionFactory;
    persistence::IAccessorPtr				m_Accessor;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTRESPONSE_REPOSITORY_H

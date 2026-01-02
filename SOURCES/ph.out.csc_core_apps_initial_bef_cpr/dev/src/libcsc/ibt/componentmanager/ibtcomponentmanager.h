#ifndef GUARD_LIBCSC_IBT_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_IBT_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactory.h>
#include <libbasar_definitions.h>
#include <ibt/environmentchecker/ienvironmentcheckerptr.h>
#include <ibt/articlequotachecker/iarticlequotacheckerptr.h>
#include <ibt/bookingcompletedchecker/ibookingcompletedcheckerptr.h>
#include <ibt/transportexclusionchecker/itransportexclusioncheckerptr.h>
#include <ibt/ibtrequest/iibtrequestrepositoryptr.h>
#include <ibt/ibtresponse/iibtresponserepositoryptr.h>
#include <ibt/ibtbranch/iibtbranchrepositoryptr.h>
#include <parameter/ibranchparametergetterptr.h>
#include <parameter/iorderparametergetterptr.h>

class pxSession;
class pxOrder;

namespace libcsc{
namespace ibt{

class IbtComponentManager : public persistence::ITransactionFactory,
                            public boost::enable_shared_from_this<IbtComponentManager>
{
public:
    IbtComponentManager();
    virtual ~IbtComponentManager();

    void injectConnection( persistence::ConnectionPtr connection );
    void injectTransactionHandler (nDataBase * transHandler);

    IArticleQuotaCheckerPtr getArticleQuotaChecker();
    IBookingCompletedCheckerPtr getBookingCompletedChecker();
    IEnvironmentCheckerPtr getEnvironmentChecker();
    ITransportExclusionCheckerPtr getTransportExclusionChecker();

    virtual persistence::TransactionGuard createTransaction() const;
    ibt::IIbtRequestRepositoryPtr createIbtRequestRepository();
    ibt::IIbtRequestRepositoryPtr createIbtRequestRepository( const pxOrder * order );
    ibt::IIbtResponseRepositoryPtr createIbtResponseRepository();
	ibt::IIbtBranchRepositoryPtr createIbtBranchRepository();

private:
    IbtComponentManager( const IbtComponentManager & );
    IbtComponentManager & operator=( const IbtComponentManager & );

    persistence::IAccessorPtr createAccessor();
    persistence::IAccessorPtr createAccessor( const pxOrder * order );
	parameter::IOrderParameterGetterPtr createOrderParameterGetter( const pxOrder * order );

    persistence::ConnectionPtr m_Connection;
    nDataBase *                m_TransactionHandler;
};

} // end namespace ibt
} // end namespace libcsc

#endif //end GUARD_LIBCSC_IBT_COMPONENT_MANAGER_H

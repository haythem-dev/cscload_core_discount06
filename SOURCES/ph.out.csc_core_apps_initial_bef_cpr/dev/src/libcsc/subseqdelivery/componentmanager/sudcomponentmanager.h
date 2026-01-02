#ifndef GUARD_LIBCSC_SUD_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_SUD_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactory.h>
#include <subseqdelivery/workupcompletedchecker/iworkupcompletedcheckerptr.h>

class pxSession;

namespace libcsc
{
namespace sud
{
class SudComponentManager : public persistence::ITransactionFactory,
                            public boost::enable_shared_from_this<SudComponentManager>
{
public:
    SudComponentManager();
    virtual ~SudComponentManager();

    void injectConnection( persistence::ConnectionPtr connection );
    void injectTransactionHandler (nDataBase * transHandler);

	
	IWorkupCompletedCheckerPtr getWorkupCompletedChecker();

    virtual persistence::TransactionGuard createTransaction() const;
    
private:
    SudComponentManager( const SudComponentManager & );
    SudComponentManager & operator=( const SudComponentManager & );

    persistence::IAccessorPtr createAccessor();
	 
    persistence::ConnectionPtr	m_Connection;
    nDataBase *					m_TransactionHandler;
};

} // end namespace sud
} // end namespace libcsc

#endif //end GUARD_LIBCSC_SUD_COMPONENT_MANAGER_H

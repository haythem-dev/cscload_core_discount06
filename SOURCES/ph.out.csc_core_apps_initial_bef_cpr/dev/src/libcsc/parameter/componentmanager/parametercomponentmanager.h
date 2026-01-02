#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/itransactionfactory.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <parameter/ibranchparametergetterptr.h>

#include <parameter/csvorderimport/icsvorderimportrepositoryptr.h>

class pxSession;

namespace libcsc {
namespace parameter {

class ParameterComponentManager : public persistence::ITransactionFactory,
							 public boost::enable_shared_from_this<ParameterComponentManager>
{
public:
	ParameterComponentManager();
	virtual ~ParameterComponentManager();

	void injectConnection( persistence::ConnectionPtr connection );
	void injectTransactionHandler (nDataBase * transHandler);

	virtual libcsc::persistence::TransactionGuard	createTransaction() const;

	ICSVOrderImportRepositoryPtr					getCSVOrderImportRepository() const;
	

private:
//	ParameterComponentManager( const ParameterComponentManager & );
//	ParameterComponentManager & operator=( const ParameterComponentManager & );

	persistence::IAccessorPtr					createAccessor() const;
	ICSVOrderImportRepositoryPtr				createCSVOrderImportRepository() const;

	persistence::ConnectionPtr					m_Connection;
	nDataBase *									m_TransactionHandler;

	mutable ICSVOrderImportRepositoryPtr		m_CSVOrderImportRepository;
	parameter::IBranchParameterGetterPtr		m_BranchParameterGetter;
};

} // end namespace parameter
} // end namespace libcsc

#endif //end GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_COMPONENT_MANAGER_H

#ifndef GUARD_LIBCSC_CSCORDERTYPE_REPOSITORY_H
#define GUARD_LIBCSC_CSCORDERTYPE_REPOSITORY_H

#include <cscordertype/repository/icscordertyperepository.h>
#include <persistence/iaccessorptr.h>
#include <map>
#include <persistence/itransactionfactoryptr.h>
#include <cscordertype/cscordertypebatchconfig/cscordertypebatchconfigptr.h>

namespace libcsc
{
namespace cscordertype
{
class CSCOrderTypeRepository : public ICSCOrderTypeRepository
{
public:
	CSCOrderTypeRepository();
	virtual ~CSCOrderTypeRepository();

	virtual void reset();

	void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
	void injectAccessor( persistence::IAccessorPtr accessor );

	virtual void injectSelectCSCOrderTypeAccessor(persistence::IAccessorPtr accessor);
	virtual void injectInsertCSCOrderTypeAccessor(persistence::IAccessorPtr accessor);
	virtual void injectUpdateCSCOrderTypeAccessor(persistence::IAccessorPtr accessor);
	virtual void injectDeleteCSCOrderTypeAccessor(persistence::IAccessorPtr accessor);

	virtual void injectSelectCSCOrderTypeBatchConfigAccessor(persistence::IAccessorPtr accessor);
	virtual void injectInsertCSCOrderTypeBatchConfigAccessor(persistence::IAccessorPtr accessor);
	virtual void injectUpdateCSCOrderTypeBatchConfigAccessor(persistence::IAccessorPtr accessor);
	virtual void injectDeleteCSCOrderTypeBatchConfigAccessor(persistence::IAccessorPtr accessor);

	virtual void injectSelectCSCOrderTypeFlagTypeAccessor(persistence::IAccessorPtr accessor);

	ICSCOrderTypePtr createOrderType() const;
	CSCOrderTypeCollectionPtr findOrderTypes( const basar::Int16 branchNo ) const;
	ICSCOrderTypePtr findOrderType( const basar::Int16 branchNo, const basar::VarString & orderType ) const;
	void saveOrderType( const ICSCOrderTypePtr orderType ) const;
	void deleteOrderType( const ICSCOrderTypePtr orderType ) const;

private:
	void saveOrderTypeBatchConfig( CSCOrderTypeBatchConfigPtr batchConfig ) const;

	mutable CSCOrderTypeCollectionPtr m_CSCOrderTypeList;

	mutable persistence::IAccessorPtr m_Accessor;
	persistence::IAccessorPtr m_SelectCSCOrderTypeAccessor;
	persistence::IAccessorPtr m_InsertCSCOrderTypeAccessor;
	persistence::IAccessorPtr m_UpdateCSCOrderTypeAccessor;
	persistence::IAccessorPtr m_DeleteCSCOrderTypeAccessor;
	persistence::IAccessorPtr m_SelectCSCOrderTypeBatchConfigAccessor;
	persistence::IAccessorPtr m_InsertCSCOrderTypeBatchConfigAccessor;
	persistence::IAccessorPtr m_UpdateCSCOrderTypeBatchConfigAccessor;
	persistence::IAccessorPtr m_DeleteCSCOrderTypeBatchConfigAccessor;
	persistence::IAccessorPtr m_SelectCSCOrderTypeFlagTypeAccessor;
	persistence::ITransactionFactoryPtr	m_TransactionFactory;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_REPOSITORY_H

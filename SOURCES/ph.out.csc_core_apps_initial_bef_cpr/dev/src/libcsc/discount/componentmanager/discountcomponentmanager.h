#ifndef GUARD_LIBCSC_DISCOUNT_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_DISCOUNT_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/itransactionfactory.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>

#include <discount/tender/repository/tenderdiscountrepositoryptr.h>
#include <discount/basevalues/discountbasevalue/discountbasevaluerepositoryptr.h>
#include <discount/basevalues/orderbasevalue/articleclassificationrepository.h>
#include <discount/calculator/commands/idiscountcalculatorcommandptr.h>
#include <discount/discountcollectionfinder/idiscountcollectionfinderptr.h>
#include <discount/logger/discountlogger/idiscountloggerptr.h>
#include <discount/orderpositiondiscount/orderpositiondiscountrepositoryptr.h>
#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedrepositoryptr.h>
#include <discount/resultprocessor/iresultprocessorptr.h>
#include <discount/resultprocessor/repositoryresultprocessor.h>
#include <discount/resultprocessor/rebateinkindresultprocessor.h>
#include <discount/resultprocessor/compositeresultprocessor.h>

#include <parameter/isessionparametergetterptr.h>
#include <base/irunnableptr.h>

class pxOrder;
class pxOrderItem;

namespace libcsc
{
namespace discount
{
class DiscountComponentManager : public persistence::ITransactionFactory,
								 public boost::enable_shared_from_this<DiscountComponentManager>
{
public:
	DiscountComponentManager();
	virtual ~DiscountComponentManager();

	void injectConnection( persistence::ConnectionPtr connection );
	void injectTransactionHandler (nDataBase * transHandler);
	void injectParameterGetter( parameter::ISessionParameterGetterPtr parameterGetter );

	virtual libcsc::persistence::TransactionGuard createTransaction() const;
	OrderPositionDiscountRepositoryPtr createOrderPositionDiscountRepository();
    libcsc::discount::IDiscountCollectionFinderPtr      createDiscountCollectionFinder();
    TenderDiscountRepositoryPtr createTenderDiscountRepository();
    //IOrderBaseValueGetterPtr                            createOrderBaseValueGetter(pxOrderItem *);

	base::IRunnablePtr getPositionDiscountCalcUC( pxOrderItem * orderItem );
	base::IRunnablePtr getOrderDiscountCalcUC( pxOrder * order );

private:
	DiscountComponentManager( const DiscountComponentManager & );
	DiscountComponentManager & operator=( const DiscountComponentManager & );

	DiscountBaseValueRepositoryPtr createDiscountBaseValueRepository();
	OrderPositionDiscountProcessedRepositoryPtr createPositionDiscountProcessedRepository();
	ArticleClassificationRepositoryPtr createArticleClassificationRepository();

	CompositeResultProcessorPtr createCompositeResultProcessor();
	RebateInKindResultProcessorPtr createRebateInKindResultProcessor( OrderPositionDiscountRepositoryPtr orderPositionDiscountRepository );
	RepositoryResultProcessorPtr createRepositoryResultProcessor( OrderPositionDiscountRepositoryPtr orderPositionDiscountRepository );

	IDiscountLoggerPtr createDiscountLogger();
	persistence::IAccessorPtr createAccessor();

	persistence::ConnectionPtr				m_Connection;
	parameter::ISessionParameterGetterPtr	m_SessionParameterGetter;
	nDataBase *								m_TransactionHandler;
};

} // end namespace discount
} // end namespace libcsc

#endif //end GUARD_LIBCSC_DISCOUNT_COMPONENT_MANAGER_H

#ifndef GUARD_CSC_PHADEX_USECASE_TRANSACTION_RECORD_MAPPER_H
#define GUARD_CSC_PHADEX_USECASE_TRANSACTION_RECORD_MAPPER_H

#include "componentmanager/csc_phadexapplcompmgrptr.h"
#include "itransactionrecordmapper.h"
#include "componentmanager/iusecasegetterptr.h"
#include <domainmodule/phadextransaction/iphadextransactionptr.h>
#include <libbasarcmnutil.h>

namespace csc_phadex
{
namespace useCase
{
class TransactionRecordMapper : public ITransactionRecordMapper
{
public:
	TransactionRecordMapper();
	virtual ~TransactionRecordMapper();

	void injectUseCaseGetter( csc_phadex::componentManager::IUseCaseGetterPtr useCaseGetter );

    virtual libutil::useCase::IRunnablePtr map( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord );

private:
	TransactionRecordMapper( const TransactionRecordMapper & );
	TransactionRecordMapper & operator= ( const TransactionRecordMapper & );

    libutil::useCase::IRunnablePtr getTenderCancellationUC( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord );
    libutil::useCase::IRunnablePtr getNarcPrintUpdateUC( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord );
    libutil::useCase::IRunnablePtr getDeliveryNoteCompletedUC( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord );

    libutil::useCase::IRunnablePtr getDeliveryNoteCancellationUC(csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord);
	libutil::useCase::IRunnablePtr getBlockedArticleUC(csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord);

	libutil::useCase::IRunnablePtr getDocumentPrintInfoUC(csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord);
	libutil::useCase::IRunnablePtr getSAPReferenceNoUC(csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord);

	csc_phadex::componentManager::IUseCaseGetterPtr		m_UseCaseGetter;
    const log4cplus::Logger &                           m_Logger;
};

} // namespace useCase
} // namespace csc_phadex

#endif // GUARD_CSC_PHADEX_USECASE_TRANSACTION_RECORD_MAPPER_H

#ifndef GUARD_CSC_PHADEX_COMPONENTMANAGER_IUSECASEGETTER_H
#define GUARD_CSC_PHADEX_COMPONENTMANAGER_IUSECASEGETTER_H

#include <libutil/irunnableptr.h>
#include <usecase/transferuc/itransferucptr.h>
#include <usecase/tendercancellationuc/itendercancellationucptr.h>
#include <usecase/narcprintupdateuc/inarcprintupdateucptr.h>
#include <usecase/deliverynotecompleteduc/ideliverynotecompleteducptr.h>
#include <usecase/deliverynotecancellationuc/ideliverynotecancellationucptr.h>
#include <usecase/blockedarticleuc/iblockedarticleucptr.h>
#include <usecase/documentprintinfouc/idocumentprintinfoucptr.h>
#include <usecase/sapreferencenouc/isapreferencenoucptr.h>

namespace csc_phadex
{
namespace componentManager
{
class IUseCaseGetter
{
public:
	virtual ~IUseCaseGetter() {};

	virtual csc_phadex::useCase::ITransferUCPtr getTransferUC() = 0;
	virtual libutil::useCase::IRunnablePtr getProcessUC() = 0;
    virtual csc_phadex::useCase::ITenderCancellationUCPtr getTenderCancellationUC() = 0;
    virtual csc_phadex::useCase::INarcPrintUpdateUCPtr getNarcPrintUpdateUC() = 0;
    virtual csc_phadex::useCase::IDeliveryNoteCompletedUCPtr getDeliveryNoteCompletedUC() = 0;
    virtual csc_phadex::useCase::IDeliveryNoteCancellationUCPtr getDeliveryNoteCancellationUC() = 0;
	virtual csc_phadex::useCase::IBlockedArticleUCPtr getBlockedArticleUC() = 0;
	virtual csc_phadex::useCase::IDocumentPrintInfoUCPtr getDocumentPrintInfoUC() = 0;
	virtual csc_phadex::useCase::ISAPReferenceNoUCPtr getSAPReferenceNoUC() = 0;
};
}
}

#endif // GUARD_CSC_PHADEX_COMPONENTMANAGER_IUSECASEGETTER_H

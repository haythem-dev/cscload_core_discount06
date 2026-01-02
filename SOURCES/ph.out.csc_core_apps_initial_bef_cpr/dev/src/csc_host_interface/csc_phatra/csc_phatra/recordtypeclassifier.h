//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   05.02.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORD_TYPE_CLASSIFIER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORD_TYPE_CLASSIFIER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil.h>
#include "irecordtypeof.h"
#include <set>

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
        }
    }
}

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{
class RecordTypeClassifier : public IRecordTypeOf
{
    public:
        RecordTypeClassifier( const basar::VarString& type );
        ~RecordTypeClassifier();

        virtual bool isTypeOf_ChangeOrderItem() const;
        virtual bool isTypeOf_ArticleInfoGoodsIn() const;
        virtual bool isTypeOf_StopSellingOfArticle() const;
        virtual bool isTypeOf_ChangeIBTStockLevel() const;
        virtual bool isTypeOf_ChangeQuarantine() const;
        virtual bool isTypeOf_CodeBlocage() const;
        virtual bool isTypeOf_Batch() const;
        virtual bool isTypeOf_DealerVolumeTotal() const;
        virtual bool isTypeOf_DealerVolumeElectronic() const;
        virtual bool isTypeOf_DealerVolumeExclusiveTotal() const;
        virtual bool isTypeOf_DealerVolumeExclusiveElectronic() const;
        virtual bool isTypeOf_CustomerReturn() const;
        virtual bool isTypeOf_CreditLimitChain() const;
        virtual bool isTypeOf_CreditLimitCustomer() const;
        virtual bool isTypeOf_CreditLimitCustomerReturn() const;
        virtual bool isTypeOf_CreditLimitGroup() const;
        virtual bool isTypeOf_CreditLimit() const;
        virtual bool isTypeOf_DiscountAccount() const;
        virtual bool isTypeOf_ExpiryDate() const;
        virtual bool isTypeOf_ChangeArticleDetails() const;
        virtual bool isTypeOf_ImportInvoiceNo() const;
        virtual bool isTypeOf_TransferQuarantine() const;
        virtual bool isTypeOf_GoodsIn() const;
        virtual bool isTypeOf_OTHER() const;
        virtual bool isTypeOf_TenderChangeCustomerReturn() const;
        virtual bool isTypeOf_PickingLack() const;
        virtual bool isTypeOf_StorageReconciliation() const;
        virtual bool isTypeOf_BatchInconsistency() const;
        virtual bool isTypeOf_PerpetualStocktaking() const;
        virtual bool isTypeOf_StorageReconciliationPrewholesale() const;
        virtual bool isTypeOf_InvoiceCancellation() const;
        virtual bool isTypeOf_ChangeArticleMasterData() const;
        virtual bool isTypeOf_IBTGoods() const;

    private:
        RecordTypeClassifier( const RecordTypeClassifier& );
        RecordTypeClassifier& operator= ( const RecordTypeClassifier& );

        /* static */ std::set<basar::VarString> m_RecordTypes; // Björn

        const basar::VarString m_Type;
};

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

//----------------------------------------------------------------------------
#endif

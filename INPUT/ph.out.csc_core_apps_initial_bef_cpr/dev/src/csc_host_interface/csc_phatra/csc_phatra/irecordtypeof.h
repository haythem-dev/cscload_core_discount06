//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   05.02.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_IRECORD_TYPE_OF_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_IRECORD_TYPE_OF_H

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

class IRecordTypeOf
{
public:
    virtual ~IRecordTypeOf(){};
    virtual bool isTypeOf_ChangeOrderItem() const = 0;
    virtual bool isTypeOf_ArticleInfoGoodsIn() const = 0;
    virtual bool isTypeOf_StopSellingOfArticle() const = 0;
    virtual bool isTypeOf_ChangeIBTStockLevel() const = 0;
    virtual bool isTypeOf_ChangeQuarantine() const = 0;
    virtual bool isTypeOf_CodeBlocage() const = 0;
    virtual bool isTypeOf_Batch() const = 0;
    virtual bool isTypeOf_CustomerReturn() const = 0;
    virtual bool isTypeOf_DealerVolumeTotal() const = 0;
    virtual bool isTypeOf_DealerVolumeElectronic() const = 0;
    virtual bool isTypeOf_DealerVolumeExclusiveTotal() const = 0;
    virtual bool isTypeOf_DealerVolumeExclusiveElectronic() const = 0;
    virtual bool isTypeOf_CreditLimitChain() const = 0;
    virtual bool isTypeOf_CreditLimitCustomer() const = 0;
    virtual bool isTypeOf_CreditLimitCustomerReturn() const = 0;
    virtual bool isTypeOf_CreditLimitGroup() const = 0;
    virtual bool isTypeOf_CreditLimit() const = 0;
    virtual bool isTypeOf_DiscountAccount() const = 0;
    virtual bool isTypeOf_ExpiryDate() const = 0;
    virtual bool isTypeOf_ChangeArticleDetails() const = 0;
    virtual bool isTypeOf_ImportInvoiceNo() const = 0;
    virtual bool isTypeOf_TransferQuarantine() const = 0;
    virtual bool isTypeOf_GoodsIn() const = 0;
    virtual bool isTypeOf_TenderChangeCustomerReturn() const = 0;
    virtual bool isTypeOf_PickingLack() const = 0;
    virtual bool isTypeOf_StorageReconciliation() const = 0;
    virtual bool isTypeOf_BatchInconsistency() const = 0;
    virtual bool isTypeOf_PerpetualStocktaking() const = 0;
    virtual bool isTypeOf_StorageReconciliationPrewholesale() const = 0;
    virtual bool isTypeOf_InvoiceCancellation() const = 0;
    virtual bool isTypeOf_ChangeArticleMasterData() const = 0;
    virtual bool isTypeOf_IBTGoods() const = 0;
};

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

//----------------------------------------------------------------------------
#endif

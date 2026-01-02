    //----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   05.02.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypeclassifier.h"
#include "recordtypeclassifier_definitions.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{

RecordTypeClassifier::RecordTypeClassifier( const basar::VarString& type )
: m_Type( type )
{
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_CHANGEORDERITEM );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_ARTICLEINFOGOODSIN );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_STOPSELLINGOFARTICLE );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_CHANGEIBTSTOCKLEVEL );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_CODEBLOCAGE );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_BATCH );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_DEALERVOLUMETOTAL );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_DEALERVOLUMEELECTRONIC );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_DEALERVOLUMEEXCLUSIVETOTAL );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_DEALERVOLUMEEXCLUSIVEELECTRONIC );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_CREDITLIMITCHAIN );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_CREDITLIMITCUSTOMER );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_CREDITLIMIT );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_DISCOUNTACCOUNT );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_CHANGEARTICLEDETAILS );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_IMPORTINVOICENO );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_TRANSFERQUARANTINE );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_GOODSIN );
    //m_RecordTypes.insert( util::recordtypes::RECORDTYPE_RETURNPREDELIVEREDARTICLE );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_TENDERCHANGECUSTOMERRETURN );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_PICKINGLACK );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_STORAGERECONCILIATIONPREWHOLESALE );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_BATCHINCONSISTENCY );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_STORAGERECONCILIATION );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_PERPETUALSTOCKTAKING );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_INVOICECANCELLATION );
    m_RecordTypes.insert( util::recordtypes::RECORDTYPE_CHANGEARTICLEMASTERDATA );
}

RecordTypeClassifier::~RecordTypeClassifier()
{
}

bool RecordTypeClassifier::isTypeOf_OTHER() const
{
    if( m_RecordTypes.find( m_Type ) == m_RecordTypes.end() )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_ChangeOrderItem() const
{
    if( util::recordtypes::RECORDTYPE_CHANGEORDERITEM == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_ArticleInfoGoodsIn() const
{
    if( util::recordtypes::RECORDTYPE_ARTICLEINFOGOODSIN == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_StopSellingOfArticle() const
{
    if( util::recordtypes::RECORDTYPE_STOPSELLINGOFARTICLE == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_ChangeIBTStockLevel() const
{
    if( util::recordtypes::RECORDTYPE_CHANGEIBTSTOCKLEVEL == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_ChangeQuarantine() const
{
    if( util::recordtypes::RECORDTYPE_CHANGEQUARANTINE == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_CodeBlocage() const
{
    if( util::recordtypes::RECORDTYPE_CODEBLOCAGE == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_Batch() const
{
    if( util::recordtypes::RECORDTYPE_BATCH == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_DealerVolumeTotal() const
{
    if( util::recordtypes::RECORDTYPE_DEALERVOLUMETOTAL == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_CustomerReturn() const
{
    if( util::recordtypes::RECORDTYPE_CUSTOMERRETURN == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_DealerVolumeElectronic() const
{
    if( util::recordtypes::RECORDTYPE_DEALERVOLUMEELECTRONIC == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_DealerVolumeExclusiveTotal() const
{
    if( util::recordtypes::RECORDTYPE_DEALERVOLUMEEXCLUSIVETOTAL == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_DealerVolumeExclusiveElectronic() const
{
    if( util::recordtypes::RECORDTYPE_DEALERVOLUMEEXCLUSIVEELECTRONIC == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_CreditLimitChain() const
{
    if( util::recordtypes::RECORDTYPE_CREDITLIMITCHAIN == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_CreditLimitGroup() const
{
    if( util::recordtypes::RECORDTYPE_CREDITLIMITGROUP == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_CreditLimitCustomer() const
{
    if( util::recordtypes::RECORDTYPE_CREDITLIMITCUSTOMER == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_CreditLimitCustomerReturn() const
{
    if( util::recordtypes::RECORDTYPE_CREDITLIMITCUSTOMERRETURN == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_CreditLimit() const
{
    if( util::recordtypes::RECORDTYPE_CREDITLIMIT == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_DiscountAccount() const
{
    if( util::recordtypes::RECORDTYPE_DISCOUNTACCOUNT == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_ExpiryDate() const
{
    if( util::recordtypes::RECORDTYPE_EXPIRYDATE == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_ChangeArticleDetails() const
{
    if( util::recordtypes::RECORDTYPE_CHANGEARTICLEDETAILS == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_ImportInvoiceNo() const
{
    if( util::recordtypes::RECORDTYPE_IMPORTINVOICENO == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_TransferQuarantine() const
{
    if( util::recordtypes::RECORDTYPE_TRANSFERQUARANTINE == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_GoodsIn() const
{
    if( util::recordtypes::RECORDTYPE_GOODSIN == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_TenderChangeCustomerReturn() const
{
    if( util::recordtypes::RECORDTYPE_TENDERCHANGECUSTOMERRETURN == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_InvoiceCancellation() const
{
    if( util::recordtypes::RECORDTYPE_INVOICECANCELLATION == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_PickingLack() const
{
    if( util::recordtypes::RECORDTYPE_PICKINGLACK == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_StorageReconciliation() const
{
    if( util::recordtypes::RECORDTYPE_STORAGERECONCILIATION == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_BatchInconsistency() const
{
    if( util::recordtypes::RECORDTYPE_BATCHINCONSISTENCY == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_PerpetualStocktaking() const
{
    if( util::recordtypes::RECORDTYPE_PERPETUALSTOCKTAKING == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_StorageReconciliationPrewholesale() const
{
    if( util::recordtypes::RECORDTYPE_STORAGERECONCILIATIONPREWHOLESALE == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_ChangeArticleMasterData() const
{
    if( util::recordtypes::RECORDTYPE_CHANGEARTICLEMASTERDATA == m_Type )
    {
        return true;
    }
    return false;
}

bool RecordTypeClassifier::isTypeOf_IBTGoods() const
{
    if( util::recordtypes::RECORDTYPE_IBTGOODS == m_Type )
    {
        return true;
    }
    return false;
}

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

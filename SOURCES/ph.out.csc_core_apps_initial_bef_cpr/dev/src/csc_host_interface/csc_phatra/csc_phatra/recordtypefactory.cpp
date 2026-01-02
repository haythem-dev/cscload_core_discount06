//---------------------------------------------------------------------------//
/*! \file
 *  \brief      Encapsulation of creation process of return type
 *  \author     Bjoern Bischof
 *  \date       05.03.2011
 *  \version    00.00.00.01 first version
 */ //-----------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypefactory.h"
#include "irecordtypeof.h"
#include "ipxvbservicelocator.h"
#include "transactionrecordbase.h"

#include "recordprocesshelperptr.h"
#include "recordprocesshelper.h"
// record types

#include "recordtypenoprocessing.h"
#include "recordtypearticleinfogoodsin.h"
#include "recordtypebatch.h"
#include "recordtypeexpirydate.h"
#include "recordtypechangearticledetails.h"
#include "recordtypechangeibtstocklevel.h"
#include "recordtypechangeorderitem.h"
#include "recordtypechangequarantine.h"
#include "recordtypecodeblocage.h"
#include "recordtypecreditlimit.h"
#include "recordtypecreditlimitchain.h"
#include "recordtypecreditlimitgroup.h"
#include "recordtypecreditlimitcustomer.h"
#include "recordtypecreditlimitcustomerreturn.h"
#include "recordtypecustomerreturn.h"
#include "recordtypedealervolumetotal.h"
#include "recordtypedealervolumeelectronic.h"
#include "recordtypedealervolumeexclusivetotal.h"
#include "recordtypedealervolumeexclusiveelectronic.h"
#include "recordtypediscountaccount.h"
#include "recordtypegoodsin.h"
#include "recordtypeimportinvoiceno.h"
#include "recordtypeother.h"
#include "recordtypereturnpredeliveredarticle.h"
#include "recordtypestopsellingofarticle.h"
#include "recordtypetransferquarantine.h"
#include "irecordtypetransformer.h"
#include "recordtypetenderchangecustomerreturn.h"
#include "recordtypepickinglack.h"
#include "recordtypeinvoicecancellation.h"
#include "recordtypechangearticlemasterdata.h"
#include "recordtypeibtgoods.h"

//recordtype ptrs (for injection)
#include "recordtypetransferquarantineptr.h"
#include "recordtypecodeblocageptr.h"
#include "recordtypegoodsinptr.h"
#include "recordtypeotherptr.h"
#include "recordtypecustomerreturnptr.h"
#include "recordtypepickinglackptr.h"
#include "recordtypeinvoicecancellationptr.h"
#include "recordtypetenderchangecustomerreturnptr.h"
#include "recordtypeibtgoodsptr.h"

#include <icsc_loggerptr.h>
#include <icsc_logger.h>
//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{

    RecordTypeFactory::RecordTypeFactory( pxVerbund::IPXVBServiceLocatorPtr vbsvcloc, libcsc_utils::ICSC_LoggerPtr csc_logger )
: m_IPXVBServiceLocator( vbsvcloc ), m_CSC_Logger(csc_logger)
{
    m_RecordProcessHelperPtr = processing::RecordProcessHelperPtr( new processing::RecordProcessHelper(  m_IPXVBServiceLocator->getPXVBSession(),  m_IPXVBServiceLocator->getPXVBOrderEntryParamChecker(), m_IPXVBServiceLocator->getPXVBDBConnection(), m_CSC_Logger ) );
}

RecordTypeFactory::~RecordTypeFactory()
{
}

util::IRecordTypeProcessorPtr RecordTypeFactory::createRecordType( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeFactory, createRecordType );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    RecordTypeBasePtr recordType;
    recordType = create( record );
    recordType->injectPXVBDBConnection( m_IPXVBServiceLocator->getPXVBDBConnection() );
    recordType->injectPXVBSession( m_IPXVBServiceLocator->getPXVBSession() );
    recordType->injectCSC_Logger( m_CSC_Logger );
    return recordType;
}

util::IRecordTypeTransformerPtr RecordTypeFactory::createTransformer( const IRecordTypeOfPtr typeOf ) const
{
    METHODNAME_DEF( RecordTypeFactory, createTransformer );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    return create( typeOf );
}

RecordTypeBasePtr RecordTypeFactory::create( const IRecordTypeOfPtr typeOf ) const
{
    METHODNAME_DEF( RecordTypeFactory, create );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    if( typeOf->isTypeOf_DealerVolumeTotal() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeDealerVolumeTotal() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_DealerVolumeElectronic() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeDealerVolumeElectronic() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_DealerVolumeExclusiveTotal() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeDealerVolumeExclusiveTotal() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_DealerVolumeExclusiveElectronic() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeDealerVolumeExclusiveElectronic() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_TransferQuarantine() )
    {
        processing::RecordTypeTransferQuarantinePtr recordType = processing::RecordTypeTransferQuarantinePtr( new processing::RecordTypeTransferQuarantine() );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_ChangeIBTStockLevel() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeChangeIBTStockLevel() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_ChangeQuarantine() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeChangeQuarantine() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_ExpiryDate() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeExpiryDate() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_ChangeArticleDetails() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeChangeArticleDetails() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_ChangeOrderItem() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeChangeOrderItem() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_StopSellingOfArticle() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeStopSellingOfArticle() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_ArticleInfoGoodsIn() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeArticleInfoGoodsIn() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_CreditLimit() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeCreditLimit() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_CreditLimitChain() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeCreditLimitChain() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_CreditLimitGroup() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeCreditLimitGroup() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_CreditLimitCustomer() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeCreditLimitCustomer() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_CreditLimitCustomerReturn() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeCreditLimitCustomerReturn() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_CodeBlocage() )
    {
        processing::RecordTypeCodeBlocagePtr recordType = processing::RecordTypeCodeBlocagePtr( new processing::RecordTypeCodeBlocage() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        return recordType;
    }
    else if( typeOf->isTypeOf_Batch() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new domMod::pharmosTransaction::processing::RecordTypeBatch() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_GoodsIn() )
    {
        processing::RecordTypeGoodsInPtr recordType = processing::RecordTypeGoodsInPtr( new processing::RecordTypeGoodsIn() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        return recordType;
    }
    else if( typeOf->isTypeOf_DiscountAccount() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeDiscountAccount() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_ImportInvoiceNo() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeImportInvoiceNo() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_CustomerReturn() )
    {
        processing::RecordTypeCustomerReturnPtr recordType = processing::RecordTypeCustomerReturnPtr( new processing::RecordTypeCustomerReturn() );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_TenderChangeCustomerReturn() )
    {
        processing::RecordTypeTenderChangeCustomerReturnPtr recordType = processing::RecordTypeTenderChangeCustomerReturnPtr( new processing::RecordTypeTenderChangeCustomerReturn() );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_PickingLack() )
    {
        processing::RecordTypePickingLackPtr recordType = processing::RecordTypePickingLackPtr( new processing::RecordTypePickingLack() );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_InvoiceCancellation() )
    {
        processing::RecordTypeInvoiceCancellationPtr recordType = processing::RecordTypeInvoiceCancellationPtr( new processing::RecordTypeInvoiceCancellation() );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_StorageReconciliation() )
    {
        processing::RecordTypeOtherPtr recordType = processing::RecordTypeOtherPtr( new processing::RecordTypeOther() );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_BatchInconsistency() )
    {
        processing::RecordTypeOtherPtr recordType = processing::RecordTypeOtherPtr( new processing::RecordTypeOther() );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_PerpetualStocktaking() )
    {
        processing::RecordTypeOtherPtr recordType = processing::RecordTypeOtherPtr( new processing::RecordTypeOther() );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_StorageReconciliationPrewholesale() )
    {
        processing::RecordTypeOtherPtr recordType = processing::RecordTypeOtherPtr( new processing::RecordTypeOther() );
        recordType->injectRecordProcessHelper( m_RecordProcessHelperPtr );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_IBTGoods() )
    {
        processing::RecordTypeIBTGoodsPtr recordType = processing::RecordTypeIBTGoodsPtr( new processing::RecordTypeIBTGoods() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else if( typeOf->isTypeOf_ChangeArticleMasterData() )
    {
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeChangeArticleMasterData() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
    else
    {
        // no processing for unknown recordtypes
        RecordTypeBasePtr recordType = RecordTypeBasePtr( new processing::RecordTypeNoProcessing() );
        recordType->injectCSC_Logger( m_CSC_Logger );
        return recordType;
    }
}

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

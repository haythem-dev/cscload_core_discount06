//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeChangeArticleDetails
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypechangearticledetails.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include <convhelper.h>

#include <icsc_logger.h>

#include "pxartbaseptr.h"
#include "pxartpriceptr.h"
#include "pxartoldpriceptr.h"
#include "pvhx01_includes.h"


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

    struct null_deleter
    {
        void operator()(void const *) const
        {
        }
    };


RecordTypeChangeArticleDetails::RecordTypeChangeArticleDetails()
{
}

RecordTypeChangeArticleDetails::~RecordTypeChangeArticleDetails()
{
}

void RecordTypeChangeArticleDetails::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBookingType( source->getKbvzBukz() );
		target->setCostPrice( source->getKbvzGEP() );
		target->setPharmacySellPrice( source->getKbvzAVP() );
		target->setPharmacyPurchasePrice( source->getKbvzAEP() );
		target->setQuantity( source->getKbvzMeng() );
		target->setStationNo( source->getKbvzStat() );
		target->setStorageArea( source->getKbvzLgnr() );
		target->setStorageLocation( source->getKbvzLgfnr() );
        
		//it should convert from MMYY (it's what the orig code does, see pv1serv.cpp lines 549 ff - trick is the nDate cast, see constructor of nDate  )
		basar::Date expdate;
		if( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_MINDATE == source->getKbvzVerf() )
		{
			expdate = core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_MINDATE;
		}
		else if( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_MAXDATE == source->getKbvzVerf() )
		{
			expdate = core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_MAXDATE;
		}
		else
		{
			expdate = libcsc_utils::ConvHelper::getDateFor4DigitsDateMMYY( source->getKbvzVerf() );
		}
		target->setExpiryDate( expdate );

		target->setExpiryDateChangeFlag( core::IFX_NO );
		if( core::PHARMOS_YES == source->getKbvzKVerf() )
		{
			target->setExpiryDateChangeFlag( core::IFX_YES );
		}	
		
		target->setStorageLocationChangeFlag( core::IFX_NO );
		if( core::PHARMOS_YES == source->getKbvzKLgfnr() )
		{
			target->setStorageLocationChangeFlag( core::IFX_YES );	
		}
		
		//old: SKDGEP
		target->setCostPriceChangeFlag( core::IFX_NO );
		if( core::PHARMOS_YES == source->getKbvzKGEP() )
		{
			target->setCostPriceChangeFlag( core::IFX_YES );
		}

		//old: SKDAEP
		target->setPharmacyPurchasePriceChangeFlag( core::IFX_NO );
		if( core::PHARMOS_YES == source->getKbvzKAEP() )
		{
			target->setPharmacyPurchasePriceChangeFlag( core::IFX_YES );
		}

		//old: SKDAVP
		target->setPharmacySellPriceChangeFlag( core::IFX_NO );
		if( core::PHARMOS_YES == source->getKbvzKAVP() )
		{
			target->setPharmacySellPriceChangeFlag( core::IFX_YES );
		}
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeChangeArticleDetails::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeChangeArticleDetails::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeChangeArticleDetails::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeChangeArticleDetails, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	
	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );
        
        pxArtBasePtr artBase = pxArtBasePtr(pxArtBase::CreateArticle( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(), cDBGET_FORUPDATE) );

		if ( artBase->IsGoodState() )	
		{
			if( record->getExpiryDateChangeFlag() )	
			{
				pxArtStoreLoc artStoreLoc( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(),  artBase->LagerBereichNr(), artBase->LagerFachNr(), cDBGET_FORUPDATE);

				if (artStoreLoc.IsGoodState())
				{
					if( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_MINDATE == record->getExpiryDate() )
					{
						artStoreLoc.DatumVerfall( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_MINDATE ); 
					}
					else if( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_MAXDATE == record->getExpiryDate() )
					{
						artStoreLoc.DatumVerfall( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_MAXDATE ); 
					}
					else if( !record->getExpiryDate().isValid() )
					{
						artStoreLoc.DatumVerfall( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_DATE ); 
					}
					else
					{
						artStoreLoc.DatumVerfall( libcsc_utils::ConvHelper::get4DigitsDateYYMMFromDate(record->getExpiryDate()) ); 
					}

					//store only months and year, also invalid dates map to 0, see pv1serv.cpp lines 549 ff.
					/*
                    if ( !record->getExpiryDate().isValid())
                    {
                        artStoreLoc.DatumVerfall( core::PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_DATE ); 
                    }
                    else
                    {
                        artStoreLoc.DatumVerfall( libcsc_utils::ConvHelper::get4DigitsDateYYMMFromDate(record->getExpiryDate()) ); 
                    }
					*/
                    
					artStoreLoc.Put();

					if ( !artStoreLoc.IsGoodState() )
					{
						//todo: logging
						m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text save artStoreLoc failed", record );
					}
				}
			}

			if ( record->getStorageLocationChangeFlag() )
			{
				pxArtStoreLoc artStoreLocOld( m_PXVBSession->get(), record->getArticleNo(), record->getBranchNo(),  artBase->LagerBereichNr(), artBase->LagerFachNr(), cDBGET_FORUPDATE);

				artBase->SetLagerBereichNr(static_cast<basar::Int16>(record->getStorageArea().stoi()));
				artBase->SetLagerFachNr(record->getStorageLocation().c_str());
				artBase->SetStationNr(record->getStationNo().c_str());

				if (artStoreLocOld.IsGoodState() )
				{
					pxArtStoreLoc artStoreLocNew(artStoreLocOld);

					artStoreLocOld.Delete();

					if (!artStoreLocOld.IsGoodState())
					{
						//todo: logging
						m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text deletion artStoreLocOld failed", record );
					}
					
					artStoreLocNew.LagerBereichNr( static_cast<basar::Int16>(record->getStorageArea().stoi()) );
					artStoreLocNew.LagerFachNr( record->getStorageLocation().c_str() );
					artStoreLocNew.StationNr( record->getStationNo().c_str() );
					artStoreLocNew.Put();
					if ( !artStoreLocNew.IsGoodState() )
					{
						//todo: logging
						m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text save artStoreLocNew failed", record );
					}

				}
				artBase->Put();
			}

            //French Price Changement

            if (m_PXVBSession->get()->isFrance())
            {
                if (record->getCostPriceChangeFlag() && record->getPharmacyPurchasePriceChangeFlag() && record->getPharmacySellPriceChangeFlag())
                {
                    pxArtOldPriceList oldPriceList(m_PXVBSession->get());
                    pxArtPriceList priceList(m_PXVBSession->get());
                    priceList.Select(artBase->ArtikelNr());
                    priceList.DeleteExpired(); //remove expired prices, only one entry should remain

                    //todo: shared_ptr
                    pxArtPricePtr price = pxArtPricePtr(static_cast<pxArtPrice* >(priceList.RemoveAt(0)));

                    if (!price->IsGoodState())
                    {
                        //todo: logging
                        m_PXVBDBConnection->rollbackTransaction();
                        m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - price not in good state", record );
                        return;
                    }
                    
                    if (price->Get(cDBGET_READONLY) != 0)
                    {
                        //todo: loggins
                        m_PXVBDBConnection->rollbackTransaction();
                        m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - price get read only failed", record );
                        return;
                    }

                    oldPriceList.Select(artBase->FilialNr(), artBase->ArtikelNr());
                                        
                    pxArtOldPrice* oldPrice = NULL;

                    if (oldPriceList.Entries())
                    {
                        oldPrice = static_cast<pxArtOldPrice*>( oldPriceList.RemoveAt(0) );
                    }
                    
                    nMoney EKApo(record->getPharmacyPurchasePrice().toFloat64());
                    nMoney VKApo(record->getPharmacySellPrice().toFloat64());
                    nMoney VKGep(record->getCostPrice().toFloat64());

                    if ( EKApo == price->PreisEKApo()  && VKApo == price->PreisVKApo())
                    {
                        if ( 0 != oldPrice )
                        {
                            oldPrice->Delete();
                        }
                    }
                    else
                    {
                        if (0 == oldPrice)
                        {
                            oldPrice = new pxArtOldPrice( m_PXVBSession->get(), artBase->FilialNr(), artBase->ArtikelNr() );
                        }

                        oldPrice->PreisEKApo(record->getPharmacyPurchasePrice().toFloat64());
                        oldPrice->PreisVKApo(record->getPharmacySellPrice().toFloat64());
                        oldPrice->PreisEKGrosso(record->getCostPrice().toFloat64());
                        oldPrice->PreisEKGrossoNA(price->PreisEKGrossoNA());
                        oldPrice->Put();
                        if ( !oldPrice->IsGoodState() )
                        {
                            //todo: logging
                            m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - oldPrice put failed", record );
							delete oldPrice;
							oldPrice = NULL;
                        }
                        else
                        {
                            oldPriceList.Append(oldPrice);
                        }

                    }

                    //cleanup?                    
                    //price.reset();
                }
            }

            if (record->getCostPriceChangeFlag() || record->getPharmacyPurchasePriceChangeFlag() || record->getPharmacySellPriceChangeFlag())
            {
                pxArtPriceList priceList(m_PXVBSession->get());
                priceList.Select(artBase->ArtikelNr());
                priceList.DeleteExpired(); //remove expired prices, only one entry should remain

                //todo: shared_ptr
                pxArtPricePtr price = pxArtPricePtr(static_cast<pxArtPrice* >(priceList.RemoveAt(0)));

                if (!price->IsGoodState())
                {
                    //todo: logging
                    m_PXVBDBConnection->rollbackTransaction();
                    return;
                }                
                if (price->Get(cDBGET_FORUPDATE) != 0)
                {
                    //logging
                    m_PXVBDBConnection->rollbackTransaction();
                    return;
                }

                if (record->getPharmacyPurchasePriceChangeFlag())
                {
                    price->PreisEKApo(record->getPharmacyPurchasePrice().toFloat64());
                }
                if (record->getPharmacySellPriceChangeFlag())
                {
                    price->PreisVKApo(record->getPharmacySellPrice().toFloat64());
                }
                if (record->getCostPriceChangeFlag())
                {
                    price->PreisEKGrosso(record->getCostPrice().toFloat64());
                }

                price->Put();

                if (!price->IsGoodState())
                {
                    //logging
                    m_PXVBDBConnection->rollbackTransaction();
                    m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - price put failed", record );
                    return;
                }

                //price.reset();
            }

			if ( !artBase->IsGoodState() )
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - artBase not in good state", record );
			}
			else
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );//mutli -> artBase + artStoreLocNew
                record->markAsProcessed();
			}

		}
        else
        {
            m_PXVBDBConnection->rollbackTransaction();
        }
	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeChangeArticleDetails::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeChangeArticleDetails::process...-text generic exception", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

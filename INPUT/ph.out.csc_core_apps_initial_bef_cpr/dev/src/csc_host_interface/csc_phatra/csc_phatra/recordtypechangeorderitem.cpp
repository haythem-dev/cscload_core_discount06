//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeChangeOrderItem
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypechangeorderitem.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

#include <icsc_logger.h>
#include <pxordervalues.hpp>

#include "pvhx01_includes.h"
#include "pxartacc.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeChangeOrderItem::RecordTypeChangeOrderItem()
{
}

RecordTypeChangeOrderItem::~RecordTypeChangeOrderItem()
{
}

void RecordTypeChangeOrderItem::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
    try
    {
        target->setArticleNo( source->getKbvzPZN() );
        target->setBookingType( source->getKbvzBukz() );
        target->setQuantity( source->getKbvzMeng() );

        basar::VarString cscorderno = source->getKbvzLgfnr();
        target->setCSCOrderNo( cscorderno );

        target->setOrderPositionNo( source->getKbvzVerf() );
        target->setQuantityNatra( source->getKbvzWert().toInt32() );

        basar::VarString customerno = source->getKbvzET3().substr(0,7);
        target->setCustomerNo( customerno );
    }
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeChangeOrderItem::doTransform-text basar exception caught", ex, source);
    }
    catch( ... )
    {
        m_CSC_Logger->logGenericException("RecordTypeChangeOrderItem::doTransform...-text generic exception caught", source );
        //throw;
    }
}

void RecordTypeChangeOrderItem::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeChangeOrderItem, process );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    try
    {
        m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

        pxOrder order(m_PXVBSession->get(), record->getCSCOrderNo().stol(), cDBGET_FORUPDATE);

        if (order.IsGoodState())
        {
            order.OrderType(order.KdAuftragArt(), order.KoArt(), order.BuchArt());

            enum BookingTypeEnum st = order.StockTrans().StockTransactionCode();
            enum PickingTypeEnum ct = order.CommType().ShipCode();

            order.SaveOrderValuesDebtLimit();
            order.DeleteOrderValues();
            nMoney oldOrderValuesDebtLimit = order.SaveOrderValueDL();

            pxOrderItem item(order, record->getOrderPositionNo() );

            if (item.Get( cDBGET_FORUPDATE ))
            {
                m_PXVBDBConnection->rollbackTransaction();
                m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - item entry not found", record );
                return;
            }

            basar::BLong positionDifference = 0;
            basar::BLong savePositionDifference = 0;

            if ( record->getBookingType() == ACCOUNT_SET_QUANTITY)
            {
                positionDifference = item.MengeGeliefert() - (basar::BLong)record->getQuantity();
                savePositionDifference = positionDifference;

                if (item.MengeBestaetigt() == 0 && item.MengeNatra() > 0)
                {
                    positionDifference = 0;
                }
                item.MengeGeliefert(record->getQuantity());
                item.MengeBestaetigt(record->getQuantity() - record->getQuantityNatra());
                item.MengeAbgebucht(record->getQuantity());
                item.MengeNatra(record->getQuantityNatra() );
                item.SendeStatus(pxOrderItem::cVSECoCorrection);

                order.SendeStatus(pxOrder::cVSECoCorrection);

                if (positionDifference > 0)
                {
                    pxArtAccount acct(m_PXVBSession->get(), TRANSACTIONTYPE_PICKING_CORRECTION);
                    acct.FilialNr(order.FilialNr());
                    acct.ArtikelNr(item.ArtikelNr());
                    acct.Menge(-1 * positionDifference);
                    acct.TransActionKey(st, ct);
                    acct.IDFNr(order.IDFNr());
                    acct.BelegNr(order.KdAuftragNr());
                    acct.PosNr(item.PosNr());
                    acct.Uid(0);
                    acct.Put();

                    //since we use a local object, we don't need to delete
                    //but we will check IsGoodState for logging purpuses
                    if (!acct.IsGoodState())
                    {
                        m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text pxArtAccount put failed", record );
                    }
                }

            }

            if (item.IsGoodState())
            {
                order.VSEPut();
                if ( positionDifference > 0 )
                {
                    pxOrderValues orderValues( m_PXVBSession->get(), record->getCSCOrderNo().stol() );
                    if ( orderValues.Get(cDBGET_FORUPDATE ) )          // entry not found
                    {
                        m_PXVBDBConnection->rollbackTransaction();
                        m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text no order values entry found", record );
                        return;
                    }
                    orderValues.ReduceOrderValues(&item, positionDifference);
                    orderValues.Put();
                    if (orderValues.IsGoodState())
                    {
                        m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
                    }
                    else
                    {
                        m_PXVBDBConnection->rollbackTransaction();
                        m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - order values put failed", record );
                        return;
                    }
                }

                m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

                //read order again
                pxOrder readonly_order(m_PXVBSession->get(), record->getCSCOrderNo().stol(), cDBGET_READONLY);

                if (!readonly_order.IsGoodState())
                {
                    m_PXVBDBConnection->rollbackTransaction();
                    m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - 2nd order read is not good state", record );
                    return;
                }


                readonly_order.OrderType(readonly_order.KdAuftragArt(), readonly_order.KoArt(), readonly_order.BuchArt());
                readonly_order.SaveOrderValuesDebtLimit();

                nMoney newOrderValuesDebtLimit = readonly_order.SaveOrderValueDL();

                item.UndoCreditDayTurnOver(oldOrderValuesDebtLimit, newOrderValuesDebtLimit);
                item.ReleasePromoQuota(positionDifference);

                pxOrderPosChange orderPosChange( m_PXVBSession->get(), record->getCSCOrderNo().stol(), record->getOrderPositionNo() );
                orderPosChange.Get(cDBGET_FORUPDATE );
                orderPosChange.SetMengeBestellt(item.MengeBestellt());
                orderPosChange.SetMengeBestaetigt(item.MengeBestaetigt());
                orderPosChange.SetMengeAlt(item.MengeBestaetigt() + savePositionDifference);
                orderPosChange.SetSWChecked('0');
                orderPosChange.Put();

                if (orderPosChange.IsGoodState())
                {
                    m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
                    record->markAsProcessed();
                }
                else
                {
                    m_PXVBDBConnection->rollbackTransaction();
                    m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - 2nd order read put failed", record );
                }
            }
        }
        else
        {
            m_PXVBDBConnection->rollbackTransaction();
            m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - order not in good state", record );
        }
    }
    catch( basar::Exception& ex )
    {
        // TODO
        m_CSC_Logger->logBasarException("RecordTypeChangeOrderItem::process-text basar exception caught", ex, record );
        //throw;
    }
    catch( ... )
    {
        // TODO
        m_CSC_Logger->logGenericException("RecordTypeChangeOrderItem::process...-text generic exception caught", record );
        //throw;
    }
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

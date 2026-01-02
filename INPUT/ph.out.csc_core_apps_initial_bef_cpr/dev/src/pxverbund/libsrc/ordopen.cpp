#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstbtm.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordevt.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxordvtr.hpp"
#include "pxcstot.hpp"
#include "pxholiday.hpp"
#include "pxordtaxvalues.hpp"
#include "pxorderperiod.hpp"
#include "tourmanager.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

#include <liblockmanager/lockguard/ilockguard.h>
#include <liblockmanager/exceptions/alreadylockedexception.h>

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
/*  Open order processing.                                                    */
/*----------------------------------------------------------------------------*/
int
pxOrder :: OpenOrder
(
    DBAccessMode mode,                  // open mode
    pxCustBase   *cp                    // ptr to customer object or NULL
)
{
    ClearError();
    MessageCodeEnum logid = CMSG_LOG_ORDVIEW; // default log msg id
    short DelayedDays = Param()->DelayedDays();
    if ( ItemList_ )                    // then order item processing already open
        return ExternalError(CMsgStream(), CMSG_ORD_STILLOPEN, KdAuftragNr_);
    if ( (cp != NULL) && (cp->IDFNr() == IDFNr_) )
    {
        Customer_ = cp;                 // link with existing customer object
        SetNoCustDestruct();            // avoid its deletion during destruction
    }
    if ( !Customer() )                  // ensure a valid customer is linked
       return ExternalError(CMsgStream(), CMSG_ORD_NOCUSTOMER, KdAuftragNr_);

    // Test desired order processing type:
    switch (mode)
    {
        case cDBOPEN_READONLY:
            break;

        case cDBOPEN_UPDATE:
            if ( IsCancelled() || IsProtected() )
                return ExternalError(CMsgStream(), CMSG_ORD_PROTECTED, KdAuftragNr_);

            if ( !IsEntryClosed() )       // order entry not closed
                return ExternalError(CMsgStream(), CMSG_ORD_ENTRY_NOTCLOSED, KdAuftragNr_);
            SetUpdateInProgress();
            logid = CMSG_LOG_ORDUPDATE;
            break;

        case cDBOPEN_INSERT:
            if ( Customer()->Flags().IsKundeGesperrt() )
                return ExternalError(CMsgStream(), CMSG_ORD_CUST_NO_ORDERENTRY, Customer()->IDFNr());

            // check restrictions for this Customer
            if ( Customer_->ManufacturerNo() > 0 )
            {
                if ( checkOrderEntryRestrictions( Customer_->ManufacturerNo() ) )
                {
                    return  ExternalError(CMsgStream(), CMSG_ORD_OPENRESTRICTED, Customer_->IDFNr() );
                }
            }

            if ( !(KdAuftragNr_ > 0) )
                SetNewOrder();
            else
            {
                if( m_LockGuard.get() == NULL )
                {
                    m_LockGuard = Session()->createCustomerOrderLockGuard( "pxOrder", KdAuftragNr_ );
                }
                try
                {
                    m_LockGuard->lock();
                }
                catch( libLockManager::exceptions::AlreadyLockedException& alex )
                {
                    m_LockGuard.reset();
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), alex.what());
                    return ExternalError(CMsgStream(), CMSG_ORD_LOCKED, KdAuftragNr_);
                }
                catch( basar::cmnutil::BasarException& bex )
                {
                    m_LockGuard.reset();
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), bex.what());
                    return ExternalError(CMsgStream(), CMSG_ORD_LOCKED, KdAuftragNr_);
                }
                catch( std::exception& sex )
                {
                    m_LockGuard.reset();
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), sex.what());
                    return ExternalError(CMsgStream(), CMSG_ORD_LOCKED, KdAuftragNr_);
                }
                catch( ... )
                {
                    m_LockGuard.reset();
                    BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), "Error in LockGuard->lock()");
                    return ExternalError(CMsgStream(), CMSG_ORD_LOCKED, KdAuftragNr_);
                }

                nDBBeginTransaction(cDBTransSet);
                Get(cDBGET_FORUPDATE);
                if ( IsCancelled() || IsProtected() || IsEntryClosed()
                    || IsShipmentInProgress()
                    || IsShipmentClosed()
                    || IsInvoiceable()
                    || IsInvoiced() )
                {
                    ExternalError(CMsgStream(), CMSG_ORD_PROTECTED, KdAuftragNr_);
                    m_LockGuard.reset();
                    nDBRollBack();
                    return ErrorState();
                }
            }
            ClearEntryClosed();           // Swap states to
            ClearEntryDeferred();         // continue with
            SetEntryInProgress();         // order entry processing
            logid = CMSG_LOG_ORDENTRY;
            FirstTransPos_ = AnzPos_;     // first position within transmission
            break;

        default:
            return ExternalError(CMsgStream(), CMSG_ORD_INVALID_OPEN, KdAuftragNr_, (int) mode);
    }

/*----------------------------------------------------------------------------*/
/*  Write order object into database.                                         */
/*----------------------------------------------------------------------------*/
    if ( IsNewOrder() && KdAuftragArt_.IsEmpty() )
    {                                   // then no order type has been assigned yet
        pxOrderValidTrans *vtp =        // so we try to assign a default
        Session()->OrderValidTransList(Customer()->Vertriebszentrum())->Find(*Customer(), KdAuftragArt_);
        if ( vtp )                      // then valid order transaction ptr there
        {                               // copy order type values
            KdAuftragArt_ = vtp->KdAuftragArt();
            KoArt_        = vtp->KoArt();
            BuchArt_      = vtp->BuchArt();
        }
    }
                                        // reference order type:
    OrderType(KdAuftragArt_, KoArt_, BuchArt_ );
    // Start INC-044238
    if ( !(IsGoodState()) )
    {
        nDBRollBack();
        m_LockGuard.reset(); // delete ptr - destructor deletes lock automatically from DB

        return ErrorState();
    }
    // End INC-044238

    if ( ! IsOrderViewing() && IsGoodState())
    {                                   // Log who is doing this:

        GeraetName_ = Session()->Device()->Name();
        GeraetName_.Strip();
        // Krücke
        if ( IsNewOrder() )
        {
            if ( (GeraetName_ == "XML" ||  GeraetName_ == "KSCTEST" ) && (Session()->isBulgaria() || Session()->isSwitzerland() || Session()->isAustria())  )
            {
                SetAuftragVomXML();
            }
        }
        if ( Session()->PersonnelNo() != 0 )
        {
            if (Session()->isBulgaria())
            {
                if ( IsNewOrder() )                   // and is new order
                {
                PersonalNr_    = Session()->PersonnelNo();
                }
            }
            else
            {
                PersonalNr_    = Session()->PersonnelNo();
            }
        }
        // For an existing order, we read the creation event from the event log
        DateTimeCreated();
        nDBBeginTransaction(cDBTransSet);
        Lock();                          // Lock current order
        if ( IsGoodState() )             // ensure all was successful
        {
            pxOrderEvent event(*this);    // construct order event
            event.Put();                  // write it into the data base
            if ( DateTimeCreated_ == time_t(0L) ) // then its a new order
            {
                DateTimeCreated_ = event.DateTime();
                WriteOrderCreationEvent();
            }
            nDBCommit(cDBTransSet);
        }
        else
            nDBRollBack();                // else rollback updates
    }

    if ( IsGoodState() )                 // avoid destroying the current error state
    {                                    // This will mark the order as opened:
        ItemList();                      // construct order item list
        AnzPos_ = static_cast<long>(ItemList()->Entries()); // in the case of an error before orderentry
        OrdTaxValues();                  // order tax values
        OrdTaxValues()->ReCalcOrderValues(this);  // recal order tax values
        ReCalcValuesCollectList();
        OrderValues();                   // special Bulgarien appl. (KDAUFTRAGWERTE)
        OrderCalcMode();                 // special Bulgarien appl. (KDAUFTRAGRECHART)
        OrderDiscAcc();                  // special Bulgarien appl. (KDAUFTRAGDISCACC)
        injectPreisTypSavedForAllItemsInItemlist(); // special Bulgarion appl. (SR-16039137)
        Customer()->DiscountGrpMemListFive();  // special Bulgarien appl. Liste 5
        //UndoCreditDayTurnOver();         // special Bulgarian appl.
        if ( ! IsOrderViewing() && IsGoodState() && !IsProblemClearance() )
        {
            CancelDebtLimitSumDayTurnOver();   // special for the Crema application
        }
        LogEvent(CMsgStream(), logid, KdAuftragNr_, IDFNr_);
        if ( IsNewOrder() )                 // do some initial things for a
        {                                   // new order
            pxCustBusinessTimes& btime = Customer()->BusyTime();
            Customer()->DeleteRouteList();
            ZeitEndeAM_ = btime.EndAM();  // copy customer's business times
            ZeitEndePM_ = btime.EndPM();
            if (Session()->isBulgaria())
            {
                SetPaymentType('0');          // Paymenttype = 0
            }

            if (!(CommType().IsNoShipment()) && !(Session()->Device()->IsFILE()) )
            {
                RouteAssign();                // assign a default route
                if ( !IsGoodState() )
                {
                    if ( !(Session()->Device()->IsVideo()) )
                    {
                        ClearError();
                    }
                }
            }
            if ( !(CommType().IsNoShipment()) )
            {
                if ( DelayedDays > 0 )  // Ivrylab
                {

                    const pxCustOrderType& ot = OrderType();
                    if ( !(ot.IsCollectiveOrder()) )
                    {
                        if ( DatumAuslieferung_ == pxConstants::NullDate )
                        {
                            pxHoliDayList* holidaylist = Session()->HoliDayList(Customer_->Vertriebszentrum());
                            nDate now;
                            DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(((now+DelayedDays) -1),Customer_->Vertriebszentrum())) );
                        }
                    }
                }
            }

        }
        if (Session()->isBulgaria())
        {
            if ( Session()->Device()->IsVideo() )
            {
                if ( mode != cDBOPEN_READONLY )
                {
                    Session()->SetCurrentOrder(this);
                }
            }
        }

        if(!IsOrderViewing()) verifyCurrentTourAssignment(); // if the current order has a tour from the past, the current tour has to be assigned

        if(Param()->IsSCrema() && WasOrderReleased())
        {
            SetNoDebtLimitCheck();
        }
        if (false == IsNewOrder())
        {
            getIbtRequestHandler().readAllIbtRequests(this); // construct list of auxiliary remote headers, if necessary
        }
    }
    return ErrorState();
}

int
pxOrder :: Lock()
{
    Put();                              // ReadLock write

    // Ensure success so far, then protect this order against concurrent access
    if ( IsGoodState() )
    {
        if ( IsNewOrder() )
        {
            if ( m_LockGuard.get() == NULL )
            {
                m_LockGuard = Session()->createCustomerOrderLockGuard( "pxOrder", KdAuftragNr_ );
            }
            try
            {
                m_LockGuard->lock();
            }
            catch( libLockManager::exceptions::AlreadyLockedException& alex)
            {
                m_LockGuard.reset();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), alex.what());
                return ExternalError(CMsgStream(), CMSG_ORD_LOCKED, KdAuftragNr_);
            }
            catch( basar::cmnutil::BasarException& bex )
            {
                m_LockGuard.reset();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), bex.what());
                return ExternalError(CMsgStream(), CMSG_ORD_LOCKED, KdAuftragNr_);
            }
            catch( std::exception& sex )
            {
                m_LockGuard.reset();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), sex.what());
                return ExternalError(CMsgStream(), CMSG_ORD_LOCKED, KdAuftragNr_);
            }
            catch( ... )
            {
                m_LockGuard.reset();
                BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), "Error in LockGuard->lock()");
                return ExternalError(CMsgStream(), CMSG_ORD_LOCKED, KdAuftragNr_);
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Open order Info                                                           */
/*----------------------------------------------------------------------------*/
int
pxOrder :: OpenInfo
(
)
{
    OpenInfoCommon();

    if ( IsGoodState() )                // avoid destroying the current error state
    {                                   // This will mark the order as opened:
        SetPseudoLock();                // simulate lockmanager
        pxGlobalNoDatabaseWrite = true; // do not
        ItemList();                     // construct order item list
        OrderValues();                  // special Bulgarien appl. (KDAUFTRAGWERTE)
        if ( IsNewOrder() )             // do some initial things for a
        {                               // new order
            pxCustBusinessTimes& btime = Customer()->BusyTime();
            ZeitEndeAM_ = btime.EndAM(); // copy customer's business times
            ZeitEndePM_ = btime.EndPM();
        }
        RouteAssign();                  // assign a default route
        ClearError();
    }                                   // if necessary
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Open order Info                                                           */
/*----------------------------------------------------------------------------*/
int
pxOrder :: OpenProforma
(
)
{
    OpenInfoCommon();

    if ( IsGoodState() )                // avoid destroying the current error state
    {                                   // This will mark the order as opened:
        SetPseudoLock();                // simulate lockmanager
        SetNewOrder();                  // simulate neworder
        // Krücke
        if ( GeraetName_ == "XML" ||  GeraetName_ == "KSCTEST" )
        {
            SetAuftragVomXML();
        }
        pxGlobalNoDatabaseWrite = true; // do not
        ItemList();                     // construct order item list
        OrderCalcMode();                // special Bulgarien appl. (KDAUFTRAGRECHART)
        if ( IsNewOrder() )             // do some initial things for a
        {                               // new order
            pxCustBusinessTimes& btime = Customer()->BusyTime();
            ZeitEndeAM_ = btime.EndAM(); // copy customer's business times
            ZeitEndePM_ = btime.EndPM();
        }
    }                                   // if necessary
    return ErrorState();
}

void pxOrder::OpenInfoCommon()
{
    ClearError();

    if ( ItemList_ )                    // then order item processing already open
    {
        ExternalError(CMsgStream(), CMSG_ORD_STILLOPEN, KdAuftragNr_);
        return;
    }
    if ( !Customer() )                  // ensure a valid customer is linked
    {
        ExternalError(CMsgStream(), CMSG_ORD_NOCUSTOMER, KdAuftragNr_);
        return;
    }

    ClearEntryClosed();           // Swap states to
    ClearEntryDeferred();         // continue with
    SetEntryInProgress();         // order entry processing

    KdAuftragArt_ = "NO";
    KoArt_        = '0';
    BuchArt_      = '0';
    OrderType(KdAuftragArt_, KoArt_, BuchArt_);
    if ( !IsGoodState() )
    {
        ClearError();
        KdAuftragArt_.Clear();
        pxOrderValidTrans *vtp =         // so we try to assign a default
        Session()->OrderValidTransList(Customer()->Vertriebszentrum())->Find(*Customer(), KdAuftragArt_);
        if ( vtp )                       // then valid order transaction ptr there
        {                                // copy order type values
            KdAuftragArt_ = vtp->KdAuftragArt();
            KoArt_        = vtp->KoArt();
            BuchArt_      = vtp->BuchArt();
        }
        OrderType(KdAuftragArt_, KoArt_, BuchArt_);
        if ( !IsGoodState() )
        {
            return;
        }
    }
    GeraetName_ = Session()->Device()->Name();
    GeraetName_.Strip();
    PersonalNr_ = Session()->PersonnelNo();
}

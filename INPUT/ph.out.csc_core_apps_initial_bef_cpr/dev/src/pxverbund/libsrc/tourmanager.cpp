/***************************************************************************************************************************/
#include "tourmanager.hpp"
#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxoeparm.hpp"
#include "pxcomtyp.hpp"
#include "pxcstbas.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxholiday.hpp"
#include "pxordvtr.hpp"
#include "pxorder.hpp"
#include "tourutil.hpp"
#include "csccustomer.hpp"
#include "customertourlist.hpp"
#include "customertour.hpp"
#include "ibtbrancheslist.hpp"
#include "ibtbranches.hpp"
#include "customerbusinesshourslist.hpp"
#include "customerbusinesshours.hpp"
#include "types/messagecodeenum.inc"
#include "pxartflg.hpp"
#include "pxorderitemtour.hpp"
#include "pxparameter.hpp"
#include "pxcustomerspecials.hpp"
#include "pxbranch.hpp"
#include "pxorderperiod.hpp"
#include "emergencyservice.h"
#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <ibt/transportexclusionchecker/itransportexclusionchecker.h>

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/***************************************************************************************************************************/
/* static */ TourInfo TourManager::determineReturnsTour(pxSession* session, const short branchno, const long customerno)
{
    pxCommType* pickingtype = new pxCommType(session, '0', branchno);
    TourManager tourman(session, 0, branchno, customerno, pickingtype);
    tourman.injectReturnsTourSearch(true);
    tourman.injectDeliveryDate(TourUtil::getTomorrowsDate());
    TourInfo retval = tourman.determineTour();

    // If there is no returns tour, search for the next available tour starting from tomorrow....
    if (!retval.getTourFound())
    {
        TourManager tourman1(session, 0, branchno, customerno, pickingtype);
        tourman1.injectDeliveryDate(TourUtil::getTomorrowsDate());
        retval = tourman1.determineTour();
    }

    if (NULL != pickingtype) delete pickingtype;

    return retval;
}

/***************************************************************************************************************************/
/* static */ TourInfo TourManager::getNextCustomerTourOccurrance(pxSession* session, const short branchno, const long customerno, const nString& tourid)
{
       pxCommType* pickingtype = new pxCommType( session, '0', branchno );

       TourManager tourman( session, 0, branchno, customerno, pickingtype );
       tourman.injectDesiredTourId(tourid);
       TourInfo retval = tourman.determineTour();

       if( NULL != pickingtype ) delete pickingtype;

       return retval;
}


/***************************************************************************************************************************/
/* static */ TourInfo TourManager::getCustomerTourForArticle(pxSession* session, const short branchno, const long customerno, const long articleno /*= 0*/)
{
    pxCommType* pickingtype = new pxCommType( session, '0', branchno );
    pxArtBase* article = NULL;

    TourManager tourman( session, 0, branchno, customerno, pickingtype );
    if( articleno > 0 )
    {
        article = pxArtBase::CreateArticle(session, articleno, branchno);
        tourman.injectArticle( article );
    }
    TourInfo retval = tourman.determineTour();

    if( NULL != pickingtype ) delete pickingtype;
    if( NULL != article ) delete article;

    return retval;
}

/***************************************************************************************************************************/
TourInfo TourManager::determineTour()
{
    resetError();

    std::stringstream s;
    s << "TM:determineTour ARGS(" << serializeArgs() << ") ";
    TourUtil::writeLogINFO( s, true );

    // check if the shuttle customer has to be used
    checkShuttleCustomer();

    loadTours();
    m_TourInfo.init();

    checkDesiredTourExistence();

    // set flag for IBTShuttle-Tour determination
    m_CustomerToursCurrent->setIBTShuttleTourDetermination(m_ArgInIBTShuttleTourDetermination);
    m_CustomerToursCurrent->setIBTOrderImport(m_ArgIsOrderFromIBT);
    m_CustomerToursWeek->setIBTShuttleTourDetermination(m_ArgInIBTShuttleTourDetermination);
    m_CustomerToursWeek->setIBTOrderImport(m_ArgIsOrderFromIBT);

    // check for customer special routes for order type UW
    checkCustomerSpecialSettings();

    // delay delivery if necessary (holiday, delay days in parameter, ...)
    delayDelivery();

    // delay delivery for specific articles (narcotics, cool chain, ...)
    delayDeliveryForArticle();

    // check desired tour
    if( isTransportExclusionEnabled() )
    {
        checkDesiredTour();
    }

    // determine IBT tour
    if( this->m_ArgIBTBranchNo > 0 )
    {
        this->determineIBTTour();
    }
    else // determine local tour
    {
        // use order type specific tour if configured and tour is valid
        if( this->useOrderTypeSpecificTour() && this->m_ArgDesiredTourId.IsEmpty() )
        {
            s << "TM:determineTour RESULT(" << m_TourInfo.serialize() << ") OTSpecificTour! ";
            TourUtil::writeLogINFO( s, true );
            return m_TourInfo;
        }
        else
        {
            this->determineLocalTour();
        }
    }

    if( m_TourInfo.getTourFound() )
    {
        resetError();
    }
    else
    {
        s << "TM:WARNING determineTour !!!NO TOUR FOUND!!! RESULT(" << m_TourInfo.serialize() << ") ";
        TourUtil::writeLogINFO( s, true );
    }

    s << "TM:determineTour RESULT(" << m_TourInfo.serialize() << ") ";
    TourUtil::writeLogINFO( s, true );
    return m_TourInfo;
}

/***************************************************************************************************************************/
void TourManager::checkDesiredTour()
{
    std::stringstream s;
    s << "TM:checkDesiredTour ";

    if( "" != m_ArgDesiredTourId && !TourUtil::isNullOrCurrentDate( this->m_ArgDeliveryDate ) )
    {
        if( !this->m_CustomerToursWeek->isTourAvailableForWeekday( this->m_ArgDesiredTourId, this->m_ArgDeliveryDate.GetDayOfWeek() ) )
        {
            this->m_ArgDesiredTourId = "";
            s << "Removed DesiredTour! NotForWeekday! DDate:" << this->m_ArgDeliveryDate.GetYYYYMMDD() << " ";
            TourUtil::writeLogINFO( s );
            return;
        }
    }

    if( isTransportExclusionEnabled() )
    {
        if( TourUtil::isNullOrCurrentDate( this->m_ArgDeliveryDate ) )
        {
            if( !this->m_CustomerToursCurrent->isTourPossibleForArticle( this->m_ArgDesiredTourId, this->m_ArgArticle ) )
            {
                this->m_ArgDesiredTourId = "";
                s << "Removed DesiredTour (TPT)! NotForArticle! ArticleNo " << this->m_ArgArticle->ArtikelNr() << " DDate:" << this->m_ArgDeliveryDate.GetYYYYMMDD() << " ";
                TourUtil::writeLogINFO( s );
                return;
            }
            if( NULL != m_ArgArticle )
            {
                if( !isTourValid(this->m_ArgDesiredTourId, this->m_PickingType, m_ArgDeliveryDate) )
                {
                    this->m_ArgDesiredTourId = "";
                    s << "Removed DesiredTour (TPT)! NotValid! ArticleNo " << this->m_ArgArticle->ArtikelNr() << " DDate:" << this->m_ArgDeliveryDate.GetYYYYMMDD() << " ";
                    TourUtil::writeLogINFO( s );
                    return;
                }
            }
        }
        else
        {
            if( !this->m_CustomerToursWeek->isTourPossibleForArticle( this->m_ArgDesiredTourId, this->m_ArgArticle ) )
            {
                this->m_ArgDesiredTourId = "";
                s << "Removed DesiredTour (TPTW)! NotForArticle! ArticleNo " << this->m_ArgArticle->ArtikelNr() << " DDate:" << this->m_ArgDeliveryDate.GetYYYYMMDD() << " ";
                TourUtil::writeLogINFO( s );
                return;
            }
        }
    }
}

/***************************************************************************************************************************/
TourInfo TourManager::determineFollowingTour( TourInfo* currentTourInfo )
{
    this->resetArgInjections();

    std::stringstream s;
    s << "TM:determineFollowingTour TourID [" << currentTourInfo->getTourID() << "/" << currentTourInfo->getTourDate().GetYYYYMMDD() << "] ";
    TourUtil::writeLogINFO( s, true );

    nDate tourdate = currentTourInfo->getTourDate();
    long tourhours = TourUtil::getHoursFromTourId( currentTourInfo->getTourID() );
    long tourminutes = TourUtil::getMinutesFromTourId( currentTourInfo->getTourID() ) + 1;
    if( tourminutes > 59 ){ ++tourhours; }
    long tourtime = (tourhours * 100) + tourminutes;
    if( tourtime > 2359 )
    {
        tourtime = 0;
        tourdate = tourdate.add(1);
    }
    nDate currentTourDateTime = TourUtil::getDateTime( tourdate.GetYYYYMMDD(), tourtime );

    this->injectTimeOffset( currentTourDateTime );
    this->injectDeliveryDate( currentTourDateTime );
    this->m_ArgForceTimeOffsetUsage = true;
    determineTour();
    this->m_ArgForceTimeOffsetUsage = false;
    return m_TourInfo;
}

/***************************************************************************************************************************/
void TourManager::checkShuttleCustomer()
{
    if( !this->m_ArgIsOrderFromIBT ) return;
    if( !m_OrderEntryParam->IsSIbtCstOrg() ) return;
    if( this->m_ShuttleCustomerNo > 0 ) return;

    this->m_ShuttleCustomerNo = 0;
    pxCustBase customer( m_Session, this->m_BranchNo, this->m_CustomerNo );

    // customer not available
    if( !customer.IsGoodState() ) return;

    if( 0 == customer.OriginalFilialNr() )
    {
        pxBranch branch( m_Session, this->m_BranchNo );
        if( !branch.IsGoodState() ) return;
        this->m_ShuttleCustomerNo = branch.BGANr_EK();
    }
    else
    {
        pxBranch branch( m_Session, customer.OriginalFilialNr() );
        if( !branch.IsGoodState() ) return;
        this->m_ShuttleCustomerNo = branch.BGANr_EK();
    }

    if( this->m_ShuttleCustomerNo > 0 )
    {
        std::stringstream s;
        s << "TM:checkShuttleCustomer CustNo[" << this->m_ShuttleCustomerNo << "] ";
        TourUtil::writeLogINFO( s, true );
    }
}

/***************************************************************************************************************************/
void TourManager::checkCustomerSpecialSettings()
{
    if( m_ArgDesiredTourId.IsEmpty() && ( "UW" == m_OrderType ) )
    {
        std::stringstream s;
        s << "TM:checkCustomerSpecialSettings ";

        pxParameter* par = new pxParameter( m_Session, m_BranchNo, (nString)cPAR_KSCSERVER_GROUP,
            (nString)cPAR_KSCSERVER_PURPOSE_CUSTOMERSPECIALS, (nString)cPAR_KSCSERVER_PARAMNAME );
        if( !(par->Get(cDBGET_READONLY)) )
        {
            if( 1 == par->Wert() )
            {
                pxCustomerSpecialsList* csList = new pxCustomerSpecialsList( m_Session );
                csList->Select( m_BranchNo, m_CustomerNo );
                if( 0 == csList->Entries() )
                {
                    csList->SelectUWIDF( m_BranchNo, m_CustomerNo );
                }
                if( csList->Entries() > 0 )
                {
                    pxCustomerSpecials* csp = csList->FindActivDow( TourUtil::getCurrentWeekday() );
                    if( csp  )
                    {
                        if( csp->WeekDay() == TourUtil::getCurrentWeekday() )
                        {
                            if( !csp->UW_Tour().IsEmpty() )
                            {
                                if( this->isTourValid( csp->UW_Tour(), this->m_PickingType, this->m_ArgDeliveryDate ) ) // OK
                                {
                                    this->m_ArgDesiredTourId = csp->UW_Tour();
                                    s << "UW Tour [" << m_ArgDesiredTourId << "] ";
                                    TourUtil::writeLogINFO( s, true );
                                }
                            }
                        }
                        else
                        {
                            this->m_ArgDeliveryDate = TourUtil::getDateForSubsequentWeekday( csp->WeekDay() );
                            if ( !(csp->UW_Tour().IsEmpty()) )
                            {
                                if( this->isUpcomingTourValid( csp->UW_Tour(), this->m_ArgDeliveryDate ) )
                                {
                                    this->m_ArgDesiredTourId = csp->UW_Tour();
                                    s << "UW Tour [" << m_ArgDesiredTourId << "] (not for today)";
                                    TourUtil::writeLogINFO( s, true );
                                }
                            }
                        }
                    }
                }
                delete csList;
                csList = NULL;
            }
        }
        delete par;
        par = NULL;
    }
}

/***************************************************************************************************************************/
bool TourManager::hasToDoTourDetermination()
{
    // no tour determination necessary if there is no picking for the picking type
    if( NULL != m_PickingType ) // OK
    {
        if( m_PickingType->IsNoShipment() ) // OK
        {
            return false;
        }
    }
    return true;
}

/***************************************************************************************************************************/
void TourManager::resetArgInjections()
{
    this->m_ArgIBTBranchNo = 0;
    this->m_ArgDeliveryDate = TourUtil::getNullDate();
    this->m_ArgArticle = NULL;
    this->m_ArgNewOrder = false;
    this->m_ArgIBTTypeArticle = 0;
    this->m_ArgNLevelIBTType = 0;
    this->m_ArgDesiredTourId = "";
    this->m_ArgTimeOffset = TourUtil::getCurrentTime();
    this->m_ArgUseTimeOffset = false;
    this->m_ArgIBTTourDetermination = false;
    this->m_ArgIsOrderFromIBT = false;
    this->m_ArgAcceptAutoAssignableToursOnly = false;
    this->m_ArgNoCheckForTransitionTimesAndPickingDurations = false;
    this->m_ArgInIBTShuttleTourDetermination = false;
    this->m_ArgNoDelayedDelivery = false;
    this->m_ArgUseTransportExclusion = false;
    this->m_ArgOrderTourDate = TourUtil::getNullDate();
    this->m_ArgOrderTourID = "";
    this->m_ArgNotEarlierThanOrderTour = false;
    this->m_ArgReturnsToursOnly = false;
    this->m_ArgSearchLatestPossibleTour = false;
    this->m_ArgLatestArrival = TourUtil::getNullDate();
}

/***************************************************************************************************************************/
void TourManager::injectNoDelayedDelivery( const bool b /*= true*/ )
{
    this->m_ArgNoDelayedDelivery = b;
}

/***************************************************************************************************************************/
void TourManager::injectUseTransportExclusion(const bool b /*= true*/)
{
    this->m_ArgUseTransportExclusion = b;
}

/***************************************************************************************************************************/
void TourManager::injectReturnsTourSearch(const bool b /*= true*/)
{
    this->m_ArgReturnsToursOnly = b;
}

/***************************************************************************************************************************/
void TourManager::injectLatestPossibleTourSearch(const bool b, const nDate& tourdeparturedatetime)
{
    this->m_ArgSearchLatestPossibleTour = b;
    this->m_ArgLatestArrival = tourdeparturedatetime;
}


/***************************************************************************************************************************/
void TourManager::setNotEarlierThanOrderTour(nString tourid, nDate tourdate)
{
    m_ArgOrderTourDate = tourdate;
    m_ArgOrderTourID = tourid;
    m_ArgNotEarlierThanOrderTour = true;
}

/***************************************************************************************************************************/
void TourManager::injectNoCheckForTransitionTimesAndPickingDurations( const bool b /*= true*/ )
{
    this->m_ArgNoCheckForTransitionTimesAndPickingDurations = b;
}

/***************************************************************************************************************************/
void TourManager::injectTimeOffset( nTime timeOffset )
{
    this->m_ArgTimeOffset = timeOffset;
    this->m_ArgUseTimeOffset = true;

    // if timeOffset is in the past, use the current date
    if( nDate(TourUtil::getLongDate(m_ArgTimeOffset)).GetYYYYMMDD() < TourUtil::getCurrentDate().GetYYYYMMDD() )
    {
        std::stringstream s;
        s << "TM:injectTimeOffset [" << nDate(TourUtil::getLongDate(m_ArgTimeOffset)).GetYYYYMMDD() << "] ";

        this->m_ArgTimeOffset = nTime();

        s << "set to " << nDate(TourUtil::getLongDate(m_ArgTimeOffset)).GetYYYYMMDD() << " ";
        TourUtil::writeLogINFO( s, true );
    }
}

/***************************************************************************************************************************/
void TourManager::injectIBTBranchNo( const short& ibtbranchno )
{
    this->m_ArgIBTBranchNo = ibtbranchno;
}

/***************************************************************************************************************************/
void TourManager::injectIBTTypeArticle( const short& ibttypearticle )
{
    this->m_ArgIBTTypeArticle = ibttypearticle;
}

/***************************************************************************************************************************/
void TourManager::injectNLevelIBTType( const short& nlevelibttype )
{
    this->m_ArgNLevelIBTType = nlevelibttype;
}

/***************************************************************************************************************************/
void TourManager::injectDeliveryDate( const nDate& deliverydate )
{
    this->m_ArgDeliveryDate = TourUtil::getNullDate();
    if( TourUtil::getNullDate() != deliverydate && deliverydate > TourUtil::getCurrentDate() )
    {
        this->m_ArgDeliveryDate = deliverydate;
    }
}

/***************************************************************************************************************************/
void TourManager::injectArticle( pxArtBase* article )
{
    this->m_ArgArticle = article;
}

/***************************************************************************************************************************/
void TourManager::injectNewOrderFlag( const bool neworder )
{
    this->m_ArgNewOrder = neworder;
}

/***************************************************************************************************************************/
void TourManager::injectDesiredTourId( const nString& desiredtourid )
{
    this->m_ArgDesiredTourId = desiredtourid;
    if( "000000" == this->m_ArgDesiredTourId )
    {
        this->m_ArgDesiredTourId = "";
    }
}

/***************************************************************************************************************************/
void TourManager::injectIsOrderFromIBT( const bool isorderfromibt )
{
    this->m_ArgIsOrderFromIBT = isorderfromibt;
}

/***************************************************************************************************************************/
nString TourManager::getOrderTypeSpecificTour()
{
    nString retval;

    if( this->m_ArgIBTBranchNo <= 0 && this->m_ArgNewOrder )
    {
        pxOrderValidTrans *vtp = this->m_Session->OrderValidTransList( this->getCustomer()->getBranchNo() )->FindByCustomer(
            this->getCustomer(), this->m_OrderType);
        if( vtp )
        {
            if( !(vtp->TourId().IsEmpty()) )
            {
                if( this->isTourValid( vtp->TourId(), this->m_PickingType ) ) // OK
                {
                    retval = vtp->TourId();
                }
            }
        }
    }

    return retval;
}

/***************************************************************************************************************************/
pxOrderItemTourList* TourManager::getTourInformation( const long& orderno, const long& lineno )
{
    if( NULL == this->m_pxOrderItemTourList )
    {
        this->m_pxOrderItemTourList = new pxOrderItemTourList(this->m_Session);
    }
    m_pxOrderItemTourList->SelectOrderItemTour( orderno, lineno );
    return m_pxOrderItemTourList;
}

/***************************************************************************************************************************/
void TourManager::resetTourInformation( const long& orderno, const long& lineno )
{
    try
    {
        if( NULL == this->m_pxOrderItemTourList )
        {
            this->m_pxOrderItemTourList = new pxOrderItemTourList( this->m_Session );
        }
        m_pxOrderItemTourList->RemoveOrderItemTour( orderno, lineno );
    }
    catch( ... )
    {
    }
}

/***************************************************************************************************************************/
void TourManager::removeTourInformationIBT( const long& orderno, const long& lineno )
{
    try
    {
        if( NULL == this->m_pxOrderItemTourList )
        {
            this->m_pxOrderItemTourList = new pxOrderItemTourList( this->m_Session );
        }
        m_pxOrderItemTourList->RemoveOrderItemTourIBT( orderno, lineno );
    }
    catch( ... )
    {
    }
}

/***************************************************************************************************************************/
void TourManager::saveTourInformation( const long& orderno, const long& lineno, const TourInfo& tourinfo )
{
    try
    {
        // check if tour determination is necessary!
        if( this->hasToDoTourDetermination() )
        {
            if( orderno < pxOrder::PSEUDO_ORDER_NUMBER )
            {
                if( NULL == m_pxOrderItemTourList )
                {
                    m_pxOrderItemTourList = new pxOrderItemTourList(m_Session);
                }
                m_pxOrderItemTourList->AddOrderItemTour( orderno, lineno, tourinfo );

                std::stringstream s;
                s << "saveTourInformation orderno[" << orderno << "] lineno [" << lineno << "] " << tourinfo.serialize();
                TourUtil::writeLogINFO(s);
            }
        }
    }
    catch( ... )
    {
    }
}

/***************************************************************************************************************************/
TourManager::TourManager( pxSession* session, const long& orderno, const short& branchno, const long& customerno, const pxCommType* commtype, const nString& ordertype /*= ""*/ )
    : pxErrorLoggable(), m_OrderNo( orderno ), m_BranchNo( branchno ), m_CustomerNo( customerno ), m_OrderEntryParam(session->getOrderEntryParam(branchno)), m_OrderType( ordertype ), m_PickingType( commtype ), m_Session( session )
{
    m_CustomerToursCurrent = NULL;
    m_CustomerToursWeek = NULL;
    m_Customer = NULL;
    m_pxOrderItemTourList = NULL;
    m_IBTBranchesList = NULL;
    m_ToursLoaded = false;
    m_ShuttleCustomerNo = 0;
    m_HolidayList = NULL;
    m_HolidaysLoadedForBranch = 0;
    this->resetArgInjections();
}

/***************************************************************************************************************************/
TourManager::~TourManager()
{
    m_Session = NULL;           // don�t delete session object!
    m_PickingType = NULL;       // don�t delete comm type object!
    m_HolidayList = NULL;       // don�t delete holidaylist object!

    if( NULL != m_Customer )
    {
        delete m_Customer;
        m_Customer = NULL;
    }

    if( NULL != m_IBTBranchesList )
    {
        delete m_IBTBranchesList;
        m_IBTBranchesList = NULL;
    }

    if( NULL != m_CustomerToursCurrent )
    {
        delete m_CustomerToursCurrent;
        m_CustomerToursCurrent = NULL;
    }

    if( NULL != m_CustomerToursWeek )
    {
        delete m_CustomerToursWeek;
        m_CustomerToursWeek = NULL;
    }

    if( NULL != m_pxOrderItemTourList )
    {
        delete m_pxOrderItemTourList;
        m_pxOrderItemTourList = NULL;
    }
}

pxHoliDayList* TourManager::getHolidayList()
{
    if( NULL == m_HolidayList || m_HolidaysLoadedForBranch != getCustomer()->getBranchNo())
    {
        m_HolidayList = m_Session->HoliDayList( this->getCustomer()->getBranchNo() );
    }
    return m_HolidayList;
}

/***************************************************************************************************************************/
TourInfo TourManager::getTourInformation( const nString& tourid )
{
    TourInfo retval;

    CustomerTourList tl( this->m_Session, m_BranchNo, m_CustomerNo );
    if( !tl.getCurrentTour( tourid ) && !tl.getTour( tourid ) )
    {
        return retval;
    }

    if( tl.Entries() == 0 )
    {
        return retval;
    }

    CustomerTour* ct = NULL;
    CustomerTourListIter iter(tl);
    while( (ct = (CustomerTour*)++iter ) != NULL )
    {
        retval = getCustomerTourAsTourInfo( ct, ct->getPickingDate() );
        break;
    }

    return retval;
}

/***************************************************************************************************************************/
bool TourManager::isTourValidForOrderClosure(const nString& tourid, const pxCommType* pickingtype, const bool checkDurationsAndTransitionTimes /*= true*/)
{
    resetError();
    loadTours();
    return isCurrentTourValid(tourid, pickingtype, true, checkDurationsAndTransitionTimes );
}

/***************************************************************************************************************************/
bool TourManager::specialTourPossible( pxArtBase* article ) const
{
    return this->isArticleWithSpecialDeliveryConditions( article );
}

/***************************************************************************************************************************/
bool TourManager::isArticleDeliverable( pxArtBase* article )
{
    resetError();
    loadTours();

    if( !this->specialTourPossible(article) )
    {
        return true;
    }
    if( m_CustomerToursCurrent->isArticleDeliverable( article ) )
    {
        return true;
    }
    if( m_CustomerToursWeek->isArticleDeliverable( article ) )
    {
        return true;
    }
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isArticleDeliverableForIBT( const short ibtbranchno, pxArtBase* article )
{
    if( !isTransportExclusionEnabled() ) return true;
    if( !isArticleWithSpecialDeliveryConditions(article) ) return true;

    // check if the customer has ibt tours with permission for the article type
    if( !m_Session->getIbtComponentManager()->getTransportExclusionChecker()->isTransportPossibleForCustomer(m_BranchNo, m_CustomerNo, article->ArtikelNr()) )
    {
        return false;
    }

    // check if the shuttle-customers have ibt tours with permission for the article type
    if( !m_Session->getIbtComponentManager()->getTransportExclusionChecker()->isTransportPossible(this->m_BranchNo, ibtbranchno, article->ArtikelNr()) )
    {
        return false;
    }

    return true;
}

/***************************************************************************************************************************/
/*static*/ bool TourManager::checkIsTourValid(pxSession* session, const short branchno, const long customerno, const nString& tourid, const nDate& deliverydate /*= TourUtil::getNullDate()*/)
{
    pxCommType commtype(session, '0', branchno);
    TourManager tm(session, 0, branchno, customerno, &commtype);
    return tm.isTourValidForDate(tourid, deliverydate);
}

/***************************************************************************************************************************/
bool TourManager::isTourValidForDate(const nString& tourid, const nDate& deliverydate /*= TourUtil::getNullDate()*/)
{
    resetError();
    loadTours();

    short weekday = TourUtil::getCurrentDate().GetDayOfWeek();
    if( deliverydate != TourUtil::getNullDate() ) weekday = deliverydate.GetDayOfWeek();

    CustomerTour* tour = getTourForWeekday(tourid, TourUtil::getWeekDay(weekday));
    if( NULL == tour )
    {
        return false;
    }
    return true;

}

/***************************************************************************************************************************/
bool TourManager::isTourValid(const nString& tourid, const pxCommType* pickingtype, const nDate& deliverydate /*= TourUtil::getNullDate()*/)
{
    resetError();
    loadTours();

    // if there is no specific deliverydate or the deliverydate is today or in the past check tour within current tours
    if( deliverydate == TourUtil::getNullDate() )
    {
        return isCurrentTourValid(tourid, pickingtype);
    }
    else
    {
        if( deliverydate < TourUtil::getCurrentDate() )
        {
            std::stringstream s;
            s << "TM:isTourValid Tour[" << tourid << "/" << deliverydate.GetYYYYMMDD() << "] -> FALSE";
            TourUtil::writeLogINFO( s );
            return false;
        }

        if( deliverydate > TourUtil::getCurrentDate() )
        {
            return isUpcomingTourValid(tourid, deliverydate); // deliverydate is in the future
        }

        return isCurrentTourValid(tourid, pickingtype); // deliverydate is current date
    }
}

/***************************************************************************************************************************/
void TourManager::setOrderType( const nString& ordertype )
{
    if( m_OrderType != ordertype )
    {
        m_OrderType = ordertype;
        m_ToursLoaded = false;
    }
}

/***************************************************************************************************************************/
void TourManager::setPickingType( const pxCommType* commtype )
{
    if( NULL != m_PickingType )
    {
        m_PickingType = NULL;
    }
    m_PickingType = commtype;
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/***************************************************************************************************************************/
bool TourManager::isDesiredTourCheckSuccessful( CustomerTour* ct )
{
    if( !this->m_ArgDesiredTourId.IsEmpty() )
    {
        if( this->m_ArgDesiredTourId != ct->getTourId() )
        {
            std::stringstream s;
            s << "TM:isDesiredTourCheckSuccessful Tour[" << m_ArgDesiredTourId << "|" << ct->getPickingDate().GetYYYYMMDD() << "] WD[" << ct->getWeekDay() << "] -> FALSE";
            TourUtil::writeLogINFO( s );
            return false;
        }
    }
    else
    {
        // SR-15061150: TourManager: Nicht automatisch zuordbare Touren nur w�hlen wenn als Wunschtour gesetzt
        if( !ct->isAutoAssignable() )
        {
            std::stringstream s;
            s << "TM:isDesiredTourCheckSuccessful NotAA Tour[" << m_ArgDesiredTourId << "|" << ct->getPickingDate().GetYYYYMMDD() << "] WD[" << ct->getWeekDay() << "] -> FALSE";
            TourUtil::writeLogINFO( s );
            return false;
        }
    }
    return true;
}

/***************************************************************************************************************************/
bool TourManager::isReturnsTourCheckSuccessful(CustomerTour* ct)
{
    if (m_ArgReturnsToursOnly)
    {
        if (!ct->isReturnsTour())
        {
            std::stringstream s;
            s << "TM:isReturnsTourCheckSuccessful Tour[" << ct->getTourId() << "|" << ct->getPickingDate().GetYYYYMMDD() << "] -> FALSE";
            TourUtil::writeLogINFO(s);
            return false;
        }

        return true;
    }
    return true;
}

/***************************************************************************************************************************/
bool TourManager::isIBTTourCheckSuccessful( CustomerTour* ct )
{
    if( this->m_ArgIBTTourDetermination )
    {
        if( !ct->isIBTTour() )
        {
            std::stringstream s;
            s << "TM:isIBTTourCheckSuccessful Tour[" << ct->getTourId() << "|" << ct->getPickingDate().GetYYYYMMDD() << "] -> FALSE";
            TourUtil::writeLogINFO(s);
            return false;
        }

        // check if tour is affected by delayed delivery
        if (isTransportExclusionEnabled() && isArticleWithSpecialDeliveryConditions(m_ArgArticle) )
        {
            pxCustDelDeliveryList deldeliverylist(m_Session);
            pxCustDelDelivery* custdeldelivery = NULL;
            custdeldelivery = deldeliverylist.getDelayedDeliveryForDate(m_BranchNo, m_CustomerNo, ct->getPickingDate().GetYYYYMMDD(), ct->getPickingDate().GetDayOfWeek(), m_ArgArticle);
            if (custdeldelivery != NULL && this->delayDeliveryDespiteEmergencyService(ct->getPickingDate().GetYYYYMMDD()))
            {
                if (TourUtil::getTourIdAsHHMM(ct->getTourId()) > 2400)
                {
                    std::stringstream s;
                    s << "TM:isIBTTourCheckSuccessful Tour[" << ct->getTourId() << "|" << ct->getPickingDate().GetYYYYMMDD() << "] -> FALSE (DelayedDelivery for >2400 Tour)";
                    TourUtil::writeLogINFO(s);
                    return false;
                }
                nClock desiredtour(TourUtil::getTourIdAsHHMM(ct->getTourId()) * 100);
                if (desiredtour.GetDaySeconds() > custdeldelivery->Time().GetDaySeconds())
                {
                    std::stringstream s;
                    s << "TM:isIBTTourCheckSuccessful Tour[" << ct->getTourId() << "|" << ct->getPickingDate().GetYYYYMMDD() << "] -> FALSE (DelayedDelivery for Tour)";
                    TourUtil::writeLogINFO(s);
                    return false;
                }
            }
        }

    }
    return true;
}

/***************************************************************************************************************************/
bool TourManager::isTourAssignabilityCheckSuccessful( CustomerTour* ct )
{
    std::stringstream s;
    s << "TM:isTourAssignabilityCheckSuccessful Tour[" << ct->getTourId() << "|" << ct->getPickingDate().GetYYYYMMDD() << "] ";

    if( this->m_ArgNoCheckForTransitionTimesAndPickingDurations )
    {
        ct->injectNoCheckForTransitionTimesAndPickingDurations(true);
        s << "NoCheckTTPD! ";
    }

    bool pickdurationcheck = this->m_ArgNoCheckForTransitionTimesAndPickingDurations;

    if( this->m_ArgIBTTourDetermination )
    {
        ct->injectNoCheckForTransitionTimesAndPickingDurations(true);
        s << "NoCheckTTPD due to IBTTourDet! ";
    }

    bool useAutoAssignableToursOnly = this->m_ArgAcceptAutoAssignableToursOnly;
    if( !this->m_ArgDesiredTourId.IsEmpty() )
    {
        if( this->m_ArgDesiredTourId == ct->getTourId() )
        {
            useAutoAssignableToursOnly = false;
            s << "NotOnlyAA! ";
        }
    }

    if( isHoliday(ct->getPickingDate()) )
    {
        s << "Holiday! -> FALSE";
        TourUtil::writeLogINFO(s);
        return false;
    }

    if( NULL != this->m_PickingType ) // OK
    {
        if( this->m_PickingType->IsNoShipment() ) // OK
        {
            s << "NoShipment! -> TRUE";
            TourUtil::writeLogINFO(s);
            return true;
        }
    }

    if( !this->m_ArgUseTimeOffset )
    {
        if( ct->isAssignable( useAutoAssignableToursOnly ) )
        {
            ct->injectNoCheckForTransitionTimesAndPickingDurations(pickdurationcheck); // restore old settings
            s << "#1 -> TRUE";
            TourUtil::writeLogINFO(s);
            return true;
        }
    }
    else
    {
        if( ct->isAssignable( useAutoAssignableToursOnly, this->m_ArgTimeOffset, m_ArgForceTimeOffsetUsage ) )
        {
            ct->injectNoCheckForTransitionTimesAndPickingDurations(pickdurationcheck); // restore old settings
            s << "#2 -> TRUE";
            TourUtil::writeLogINFO(s);
            return true;
        }
    }

    if( m_ArgUseTimeOffset )
    {
        if( ct->getPickingDate().GetYYYYMMDD() > nDate(TourUtil::getLongDate(m_ArgTimeOffset)).GetYYYYMMDD() )
        {
            s << "#3 -> TRUE";
            TourUtil::writeLogINFO(s);
            return true;
        }
    }

    s << "-> FALSE Offset[" << TourUtil::getLongTime(this->m_ArgTimeOffset) << " " << TourUtil::getLongDate( this->m_ArgTimeOffset ) << "] ";
    if( m_ArgUseTimeOffset ) s << "UseTO! ";
    if( useAutoAssignableToursOnly ) s << "AAOnly! ";
    s << "CMSG_ORD_ROUTE_TIMEOFF";
    TourUtil::writeLogINFO(s);

    this->setTourInfoError( CMSG_ORD_ROUTE_TIMEOFF );
    ct->injectNoCheckForTransitionTimesAndPickingDurations(pickdurationcheck); // restore old settings
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isArticleAssignabilityCheckSuccessful( CustomerTour* ct, pxArtBase* article )
{
    if( ct->isValidForArticle( article ) )
    {
        return true;
    }

    std::stringstream s;
    s << "TM:isArticleAssignabilityCheckSuccessful Tour[" << ct->getTourId() << "|" << ct->getPickingDate().GetYYYYMMDD() << "] ";

    if( isTransportExclusionEnabled() )
    {
        m_TourInfo.setWarning( CMSG_ORD_ROUTE_NOPERMISSION ); // not treated as error at the moment!!!
        s << " -> FALSE Warning:CMSG_ORD_ROUTE_NOPERMISSION";
        TourUtil::writeLogINFO(s);
        return false;
    }

    m_TourInfo.setWarning( CMSG_ORD_ROUTE_NOPERMISSION ); // not treated as error at the moment!!!

    s << " -> TRUE Warning:CMSG_ORD_ROUTE_NOPERMISSION";
    TourUtil::writeLogINFO(s);

    return true;
}

/***************************************************************************************************************************/
bool TourManager::isWeekdayCheckSuccessful( CustomerTour* ct, short weekday )
{
    //Commented because Aufträge verzögern icht möglich
    /*if ( isTourOverMidnightMatchingNextWeekday(ct, weekday) )
    {
        return true;
    }*/

    if( ct->getWeekDay() != TourUtil::getWeekDay(weekday) )
    {
        return false;
    }

    return true;
}

/***************************************************************************************************************************/
//Commented because Aufträge verzögern icht möglich
/*bool TourManager::isTourOverMidnightMatchingNextWeekday(CustomerTour* ct, short weekday)
{
    // Check if the tour's time is between 24:00 and 48:00 (over midnight)
    long tourTimeHHMM = TourUtil::getTourIdAsHHMM(ct->getTourId());
    if (tourTimeHHMM > 2400 && tourTimeHHMM < 4800)
    {
        // Check if the given weekday is the next weekday after the tour's weekday
        if (weekday == TourUtil::getNextWeekday(static_cast<short>(ct->getWeekDay())))
        {
            return true;
        }
    }
    return false;
}*/

/***************************************************************************************************************************/
bool TourManager::isTransportExclusionEnabled()
{
    if( m_OrderEntryParam->IsUseTourManagerWithTransportExclusion() ) return true;
    if( m_ArgUseTransportExclusion ) return true;
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isHoliday(const nDate& dateToCheck)
{
    if( getHolidayList()->CheckDateForHoliday( dateToCheck, this->getCustomer()->getBranchNo() ) )
    {
        return true;
    }
    return false;
}

/***************************************************************************************************************************/
nDate TourManager::changeDeliveryDateForPublicHolidays( const nDate& deliverydate )
{
    nDate retval = deliverydate;
    if( retval == TourUtil::getNullDate() )
    {
        retval = TourUtil::getCurrentDate();
    }

    if( getHolidayList()->CheckDateForHoliday( deliverydate, this->getCustomer()->getBranchNo() ) )
    {
        long deliveryday = getHolidayList()->CalculateNextWorkDay( deliverydate, this->getCustomer()->getBranchNo() );
        retval = nDate(deliveryday);

        std::stringstream s;
        s << "TM:changeDeliveryDateForPublicHolidays Date[" << deliverydate.GetYYYYMMDD() << "] ";
        s << "Holiday! DeliveryDay[" << retval.GetYYYYMMDD() << "] ";

        // P-16000011 -> Verz�gerung auf invalide Tour! Erste Tour des Tages auf den verz�gert wird verwenden!
        if( "" != m_ArgDesiredTourId )
        {
            if( !this->m_CustomerToursWeek->isTourAvailableForWeekday( this->m_ArgDesiredTourId, retval.GetDayOfWeek() ) )
            {
                this->m_ArgDesiredTourId = "";
                s << "TourID not available for weekday! Removed DesiredTour! ";
            }
        }

        TourUtil::writeLogINFO(s);
    }
    return retval;
}

/***************************************************************************************************************************/
void TourManager::delayDelivery()
{
    // check if all orders should be delayed
    if( TourUtil::getNullDate() == this->m_ArgDeliveryDate )
    {
        if( this->m_OrderEntryParam->DelayedDays() > 0 )
        {
            this->m_ArgDeliveryDate = TourUtil::getCurrentDate().add( this->m_OrderEntryParam->DelayedDays() );
            std::stringstream s;
            s << "TM:delayDelivery DelayedDelivery due to " << this->m_OrderEntryParam->DelayedDays() << " DelayedDays in Param! " << this->m_ArgDeliveryDate.GetYYYYMMDD();
            TourUtil::writeLogINFO(s);
        }
    }

    // if the desired delivery date is a public holiday, get the next working day
    if( TourUtil::getNullDate() != this->m_ArgDeliveryDate )
    {
        this->m_ArgDeliveryDate = this->changeDeliveryDateForPublicHolidays( this->m_ArgDeliveryDate );
    }
}

/***************************************************************************************************************************/
bool TourManager::delayDeliveryDespiteEmergencyService(long datum /*= 0*/)
{
    if( !isTransportExclusionEnabled() ) return true;

    EmergencyService esvc( this->m_Session, this->m_BranchNo, this->m_CustomerNo );
    if( !esvc.Get(datum) ) return true;
    if( !esvc.isRelevantForTour(this->m_ArgDesiredTourId) ) return true;
    return esvc.delayDeliveryForArticle(this->m_ArgArticle);
}

/***************************************************************************************************************************/
void TourManager::delayDeliveryForArticle()
{
    std::stringstream s;
    s << "TM:delayDeliveryForArticle ";

    if( this->m_ArgNoDelayedDelivery )
    {
        s << "NoDD! ";
        TourUtil::writeLogINFO(s);
        return;
    }

    if( !this->isArticleWithSpecialDeliveryConditions(this->m_ArgArticle) ) return;
    if( TourUtil::getNullDate() != this->m_ArgDeliveryDate ) return;

    // check delayed delivery
    pxCustDelDeliveryList deldeliverylist(this->m_Session);
    pxCustDelDelivery* custdeldelivery = NULL;
    if( isTransportExclusionEnabled() )
    {
        custdeldelivery = deldeliverylist.getDelayedDelivery(this->m_BranchNo, this->m_CustomerNo, TourUtil::getCurrentWeekday(), true, this->m_ArgArticle);
    }
    else
    {
        custdeldelivery = deldeliverylist.getDelayedDelivery(this->m_BranchNo, this->m_CustomerNo, TourUtil::getCurrentWeekday(), false, this->m_ArgArticle);
    }

    // no valid entry in delayed delivery
    if( NULL == custdeldelivery ) return;

    // no delayed delivery due to emergency service

    long pickdate = 0;
    if (TourUtil::getNullDate() != m_ArgDeliveryDate) pickdate = m_ArgDeliveryDate.GetYYYYMMDD();
    if( !this->delayDeliveryDespiteEmergencyService(pickdate) ) return;

    nClock desiredtour( TourUtil::getTourIdAsHHMM(this->m_ArgDesiredTourId) * 100 );

    if( TourUtil::getTourIdAsHHMM(this->m_ArgDesiredTourId) > 2400 )
    {
        this->m_ArgDesiredTourId = custdeldelivery->TourId();
        this->m_ArgDeliveryDate = TourUtil::getDateForSubsequentWeekdayOccurrence( custdeldelivery->DelayedWeekDay() );
        this->m_ArgDeliveryDate = this->changeDeliveryDateForPublicHolidays( this->m_ArgDeliveryDate );

        s << "delay#1 TourID[" << m_ArgDesiredTourId << "/" << m_ArgDeliveryDate.GetYYYYMMDD() << "] ";

        // P-16000011 -> Verz�gerung auf invalide Tour! Erste Tour des Tages auf den verz�gert wird verwenden!
        if( !this->m_CustomerToursWeek->isTourAvailableForWeekday( this->m_ArgDesiredTourId, custdeldelivery->DelayedWeekDay() ) )
        {
            this->m_ArgDesiredTourId = "";
            s << "TourID not for WeekDay! Removed! ";
        }
        TourUtil::writeLogINFO(s);
    }
    else if( desiredtour.GetDaySeconds() > custdeldelivery->Time().GetDaySeconds() )
    {
        this->m_ArgDesiredTourId = custdeldelivery->TourId();
        this->m_ArgDeliveryDate = TourUtil::getDateForSubsequentWeekdayOccurrence( custdeldelivery->DelayedWeekDay() );
        this->m_ArgDeliveryDate = this->changeDeliveryDateForPublicHolidays( this->m_ArgDeliveryDate );

        s << "delay#2 TourID[" << m_ArgDesiredTourId << "/" << m_ArgDeliveryDate.GetYYYYMMDD() << "] ";

        // P-16000011 -> Verz�gerung auf invalide Tour! Erste Tour des Tages auf den verz�gert wird verwenden!
        if( !this->m_CustomerToursWeek->isTourAvailableForWeekday( this->m_ArgDesiredTourId, custdeldelivery->DelayedWeekDay() ) )
        {
            this->m_ArgDesiredTourId = "";
            s << "TourID not for WeekDay! Removed! ";
        }
        TourUtil::writeLogINFO(s);
    }
}

/***************************************************************************************************************************/
bool TourManager::isArticleWithSpecialDeliveryConditions( pxArtBase* article ) const
{
    if( NULL != article )
    {
        if( this->isNarcoticArticle(article) )
        {
            return true;
        }
        if( this->isCoolArticle(article) )
        {
            return true;
        }
        if( this->isCoolBelow8Article(article) )
        {
            return true;
        }
        if( this->isCoolBelow20Article(article) )
        {
            return true;
        }
        if ( this->isPsychotropicArticle(article) )
        {
            return true;
        }
    }
    return false;
}

/***************************************************************************************************************************/
void TourManager::determineLocalTour()
{
    m_TourInfo.init();
    if( this->isDeliveryDateInTheFuture() )
    {
        determineTourForDeliveryDate( this->m_ArgDeliveryDate, this->m_ArgArticle );
    }
    else
    {
        determineCurrentTour(this->m_ArgArticle);
        if( !m_TourInfo.getTourFound() )
        {
            determineSubsequentTour(this->m_ArgArticle);
        }
    }

    if( m_TourInfo.getTourFound() )
    {
        m_TourInfo.resetErrorsAndWarnings();
        resetError();
    }
}

/***************************************************************************************************************************/
void TourManager::determineCurrentTour( pxArtBase* article )
{
    m_TourInfo.resetErrorsAndWarnings();

    if (this->m_ArgSearchLatestPossibleTour == true)
    {
        return;
    }

    std::stringstream s;
    s << "TM:determineCurrentTour ";

    if( 0 != m_CustomerToursCurrent->Entries() )
    {
        CustomerTourListIter iter(*m_CustomerToursCurrent);
        CustomerTour* ct = NULL;
        while( (ct = (CustomerTour*)++iter) != NULL )
        {
            s.str(std::string());
            s << "TM:determineCurrentTour ";
            s << "Tour[" << ct->getTourId() << "/" << ct->getPickingDate().GetYYYYMMDD() << "(" << ct->getWeekDay() << ")] ";

            ct->injectNoCheckForTransitionTimesAndPickingDurations(m_ArgNoCheckForTransitionTimesAndPickingDurations);
            if( !isDesiredTourCheckSuccessful( ct ) ) continue;
            if( !isIBTTourCheckSuccessful( ct ) ) continue;
            if (!isReturnsTourCheckSuccessful(ct)) continue;
            if( !isTourAssignabilityCheckSuccessful( ct ) ) continue;
            if( !isArticleAssignabilityCheckSuccessful( ct, article ) ) continue;
            if( !isNotEarlierThanOrderTour(ct) ) continue;
            //Commented because Aufträge verzögern icht mögl
            //If the Tour departure results in Public Holiday.
            //if( isHoliday(ct->getTourDepartureDateTime( TourUtil::getNullDate()))) continue;

            transferCustomerTour2TourInfo(ct);
            s << "OK! ";
            TourUtil::writeLogINFO(s);
            return;
        }
    }

    s << "No Tour found! ";
    TourUtil::writeLogINFO(s);
}

/***************************************************************************************************************************/
void TourManager::determineSubsequentTour( pxArtBase* article )
{
    if (m_ArgSearchLatestPossibleTour)
    {
        determineSubsequentLatestPossibleTour(article);
    }
    else
    {
        std::stringstream s;
        s << "TM:determineSubsequentTour ";

        if (m_CustomerToursWeek->Entries() > 0)
        {
            nDate date = TourUtil::getCurrentDate();
            short startingWeekday = date.GetDayOfWeek();
            short day = TourUtil::getNextWeekday(startingWeekday);

            for (int weekdayschecked = 0; weekdayschecked < 7; ++weekdayschecked)
            {
                nDate temptourdate = TourUtil::getDateForSubsequentWeekday(static_cast<short>(TourUtil::getWeekDay(day)));
                if (temptourdate == this->changeDeliveryDateForPublicHolidays(temptourdate)) // do not use date if it�s a public holiday
                {
                    CustomerTourListIter iter(*m_CustomerToursWeek);
                    CustomerTour* ct = NULL;
                    {
                        while ((ct = (CustomerTour*)++iter) != NULL)
                        {
                            ct->injectNoCheckForTransitionTimesAndPickingDurations(this->m_ArgNoCheckForTransitionTimesAndPickingDurations);
                            if (ct->getWeekDay() == TourUtil::getWeekDay(day))
                            {
                                ct->setPickingDate(temptourdate);
                                s.str(std::string());
                                s << "TM:determineSubsequentTour Tour[" << ct->getTourId() << "/" << ct->getPickingDate().GetYYYYMMDD() << "(" << ct->getWeekDay() << ")] ";
                                if (!isDesiredTourCheckSuccessful(ct)) continue;
                                if (!isIBTTourCheckSuccessful(ct)) continue;
                                if (!isReturnsTourCheckSuccessful(ct)) continue;
                                if (!isTourAssignabilityCheckSuccessful(ct)) continue;
                                if (!isArticleAssignabilityCheckSuccessful(ct, article)) continue;
                                if (!isNotEarlierThanOrderTour(ct)) continue;

                                transferCustomerTour2TourInfo(ct, temptourdate);
                                s << "OK! ";
                                TourUtil::writeLogINFO(s);
                                return;
                            }
                            else
                            {
                                s.str(std::string());
                                s << "TM:determineSubsequentTour !!!day:[" << TourUtil::getWeekDay(day) << "] Tour[" << ct->getTourId() << "/" << ct->getPickingDate().GetYYYYMMDD() << "(" << ct->getWeekDay() << ")] ";
                                TourUtil::writeLogINFO(s);
                            }
                        }
                    }
                }
                day = TourUtil::getNextWeekday(day);
            }
        }

        s << "No Tour found! CMSG_ORD_ROUTE_NOMORE";
        TourUtil::writeLogINFO(s);
        this->setTourInfoError(CMSG_ORD_ROUTE_NOMORE);
    }
}

/***************************************************************************************************************************/
void TourManager::determineSubsequentLatestPossibleTour(pxArtBase* article)
{
     std::stringstream s;
     s << "TM:determineSubsequentLatestPossibleTour ";
     bool tourFound = false;
     if (m_CustomerToursWeek->Entries() > 0)
     {
         nDate date = TourUtil::getCurrentDate();
	 short startingWeekday = date.GetDayOfWeek();
         short day = TourUtil::getNextWeekday(startingWeekday);
         //Commented because Aufträge verzögern icht möglich
	 //short day = date.GetDayOfWeek();

         for (int weekdayschecked = 0; weekdayschecked < 7; ++weekdayschecked)
         {
	     nDate temptourdate = TourUtil::getDateForSubsequentWeekday(static_cast<short>(TourUtil::getWeekDay(day)));
             //Commented because Aufträge verzögern icht möglich
             //nDate temptourdate = date + weekdayschecked;
             if (temptourdate == this->changeDeliveryDateForPublicHolidays(temptourdate)) // do not use date if it�s a public holiday
             {
                 CustomerTourListIter iter(*m_CustomerToursWeek);
                 CustomerTour* ct = NULL;
                 {
                     while ((ct = (CustomerTour*)++iter) != NULL)
                     {
                         ct->injectNoCheckForTransitionTimesAndPickingDurations(this->m_ArgNoCheckForTransitionTimesAndPickingDurations);
                         if (ct->getWeekDay() == TourUtil::getWeekDay(day))
                         {
                             ct->setPickingDate(temptourdate);
                             s.str(std::string());
                             s << "TM:determineSubsequentLatestPossibleTour Tour[ Tourid " << ct->getTourId() << "/ picking date" << ct->getPickingDate().GetYYYYMMDD() << "week day(" << ct->getWeekDay() << ")] ";
                             if (!isDesiredTourCheckSuccessful(ct)) continue;
                             if (!isIBTTourCheckSuccessful(ct)) continue;
                             if (!isReturnsTourCheckSuccessful(ct)) continue;
                             if (!isTourAssignabilityCheckSuccessful(ct)) continue;
                             if (!isArticleAssignabilityCheckSuccessful(ct, article)) continue;
                             if (!isNotEarlierThanOrderTour(ct)) continue;

                             if( isArrivalBefore(ct, m_ArgLatestArrival))
                             {
                                s << " isArrivalBefore is true so continue! ";
                                TourUtil::writeLogINFO(s);
                                transferCustomerTour2TourInfo(ct, temptourdate);
                                tourFound = true;
                                continue;
                             }
                             else // wenn Tourankunft nicht rechtzeitig
                             {
                                 s << " isArrivalBefore is false so return ";
                                 TourUtil::writeLogINFO(s);
                                 return;
                             }
                         }
                         else
                         {
                             s.str(std::string());
                             s << "TM:determineSubsequentLatestPossibleTour !!!weekday:[" << TourUtil::getWeekDay(day) << "] Tour[" << ct->getTourId() << "/ picking date" << ct->getPickingDate().GetYYYYMMDD() << "weekday (" << ct->getWeekDay() << ")] ";
                             TourUtil::writeLogINFO(s);
                         }
                     }
                 }
             }
             day = TourUtil::getNextWeekday(day);
         }
     }

     if (!tourFound)
     {
         s << "No Tour found! CMSG_ORD_ROUTE_NOMORE";
         TourUtil::writeLogINFO(s);
         this->setTourInfoError(CMSG_ORD_ROUTE_NOMORE);
     }
     else
     {
         s.str(std::string());
         s << "TM:determineSubsequentLatestPossibleTour END !!! TourId[" << m_TourInfo.getTourID() << "/Tourdate" << m_TourInfo.getTourDate().GetYYYYMMDD() << "] ";
         TourUtil::writeLogINFO(s);
     }
}

/***************************************************************************************************************************/
void TourManager::determineTourForDeliveryDate( const nDate& deliverydate, pxArtBase* article )
{
    std::stringstream log;
    log << "O:" << m_OrderNo << " Tour4Date " << deliverydate.GetYYYYMMDD();
    TourUtil::writeLogDEBUG(log);

    if( m_CustomerToursWeek->Entries() > 0 )
    {
        //Commented because Aufträge verzögern icht möglich
        //short day = deliverydate.GetDayOfWeek();
	nDate deliverydatecalc = deliverydate;
        short startingWeekday = deliverydatecalc.GetDayOfWeek();
        short day = startingWeekday;

        for( int weekdayschecked = 0; weekdayschecked < 7; ++weekdayschecked )
        {
	    nDate temptourdate = deliverydatecalc;
            //Commented because Aufträge verzögern icht möglich
            //nDate temptourdate = deliverydate + weekdayschecked;
            CustomerTourListIter iter(*m_CustomerToursWeek);
            CustomerTour* ct = NULL;
            {
                while( (ct = (CustomerTour*)++iter) != NULL )
                {
                    if( !isWeekdayCheckSuccessful( ct, day ) ) continue;
                    //Commented because Aufträge verzögern icht möglich
                    /*If the this date is a Public holiday, so check.
                    if( isHoliday(temptourdate)) break;

                    if ( isTourOverMidnightMatchingNextWeekday( ct, day ) )
                    {
                        --temptourdate;
                        //If the this results in a Public holiday, so check.
                        if( isHoliday(temptourdate)) break;
                    }*/

                    ct->setPickingDate( temptourdate );
                    ct->injectNoCheckForTransitionTimesAndPickingDurations(this->m_ArgNoCheckForTransitionTimesAndPickingDurations);

                    log << "O:" << m_OrderNo << " WTOUR[" << ct->getPickingDate().GetYYYYMMDD() << "/" << ct->getTourId() << "/" << ct->getWeekDay() << "] ";
                    if( m_ArgNoCheckForTransitionTimesAndPickingDurations ) log << "NoKZPD ";
                    if( m_ArgUseTimeOffset ) log << "UseTimeOffset ";
                    TourUtil::writeLogDEBUG(log);

                    if( !isDesiredTourCheckSuccessful( ct ) ) { log << "O:" << m_OrderNo << " NotDesiredTour"; TourUtil::writeLog(log); continue; }
                    if( !isIBTTourCheckSuccessful( ct ) ) { log << "O:" << m_OrderNo << " NotVBTour"; TourUtil::writeLog(log); continue; }
                    if( !isReturnsTourCheckSuccessful( ct ) ) { log << "O:" << m_OrderNo << " NotReturnsTour"; TourUtil::writeLog(log); continue; }
                    if( !isArticleAssignabilityCheckSuccessful( ct, article ) ) { log << "O:" << m_OrderNo << " NotValidForArticle"; TourUtil::writeLog(log); continue; }
                    if( !isNotEarlierThanOrderTour(ct) ) continue;

                    if( this->m_ArgUseTimeOffset )
                    {
                        if( temptourdate.GetYYYYMMDD() == this->m_ArgDeliveryDate.GetYYYYMMDD() )
                        {
                            if( !isTourAssignabilityCheckSuccessful( ct ) )
                            {
                                log << "O:" << m_OrderNo << " NotAssignable [Offset:" << m_ArgTimeOffset.GetHours() << m_ArgTimeOffset.GetMinutes() << "]";
                                TourUtil::writeLog(log);
                                continue;
                            }
                        }
                    }

                    log << "O:" << m_OrderNo << " OK -> WTOUR[" << ct->getPickingDate().GetYYYYMMDD() << "/" << ct->getTourId() << "] ";
                    TourUtil::writeLogDEBUG(log);

                    transferCustomerTour2TourInfo(ct, temptourdate);
                    return;
                }
            }
            day = TourUtil::getNextWeekday(day);
            ++deliverydatecalc;
        }
    }
    else
    {
        log << "O:" << m_OrderNo << " NO WEEKTOURS";
        TourUtil::writeLog(log);
    }

    log << "O:" << m_OrderNo << " NO WEEKTOUR FOUND! => " << CMSG_ORD_ROUTE_NOMORE;
    TourUtil::writeLog(log);
    this->setTourInfoError( CMSG_ORD_ROUTE_NOMORE );
}

/***************************************************************************************************************************/
nDate TourManager::getDeliveryDateTimePPE() const
{
    std::stringstream s;
    s << "TM:getDeliveryDateTimePPE ";

    nDate retval = TourUtil::getCurrentDate();
    long currenttime = TourUtil::getLongTime( TourUtil::getCurrentTime() );
    s << "Date[" << retval.GetYYYYMMDD() << "] Time[" << currenttime << "] ";

    short currentweekday = TourUtil::getCurrentWeekday();
    short adddays = 0;
    switch( currentweekday )
    {
    case 0:
        adddays = 2;                // Sonntag, Ganztags                        -> Lieferung Dienstags
        break;
    case 5:
        if( currenttime < 1300 )
            adddays = 3;            // Freitag, vor 13:00 Uhr                   -> Lieferung 3 Tage sp�ter (Montags)
        else
            adddays = 4;            // Freitag, ab  13:00 Uhr                   -> Lieferung 4 Tage sp�ter (Dienstags)
        break;
    case 6:
        adddays = 3;
        break;                      // Samstag, Ganztags                        -> Lieferung Dienstags
    case 1:
    case 2:
    case 3:
    case 4:
    default:
        if( currenttime < 1300 )
            adddays = 1;            // Montag - Donnerstag, vor 13:00 Uhr       -> Lieferung am Folgetag
        else
            adddays = 2;            // Montag - Donnerstag, ab  13:00 Uhr       -> Lieferung 2 Tage sp�ter
        break;
    }

    retval = retval.add( adddays );
    retval = TourUtil::getDateTime( retval.GetYYYYMMDD(), 800 );

    s << "Adding Days[" << adddays << "] Result[" << retval.GetYYYYMMDD() << "] ";
    TourUtil::writeLogINFO(s);

    return retval;
}

/***************************************************************************************************************************/
void TourManager::determineIBTTour()
{
    std::stringstream ibtlog;
    std::stringstream s;
    s << "TM:determineIBTTour IBTB[" << m_ArgIBTBranchNo << "] ";

    m_TourInfo.init();
    this->m_ArgDesiredTourId = "";
    short requestedibtbranchno = this->m_ArgIBTBranchNo;

    // determine ibt branch configuration
    if( this->m_OrderEntryParam->IsNlevelIBT() )
    {
        this->getIBTBranchesList()->getIBTBranchesByNLevelIBTType( this->m_BranchNo, requestedibtbranchno, this->m_ArgNLevelIBTType );
    }
    else
    {
        this->getIBTBranchesList()->getIBTBranchesByIBTType( this->m_BranchNo, requestedibtbranchno, (pxArtFiliale::IBTProduct) this->m_ArgIBTTypeArticle );
    }

    if( 0 == this->getIBTBranchesList()->Entries() )
    {
        s << "NoIBTConfig!!! ExternalError CMSG_ORD_ROUTE_NOIBTCONFIGURATION";
        TourUtil::writeLogINFO(s);
        ExternalError(m_Session->CMsgStream(), CMSG_ORD_ROUTE_NOIBTCONFIGURATION );
        this->setTourInfoError( CMSG_ORD_ROUTE_NOIBTCONFIGURATION );
        return;
    }

    this->m_ArgAcceptAutoAssignableToursOnly = true;

    // determine tour
    bool ibttourfound = false;
    IBTBranchesListIter iter(*this->getIBTBranchesList());
    IBTBranches* ibtb = NULL;
    long lastibtcustomerno = 0;
    short lastibttype = 0;

    TourInfo shuttleTourInfo;
    shuttleTourInfo.init();

    while( ( ibtb = (IBTBranches*)++iter) != NULL )
    {
        if( ibtb->getIBTBranchNo() != requestedibtbranchno )
        {
            continue;
        }

        m_TourInfo.init();
        lastibtcustomerno = ibtb->getIBTCustomerNo();
        lastibttype = ibtb->getIBTType();
        s << "TM:determineIBTTour IBTTyp[" << lastibttype << "] IDF[" << lastibtcustomerno << "] ";

        // special handling for private assortment Germany
        if( 27 == requestedibtbranchno && m_Session->isGermany() ) // PPE Verbundtour Spezialit�t
        {
            // search customer tour with offset of ibt delivery to local branch
            nDate deliverydate = getDeliveryDateTimePPE();
            s << "IBT-PPE-Delivery! DelDat[" << TourUtil::getReadableDateTime( deliverydate ) << "] ";
            this->m_ArgUseTimeOffset = true;
            this->m_ArgTimeOffset = deliverydate;
            this->m_ArgIBTTourDetermination = false;
            this->injectDeliveryDate( deliverydate ); // no day ibt! use next day!
            this->determineLocalTour();
            if( this->m_TourInfo.getTourFound() )
            {
                this->m_TourInfo.setIBTBranchNo( requestedibtbranchno );
                this->m_TourInfo.setIBTCustomerNo( ibtb->getIBTCustomerNo() );
                this->m_TourInfo.setIBTType( ibtb->getIBTType() );
                ibttourfound = true;

                s << "OK! ";
                TourUtil::writeLogINFO(s, true);

                break;
            }

            s << "Not OK! ";
            TourUtil::writeLogINFO(s, true);

            break;
        }

        if( ibtb->isDayIBT() ) // day ibt
        {
            s << "DayIBT! ";

            // determine shuttle tour
            TourManager ibttourman( this->m_Session, this->m_OrderNo, requestedibtbranchno, ibtb->getIBTCustomerNo(), this->m_PickingType );
            ibttourman.m_ArgAcceptAutoAssignableToursOnly = true;
            ibttourman.m_ArgInIBTShuttleTourDetermination = true;
            if( isTransportExclusionEnabled() )
            {
                ibttourman.m_ArgArticle = this->m_ArgArticle;
                ibttourman.injectUseTransportExclusion();
            }
            TourInfo ibttourinfo = ibttourman.determineTour();
            if( !ibttourinfo.getTourFound() )
            {
                s << "NoDayIBT NoShuttleTour! ";
                TourUtil::writeLogINFO(s, true);
                continue;
            }
            else
            {
                shuttleTourInfo = ibttourinfo;
                shuttleTourInfo.setIBTBranchNo(requestedibtbranchno);
                shuttleTourInfo.setIBTCustomerNo(ibtb->getIBTCustomerNo());
                shuttleTourInfo.setIBTType(ibtb->getIBTType());
            }

            ibtlog << "O:" << m_OrderNo << " --VB-- SHUTTLE DAYIBT: [" << requestedibtbranchno << "|" << ibtb->getIBTCustomerNo() << "] -> ["
                << ibttourinfo.getTourDate().GetYYYYMMDD() << "/" << ibttourinfo.getTourID()
                << " -> " << ibttourinfo.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() << " "
                << (ibttourinfo.getCustomerDeliveryDateTimeMin().GetHours() * 100) + ibttourinfo.getCustomerDeliveryDateTimeMin().GetMinutes() << "]";
            TourUtil::writeLog(ibtlog);

            if( TourUtil::getCurrentDate().GetYYYYMMDD() != ibttourinfo.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() ) // not today? -> no day ibt
            {
                ibtlog << "O:" << m_OrderNo << " --VB-- KEIN TAGVB - ANKUNFT NICHT HEUTE!";
                TourUtil::writeLog(ibtlog);
                continue;
            }
            s << "ShuttleTour [" << ibttourinfo.getTourID() << "/" << ibttourinfo.getTourDate().GetYYYYMMDD() << "] ";

            // search customer tour with offset of ibt delivery to local branch
            this->m_ArgUseTimeOffset = true;
            this->m_ArgTimeOffset = ibttourinfo.getCustomerDeliveryDateTimeMin();
            this->m_ArgIBTTourDetermination = true;
            this->injectIBTBranchNo(0);
            this->injectDeliveryDate(ibttourinfo.getCustomerDeliveryDateTimeMin());
            this->determineCurrentTour(this->m_ArgArticle); // check current tours first due to >24:00 o�clock tours
            if( !this->m_TourInfo.getTourFound() )
            {
                this->determineLocalTour();
            }
            if( this->m_TourInfo.getTourFound() )
            {
                if( TourUtil::getCurrentDate().GetYYYYMMDD() == this->m_TourInfo.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() )
                {
                    if( this->isInsideBusinessHours( this->m_TourInfo.getCustomerDeliveryDateTimeMin() ) )
                    {
                        this->m_TourInfo.setIBTBranchNo( requestedibtbranchno );
                        this->m_TourInfo.setIBTCustomerNo( ibtb->getIBTCustomerNo() );
                        this->m_TourInfo.setIBTType( ibtb->getIBTType() );
                        this->m_TourInfo.setIBTTourId( ibttourinfo.getTourID() );
                        this->m_TourInfo.setIBTTourDate( ibttourinfo.getTourDate() );
                        this->m_TourInfo.setIBTSameDay(true);
                        ibttourfound = true;
                        s << "OK! DayIBT! ";
                        TourUtil::writeLogINFO(s, true);
                        break;
                    }
                    else
                    {
                        ibtlog << "O:" << m_OrderNo << " --VB-- KEIN TAGVB WEGEN OEFFNUNGSZEITEN!";
                        TourUtil::writeLog(ibtlog);
                    }
                }
            }
        }
        else // no day ibt
        {
            s << "No DayIBT! ";
            TourManager ibttourman( this->m_Session, this->m_OrderNo, requestedibtbranchno, ibtb->getIBTCustomerNo(), this->m_PickingType );
            ibttourman.m_ArgAcceptAutoAssignableToursOnly = true;
            ibttourman.m_ArgInIBTShuttleTourDetermination = true;
            if( isTransportExclusionEnabled() )
            {
                ibttourman.m_ArgArticle = this->m_ArgArticle;
                ibttourman.injectUseTransportExclusion();
            }
            if( this->m_OrderEntryParam->DelayedDays() > 0 )
            {
                nDate deldate = TourUtil::getCurrentDate();
                deldate = deldate.add( this->m_OrderEntryParam->DelayedDays() );
                ibttourman.injectDeliveryDate( deldate );
                s << "DelayedDays added [" << deldate.GetYYYYMMDD() << "] ";
            }
            TourInfo ibttourinfo = ibttourman.determineTour();
            if( !ibttourinfo.getTourFound() )
            {
                s << "No ShuttleTour found!";
                TourUtil::writeLogINFO(s,true);
                continue;
            }
            else
            {
                shuttleTourInfo = ibttourinfo;
                shuttleTourInfo.setIBTBranchNo(requestedibtbranchno);
                shuttleTourInfo.setIBTCustomerNo(ibtb->getIBTCustomerNo());
                shuttleTourInfo.setIBTType(ibtb->getIBTType());
            }
            s << "ShuttleTour [" << ibttourinfo.getTourID() << "/" << ibttourinfo.getTourDate().GetYYYYMMDD() << "] ";

            ibtlog << "O:" << m_OrderNo << " --VB-- SHUTTLE IBT: [" << requestedibtbranchno << "|" << ibtb->getIBTCustomerNo() << "] -> ["
                << ibttourinfo.getTourDate().GetYYYYMMDD() << "/" << ibttourinfo.getTourID()
                << " -> " << ibttourinfo.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() << " "
                << (ibttourinfo.getCustomerDeliveryDateTimeMin().GetHours() * 100) + ibttourinfo.getCustomerDeliveryDateTimeMin().GetMinutes() << "]";
            TourUtil::writeLog(ibtlog);

            // search customer tour with offset of ibt delivery to local branch
            nDate deliverydate = ibttourinfo.getCustomerDeliveryDateTimeMin();
            this->m_ArgTimeOffset = ibttourinfo.getCustomerDeliveryDateTimeMin();
            this->m_ArgUseTimeOffset = true;
            this->m_ArgIBTTourDetermination = true;
            this->injectIBTBranchNo(0);
            this->injectDeliveryDate( deliverydate );

            this->determineCurrentTour(this->m_ArgArticle); // check current tours first due to >24:00 o�clock tours
            if( !this->m_TourInfo.getTourFound() )
            {
                this->m_ArgTimeOffset = ibttourinfo.getCustomerDeliveryDateTimeMin();
                this->m_ArgUseTimeOffset = true;
                this->m_ArgIBTTourDetermination = true;
                this->injectIBTBranchNo(0);
                this->injectDeliveryDate( deliverydate );
                this->m_ArgForceTimeOffsetUsage = true;
                this->determineLocalTour();
                this->m_ArgForceTimeOffsetUsage = false;
            }
            if( this->m_TourInfo.getTourFound() )
            {
                this->m_TourInfo.setIBTBranchNo(requestedibtbranchno);
                this->m_TourInfo.setIBTCustomerNo(ibtb->getIBTCustomerNo());
                this->m_TourInfo.setIBTType(ibtb->getIBTType());
                this->m_TourInfo.setIBTTourId(ibttourinfo.getTourID());
                this->m_TourInfo.setIBTTourDate(ibttourinfo.getTourDate());
				ibttourfound = true;    // Kundentour mit Verbund-Kennzeichen gefunden

                if ( m_OrderEntryParam->IsUseLatestIbtTour() )
                {
                    TourInfo ibttourinfo2;
                    ibttourman.injectLatestPossibleTourSearch(true, this->m_TourInfo.getTourDepartureDateTime());
                    ibttourinfo2 = ibttourman.determineTour();
                    if (ibttourinfo2.getTourFound())
                    {
                        shuttleTourInfo = ibttourinfo2;
                        shuttleTourInfo.setIBTBranchNo(requestedibtbranchno);
                        shuttleTourInfo.setIBTCustomerNo(ibtb->getIBTCustomerNo());
                        shuttleTourInfo.setIBTType(ibtb->getIBTType());
                    }
                }

                s << "Tour found!";
                TourUtil::writeLogINFO(s,true);
                break;
            }
        }
        s << "NoTour? ";
        TourUtil::writeLogINFO(s,true);
    }

    if( !ibttourfound )
    {
        if( !(m_OrderEntryParam->IsUseTourManagerWithTransportExclusion() && this->isArticleWithSpecialDeliveryConditions(this->m_ArgArticle)) )
        {
            s << "No customer tour with IBT-flag found! ";
            // search customer tour with offset of next day
            m_TourInfo.init();
            this->m_ArgUseTimeOffset = false;
            this->m_ArgIBTTourDetermination = false;
            this->injectIBTBranchNo(0);
            if( this->m_OrderEntryParam->DelayedDays() > 0 )
            {
                nDate deldate = TourUtil::getCurrentDate();
                deldate = deldate.add( this->m_OrderEntryParam->DelayedDays() );
                this->injectDeliveryDate( deldate );
                s << "DelayedDays added [" << deldate.GetYYYYMMDD() << "] ";
            }
            else if ( shuttleTourInfo.getTourFound() )
            {
                nDate deliveryDate = shuttleTourInfo.getCustomerDeliveryDateTimeMin();
                this->injectDeliveryDate( deliveryDate.add(1) );
            }
			else
			{
				this->injectDeliveryDate( TourUtil::getCurrentDate().add(1) );
			}

            this->determineLocalTour();
        }
    }

    if( this->m_OrderEntryParam->IsNlevelIBT() )
    {
        this->m_TourInfo.setIBTType( this->m_ArgNLevelIBTType );
    }

    if( this->m_TourInfo.getTourFound() )
    {
        this->m_TourInfo.setIBTBranchNo(shuttleTourInfo.getIBTBranchNo());
        this->m_TourInfo.setIBTCustomerNo(shuttleTourInfo.getIBTCustomerNo());
        this->m_TourInfo.setIBTType(shuttleTourInfo.getIBTType());
        this->m_TourInfo.setIBTTourId(shuttleTourInfo.getTourID());
        this->m_TourInfo.setIBTTourDate(shuttleTourInfo.getTourDate());
        s << "Tour found!";
        resetError();
    }
    else
    {
        s << "No Tour found!";
    }
    TourUtil::writeLogINFO(s);

    this->m_ArgAcceptAutoAssignableToursOnly = false;
}

/***************************************************************************************************************************/
CustomerTour* TourManager::getNextAssignableTour(const nString& tourid)
{
    CustomerTour* tour = NULL;
    CustomerTourListIter iter(*m_CustomerToursCurrent);
    while( (tour = (CustomerTour*)++iter) != NULL )
    {
        if( this->m_ArgNoCheckForTransitionTimesAndPickingDurations )
        {
            tour->injectNoCheckForTransitionTimesAndPickingDurations(true);
        }

        if( tour->getTourId() != tourid )
        {
            continue;
        }

        if( !tour->isAssignable() )
        {
            continue;
        }

        break;
    }
    return tour;
}

/***************************************************************************************************************************/
CustomerTour* TourManager::getTour(const nString& tourid)
{
    resetError();
    loadTours();

    CustomerTour* tour = NULL;
    CustomerTourListIter iter(*m_CustomerToursCurrent);
    while( (tour = (CustomerTour*)++iter) != NULL )
    {
        if( this->m_ArgNoCheckForTransitionTimesAndPickingDurations )
        {
            tour->injectNoCheckForTransitionTimesAndPickingDurations(true);
        }
        if( tour->getTourId() != tourid )
        {
            continue;
        }
        break;
    }
    return tour;
}

/***************************************************************************************************************************/
CustomerTour* TourManager::getTourForWeekday(const nString& tourid, const TourUtil::WeekDayEnum weekday)
{
    CustomerTour* tour = NULL;
    CustomerTourListIter iter(*m_CustomerToursWeek);
    while( (tour = (CustomerTour*)++iter) != NULL )
    {
        if( this->m_ArgNoCheckForTransitionTimesAndPickingDurations )
        {
            tour->injectNoCheckForTransitionTimesAndPickingDurations(true);
        }

        if( tour->getTourId() != tourid )
        {
            continue;
        }

        if( tour->getWeekDay() == weekday )
        {
            break;
        }
    }
    return tour;
}

/***************************************************************************************************************************/
bool TourManager::isCoolArticle( pxArtBase* article ) const
{
    if( NULL != article )
    {
        if( article->ArtFlags().IsKuehlKette() )
        {
            return true;
        }
    }
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isCoolBelow8Article( pxArtBase* article ) const
{
    if( NULL != article )
    {
        if( article->ArtFlags().IsGekuehlt08() )
        {
            return true;
        }
    }
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isCoolBelow20Article( pxArtBase* article ) const
{
    if( NULL != article )
    {
        if( article->ArtFlags().IsGekuehlt20() )
        {
            return true;
        }
    }
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isPsychotropicArticle( pxArtBase* article ) const
{
    if (NULL != article)
    {
        if (article->IsKzPsychoStoffe())
        {
            return true;
        }
    }
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isCurrentTourValid(const nString& tourid, const pxCommType* pickingtype, const bool closeorder /* = false */,
    const bool checkDurationsAndTransitionTimes /* = true */)
{
    std::stringstream s;
    s << "TM:isCurrentTourValid Tour[" << tourid << "] ";
    if( closeorder ) s << "CO! ";

    CustomerTour* tour = NULL;
    if( closeorder )
    {
        tour = getTour( tourid );
    }
    else
    {
        tour = getNextAssignableTour(tourid);
    }

    if( NULL == tour )
    {
        ExternalError(m_Session->CMsgStream(), CMSG_ORD_ROUTE_INVALID, (char*)tourid);
        this->setTourInfoError( CMSG_ORD_ROUTE_INVALID );
        s << "ExternalError CMSG_ORD_ROUTE_INVALID";
        TourUtil::writeLogINFO(s);
        return false;
    }

    if( this->m_ArgNoCheckForTransitionTimesAndPickingDurations )
    {
        tour->injectNoCheckForTransitionTimesAndPickingDurations(true);
    }

    if( NULL != this->m_PickingType )  // OK
    {
        if( this->m_PickingType->IsNoShipment() ) // OK
        {
            return true;
        }
    }

    if( tour->hasExpired(pickingtype, checkDurationsAndTransitionTimes) )
    {
        ExternalError(m_Session->CMsgStream(), CMSG_ORD_ROUTE_TIMEOFF, (char*)tourid);
        this->setTourInfoError( CMSG_ORD_ROUTE_TIMEOFF );
        s << "ExternalError CMSG_ORD_ROUTE_TIMEOFF";
        TourUtil::writeLogINFO(s);
        return false;
    }

    return true;
}

/***************************************************************************************************************************/
bool TourManager::isDeliveryDateInTheFuture() const
{
    if( this->m_ArgDeliveryDate == TourUtil::getNullDate() )
    {
        return false;
    }
    if( this->m_ArgDeliveryDate > TourUtil::getCurrentDate() )
    {
        return true;
    }
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isInsideBusinessHours(const nDate& datetime)
{
    if (   ( NULL != this->getCustomer()->getCustomerBusinessHoursList() )
        && this->getCustomer()->getCustomerBusinessHoursList()->isInsideBusinessHours( datetime ) )
    {
        return true;
    }
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isNarcoticArticle( pxArtBase* article ) const
{
    if ((NULL != article) && article->ArtClass().IsOpiat())
    {
        return true;
    }
    return false;
}

/***************************************************************************************************************************/
bool TourManager::isUpcomingTourValid(const nString& tourid, const nDate& deliverydate)
{
    if( !m_Session->isBulgaria() ) { return true;  } // only checked for Bulgaria

    TourUtil::WeekDayEnum weekday = TourUtil::getWeekDay(deliverydate.GetDayOfWeek());
    CustomerTour* tour = getTourForWeekday(tourid, weekday);
    if( NULL == tour )
    {
        ExternalError(m_Session->CMsgStream(), CMSG_ORD_ROUTE_INVALID, (char*)tourid);
        this->setTourInfoError( CMSG_ORD_ROUTE_INVALID );
        std::stringstream s;
        s << "TM:isUpcomingTourValid Tour[" << tourid << "/" << deliverydate.GetYYYYMMDD() << "] ExternalError CMSG_ORD_ROUTE_INVALID";
        TourUtil::writeLogINFO(s);
        return false;
    }
    return true;
}

/***************************************************************************************************************************/
void TourManager::checkDesiredTourExistence()
{
    loadTours();
    if( !m_ArgDesiredTourId.IsEmpty() )
    {
        // remove desired TOURID if it�s not available in the customer�s tours
        if( !m_CustomerToursWeek->isTourAvailable( m_ArgDesiredTourId ) )
        {
            if( !m_CustomerToursCurrent->isTourAvailable( m_ArgDesiredTourId ) )
            {
                m_ArgDesiredTourId = "";
                std::stringstream s;
                s << "TM:checkDesiredTourExistence Tour[" << m_ArgDesiredTourId << "] Removed! Not available for Customer!";
                TourUtil::writeLogINFO(s);
            }
        }

        // remove desired TOURID for the current date if departure is on a public holiday
        if( TourUtil::getCurrentDate().GetYYYYMMDD() == this->m_ArgDeliveryDate.GetYYYYMMDD() )
        {
            if( m_CustomerToursCurrent->Entries() > 0 )
            {
                CustomerTour* ct = NULL;
                CustomerTourListIter iter(*m_CustomerToursCurrent);
                while ( (ct = (CustomerTour*)++iter) != NULL )
                {
                    if( ct->isDepartureOnPublicHoliday() )
                    {
                        m_ArgDesiredTourId = "";
                        std::stringstream s;
                        s << "TM:checkDesiredTourExistence Tour[" << m_ArgDesiredTourId << "] Removed! Not available for Current Date due to public holiday on DepartureDate!";
                        TourUtil::writeLogINFO(s);
                    }
                }
            }
        }

    }
}

/***************************************************************************************************************************/
void TourManager::loadTours()
{
    // check if the shuttle customer has to be used
    checkShuttleCustomer();

    long customerno = m_CustomerNo;
    if( m_ShuttleCustomerNo > 0 )
    {
        customerno = m_ShuttleCustomerNo;
        std::stringstream s;
        s << "TM:loadTours using ShuttleCustomer[" << customerno << "]!";
        TourUtil::writeLogINFO(s);
    }

    if( !m_ToursLoaded )
    {
        if( NULL != m_CustomerToursCurrent )
        {
            delete m_CustomerToursCurrent;
            m_CustomerToursCurrent = NULL;
        }

        if( NULL != m_CustomerToursWeek )
        {
            delete m_CustomerToursWeek;
            m_CustomerToursWeek = NULL;
        }

        m_CustomerToursCurrent = new CustomerTourList(m_Session, m_BranchNo, customerno); // get tours for today
        if( !m_CustomerToursCurrent->getCurrentTours(m_OrderType) )
        {
            std::stringstream s;
            s << "TM:loadTours getCurrentTours failed for branchno " << m_BranchNo << " and customerno " << customerno << "!";
            TourUtil::writeLogINFO(s);
        }

        m_CustomerToursWeek = new CustomerTourList(m_Session, m_BranchNo, customerno); // get all tours
        if( !m_CustomerToursWeek->getTours(m_OrderType) )
        {
            std::stringstream s;
            s << "TM:loadTours getTours failed for branchno " << m_BranchNo << " and customerno " << customerno << "!";
            TourUtil::writeLogINFO(s);
        }

        m_ToursLoaded = true;
    }
}

/***************************************************************************************************************************/
bool TourManager::useOrderTypeSpecificTour()
{
    m_TourInfo.init();
    nString tourid = this->getOrderTypeSpecificTour();
    if( tourid.IsEmpty() )
    {
        return false;
    }

    CustomerTourList tourlist( m_Session, m_BranchNo, m_CustomerNo);
    if( !tourlist.getCurrentTour(tourid) )
    {
        if( !tourlist.getTour(tourid) )
        {
            return false;
        }
    }
    tourlist.removeExpiredTours(m_PickingType); // OK
    tourlist.removeUnassignableTours();

    if( tourlist.Entries() > 0 )
    {
        CustomerTour* ct = NULL;
        CustomerTourListIter iter(tourlist);
        while( (ct = (CustomerTour*)++iter) != NULL )
        {
            if( !ct->hasExpired(m_PickingType) && ct->isAssignable() ) // OK
            {
                transferCustomerTour2TourInfo( ct );
                std::stringstream s;
                s << "TM:useOrderTypeSpecificTour!";
                TourUtil::writeLogINFO(s);
                return true;
            }
        }
    }

    return false;
}

/***************************************************************************************************************************/
TourInfo TourManager::getCustomerTourAsTourInfo(const CustomerTour* ct, const nDate& date /*= TourUtil::getNullDate()*/) const
{
    nDate datetouse(date);
    if( datetouse != TourUtil::getNullDate() )
    {
        if( datetouse.GetYYYYMMDD() < TourUtil::getCurrentDate().GetYYYYMMDD() )
        {
            datetouse = TourUtil::getCurrentDate();
        }
    }

    TourInfo retval;
    retval.setTourID(ct->getTourId());
    retval.setDrivingDuration(ct->getDrivingDuration());
    retval.setTourDate(ct->getPickingDate());
    retval.setPickingType(ct->getPickingType());
    retval.setDeliveryTimeBuffer(ct->getDeliveryTimeBuffer());
    retval.setTourDepartureDateTime( ct->getTourDepartureDateTime( datetouse ) );
    retval.setTourDepartureDateTimeNormalized( ct->getTourDepartureDateTime( datetouse ) );
    retval.setCustomerDeliveryDateTimeMin( ct->getTourDeliveryDateTimeMin( datetouse ) );
    retval.setCustomerDeliveryDateTimeMax( ct->getTourDeliveryDateTimeMax( datetouse ) );
    retval.setTourClosingDateTime( ct->getTourClosingDateTime( m_PickingType, datetouse ) );
    retval.setTourClosingDateTimeAvailable(true);
    retval.setLagRechTour( ct->getLagRechTour() );
    retval.setTourFound( true );
    if( TourUtil::getNullDate() != datetouse )
    {
        retval.setTourDate( datetouse );
    }
    return retval;
}

/***************************************************************************************************************************/
void TourManager::transferCustomerTour2TourInfo(const CustomerTour* ct, const nDate& date /*= TourUtil::getNullDate()*/ )
{
    nDate datetouse(date);
    if( datetouse != TourUtil::getNullDate() )
    {
        if( datetouse.GetYYYYMMDD() < TourUtil::getCurrentDate().GetYYYYMMDD() )
        {
            datetouse = TourUtil::getCurrentDate();
        }
    }

    m_TourInfo.setTourID(ct->getTourId());
    m_TourInfo.setDrivingDuration(ct->getDrivingDuration());
    m_TourInfo.setTourDate(ct->getPickingDate());
    m_TourInfo.setPickingType(ct->getPickingType());
    m_TourInfo.setDeliveryTimeBuffer(ct->getDeliveryTimeBuffer());
    m_TourInfo.setLagRechTour( ct->getLagRechTour() );
    m_TourInfo.setTourDepartureDateTime( ct->getTourDepartureDateTime( datetouse ) );
    m_TourInfo.setTourDepartureDateTimeNormalized( ct->getTourDepartureDateTime( datetouse ) );
    m_TourInfo.setCustomerDeliveryDateTimeMin( ct->getTourDeliveryDateTimeMin( datetouse ) );
    m_TourInfo.setCustomerDeliveryDateTimeMax( ct->getTourDeliveryDateTimeMax( datetouse ) );
    m_TourInfo.setTourClosingDateTime( ct->getTourClosingDateTime( m_PickingType, datetouse ) );
    m_TourInfo.setTourClosingDateTimeAvailable(true);
    m_TourInfo.setTourFound( true );
    if( TourUtil::getNullDate() != datetouse )
    {
        m_TourInfo.setTourDate( datetouse );
    }
}

/***************************************************************************************************************************/
CSCCustomer* TourManager::getCustomer()
{
    if( NULL != this->m_Customer )
    {
        // customer instance does not belong to the correct branch
        if( this->m_Customer->getBranchNo() != this->m_BranchNo )
        {
            delete this->m_Customer;
            this->m_Customer = NULL;
        }

        // customer instance does not contain the correct customer
        if( this->m_ShuttleCustomerNo > 0 )
        {
            if( this->m_Customer->getCustomerNo() != this->m_ShuttleCustomerNo )
            {
                delete this->m_Customer;
                this->m_Customer = NULL;
            }
        }
        else
        {
            if( this->m_Customer->getCustomerNo() != this->m_CustomerNo )
            {
                delete this->m_Customer;
                this->m_Customer = NULL;
            }
        }
    }

    if( NULL == this->m_Customer )
    {
        if( this->m_ShuttleCustomerNo > 0 )
        {
            this->m_Customer = new CSCCustomer( this->m_Session, this->m_BranchNo, this->m_ShuttleCustomerNo );
        }
        else
        {
            this->m_Customer = new CSCCustomer( this->m_Session, this->m_BranchNo, this->m_CustomerNo );
        }
        this->m_Customer->Read();
    }

    return this->m_Customer;
}

/***************************************************************************************************************************/
IBTBranchesList* TourManager::getIBTBranchesList()
{
    if( NULL == this->m_IBTBranchesList )
    {
        this->m_IBTBranchesList = new IBTBranchesList( this->m_Session );
    }
    return this->m_IBTBranchesList;
}

/***************************************************************************************************************************/
nString TourManager::serializeArgs() const
{
    short ibttype = this->m_ArgIBTTypeArticle;
    if( this->m_OrderEntryParam->IsNlevelIBT() )
    {
        ibttype = this->m_ArgNLevelIBTType;
    }

    std::stringstream s;
    s << "CSC:" << this->m_OrderNo;
    s << " FI:" << this->m_BranchNo;
    s << " IDF:" << this->m_CustomerNo;
    s << " AA:" << static_cast<const char* const>(this->m_OrderType);
    s << " OFFSET(" << this->m_ArgUseTimeOffset << "):" << (long)((this->m_ArgTimeOffset.GetHours() * 100) + this->m_ArgTimeOffset.GetMinutes());

    if( NULL != this->m_ArgArticle ) s << " PZN:" << this->m_ArgArticle->ArtikelNr();
    if( this->m_ArgIBTBranchNo > 0 ) s << " IBTFI:" << this->m_ArgIBTBranchNo << "(" << ibttype << ")";
    if( this->m_ArgIBTTourDetermination ) s << " IBTDet";
    if( !TourUtil::isNullOrCurrentDate( this->m_ArgDeliveryDate ) ) s << " Date:" << TourUtil::getReadableDateTime( this->m_ArgDeliveryDate );
    if( !m_ArgDesiredTourId.IsEmpty() ) s << " Desired:" << static_cast<const char* const>(this->m_ArgDesiredTourId);
    if( m_ArgAcceptAutoAssignableToursOnly ) s << " AAOnly";
    if( m_ArgNoCheckForTransitionTimesAndPickingDurations ) s << " NoPickTransCheck!";
    if( m_ArgInIBTShuttleTourDetermination ) s << " IBTShuttleDet!";
    if( m_ArgNotEarlierThanOrderTour ) s << " NotEarlierThanOrder!";
    if( m_ArgOrderTourDate != TourUtil::getNullDate() ) s << " OrderTourDate:" << m_ArgOrderTourDate.GetYYYYMMDD();
    if( "" != m_ArgOrderTourID ) s << " OrderTourID:" << static_cast<const char* const>(m_ArgOrderTourID);
    if (m_ArgReturnsToursOnly) s << " ReturnsTourOnly";

    char tmp[1024] = {' '};
    sprintf( tmp, "%s", s.str().c_str() );
    nString retval(tmp);
    return retval;
}

/***************************************************************************************************************************/
void TourManager::resetError()
{
    m_TourInfo.setError(0);
    ClearError();
}


/***************************************************************************************************************************/
/*static*/ pxOrderPeriod TourManager::getCurrentMSV3OrderPeriod(pxSession* session, const short branchno, const long customerno)
{
    const pxOrderEntryParamPtr oeparam = session->getOrderEntryParam(branchno);
    short orderPeriodTourAssignment = oeparam->OrderPeriodTourAssignment();
    short tourWeekDay = oeparam->TourWeekDay();

    pxOrderPeriod retval(session);
    pxOrderPeriodList* orderperiodlist = new pxOrderPeriodList(session);

    if( 1 == orderPeriodTourAssignment )
    {
        retval = orderperiodlist->getCurrentOrderPeriod( branchno, customerno, tourWeekDay );

        // check if weekday of order period is a public holiday
        pxHoliDayList* holidaylist = session->HoliDayList(branchno);
        nDate dateforTourWeekday = TourUtil::getDateForNextWeekdayOccurrence(retval.WeekDay());
        if( holidaylist->CheckDateForHoliday( dateforTourWeekday, branchno ) )
        {
            tourWeekDay = nDate(holidaylist->CalculateNextWorkDay( dateforTourWeekday, branchno )).GetDayOfWeek();
            retval = orderperiodlist->getFirstOrderPeriodByWeekday(branchno, customerno, tourWeekDay);
        }
    }
    else
    {
        retval = orderperiodlist->getCurrentOrderPeriodID( branchno, customerno );
    }

    return retval;
}

/***************************************************************************************************************************/
void TourManager::setTourInfoError(const int value)
{
    m_TourInfo.setError( value );

    std::stringstream s;
    s << "TM:setTourInfoError " << value;
    TourUtil::writeLogINFO( s );
}
/***************************************************************************************************************************/
bool TourManager::isArrivalBefore(CustomerTour* ct, nDate dateToCheck)
{
    if (TourUtil::getNullDate() == dateToCheck)
    {
        return false;
    }
    std::stringstream s;
    if (ct->getTourDeliveryDateTimeMin().GetYYYYMMDD() > dateToCheck.GetYYYYMMDD())
    {
        s.str(std::string());
        s << "TM:CustTour DeliveryDate:[" << ct->getTourDeliveryDateTimeMin().GetYYYYMMDD() << "] is greater than latest arrival date [" << dateToCheck.GetYYYYMMDD() << "] so isArrivalBefore returns FALSE ";
        TourUtil::writeLogINFO(s);
        return false;
    }
    if (ct->getTourDeliveryDateTimeMin().GetYYYYMMDD() < dateToCheck.GetYYYYMMDD())
    {
        s.str(std::string());
        s << "TM:CustTour DeliveryDate:[" << ct->getTourDeliveryDateTimeMin().GetYYYYMMDD() << "] is less than latest arrival date [" << dateToCheck.GetYYYYMMDD() << "] so isArrivalBefore returns TRUE ";
        TourUtil::writeLogINFO(s);
        return true;
    }

    long timeToCheck = (dateToCheck.GetHours() * 10000) + (dateToCheck.GetMinutes() * 100) + dateToCheck.GetSeconds();
    long timeArrival = (ct->getTourDeliveryDateTimeMin().GetHours() * 10000) + (ct->getTourDeliveryDateTimeMin().GetMinutes() * 100) + ct->getTourDeliveryDateTimeMin().GetSeconds();
    if (timeArrival > timeToCheck)
    {
        s.str(std::string());
        s << " timeArrival " << timeArrival << " is greater then timeToCheck " << timeToCheck << " so isArrivalBefore return False " ;
        TourUtil::writeLogINFO(s);
        return false;
    }

    return true;
}


/***************************************************************************************************************************/
bool TourManager::isNotEarlierThanOrderTour( CustomerTour* ct )
{
    // no check if the parameter is not set
    if( !m_ArgNotEarlierThanOrderTour )
        return true;

    // tourdate and tourid are not set
    if( m_ArgOrderTourDate == TourUtil::getNullDate() && "" == m_ArgOrderTourID )
        return true;

    // date for comparison:
    long orderdate = TourUtil::getCurrentDate().GetYYYYMMDD();
    if( m_ArgOrderTourDate != TourUtil::getNullDate() )
        orderdate = m_ArgOrderTourDate.GetYYYYMMDD();
    long ordertour = TourUtil::getTourIdAsHHMM(m_ArgOrderTourID);

    long tourdate = ct->getTourDepartureDateTime().GetYYYYMMDD();
    long tourid = TourUtil::getTourIdAsHHMM(ct->getTourId());

    // if tour�s date is the same as the tourdate of the order, check the tourid
    if( tourdate == orderdate )
    {
        if( tourid >= ordertour )
        {
            return true;
        }
        return false;
    }

    // if tour�s date is greater than the tourdate of the order there is no need to check the tourid
    if( tourdate > orderdate )
    {
        return true;
    }

    // should never happen, this would mean that there is a tour that was in the past
    return false;
}

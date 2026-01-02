#include "tourassignmentutil.hpp"
#include "tourutil.hpp"
#include "tourmanager.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcstot.hpp"
#include "pxcustrouting.hpp"
#include "pxcomtyp.hpp"
#include "customertour.hpp"
#include "csccustomer.hpp"
#include "pxoeparm.hpp"
#include "pxorder.hpp"
#include "pxartbas.hpp"
#include "pxorderitemtour.hpp"
#include <libbasarcmnutil_bstring.h>
#include <logger/loggerpool.h>
#include <sstream>
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/***************************************************************************************************************************/
TourAssignmentUtil::TourAssignmentUtil( pxOrder* order )
    : m_Order( order )
{
    m_TourManager = NULL;
    m_TourManager4CustomerRouting = NULL;

    m_TourInfoBTM = TourInfo();
    m_TourInfoKK = TourInfo();
    m_TourInfoK8 = TourInfo();
    m_TourInfoK20 = TourInfo();

    resetInjections();
}

/***************************************************************************************************************************/
TourAssignmentUtil::~TourAssignmentUtil()
{
    m_Order = NULL;             // don´t delete order object!

    if( NULL != m_TourManager )
    {
        delete m_TourManager;
        m_TourManager = NULL;
    }

    if( NULL != m_TourManager4CustomerRouting )
    {
        delete m_TourManager4CustomerRouting;
        m_TourManager4CustomerRouting = NULL;
    }
}

/***************************************************************************************************************************/
int TourAssignmentUtil::assignItemTour( pxOrderItem* item )
{
    m_LastTourInfo = TourInfo();
    m_Order->ClearError();

    std::stringstream s;
    s << "TAU:assignItemTour OrdPos[" << item->KdAuftragNr() << "|" << item->PosNr() << "] ";

    if( !m_Order->IsChangeable() )
    {
        s << "NotChangeable! ";
        TourUtil::writeLogINFO(s);
        return m_Order->ErrorState();
    }

    if( !m_Order->IsEntryInProgress() )
    {
        setErrorMessage( CMSG_ORD_ROUTE_NOENTRY );
        s << "NotInProgress! CMSG_ORD_ROUTE_NOENTRY";
        TourUtil::writeLogINFO(s);
        return m_Order->ErrorState();
    }
    TourUtil::writeLogINFO(s);


    m_LastTourInfo.setTourFound(false);
    // Wurde schon eine Tour für den Artikeltyp ermittelt? Dann diesen weiter verwenden!
    if( !m_Order->Session()->Device()->IsVideo() && 0 == m_ArgIBTBranchNo && NULL != m_ArgArticle )
    {
        if( m_TourInfoBTM.getTourFound() && isArticleNarcoticOnly()   ) m_LastTourInfo = m_TourInfoBTM; // rein BTM, kein KK,K8,K20
        if( m_TourInfoBTM.getTourFound() && isArticleCoolChainOnly()  ) m_LastTourInfo = m_TourInfoKK;  // rein KK, kein BTM,K8,K20
        if( m_TourInfoBTM.getTourFound() && isArticleCoolBelow8Only() ) m_LastTourInfo = m_TourInfoK8;  // rein K8, kein BTM,KK,K20
        if( m_TourInfoBTM.getTourFound() && isArticleCoolBelow20Only()) m_LastTourInfo = m_TourInfoK20; // rein K20, kein BTM,KK,K8
    }

    if( !m_LastTourInfo.getTourFound() )
    {
        m_LastTourInfo = determineItemTour(item, false);
    }

    if( m_LastTourInfo.getTourFound() )
    {
        nString tourid = m_LastTourInfo.getTourID();
        if( m_ArgIBTBranchNo > 0 )
        {
            item->SetIBTTourWeekDay( m_LastTourInfo.getTourDate().GetDayOfWeek() );
            item->SetTourIdIBT( tourid );
            item->SetIBTType( m_LastTourInfo.getIBTType() );
        }
        else
        {
            item->SetTourId( tourid );

            // Tour für Artikeltypen merken falls nochmal der gleiche Artikeltyp kommt
            if( NULL != m_ArgArticle && 0 == m_ArgIBTBranchNo )
            {
                if( isArticleNarcoticOnly()   ) m_TourInfoBTM = m_LastTourInfo;
                if( isArticleCoolChainOnly()  ) m_TourInfoKK  = m_LastTourInfo;
                if( isArticleCoolBelow8Only() ) m_TourInfoK8  = m_LastTourInfo;
                if( isArticleCoolBelow20Only()) m_TourInfoK20 = m_LastTourInfo;
            }
        }

        getTourManager()->saveTourInformation(m_Order->KdAuftragNr(), item->PosNr(), m_LastTourInfo);

        if( m_ArgIBTBranchNo > 0 )
        {
            if( NULL != item->m_ItemTourInfoIBT )
            {
                delete item->m_ItemTourInfoIBT;
                item->m_ItemTourInfoIBT = NULL;
            }
            item->m_ItemTourInfoIBT = new TourInfo( m_LastTourInfo );
        }
        else
        {
            if( NULL != item->m_ItemTourInfo )
            {
                delete item->m_ItemTourInfo;
                item->m_ItemTourInfo = NULL;
            }
            item->m_ItemTourInfo = new TourInfo( m_LastTourInfo );
        }

        setErrorMessage( getTourManager()->ErrorNumber() );
    }
    else
    {
        setErrorMessage( getTourManager()->ErrorNumber() );
    }

    return m_Order->ErrorState();
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::hasCustomerRouting()
{
    bool retval = false;

    if( m_Order->Param()->IsSDayNightMerge() )
    {
        pxCustRoutingList* customerroutinglist = new pxCustRoutingList( m_Order->Session() );
        if( customerroutinglist->hasRoutingStartingToday( this->m_Order->FilialNr(), this->m_Order->IDFNr(), m_ArgIBTBranchNo ) )
        {
            std::stringstream s;
            s << "TAU:hasCustomerRouting TRUE!";
            TourUtil::writeLogINFO(s);
            retval = true;
        }
        delete customerroutinglist;
        customerroutinglist = NULL;
    }

    return retval;
}

/***************************************************************************************************************************/
TourInfo TourAssignmentUtil::getNormalDeliveryTour(const nString& tourid, const short weekday /*= -1*/)
{
    std::stringstream s;
    s << "TAU:determineNormalDeliveryTour:";

    TourInfo retval = TourInfo();
    retval.setTourFound(false);

    getTourManager()->resetArgInjections();
    getTourManager()->injectNewOrderFlag( true );
    if( 1 == m_Order->Param()->OrderPeriodTourAssignment() && tourid.Length() > 0 )
    {
        getTourManager()->injectDesiredTourId( tourid );
        if( weekday > -1 && weekday != TourUtil::getCurrentWeekday() ) getTourManager()->injectDeliveryDate( TourUtil::getDateForSubsequentWeekdayOccurrence( weekday ) );
        retval = getTourManager()->determineTour();
        // wenn die Tour aus dem Bestellfenster nicht zugewiesen werden konnte muss die aktuelle Tour verwendet werden!
        if( 1 == m_Order->Param()->OrderPeriodTourAssignment() && TourUtil::getCurrentWeekday() != m_Order->Param()->TourWeekDay() )
        {
            if( retval.getTourFound() && !TourUtil::isNullOrCurrentDate(retval.getTourDate()) )
            {
                retval.setTourFound(false);
            }
        }
        if( !TourUtil::isNullOrCurrentDate(retval.getTourDate() ) ) // Fixe Bindung gilt nur für den aktuellen Tag!!!
        {
            retval.setTourFound(false);
        }
        s << static_cast<const char* const>(retval.serialize());
    }

    if( false == retval.getTourFound() )
    {
        getTourManager()->resetArgInjections();
        getTourManager()->injectNewOrderFlag( true );
        retval = getTourManager()->determineTour();
    }

    s << static_cast<const char* const>(retval.serialize());
    TourUtil::writeLogINFO(s);
    return retval;
}

/***************************************************************************************************************************/
int TourAssignmentUtil::assignTour()
{
    std::stringstream s;
    s << "TAU:assignTour Ord[" << m_Order->KdAuftragNr() << "] ";

    m_LastTourInfo = TourInfo();

    m_Order->ClearError();

    if( !m_Order->IsChangeable() )
    {
        return m_Order->ErrorState();
    }

    if( !m_Order->IsEntryInProgress() )
    {
        setErrorMessage( CMSG_ORD_ROUTE_NOENTRY );
        s << "NotInProgress! CMSG_ORD_ROUTE_NOENTRY";
        TourUtil::writeLogINFO(s);
        return m_Order->ErrorState();
    }

    basar::VarString lasttourid(m_Order->TourId());
    lasttourid.trim(basar::cmnutil::BString::ALL);
    nDate lastdeliverydate = m_Order->DatumAuslieferung();

    if( m_ArgWeekday > -1 )
    {
        m_Order->DatumAuslieferung_ = TourUtil::getDateForSubsequentWeekdayOccurrence( m_ArgWeekday );
    }

    getTourManager()->resetArgInjections();
    if( m_Order->IsNewOrder() ){ getTourManager()->injectNewOrderFlag( true ); }
    getTourManager()->injectDesiredTourId( m_ArgDesiredTourId );
    getTourManager()->injectDeliveryDate( m_Order->DatumAuslieferung() );
    getTourManager()->injectIBTBranchNo( m_ArgIBTBranchNo );
    getTourManager()->injectArticle( m_ArgArticle );
    getTourManager()->injectIBTTypeArticle( m_ArgIBTTypeArticle );
    getTourManager()->injectNoCheckForTransitionTimesAndPickingDurations( m_ArgNoCheckForTransitionTimesAndPickingDurations );
    if( m_Order->Customer()->IsNoSeparate() ){ getTourManager()->injectNoDelayedDelivery(); }
    if( m_Order->getNoDelayedDelivery() ){ getTourManager()->injectNoDelayedDelivery(); }

    if( cORTYPE_AUXILIARY == m_Order->BatchSchreiben() )
    {
        getTourManager()->injectIsOrderFromIBT( true );
    }

    m_LastTourInfo = getTourManager()->determineTour();

    if( m_LastTourInfo.getTourFound() )
    {
        if( getTourManager()->hasToDoTourDetermination() )
        {
            if( TourUtil::getCurrentDate() != m_LastTourInfo.getTourDate() )
            {
                if( m_Order->IsNewOrder() )
                {
                    m_Order->DatumOrg_ = TourUtil::getCurrentDate();
                }
                m_Order->DatumAuslieferung_ = m_LastTourInfo.getTourDate();
            }

            m_Order->OrderTourId_ = m_LastTourInfo.getTourID();
            m_Order->DatumVersand_ = m_LastTourInfo.getTourDate();

            if( m_LastTourInfo.getPickingType() > '0' && m_LastTourInfo.getPickingType() < '9' )
            {
                m_Order->OrderType(m_Order->KdAuftragArt(), m_LastTourInfo.getPickingType(), m_Order->BuchArt());
            }
            getTourManager()->resetTourInformation(m_Order->KdAuftragNr(), 0);
            getTourManager()->saveTourInformation(m_Order->KdAuftragNr(), 0, m_LastTourInfo);
        }

        if( NULL != m_Order->m_TourInfo )
        {
            delete m_Order->m_TourInfo;
            m_Order->m_TourInfo = NULL;
        }
        m_Order->m_TourInfo = new TourInfo( m_LastTourInfo );
    }
    else
    {
        setErrorMessage( getTourManager()->ErrorNumber() );
    }

    basar::VarString currenttourid(m_Order->TourId());
    currenttourid.trim(basar::cmnutil::BString::ALL);

    if( m_Order->Param()->IsUseTourManagerWithTransportExclusion() )
    {
        if( m_Order->AnzPos() > 0 )
        {
            m_Order->updateItemTours();
        }
    }

    return m_Order->ErrorState();
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::changeToUrgentPickingIfNecessary()
{
    if( m_Order->TourId().IsEmpty() )
    {
        return false;
    }

    CustomerTour* ct = getTourManager()->getTour( m_Order->TourId() );
    if( NULL != ct )
    {
        nTime now;
        now -= m_Order->Param()->TourVerspaetung() * TourUtil::SecondsPerMinute;

        nTime pickingTimeNormal( (m_Order->Param()->DurchlaufNormal()  * TourUtil::SecondsPerMinute) + now.GetSecs() );
        if( ct->getPickingTime() >= pickingTimeNormal )
        {
            return true;
        }

        nTime pickingTimeUrgent( (m_Order->Param()->DurchlaufEilbote() * TourUtil::SecondsPerMinute) + now.GetSecs() );
        if( ct->getPickingTime() >=  pickingTimeUrgent )
        {
            m_Order->OrderType( m_Order->KdAuftragArt(), ('0') + ShipUrgent, m_Order->BuchArt() );
            return true;
        }
    }

    return false;
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isArticleDeliverableByArticleNo( const long articleno )
{
    bool retval = true;

    pxArtBase* artbase = pxArtBase::CreateArticle( this->m_Order->Session(), articleno, this->m_Order->FilialNr() );
    if( artbase->IsGoodState() )
    {
        retval = this->isArticleDeliverable( artbase );
    }
    if( artbase )
    {
        delete artbase;
        artbase = NULL;
    }

    return retval;
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isArticleDeliverable( pxArtBase* article )
{
    return getTourManager()->isArticleDeliverable( article );
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isArticleDeliverableForIBT(short ibtbranchno, pxArtBase* article)
{
    if( m_Order->Param()->IsUseTourManagerWithTransportExclusion() )
    {
        return getTourManager()->isArticleDeliverableForIBT(ibtbranchno, article);
    }
    return true;
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isTourValidForDate( const nString& tourid )
{
    bool retval = getTourManager()->isTourValidForDate( tourid, m_Order->DatumAuslieferung() );
    setErrorMessage( getTourManager()->ErrorNumber() );
    return retval;
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isTourValid( const nString& tourid )
{
    bool retval = getTourManager()->isTourValid( tourid, &m_Order->CommType(), m_Order->DatumAuslieferung() );
    setErrorMessage( getTourManager()->ErrorNumber() );
    return retval;
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isTourValidForOrderClosure( const nString& tourid )
{
    if( this->m_Order->DatumAuslieferung() != TourUtil::getNullDate() )
    {
        if( this->m_Order->DatumAuslieferung().GetYYYYMMDD() > TourUtil::getCurrentDate().GetYYYYMMDD() )
        {
            return true;
        }
    }
    bool retval = true;

    if( this->m_ArgNoCheckForTransitionTimesAndPickingDurations )
    {
        retval = getTourManager()->isTourValidForOrderClosure( tourid, &m_Order->CommType(), false );
    }
    else
    {
        retval = getTourManager()->isTourValidForOrderClosure( tourid, &m_Order->CommType(), true );
    }
    setErrorMessage( getTourManager()->ErrorNumber() );

    return retval;
}

/***************************************************************************************************************************/
char TourAssignmentUtil::getPickingTypeForTour( const nString& tourid )
{
    TourInfo ti = getTourManager()->getTourInformation( tourid );
    if( ti.getPickingType() > '0' && ti.getPickingType() < '9' )
    {
        return ti.getPickingType();
    }
    return ' ';
}

/***************************************************************************************************************************/
const TourInfo& TourAssignmentUtil::getLastTourInfo()
{
    return this->m_LastTourInfo;
}

/***************************************************************************************************************************/
TourInfo TourAssignmentUtil::getTourInformation( const long& orderno, const long& lineno, bool ibt /* = false */ )
{
    TourInfo init;

    pxOrderItemTourList* tourlist = getTourManager()->getTourInformation( orderno, lineno );
    pxOrderItemTourListIter iter(*tourlist);
    pxOrderItemTour* oit = NULL;
    while( (oit = (pxOrderItemTour*)++iter ) != NULL )
    {
        if( !ibt )
        {
            if( 0 == oit->getDeliveryBranchNo() )
            {
                TourInfo retval(oit);
                if( !retval.getTourClosingDateTimeAvailable() )
                {
                    retval.setTourClosingDateTime( oit->getTourClosingDateTime( m_Order->FilialNr(), m_Order->IDFNr(), &m_Order->CommType() ) );
                    retval.setTourClosingDateTimeAvailable(true);
                }

                return retval;
            }
        }
        else
        {
            if( oit->getDeliveryBranchNo() > 0 )
            {
                TourInfo retval(oit);
                if( !retval.getTourClosingDateTimeAvailable() )
                {
                    retval.setTourClosingDateTime( oit->getTourClosingDateTime( m_Order->FilialNr(), m_Order->IDFNr(), &m_Order->CommType() ) );
                    retval.setTourClosingDateTimeAvailable(true);
                }
                return retval;
            }
        }
    }
    return init;
}

/***************************************************************************************************************************/
int TourAssignmentUtil::resetItemTourAssignments( pxOrderItem* item )
{
    getTourManager()->resetTourInformation(m_Order->KdAuftragNr(), item->PosNr() );
    return 0;
}

/***************************************************************************************************************************/
void TourAssignmentUtil::saveItemTourInformationFromOrder( const long& lineno )
{
    this->getTourManager()->saveTourInformation( this->m_Order->KdAuftragNr(), lineno, *this->m_Order->getTourInformation() );
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::specialTourPossible( pxArtBase* article )
{
    return this->getTourManager()->specialTourPossible( article );
}

/***************************************************************************************************************************/
void TourAssignmentUtil::removeIBTTourAssignment(pxOrderItem* item)
{
    getTourManager()->removeTourInformationIBT( m_Order->KdAuftragNr(), item->PosNr());
}

/***************************************************************************************************************************/
int TourAssignmentUtil::removeTourAssignments()
{
    m_Order->ClearError();

    if( !m_Order->IsChangeable() )
    {
        return m_Order->ErrorState();
    }

    if( !m_Order->IsEntryInProgress() )
    {
        setErrorMessage( CMSG_ORD_ROUTE_NOENTRY );
        return m_Order->ErrorState();
    }

    m_Order->OrderTourId_.Clear();
    if( m_Order->IsGoodState() )
    {
        m_Order->SetDirty();
    }

    getTourManager()->resetTourInformation( m_Order->KdAuftragNr(), 0 );

    return m_Order->ErrorState();
}

/***************************************************************************************************************************/
void TourAssignmentUtil::injectArticle( pxArtBase* article )
{
    this->m_ArgArticle = article;
}

/***************************************************************************************************************************/
void TourAssignmentUtil::injectDesiredTourId( const nString& tourid )
{
    this->m_ArgDesiredTourId = tourid;
    if( "000000" == this->m_ArgDesiredTourId ) { this->m_ArgDesiredTourId = ""; }
}

/***************************************************************************************************************************/
void TourAssignmentUtil::injectWeekday( const short weekday )
{
    this->m_ArgWeekday = weekday;
}

/***************************************************************************************************************************/
void TourAssignmentUtil::injectIBTBranchNo( const short ibtbranchno )
{
    this->m_ArgIBTBranchNo = ibtbranchno;
}

/***************************************************************************************************************************/
void TourAssignmentUtil::injectIBTTypeArticle( const short& ibttypearticle, const short& nlevelibttype /*= 0*/ )
{
    this->m_ArgIBTTypeArticle = ibttypearticle;
    this->m_ArgNLevelIBTType = nlevelibttype;
}

/***************************************************************************************************************************/
void TourAssignmentUtil::injectOrderPosNo( const long& orderposno )
{
    this->m_ArgOrderPosNo = orderposno;
}

/***************************************************************************************************************************/
void TourAssignmentUtil::injectNoCheckForTransitionTimesAndPickingDurations( const bool b /*= true*/ )
{
    this->m_ArgNoCheckForTransitionTimesAndPickingDurations = b;
}

/***************************************************************************************************************************/
void TourAssignmentUtil::resetInjections()
{
    this->m_ArgDesiredTourId = "";
    this->m_ArgWeekday = -1;
    this->m_ArgIBTBranchNo = 0;
    this->m_ArgArticle = NULL;
    this->m_ArgIBTTypeArticle = 0;
    this->m_ArgOrderPosNo = 0;
    this->m_ArgNLevelIBTType = 0;
    this->m_ArgNoCheckForTransitionTimesAndPickingDurations = false;
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/***************************************************************************************************************************/
TourManager* TourAssignmentUtil::getTourManager()
{
    bool createNewTourManager = false;
    if( NULL == m_TourManager )
    {
        createNewTourManager = true;
    }
    else
    {
        // still the same customer?
        if( m_TourManager->getCustomer()->getCustomerNo() != m_Order->Customer()->IDFNr() )
        {
            createNewTourManager = true;
        }
        // still the same branch?
        if( m_TourManager->getCustomer()->getBranchNo() != m_Order->Customer()->FilialNr() )
        {
            createNewTourManager = true;
        }
    }

    if( createNewTourManager )
    {
        if( NULL != m_TourManager )
        {
            delete m_TourManager; m_TourManager = NULL;
        }
        m_TourManager = new TourManager(    m_Order->Session(),
                                            m_Order->KdAuftragNr(),
                                            m_Order->Customer()->Vertriebszentrum(),
                                            m_Order->Customer()->IDFNr(),
                                            &m_Order->CommType(),
                                            m_Order->OrderType().KdAuftragArt() );
    }

    m_TourManager->setOrderType( m_Order->KdAuftragArt() );
    m_TourManager->setPickingType( &m_Order->CommType() );

    return m_TourManager;
}

/***************************************************************************************************************************/
TourManager* TourAssignmentUtil::getTourManager4CustomerRouting()
{
    if( NULL == m_TourManager4CustomerRouting )
    {
        m_TourManager4CustomerRouting = new TourManager(    m_Order->Session(),
                                                            m_Order->KdAuftragNr(),
                                                            m_ArgIBTBranchNo,
                                                            m_Order->Customer()->IDFNr(),
                                                            &m_Order->CommType(),
                                                            m_Order->OrderType().KdAuftragArt() );
    }

    m_TourManager4CustomerRouting->setOrderType( m_Order->KdAuftragArt() );
    m_TourManager4CustomerRouting->setPickingType( &m_Order->CommType() );

    return m_TourManager4CustomerRouting;
}

/***************************************************************************************************************************/
void TourAssignmentUtil::setErrorMessage( const int errorno )
{
    switch( errorno )
    {
        case 0:
            break;
        case CMSG_ORD_ROUTE_INVALID:
        case CMSG_ORD_ROUTE_TIMEOFF:
            m_Order->ExternalError( m_Order->Session()->CMsgStream(), errorno, basar::VarString("").c_str() );
            break;
        default:
            m_Order->ExternalError( m_Order->Session()->CMsgStream(), errorno );
            break;
    }

    if( errorno > 0 )
    {
        std::stringstream s;
        s << "TAU:setErrorMessage " << errorno;
        TourUtil::writeLogINFO(s);
    }
}

/***************************************************************************************************************************/
TourInfo TourAssignmentUtil::determineItemTour( pxOrderItem* item, bool avoidCustRouting /*= false*/ )
{
    getTourManager()->resetArgInjections();


    if( m_Order->IsNewOrder() ){ getTourManager()->injectNewOrderFlag( true ); }
    getTourManager()->injectDesiredTourId( m_Order->TourId() );
    getTourManager()->injectDeliveryDate( m_Order->DatumAuslieferung() );
    getTourManager()->injectIBTBranchNo( m_ArgIBTBranchNo );
    getTourManager()->injectArticle( m_ArgArticle );
    getTourManager()->injectIBTTypeArticle( m_ArgIBTTypeArticle );
    getTourManager()->injectNoCheckForTransitionTimesAndPickingDurations( m_ArgNoCheckForTransitionTimesAndPickingDurations );
    if( m_Order->Customer()->IsNoSeparate() ){ getTourManager()->injectNoDelayedDelivery(); }
    if( m_Order->getNoDelayedDelivery() ){ getTourManager()->injectNoDelayedDelivery(); }

    // NLevelIBT -> Tourermittlung für Positionsbuchung
    if( m_Order->Param()->IsNlevelIBT() )
    {
        if( item->getNLevelIBTTypeID() > 0 )
        {
            this->m_ArgNLevelIBTType = item->getNLevelIBTTypeID();
        }
        getTourManager()->injectNLevelIBTType( m_ArgNLevelIBTType );
    }

    if( cORTYPE_AUXILIARY == m_Order->BatchSchreiben() )
    {
        getTourManager()->injectIsOrderFromIBT( true );
    }

    if( m_ArgIBTBranchNo > 0 )
    {
        if( !avoidCustRouting && hasCustomerRouting() )
        {
            return determineCustomerRoutingTour();
        }
    }

    // for special articles the determined tour may not be earlier than the tour of the order
    if( 0 == m_ArgIBTBranchNo )
    {
        getTourManager()->setNotEarlierThanOrderTour(m_Order->TourId(), m_Order->DatumAuslieferung());
    }

    return getTourManager()->determineTour();
}

/***************************************************************************************************************************/
TourInfo TourAssignmentUtil::determineCustomerRoutingTour()
{
    getTourManager4CustomerRouting()->resetArgInjections();
    getTourManager4CustomerRouting()->injectNewOrderFlag( true );
    return getTourManager4CustomerRouting()->determineTour();
}


/***************************************************************************************************************************/
bool TourAssignmentUtil::isDayNightMergeDeliveryFaster(pxOrderItem* item, short routingBranchNo)
{
    getTourManager()->resetArgInjections();
    if( m_Order->IsNewOrder() ){ getTourManager()->injectNewOrderFlag( true ); }
    getTourManager()->injectDeliveryDate( m_Order->DatumAuslieferung() );
    getTourManager()->injectIBTBranchNo( routingBranchNo );
    getTourManager()->injectArticle( item->ArtBase() );
    getTourManager()->injectIBTTypeArticle( item->ArtBase()->getIBTType() );
    getTourManager()->injectNoCheckForTransitionTimesAndPickingDurations( m_ArgNoCheckForTransitionTimesAndPickingDurations );
    if( m_Order->Customer()->IsNoSeparate() ){ getTourManager()->injectNoDelayedDelivery(); }
    if( m_Order->getNoDelayedDelivery() ){ getTourManager()->injectNoDelayedDelivery(); }
    if( m_Order->Param()->IsNlevelIBT() ) getTourManager()->injectNLevelIBTType( item->getNLevelIBTTypeID() );

    TourInfo tour_ibt = determineItemTour( item, true );
    TourInfo tour_daynight = determineCustomerRoutingTour();

    std::stringstream s;
    s << "TAU:isDayNightMergeDeliveryFaster" << std::endl <<
        "IBT: "  << tour_ibt.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() << " "
                 << tour_ibt.getCustomerDeliveryDateTimeMin().GetHours() << ":"
                 << tour_ibt.getCustomerDeliveryDateTimeMin().GetMinutes() << std::endl <<
        "DNM: "  << tour_daynight.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() << " "
                 << tour_daynight.getCustomerDeliveryDateTimeMin().GetHours() << ":"
                 << tour_daynight.getCustomerDeliveryDateTimeMin().GetMinutes() << std::endl;
    TourUtil::writeLog(s);

    if( tour_daynight.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() < tour_ibt.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() )
    {
        return true; // DayNightMerge kommt mindestens 1 Tag früher als Verbund
    }

    if( tour_daynight.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() > tour_ibt.getCustomerDeliveryDateTimeMin().GetYYYYMMDD() )
    {
        return false; // DayNightMerge kommt mindestens 1 Tag später als Verbund
    }

    int daynightTime = (tour_daynight.getCustomerDeliveryDateTimeMin().GetHours() * 100) + tour_daynight.getCustomerDeliveryDateTimeMin().GetMinutes();
    int ibtTime = (tour_ibt.getCustomerDeliveryDateTimeMin().GetHours() * 100) + tour_ibt.getCustomerDeliveryDateTimeMin().GetMinutes();
    if( daynightTime < ibtTime )
    {
        return true; // DayNightMerge ist am gleichen Tag schneller als Verbund
    }

    return false; // kein DayNightMerge weil sonst 2 Autos zum Kunden fahren
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isArticleNarcoticOnly()
{
    if( m_ArgArticle->ArtFlags().IsKuehlKette() ) return false;
    if( m_ArgArticle->ArtFlags().IsGekuehlt08() ) return false;
    if( m_ArgArticle->ArtFlags().IsGekuehlt20() ) return false;

    if( m_ArgArticle->ArtClass().IsOpiat() ) return true;
    return false;
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isArticleCoolChainOnly()
{
    if( m_ArgArticle->ArtClass().IsOpiat() ) return false;
    if( m_ArgArticle->ArtFlags().IsGekuehlt08() ) return false;
    if( m_ArgArticle->ArtFlags().IsGekuehlt20() ) return false;

    if( m_ArgArticle->ArtFlags().IsKuehlKette() ) return true;
    return false;
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isArticleCoolBelow8Only()
{
    if( m_ArgArticle->ArtClass().IsOpiat() ) return false;
    if( m_ArgArticle->ArtFlags().IsGekuehlt20() ) return false;
    if( m_ArgArticle->ArtFlags().IsKuehlKette() ) return false;

    if( m_ArgArticle->ArtFlags().IsGekuehlt08() ) return true;
    return false;
}

/***************************************************************************************************************************/
bool TourAssignmentUtil::isArticleCoolBelow20Only()
{
    if( m_ArgArticle->ArtClass().IsOpiat() ) return false;
    if( m_ArgArticle->ArtFlags().IsKuehlKette() ) return false;
    if( m_ArgArticle->ArtFlags().IsGekuehlt08() ) return false;

    if( m_ArgArticle->ArtFlags().IsGekuehlt20() ) return true;
    return false;
}


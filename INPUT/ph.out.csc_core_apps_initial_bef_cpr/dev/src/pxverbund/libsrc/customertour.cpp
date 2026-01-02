#include "customertour.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "csccustomer.hpp"
#include "pxcomtyp.hpp"
#include "pxartbas.hpp"
#include "pxholiday.hpp"
#include "pxoeparm.hpp"
#include <logger/loggerpool.h>
#include <libbasarcmnutil_datetime.h>
#include <libbasarcmnutil_timespan.h>
#include <libbasarcmnutil_i18nstring.h>

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTour::CustomerTour( pxSession* session, const short branchno, const long customerno )
    : pxDBRecord(session), m_BranchNo(branchno), m_CustomerNo(customerno),
      m_ArgNoCheckForTransitionTimesAndPickingDurations(false),
      m_IBTShuttleTourDetermination(false),
      m_IBTOrderImport(false)
{
    m_Customer = NULL;
}


/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTour::~CustomerTour()
{
    if( NULL != m_Customer )
    {
        delete m_Customer;
        m_Customer = NULL;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTour::injectIBTShuttleTourDetermination( const bool b /*= true*/ )
{
    this->m_IBTShuttleTourDetermination = b;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTour::injectIBTOrderImport( const bool b /*= true*/ )
{
    this->m_IBTOrderImport = b;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTour::injectNoCheckForTransitionTimesAndPickingDurations( const bool b /*= true*/ )
{
    this->m_ArgNoCheckForTransitionTimesAndPickingDurations = b;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long CustomerTour::getDrivingDuration() const
{
    return m_DrivingDuration;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short CustomerTour::getDeliveryTimeBuffer() const
{
    return m_DeliveryTimeBuffer;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long CustomerTour::getLagRechTour() const
{
    return m_LagRechTour;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nDate CustomerTour::getPickingDate() const
{
    return m_PickingDate;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
char CustomerTour::getPickingType() const
{
    return m_PickingType;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nString CustomerTour::getTourId() const
{
    return m_TourId;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nTime CustomerTour::getTourTime() const
{
    nTime retval( TourUtil::getTourIdInSeconds( this->getTourId() ) );
    return retval;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nDate CustomerTour::getTourDepartureDateTime(const nDate& date /*= TourUtil::getNullDate()*/ ) const
{
    long additionalSecs = TourUtil::getTourIdInSeconds( this->getTourId() );
    return calcTourDeliveryDateTime( additionalSecs, date );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nDate CustomerTour::getTourDeliveryDateTimeMin(const nDate& date /*= TourUtil::getNullDate()*/) const
{
    long additionalSecs = TourUtil::getTourIdInSeconds( this->getTourId() );
    additionalSecs += (this->getDrivingDuration() * TourUtil::SecondsPerMinute); // add driving duration in seconds
    return calcTourDeliveryDateTime( additionalSecs, date );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nDate CustomerTour::getTourDeliveryDateTimeMax(const nDate& date /*= TourUtil::getNullDate()*/) const
{
    long additionalSecs = TourUtil::getTourIdInSeconds( this->getTourId() );
    additionalSecs += (this->getDrivingDuration() * TourUtil::SecondsPerMinute); // add driving duration in seconds
    additionalSecs += (this->getDeliveryTimeBuffer() * TourUtil::SecondsPerMinute); // add delivery time buffer in seconds
    return calcTourDeliveryDateTime( additionalSecs, date );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nDate CustomerTour::calcTourDeliveryDateTime( const long& additionalSecs, const nDate& date /*= TourUtil::getNullDate()*/ ) const
{
    if( this->isPseudoTour() )
    {
        nDate today = TourUtil::getCurrentDate().add(1);
        nTime t( today.GetYear(), today.GetMonth(), today.GetDay(), 0, 0, 0 );
        return nDate(t);
    }

    nDate calcdate = date;
    if( TourUtil::getNullDate() != this->getPickingDate() )
    {
        calcdate = this->getPickingDate();
    }
    if( TourUtil::getNullDate() == calcdate )
    {
        return TourUtil::getNullDate();
    }

    long seconds = additionalSecs;

    int addDays = 0;
    int hours = 0;
    int minutes = 0;
    while( seconds >= TourUtil::SecondsPerDay    )
    {
        ++addDays;
        seconds -= TourUtil::SecondsPerDay;
    }
    while( seconds >= TourUtil::SecondsPerHour   )
    {
        ++hours;
        seconds -= TourUtil::SecondsPerHour;
    }
    while( seconds >= TourUtil::SecondsPerMinute )
    {
        ++minutes;
        seconds -= TourUtil::SecondsPerMinute;
    }

    nTime retvaltime( calcdate.GetYear(), calcdate.GetMonth(), calcdate.GetDay(), hours, minutes, 0 );
    nDate retval(retvaltime);
    while( addDays > 0 )
    {
        ++retval;
        addDays -= 1;
    }

    return nDate(retval);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
TourUtil::WeekDayEnum CustomerTour::getWeekDay() const
{
    return m_WeekDay;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::hasCoolPermission() const
{
    if( 0 == m_IsCoolTour )
    {
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::hasCoolBelow8Permission() const
{
    if( 0 == m_IsCoolBelow8Tour )
    {
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::hasCoolBelow20Permission() const
{
    if( 0 == m_IsCoolBelow20Tour )
    {
        return false;
    }
    return true;
}

bool CustomerTour::isReturnsTour() const
{
    if( 0 == m_ReturnsTour )
    {
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::hasExpired( const pxCommType* pickingtype, const bool checkDurationAndTransitionTimes /*= true*/ ) const
{
    std::stringstream s;
    nTime pickingTime = getPickingTime();
    nTime expiryTime = getExpiryTime(pickingtype, checkDurationAndTransitionTimes); // time for comparison with tour time

    if( TourUtil::getLongTime(expiryTime) > TourUtil::getLongTime(pickingTime) )
    {
        s << "CT:hasExpired: TRUE " << static_cast<const char* const>(this->getTourId()) << " pickTime: " << TourUtil::getLongTime( pickingTime ) << " expTime: " << TourUtil::getLongTime(expiryTime);
        TourUtil::writeLogDEBUG( s );
        return true;
    }
    s << "CT:hasExpired: FALSE " << static_cast<const char* const>(this->getTourId()) << " pickTime: " << TourUtil::getLongTime( pickingTime ) << " expTime: " << TourUtil::getLongTime(expiryTime);
    TourUtil::writeLogDEBUG( s );

    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::hasNarcoticsPermission() const
{
    if( 0 == m_IsNarcoticsTour )
    {
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::hasPsychotropicPermission() const
{
    if ( 1 == m_IsPsychotropicTransportExcluded )
    {
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::isAssignable( bool acceptAutoAssignableToursOnly /*= false*/, nTime timeoffset /*= TourUtil::getCurrentTime()*/, bool forceTimeCheck /*= false*/ )
{
    // TODOSH TourManager: Kippzeiten müssen > Lagerdurchlaufzeit bzw. Lagerdurchlaufzeit Eilbote sein!!! Problem: PickingType ist nicht bekannt!
    std::stringstream s;
    s << "CT:isAssignable: Tour[" << m_TourId << "/" << m_PickingDate.GetYYYYMMDD() << "] Offset[" << TourUtil::getLongTime(timeoffset) << " " << timeoffset.GetYear() << "-" << timeoffset.GetMonth() << "-" << timeoffset.GetDay() << "] ";
    if( acceptAutoAssignableToursOnly ) s << "AAOnly ";
    if( m_ArgNoCheckForTransitionTimesAndPickingDurations ) s << "NoCheckFTTAPD ";
    if( forceTimeCheck ) s << "fTCHK ";

    long tourverspaetung = getOrderEntryParam()->TourVerspaetung();
    if( tourverspaetung  > 0 ) s << "VSpaet " << tourverspaetung << " ";

    // for non video devices Pseudo-Tours without flag AutoAssignable cannot be used
    if( acceptAutoAssignableToursOnly )
    {
        if( !Session()->Device()->IsVideo() && !this->isAutoAssignable() )
        {
            s << "FALSE !Video & !AA";
            TourUtil::writeLogDEBUG( s );
            return false;
        }
    }

    if( acceptAutoAssignableToursOnly && !this->isAutoAssignable() )
    {
        s << "FALSE !AA";
        TourUtil::writeLogDEBUG( s );
        return false;
    }

    // tours should not be assigned if departure is on a public holiday
    if( this->isDepartureOnPublicHoliday() )
    {
        s << "FALSE !PUBHOL";
        TourUtil::writeLogDEBUG( s );
        return false;
    }

    // do not check the times if the tour is not today
    if( this->m_PickingDate != TourUtil::getNullDate() )
    {
        if( this->m_PickingDate.GetYYYYMMDD() > TourUtil::getCurrentDate().GetYYYYMMDD() )
        {
            if( !forceTimeCheck )
            {
                s << "TRUE FutureDate ";
                TourUtil::writeLogDEBUG( s );
                return true;
            }

            if( forceTimeCheck && 0 == timeoffset.GetHours() && 0 == timeoffset.GetMinutes() )
            {
                s << "TRUE FutureDate2 ";
                TourUtil::writeLogDEBUG( s );
                return true;
            }
        }
    }

    // calculate current time for tour determination
    nTime CurrentTimeOffset = timeoffset;
    if( this->m_PickingDate != TourUtil::getNullDate() )
    {
        if( this->m_PickingDate == TourUtil::getCurrentDate() )
        {
            CurrentTimeOffset = CurrentTimeOffset - (tourverspaetung * 60L); // delay has to be taken into account only for the current day
        }
    }

    long timelimit = TourUtil::getTimeInSeconds( CurrentTimeOffset );
    s << "tlimit " << timelimit << " ";
    if( this->m_PickingDate != TourUtil::getNullDate() )
    {
        nDate offdate(CurrentTimeOffset.GetYear(), CurrentTimeOffset.GetMonth(), CurrentTimeOffset.GetDay() );
        long daysbetween = 0;
        if( m_PickingDate.GetAbsday() != offdate.GetAbsday() )
        {
            if( offdate.GetAbsday() < (TourUtil::getCurrentDate().GetAbsday()) )
            {
                s << "DepDate? (" << offdate.GetAbsday() << "/" << TourUtil::getCurrentDate().GetAbsday() << ") ";
            }
            else
            {
                daysbetween = ((offdate.GetAbsday()) - (TourUtil::getCurrentDate().GetAbsday()));
            }
        }

        timelimit += (daysbetween) * (24 * 60 * 60);
        s << "OffDVar " << timelimit << "(" << daysbetween << ") ";
    }

    if( TourUtil::isPseudoTour( this->m_TourId ) )
    {
        s << "PseudoTour!";
        TourUtil::writeLogDEBUG( s );
        return true;
    }

    TourUtil::writeLogDEBUG( s );

    if( !Session()->Device()->IsVideo() || m_IBTShuttleTourDetermination )
    {
        return isAssignableBeforeTransition(timelimit); // transition times are only taken into account for non video devices!
    }
    return isAssignableBeforeTourDeparture(timelimit);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::isDepartureOnPublicHoliday()
{
    if( !this->getOrderEntryParam()->AreToursWithDepartureOnHolidayDisabled() ) return false;
    if( !this->isPseudoTour() )
    {
        pxHoliDayList* holidaylist = Session()->HoliDayList( this->getCustomer()->getBranchNo() );
        if( holidaylist->CheckDateForHoliday( getTourDepartureDateTime(), this->getCustomer()->getBranchNo() ) )
        {
            return true;
        }
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::isAutoAssignable() const
{
    if( '1' == m_AutoAssignable )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::isIBTTour() const
{
    if( '1' == this->m_IbtTour )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::isPseudoTour() const
{
    return TourUtil::isPseudoTour( getTourId() );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTour::setPickingDate( const nDate& date )
{
    this->m_PickingDate = date;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::isValidForArticle( pxArtBase* article ) const
{
    if( NULL == article )
    {
        return true;
    }
    else
    {
        // check cool articles
        if( article->ArtFlags().IsKuehlKette() && !hasCoolPermission() )
        {
            return false;
        }

        // check cool below 8° articles
        if( article->ArtFlags().IsGekuehlt08() && !hasCoolBelow8Permission() )
        {
            return false;
        }

        // check cool below 20° articles
        if( article->ArtFlags().IsGekuehlt20() && !hasCoolBelow20Permission() )
        {
            return false;
        }

        // check psychotropic articles
        if ( article->IsKzPsychoStoffe() && !hasPsychotropicPermission() )
        {
            return false;
        }

        // check narcotics
        if( article->ArtClass().IsOpiat() && !hasNarcoticsPermission() )
        {
            return false;
        }

        return true;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nDate CustomerTour::getTourClosingDateTime( const pxCommType* pickingtype /*= NULL*/, nDate datetouse /*= TourUtil::getNullDate()*/ ) const
{
    std::stringstream log;
    log << "CT:getTourClosingDateTime TourId[" << m_TourId << "/" << TourUtil::getReadableDateTime(this->getTourDepartureDateTime()) << "] PiDat[" << TourUtil::getReadableDateTime(this->getPickingDateTime()) << "] TVSpaet[" << getOrderEntryParam()->TourVerspaetung() << "] FIL[" << m_BranchNo << "] IDF[" << m_CustomerNo << "] ";

    // Mit welchem Datum muss gerechnet werden?
    nDate retval = datetouse; // wurde ein bestimmtes Datum vorgegeben, dann muss dieses verwendet werden!
    if( datetouse == TourUtil::getNullDate() )
    {
        retval = getPickingDate(); // wenn wir kein Datum haben, nehmen wir das Kommidatum der Tour
        if( retval == TourUtil::getNullDate() )
        {
            retval = TourUtil::getCurrentDate(); // wenn wir kein Kommidatum haben nehmen wir den aktuellen Tag
        }
    }

    long tourDepartureInSeconds = TourUtil::getTourIdInSeconds( this->getTourId() ); // das ist die Tourabfahrt!
    tourDepartureInSeconds += (getOrderEntryParam()->TourVerspaetung() * 60L); // wenn es eine Tourverspätung gibt muss diese berücksichtigt werden!

    long tourClosureInSeconds = tourDepartureInSeconds; // bis dahin ist die Tour buchbar (jetzt müssen wir noch die Lagerdurchlaufzeit/Kippzeit abziehen
    if( Session()->Device()->IsVideo() )
    {
        if( NULL == pickingtype )
        {
            tourClosureInSeconds -= ( getOrderEntryParam()->DurchlaufNormal() * 60L );
        }
        else
        {
            if( !pickingtype->IsShipSpecialAnyway() ) // picking types 6, 7
            {
                if( pickingtype->IsUrgentAnyway() ) // picking types 3,4,5
                {
                    tourClosureInSeconds -= (getOrderEntryParam()->DurchlaufEilbote() * 60L);
                }
                else
                {
                    tourClosureInSeconds -= (getOrderEntryParam()->DurchlaufNormal() * 60L);
                }
            }
        }
    }
    else
    {
        tourClosureInSeconds -= (getTourTransitionTime() * 60L);
    }
    if( tourClosureInSeconds < 0 ) tourClosureInSeconds = 0;

    if( tourClosureInSeconds > TourUtil::SecondsPerDay )
    {
        tourClosureInSeconds -= TourUtil::SecondsPerDay;
        ++retval;
    }

    int hours = 0;
    int minutes = 0;
    while( tourClosureInSeconds >= TourUtil::SecondsPerHour   )
    {
        tourClosureInSeconds -= TourUtil::SecondsPerHour;
        ++hours;
    }
    while( tourClosureInSeconds >= TourUtil::SecondsPerMinute )
    {
        tourClosureInSeconds -= TourUtil::SecondsPerMinute;
        ++minutes;
    }

    nDate t( nTime(retval.GetYear(), retval.GetMonth(), retval.GetDay(), hours, minutes, 0) );

    log << "RetVal: " << TourUtil::getReadableDateTime(t) << std::endl;

    TourUtil::writeLogDEBUG( log );
    return t;
}

/*############################################################################################################################*/
/*                                       P R O T E C T E D                                                                    */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTour& CustomerTour::Assign( CustomerTour& dest, const tCUSTOMERTOUR& src )
{
    dest.m_TourId = src.TourId;
    dest.m_PickingDate = nDate(src.PickingDate);
    dest.m_DrivingDuration = src.DrivingDuration;
    dest.m_IbtTour = src.IsIBTTour;
    dest.m_TransitionTime = src.TransitionTime;
    dest.m_TourTransitionTime = src.TourTransitionTime;
    dest.m_AutoAssignable = src.AutoAssignable;
    dest.m_OrderType = src.OrderType;
    dest.setWeekDay( src.WeekDay );
    dest.m_TimeEndOfPicking = src.TimeEndOfPicking;
    dest.m_IsCoolTour = src.IsCoolTour;
    dest.m_IsCoolBelow8Tour = src.IsCoolBelow8Tour;
    dest.m_IsCoolBelow20Tour = src.IsCoolBelow20Tour;
    dest.m_IsNarcoticsTour = src.IsNarcoticsTour;
    dest.m_IsPsychotropicTransportExcluded = src.IsPsychotropicTransportExcluded;
    dest.m_PickingType = src.PickingType;
    dest.m_DeliveryTimeBuffer = src.DeliveryTimeBuffer;
    dest.m_LagRechTour = src.LagRechTour;
    dest.m_ArgNoCheckForTransitionTimesAndPickingDurations = false;
    dest.m_BranchNo = src.BranchNo;
    dest.m_CustomerNo = src.CustomerNo;
    dest.m_ReturnsTour = src.ReturnsTour;
    return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
tCUSTOMERTOUR& CustomerTour::Assign( tCUSTOMERTOUR&  dest, const CustomerTour& src )
{
    src.m_TourId.GetData( dest.TourId );
    src.m_OrderType.GetData( dest.OrderType );
    dest.PickingDate = src.m_PickingDate.GetYYYYMMDD();
    dest.DrivingDuration = src.m_DrivingDuration;
    dest.IsIBTTour = src.m_IbtTour;
    dest.TransitionTime = src.m_TransitionTime;
    dest.TourTransitionTime = src.m_TourTransitionTime;
    dest.AutoAssignable = src.m_AutoAssignable;
    dest.WeekDay = static_cast<short>(src.m_WeekDay);
    dest.TimeEndOfPicking = src.m_TimeEndOfPicking;
    dest.IsCoolTour = src.m_IsCoolTour;
    dest.IsCoolBelow8Tour = src.m_IsCoolBelow8Tour;
    dest.IsCoolBelow20Tour = src.m_IsCoolBelow20Tour;
    dest.IsNarcoticsTour = src.m_IsNarcoticsTour;
    dest.IsPsychotropicTransportExcluded = src.m_IsPsychotropicTransportExcluded;
    dest.PickingType = src.m_PickingType;
    dest.DeliveryTimeBuffer = src.m_DeliveryTimeBuffer;
    dest.LagRechTour = src.m_LagRechTour;
    dest.BranchNo = src.m_BranchNo;
    dest.CustomerNo = src.m_CustomerNo;
    dest.ReturnsTour = src.m_ReturnsTour;
    return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nTime CustomerTour::getPickingTime() const
{
    nClock clock(m_TimeEndOfPicking);
    return nTime( (int)m_PickingDate.GetYear(), (int)m_PickingDate.GetMonth(), (int)m_PickingDate.GetDay(), (int)clock.GetHours(), (int)clock.GetMinutes(), (int)clock.GetSeconds() );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nDate CustomerTour::getPickingDateTime() const
{
    nTime t( getPickingDate().GetYear(), getPickingDate().GetMonth(), getPickingDate().GetDay(), getPickingTime().GetHours(), getPickingTime().GetMinutes(), 0 );
    return (nDate)t;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::hasOrderType( const nString& ordertype /*= ""*/ ) const
{
    if( m_OrderType.IsEmpty() )
    {
        return false;
    }

    nString ordtype = ordertype;
    ordtype.Strip();

    // if method is called without specific order type, check if ordertype is available for item
    if( ordtype.IsEmpty() )
    {
        return true;
    }

    // if method is called with specific order type, check if ordertype is equal to the ordertype of this
    if( ordtype == m_OrderType )
    {
        return true;
    }

    return false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTour::Init()
{
    tCUSTOMERTOUR record;
    memset( &record, 0, sizeof(tCUSTOMERTOUR) );
    Assign( *this, record );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerTour::setWeekDay( const short& weekday )
{
    m_WeekDay = TourUtil::getWeekDay(weekday);
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTour::CustomerTour( pxSession* session, const short branchno, const long customerno, tCUSTOMERTOUR& src )
    : pxDBRecord(session), m_BranchNo(branchno), m_CustomerNo(customerno), m_ArgNoCheckForTransitionTimesAndPickingDurations( false )
{
    Init();
    (*this) = src;
    m_Customer = NULL;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTour::CustomerTour( CustomerTour& src )
    : pxDBRecord(src.Session()), m_BranchNo(src.m_BranchNo), m_CustomerNo(src.m_CustomerNo),
      m_ArgNoCheckForTransitionTimesAndPickingDurations(false)
{
    Init();
    (*this) = src;
    m_Customer = NULL;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTour& CustomerTour::operator=( const tCUSTOMERTOUR& src )
{
    return Assign( *this, src );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerTour& CustomerTour::operator=( const CustomerTour& src )
{
    tCUSTOMERTOUR record;
    Assign( *this, Assign(record, src) );
    return *this;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CustomerTour::CompareTo( const nCollectable* That/*, void* p, const long lparm*/ ) const
{
    CustomerTour* that = (CustomerTour*)That;
    int retval = 0;
    if( 0 == retval )
    {
        retval = ( m_WeekDay == that->m_WeekDay ) ? 0 : 1;
    }
    if( 0 == retval )
    {
        retval = ( m_TourId == that->m_TourId ) ? 0 : ( m_TourId > that->m_TourId ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_PickingDate == that->m_PickingDate ) ? 0 : ( m_PickingDate > that->m_PickingDate ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_DrivingDuration == that->m_DrivingDuration ) ? 0 : ( m_DrivingDuration > that->m_DrivingDuration ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_IbtTour == that->m_IbtTour ) ? 0 : ( m_IbtTour > that->m_IbtTour ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_TransitionTime == that->m_TransitionTime ) ? 0 : ( m_TransitionTime > that->m_TransitionTime ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_AutoAssignable == that->m_AutoAssignable ) ? 0 : ( m_AutoAssignable > that->m_AutoAssignable ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_OrderType == that->m_OrderType ) ? 0 : ( m_OrderType > that->m_OrderType ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_TimeEndOfPicking == that->m_TimeEndOfPicking ) ? 0 : 1;
    }
    if( 0 == retval )
    {
        retval = ( m_IsCoolTour == that->m_IsCoolTour ) ? 0 : ( m_IsCoolTour > that->m_IsCoolTour ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_IsCoolBelow8Tour == that->m_IsCoolBelow8Tour ) ? 0 : ( m_IsCoolBelow8Tour > that->m_IsCoolBelow8Tour ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_IsCoolBelow20Tour == that->m_IsCoolBelow20Tour ) ? 0 : ( m_IsCoolBelow20Tour > that->m_IsCoolBelow20Tour ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_IsNarcoticsTour == that->m_IsNarcoticsTour ) ? 0 : ( m_IsNarcoticsTour > that->m_IsNarcoticsTour ? 1 : -1 );
    }
    if (0 == retval)
    {
        retval = ( m_IsPsychotropicTransportExcluded == that->m_IsPsychotropicTransportExcluded ) ? 0 : ( m_IsPsychotropicTransportExcluded > that->m_IsPsychotropicTransportExcluded ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_PickingType == that->m_PickingType ) ? 0 : ( m_PickingType > that->m_PickingType ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_DeliveryTimeBuffer == that->m_DeliveryTimeBuffer ) ? 0 : ( m_DeliveryTimeBuffer > that->m_DeliveryTimeBuffer ? 1 : -1 );
    }
    if( 0 == retval )
    {
        retval = ( m_LagRechTour == that->m_LagRechTour ) ? 0 : 1;
    }
    return retval;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
const CSCCustomer* CustomerTour::getCustomer() const
{
    if( NULL == m_Customer )
    {
        m_Customer = new CSCCustomer( this->Session(), m_BranchNo, m_CustomerNo );
        m_Customer->Read();
    }
    return m_Customer;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nTime CustomerTour::getExpiryTime( const pxCommType* pickingtype, const bool checkDurationAndTransitionTimes /*= true*/ ) const
{
    nTime retval;

    std::stringstream s;
    s << "CT:getExpiryTime " ;
    if( !checkDurationAndTransitionTimes ) s << "CDTTimes! ";
    if( getOrderEntryParam()->TourVerspaetung() > 0 ) s << "TVSpaet " << getOrderEntryParam()->TourVerspaetung() << " ";

    retval -= (getOrderEntryParam()->TourVerspaetung() * 60L);

    if( !checkDurationAndTransitionTimes )
    {
        s << " No Check For PickingDurations! -> " << TourUtil::getLongTime( retval ) << " ";
        TourUtil::writeLogDEBUG( s );
        return retval;
    }

    if( true == m_ArgNoCheckForTransitionTimesAndPickingDurations )
    {
        s << " No Check For PickingDurations2! -> " << TourUtil::getLongTime( retval ) << " ";
        TourUtil::writeLogDEBUG( s );
        return retval;
    }

    if( NULL != pickingtype )
    {
        if( pickingtype->IsShipSpecialAnyway() ) // picking types 6, 7
        {
            s << " PickTyp SpecialAnyway! -> " << TourUtil::getLongTime( retval ) << " ";
            TourUtil::writeLogDEBUG( s );
            return retval;
        }
        if( pickingtype->IsUrgentAnyway() ) // picking types 3,4,5
        {
            s << " PickTyp UrgentAnyway! DLEil " << getOrderEntryParam()->DurchlaufEilbote() << " ";
            retval += (getOrderEntryParam()->DurchlaufEilbote() * 60L);
        }
        else
        {
            s << " PickTyp Normal! DLNorm " << getOrderEntryParam()->DurchlaufNormal() << " ";
            retval += ( getOrderEntryParam()->DurchlaufNormal() * 60L );
        }
    }
    else
    {
        s << " NoPickTyp! DLNorm " << getOrderEntryParam()->DurchlaufNormal() << " ";
        retval += ( getOrderEntryParam()->DurchlaufNormal() * 60L );
    }

    s << "=> Expiry-Uhrzeit: " << TourUtil::getLongTime( retval );
    TourUtil::writeLogDEBUG( s );

    return retval;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
const pxOrderEntryParamPtr CustomerTour::getOrderEntryParam() const
{
    return this->Session()->getOrderEntryParam(m_BranchNo);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::isAssignableBeforeTourDeparture(long& timelimit)
{
    std::stringstream s;
    s << "CT:isAssignableBeforeTourDeparture TLimit " << timelimit << " TourIDSecs " << TourUtil::getTourIdInSeconds(getTourId()) << " ";

    if( timelimit > TourUtil::getTourIdInSeconds(getTourId()) )
    {
        s << "=> FALSE ";
        TourUtil::writeLogDEBUG( s );
        return false;
    }
    s << "=> TRUE ";
    TourUtil::writeLogDEBUG( s );
    return true;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerTour::isAssignableBeforeTransition(long& timelimit)
{
    // TODOSH TourManager: Kippzeiten müssen > Lagerdurchlaufzeit bzw. Lagerdurchlaufzeit Eilbote sein!!! Problem: PickingType ist nicht bekannt!
    std::stringstream s;
    s << "CT:isAssignableBeforeTransition TL " << timelimit << " ";
    if( !m_ArgNoCheckForTransitionTimesAndPickingDurations ) s << "!NCTTPD ";
    if( !m_IBTOrderImport ) s << "!IOI ";

    long offset = timelimit;
    long usedtransitiontime = 0;

    if( false == m_ArgNoCheckForTransitionTimesAndPickingDurations )
    {
        usedtransitiontime = (getTourTransitionTime() * 60L);
        if( this->m_IBTOrderImport ){ usedtransitiontime -= (3 * 60L); } // 3 Minutes for ibtorderimport/vborderimport
        offset += usedtransitiontime;
    }

    s << "TransTime " << usedtransitiontime << " OS " << offset;
    TourUtil::writeLogINFO( s );

    return isAssignableBeforeTourDeparture( offset );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long CustomerTour::getTourTransitionTime() const
{
    long retval = 0;

    if( m_TransitionTime > 0 ) // 1st priority: Kippzeit aus tourplantag
    {
            retval = m_TransitionTime;
    }
    else if( m_TourTransitionTime > 0 ) // 2nd priority: Kippzeit aus tour
    {
            retval = m_TourTransitionTime;
    }
    else if( getCustomer()->getTourBreakoverMinutes() > 0 ) // 3rd priority: Kippzeit aus kunde
    {
        retval = getCustomer()->getTourBreakoverMinutes();
    }
    else if( getOrderEntryParam()->TourenKippZeit() > 0 ) // 4th priority: Kippzeit aus paraauftragbearb
    {

        retval = getOrderEntryParam()->TourenKippZeit();
    }

    return retval;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short CustomerTour::getBranchNo() const
{
    return m_BranchNo;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long CustomerTour::getCustomerNo() const
{
    return m_CustomerNo;
}

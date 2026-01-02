#include "tourinfo.hpp"
#include "tourutil.hpp"
#include "pxorderitemtour.hpp"
#include <sstream>

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/***************************************************************************************************************************/
TourInfo::TourInfo()
{
    init();
}

TourInfo::TourInfo( const TourInfo& src )
{
    init();

    m_TourDepartureDateTime = src.getTourDepartureDateTime();
    m_TourDepartureDateTimeNormalized = src.getTourDepartureDateTimeNormalized();

    m_TourFound = src.getTourFound();
    m_CustomerDeliveryDateTimeMin = src.getCustomerDeliveryDateTimeMin();
    m_CustomerDeliveryDateTimeMax = src.getCustomerDeliveryDateTimeMax();
    m_TourClosingDateTime = src.getTourClosingDateTime();
    m_TourID = src.getTourID();
    m_TourDate = src.getTourDate();
    m_DrivingDuration = src.getDrivingDuration();
    m_PickingType = src.getPickingType();
    m_DeliveryTimeBuffer = src.getDeliveryTimeBuffer();
    m_LagRechTour = src.getLagRechTour();
    m_IBTBranchNo = src.getIBTBranchNo();
    m_IBTCustomerNo = src.getIBTCustomerNo();
    m_IBTType = src.getIBTType();
    if( src.isDayIBT() ) m_IBTSameDay = 1;
    m_IBTTourId = src.getIBTTourID();
    m_IBTTourDate = src.getIBTTourDate();
}

/***************************************************************************************************************************/
nString TourInfo::serialize() const
{
    std::stringstream s;
    if( !getTourFound() )
    {
        s << "No Tour found! Error: " << getError() << " Warning: " << getWarning();
        return (nString)(s.str().c_str());
    }
    else
    {

        s << "TourID:" << static_cast<const char* const>(getTourID());
        s << " Date:" << getTourDate().GetYYYYMMDD();
        s << " Dept:" << TourUtil::getReadableDateTime(getTourDepartureDateTime());
        s << " Dept Norm:" << TourUtil::getReadableDateTime(getTourDepartureDateTimeNormalized());
        s << " FDA:" << getDrivingDuration();
        s << " MinDelivery:" << TourUtil::getReadableDateTime(getCustomerDeliveryDateTimeMin());
        s << " Closing Time:" << TourUtil::getReadableDateTime(getTourClosingDateTime());
        s << " KA:" << getPickingType();
        if( getIBTBranchNo() > 0 )
        {
        s << "\n IBT TourID:" << static_cast<const char* const>(getIBTTourID()) << " Date: " << getIBTTourDate().GetYYYYMMDD();
            s << " Typ:"  << getIBTType();
            if( isDayIBT() )
            {
                s << " TagVB";
            }
            s << " FIL:" << getIBTBranchNo();
            s << " IDF:" << getIBTCustomerNo();
        }
        if( getWarning() > 0 ) s << "\n WARNING:" << getWarning();
        if( getError() > 0 ) s << "\n ERROR:" << getError();

        return (nString)(s.str().c_str());
    }
}

/***************************************************************************************************************************/
TourInfo::TourInfo( pxOrderItemTour* orderitemtour )
{
    init();
    if( NULL != orderitemtour )
    {
        if( 1 == orderitemtour->getDayIBT() )
        {
            this->setIBTSameDay( true );
        }
        else
        {
            this->setIBTSameDay( false );
        }
        this->setDeliveryTimeBuffer( orderitemtour->getDeliveryTimeBuffer() );
        this->setDrivingDuration( orderitemtour->getDrivingDuration() );
        this->setIBTBranchNo( orderitemtour->getDeliveryBranchNo() );
        this->setIBTCustomerNo( orderitemtour->getIBTCustomerNo() );
        this->setIBTTourId( orderitemtour->getIBTTourId() );
        this->setIBTTourDate( nDate(orderitemtour->getIBTTourDate()) );
        this->setIBTType( orderitemtour->getIBTType() );
        this->setTourFound( true );
        this->setTourID( orderitemtour->getTourId() );
        this->setTourDate( nDate(orderitemtour->getDepartureDate()) );
        this->setTourClosingDateTime( nDate(orderitemtour->getDepartureDate()) );

        nDate mindelivery = TourUtil::getDateTime( orderitemtour->getDeliveryDate(), orderitemtour->getDeliveryTime() );
        this->setCustomerDeliveryDateTimeMin( mindelivery );

        nTime maxdelivery( mindelivery.GetYear(), mindelivery.GetMonth(), mindelivery.GetDay(), mindelivery.GetHours(), mindelivery.GetMinutes(), 0 );
        maxdelivery.add( orderitemtour->getDeliveryTimeBuffer() * 60 );
        this->setCustomerDeliveryDateTimeMax( nDate(maxdelivery) );

        this->setTourDepartureDateTime( orderitemtour->getTourDepartureDateTime() );
        this->setTourDepartureDateTimeNormalized( orderitemtour->getTourDepartureDateTime(true) );
    }
}

/***************************************************************************************************************************/
TourInfo::~TourInfo()
{
}

/***************************************************************************************************************************/
void TourInfo::init()
{
    m_TourFound = false;
    m_TourClosingDateTimeAvailable = false;
    m_TourDepartureDateTime = TourUtil::getNullDate();
    m_TourDepartureDateTimeNormalized = TourUtil::getNullDate();
    m_CustomerDeliveryDateTimeMin = TourUtil::getNullDate();
    m_CustomerDeliveryDateTimeMax = TourUtil::getNullDate();
    m_TourClosingDateTime = TourUtil::getNullDate();
    m_TourID = "     ";
    m_TourDate = TourUtil::getNullDate();
    m_DrivingDuration = 0;
    m_PickingType = ' ';
    m_DeliveryTimeBuffer = 0;
    m_IBTBranchNo = 0;
    m_IBTCustomerNo = 0;
    m_IBTType = 0;
    m_IBTSameDay = 0;
    m_IBTTourId = "     ";
    m_IBTTourDate = TourUtil::getNullDate();
    m_LagRechTour = 0;
    m_Warning = 0;
    m_Error = 0;
}

/***************************************************************************************************************************/
const nDate& TourInfo::getTourDepartureDateTime() const
{
    return this->m_TourDepartureDateTime;
}

/***************************************************************************************************************************/
const nDate& TourInfo::getTourDepartureDateTimeNormalized() const
{
    return this->m_TourDepartureDateTimeNormalized;
}

/***************************************************************************************************************************/
const nDate& TourInfo::getCustomerDeliveryDateTimeMin() const
{
    return this->m_CustomerDeliveryDateTimeMin;
}

/***************************************************************************************************************************/
const nDate& TourInfo::getCustomerDeliveryDateTimeMax() const
{
    return this->m_CustomerDeliveryDateTimeMax;
}

/***************************************************************************************************************************/
const nDate& TourInfo::getTourClosingDateTime() const
{
    return this->m_TourClosingDateTime;
}

/***************************************************************************************************************************/
bool TourInfo::getTourClosingDateTimeAvailable() const
{
    return this->m_TourClosingDateTimeAvailable;
}

/***************************************************************************************************************************/
const nString& TourInfo::getTourID() const
{
    return m_TourID;
}

/***************************************************************************************************************************/
const nDate& TourInfo::getTourDate() const
{
    return m_TourDate;
}

/***************************************************************************************************************************/
int TourInfo::getDrivingDuration() const
{
    return m_DrivingDuration;
}

/***************************************************************************************************************************/
char TourInfo::getPickingType() const
{
    return m_PickingType;
}

/***************************************************************************************************************************/
short TourInfo::getDeliveryTimeBuffer() const
{
    return m_DeliveryTimeBuffer;
}

/***************************************************************************************************************************/
long TourInfo::getLagRechTour() const
{
    return m_LagRechTour;
}

/***************************************************************************************************************************/
short TourInfo::getIBTBranchNo() const
{
    return m_IBTBranchNo;
}

/***************************************************************************************************************************/
int TourInfo::getIBTCustomerNo() const
{
    return m_IBTCustomerNo;
}

/***************************************************************************************************************************/
short TourInfo::getIBTType() const
{
    return m_IBTType;
}

/***************************************************************************************************************************/
const nString& TourInfo::getIBTTourID() const
{
    return m_IBTTourId;
}

/***************************************************************************************************************************/
const nDate& TourInfo::getIBTTourDate() const
{
    return m_IBTTourDate;
}

/***************************************************************************************************************************/
bool TourInfo::isDayIBT() const
{
    if( 1 == this->m_IBTSameDay )
    {
        return true;
    }
    return false;
}

/***************************************************************************************************************************/
bool TourInfo::getTourFound() const
{
    return m_TourFound;
}

/***************************************************************************************************************************/
int TourInfo::getWarning() const
{
    return m_Warning;
}

/***************************************************************************************************************************/
int TourInfo::getError() const
{
    return m_Error;
}

/*############################################################################################################################*/
/*                                       P R O T E C T E D                                                                    */
/*############################################################################################################################*/

/***************************************************************************************************************************/
void TourInfo::resetErrorsAndWarnings()
{
    m_Warning = 0;
    m_Error = 0;
}

/***************************************************************************************************************************/
void TourInfo::setWarning( const int value )
{
    m_Warning = value;
}

/***************************************************************************************************************************/
void TourInfo::setError( const int value )
{
    m_Error = value;
}

/***************************************************************************************************************************/
void TourInfo::setTourDepartureDateTime(const nDate& value)
{
    this->m_TourDepartureDateTime = value;
    this->setTourDepartureDateTimeNormalized(value);
}

/***************************************************************************************************************************/
void TourInfo::setTourDepartureDateTimeNormalized(const nDate& value)
{
    this->m_TourDepartureDateTimeNormalized = value;
}

/***************************************************************************************************************************/
void TourInfo::setCustomerDeliveryDateTimeMin(const nDate& value)
{
    this->m_CustomerDeliveryDateTimeMin = value;
}

/***************************************************************************************************************************/
void TourInfo::setCustomerDeliveryDateTimeMax(const nDate& value)
{
    this->m_CustomerDeliveryDateTimeMax = value;
}

/***************************************************************************************************************************/
void TourInfo::setTourClosingDateTime(const nDate& value)
{
    this->m_TourClosingDateTime = value;
}

/***************************************************************************************************************************/
void TourInfo::setTourID(const nString& value)
{
    m_TourID = value;
}

/***************************************************************************************************************************/
void TourInfo::setIBTTourId(const nString& value)
{
    m_IBTTourId = value;
}

/***************************************************************************************************************************/
void TourInfo::setIBTTourDate(const nDate& value)
{
    m_IBTTourDate = value;
}

/***************************************************************************************************************************/
void TourInfo::setIBTSameDay(const bool value)
{
    if( value )
    {
        this->m_IBTSameDay = 1;
    }
    else
    {
        this->m_IBTSameDay = 0;
    }
}

/***************************************************************************************************************************/
void TourInfo::setTourDate(const nDate& value)
{
    m_TourDate = value;
}

/***************************************************************************************************************************/
void TourInfo::setDrivingDuration(const long value)
{
    m_DrivingDuration = value;
}

/***************************************************************************************************************************/
void TourInfo::setPickingType(const char value)
{
    m_PickingType = value;
}

/***************************************************************************************************************************/
void TourInfo::setDeliveryTimeBuffer(const short value)
{
    m_DeliveryTimeBuffer = value;
}

/***************************************************************************************************************************/
void TourInfo::setLagRechTour(const long value)
{
    m_LagRechTour = value;
}

/***************************************************************************************************************************/
void TourInfo::setIBTBranchNo(const short value)
{
    m_IBTBranchNo = value;
}

/***************************************************************************************************************************/
void TourInfo::setIBTCustomerNo(const int value)
{
    m_IBTCustomerNo = value;
}

/***************************************************************************************************************************/
void TourInfo::setIBTType(const short value)
{
    m_IBTType = value;
}

/***************************************************************************************************************************/
void TourInfo::setTourFound(const bool value)
{
    m_TourFound = value;
}

void TourInfo::setTourClosingDateTimeAvailable(bool value /*= true*/)
{
    this->m_TourClosingDateTimeAvailable = value;
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

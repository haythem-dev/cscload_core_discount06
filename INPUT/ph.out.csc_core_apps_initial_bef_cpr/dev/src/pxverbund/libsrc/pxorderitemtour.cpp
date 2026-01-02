#include "pxorderitemtour.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "tourinfo.hpp"
#include "tourutil.hpp"
#include "customertourlist.hpp"
#include "customertour.hpp"
#include "csccustomer.hpp"
#include <sstream>

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
long pxOrderItemTour::getOrderNo() const
{
    return m_OrderItemTourData.OrderNo;
}

/*----------------------------------------------------------------------------*/
long pxOrderItemTour::getLineNo() const
{
    return m_OrderItemTourData.LineNo;
}

/*----------------------------------------------------------------------------*/
short pxOrderItemTour::getDeliveryBranchNo() const
{
    return m_OrderItemTourData.DeliveryBranchNo;
}

/*----------------------------------------------------------------------------*/
long pxOrderItemTour::getDeliveryDate() const
{
    return m_OrderItemTourData.DeliveryDate;
}

/*----------------------------------------------------------------------------*/
short pxOrderItemTour::getDeliveryTime() const
{
    return m_OrderItemTourData.DeliveryTime;
}

/*----------------------------------------------------------------------------*/
nString pxOrderItemTour::getTourId() const
{
    return (nString)m_OrderItemTourData.TourId;
}

/*----------------------------------------------------------------------------*/
long pxOrderItemTour::getDepartureDate() const
{
    return m_OrderItemTourData.DepartureDate;
}

/*----------------------------------------------------------------------------*/
short pxOrderItemTour::getDepartureTime() const
{
    return m_OrderItemTourData.DepartureTime;
}

/*----------------------------------------------------------------------------*/
nDate pxOrderItemTour::getTourDepartureDateTime(const bool normalized /* = false */) const
{
    return TourUtil::getDateTime( this->getDepartureDate(), this->getDepartureTime(), normalized );
}

/*----------------------------------------------------------------------------*/
long pxOrderItemTour::getIBTTourDate() const
{
    return m_OrderItemTourData.IBTTourDate;
}

/*----------------------------------------------------------------------------*/
long pxOrderItemTour::getIBTDepartureDate() const
{
    long tourHours = TourUtil::getHoursFromTourId(m_OrderItemTourData.IBTTourId);
    long addDays = 0;
    while( tourHours >= 24 )
    {
        ++addDays;
        tourHours -= 24;
    }
    nDate tempdate = TourUtil::getDateTime( this->getDepartureDate(), this->getDepartureTime() );
    tempdate = tempdate.add( addDays );
    return tempdate.GetYYYYMMDD();
}

/*----------------------------------------------------------------------------*/
long pxOrderItemTour::getIBTDepartureTime() const
{
    long tourHours = TourUtil::getHoursFromTourId(m_OrderItemTourData.IBTTourId);
    while( tourHours >= 24 ) tourHours -= 24;
    return (tourHours * 100) + TourUtil::getMinutesFromTourId(m_OrderItemTourData.IBTTourId);
}

/*----------------------------------------------------------------------------*/
nDate pxOrderItemTour::getIBTTourDepartureDateTime() const
{
    return TourUtil::getDateTime( this->getIBTDepartureDate(), this->getIBTDepartureTime() );
}

/*----------------------------------------------------------------------------*/
long pxOrderItemTour::getDrivingDuration() const
{
    return m_OrderItemTourData.DrivingDuration;
}

/*----------------------------------------------------------------------------*/
short pxOrderItemTour::getDeliveryTimeBuffer() const
{
    return m_OrderItemTourData.DeliveryTimeBuffer;
}

/*----------------------------------------------------------------------------*/
nString pxOrderItemTour::getIBTTourId() const
{
    return m_OrderItemTourData.IBTTourId;
}

/*----------------------------------------------------------------------------*/
long pxOrderItemTour::getIBTCustomerNo() const
{
    return m_OrderItemTourData.IBTCustomerNo;
}

/*----------------------------------------------------------------------------*/
short pxOrderItemTour::getIBTType() const
{
    return m_OrderItemTourData.IBTType;
}

/*----------------------------------------------------------------------------*/
short pxOrderItemTour::getDayIBT() const
{
    return m_OrderItemTourData.DayIBT;
}

/*----------------------------------------------------------------------------*/
pxOrderItemTour::~pxOrderItemTour()
{
}

/*----------------------------------------------------------------------------*/
void pxOrderItemTour::Init()
{
    tKDAUFTRAGPOSTOUR record;
    memset( &record, 0, sizeof(tKDAUFTRAGPOSTOUR) );
    Assign( *this, record );
}

/*----------------------------------------------------------------------------*/
pxOrderItemTour::pxOrderItemTour( pxSession* session )
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
pxOrderItemTour::pxOrderItemTour( pxOrderItemTour& src )
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
pxOrderItemTour::pxOrderItemTour( pxSession* session, tKDAUFTRAGPOSTOUR& src )
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
tKDAUFTRAGPOSTOUR& pxOrderItemTour::Assign( tKDAUFTRAGPOSTOUR& dest, const pxOrderItemTour& src )
{
    dest.DeliveryBranchNo = src.getDeliveryBranchNo();
    dest.DeliveryDate = src.getDeliveryDate();
    dest.DeliveryTime = src.getDeliveryTime();
    dest.DepartureDate = src.getDepartureDate();
    dest.DepartureTime = src.getDepartureTime();
    dest.DrivingDuration = src.getDrivingDuration();
    dest.DeliveryTimeBuffer = src.getDeliveryTimeBuffer();
    dest.LineNo = src.getLineNo();
    dest.OrderNo = src.getOrderNo();
    dest.IBTCustomerNo = src.getIBTCustomerNo();
    dest.IBTType = src.getIBTType();
    dest.DayIBT = src.getDayIBT();
    dest.IBTTourDate = src.getIBTTourDate();

    src.getTourId().GetData( dest.TourId );
    src.getIBTTourId().GetData( dest.IBTTourId );

    return dest;
}

/*----------------------------------------------------------------------------*/
pxOrderItemTour& pxOrderItemTour::Assign( pxOrderItemTour& dest, const tKDAUFTRAGPOSTOUR& src )
{
    m_OrderItemTourData.DeliveryBranchNo = src.DeliveryBranchNo;
    m_OrderItemTourData.DeliveryDate = src.DeliveryDate;
    m_OrderItemTourData.DeliveryTime = src.DeliveryTime;
    m_OrderItemTourData.DepartureDate = src.DepartureDate;
    m_OrderItemTourData.DepartureTime = src.DepartureTime;
    m_OrderItemTourData.DrivingDuration = src.DrivingDuration;
    m_OrderItemTourData.DeliveryTimeBuffer = src.DeliveryTimeBuffer;
    m_OrderItemTourData.LineNo = src.LineNo;
    m_OrderItemTourData.OrderNo = src.OrderNo;
    m_OrderItemTourData.IBTCustomerNo = src.IBTCustomerNo;
    m_OrderItemTourData.IBTType = src.IBTType;
    m_OrderItemTourData.DayIBT = src.DayIBT;
    m_OrderItemTourData.IBTTourDate = src.IBTTourDate;

    ((nString)src.TourId).GetData( m_OrderItemTourData.TourId );
    ((nString)src.IBTTourId).GetData( m_OrderItemTourData.IBTTourId );

    return dest;
}

/*----------------------------------------------------------------------------*/
pxOrderItemTour& pxOrderItemTour::operator=( const pxOrderItemTour& src )
{
    tKDAUFTRAGPOSTOUR record;
    Assign( *this, Assign(record, src) );
    return *this;
}

/*----------------------------------------------------------------------------*/
pxOrderItemTour& pxOrderItemTour::operator=( const tKDAUFTRAGPOSTOUR& src)
{
    return Assign( *this, src );
}

/*----------------------------------------------------------------------------*/
int pxOrderItemTour::Get( DBAccessMode /*mode*/ )
{
    tKDAUFTRAGPOSTOUR record;
    memset( &record, 0, sizeof(tKDAUFTRAGPOSTOUR) );
    int retval = nDBRead( &record );
    if( !retval )
    {
       (*this) = record;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
int pxOrderItemTour::Read( const void* record )
{
    return KdAuftragPosTourRead( (tKDAUFTRAGPOSTOUR*)record );
}

/*----------------------------------------------------------------------------*/
int pxOrderItemTour::CompareTo( const nCollectable* That, void* /*p*/, const long /*lparm*/ ) const
{
    pxOrderItemTour *that = (pxOrderItemTour*)That;
    int retval = 0;

    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.DeliveryBranchNo == that->getDeliveryBranchNo() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.DeliveryDate == that->getDeliveryDate() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.DeliveryTime == that->getDeliveryTime() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.DepartureDate == that->getDepartureDate() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.DepartureTime == that->getDepartureTime() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.DrivingDuration == that->getDrivingDuration() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.LineNo == that->getLineNo() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.OrderNo == that->getOrderNo() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.TourId == that->getTourId() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.DeliveryTimeBuffer == that->getDeliveryTimeBuffer() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.IBTCustomerNo == that->getIBTCustomerNo() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.IBTType == that->getIBTType() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.IBTTourId == that->getIBTTourId() ) ? 0 : 1; }
    if( 0 == retval ) { retval = ( this->m_OrderItemTourData.DayIBT == that->getDayIBT() ) ? 0 : 1; }

    return retval;
}

/*----------------------------------------------------------------------------*/
pxOrderItemTourList::pxOrderItemTourList(pxSession* session)
    : nDBRecordSet( session )
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*virtual*/ pxOrderItemTourList::~pxOrderItemTourList()
{
    Clear();
}

/*----------------------------------------------------------------------------*/
void pxOrderItemTourList::Clear()
{
    nDBRecordSet::Clear();
}

/*----------------------------------------------------------------------------*/
pxSession* pxOrderItemTourList::Session()
{
    return (pxSession*) DataBase();
}

/*----------------------------------------------------------------------------*/
int pxOrderItemTourList::EndBrowse(const int cursorid)
{
    return KdAuftragPosTourEndBrowse(cursorid);
}

/*----------------------------------------------------------------------------*/
int pxOrderItemTourList::StartBrowse(const void* keys, const int cursorid)
{
    return KdAuftragPosTourStartBrowse( (tKDAUFTRAGPOSTOUR*)keys, cursorid );
}

/*----------------------------------------------------------------------------*/
int pxOrderItemTourList::GetNext(const void* record, const int cursorid)
{
    return KdAuftragPosTourGetNext( (tKDAUFTRAGPOSTOUR*)record, cursorid );
}

/*----------------------------------------------------------------------------*/
nCollectable* pxOrderItemTourList::AddToList( const void* record, const int /* row */)
{
    pxOrderItemTour *objectp = new pxOrderItemTour(Session(), *(tKDAUFTRAGPOSTOUR*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
bool pxOrderItemTourList::SelectOrderItemTour( const long& cscorderno, const long& positionno )
{
    tKDAUFTRAGPOSTOUR a;
    int count_ = -1;
    memset( &a, 0, sizeof(tKDAUFTRAGPOSTOUR) );

    a.OrderNo = cscorderno;
    a.LineNo = positionno;

    int cursorid = cCRS_DEFAULT;
    count_ = nDBSelect( &a, cursorid, count_, &a );
    return count_ > 0 ? true : false;
}

/*----------------------------------------------------------------------------*/
int pxOrderItemTourList::SelectForOrder(const long& cscorderno)
{
    tKDAUFTRAGPOSTOUR a;
    memset(&a, 0, sizeof(tKDAUFTRAGPOSTOUR));

    a.OrderNo = cscorderno;

    nDBSelect(&a, cKDAUFTRAGPOSTOUR_ORDER, cDEFAULT);
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
bool pxOrderItemTourList::AddOrderItemTour( const long& cscorderno, const long& positionno, const TourInfo& tourinfo )
{
    tKDAUFTRAGPOSTOUR data;
    data.OrderNo = cscorderno;
    data.LineNo = positionno;
    data.DeliveryBranchNo = tourinfo.getIBTBranchNo();
    data.DeliveryDate = TourUtil::getLongDate( tourinfo.getCustomerDeliveryDateTimeMin() );
    data.DeliveryTime = static_cast<short>(TourUtil::getLongTime( tourinfo.getCustomerDeliveryDateTimeMin() ));
    data.DepartureDate = TourUtil::getLongDate( tourinfo.getTourDate() );
    data.DepartureTime = static_cast<short>(TourUtil::getTourIdAsHHMM( tourinfo.getTourID() ));
    data.DrivingDuration = tourinfo.getDrivingDuration();
    data.DeliveryTimeBuffer = tourinfo.getDeliveryTimeBuffer();
    data.IBTCustomerNo = tourinfo.getIBTCustomerNo();
    data.IBTType = tourinfo.getIBTType();
    data.DayIBT = tourinfo.isDayIBT() ? 1 : 0;
    strcpy( data.IBTTourId, tourinfo.getIBTTourID() );
    strcpy( data.TourId, tourinfo.getTourID() );
    data.IBTTourDate = (long)0;
    if( TourUtil::getNullDate() != tourinfo.getIBTTourDate() ) data.IBTTourDate = tourinfo.getIBTTourDate().GetYYYYMMDD();

    bool retval = InsertData( data );

    std::stringstream s;
    s << "AddOrderItemTour order[" << cscorderno << "] positionno [" << positionno << "] TourInfo: " << static_cast<const char* const>(tourinfo.serialize()) << " RC:" << retval;
    TourUtil::writeLog(s);

    return retval;
}

/*----------------------------------------------------------------------------*/
bool pxOrderItemTourList::InsertData( const tKDAUFTRAGPOSTOUR& data )
{
    if (true == pxGlobalNoDatabaseWrite)
    {
        return true;
    }
    tKDAUFTRAGPOSTOUR fil;
    int rc;
    memset( &fil, 0, sizeof(tKDAUFTRAGPOSTOUR) );
    fil = data;
    rc = KdAuftragPosTourInsert( &fil );
    if( 0 == rc )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxOrderItemTourList::RemoveOrderItemTour( const long& cscorderno, const long& positionno )
{
    if (true == pxGlobalNoDatabaseWrite)
    {
        return true;
    }
    tKDAUFTRAGPOSTOUR data;
    data.OrderNo = cscorderno;
    data.LineNo = positionno;

    int rc = KdAuftragPosTourDelete( &data );

    std::stringstream s;
    s << "RemoveOrderItemTour order[" << cscorderno << "] positionno [" << positionno << "] RC:" << rc;
    TourUtil::writeLog(s);

    if( 0 == rc )
    {
        return true;
    }
    return false;
}

bool pxOrderItemTourList::RemoveOrderItemTourIBT( const long& cscorderno, const long& positionno )
{
    if (true == pxGlobalNoDatabaseWrite)
    {
        return true;
    }
    tKDAUFTRAGPOSTOUR data;
    data.OrderNo = cscorderno;
    data.LineNo = positionno;

    int rc = KdAuftragPosTourDeleteIBT( &data );

    std::stringstream s;
    s << "RemoveOrderItemTourIBT order[" << cscorderno << "] positionno [" << positionno << "] RC:" << rc;
    TourUtil::writeLog(s);

    if( 0 == rc )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
nDate pxOrderItemTour::getTourClosingDateTime(short branchno, long customerno, const pxCommType* pickingtype)
{
    CSCCustomer* cust = new CSCCustomer(this->Session(), branchno, customerno );
    CustomerTourList ctlist(this->Session(), branchno, customerno );
    CustomerTour* custtour = ctlist.getTour( this->getTourId(), this->getDepartureDate() );
    if( NULL != custtour )
    {
        delete cust;
        return custtour->getTourClosingDateTime( pickingtype );
    }
    delete cust;
    return this->getDepartureDate();
}

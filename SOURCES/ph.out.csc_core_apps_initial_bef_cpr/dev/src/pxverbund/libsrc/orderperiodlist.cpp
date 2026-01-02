#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxorderperiod.hpp"
#include "tourutil.hpp"
#include "pxoeparm.hpp"

/*----------------------------------------------------------------------------*/
void pxOrderPeriodList::Clear()
{
    nDBRecordSet::Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxSession* pxOrderPeriodList::Session()
{
    return (pxSession*) DataBase();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriodList::~pxOrderPeriodList()
{
    Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriodList::pxOrderPeriodList( pxSession* session )
: nDBRecordSet( session )
{
    nDBSetList(this);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
size_t pxOrderPeriodList::SelectByBranchNoCustomerNo(const short FilialNr, const long IDFNr)
{
    tORDERPERIOD op;
    memset(&op, 0, sizeof(tORDERPERIOD));
    op.BranchNo = FilialNr;
    op.CustomerNo = IDFNr;
    nDBSelect(&op, cCRSORDERPERIOD_SEL_BY_BRANCHNO_CUSTOMERNO, -1);
    return Entries();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
tORDERPERIOD pxOrderPeriodList::SelectCurrentOrderPeriod( const short FilialNr, const long IDFNr, const short WeekDay )
{
    tORDERPERIOD op;
    memset(&op, 0, sizeof(tORDERPERIOD));
    op.BranchNo = FilialNr;
    op.CustomerNo = IDFNr;
    op.WeekDay = WeekDay;
    int count_ = -1;
    int cursorid = cCRSORDERPERIOD_GETORDERPERIODBYWEEKDAY;
    nDBSelect(&op, cursorid, count_, &op);
    return op;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
tORDERPERIOD pxOrderPeriodList::SelectFirstOrderPeriodByWeekday( const short FilialNr, const long IDFNr, const short WeekDay )
{
    tORDERPERIOD op;
    memset(&op, 0, sizeof(tORDERPERIOD));
    op.BranchNo = FilialNr;
    op.CustomerNo = IDFNr;
    op.WeekDay = WeekDay;
    int count_ = -1;
    int cursorid = cCRSORDERPERIOD_GETFIRSTORDERPERIODBYWEEKDAY;
    nDBSelect(&op, cursorid, count_, &op);
    return op;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
tORDERPERIOD pxOrderPeriodList::SelectCurrentOrderPeriodID( const short FilialNr, const long IDFNr )
{
    tORDERPERIOD op;
    memset(&op, 0, sizeof(tORDERPERIOD));
    op.BranchNo = FilialNr;
    op.CustomerNo = IDFNr;
    int count_ = -1;
    int cursorid = cCRSORDERPERIOD_GETCURRENTORDERPERIOD;
    nDBSelect(&op, cursorid, count_, &op);
    return op;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
tORDERPERIOD pxOrderPeriodList::SelectFirstOrderPeriodIDOfWeek( const short FilialNr, const long IDFNr )
{
    tORDERPERIOD op;
    memset(&op, 0, sizeof(tORDERPERIOD));
    op.BranchNo = FilialNr;
    op.CustomerNo = IDFNr;
    int count_ = -1;
    int cursorid = cCRSORDERPERIOD_GETFIRSTORDERPERIODOFWEEK;
    nDBSelect(&op, cursorid, count_, &op);
    return op;
}

/*----------------------------------------------------------------------------*/
pxOrderPeriod pxOrderPeriodList::getFirstOrderPeriodByWeekday(const short filialnr, const long idfnr, const short weekday)
{
    pxOrderPeriod retval(this->Session());
    retval.TourID_ = "";
    retval.Order_Period_ID_ = -1;
    retval.WeekDay_ = -1;
    retval.ID_ = -1;

    this->Clear();
    this->SelectFirstOrderPeriodByWeekday(filialnr, idfnr, weekday);
    if( this->Entries() > 0 )
    {
        pxOrderPeriodListIter iter = pxOrderPeriodListIter(*this);
        pxOrderPeriod* op = NULL;
        if( NULL != (op = (pxOrderPeriod*) ++iter) )
        {
            retval.TourID_ = op->TourID();
            retval.WeekDay_ = op->WeekDay();
            retval.Order_Period_ID_ = op->Order_Period_ID();
            retval.ID_ = op->ID();
        }
    }
    this->Clear();
    return retval;
}

/*----------------------------------------------------------------------------*/
pxOrderPeriod pxOrderPeriodList::getCurrentOrderPeriod(const short filialnr, const long idfnr, short weekday)
{
    pxOrderPeriod retval(this->Session());
    retval.TourID_ = "";
    retval.Order_Period_ID_ = -1;
    retval.WeekDay_ = -1;
    retval.ID_ = -1;
    short toursloadedfor = weekday;

    // step 1: search for orderperiods for the weekday from paraauftragbearb.tourweekday
    this->Clear();
    this->SelectCurrentOrderPeriod(filialnr, idfnr, weekday);
    if( 0 == this->Entries() )
    {
        // step 2: if no orderperiods have been found, try to get the first order period for the next working day
        this->Clear();
        weekday = TourUtil::getDateOfNextWorkingDay( Session()->HoliDayList( filialnr ), filialnr, TourUtil::getCurrentDate() ).GetDayOfWeek();
        this->SelectFirstOrderPeriodByWeekday(filialnr, idfnr, weekday);
        if( 0 == this->Entries() )
        {
            // step 3: if no orderperiods have been found, try to get the first order period for the week
            this->Clear();
            this->SelectFirstOrderPeriodIDOfWeek(filialnr, idfnr);
        }
    }

    if( this->Entries() > 0 )
    {
        pxOrderPeriodListIter iter = pxOrderPeriodListIter(*this);
        pxOrderPeriod* op = NULL;
        if( NULL != (op = (pxOrderPeriod*) ++iter) )
        {
            retval.TourID_ = op->TourID();
            retval.WeekDay_ = op->WeekDay();
            retval.Order_Period_ID_ = op->Order_Period_ID();
            retval.ID_ = op->ID();

            // if tours have been loaded not for the current weekday
            if( toursloadedfor != -1 )
            {
                if( toursloadedfor != TourUtil::getCurrentWeekday() )
                {
                    retval.WeekDay_ = TourUtil::getCurrentWeekday();
                }
            }
        }
    }

    this->Clear();
    return retval;
}

/*----------------------------------------------------------------------------*/
pxOrderPeriod pxOrderPeriodList::getCurrentOrderPeriodID(const short filialnr, const long idfnr)
{
    pxOrderPeriod retval(this->Session());
    retval.TourID_ = "";
    retval.Order_Period_ID_ = -1;
    retval.WeekDay_ = -1;

    this->Clear();
    this->SelectCurrentOrderPeriodID(filialnr, idfnr);
    if( 0 == this->Entries() )
    {
        this->SelectFirstOrderPeriodIDOfWeek(filialnr, idfnr);
    }
    if( this->Entries() > 0 )
    {
        pxOrderPeriodListIter iter = pxOrderPeriodListIter(*this);
        pxOrderPeriod* op = NULL;
        if( NULL != (op = (pxOrderPeriod*) ++iter) )
        {
            retval.Order_Period_ID_ = op->Order_Period_ID();
            retval.TourID_ = op->TourID();
            retval.WeekDay_ = op->WeekDay();
            retval.ID_ = op->ID();
        }
    }
    this->Clear();

    return retval;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderPeriodList::EndBrowse( const int cursorid )
{
    return pxOrderPeriodEndBrowse(cursorid);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderPeriodList::GetNext( const void* record, const int cursorid )
{
    return pxOrderPeriodGetNext((tORDERPERIOD*)record, cursorid);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderPeriodList::StartBrowse( const void* keys, const int cursorid)
{
    struct tORDERPERIOD* recordp;
    recordp = (tORDERPERIOD*)keys;
    nClock time;
    time -= Session()->getOrderEntryParam(recordp->BranchNo)->TourVerspaetung() * 60L;
    long currenttime = time.GetHHMMSS() / 100; // currentime HHMM

    return pxOrderPeriodStartBrowse((tORDERPERIOD*)keys, cursorid, currenttime) ;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
nCollectable* pxOrderPeriodList::AddToList( const void* record, const int /* row */ )
{
    // construct new object:
    pxOrderPeriod *objectp = new pxOrderPeriod(Session(), *(tORDERPERIOD*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/

/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXEVENTREASON
Event Reason Class.

REVISION HISTORY

08 Okt 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXEVENTREASON_INC
#define PXEVENTREASON_INC

#include "pxbase/pxrecord.hpp"

struct tEVENTREASONS;

class pxEventReason : public pxDBRecord
{
public:

/*----------------------------------------------------------------------------*/
/*  Event Reason Code Definitions                                             */
/*----------------------------------------------------------------------------*/
    enum EventCodes
    {
       NoReasonCode = 0,
       WithReleasedDeliveryPositions = 1,    // #1  order with released delivery positions(nachlieferpos)
       LimitCheck                       ,    // #2  Max PosMenge überschritten
       NoValidRoute                     ,    // #3  Do Route check
       ReleaseableRestDeliveryPos       ,    // #4  ther are releasable rest delivery positions available
       CorruptLimitCheck                ,    // #5  Value of corrupt values exceeded
       HighValuePosition                ,    // #6  Value of position higher then 10000000.00
       RebateArticleSelection           ,    // #7  Possibility to choice a rebate article
       NoCicsAvailable                  ,    // #8  No Cics available during close order
       OrderIsNullDocument              ,    // #9  Order has no value(NullDocument)
       CallBack                         ,    // #10 Please callback the customer
       OrderWithFreeText                ,    // #11 Order with free text
       DoubleOrder                      ,    // #12 Order send double
       TransMissionCanceled             ,    // #13 Transmission canceled after receiving record type 99
       DeferOrderByParam                ,    // #14 Defer Order by customer parameter SKdAuftragZurueck
       WrongCustomerNumber              ,    // #15 Order came in for a wrong customer
       CreditLimitExceeded              ,    // #16 Customers credit-limit exceeded
       NotCloseDelayedDeliveryOrder     ,    // #17 Do not close delayed delivery order
       TotalTransPosExceeded            ,    // #18 Total transferred positions higher then parameter AnzPosZu
       NoCloseDefectAndIBTPositions     ,    // #19 Order with defect or IBT position and customers parameter NoCloseDefVB
       CheckOrderOverdrive              ,    // #20 Order value too low on order type OV depend on customer conditions
       OrderTypeIsDeferOrder            ,    // #21 Defer order on order type parameter DeferOrder
       ErrorOnMethodeOrderType          ,    // #22 Ordertype or combinations of ordertype,commitype,bookingtype not definded
       CustomerError                    ,    // #23 Customer not found
	   MSV3InvalidTourInOrderPeriod		,	 // #24 TourID aus MSV3-Bestellfenster konnte nicht vergeben werden
	   CremaVotingInProcess				,	 // #25 es müssen noch weitere Personen über die CREMA- Freigabe abstimmen
	   MSV3CancelledPartialDelivery			 // #26 MSV3-Bestellung storniert wegen Teillieferung
    };


// destructor:
    virtual           ~pxEventReason();
// constructors:
                      pxEventReason(pxEventReason& src);
                      pxEventReason(pxSession *session);
                      pxEventReason(pxSession *session, EventCodes EventCode,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxEventReason&      operator=(const pxEventReason& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int      Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int      Put();

//  Queries:

    EventCodes        EventCode       () {return EventCode_;                       }
    nString&          EventDescription() {return EventDescription_;                }


protected:
                      pxEventReason(pxSession *session, tEVENTREASONS& src);
    pxEventReason&      operator=(const tEVENTREASONS& src);
    friend
    pxEventReason&    Assign(pxEventReason& dest, const tEVENTREASONS& src);
    friend
    tEVENTREASONS&    Assign(tEVENTREASONS& dest, const pxEventReason& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int      Read(const void *record);
    virtual  int      ReadLock(const void *record);
    virtual  int      Insert(const void *record);
    virtual  int      Update(const void *record);
    void              Init();

    EventCodes        EventCode_;            // EventCode
    nString           EventDescription_;     // Event description


private:
    friend class pxEventReasonList;
};

class pxEventReasonList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxEventReasonList() {Clear();}
                      pxEventReasonList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const short EventCode, const int count = cDEFAULT);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxEventReasonListIter;
};

class pxEventReasonListIter : public nDListCollectIter
{

public:
// constructors:
    pxEventReasonListIter(pxEventReasonList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxEventReasonListIter() {;}

};

#endif

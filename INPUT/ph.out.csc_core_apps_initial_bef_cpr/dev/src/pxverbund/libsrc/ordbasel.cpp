#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxorderperiod.hpp"
#include "pxeventreason.hpp"
#include "tourutil.hpp"
#include "pxdefs.hpp"

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxOrderList :: pxOrderList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    sort_ = SortDefault;
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using a combination of the possible key values.      */
/*----------------------------------------------------------------------------*/
size_t
pxOrderList :: SelectByCustomerNo
(
    const long    IDFNr,               // customer number
    const nString& TourId,
    const nString& GeraetName,
    const short   FilialNr,
    ...                                 // order state values
)

{
    va_list  arglist;
    va_start (arglist, FilialNr);

    tKDAUFTRAG a;
    memset(&a, 0, sizeof(tKDAUFTRAG));     // zero out entire record buffer

    a.IDFNr        = IDFNr;
    TourId.GetData(a.TourId);
    GeraetName.GetData(a.GeraetName);
    a.FilialNr     = FilialNr;

    nString  like('_', Order::cStateLast);
    like(0,1) = '0';                    // first state must be always 0
    ::pxStatesToLikeString(like, arglist);
    like.GetData(a.KdAuftragStat);
    va_end(arglist);
    return SelectByKDAUFTRAGStruct(&a);
}

/*----------------------------------------------------------------------------*/
/*  select orders for aaorderclose                                            */
/*----------------------------------------------------------------------------*/
size_t pxOrderList::SelectForAutomaticClosure(const short branchno, const char* postponereason, ... )
{
    va_list  arglist;
    va_start (arglist, postponereason);

    tKDAUFTRAG a;
    memset(&a, 0, sizeof(tKDAUFTRAG));     // zero out entire record buffer

    a.FilialNr = branchno;
    nString postponereason_tmp(postponereason);
    postponereason_tmp.GetData(a.ZuGrund);

    nString  like('_', Order::cStateLast);
    like(0,1) = '0';
    ::pxStatesToLikeString(like, arglist);
    like.GetData(a.KdAuftragStat);

    int cursorid = 0;
    cursorid += cCRSORD_AUTOMATICCLOSURE;
    nDBSelect(&a, cursorid, -1);
    va_end(arglist);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using a combination of the possible key values.      */
/*----------------------------------------------------------------------------*/
size_t
pxOrderList :: SelectVSE
(
    const pxOrder::OrderSendStatusEnum VSEstatus,
    const int     count_,
    const short   FilialNr,
    const int     SelMod,
    ...                                 // order state values
)

{
    va_list  arglist;
    va_start (arglist, SelMod);

    tKDAUFTRAG a;
    memset(&a, 0, sizeof(tKDAUFTRAG));     // zero out entire record buffer

    a.FilialNr     = FilialNr;
    a.SendeStatus  = static_cast<short>(VSEstatus);

    nString  like('_', Order::cStateLast);
    like(0,1) = '0';                    // first state must be always 0
    ::pxStatesToLikeString(like, arglist);
    like.GetData(a.KdAuftragStat);
    va_end(arglist);
    return SelectByKDAUFTRAGStruct(&a,count_,SelMod);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using a combination of the possible key values.      */
/*----------------------------------------------------------------------------*/
size_t
pxOrderList :: SelectBatchOrder
(
    const short   VertriebszentrumNr,
    const long    KundenNr,
    const nString& ZuGrund,
    const long    BatchAuftragNr
    ...                                 // order state values
)

{
    va_list  arglist;
    va_start (arglist,BatchAuftragNr);

    tKDAUFTRAG a;
    memset(&a, 0, sizeof(tKDAUFTRAG));     // zero out entire record buffer
    a.KundenNr            = KundenNr;
    a.VertriebszentrumNr  = VertriebszentrumNr;
    ZuGrund.GetData(a.ZuGrund);
    a.BatchAuftragNr = BatchAuftragNr;

    nString  like('_', Order::cStateLast);
    like(0,1) = '0';                    // first state must be always 0
    ::pxStatesToLikeString(like, arglist);
    like.GetData(a.KdAuftragStat);
    va_end(arglist);
    return SelectByKDAUFTRAGStruct(&a);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tKDAUFTRAG structure.  */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxOrderList :: SelectByKDAUFTRAGStruct
(
          tKDAUFTRAG  *auftragp,
    const int        count_,
    const int        SelMod
)

{
    // Set the cursor id:
    // tCRSID_ORDER cursorid = 0;
    int cursorid = 0;

    if (auftragp->IDFNr > 0)
    {
       cursorid |= cCRSORD_IDFNr;
    }
    if ( *(auftragp->TourId) )
    {
       cursorid |= cCRSORD_TourId;
    }
    if ( *(auftragp->GeraetName) )
    {
       cursorid |= cCRSORD_GeraetName;
    }
    if (auftragp->FilialNr > 0)
    {
       cursorid |= cCRSORD_FilialNr;
    }
    if (auftragp->KundenNr > 0)
    {
       cursorid |= cCRSORD_KundenNr;
    }
    if (auftragp->VertriebszentrumNr > 0)
    {
       cursorid |= cCRSORD_VertriebszentrumNr;
    }
    if ( *(auftragp->KdAuftragStat) )
    {
       cursorid |= cCRSORD_KdAuftragStat;
    }
    if (SelMod == 0)
    {
       cursorid |= cCRSORD_SelectModeEven;
    }
    if (SelMod == 1)
    {
       cursorid |= cCRSORD_SelectModeOdd;
    }
    if ( *(auftragp->ZuGrund) )
    {
       cursorid |= cCRSORD_ZuGrund;
    }
    if (auftragp->BatchAuftragNr > 0)
    {
       cursorid |= cCRSORD_BatchAuftragNr;
    }
    if ( *(auftragp->KdAuftragArt) )
    {
        cursorid |= cCRSORD_KdAuftragArt;
    }
    if ( auftragp->OrderPeriodID > 0 )
    {
        cursorid |= cCRSORD_OrderPeriodID;
    }

    nDBSelect(auftragp, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxOrder *objectp = new pxOrder(Session(), *(tKDAUFTRAG*) record); // construct new object
    InsertAscending(objectp, (long)sort_);
    return objectp;
}

int
pxOrderList :: EndBrowse
(
    const int  cursorid
)
{

    return pxAuftragEndBrowse(cursorid);
}


int
pxOrderList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxAuftragGetNext((tKDAUFTRAG*)record, cursorid);
}

int
pxOrderList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxAuftragStartBrowse((tKDAUFTRAG*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  The following overloaded "NewOrder" functions create a new order object   */
/*  instance, open it for order item entry processing and add it to the list. */
/*  In case of a successful construction, a pointer to the new order object   */
/*  is returned, otherwise a NULL pointer is returned, and an appropiate error*/
/*  is stored within the nError object of the list.                           */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderList :: NewOrder
(
    pxCustBase& customer
)
{
    pxOrder  *order = new pxOrder(Session(), customer);
    return   AddNewOrder(order);
}
pxOrder*
pxOrderList :: NewOrderInfo
(
    pxCustBase* customer
)
{
    pxOrder  *order = new pxOrder(Session(), customer, pxOrder::INFO_ORDER_TYPE_DEFAULT);
    return   AddNewOrder(order);
}

pxOrder*
pxOrderList :: NewOrderProforma
(
    pxCustBase* customer
)
{
    pxOrder  *order = new pxOrder(Session(), customer, pxOrder::INFO_ORDER_TYPE_PROFORMA);
    return   AddNewOrder(order);
}

/* open new InfoOrder for MSV3 */
pxOrder* pxOrderList :: NewMSV3InfoOrder( pxCustBase* customer, const pxOrderPeriod& _orderperiod)
{
    pxOrder  *order = new pxOrder(Session(), customer, pxOrder::INFO_ORDER_TYPE_DEFAULT);
    order->SetOrderPeriodID( _orderperiod.ID() );
    if( 1 == order->Param()->OrderPeriodTourAssignment() && _orderperiod.TourID().Length() > 0 )
    {
       int rc = 0;
       if( _orderperiod.WeekDay() == TourUtil::getCurrentWeekday() )
       {
          order->DatumAuslieferung_ = TourUtil::getNullDate();
          order->OrderTourId_ = ""; // OK
          rc = order->RouteAssign( _orderperiod.TourID(), -1 );
       }
       else
       {
          order->DatumAuslieferung_ = TourUtil::getNullDate();
          order->OrderTourId_ = ""; // OK
          rc = order->RouteAssign( _orderperiod.TourID(), _orderperiod.WeekDay() );
       }
       if( rc != 0 )
       {
          order->SetEventCode( pxEventReason::MSV3InvalidTourInOrderPeriod );
          order->DatumAuslieferung_ = TourUtil::getNullDate();
          order->OrderTourId_ = ""; // OK
          rc = order->RouteAssign();
          if( rc != 0 )
          {
             order->ClearError();
          }
       }
    }
    return   AddNewOrder(order);
}


pxOrder*
pxOrderList :: NewOrder
(
    pxCustBase        *customer,
    pxOrderValidTrans *vtp,
    const  long       n,
    const  long       DeliveryDate,
    const  OriginTypeEnum batchschreiben
)
{
    pxOrder  *order = new pxOrder(customer,vtp,n,DeliveryDate, batchschreiben);
    return   AddNewOrder(order);
}

/* open new order for MSV3 */
pxOrder* pxOrderList::NewOrderMSV3( pxCustBase* customer, const pxOrderValidTrans* vt, const long n, const nString& _orderlabel, const pxOrderPeriod& _orderperiod )
{
    int rc = 0;
    pxOrder *order = new pxOrder(customer,vt,n);
    order->SetOrderLabel( _orderlabel );
    order->SetOrderPeriodID( _orderperiod.ID() );

    if (1 == order->Param()->OrderPeriodTourAssignment() && _orderperiod.TourID().Length() > 0)
    {
        order->DatumAuslieferung_ = TourUtil::getNullDate();
        TourInfo ti = order->getNormalDeliveryTourInfo(_orderperiod.TourID(), _orderperiod.WeekDay());

        short weekdayForTourAssignment = ti.getTourDate().GetDayOfWeek();
        if (ti.getTourDate().GetDayOfWeek() == TourUtil::getCurrentWeekday())
        {
            weekdayForTourAssignment = -1;
        }
        rc = order->RouteAssign(ti.getTourID(), weekdayForTourAssignment);
        if (order->DatumAuslieferung() != TourUtil::getNullDate()) { rc = 1; } // Fixe Bindung gilt nur für den aktuellen Tag!!!

        if (rc != 0)
        {
            order->SetEventCode(pxEventReason::MSV3InvalidTourInOrderPeriod);
            order->DatumAuslieferung_ = TourUtil::getNullDate();
            order->OrderTourId_ = ""; // OK
            rc = order->RouteAssign();
            if (rc != 0)
            {
                order->ClearError();
            }
        }
    }

    return AddNewOrder(order);
}

/*----------------------------------------------------------------------------*/
/*  Add the new customer order object to the list.                            */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderList :: AddNewOrder
(
    pxOrder    *order
)

{
    if ( order->IsGoodState() )         // ensure object is well constructed
    {
       Append(order);                   // then put it on the list
       return order;
    }
    Error() = (order->Error());         // copy error object instance
    delete order;                       // and delete current order object
    return NULL;
}

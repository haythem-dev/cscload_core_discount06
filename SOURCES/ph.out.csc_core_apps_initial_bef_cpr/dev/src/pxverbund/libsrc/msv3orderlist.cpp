#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxmsv3order.hpp"

/*----------------------------------------------------------------------------*/
void pxMSV3OrderList::Clear()
{
    nDBRecordSet::Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxSession* pxMSV3OrderList::Session()
{ 
    return (pxSession*) DataBase();
}    
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxMSV3OrderList::~pxMSV3OrderList() 
{
    Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxMSV3OrderList::pxMSV3OrderList( pxSession* session )
: nDBRecordSet( session )
{
    nDBSetList(this);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
size_t pxMSV3OrderList::SelectMSV3OrderLabel( const short FilialNr, const long IDFNr, const nString& AuftragsArt, const long OrderPeriodID )
{
    tKDAUFTRAG a;
    memset(&a, 0, sizeof(tKDAUFTRAG));
    a.FilialNr = FilialNr;
    a.IDFNr = IDFNr;
    AuftragsArt.GetData(a.KdAuftragArt);
    a.OrderPeriodID = OrderPeriodID;

    int count_ = -1;
    int cursorid = cCRSMSV3ORDER_GETDISTINCTORDERLABEL;
    nDBSelect(&a, cursorid, count_, &a);
    return Entries();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxMSV3OrderList::EndBrowse( const int cursorid )
{
    return pxMSV3OrderEndBrowse(cursorid);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxMSV3OrderList::GetNext( const void* record, const int cursorid )
{
    return pxMSV3OrderGetNext((tKDAUFTRAG*)record, cursorid);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxMSV3OrderList::StartBrowse( const void* keys, const int cursorid )
{
    return pxMSV3OrderStartBrowse((tKDAUFTRAG*)keys, cursorid);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
nCollectable* pxMSV3OrderList::AddToList( const void* record, const int /* row */ )
{
    // construct new 'pxDiscount' object:
    pxMSV3Order *objectp = new pxMSV3Order(Session(), *(tKDAUFTRAG*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/

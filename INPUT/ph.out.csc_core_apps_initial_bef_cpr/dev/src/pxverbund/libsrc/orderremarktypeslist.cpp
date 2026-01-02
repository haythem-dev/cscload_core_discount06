#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxorderremarktypes.hpp"

/*----------------------------------------------------------------------------*/
pxOrderRemarkTypeList::pxOrderRemarkTypeList(pxSession* session)
    : nDBRecordSet( session )
{
    nDBSetList(this);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRemarkTypeList::EndBrowse(const int cursorid)
{
    return pxOrderRemarkTypesEndBrowse(cursorid);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRemarkTypeList::GetNext(const void* record, const int cursorid)
{
    return pxOrderRemarkTypesGetNext( (tORDERREMARKTYPES*)record, cursorid );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRemarkTypeList::StartBrowse(const void* keys, const int cursorid)
{
    return pxOrderRemarkTypesStartBrowse( (tORDERREMARKTYPES*)keys, cursorid );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
nCollectable* pxOrderRemarkTypeList::AddToList( const void* record, const int /* row */)
{
    pxOrderRemarkType *objectp = new pxOrderRemarkType(Session(), *(tORDERREMARKTYPES*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*virtual*/ pxOrderRemarkTypeList::~pxOrderRemarkTypeList()
{
    Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxSession* pxOrderRemarkTypeList::Session()
{ 
    return (pxSession*) DataBase();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrderRemarkTypeList::Clear()
{
    nDBRecordSet::Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRemarkTypeList::SelectOrderRemarkTypes( pxOrderRemarkType::OrderRemarkLevel level /*= eOrderRemarkTypeBoth*/ )
{
    tORDERREMARKTYPES a;
    int count_ = -1;
    memset( &a, 0, sizeof(tORDERREMARKTYPES) );

    int cursorid = cCRSORDERREMARKTYPES_GETALLORDERREMARKTYPES;
    switch( level )
    {
        case pxOrderRemarkType::eOrderRemarkTypeHeaderLevel:
            cursorid = cCRSORDERREMARKTYPES_GETHEADERORDERREMARKTYPES;
            break;
        case pxOrderRemarkType::eOrderRemarkTypeLineLevel:
            cursorid = cCRSORDERREMARKTYPES_GETLINEORDERREMARKTYPES;
            break;
        case pxOrderRemarkType::eOrderRemarkTypeBoth:
        default:
            cursorid = cCRSORDERREMARKTYPES_GETALLORDERREMARKTYPES;
            break;
    }

    count_ = nDBSelect( &a, cursorid, count_, &a );
    return (count_ > 0);
}
/*----------------------------------------------------------------------------*/

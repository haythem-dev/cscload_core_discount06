#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxorderrelationno.hpp"

/*----------------------------------------------------------------------------*/
pxOrderRelationNoList::pxOrderRelationNoList(pxSession* session)
    : nDBRecordSet( session )
{
    nDBSetList(this);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNoList::EndBrowse(const int cursorid)
{
    return pxOrderRelationNoEndBrowse(cursorid);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNoList::GetNext(const void* record, const int cursorid)
{
    return pxOrderRelationNoGetNext( (tORDERRELATIONNO*)record, cursorid );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNoList::StartBrowse(const void* keys, const int cursorid)
{
    return pxOrderRelationNoStartBrowse( (tORDERRELATIONNO*)keys, cursorid );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
nCollectable* pxOrderRelationNoList::AddToList( const void* record, const int /* row */)
{
    pxOrderRelationNo *objectp = new pxOrderRelationNo(Session(), *(tORDERRELATIONNO*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*virtual*/ pxOrderRelationNoList::~pxOrderRelationNoList()
{
    Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxSession* pxOrderRelationNoList::Session()
{
    return (pxSession*) DataBase();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrderRelationNoList::Clear()
{
    nDBRecordSet::Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRelationNoList::InsertData( const tORDERRELATIONNO& data )
{
    tORDERRELATIONNO fil;
    int rc;
    memset( &fil, 0, sizeof(tORDERRELATIONNO) );
    fil = data;
    rc = pxOrderRelationNoInsert( &fil );
    if( 0 == rc ) return true;
    return false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRelationNoList::SetOrderRelationNo( long cscorderno, long relationno, OrderRelationNoTypeEnum relationnotype )
{
    this->RemoveOrderRelationNo( cscorderno, relationnotype );
    tORDERRELATIONNO data;
    data.CSCOrderNo = cscorderno;
    data.RelationNo = relationno;
    data.RelationNoType = static_cast<short>(relationnotype);
    return InsertData( data );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRelationNoList::RemoveOrderRelationNo( long cscorderno, OrderRelationNoTypeEnum relationnotype )
{
    tORDERRELATIONNO data;
    data.CSCOrderNo = cscorderno;
    data.RelationNoType = static_cast<short>(relationnotype);
    int rc = pxOrderRelationNoDelete( &data );
    if( 0 == rc )
    {
        return true;
    }
    return false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRelationNoList::SelectOrderRelationNoByOrderNo( long cscorderno )
{
    tORDERRELATIONNO a;
    int count_ = -1;
    memset( &a, 0, sizeof(tORDERRELATIONNO) );
    a.CSCOrderNo = cscorderno;
    int cursorid = cCRSORDERRELATIONNO_GETORDERRELATIONNO;
    count_ = nDBSelect( &a, cursorid, count_, &a );
    return count_ > 0 ? true : false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRelationNoList::SelectOrderRelationNoByOrderNoAndType( long cscorderno, OrderRelationNoTypeEnum relationnotype )
{
    tORDERRELATIONNO a;
    int count_ = -1;
    memset( &a, 0, sizeof(tORDERRELATIONNO) );
    a.CSCOrderNo = cscorderno;
    a.RelationNoType = static_cast<short>(relationnotype);
    int cursorid = cCRSORDERRELATIONNO_GETBYTYPE;
    count_ = nDBSelect( &a, cursorid, count_, &a );
    return count_ > 0 ? true : false;
}
/*----------------------------------------------------------------------------*/

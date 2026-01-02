#include "pxorderremarks.hpp"
#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
pxGenericOrderRemarkList::pxGenericOrderRemarkList(pxSession* session)
    : nDBRecordSet( session )
{
    nDBSetList(this);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxGenericOrderRemarkList::EndBrowse(const int cursorid)
{
    return pxGenericOrderRemarkEndBrowse(cursorid);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxGenericOrderRemarkList::GetNext(const void* record, const int cursorid)
{
    return pxGenericOrderRemarkGetNext( (tORDERREMARKS*)record, cursorid );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxGenericOrderRemarkList::StartBrowse(const void* keys, const int cursorid)
{
    return pxGenericOrderRemarkStartBrowse( (tORDERREMARKS*)keys, cursorid );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
nCollectable* pxGenericOrderRemarkList::AddToList( const void* record, const int /* row */)
{
    pxGenericOrderRemark *objectp = new pxGenericOrderRemark(Session(), *(tORDERREMARKS*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*virtual*/ pxGenericOrderRemarkList::~pxGenericOrderRemarkList()
{
    Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxSession* pxGenericOrderRemarkList::Session()
{
    return (pxSession*) DataBase();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxGenericOrderRemarkList::Clear()
{
    nDBRecordSet::Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxGenericOrderRemarkList::SelectOrderRemarksByOrderNo( const long cscorderno )
{
    tORDERREMARKS a;
    int count_ = -1;
    memset( &a, 0, sizeof(tORDERREMARKS) );

    a.CSCOrderNo = cscorderno;

    int cursorid = cCRSORDERREMARKS_GETALLORDERREMARKS;
    count_ = nDBSelect( &a, cursorid, count_, &a );
    return count_ > 0 ? true : false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxGenericOrderRemarkList::SelectOrderRemarksByOrderLine( const long cscorderno, const long positionno )
{
    tORDERREMARKS a;
    int count_ = -1;
    memset( &a, 0, sizeof(tORDERREMARKS) );

    a.CSCOrderNo = cscorderno;
    a.PositionNo = positionno;

    int cursorid = cCRSORDERREMARKS_GETALLORDERLINEREMARKS;
    count_ = nDBSelect( &a, cursorid, count_, &a );
    return count_ > 0 ? true : false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxGenericOrderRemarkList::SelectOrderRemarksByOrderNoAndType( const long cscorderno, const OrderRemarkTypeEnum remarktype )
{
    tORDERREMARKS a;
    int count_ = -1;
    memset( &a, 0, sizeof(tORDERREMARKS) );

    a.CSCOrderNo = cscorderno;
    a.RemarkType = static_cast<short>(remarktype);

    int cursorid = cCRSORDERREMARKS_GETALLORDERREMARKSBYTYPE;
    count_ = nDBSelect( &a, cursorid, count_, &a );
    return count_ > 0 ? true : false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxGenericOrderRemarkList::SelectOrderRemarksByOrderLineAndType( const long cscorderno, const long positionno, const OrderRemarkTypeEnum remarktype )
{
    tORDERREMARKS a;
    int count_ = -1;
    memset( &a, 0, sizeof(tORDERREMARKS) );

    a.CSCOrderNo = cscorderno;
    a.PositionNo = positionno;
    a.RemarkType = static_cast<short>(remarktype);

    int cursorid = cCRSORDERREMARKS_GETALLORDERLINEREMARKSBYTYPE;
    count_ = nDBSelect( &a, cursorid, count_, &a );
    return count_ > 0 ? true : false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxGenericOrderRemarkList::AddOrderRemark( const long cscorderno, const long positionno, const OrderRemarkTypeEnum remarktype, const basar::VarString& remarktext, const short textnumber /*= 0*/ )
{
    if (true == pxGlobalNoDatabaseWrite)
    {
        return true;
    }
    tORDERREMARKS data;
    data.CSCOrderNo = cscorderno;
    data.PositionNo = positionno;
    data.RemarkType = static_cast<short>(remarktype);
    data.TextNumber = textnumber;
    strcpy( data.RemarkText, remarktext.c_str() );
    return InsertData( data );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxGenericOrderRemarkList::ChangeOrderRemark( const long cscorderno, const long positionno, const OrderRemarkTypeEnum remarktype, const basar::VarString& remarktext, const short textnumber /*= 0*/ )
{
    if (true == pxGlobalNoDatabaseWrite)
    {
        return true;
    }
    tORDERREMARKS data;
    data.CSCOrderNo = cscorderno;
    data.PositionNo = positionno;
    data.RemarkType = static_cast<short>(remarktype);
    data.TextNumber = textnumber;
    strcpy( data.RemarkText, remarktext.c_str() );
    int rc = pxGenericOrderRemarkUpdate( &data );
    if( 0 == rc )
    {
        return true;
    }
    return false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxGenericOrderRemarkList::RemoveOrderRemark( const long cscorderno, const long positionno, const OrderRemarkTypeEnum remarktype, const basar::VarString& remarktext, const short textnumber /*= 0*/ )
{
    if (true == pxGlobalNoDatabaseWrite)
    {
        return true;
    }
    tORDERREMARKS data;
    data.CSCOrderNo = cscorderno;
    data.PositionNo = positionno;
    data.RemarkType = static_cast<short>(remarktype);
    data.TextNumber = textnumber;
    strcpy( data.RemarkText, remarktext.c_str() );
    int rc = pxGenericOrderRemarkDelete( &data );
    if( 0 == rc )
    {
        return true;
    }
    return false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxGenericOrderRemarkList::InsertData( const tORDERREMARKS& data )
{
    tORDERREMARKS fil;
    int rc;
    memset( &fil, 0, sizeof(tORDERREMARKS) );
    fil = data;
    rc = pxGenericOrderRemarkInsert( &fil );
    if( 0 == rc )
    {
        return true;
    }
    return false;
}
/*----------------------------------------------------------------------------*/

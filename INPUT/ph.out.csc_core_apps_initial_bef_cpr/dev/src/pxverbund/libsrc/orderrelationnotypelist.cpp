#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxorderrelationnotype.hpp"

/*----------------------------------------------------------------------------*/
pxOrderRelationNoTypeList::pxOrderRelationNoTypeList(pxSession* session)
    : nDBRecordSet( session )
{
    nDBSetList(this);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNoTypeList::EndBrowse(const int cursorid)
{
    return pxOrderRelationNoTypesEndBrowse(cursorid);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNoTypeList::GetNext(const void* record, const int cursorid)
{
    return pxOrderRelationNoTypesGetNext( (tORDERRELATIONNOTYPES*)record, cursorid );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNoTypeList::StartBrowse(const void* keys, const int cursorid)
{
    return pxOrderRelationNoTypesStartBrowse( (tORDERRELATIONNOTYPES*)keys, cursorid );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
nCollectable* pxOrderRelationNoTypeList::AddToList( const void* record, const int /* row */)
{
    pxOrderRelationNoType *objectp = new pxOrderRelationNoType(Session(), *(tORDERRELATIONNOTYPES*)record );
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*virtual*/ pxOrderRelationNoTypeList::~pxOrderRelationNoTypeList()
{
    Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxSession* pxOrderRelationNoTypeList::Session()
{
    return (pxSession*) DataBase();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrderRelationNoTypeList::Clear()
{
    nDBRecordSet::Clear();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRelationNoTypeList::SelectOrderRelationNoTypes()
{
    tORDERRELATIONNOTYPES a;
    int count_ = -1;
    memset( &a, 0, sizeof(tORDERRELATIONNOTYPES) );
    int cursorid = cCRSORDERRELATIONNOTYPES;
    count_ = nDBSelect( &a, cursorid, count_, &a );
    return (count_ > 0);
}
/*----------------------------------------------------------------------------*/

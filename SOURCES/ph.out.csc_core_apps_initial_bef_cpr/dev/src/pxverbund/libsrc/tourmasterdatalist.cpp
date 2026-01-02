#include "tourmasterdatalist.hpp"
#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "tourmasterdata.hpp"

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
TourMasterDataList::TourMasterDataList( pxSession* session )
    : nDBRecordSet( session )
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
TourMasterDataList::~TourMasterDataList()
{
    Clear();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool TourMasterDataList::getTourMasterData( const short branchno, const nString& tourid )
{
    this->m_BranchNo = branchno;

    tTOURMASTERDATA data;
    memset( &data, 0, sizeof(tTOURMASTERDATA) );
    int cursorid = cCRSTOURMASTERDATA_GETBYTOURID;
    data.BranchNo = this->m_BranchNo;
    tourid.GetData( data.TourID );

    int count_ = -1;
    count_ = nDBSelect( &data, cursorid, count_, &data );
    return count_ > 0 ? true : false;
}

/*############################################################################################################################*/
/*                                       P R O T E C T E D                                                                    */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
nCollectable* TourMasterDataList::AddToList( const void* record, const int /* row */)
{
    TourMasterData *objectp = new TourMasterData( getSession(), *(tTOURMASTERDATA*) record  );
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void TourMasterDataList::Clear()
{
    nDBRecordSet::Clear();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int TourMasterDataList::EndBrowse(const int cursorid)
{
    return TourMasterDataEndBrowse(cursorid);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int TourMasterDataList::GetNext(const void* record, const int cursorid)
{
    return TourMasterDataGetNext( (tTOURMASTERDATA*)record, cursorid);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int TourMasterDataList::StartBrowse(const void* keys, const int cursorid)
{
    return TourMasterDataStartBrowse( (tTOURMASTERDATA*) keys, this->getSession()->getDatabaseName( this->m_BranchNo ).c_str(), cursorid);
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
pxSession* TourMasterDataList::getSession()
{
    return (pxSession*) DataBase();
}

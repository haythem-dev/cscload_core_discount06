#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "ibtbranches.hpp"
#include "ibtbrancheslist.hpp"
#include "tourutil.hpp"
#include "pxoeparm.hpp"

/*----------------------------------------------------------------------------*/
bool IBTBranchesList::isIBTPossibleNow( short localbranchno, short ibtbranchno )
{
    pxTimeTypeList timetypelist = this->getIBTTimeListByBranch( localbranchno, ibtbranchno );
    if( timetypelist.Entries() > 0 )
    {
        if( timetypelist.TimeInWindow() )
        {
            return true;
        }
    }
    return false;
}

/*----------------------------------------------------------------------------*/
pxTimeTypeList IBTBranchesList::getIBTTimeListByBranch(  short localbranchno, short ibtbranchno )
{
    pxTimeTypeList ttlist( this->getSession() );

    char buffer[sizeof(short)];
    sprintf(buffer, "%d", ibtbranchno);

    ttlist.Select( Type_ADS_Company, buffer, localbranchno );
    return ttlist;
}

/*----------------------------------------------------------------------------*/
/* static */ pxArtFiliale::IBTProduct	IBTBranchesList::getIBTProductValue( char ibtarticle )
{
    int verbundartikel = ibtarticle - '0';
    switch( verbundartikel )
    {
    case 0:
        return pxArtFiliale::IBTProductNone;
    case 1:
        return pxArtFiliale::IBTProductNormal;
    case 2:
        return pxArtFiliale::IBTProductPrivatSortiment;
    case 3:
        return pxArtFiliale::IBTProductVeterinary;
    case 4:
        return pxArtFiliale::IBTProductRegional;
    case 5:
        return pxArtFiliale::IBTProductNational;
    case 6:
        return pxArtFiliale::IBTProductNatRegional;
    case 7:
        return pxArtFiliale::IBTProductLokNational;
    case 8:
        return pxArtFiliale::IBTProductLokRegional;
    case 9:
        return pxArtFiliale::IBTProductOverAll;
    default:
        return pxArtFiliale::IBTProductNone;
    }
}

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranchesList::IBTBranchesList(pxSession* session)
    : nDBRecordSet( session )
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranchesList::~IBTBranchesList()
{
    this->Clear();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool IBTBranchesList::getRelevantNLevelIBTBranches( const short& branchno, const long& articleno )
{
    this->Clear();

    tIBTBRANCHES data;
    memset( &data, 0, sizeof(tIBTBRANCHES) );
    data.BranchNo = branchno;
    data.ArticleNo = articleno;

    int count_ = -1;
    count_ = nDBSelect( &data, cIBTBRANCHES_RELEVANTNLEVELIBTBRANCHES, count_, &data );
    return count_ > 0 ? true : false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool IBTBranchesList::getIBTBranchesByIBTType( const short& branchno, const short& ibtbranchno, pxArtFiliale::IBTProduct ibttypearticle )
{
    this->Clear();

    this->m_BranchNo = branchno;
    this->m_IBTBranchNo = ibtbranchno;

    tIBTBRANCHES data;
    memset( &data, 0, sizeof(tIBTBRANCHES) );
    data.BranchNo = branchno;
    data.IBTBranchNo = ibtbranchno;
    data.IBTType = static_cast<short>(getIBTransferTypeForArticleIBTType(ibttypearticle));
    int cursorid = cIBTBRANCHES_DEFAULT;

    if( -1 == data.IBTType )
    {
        return false;
    }

    if( -1 == ibtbranchno )
    {
        cursorid = cIBTBRANCHES_ALLENTRIES;
    }

    int count_ = -1;
    count_ = nDBSelect( &data, cursorid, count_, &data );
    return count_ > 0 ? true : false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool IBTBranchesList::getIBTBranchesByNLevelIBTType( const short& branchno, const short& ibtbranchno, short NLevelIBTType )
{
    // NLevelIBT -> getIBTBranchesByNLevelIBTType selektieren aus DB
    this->Clear();
    this->m_BranchNo = branchno;
    this->m_IBTBranchNo = ibtbranchno;
    tIBTBRANCHES data;
    memset( &data, 0, sizeof(tIBTBRANCHES) );
    data.BranchNo = branchno;
    data.IBTBranchNo = ibtbranchno;
    data.IBTType = NLevelIBTType;
    int cursorid = cIBTBRANCHES_NLEVELIBT;
    int count_ = -1;
    count_ = nDBSelect( &data, cursorid, count_, &data );
    return count_ > 0 ? true : false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool IBTBranchesList::getIBTBranchesByArticleNoForNLevelIBT( const short& branchno, const short& ibtbranchno, const long& articleno )
{
    this->Clear();
    this->m_BranchNo = branchno;
    this->m_IBTBranchNo = ibtbranchno;
    tIBTBRANCHES data;
    memset( &data, 0, sizeof(tIBTBRANCHES) );
    data.BranchNo = branchno;
    data.IBTBranchNo = ibtbranchno;
    data.ArticleNo = articleno;
    int cursorid = cIBTBRANCHES_NLEVELIBTARTICLENO;
    int count_ = -1;
    count_ = nDBSelect( &data, cursorid, count_, &data );
    return count_ > 0 ? true : false;
}

/*############################################################################################################################*/
/*                                       P R O T E C T E D                                                                    */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
nCollectable* IBTBranchesList::AddToList( const void* record, const int /* row */)
{
    IBTBranches *objectp = new IBTBranches( getSession(), *(tIBTBRANCHES*) record  );
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void IBTBranchesList::Clear()
{
    nDBRecordSet::Clear();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int IBTBranchesList::EndBrowse(const int cursorid)
{
    return IBTBranchesEndBrowse( cursorid );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int IBTBranchesList::GetNext(const void* record, const int cursorid)
{
    return IBTBranchesGetNext( (tIBTBRANCHES*)record, cursorid );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int IBTBranchesList::StartBrowse( const void *keys, const int cursorid )
{
    return IBTBranchesStartBrowse( (tIBTBRANCHES*)keys, this->getSession()->getDatabaseName( this->m_BranchNo ).c_str(),
                                   this->getSession()->getDatabaseName( this->m_IBTBranchNo ).c_str(), cursorid );
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranchesList::IBTransferType IBTBranchesList::getIBTransferTypeForArticleIBTType( pxArtFiliale::IBTProduct ibttypearticle ) const
{
    switch( ibttypearticle )
    {
    case pxArtFiliale::IBTProductLokNational:
        return IBTransferNationalAndNormal;
    case pxArtFiliale::IBTProductLokRegional:
        return IBTransferRegionalAndNormal;
    case pxArtFiliale::IBTProductNational:
        return IBTransferNational;
    case pxArtFiliale::IBTProductNatRegional:
        return IBTransferNationalAndRegional;
    case pxArtFiliale::IBTProductOverAll:
        return IBTransferAll;
    case pxArtFiliale::IBTProductNormal:
        return IBTransferNormal;
    case pxArtFiliale::IBTProductPrivatSortiment:
        return IBTransferPrivateAssortment;
    case pxArtFiliale::IBTProductRegional:
        return IBTransferRegional;
    case pxArtFiliale::IBTProductVeterinary:
        return IBTransferVeterinary;
    case pxArtFiliale::IBTProductNone:
        return IBTTransferNone;
    default:
        return IBTTransferNone;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------*/
pxSession* IBTBranchesList::getSession()
{
    return (pxSession*) DataBase();
}

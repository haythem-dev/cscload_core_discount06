#include "ibtbrancharticleconfig.h"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
IBTBranchArticleConfig::IBTBranchArticleConfig( pxSession* session, short branchno, long articleno )
	: pxDBRecord( session ), BranchNo( branchno ), ArticleNo( articleno )
{
	Init();
}

/*----------------------------------------------------------------------------*/
IBTBranchArticleConfig::~IBTBranchArticleConfig()
{	
}

/*----------------------------------------------------------------------------*/
void IBTBranchArticleConfig::Init()
{
    tIBTBRANCHARTICLECONFIG record;
    memset( &record, 0, sizeof(tIBTBRANCHARTICLECONFIG) );
    Assign( *this, record );

	m_Values.BranchNo = 0;
	m_Values.ArticleNo = 0;
	m_Values.IBTAssortmentTypeID = (int)eGeneralAssortment;
	m_Values.IBTTypeID = (int)eIBTNotAvailable;
}

/*----------------------------------------------------------------------------*/
IBTBranchArticleConfig& IBTBranchArticleConfig::operator=( const IBTBranchArticleConfig& src )
{
	tIBTBRANCHARTICLECONFIG record;
    Assign( *this, Assign(record, src) );
    return *this;
}

/*----------------------------------------------------------------------------*/
IBTBranchArticleConfig& IBTBranchArticleConfig::operator=( const tIBTBRANCHARTICLECONFIG& src )		
{
	return Assign( *this, src );
}

/*----------------------------------------------------------------------------*/
bool IBTBranchArticleConfig::Get()
{
	bool retval = false;
    tIBTBRANCHARTICLECONFIG record;	    
	memset( &record, 0, sizeof(tIBTBRANCHARTICLECONFIG) );

	record.BranchNo = this->BranchNo;
	record.ArticleNo = this->ArticleNo;
	
    int rc = nDBRead( &record );
    if( 0 == rc ) 
	{
		this->m_Values = record;		
		retval = true;
	}
    return retval;
}

/*----------------------------------------------------------------------------*/
int IBTBranchArticleConfig::Read( const void* record )
{
	return pxIBTBranchArticleConfigRead( (tIBTBRANCHARTICLECONFIG*)record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
IBTBranchArticleConfig& IBTBranchArticleConfig::Assign( IBTBranchArticleConfig& dest, const tIBTBRANCHARTICLECONFIG& src )
{	
	dest.m_Values.BranchNo = src.BranchNo;
	dest.m_Values.ArticleNo = src.ArticleNo;
	dest.m_Values.IBTAssortmentTypeID = src.IBTAssortmentTypeID;
	dest.m_Values.IBTTypeID = src.IBTTypeID;
    return dest;
}

/*----------------------------------------------------------------------------*/
tIBTBRANCHARTICLECONFIG& IBTBranchArticleConfig::Assign( tIBTBRANCHARTICLECONFIG& dest, const IBTBranchArticleConfig& src )
{	
	dest.BranchNo = src.m_Values.BranchNo;		
	dest.ArticleNo = src.m_Values.ArticleNo;
	dest.IBTAssortmentTypeID = src.m_Values.IBTAssortmentTypeID;
	dest.IBTTypeID = src.m_Values.IBTTypeID;
    return dest;
}

/*----------------------------------------------------------------------------*/
short IBTBranchArticleConfig::getBranchNo() const
{
	return m_Values.BranchNo;
}

/*----------------------------------------------------------------------------*/
long IBTBranchArticleConfig::getArticleNo() const
{
	return m_Values.ArticleNo;
}

/*----------------------------------------------------------------------------*/
short IBTBranchArticleConfig::getIBTTypeID() const
{
	return m_Values.IBTTypeID;
}

/*----------------------------------------------------------------------------*/
short IBTBranchArticleConfig::getIBTAssortmentTypeID() const
{
	return m_Values.IBTAssortmentTypeID;
}

/*----------------------------------------------------------------------------*/
IBTBranchArticleConfig::IBTAssortmentTypes IBTBranchArticleConfig::getIBTAssortmentType() const
{
	switch( getIBTAssortmentTypeID() )
	{
		case 0: return eGeneralAssortment;
		case 1: return ePrivateAssortment;
		case 2: return eVeterinaryAssortment;
		default: return eGeneralAssortment;
	}
}

/*----------------------------------------------------------------------------*/
bool IBTBranchArticleConfig::isAssortmentGeneral() const
{
	return (eGeneralAssortment == getIBTAssortmentType());
}

/*----------------------------------------------------------------------------*/
bool IBTBranchArticleConfig::isAssortmentPrivate() const
{
	return (ePrivateAssortment == getIBTAssortmentType());
}

/*----------------------------------------------------------------------------*/
bool IBTBranchArticleConfig::isAssortmentVeterinary() const
{
	return (eVeterinaryAssortment == getIBTAssortmentType());
}

/*----------------------------------------------------------------------------*/
IBTBranchArticleConfig::IBTTypes IBTBranchArticleConfig::getIBTType() const
{
	switch( getIBTTypeID() )
	{
		case 0: return eIBTNotAvailable;
		case 1: return eIBTNational;
		case 2: return eIBTRegional;
		case 3: return eIBTLocal;
		default: return eIBTNotAvailable;
	}
}

/*----------------------------------------------------------------------------*/
bool IBTBranchArticleConfig::isIBTNotAvailable() const
{
	return (eIBTNotAvailable == getIBTType() );
}

/*----------------------------------------------------------------------------*/
bool IBTBranchArticleConfig::isIBTNational() const
{
	return (eIBTNational == getIBTType() );
}

/*----------------------------------------------------------------------------*/
bool IBTBranchArticleConfig::isIBTRegional() const
{
	return (eIBTRegional == getIBTType() );
}

/*----------------------------------------------------------------------------*/
bool IBTBranchArticleConfig::isIBTLocal() const
{
	return (eIBTLocal == getIBTType() );
}

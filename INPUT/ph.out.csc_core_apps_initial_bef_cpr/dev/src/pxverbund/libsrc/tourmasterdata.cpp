#include "tourmasterdata.hpp"
#include "pxsess.hpp"


/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
TourMasterData::TourMasterData( pxSession* session )
	: pxDBRecord(session)
{
	this->Init();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
TourMasterData::~TourMasterData()
{
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long TourMasterData::getPickingDate() const
{
	return this->m_Values.PickingDate;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short TourMasterData::getBranchNo() const
{
	return this->m_Values.BranchNo;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long TourMasterData::getDecTour() const
{
	return this->m_Values.DecTour;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
const char* TourMasterData::getTourID() const
{
	return this->m_Values.TourID;
}

/*############################################################################################################################*/
/*                                       P R O T E C T E D                                                                    */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
TourMasterData& TourMasterData::Assign( TourMasterData& dest, const tTOURMASTERDATA& src )
{	
	dest.m_Values = src;	
    return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
tTOURMASTERDATA& TourMasterData::Assign( tTOURMASTERDATA&  dest, const TourMasterData& src )
{
	dest = src.m_Values;	
    return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void TourMasterData::Init()
{	
	tTOURMASTERDATA record;
	memset( &record, 0, sizeof(tTOURMASTERDATA) );	
    Assign( *this, record );
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
TourMasterData::TourMasterData( pxSession* session, tTOURMASTERDATA& src )
	: pxDBRecord(session)
{
	Init();
	(*this) = src;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
TourMasterData::TourMasterData( TourMasterData& src )
	: pxDBRecord(src.Session())
{
	Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
TourMasterData& TourMasterData::operator=( const tTOURMASTERDATA& src )
{
	return Assign( *this, src );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
TourMasterData& TourMasterData::operator=( const TourMasterData& src )
{
    tTOURMASTERDATA record;
    Assign( *this, Assign(record, src) );
    return *this;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int TourMasterData::CompareTo( const nCollectable* That ) const
{	
	TourMasterData* that = (TourMasterData*)That;	
	int retval = 0;    	
	if( 0 == retval ) { retval = ( this->m_Values.PickingDate == that->m_Values.PickingDate ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->m_Values.BranchNo == that->m_Values.BranchNo ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->m_Values.DecTour == that->m_Values.DecTour ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->m_Values.TourID == that->m_Values.TourID ) ? 0 : 1; }
	return retval;
}

/*
 * orderremarktypes.cpp
 *
 *  Created on: 05.05.2014     Author: steffen.heinlein
*/

#include "pxorderremarktypes.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"


/*----------------------------------------------------------------------------*/
OrderRemarkTypeEnum pxOrderRemarkType::RemarkType() const
{
	return RemarkType_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRemarkType::OrderRemarkLevel pxOrderRemarkType::Level() const
{	
	return Level_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
const nString& pxOrderRemarkType::RemarkName() const
{
	return RemarkName_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRemarkType::IsValidForOrderHeader() const
{
	switch( Level() )
	{
		case eOrderRemarkTypeHeaderLevel:
		case eOrderRemarkTypeBoth:
			return true;
		default:
			return false;
	}
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRemarkType::IsValidForOrderLine() const
{
	switch( Level() )
	{
		case eOrderRemarkTypeLineLevel:
		case eOrderRemarkTypeBoth:
			return true;
		default:
			return false;
	}
}
/*----------------------------------------------------------------------------*/		

/*----------------------------------------------------------------------------*/
pxOrderRemarkType::pxOrderRemarkType( pxSession* session )
	: pxDBRecord(session)
{
    Init();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRemarkType::pxOrderRemarkType( pxOrderRemarkType& src )
	: pxDBRecord(src.Session())
{
	Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRemarkType::pxOrderRemarkType( pxSession* session, tORDERREMARKTYPES& src )
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRemarkType::~pxOrderRemarkType()
{
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
tORDERREMARKTYPES& pxOrderRemarkType::Assign( tORDERREMARKTYPES& dest, const pxOrderRemarkType& src )
{
	src.RemarkName_.GetData( dest.RemarkName );
	dest.RemarkType = static_cast<short>(src.RemarkType_);
	dest.Level = static_cast<short>(src.Level_);
    return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRemarkType& pxOrderRemarkType::Assign( pxOrderRemarkType& dest, const tORDERREMARKTYPES& src )
{
	dest.RemarkName_ = src.RemarkName;
	dest.RemarkType_ = static_cast<OrderRemarkTypeEnum>(src.RemarkType);
	dest.Level_ = static_cast<pxOrderRemarkType::OrderRemarkLevel>(src.Level);
    return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrderRemarkType::Init()
{
	tORDERREMARKTYPES record;
    memset( &record, 0, sizeof(tORDERREMARKTYPES) );
    Assign( *this, record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRemarkType& pxOrderRemarkType::operator=( const pxOrderRemarkType& src )
{
    tORDERREMARKTYPES record;
    Assign( *this, Assign(record, src) );
    return *this;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRemarkType& pxOrderRemarkType::operator=( const tORDERREMARKTYPES& src)
{
    return Assign( *this, src );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRemarkType::Get( DBAccessMode /*mode*/ )
{
    tORDERREMARKTYPES record;
    memset( &record, 0, sizeof(tORDERREMARKTYPES) );
    int retval = nDBRead( &record );
    if( !retval )
	{
       (*this) = record;
	}
    return retval;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRemarkType::Read( const void* record ) 
{
    return pxOrderRemarkTypesRead( (tORDERREMARKTYPES*)record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrderRemarkType::InsertData( const tORDERREMARKTYPES& data )
{
	tORDERREMARKTYPES fil;
	int rc;
	memset( &fil, 0, sizeof(tORDERREMARKTYPES) );
	fil = data;
	rc = pxOrderRemarkTypesInsert( &fil );
	return ( 0 == rc );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRemarkType::CompareTo( const nCollectable* That, void* /*p*/, const long /*lparm*/ ) const
{
	pxOrderRemarkType *that = (pxOrderRemarkType*)That;
	int retval = 0;
    if( 0 == retval ) { retval = (RemarkName_ == that->RemarkName_) ? 0 : ( RemarkName_ > that->RemarkName_ ? 1 : -1 ); }
	if( 0 == retval ) { retval = (Level_ == that->Level_) ? 0 : (Level_ > that->Level_ ? 1 : -1); }
	if( 0 == retval ) { retval = (RemarkType_ == that->RemarkType_) ? 0 : (RemarkType_ > that->RemarkType_ ? 1 : -1); }
    return retval;
}
/*----------------------------------------------------------------------------*/

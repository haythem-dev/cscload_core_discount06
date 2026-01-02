/*
 * orderremarks.cpp
 *
 *  Created on: 05.05.2014     Author: steffen.heinlein
*/

#include "pxorderremarks.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
long pxGenericOrderRemark::CSCOrderNo() const
{
    return CSCOrderNo_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
long pxGenericOrderRemark::PositionNo() const
{
    return PositionNo_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
OrderRemarkTypeEnum pxGenericOrderRemark::RemarkType() const
{
    return RemarkType_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxGenericOrderRemark& pxGenericOrderRemark::Assign( pxGenericOrderRemark& dest, const tORDERREMARKS& src )
{
    dest.CSCOrderNo_ = src.CSCOrderNo;
    dest.PositionNo_ = src.PositionNo;
    dest.TextNumber_ = src.TextNumber;
    dest.RemarkText_ = src.RemarkText;
	dest.RemarkText_.trim();
	dest.RemarkType_ = static_cast<OrderRemarkTypeEnum>(src.RemarkType);
    return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
short pxGenericOrderRemark::TextNumber() const
{
    return TextNumber_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
const basar::VarString& pxGenericOrderRemark::RemarkText() const
{
    return RemarkText_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxGenericOrderRemark::pxGenericOrderRemark( pxSession* session )
    : pxDBRecord(session)
{
    Init();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxGenericOrderRemark::pxGenericOrderRemark( pxGenericOrderRemark& src )
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxGenericOrderRemark::pxGenericOrderRemark( pxSession* session, tORDERREMARKS& src )
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxGenericOrderRemark::~pxGenericOrderRemark()
{
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
tORDERREMARKS& pxGenericOrderRemark::Assign( tORDERREMARKS& dest, const pxGenericOrderRemark& src )
{
    dest.CSCOrderNo = src.CSCOrderNo_;
    dest.PositionNo = src.PositionNo_;
    dest.RemarkType = static_cast<short>(src.RemarkType_);
    dest.TextNumber = src.TextNumber_;
	strncpy(dest.RemarkText, src.RemarkText_.c_str(), mSIZEOF(tORDERREMARKS, RemarkText) - 1);
    return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxGenericOrderRemark::Init()
{
    tORDERREMARKS record;
    memset( &record, 0, sizeof(tORDERREMARKS) );
    Assign( *this, record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxGenericOrderRemark& pxGenericOrderRemark::operator=( const pxGenericOrderRemark& src )
{
    tORDERREMARKS record;
    Assign( *this, Assign(record, src) );
    return *this;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxGenericOrderRemark& pxGenericOrderRemark::operator=( const tORDERREMARKS& src)
{
    return Assign( *this, src );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxGenericOrderRemark::Get( DBAccessMode /*mode*/ )
{
    tORDERREMARKS record;
    memset( &record, 0, sizeof(tORDERREMARKS) );
    int retval = nDBRead( &record );
    if( !retval )
    {
        (*this) = record;
    }
    return retval;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxGenericOrderRemark::Read( const void* record )
{
    return pxGenericOrderRemarkRead( (tORDERREMARKS*)record );
}

/*----------------------------------------------------------------------------*/
int pxGenericOrderRemark::Delete()
{
	tORDERREMARKS record;
	memset(&record, 0, sizeof(tORDERREMARKS));
	Assign(record, *this);
	return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxGenericOrderRemark::CompareTo( const nCollectable* That, void* /*p*/, const long /*lparm*/ ) const
{
    pxGenericOrderRemark *that = (pxGenericOrderRemark*)That;
    int retval = 0;

    if( 0 == retval ) { retval = (CSCOrderNo_ == that->CSCOrderNo_) ? 0 : (CSCOrderNo_ > that->CSCOrderNo_ ? 1 : -1); }
    if( 0 == retval ) { retval = (PositionNo_ == that->PositionNo_) ? 0 : (PositionNo_ > that->PositionNo_ ? 1 : -1); }
    if( 0 == retval ) { retval = (RemarkType_ == that->RemarkType_) ? 0 : (RemarkType_ > that->RemarkType_ ? 1 : -1); }
    if( 0 == retval ) { retval = (TextNumber_ == that->TextNumber_) ? 0 : (TextNumber_ > that->TextNumber_ ? 1 : -1); }
    if( 0 == retval ) { retval = (RemarkText_ == that->RemarkText_) ? 0 : ( RemarkText_ > that->RemarkText_ ? 1 : -1 ); }
    return retval;
}
/*----------------------------------------------------------------------------*/

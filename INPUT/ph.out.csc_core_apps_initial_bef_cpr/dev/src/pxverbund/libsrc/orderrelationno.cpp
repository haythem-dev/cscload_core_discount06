/*
 * orderrelationno.cpp
 *
 *  Created on: 04.08.2015     Author: steffen.heinlein
*/

#include "pxorderrelationno.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
long pxOrderRelationNo::CSCOrderNo() const
{
	return this->CSCOrderNo_;
}

/*----------------------------------------------------------------------------*/
long pxOrderRelationNo::RelationNo() const
{
	return this->RelationNo_;
}

/*----------------------------------------------------------------------------*/
OrderRelationNoTypeEnum	pxOrderRelationNo::RelationNoType() const
{
	switch( this->RelationNoType_ )
	{
		case ePurchaseOrderNo:
			return ePurchaseOrderNo;
        case eIVCVoucherNo:
            return eIVCVoucherNo;
        case eOriginalInvoiceNo:
            return eOriginalInvoiceNo;
		default:
			return eUndefinedOrderRelationNo;
	}
}

/*----------------------------------------------------------------------------*/
short pxOrderRelationNo::RelationNoTypeValue() const
{
	return this->RelationNoType_;
}

/*----------------------------------------------------------------------------*/
pxOrderRelationNo::pxOrderRelationNo( pxSession* session )
	: pxDBRecord(session)
{
    Init();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNo::pxOrderRelationNo( pxOrderRelationNo& src )
	: pxDBRecord(src.Session())
{
	Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNo::pxOrderRelationNo( pxSession* session, tORDERRELATIONNO& src )
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNo::~pxOrderRelationNo()
{
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
tORDERRELATIONNO& pxOrderRelationNo::Assign( tORDERRELATIONNO& dest, const pxOrderRelationNo& src )
{
	dest.CSCOrderNo = src.CSCOrderNo();
	dest.RelationNo = src.RelationNo();
	dest.RelationNoType = src.RelationNoTypeValue();
    return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNo& pxOrderRelationNo::Assign( pxOrderRelationNo& dest, const tORDERRELATIONNO& src )
{
	dest.CSCOrderNo_ = src.CSCOrderNo;
	dest.RelationNo_ = src.RelationNo;
	dest.RelationNoType_ = src.RelationNoType;
    return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrderRelationNo::Init()
{
	tORDERRELATIONNO record;
    memset( &record, 0, sizeof(tORDERRELATIONNO) );
    Assign( *this, record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNo& pxOrderRelationNo::operator=( const pxOrderRelationNo& src )
{
    tORDERRELATIONNO record;
    Assign( *this, Assign(record, src) );
    return *this;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNo& pxOrderRelationNo::operator=( const tORDERRELATIONNO& src)
{
    return Assign( *this, src );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNo::Get( DBAccessMode /*mode*/ )
{
    tORDERRELATIONNO record;
    memset( &record, 0, sizeof(tORDERRELATIONNO) );
    int retval = nDBRead( &record );
    if( !retval )
	{
       (*this) = record;
	}
    return retval;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNo::Read( const void* record )
{
	return pxOrderRelationNoRead( (tORDERRELATIONNO*)record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNo::CompareTo( const nCollectable* That, void* /*p*/, const long /*lparm*/ ) const
{
	pxOrderRelationNo *that = (pxOrderRelationNo*)That;
	int retval = 0;

	if( 0 == retval ) { retval = (CSCOrderNo_ == that->CSCOrderNo_) ? 0 : (CSCOrderNo_ > that->CSCOrderNo_ ? 1 : -1); }
	if( 0 == retval ) { retval = (RelationNo_ == that->RelationNo_) ? 0 : (RelationNo_ > that->RelationNo_ ? 1 : -1); }
	if( 0 == retval ) { retval = (RelationNoType_ == that->RelationNoType_) ? 0 : (RelationNoType_ > that->RelationNoType_ ? 1 : -1); }

    return retval;
}
/*----------------------------------------------------------------------------*/

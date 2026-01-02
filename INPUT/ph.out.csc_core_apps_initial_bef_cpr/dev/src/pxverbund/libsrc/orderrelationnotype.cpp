/*
 * orderrelationnotype.cpp
 *
 *  Created on: 04.08.2015     Author: steffen.heinlein
*/

#include "pxorderrelationnotype.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
short pxOrderRelationNoType::getOrderRelationNoTypeValue() const
{
	return this->OrderRelationNoType_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
OrderRelationNoTypeEnum pxOrderRelationNoType::getOrderRelationNoType() const
{
	switch( this->OrderRelationNoType_ )
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

/*----------------------------------------------------------------------------*/
const nString& pxOrderRelationNoType::getOrderRelationNoTypeName() const
{
	return this->OrderRelationNoName_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNoType::pxOrderRelationNoType( pxSession* session )
	: pxDBRecord(session)
{
    Init();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNoType::pxOrderRelationNoType( pxOrderRelationNoType& src )
	: pxDBRecord(src.Session())
{
	Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNoType::pxOrderRelationNoType( pxSession* session, tORDERRELATIONNOTYPES& src )
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNoType::~pxOrderRelationNoType()
{
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
tORDERRELATIONNOTYPES& pxOrderRelationNoType::Assign( tORDERRELATIONNOTYPES& dest, const pxOrderRelationNoType& src )
{
	src.OrderRelationNoName_.GetData( dest.RelationDescription );
	dest.RelationNoType = src.OrderRelationNoType_;
    return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNoType& pxOrderRelationNoType::Assign( pxOrderRelationNoType& dest, const tORDERRELATIONNOTYPES& src )
{
	dest.OrderRelationNoName_ = src.RelationDescription;
	dest.OrderRelationNoType_ = src.RelationNoType;
    return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrderRelationNoType::Init()
{
	tORDERRELATIONNOTYPES record;
    memset( &record, 0, sizeof(tORDERRELATIONNOTYPES) );
    Assign( *this, record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNoType& pxOrderRelationNoType::operator=( const pxOrderRelationNoType& src )
{
    tORDERRELATIONNOTYPES record;
    Assign( *this, Assign(record, src) );
    return *this;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderRelationNoType& pxOrderRelationNoType::operator=( const tORDERRELATIONNOTYPES& src)
{
    return Assign( *this, src );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNoType::Get( DBAccessMode /*mode*/ )
{
    tORDERRELATIONNOTYPES record;
    memset( &record, 0, sizeof(tORDERRELATIONNOTYPES) );
    int retval = nDBRead( &record );
    if( !retval )
	{
       (*this) = record;
	}
    return retval;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNoType::Read( const void* record )
{
    return pxOrderRelationNoTypesRead( (tORDERRELATIONNOTYPES*)record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*
bool pxOrderRelationNoType::InsertData( const tORDERRELATIONNOTYPES data )
{
	tORDERRELATIONNOTYPES fil;
	int rc;
	memset( &fil, 0, sizeof(tORDERRELATIONNOTYPES) );
	fil = data;
	rc = pxOrderRelationNoTypesInsert( &fil );
	return ( 0 == rc )
}
*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderRelationNoType::CompareTo( const nCollectable* That, void* /*p*/, const long /*lparm*/ ) const
{
	pxOrderRelationNoType *that = (pxOrderRelationNoType*)That;
	int retval = 0;

	if( 0 == retval )
	{
		retval = ( this->getOrderRelationNoTypeName() == that->getOrderRelationNoTypeName() ) ? 0 : 1;
	}

	if( 0 == retval )
	{
		retval = (this->getOrderRelationNoTypeValue() == that->getOrderRelationNoTypeValue() ) ? 0 : 1;
	}

    return retval;
}
/*----------------------------------------------------------------------------*/


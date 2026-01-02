/*
 * msv3order.cpp
 *
 *  Created on: 27.08.2013     Author: steffen.heinlein
*/

#include "pxmsv3order.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
nString& pxMSV3Order::OrderLabel()
{
	return OrderLabel_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxMSV3Order::isOrderLabelEqual( nString orderlabel ) const
{
	orderlabel.Strip();
	nString thisorderlabel(OrderLabel_);
	thisorderlabel.Strip();
	return ( 0 == thisorderlabel.Compare(orderlabel) );
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
pxMSV3Order::pxMSV3Order( pxSession* session )
: pxDBRecord(session)
{
	Init();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxMSV3Order::pxMSV3Order( pxMSV3Order& src )
: pxDBRecord(src.Session())
{
	Init();
	(*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxMSV3Order::pxMSV3Order( pxSession* session, tKDAUFTRAG& src )
: pxDBRecord(session)
{
	Init();
	(*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxMSV3Order::~pxMSV3Order()
{
    ;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
tKDAUFTRAG& pxMSV3Order::Assign( tKDAUFTRAG& dest, const pxMSV3Order& src )
{
	src.OrderLabel_.GetData(dest.OrderLabel);    
	return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxMSV3Order& pxMSV3Order::Assign( pxMSV3Order& dest, const tKDAUFTRAG& src )
{
	dest.OrderLabel_ = src.OrderLabel;
	return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxMSV3Order::Init()
{
	tKDAUFTRAG record;
	memset( &record, 0, sizeof(tKDAUFTRAG) );
	Assign( *this, record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxMSV3Order& pxMSV3Order::operator=( const pxMSV3Order& src )
{
	tKDAUFTRAG record; 
	Assign(*this, Assign(record, src));
	return *this;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxMSV3Order& pxMSV3Order::operator=( const tKDAUFTRAG& src )
{
    return Assign( *this, src );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxMSV3Order::Get( DBAccessMode /*mode*/ )
{
	tKDAUFTRAG record;
	memset( &record, 0, sizeof(tKDAUFTRAG) );
	int retval = nDBRead(&record);
	if (!retval)
	{
		(*this)= record; // import the data from tKDAUFTRAG struct
	}
	return retval;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxMSV3Order::CompareTo( const nCollectable *That, void* /*p*/, const long /*lparm*/ ) const
{
	pxMSV3Order *that = (pxMSV3Order*)That;
	int retval = (OrderLabel_ == that->OrderLabel_) ? 0 : (OrderLabel_ > that->OrderLabel_ ? 1 : -1);
    return retval;
}
/*----------------------------------------------------------------------------*/

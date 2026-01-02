/*
 * orderperiod.cpp
 *
 *  Created on: 27.08.2013     Author: steffen.heinlein
*/

#include "pxorderperiod.hpp"
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
long pxOrderPeriod::CustomerNo() const
{
	return CustomerNo_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
const nString& pxOrderPeriod::TourID() const
{
	return TourID_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
long pxOrderPeriod::ID() const
{
	return ID_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
short pxOrderPeriod::BranchNo() const
{
	return BranchNo_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
short pxOrderPeriod::WeekDay() const
{
	return this->WeekDay_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
long pxOrderPeriod::Order_Period_ID() const
{
	return Order_Period_ID_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
long pxOrderPeriod::FromTime() const
{
	return FromTime_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
long pxOrderPeriod::ToTime() const
{
	return ToTime_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
long pxOrderPeriod::MainTime() const
{
	return MainTime_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
const basar::Date& pxOrderPeriod::ChangeDate() const
{
	return ChangeDate_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriod::pxOrderPeriod( pxSession* session )
: pxDBRecord(session)
{
	Init();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriod::pxOrderPeriod( pxSession* session, long id )
: pxDBRecord(session)
{
	Init();
	ID_ = id;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriod::pxOrderPeriod( pxOrderPeriod& src )
: pxDBRecord(src.Session())
{
	Init();
	(*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriod::pxOrderPeriod( pxSession* session, tORDERPERIOD& src )
: pxDBRecord(session)
{
	Init();
	(*this) = src;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriod::~pxOrderPeriod()
{
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
tORDERPERIOD& pxOrderPeriod::Assign( tORDERPERIOD& dest, const pxOrderPeriod& src )
{	
	dest.CustomerNo = src.CustomerNo_;
	src.TourID_.GetData(dest.TourID);
	dest.ID = src.ID_;
	dest.BranchNo = src.BranchNo_;
	dest.WeekDay = src.WeekDay_;
	dest.OrderPeriodID = src.Order_Period_ID_;
	dest.FromTime = src.FromTime_;
	dest.ToTime = src.ToTime_;
	dest.MainTime = src.MainTime_;
	dest.ChangeDate = src.ChangeDate_.getDate();
	return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriod& pxOrderPeriod::Assign( pxOrderPeriod& dest, const tORDERPERIOD& src )
{	
	dest.CustomerNo_ = src.CustomerNo;
	dest.TourID_ = src.TourID;
	dest.ID_ = src.ID;
	dest.BranchNo_ = src.BranchNo;
	dest.WeekDay_ = src.WeekDay;
	dest.Order_Period_ID_ = src.OrderPeriodID;
	dest.FromTime_ = src.FromTime;
	dest.ToTime_ = src.ToTime;
	dest.MainTime_ = src.MainTime;
	dest.ChangeDate_ = src.ChangeDate;
	return dest;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrderPeriod::Init()
{
	tORDERPERIOD record;
	memset( &record, 0, sizeof(tORDERPERIOD) );
	Assign( *this, record );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriod& pxOrderPeriod::operator=( const pxOrderPeriod& src )
{
	tORDERPERIOD record; 
	Assign(*this, Assign(record, src));
	return *this;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxOrderPeriod& pxOrderPeriod::operator=( const tORDERPERIOD& src )
{
    return Assign( *this, src );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderPeriod::Get( DBAccessMode /*mode*/ )
{
	tORDERPERIOD record;
	memset( &record, 0, sizeof(tORDERPERIOD) );
	record.ID = ID_;
	int retval = nDBRead(&record);
	if (!retval)
	{
		(*this)= record; // import the data from tORDERPERIOD struct
	}
	return retval;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderPeriod::Read(const void* record)
{
    return pxOrderPeriodRead((tORDERPERIOD*)record);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
int pxOrderPeriod::CompareTo( const nCollectable *That, void* /*p*/, const long /*lparm*/ ) const
{
	pxOrderPeriod *that = (pxOrderPeriod*)That;

	int retval = ( BranchNo_ == that->BranchNo_ ) ? 0 : ( BranchNo_ > that->BranchNo_ ? 1 : -1 );

    if ( retval == 0 )
	{
		retval = ( CustomerNo_ == that->CustomerNo_ ) ? 0 : ( CustomerNo_ > that->CustomerNo_ ? 1 : -1 );
	}
    if ( retval == 0 )
	{
		retval = ( WeekDay_ == that->WeekDay_ ) ? 0 : ( WeekDay_ > that->WeekDay_ ? 1 : -1 );
	}
    if ( retval == 0 )
	{
		retval = ( FromTime_ == that->FromTime_ ) ? 0 : ( FromTime_ > that->FromTime_ ? 1 : -1 );
	}
    if ( retval == 0 )
	{
		retval = ( ToTime_ == that->ToTime_ ) ? 0 : ( ToTime_ > that->ToTime_ ? 1 : -1 );
	}    
    if ( retval == 0 )
	{
		retval = ( TourID_ == that->TourID_ ) ? 0 : ( TourID_ > that->TourID_ ? 1 : -1 );
	}
    if ( retval == 0 )
	{
		retval = ( ID_ == that->ID_ ) ? 0 : ( ID_ > that->ID_ ? 1 : -1 );
	}
    if ( retval == 0 )
	{
		retval = ( Order_Period_ID_ == that->Order_Period_ID_ ) ? 0 : ( Order_Period_ID_ > that->Order_Period_ID_ ? 1 : -1 );
	}

    return retval;
}
/*----------------------------------------------------------------------------*/

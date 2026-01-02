#include "customerbusinesshours.hpp"
#include <pxdbxx.h>
#include <date.hpp>
#include "pxsess.hpp"

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHours::CustomerBusinessHours( pxSession* session, const short& branchno, const long& customerno )
	: pxDBRecord(session)
{
	this->m_Values.BranchNo = branchno;
	this->m_Values.CustomerNo = customerno;	
	this->Init(); 
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHours::~CustomerBusinessHours()
{	
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CustomerBusinessHours::isInsideBusinessHours( const nDate& datetime ) const
{
	if( datetime.GetDayOfWeek() == this->m_Values.Weekday )
	{	
		long time = (datetime.GetHours() * 10000) + (datetime.GetMinutes() * 100) + datetime.GetSeconds();
		return time >= this->m_Values.BusinesshoursStart && time <= this->m_Values.BusinesshoursEnd;
	}
	return false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short CustomerBusinessHours::getWeekday() const
{
	return this->m_Values.Weekday;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short CustomerBusinessHours::getBranchNo() const
{
	return this->m_Values.BranchNo;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long CustomerBusinessHours::getCustomerNo() const
{
	return this->m_Values.CustomerNo;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long CustomerBusinessHours::getBusinesshoursStart() const
{
	return this->m_Values.BusinesshoursStart;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long CustomerBusinessHours::getBusinesshoursEnd() const
{
	return this->m_Values.BusinesshoursEnd;
}

/*############################################################################################################################*/
/*                                       P R O T E C T E D                                                                    */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHours::CustomerBusinessHours( pxSession* session, tCUSTOMERBUSINESSHOURS& src )
	: pxDBRecord(session)
{
	Init();
	(*this) = src;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHours& CustomerBusinessHours::Assign( CustomerBusinessHours& dest, const tCUSTOMERBUSINESSHOURS& src )
{
	dest.m_Values = src;
	return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
tCUSTOMERBUSINESSHOURS& CustomerBusinessHours::Assign( tCUSTOMERBUSINESSHOURS&  dest, const CustomerBusinessHours& src )
{
	dest = src.m_Values;
    return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CustomerBusinessHours::Init()
{
	this->m_Values.BusinesshoursEnd = 0;
	this->m_Values.BusinesshoursStart = 0;
	this->m_Values.Weekday = 0;	
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHours::CustomerBusinessHours( CustomerBusinessHours& src )
	: pxDBRecord(src.Session())
{
	Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHours& CustomerBusinessHours::operator=( const tCUSTOMERBUSINESSHOURS& src )
{
	return Assign( *this, src );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHours& CustomerBusinessHours::operator=( const CustomerBusinessHours& src )
{
    tCUSTOMERBUSINESSHOURS record;
    Assign( *this, Assign(record, src) );
    return *this;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CustomerBusinessHours::CompareTo( const nCollectable* That ) const
{	
	CustomerBusinessHours* that = (CustomerBusinessHours*)That;	
	int retval = 0;   

	if( 0 == retval ) { retval = ( this->m_Values.BranchNo == that->m_Values.BranchNo ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->m_Values.CustomerNo == that->m_Values.CustomerNo ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->m_Values.Weekday == that->m_Values.Weekday ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->m_Values.BusinesshoursEnd == that->m_Values.BusinesshoursEnd ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->m_Values.BusinesshoursStart == that->m_Values.BusinesshoursStart ) ? 0 : 1; }	
    return retval;
}

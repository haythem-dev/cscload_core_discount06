#include "ibtbranches.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranches::IBTBranches( pxSession* session )
	: pxDBRecord(session)
{
}

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranches::~IBTBranches()
{	
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short IBTBranches::getBranchNo() const
{
	return this->m_Values.BranchNo;
}
	
/*----------------------------------------------------------------------------------------------------------------------------*/
short IBTBranches::getIBTBranchNo() const
{
	return this->m_Values.IBTBranchNo;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short IBTBranches::getIBTType() const
{
	return this->m_Values.IBTType;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short IBTBranches::getNLevelIBTType() const
{
	return this->m_Values.NLevelIBTTypeID;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short IBTBranches::getDayIBT() const
{
	return this->m_Values.DayIBT;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
long IBTBranches::getIBTCustomerNo() const
{
	return this->m_Values.IBTCustomerNo;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short IBTBranches::getPriority() const
{
	return this->m_Values.Priority;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
short IBTBranches::getActiveFlag() const
{
	return this->m_Values.ActiveFlag;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool IBTBranches::isDayIBT() const
{
	if( 1 == this->m_Values.DayIBT )
	{
		return true;
	}
	return false;
}

/*############################################################################################################################*/
/*                                       P R O T E C T E D                                                                    */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranches& IBTBranches::Assign( IBTBranches& dest, const tIBTBRANCHES& src )
{	
	dest.m_Values = src;	
    return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
tIBTBRANCHES& IBTBranches::Assign( tIBTBRANCHES&  dest, const IBTBranches& src )
{
	dest = src.m_Values;
    return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void IBTBranches::Init()
{
	tIBTBRANCHES record;
    memset( &record, 0, sizeof(tIBTBRANCHES) );
    Assign( *this, record );
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranches::IBTBranches( pxSession* session, tIBTBRANCHES& src )
	: pxDBRecord(session)
{
	Init();
	(*this) = src;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranches::IBTBranches( IBTBranches& src )
	: pxDBRecord(src.Session())
{
	Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranches& IBTBranches::operator=( const tIBTBRANCHES& src )
{
	return Assign( *this, src );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
IBTBranches& IBTBranches::operator=( const IBTBranches& src )
{
    tIBTBRANCHES record;
    Assign( *this, Assign(record, src) );
    return *this;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int IBTBranches::CompareTo( const nCollectable* That/*, void* p, const long lparm*/ ) const
{	
	IBTBranches* that = (IBTBranches*)That;	
	int retval = 0;    	
	if( 0 == retval ) { retval = ( this->getBranchNo() == that->getBranchNo() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getDayIBT() == that->getDayIBT() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getIBTBranchNo() == that->getIBTBranchNo() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getIBTCustomerNo() == that->getIBTCustomerNo() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getIBTType() == that->getIBTType() ) ? 0 : 1; }	
	if( 0 == retval ) { retval = ( this->getPriority() == that->getPriority() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getActiveFlag() == that->getActiveFlag() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getNLevelIBTType() == that->getNLevelIBTType() ) ? 0 : 1; }	
    return retval;
}


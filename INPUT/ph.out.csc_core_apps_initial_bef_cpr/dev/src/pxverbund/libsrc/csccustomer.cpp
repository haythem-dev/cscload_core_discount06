#include "csccustomer.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxcstot.hpp"
#include "customerbusinesshourslist.hpp"

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CSCCustomer::CSCCustomer( pxSession* session, const short& branchno, const long& customerno )
	: pxDBRecord(session)
{
	this->m_Values.FILIALNR = branchno;
	this->m_Values.IDFNR = customerno;
	this->Init();
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CSCCustomer::~CSCCustomer()
{
	if( NULL != this->m_CustomerOrderTypeList )
	{
		delete this->m_CustomerOrderTypeList;
		this->m_CustomerOrderTypeList = NULL;
	}

	if( NULL != this->m_CustomerBusinessHoursList )
	{
		delete this->m_CustomerBusinessHoursList;
		this->m_CustomerBusinessHoursList = NULL;
	}
}

/*----------------------------------------------------------------------------------------------------------------------------*/
const short& CSCCustomer::getBranchNo() const
{
	return this->m_Values.FILIALNR;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
const long& CSCCustomer::getCustomerNo() const
{
	return this->m_Values.IDFNR;
}

const basar::VarString CSCCustomer::getNameApo() const
{
	basar::VarString retval(m_Values.NAMEAPO);
	retval.trim();
	return retval;
}

const basar::VarString CSCCustomer::getNameInhaber() const
{
	basar::VarString retval(m_Values.NAMEINHABER);
	retval.trim();
	return retval;
}

const basar::VarString CSCCustomer::getStrasse() const
{
	basar::VarString retval(m_Values.STRASSE);
	retval.trim();
	return retval;
}

const basar::VarString CSCCustomer::getOrt() const
{
	basar::VarString retval(m_Values.ORT);
	retval.trim();
	return retval;
}

const basar::VarString CSCCustomer::getPostLeitZahl() const
{
	basar::VarString retval(m_Values.POSTLEITZAHL);
	retval.trim();
	return retval;
}

const basar::VarString CSCCustomer::getTelnr() const
{
	basar::VarString retval(m_Values.TELNR);
	retval.trim();
	return retval;
}

const basar::VarString CSCCustomer::getTelnrDafue() const
{
	basar::VarString retval(m_Values.TELNRDAFUE);
	retval.trim();
	return retval;
}

const basar::VarString CSCCustomer::getFaxnr() const
{
	basar::VarString retval(m_Values.FAXNR);
	retval.trim();
	return retval;
}

const basar::VarString CSCCustomer::getAnredeKz() const
{
	basar::VarString retval;
	retval.format("%d", m_Values.ANREDEKZ);
	return retval;
}

const long& CSCCustomer::getImsBezirkNr() const
{
	return m_Values.IMSBEZIRKNR;
}

const basar::VarString CSCCustomer::getKdGruppe() const
{
	basar::VarString retval(m_Values.KDGRUPPE);
	retval.trim();
	return retval;
}

const long& CSCCustomer::getPersonalNrVertr() const
{
	return m_Values.PERSONALNRVERTR;
}

const basar::VarString CSCCustomer::getKzSprache() const
{
	basar::VarString retval(m_Values.KZSPRACHE);
	retval.trim();
	return retval;
}

const basar::VarString CSCCustomer::getDafueSystemSchluessel() const
{
	basar::VarString retval(m_Values.DAFUESYSTEM);
	retval.trim();
	return retval;
}

bool CSCCustomer::isFMDCustomer() const
{
    if (this->m_Values.SKDFMD > 0)
    {
        return true;
    }
    return false;
}

const basar::VarString CSCCustomer::isVersandApo() const
{
	basar::VarString retval;
	retval.format("%c", m_Values.SKDVERSANDAPO);
	return retval;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nString CSCCustomer::getDefaultOrderType() const
{
	nString retval("");
	if( !this->getDefaultOrderTypeCombination().IsEmpty() )
	{
		retval = this->getDefaultOrderTypeCombination()(0,2);
	}
	return retval;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
nString CSCCustomer::getDefaultOrderTypeCombination() const
{
	nString retval(this->m_Values.STDAUFKOBUART);
    retval.ToUpper();
    retval.Strip();
	return retval;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
const long& CSCCustomer::getTourBreakoverMinutes() const
{
	return this->m_Values.TOURENKIPPZEIT;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
bool CSCCustomer::getUseSeparateOrder() const
{
	if( '1' == this->m_Values.SKDSEPAUFT )
	{
		return true;
	}
	return false;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
pxCustOrderTypeList* CSCCustomer::getCustomerOrderTypeList() // NO CROSS DATABASE SUPPORT!!!
{
	if( NULL == this->m_CustomerOrderTypeList )
	{
		this->m_CustomerOrderTypeList = new pxCustOrderTypeList( this->Session() );
		this->m_CustomerOrderTypeList->Build( this->getBranchNo(), this->getCustomerNo() );
	}
	return this->m_CustomerOrderTypeList;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CustomerBusinessHoursList* CSCCustomer::getCustomerBusinessHoursList()
{
	if( NULL == this->m_CustomerBusinessHoursList )
	{
		this->m_CustomerBusinessHoursList = new CustomerBusinessHoursList( this->Session() );
		this->m_CustomerBusinessHoursList->getBusinessHours( this->m_Values.FILIALNR, this->m_Values.IDFNR );
	}
	return this->m_CustomerBusinessHoursList;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CSCCustomer::Read()
{
	return CSCCustomerRead( &this->m_Values, this->Session()->getDatabaseName( this->getBranchNo() ).c_str() );
}


/*############################################################################################################################*/
/*                                       P R O T E C T E D                                                                    */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CSCCustomer& CSCCustomer::Assign( CSCCustomer& dest, const tCSCCUSTOMER& src )
{
	dest.m_Values = src;
	return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
tCSCCUSTOMER& CSCCustomer::Assign( tCSCCUSTOMER&  dest, const CSCCustomer& src )
{
	dest = src.m_Values;
    return dest;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
void CSCCustomer::Init()
{
	this->m_Values.TOURENKIPPZEIT = 0;
	this->m_CustomerOrderTypeList = NULL;
	this->m_CustomerBusinessHoursList = NULL;
	this->m_Values.SKDSEPAUFT = ' ';
    this->m_Values.SKDFMD = 0;
	std::fill( this->m_Values.STDAUFKOBUART, this->m_Values.STDAUFKOBUART + 5, ' ' ); this->m_Values.STDAUFKOBUART[4] = '\0';
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/

/*----------------------------------------------------------------------------------------------------------------------------*/
CSCCustomer::CSCCustomer( CSCCustomer& src )
	: pxDBRecord(src.Session())
{
	Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CSCCustomer& CSCCustomer::operator=( const tCSCCUSTOMER& src )
{
	return Assign( *this, src );
}

/*----------------------------------------------------------------------------------------------------------------------------*/
CSCCustomer& CSCCustomer::operator=( const CSCCustomer& src )
{
    tCSCCUSTOMER record;
    Assign( *this, Assign(record, src) );
    return *this;
}

/*----------------------------------------------------------------------------------------------------------------------------*/
int CSCCustomer::CompareTo( const nCollectable* That ) const
{
	CSCCustomer* that = (CSCCustomer*)That;
	int retval = 0;
	if( 0 == retval ) { retval = ( this->getBranchNo() == that->getBranchNo() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getCustomerNo() == that->getCustomerNo() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getTourBreakoverMinutes() == that->getTourBreakoverMinutes() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getDefaultOrderTypeCombination() == that->getDefaultOrderTypeCombination() ) ? 0 : 1; }
	if( 0 == retval ) { retval = ( this->getUseSeparateOrder() == that->getUseSeparateOrder() ) ? 0 : 1; }
    return retval;
}

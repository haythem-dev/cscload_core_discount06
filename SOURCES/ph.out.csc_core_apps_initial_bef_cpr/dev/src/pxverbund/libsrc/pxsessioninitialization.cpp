#include "pxsessioninitialization.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"

//----------------------------------------------------------------------------------------------
/*static*/ basar::VarString pxSessionInitialization::getCountryCode( const short branchNo )
{
	switch( branchNo )
	{
		// ----------------------------------------------------------
		// AT Austria
		// ----------------------------------------------------------
		case 61:
		case 62:
		case 63:
		case 64:
			return pxSession::COUNTRY_AUSTRIA;
		case 83:
			return pxSession::COUNTRY_AUSTRIA_PREWHOLE;

		// ----------------------------------------------------------
		// BG Bulgaria
		// ----------------------------------------------------------
		case 22:
		case 23:
		case 25:
		case 26:
		case 28:
			return pxSession::COUNTRY_BULGARIA;

		// ----------------------------------------------------------
		// CH Switzerland
		// ----------------------------------------------------------
		case 12:
		case 13:
		case 16:
			return pxSession::COUNTRY_SWITZERLAND;			

		// ----------------------------------------------------------
		// DE Germany
		// ----------------------------------------------------------
		case 5:
		case 6:
		case 8:
		case 9:
		case 21:
		case 27:
		case 31:
		case 33:
		case 40:
		case 44:
		case 46:
		case 51:
		case 52:
		case 54:
		case 56:
		case 57:
		case 58:
		case 59:
		case 70:
		case 78:
		case 81:
		case 82:
			return pxSession::COUNTRY_GERMANY;

		// ----------------------------------------------------------
		// FR France
		// ----------------------------------------------------------
		case 17:
		case 18:
		case 30:
		case 32:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 41:
		case 42:
		case 45:
		case 50:
		case 53:
		case 55: 
		case 60: 
		case 65: 
		case 66: 
		case 67: 
		case 68: 
		case 75: 
		case 76: 
		case 80:
		case 86: 
		case 87:
			return pxSession::COUNTRY_FRANCE;

		case 43:
		case 48:
			return pxSession::COUNTRY_FRANCE_PREWHOLE;

		// ----------------------------------------------------------
		// HR Croatia
		// ----------------------------------------------------------
		case 71:
		case 72:
		case 73:
		case 74:
		case 77:
			return pxSession::COUNTRY_CROATIA;

		// ----------------------------------------------------------
		// RS Serbia
		// ----------------------------------------------------------
		case 3:
		case 84:
		case 85:
			return pxSession::COUNTRY_SERBIA;				
		
		// ----------------------------------------------------------
		// Unknown
		// ----------------------------------------------------------
		default:
			return pxSession::COUNTRY_GERMANY;
	}
}

//----------------------------------------------------------------------------------------------
pxSessionInitialization::pxSessionInitialization()
	:	m_BranchNo(0), 
		m_CountryCode(""), 
		m_DBServerName(""), 
		m_DBName(""), 
		m_DeviceType( ::pxDVC_UNDEFINED ), 
		m_DeviceName(""), 		
		m_MessageFileName("")
{	
}

//----------------------------------------------------------------------------------------------
pxSessionInitialization::~pxSessionInitialization()
{
}

//----------------------------------------------------------------------------------------------
void pxSessionInitialization::init()
{
	setBranchInformation( 0, "" );	
	setDBInformation( "", "" );	
	setDevice( ::pxDVC_UNDEFINED, "" );
	setMessageFileName( "" );		
}

//----------------------------------------------------------------------------------------------
void pxSessionInitialization::setBranchInformation( const short branchNo, const basar::VarString& countryCode )
{
	m_BranchNo = branchNo;
	m_CountryCode = countryCode;
}

//----------------------------------------------------------------------------------------------
void pxSessionInitialization::setDBInformation( const basar::VarString& dbServerName, const basar::VarString& dbName )
{
	m_DBServerName = dbServerName;
	m_DBName = dbName;
	m_ConnectionString = m_DBName + "@" + m_DBServerName;					
}

//----------------------------------------------------------------------------------------------
void pxSessionInitialization::setDevice( const ::pxDeviceType deviceType, const basar::VarString& deviceName )
{	
	setDeviceType( deviceType );
	setDeviceName( deviceName );	
}

//----------------------------------------------------------------------------------------------
void pxSessionInitialization::setMessageFileName( const basar::VarString& messageFileName )
{
	m_MessageFileName = messageFileName;
}

//----------------------------------------------------------------------------------------------
short pxSessionInitialization::getBranchNo() const
{
	return m_BranchNo;
}

//----------------------------------------------------------------------------------------------
const basar::VarString& pxSessionInitialization::getCountryCode() const
{
	return m_CountryCode;
}

//----------------------------------------------------------------------------------------------
const basar::VarString& pxSessionInitialization::getDBServerName() const
{
	return m_DBServerName;
}

//----------------------------------------------------------------------------------------------
const basar::VarString& pxSessionInitialization::getDBName() const
{
	return m_DBName;
}

//----------------------------------------------------------------------------------------------
const basar::VarString& pxSessionInitialization::getDeviceName() const
{
	return m_DeviceName;
}

//----------------------------------------------------------------------------------------------
::pxDeviceType pxSessionInitialization::getDeviceType() const			
{
	return m_DeviceType;
}

//----------------------------------------------------------------------------------------------
const basar::VarString& pxSessionInitialization::getMessageFileName() const
{
	return m_MessageFileName;
}

//----------------------------------------------------------------------------------------------
void pxSessionInitialization::setCountryCode( const basar::VarString& countrycode )
{
	m_CountryCode = countrycode;
}

//----------------------------------------------------------------------------------------------
void pxSessionInitialization::setDeviceName( const basar::VarString& name )
{
	m_DeviceName = name;
}

//----------------------------------------------------------------------------------------------
void pxSessionInitialization::setDeviceType( const ::pxDeviceType type )
{
	if( ::IsValidDevice( type ) )
	{
		m_DeviceType = type;
	}
}

//----------------------------------------------------------------------------------------------
void pxSessionInitialization::setConnectionString( const basar::VarString& connectionstring )
{
	m_ConnectionString = connectionstring;	
}

//----------------------------------------------------------------------------------------------
const basar::VarString& pxSessionInitialization::getDBConnectionString() const
{
	return m_ConnectionString;	
}

//----------------------------------------------------------------------------------------------
bool pxSessionInitialization::isConnectionStringSet() const
{
    return false == getDBConnectionString().empty();
}

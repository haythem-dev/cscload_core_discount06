//--------------------------------------------------------------------------------------------------//
/*! \brief      
 *  \author     Bischof Bjoern
 *  \date       29.12.2010
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "appsession.h"
#include <dbconnectionbase.h>
#include <sstream>
#include <iomanip>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//

namespace csc_phatra
{
	AppSession::AppSession(
		::libBatch::dbConnection::DBConnectionBasePtr ifxconn,
		::libBatch::dbConnection::DBConnectionBasePtr tcaconn) :
		m_IFXConnection(ifxconn),
		m_TCAConnection(tcaconn)
	{
	}

	AppSession::~AppSession()
	{
	}

	std::ostream& AppSession::toStream( std::ostream& strm ) const
	{
		strm << std::endl;
		strm << m_AppArgs;    
		        
		return strm;
	}
}//end csc_phatra



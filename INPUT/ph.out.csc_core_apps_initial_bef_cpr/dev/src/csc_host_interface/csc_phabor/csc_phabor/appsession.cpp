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

namespace csc_phabor
{
	AppSession::AppSession( ::libBatch::dbConnection::DBConnectionBasePtr ifxconn,
							::libBatch::dbConnection::DBConnectionBasePtr tcaconn1,
							::libBatch::dbConnection::DBConnectionBasePtr tcaconn2 
						  )
	:m_IFXConnection(ifxconn), m_TCAConnection1(tcaconn1), m_TCAConnection2(tcaconn2)
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
}//end csc_phabor



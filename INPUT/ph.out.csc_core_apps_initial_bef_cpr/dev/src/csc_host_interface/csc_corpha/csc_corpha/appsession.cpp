//--------------------------------------------------------------------------------------------------//
/*! \brief      
 *  \author     Bischof Bjoern
 *  \date       29.12.2010
 *  \version    00.00.00.01 first version 
 */ 
//--------------------------------------------------------------------------------------------------//

#include "appsession.h"
#include <dbconnectionbase.h>
#include <sstream>
#include <iomanip>

namespace csc_corpha
{

	AppSession::AppSession( ::libBatch::dbConnection::DBConnectionBasePtr tcaconn )
		: m_TCAConnection(tcaconn)
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

}//end csc_corpha



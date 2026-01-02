//--------------------------------------------------------------------------------------------------//
/*! \brief      
 *  \author     Bischof Bjoern
 *  \date       29.12.2010
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHABOR_APPSESSION_H
#define GUARD_CSC_PHABOR_APPSESSION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "appargs.h"
#include <libbasarcmnutil.h>
#include <dbconnectionbaseptr.h>
#include <iosfwd>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor
{
	class AppSession
	{  
		public:
			AppSession( //const cmdLine::AppArgs&,
				::libBatch::dbConnection::DBConnectionBasePtr, 
				::libBatch::dbConnection::DBConnectionBasePtr,
				::libBatch::dbConnection::DBConnectionBasePtr
				);
			~AppSession();

			std::ostream& toStream( std::ostream& strm = std::cout ) const;

			libBatch::dbConnection::DBConnectionBasePtr         m_IFXConnection;
			libBatch::dbConnection::DBConnectionBasePtr         m_TCAConnection1;
			libBatch::dbConnection::DBConnectionBasePtr         m_TCAConnection2;
			const cmdLine::AppArgs                              m_AppArgs;        

		private:
			AppSession( const AppSession& );
			AppSession& operator=( const AppSession& );
	};


} // end namespace csc_phabor

#include "appsession.inl"

#endif // end GUARD_CSC_PHABOR_APPSESSION_H

//--------------------------------------------------------------------------------------------------//
/*! \brief AppInitChecker This Class is for checking the commandline and user-administration
 *  \author Johann Franz
 *  \date 09.12.2010
 *  \version 00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_APP_INITIALIZER_H
#define GUARD_LIBCSC_UTILS_APP_INITIALIZER_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "iapplconfigurationptr.h"
#include "xmlconfigreaderptr.h"
#include "icsc_loggerptr.h"
#include "icsc_cmdlineoptionptr.h"

#include "loggerpool.h"
#include "applxmlconfigwrapper.h"

#include <classinfo_macros.h>
#include <cmdlineexception.h>
#include <libbasar_definitions.h>
#include "icsc_logger.h"
#include "csc_logger.h"
#include "imailptr.h"
#include "mail.h"
#include "icsc_cmdlineoptionptr.h"
#include "icsc_cmdlineoption.h"

//exceptions
#include "xmlreaderexception.h"
#include "appinitializerexception.h"
#include "configdatainconsistantexception.h"

#include <dbconnectionbaseptr.h>
#include <cmdlineconfiguration.h>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace libBatch
{
    namespace cmdLine
    {
        class CommandLineParser;
    }
    namespace dbConnection
    {
        struct DBConnectionConfiguration;
    }
}

namespace basar
{
	namespace db
	{
		namespace sql
		{
			class DatabaseInfo;
		}
	}
}

namespace log4cplus 
{
  class Logger;
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
	class ApplXMLConfigWrapper;

	template <class T>
	class AppInitializer
	{  
		public:
			AppInitializer()
			: m_Logger( libcsc_utils::LoggerPool::LoggerCSC )
			{  
				METHODNAME_DEF( AppInitializer, AppInitializer );
				BLOG_TRACE_METHOD( m_Logger, fun );
			};

            virtual ~AppInitializer()	{
				METHODNAME_DEF( AppInitializer, ~AppInitializer );
				BLOG_TRACE_METHOD( m_Logger, fun );
			};
		
            void                                                        setAppArgs(T csc_cmdlineoptions)
			{
				m_CSC_CmdLineOptions = csc_cmdlineoptions;
			};
            
			
            void														init()
			{
				METHODNAME_DEF( AppInitializer, init );
				BLOG_TRACE_METHOD( m_Logger, fun );

				if (0 == m_CSC_CmdLineOptions.get())
				{
					throw AppInitializerException(basar::ExceptInfo(fun, "No command line options object present", __FILE__, __LINE__ ) );
				}

				try 
				{
					//handleCmdLine();
					handleAppConfiguration();   
					setupCSCLogger();
				}
				catch( XmlReaderException& ex )
				{
					throw AppInitializerException(basar::ExceptInfo(fun, ex.what(), __FILE__, __LINE__ ) );
				}
				catch ( ConfigDataInconsistantException& ex )
				{
					throw AppInitializerException(basar::ExceptInfo(fun, ex.what(), __FILE__, __LINE__) );
				}
			};

			const T														getAppArgs                  () const
			{
				METHODNAME_DEF( AppInitializer, getAppArgs );
				BLOG_TRACE_METHOD( m_Logger, fun );

				return m_CSC_CmdLineOptions;
			};        
			const basar::db::sql::DatabaseInfo&							getIFXConnConfiguration		() const
			{
				METHODNAME_DEF( AppInitializer, getIFXConnConfiguration );
				BLOG_TRACE_METHOD( m_Logger, fun );

				return m_ApplConfiguration->getIFXConfiguration();
			};
			
			const basar::db::sql::DatabaseInfo&							getTCAConnConfiguration		() const
			{
				METHODNAME_DEF( AppInitializer, getTCAConnConfiguration );
				BLOG_TRACE_METHOD( m_Logger, fun );

				return m_ApplConfiguration->getTCAConfiguration();
			};
			const IApplConfigurationPtr									getAppConfiguration			() const
			{
				METHODNAME_DEF( AppInitializer, getAppConfiguration );
				BLOG_TRACE_METHOD( m_Logger, fun );

				return m_ApplConfiguration;
			};
			const ICSC_LoggerPtr										getCSCLogger				() const
			{
				return m_CSC_Logger;
			};

		protected:    

			void														handleAppConfiguration		()
			{
				METHODNAME_DEF( AppInitializer, handleAppConfiguration);
				BLOG_TRACE_METHOD( m_Logger, fun );

				ApplXMLConfigWrapper* config = new ApplXMLConfigWrapper( m_CSC_CmdLineOptions->getBranchNo(), m_CSC_CmdLineOptions->getApplicationName(), m_CSC_CmdLineOptions->getConfigFile());

				try
				{
					config->setNoMail(m_CSC_CmdLineOptions->isNoMailSet());
					config->setTesting(m_CSC_CmdLineOptions->isTestingSet());
					config->setExtendedLogging( m_CSC_CmdLineOptions->isExtendedLoggingSet() );

					doHandleAppConfiguration( config );
					config->init();
				}
				catch( XmlReaderException& /*ex*/ )
				{
					delete config; //for bonus points - app can't run w/o config
					throw;
				}

				m_ApplConfiguration = IApplConfigurationPtr( config );
				
			};
			void														setupCSCLogger				()
			{
				IMailPtr mailObject = IMailPtr( new Mail(m_ApplConfiguration->getSmtpHost(), m_ApplConfiguration->getSmtpPort(), m_Logger) );	

				m_CSC_Logger = ICSC_LoggerPtr( new CSC_Logger(mailObject, m_ApplConfiguration, m_Logger) );

				m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "CSC_Logger ready...", m_ApplConfiguration);
			};

		    virtual void                                                doHandleAppConfiguration    ( ApplXMLConfigWrapper* ) = 0;

			const log4cplus::Logger&									m_Logger;
			T															m_CSC_CmdLineOptions;
			IApplConfigurationPtr										m_ApplConfiguration;
			ICSC_LoggerPtr												m_CSC_Logger;

		private:
			AppInitializer( const AppInitializer& );
			AppInitializer& operator=( const AppInitializer& );
	};
}//end namespace util
#endif // end GUARD_LIBCSC_UTILS_APP_INITIALIZER_H


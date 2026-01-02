//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief  definition for xml config wrapper
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_APPLXMLCONFIGWRAPPER_H
#define GUARD_LIBCSC_UTILS_APPLXMLCONFIGWRAPPER_H

#include <libbasarcmnutil.h>
#include <libbasardbsql_databaseinfo.h>
#include "iapplconfiguration.h"
#include "xmlconfigreaderptr.h"


namespace libcsc_utils
{

	class ApplXMLConfigWrapper : public IApplConfiguration
	{
		public:
			ApplXMLConfigWrapper( const basar::Int16 branchno, const basar::VarString& context, const basar::VarString& xmlFileName);

			//interface IApplConfiguration
			// IFX
			const basar::db::sql::DatabaseInfo&						getIFXConfiguration();
			basar::Int32											getIFXConnectionRetries();
			basar::Int32											getIFXConnectionWaitBeforeRetry();

			// TCA
			const basar::db::sql::DatabaseInfo&						getTCAConfiguration();
			basar::Int32											getTCAConnectionRetries();
			basar::Int32											getTCAConnectionWaitBeforeRetry();		
			bool													isTCAActivated() const;

			// pxVerbund
			basar::VarString										getMessageFile() const;
			basar::VarString										getSystemLogFile() const;
			basar::Int32											getLogMode() const;
			basar::VarString										getComputer() const;	
			basar::VarString										getLogFile() const;
			basar::VarString										getDeviceName() const;
			basar::Int32											getDeviceType() const;
			basar::Int32											getMaxSelectOrders() const;
			bool													getBulkInsert() const;
			basar::VarString										getDataSource() const;
			basar::VarString										getCountryCode() const;
			basar::Int16											getBranchNo() const;

			//KSC
			basar::VarString										getKSCHost() const;
			basar::VarString										getFinishOrderType() const;
			basar::VarString										getTerminalName() const;
			basar::Int16											getKSCServerPort() const;

			// ZDP
			basar::VarString										getZDPHost() const;
			basar::VarString										getZDPDatabase() const;
			bool													isZDPActivated() const;

			//misc
			basar::Int32											getPollingInterval() const;
			basar::VarString										getSmtpHost() const;
			basar::Int16											getSmtpPort() const;
			basar::VarString										getSmtpFromAddress() const;

			basar::VarString										getInformationSmtpRecipients() const;
			basar::VarString										getWarningSmtpRecipients() const;
			basar::VarString										getErrorSmtpRecipients() const;

			basar::VarString										getMailThreshold() const;

			basar::VarString										getApplicationName() const;

			void init(); //throws xmlreaderexception

			basar::VarString										getLogMessage() const;

            bool                                                  isTestingSet() const;
            bool                                                  isNoMailSet() const;		
            bool                                                  isBulkInsertSet() const;		

			bool													isExtendedLoggingSet() const;

            void                                                        setTesting(bool isTesting);
            void                                                        setNoMail(bool isNoMail);
			
			void														setOrderFilter( const basar::VarString orderfilter );
			basar::VarString										getOrderFilter() const;

			void														setExtendedLogging( bool extlogging );

		private:
			ApplXMLConfigWrapper(const ApplXMLConfigWrapper&);
			ApplXMLConfigWrapper& operator=(const ApplXMLConfigWrapper&);
		
			void readXmlFile(); //throws xmlreaderexception

            void checkConfigData(); //throws configdatainconsitantexception

			XmlConfigReaderPtr m_XmlConfigReader;

			basar::db::sql::DatabaseInfo                                        m_IFXConfiguration;
			basar::db::sql::DatabaseInfo                                        m_TCAConfiguration;

			basar::Int16		m_Branchno;
			basar::VarString	m_Context;
			basar::VarString	m_XmlFileName;
			basar::VarString	m_OrderFilter;
			bool				m_XmlFileRead;
            bool                m_IsTestingSet;
            bool                m_IsNoMailSet;			
			bool				m_ExtendedLogging;

	};
}//namespace libcsc_utils

#endif //#ifndef GUARD_LIBCSC_UTILS_APPLXMLCONFIGWRAPPER_H

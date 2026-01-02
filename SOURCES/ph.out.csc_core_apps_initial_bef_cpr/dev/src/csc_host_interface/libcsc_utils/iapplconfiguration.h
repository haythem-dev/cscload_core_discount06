//-------------------------------------------------------------------------------------------//
/*! \file 
*   \brief  interface declaration for application specific configuration
*   \author 
*   \date   
*/
//-------------------------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_IAPPLCONFIGURATION_H
#define GUARD_LIBCSC_UTILS_IAPPLCONFIGURATION_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//

#include "iloggable.h"

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
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



//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
//-------------------------------------------------------------------------------------------------//
// interface declaration
//-------------------------------------------------------------------------------------------------//
	class IApplConfiguration : public libcsc_utils::ILoggable
	{
		public:
			virtual ~IApplConfiguration(){};

			// IFX
			virtual const basar::db::sql::DatabaseInfo&						getIFXConfiguration() = 0;
			virtual basar::Int32											getIFXConnectionRetries() = 0;
			virtual basar::Int32											getIFXConnectionWaitBeforeRetry() = 0;

			// TCA
			virtual const basar::db::sql::DatabaseInfo&						getTCAConfiguration() = 0;
			virtual basar::Int32											getTCAConnectionRetries() = 0;
			virtual basar::Int32											getTCAConnectionWaitBeforeRetry() = 0;			
			virtual bool													isTCAActivated() const = 0;

			// pxVerbund
			virtual basar::VarString										getMessageFile() const = 0;
			virtual basar::VarString										getSystemLogFile() const = 0;
			virtual basar::Int32											getLogMode() const = 0;
			virtual basar::VarString										getComputer() const = 0;	
			virtual basar::VarString										getLogFile() const = 0;
			virtual basar::VarString										getDeviceName() const = 0;
			virtual basar::Int32											getDeviceType() const = 0;
			virtual basar::VarString										getDataSource() const = 0;
			virtual basar::VarString										getCountryCode() const = 0;
			virtual basar::Int16											getBranchNo() const = 0;
			
			//KSC
			virtual basar::VarString										getKSCHost() const = 0;
			virtual basar::VarString										getFinishOrderType() const = 0;
			virtual basar::VarString										getTerminalName() const = 0;
			virtual basar::Int16											getKSCServerPort() const = 0;

			// ZDP
			virtual basar::VarString										getZDPHost() const = 0;
			virtual basar::VarString										getZDPDatabase() const = 0;
			virtual bool													isZDPActivated() const = 0;

			//misc
			virtual basar::Int32											getPollingInterval() const = 0;
			virtual basar::Int32											getMaxSelectOrders() const = 0;
			virtual basar::VarString										getSmtpHost() const = 0;
			virtual basar::Int16											getSmtpPort() const = 0;
			virtual basar::VarString										getSmtpFromAddress() const = 0;

			virtual basar::VarString										getInformationSmtpRecipients() const = 0;
			virtual basar::VarString										getWarningSmtpRecipients() const = 0;
			virtual basar::VarString										getErrorSmtpRecipients() const = 0;

			virtual basar::VarString										getMailThreshold() const = 0;

			virtual basar::VarString										getApplicationName() const = 0;
            
            virtual bool													isTestingSet() const = 0;
            virtual bool													isNoMailSet() const = 0;
            virtual bool													isBulkInsertSet() const = 0;
			virtual bool													getBulkInsert() const = 0;

			virtual basar::VarString										getOrderFilter() const = 0;			

			virtual bool													isExtendedLoggingSet() const = 0;

	};
}//end namespace libcsc_utils
//---------------------------------------------------------------------------

#endif // GUARD_LIBCSC_UTILS_IAPPLCONFIGURATION_H

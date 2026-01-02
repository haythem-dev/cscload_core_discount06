//-------------------------------------------------------------------------------------------------------------------//
/*! \file		pxverbund.h
*  \brief		representation of config pxverbund
*  \author		
*  \date		
*/
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CONFIG_PXVERBUND_H
#define GUARD_LIBCSC_UTILS_CONFIG_PXVERBUND_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include "config_definitions.h"

namespace libcsc_utils
{
	namespace config
	{
		//-------------------------------------------------------------------------------------------------------------------//
		/*! \brief representation of config pxverbund
		*/
		//-------------------------------------------------------------------------------------------------------------------//

		class PxVerbund
		{
		public:
			PxVerbund(void);
			PxVerbund(const basar::VarString& messageFile, const basar::VarString& logFile, const basar::VarString& systemLogFile,
				basar::Int32 logMode, const basar::VarString& computer, const basar::VarString& dataSource,
				const basar::VarString& deviceName, basar::Int32 deviceType);
			
			virtual ~PxVerbund(void);

			// Setter
			void					setMessageFile          (const basar::VarString& messageFile);
			void					setLogFile				(const basar::VarString& logFile);
			void					setSystemLogFile		(const basar::VarString& systemLogFile);
			void					setLogMode				(basar::Int32 logMode);
			void					setComputer				(const basar::VarString& computer);
			void					setDataSource			(const basar::VarString& dataSource);
			void					setDeviceName			(const basar::VarString& deviceName);
			void					setDeviceType			(basar::Int32 deviceType);

			// Getter
			const basar::VarString&	getMessageFile          (void) const;
			const basar::VarString&	getLogFile				(void) const;
			const basar::VarString&	getSystemLogFile		(void) const;
			basar::Int32		getLogMode				(void) const;
			const basar::VarString&	getComputer				(void) const;
			const basar::VarString&	getDataSource			(void) const;
			const basar::VarString&	getDeviceName			(void) const;
			basar::Int32  	getDeviceType			(void) const;

			// 
			bool				isSetMessageFile		(void) const;
			bool				isSetLogFile			(void) const;
			bool				isSetSystemLogFile		(void) const;
			bool				isSetLogMode	 		(void) const;
			bool				isSetComputer			(void) const;
			bool				isSetDataSource			(void) const;
			bool				isSetDeviceName			(void) const;
			bool				isSetDeviceType			(void) const;


		private:
			basar::VarString m_MessageFile;
			basar::VarString m_LogFile;
			basar::VarString m_SystemLogFile;
			basar::Int32     m_LogMode;
			basar::VarString m_Computer;
			basar::VarString m_DataSource;
			basar::VarString m_DeviceName;
			basar::Int32     m_DeviceType;

			bool m_IsSetMessageFile;
			bool m_IsSetLogFile;
			bool m_IsSetSystemLogFile;
			bool m_IsSetLogMode;
			bool m_IsSetComputer;
			bool m_IsSetDataSource;
			bool m_IsSetDeviceName;
			bool m_IsSetDeviceType;

		};
	}
}
#endif //GUARD_LIBCSC_UTILS_CONFIG_PXVERBUND_H

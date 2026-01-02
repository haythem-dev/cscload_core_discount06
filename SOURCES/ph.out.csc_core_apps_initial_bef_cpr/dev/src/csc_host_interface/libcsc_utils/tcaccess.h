//-------------------------------------------------------------------------------------------------------------------//
/*! \file		tcaccess.h
*  \brief		representation of config tcaccess
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CONFIG_TCACCESS_H
#define GUARD_LIBCSC_UTILS_CONFIG_TCACCESS_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc_utils
{
namespace config
{
	//-------------------------------------------------------------------------------------------------------------------//
	/*! \brief representation of config tcaccess
	*/
	//-------------------------------------------------------------------------------------------------------------------//
	class TCAccess
	{
	public:
		TCAccess(void);
		TCAccess(basar::VarString const& tcaHost, basar::VarString const& ipAddress, basar::Int32 port, basar::VarString const& tcaTransaction,
			basar::VarString const& username, basar::VarString const& password, basar::VarString const& cicsLinkProgram, basar::Int32 comareaLength);
		~TCAccess(void);

		void						setTcaHost				(basar::VarString const& value);
		void						setIpAddress			(basar::VarString const& value);
		void						setPort					(basar::Int32 value);
		void						setTcaTransaction		(basar::VarString const& value);
		void						setUsername				(basar::VarString const& value);
		void						setPassword				(basar::VarString const& value);
		void						setCicsLinkProgram		(basar::VarString const& value);
		void						setComareaLength		(basar::Int32 value);
		void                        setConnectionRetries    (basar::Int32 value);
		void                        setConnWaitBeforeRetry  (basar::Int32 value);
		void                        setActivate 			(bool value);

		basar::VarString		getTcaHost				(void) const;
		basar::VarString		getIpAddress			(void) const;
		basar::Int32			getPort					(void) const;
		basar::VarString		getTcaTransaction		(void) const;
		basar::VarString		getUsername				(void) const;
		basar::VarString		getPassword				(void) const;
		basar::VarString		getCicsLinkProgram		(void) const;
		basar::Int32			getComareaLength		(void) const;
		basar::Int32			getConnectionRetries    (void) const;
		basar::Int32			getConnWaitBeforeRetry	(void) const;
		bool					getActivate 			(void) const;

		bool					isSetTcaHost			(void) const;
		bool					isSetIpAddress			(void) const;
		bool					isSetPort				(void) const;
		bool					isSetTcaTransaction		(void) const;
		bool					isSetUsername			(void) const;
		bool					isSetPassword			(void) const;
		bool					isSetCicsLinkProgram	(void) const;
		bool					isSetComareaLength		(void) const;
		bool					isSetConnectionRetries  (void) const;
		bool					isSetConnWaitBeforeRetry(void) const;
		bool					isSetActivate			(void) const;

	private:
	
		basar::VarString m_TcaHost;
		basar::VarString m_IpAddress;
		basar::Int32 m_Port;
		basar::VarString m_TcaTransaction;
		basar::VarString m_Username;
		basar::VarString m_Password;
		basar::VarString m_CicsLinkProgram;
		basar::Int32 m_ComareaLength;
		basar::Int32 m_ConnectionRetries;
		basar::Int32 m_ConnectionWaitBeforeRetry;
		bool m_Activate;

		bool m_IsSetTcaHost;
		bool m_IsSetIpAddress;
		bool m_IsSetPort;
		bool m_IsSetTcaTransaction;
		bool m_IsSetUsername;
		bool m_IsSetPassword;
		bool m_IsSetCicsLinkProgram;
		bool m_IsSetComareaLength;
		bool m_IsSetConnectionRetries;
		bool m_IsSetConnectionWaitBeforeRetry;
		bool m_IsSetActivate;
	};
}
}
#endif // GUARD_LIBCSC_UTILS_CONFIG_TCACCESS_H

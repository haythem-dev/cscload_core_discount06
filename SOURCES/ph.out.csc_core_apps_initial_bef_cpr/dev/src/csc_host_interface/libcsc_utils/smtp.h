//-------------------------------------------------------------------------------------------------------------------//
/*! \file		smtp.h
*  \brief		representation of config smtp
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CONFIG_SMTP_H
#define GUARD_LIBCSC_UTILS_CONFIG_SMTP_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include "config_definitions.h"

namespace libcsc_utils
{
namespace config
{
	//-------------------------------------------------------------------------------------------------------------------//
	/*! \brief representation of config smtp
	*/
	//-------------------------------------------------------------------------------------------------------------------//

	class SMTP
	{

	public:
		SMTP(void);
		SMTP(basar::VarString const& host, basar::Int32 port, basar::VarString const& username, basar::VarString const& password,
			basar::VarString const& sendMailFrom, basar::VarString const& smtTypeInformation, basar::VarString const& smtTypeWarnings, 
			basar::VarString const& smtTypeErrors);

		virtual ~SMTP(void);

		void setHost				(basar::VarString const& value);
		void setPort				(basar::Int32 value);
		void setUsername			(basar::VarString const& value);
		void setPassword			(basar::VarString const& value);
		void setSendMailFrom		(basar::VarString const& value);
		void setSmtpTypeInformation	(basar::VarString const& value);
		void setSmtpTypeWarnings	(basar::VarString const& value);
		void setSmtpTypeErrors		(basar::VarString const& value);
		
		basar::VarString		getHost					(void) const;
		basar::Int32			getPort					(void) const;
		basar::VarString		getUsername				(void) const;
		basar::VarString		getPassword				(void) const;
		basar::VarString		getSendMailFrom			(void) const;
		basar::VarString		getSmtpTypeInformation	(void);
		basar::VarString		getSmtpTypeWarnings		(void);
		basar::VarString		getSmtpTypeErrors		(void);

		bool isSetHost				(void) const;
		bool isSetPort				(void) const;
		bool isSetUsername			(void) const;
		bool isSetPassword			(void) const;
		bool isSetSendMailFrom		(void) const;
		bool isSetSmtpTypeInformation	(void) const;
		bool isSetSmtpTypeWarnings	(void) const;
		bool isSetSmtpTypeErrors		(void) const;

	private:
		basar::VarString m_Host;
		basar::Int32 m_Port;
		basar::VarString m_Username;
		basar::VarString m_Password;
		basar::VarString m_SendMailFrom;
		SmtpTypeList m_SmtpTypeList;

		bool m_IsSetSmtpTypeInformation;
		bool m_IsSetSmtpTypeWarnings;
		bool m_IsSetSmtpTypeErrors;
		bool m_IsSetHost;
		bool m_IsSetPort;
		bool m_IsSetUsername;
		bool m_IsSetPassword;
		bool m_IsSetSendMailFrom;
	};
}
}
#endif //GUARD_LIBCSC_UTILS_CONFIG_SMTP_H

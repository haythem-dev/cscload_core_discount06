//---------------------------------------------------------------------------//
/*! \file		
 *  \brief	class for mailing
 *  \author	Steffen Heinlein
 *  \date		25.06.2012
 *  \version	00.00.00.01 first version
*/ 
//---------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_MAIL_H
#define GUARD_LIBCSC_UTILS_MAIL_H

//#include <vector>
#include <set>
#include <libbasarcmnutil.h>
#include "imail.h"

namespace libcsc_utils
{

	class Mail : public IMail
	{
	public:
		Mail( const basar::VarString& smtpserver, const basar::Int16 smtpport, const log4cplus::Logger& logger );
		virtual ~Mail();	

		void sendMail(	const basar::I18nString & subject, const basar::I18nString & message
						, const basar::cmnutil::Locale::LanguageEnum locale	= basar::cmnutil::Locale::getLocale() );

		void setHtmlFormat(const bool html = true );

		void setSendFrom( const basar::VarString& sender );

		void setRecipientSendTo(const basar::VarString& recipient );
		void setRecipientSendToCopy(const basar::VarString& recipient );
		void setRecipientSendToBlindCopy(const basar::VarString& recipient );

	private:
		typedef std::set<basar::VarString> RecipientCollection;
		typedef void (basar::cmnutil::MailMessage::*PtrToSetFunction)(const basar::VarString &);

		Mail(const Mail& r);
		Mail & operator = (const Mail& r);

		void init();
		void shutdown();

		void addRecipientToMail( basar::cmnutil::MailMessage& mail, const RecipientCollection& coll, PtrToSetFunction ptrSetFunction );
		void addRecipientToCollection(RecipientCollection & coll, const basar::VarString & recipient);
		void checkMail(const basar::I18nString& subject, const basar::I18nString& message);
		bool isValidEmailAddress(const basar::VarString& address) const;

		basar::VarString			m_SendFrom;	
		RecipientCollection			m_SendTo;		
		RecipientCollection			m_SendToCopy;	
		RecipientCollection			m_SendToBlindCopy;
		bool						m_HtmlFormat;
		basar::VarString			m_SMTPServer;
		basar::Int16				m_PortNumber;
		const log4cplus::Logger&	m_Logger;
	};

} // namespace util

#endif // GUARD_LIBCSC_UTILS_MAIL_H

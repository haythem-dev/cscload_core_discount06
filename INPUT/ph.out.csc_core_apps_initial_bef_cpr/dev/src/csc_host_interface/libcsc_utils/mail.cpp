//---------------------------------------------------------------------------//
/*! \file branchdm.cpp
 *  \brief implementation of domain module Mail
 *  \author Dirk Kapusta
 *  \date 05.02.2008
 *  \version 00.00.00.01 first version
 */ 
//---------------------------------------------------------------------------//

#include "mail.h"
#include "mailexception.h"

#include <boost/regex.hpp>
#include <libbasarcmnutil_email.h>
#include <classinfo_macros.h>

namespace libcsc_utils
{

void Mail::sendMail(	const basar::I18nString & subject, const basar::I18nString & message
						, const basar::cmnutil::Locale::LanguageEnum locale	/*= basar::cmnutil::Locale::getLocale()*/ )
{
	METHODNAME_DEF( Mail, sendMail )
	BLOG_TRACE_METHOD( m_Logger, fun );	
	
	basar::VarString msg;
	using namespace basar::cmnutil;

	this->checkMail( subject, message );

	MailMessage mail( locale );
	mail.setContentType( m_HtmlFormat ? MailMessage::TEXT_SIMPLEHTML : MailMessage::TEXT_PLAIN );
	mail.setFrom( m_SendFrom );
	mail.setSubject( subject );
	mail.setBody( message );
	this->addRecipientToMail( mail, m_SendTo, &MailMessage::setTo );
	this->addRecipientToMail( mail, m_SendToCopy, &MailMessage::setCC );
	this->addRecipientToMail( mail, m_SendToBlindCopy, &MailMessage::setBCC );

	Smtp smtp( m_SMTPServer, m_PortNumber );
	Smtp::RetCodeEnum res = smtp.connect();
	if( Smtp::SMTP_SUCCESS != res )
	{
		msg = "Unable to connect to " + m_SMTPServer;		
		throw MailException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
	}

	res = smtp.send( mail );
	if( Smtp::SMTP_SUCCESS != res )
	{
		smtp.disconnect();
		msg = "Unable to send mail";		
		throw MailException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
	}

	smtp.disconnect();
}

//---------------------------------------------------------------------------//
Mail::Mail( const basar::VarString& smtpserver, const basar::Int16 smtpport, const log4cplus::Logger& logger )
: m_SMTPServer( smtpserver ), m_PortNumber( smtpport ), m_Logger( logger )
{
	METHODNAME_DEF( Mail, Mail )
	BLOG_TRACE_METHOD( m_Logger, fun );	
}

//---------------------------------------------------------------------------//
Mail::~Mail()
{
	METHODNAME_DEF( Mail, ~Mail )
	BLOG_TRACE_METHOD( m_Logger, fun );	
}

//---------------------------------------------------------------------------//
void Mail::init()
{
	METHODNAME_DEF( Mail, init )
	BLOG_TRACE_METHOD( m_Logger, fun );	
}

//---------------------------------------------------------------------------//
void Mail::shutdown()
{
	METHODNAME_DEF( Mail, shutdown )
	BLOG_TRACE_METHOD( m_Logger, fun );	

	m_HtmlFormat = false;
	m_SMTPServer = "";
	m_PortNumber = 0;
	m_SendFrom = "";
	m_SendTo.clear();
	m_SendToCopy.clear();
	m_SendToBlindCopy.clear();
}

//---------------------------------------------------------------------------//
void Mail::addRecipientToCollection(RecipientCollection& coll,	const basar::VarString& recipient)
{
	METHODNAME_DEF( Mail, addRecipientToCollection )
	BLOG_TRACE_METHOD( m_Logger, fun );

	using basar::cmnutil::CollBString;
	CollBString recipients;
	recipient.tokenizeAndTrim( recipients, ";", basar::cmnutil::BString::ALL, true, true );
	for( CollBString::const_iterator iter = recipients.begin(); iter != recipients.end(); ++iter )
	{
		basar::VarString address( *iter );
		if( !this->isValidEmailAddress( address ) )
		{
			basar::VarString msg = address + " is not a valid email address";
			throw MailException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
		}
		coll.insert( address );
	}
}

//---------------------------------------------------------------------------//
bool Mail::isValidEmailAddress(const basar::VarString& address) const
{
	METHODNAME_DEF( Mail, isValidEmailAddress )
	BLOG_TRACE_METHOD( m_Logger, fun );

	static const boost::regex e(	"^([a-zA-Z0-9_\\-\\.]+)@((\\[[0-9]{1,3}"
									"\\.[0-9]{1,3}\\.[0-9]{1,3}\\.)|(([a-zA-Z0-9\\-]+\\"
									".)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\\]?)$" );
	return boost::regex_match( address, e );
}

//---------------------------------------------------------------------------//
void Mail::setSendFrom( const basar::VarString& sender )
{
	METHODNAME_DEF( Mail, setSendFrom )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_SendFrom = sender;
	m_SendFrom.trim( basar::cmnutil::BString::ALL );
}

//---------------------------------------------------------------------------//
void Mail::setRecipientSendTo(const basar::VarString& recipient )
{
	METHODNAME_DEF( Mail, setRecipientSendTo )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_SendTo.clear();
	this->addRecipientToCollection( m_SendTo, recipient );
}

//---------------------------------------------------------------------------//
void Mail::setRecipientSendToCopy(const basar::VarString& recipient )
{
	METHODNAME_DEF( Mail, setRecipientSendToCopy )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_SendToCopy.clear();
	this->addRecipientToCollection( m_SendToCopy, recipient );
}

//---------------------------------------------------------------------------//
void Mail::setRecipientSendToBlindCopy(const basar::VarString& recipient )
{
	METHODNAME_DEF( Mail, setRecipientSendToBlindCopy )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_SendToBlindCopy.clear();
	this->addRecipientToCollection( m_SendToBlindCopy, recipient );
}

//---------------------------------------------------------------------------//
void Mail::setHtmlFormat(const bool html /*= true */)
{
	METHODNAME_DEF( Mail, setHtmlFormat )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_HtmlFormat = html;
}

//---------------------------------------------------------------------------//
void Mail::checkMail(const basar::I18nString& subject, const basar::I18nString& message)
{
	METHODNAME_DEF( Mail, checkMail )
	BLOG_TRACE_METHOD( m_Logger, fun );

	basar::VarString msg;

	if( 0 == m_SendFrom.length() )
	{
		m_SendFrom = "zbw@phoenixgroup.eu";
		/*
		msg = "Sender email address not set!";
		throw MailException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
		*/
	}

	if( m_SendTo.empty() )
	{
		msg = "Recipient email address not set!";
		throw MailException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
	}

	if( 0 == subject.length() )
	{
		msg = "No subject given!";
		throw MailException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
	}

	if( 0 == message.length() )
	{
		msg = "No message given!";
		throw MailException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
	}
}

//---------------------------------------------------------------------------//
void Mail::addRecipientToMail(basar::cmnutil::MailMessage & mail, const RecipientCollection & coll, PtrToSetFunction ptrSetFunction)
{
	METHODNAME_DEF( Mail, addRecipientToMail )
	BLOG_TRACE_METHOD( m_Logger, fun );

	for( RecipientCollection::const_iterator iter = coll.begin(); iter != coll.end(); ++iter )
	{
		// call member function through function pointer
		( mail.*ptrSetFunction ) ( *iter );
	}
}

} // namespace util

#ifndef GUARD_LIBCSC_UTILS_IMAIL_H
#define GUARD_LIBCSC_UTILS_IMAIL_H

#include <libbasarcmnutil.h>

namespace libcsc_utils
{
	class IMail
	{
		public:
			
			virtual ~IMail(){};

			virtual void sendMail(	const basar::I18nString & subject, const basar::I18nString & message
							, const basar::cmnutil::Locale::LanguageEnum locale	= basar::cmnutil::Locale::getLocale() ) = 0;

			virtual void setHtmlFormat(const bool html = true ) = 0;

			virtual void setSendFrom( const basar::VarString& sender ) = 0;

			virtual void setRecipientSendTo(const basar::VarString& recipient ) = 0;
			virtual void setRecipientSendToCopy(const basar::VarString& recipient ) = 0;
			virtual void setRecipientSendToBlindCopy(const basar::VarString& recipient ) = 0;
	};
}//end namespace util

#endif //#ifndef GUARD_LIBCSC_UTILS_IMAIL_H

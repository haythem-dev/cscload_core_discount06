#ifndef GUARD_LIBCSC_UTILS_XMLCONFIGREADER_H
#define GUARD_LIBCSC_UTILS_XMLCONFIGREADER_H

#include "config_definitions.h"
#include "iapplconfigurationptr.h"

#include <libbasarcmnutil.h>

#ifdef WIN32
#pragma warning (push)
#pragma warning (disable: 4512)
#endif
#include <QtCore/QXmlStreamReader>
#ifdef WIN32
#pragma warning (pop)
#endif

namespace libcsc_utils
{
	namespace config
	{
		class General;
		class Informix;
		class KSCServer;
		class SMTP;
		class TCAccess;
	}//end namespace config

	class XmlConfigReader
	{
	public:
		XmlConfigReader( const basar::Int16 branchno, const basar::VarString& context );
		~XmlConfigReader();

		void                             readFile(const basar::VarString& fileName);
		const config::SettingsPtr        getSettings()                                const;

	private:
		void parseXml();
		void readKSCRefreshSettingsSection();
		void readCountrySection();
		void readSettingsSection();
		void readInterfacesSection();
		void readBranchesSection();
		void readBranchSection();
		void readIfaceSection();
		void readSmtpSection();

		void fillGeneral();
		void fillInformix(config::InformixPtr ifxptr);
		void fillKSCServer();
		void fillSmtp();
		void fillTCAccess();
		void fillPxVerbund();

	private:
		const log4cplus::Logger&                                m_Logger;
		basar::VarString                                        m_IfaceName;
		basar::Int16                                            m_Branchno;
		QXmlStreamReader                                        m_XmlStreamReader;
		basar::Int8												m_VisitLevel;

		config::GeneralPtr                                      m_ConfigGeneralPtr;
		config::InformixPtr                                     m_ConfigInformixCSCPtr;
		config::InformixPtr                                     m_ConfigInformixZDPPtr;
		config::KSCServerPtr                                    m_ConfigKSCServerPtr;
		config::PxVerbundPtr                                    m_ConfigPxVerbundPtr;
		config::SMTPPtr                                         m_ConfigSmtpPtr;
		config::TCAccessPtr                                     m_ConfigTCAccessPtr;
	};

} /* namespace libcsc_utils */
#endif /*GUARD_LIBCSC_UTILS_XMLCONFIGREADER_H_ */

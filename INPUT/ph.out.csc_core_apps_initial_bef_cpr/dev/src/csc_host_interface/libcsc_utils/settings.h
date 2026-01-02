//-------------------------------------------------------------------------------------------------------------------//
/*! \file		settings.h
*  \brief		representation of config settings
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_SETTINGS_H
#define GUARD_LIBCSC_UTILS_SETTINGS_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include "config_definitions.h"

namespace libcsc_utils
{

namespace config
{
	//-------------------------------------------------------------------------------------------------------------------//
	/*! \brief representation of config settings
	*/
	//-------------------------------------------------------------------------------------------------------------------//

	class Settings
	{
	public:
		Settings(const config::GeneralPtr generalPtr,
				const config::InformixPtr  informixPtrCSC,  const config::InformixPtr  informixPtrZDP, 
				const config::KSCServerPtr kscServerPtr, const config::SMTPPtr smtpPtr,
				const config::TCAccessPtr  tcAccessPtr,  const config::PxVerbundPtr pxVerbundPtr);
		~Settings(void);
		
		const GeneralPtr                 getGeneral()   const;
		const InformixPtr                getInformix()  const;
		const InformixPtr                getInformixZDP()  const;
		const KSCServerPtr               getKSCServer() const;
		const SMTPPtr                    getSMTP()      const;
		const TCAccessPtr                getTCAccess()  const;
		const PxVerbundPtr               getPxVerbund() const;
	
	private:
		GeneralPtr     m_Gerneral;
		InformixPtr    m_Informix;
		InformixPtr    m_InformixZDP;
		KSCServerPtr   m_KscServer;
		SMTPPtr        m_Smtp;
		TCAccessPtr    m_TcAccess;
		PxVerbundPtr   m_PxVerbund;
	};
	

}
}
#endif //GUARD_LIBCSC_UTILS_SETTINGS_H

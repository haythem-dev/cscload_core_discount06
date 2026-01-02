//-------------------------------------------------------------------------------------------------------------------//
/*! \file		settings.cpp
*  \brief		representation of config settings
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#include "settings.h"
#include "general.h"
#include "informix.h"
#include "kscserver.h"
#include "smtp.h"
#include "tcaccess.h"
#include "pxverbund.h"

namespace libcsc_utils
{
namespace config
{

Settings::Settings(const config::GeneralPtr generalPtr,
				const config::InformixPtr  informixPtrCSC, const config::InformixPtr  informixPtrZDP,
				const config::KSCServerPtr kscServerPtr, const config::SMTPPtr smtpPtr,
				const config::TCAccessPtr  tcAccessPtr,  const config::PxVerbundPtr pxVerbundPtr)
		: m_Gerneral( generalPtr),
		  m_Informix(  informixPtrCSC),
		  m_InformixZDP(  informixPtrZDP),
		  m_KscServer( kscServerPtr ),
		  m_Smtp( smtpPtr ),
		  m_TcAccess( tcAccessPtr ),
		  m_PxVerbund( pxVerbundPtr)

	{
		
	}

	Settings::~Settings(void)
	{
	}

	const GeneralPtr Settings::getGeneral(void) const
	{
		return m_Gerneral;
	}

	const InformixPtr Settings::getInformix(void) const
	{
		return m_Informix;
	}

	const InformixPtr Settings::getInformixZDP(void) const
	{
		return m_InformixZDP;
	}

	const KSCServerPtr Settings::getKSCServer(void) const
	{
		return m_KscServer;
	}

	const SMTPPtr Settings::getSMTP(void) const
	{
		return m_Smtp;
	}

	const TCAccessPtr Settings::getTCAccess(void) const
	{
		return m_TcAccess;
	}

	const PxVerbundPtr Settings::getPxVerbund(void) const
	{
		return m_PxVerbund;
	}
}
}

//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Andre Egerer
 *  \date       23.04.2012
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CONFIG_DEFINITIONS_H
#define GUARD_LIBCSC_UTILS_CONFIG_DEFINITIONS_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <libbasarcmnutil.h>
#include <boost/shared_ptr.hpp>
#include <map>

//--------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------//
namespace libcsc_utils
{
namespace config
{
	//forward
	class General;
	class Informix;
	class KSCServer;
	class SMTP;
	class TCAccess;
	class PxVerbund;
	class Settings;
	class Pvhx;

	typedef boost::shared_ptr< General >	GeneralPtr;
	typedef boost::shared_ptr< Informix >	InformixPtr;
	typedef boost::shared_ptr< KSCServer >	KSCServerPtr;
	typedef boost::shared_ptr< SMTP >		SMTPPtr;
	typedef boost::shared_ptr< TCAccess >	TCAccessPtr;
	typedef boost::shared_ptr< PxVerbund >  PxVerbundPtr;
	typedef boost::shared_ptr< Settings >	SettingsPtr;
	typedef boost::shared_ptr< Pvhx >		PvhxPtr;
	
	enum SmtpRecipientsType {Information, Warnings, Errors};
	typedef std::map<SmtpRecipientsType, basar::VarString> SmtpTypeList;

}
}
#endif // GUARD_LIBCSC_UTILS_CONFIG_DEFINITIONS_H

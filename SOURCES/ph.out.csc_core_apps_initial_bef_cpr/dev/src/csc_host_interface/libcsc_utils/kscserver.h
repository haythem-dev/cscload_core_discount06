//-------------------------------------------------------------------------------------------------------------------//
/*! \file		kscserver.h
*  \brief		representation of config kscserver
*  \author		Andre Egerer
*  \date		17.04.2012
*/
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_CONFIG_KSCSERVER_H
#define GUARD_LIBCSC_UTILS_CONFIG_KSCSERVER_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc_utils
{
namespace config
{
	//-------------------------------------------------------------------------------------------------------------------//
	/*! \brief representation of config kscserver
	*/
	//-------------------------------------------------------------------------------------------------------------------//
	class KSCServer
	{
	public:
		KSCServer(void);
		KSCServer(basar::VarString const& kscHost, basar::Int32 port, basar::VarString const& terminalName, basar::VarString const& finishOrderType);

		virtual ~KSCServer(void);

		//Setter
		void					setKscHost				(basar::VarString const& value);
		void					setPort					(basar::Int32 value);
		void					setTerminalName			(basar::VarString const& value);
		void					setFinishOrderType		(basar::VarString const& value);

		//Getter
		basar::VarString	getKscHost				(void) const;
		basar::Int32		getPort					(void) const;
		basar::VarString	getTerminalName			(void) const;
		basar::VarString	getFinishOrderType		(void) const;

		bool				isSetKscHost			(void) const;
		bool				isSetPort				(void) const;
		bool				isSetTerminalName		(void) const;
		bool				isSetFinishOrderType	(void) const;

	private:
		basar::VarString m_KscHost;
		basar::Int32 m_Port;
		basar::VarString m_TerminalName;
		basar::VarString m_FinishOrderType;

		bool m_IsSetKscHost;
		bool m_IsSetPort;
		bool m_IsSetTerminalName;
		bool m_IsSetFinishOrderType;
	};
}
}
#endif // GUARD_LIBCSC_UTILS_CONFIG_KSCSERVER_H

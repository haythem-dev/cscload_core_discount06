#ifndef GUARD_LIBCSC_LOGGER_CONFIG_H
#define GUARD_LIBCSC_LOGGER_CONFIG_H

#include <libbasarcmnutil_bstring.h>
#include <libbasar_definitions.h>
#include <vector>

namespace libcsc
{
class LoggerConfig
{
public:
	// moduleName is the basic filename:
	// ${MARATHON_LOG_CONFIGDIR}/<moduleName>.cfg 
	// as default or
	// ${MARATHON_LOG_CONFIGDIR}/<moduleName>.<BRANCHNO>.cfg
	//
	// for example: 
	// ${MARATHON_LOG_CONFIGDIR}/kscserver.05.cfg
	LoggerConfig( const basar::VarString & moduleName );

	void doConfigure( const basar::Int16 branchno, const basar::Int32 orderno, const basar::Int32 customerno );

private:
	typedef std::vector<basar::VarString> StringCollection;

	void setEnvironment( const StringCollection & envStrings ) const;
	const basar::VarString getConfigFilename( const basar::Int16 branchno ) const;
	bool fileExists( const basar::VarString & fileName ) const;

	basar::VarString	m_ModuleName;
};

} // end namespace libcsc


#endif // GUARD_LIBCSC_LOGGER_CONFIG_H


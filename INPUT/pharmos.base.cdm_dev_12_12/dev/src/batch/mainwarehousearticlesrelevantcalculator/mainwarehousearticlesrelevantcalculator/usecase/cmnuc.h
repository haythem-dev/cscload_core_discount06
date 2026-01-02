#ifndef GUARD_CMNUC_H
#define GUARD_CMNUC_H

//------------------------------------------------------------------------------
// displays stage of precompiling, so not fulfilled precompile conditions can be detected
#ifdef WIN32
	#ifndef PRECOMPILEDHDR__MESSAGE__COMMONHEADER_H
		#pragma message("    compiling " __FILE__ " ...")
		#define PRECOMPILEDHDR__MESSAGE__COMMONHEADER_H
	#endif
#endif

#include <libbasar_definitions.h>
#include <libbasarappl.h>
#include <libbasarappl_systemeventmanager.h>
#include <libbasardbaspect.h>
#include <libbasardbsql.h>
#include <libbasarproperty.h>
#include <libbasarcmnutil.h>
#include <libbasarcmnutil_locale.h>
#include <libbasarcmnutil_remote.h>
#include <libbasarlogin.h>
//#include <typedefdm_definitions.h>
//#include "utils/log_macros.h"
//#include "libpurchaseucv2/loggerpool/loggerpool.h"
#include <libutil/exceptions/accessorexecutionexception.h>
//#include <utils/executeerrorenum2stringmapper.h>
//#include <utils/searchyiterator.h>
#include <string.h>
#include <libutil/misc/log_macro_definitions.h>
#include <libutil/misc/metaclassmacro_definitions.h>
#include <libutil/exception.h>
#include <libutil/irunnable.h>
#include <libutil/irunnableptr.h>
#include <libutil/dbtransaction.h>
#include <libutil/util.h>

#endif	// GUARD_CMNUC_H

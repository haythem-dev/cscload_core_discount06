#ifndef GUARD_LIBCSC_UNITTEST_CMNUT_H 
#define GUARD_LIBCSC_UNITTEST_CMNUT_H

// displays stage of precompiling, so not fulfilled precompile conditions can be detected
#ifdef WIN32
	#ifndef PRECOMPILEDHDR__MESSAGE__COMMONHEADER_H
		#pragma message("    compiling " __FILE__ " ...")
		#define PRECOMPILEDHDR__MESSAGE__COMMONHEADER_H
	#endif
#endif

#include <libbasardbsql_definitions.h>
#include <libbasardbsql_statementref.h>
#include <iostream>
#include <libbasarcmnutil_bstring.h>
#include <libbasardbaspect_accessorpropertytable_yiterator.h>
#include <UnitTest++.h>
//#include "unittestconnection.h"
#include <unittest/testutils.h>

#endif // GUARD_LIBCSC_UNITTEST_CMNUT_H


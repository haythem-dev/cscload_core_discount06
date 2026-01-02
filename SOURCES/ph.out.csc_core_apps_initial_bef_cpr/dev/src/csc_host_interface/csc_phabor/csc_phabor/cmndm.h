//---------------------------------------------------------------------------//
/*! \file cmndm.h
 *  \brief common header files include for domain modules
		\n contains a collection of stable(!) header files
		\n collection can be extended if necessary
 *  \author Dirk Kapusta
 *  \date 03.12.2008
 *  \version 00.00.00.01 first version
 */ //-----------------------------------------------------------------------//

#ifndef GUARD_RR_CMNDM_H
#define GUARD_RR_CMNDM_H

// displays stage of precompiling, so not fulfilled precompile conditions can be detected
#ifdef WIN32
	#ifndef PRECOMPILEDHDR__MESSAGE__COMMONHEADER_H
		#pragma message("    compiling " __FILE__ " ...")
		#define PRECOMPILEDHDR__MESSAGE__COMMONHEADER_H
	#endif
#endif

#include <libbasar_definitions.h>
#include <libbasardbaspect.h>
#include "loggerpool.h"
#include <libbasarproperty.h>
#include <libbasarcmnutil_datetime.h> 
#include <classinfo_macros.h>
#include <searchyiterator.h>


#endif // GUARD_RR_CMNDM_H


//-------------------------------------------------------------------------------------------------//
/*! \file   commonheader.h
 *  \brief  common header files include
 *  \author Frank Naumann
 *  \date   31.03.2010
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_COMMONHEADER_H
#define GUARD_COMMONHEADER_H

//-------------------------------------------------------------------------------------------------//
// displays stage of precompiling, so not fulfilled precompile conditions can be detected
#ifdef WIN32
  #ifndef PRECOMPILEDHDR__MESSAGE__COMMONHEADER_H
    #pragma message("    precompiling " __FILE__ " ...")
    #define PRECOMPILEDHDR__MESSAGE__COMMONHEADER_H
  #endif
#endif

//-------------------------------------------------------------------------------------------------//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <exception>

#include <libbasar_pkgversion.h>
#include <libbasar_definitions.h>
#include <libbasarcmnutil.h>
#include <libbasardbsql.h>
#include <libbasarproperty.h>
#include <libbasardbaspect.h>
#include <libbasarappl.h>
#include <libbasarlogin.h>

//-------------------------------------------------------------------------------------------------//

using basar::Int16;
using basar::Int32;
using basar::I18nString;
using basar::ConstString;
using basar::VarString;
using basar::Date;
using basar::db::aspect::AccessorPropertyTable_YIterator;
using basar::appl::EventReturnStruct;
using basar::appl::IEventSource;
using basar::appl::EventReturnType;
using basar::appl::NullEventSource;
using basar::appl::SystemEventManager;
using basar::db::aspect::SQLStringBuilder;
using basar::db::aspect::ConnectionRef;
using basar::db::aspect::AccessorPropertyTable_YIterator;
using basar::db::aspect::AccessorPropertyTableRef;
using basar::db::aspect::AccessorInstanceRef;
using basar::db::aspect::ExecuteResultInfo;

//-------------------------------------------------------------------------------------------------//

#endif	// GUARD_COMMONHEADER_H

//-------------------------------------------------------------------------------------------------//

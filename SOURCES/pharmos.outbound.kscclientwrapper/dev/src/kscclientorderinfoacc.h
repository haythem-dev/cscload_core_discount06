//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientorderinfoacc.h
 *  \brief  Accessor for infos about a KSC order.
 *  \author Stefan Will
 *  \date   08.02.2008
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_KSCCLIENTORDERINFOACC_H
#define GUARD_KSCCLIENTORDERINFOACC_H

#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

namespace acc_kscclientorderinfo
{
  // at least 1 SQL builder necessary for instantiating the accessor
  BEGIN_QUERY_BUILDER_DECLARATION(DummyBuilder)
  END_BUILDER_DECLARATION
}

#endif

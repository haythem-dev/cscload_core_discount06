//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientiteminfoacc.h
 *  \brief  Accessor for infos about KSC items.
 *  \author Stefan Will
 *  \date   08.02.2008
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_KSCCLIENTITEMINFOACC_H
#define GUARD_KSCCLIENTITEMINFOACC_H

#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

namespace acc_kscclientiteminfo
{
  // at least 1 SQL builder necessary for instantiating the accessor
  BEGIN_QUERY_BUILDER_DECLARATION(DummyBuilder)
  END_BUILDER_DECLARATION
}

#endif

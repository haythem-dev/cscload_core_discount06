//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientitemacc.h
 *  \brief  Accessor for KSC items.
 *  \author Stefan Will
 *  \date   04.02.2008
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_KSCCLIENTITEMACC_H
#define GUARD_KSCCLIENTITEMACC_H

#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

namespace acc_kscclientitem
{
  // at least 1 SQL builder necessary for instantiating the accessor
  BEGIN_QUERY_BUILDER_DECLARATION(DummyBuilder)
  END_BUILDER_DECLARATION
}

#endif

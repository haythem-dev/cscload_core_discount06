//-------------------------------------------------------------------------------------------------//
/*! \file   kscclientorderacc.h
 *  \brief  Accessor for KSC order.
 *  \author Klaus Hinz
 *  \date   21.01.2008
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_KSCCLIENTORDERACC_H
#define GUARD_KSCCLIENTORDERACC_H

#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

namespace acc_kscclientorder
{
  // at least 1 SQL builder necessary for instantiating the accessor
  BEGIN_QUERY_BUILDER_DECLARATION(DummyBuilder)
  END_BUILDER_DECLARATION
}

#endif

//----------------------------------------------------------------------------
/*! \file	  dkkulacc.h
 *  \brief  string builder declaration for VSAM.DKKUL accessor
 *  \author	Frank Naumann
 *  \date   23.03.2010
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DKKULACC_H
#define GUARD_DKKULACC_H

//----------------------------------------------------------------------------

#include <libbasardbaspect_macros.h>

//----------------------------------------------------------------------------
/*! \brief namespace for DKKUL-accessor.
 */
namespace acc_dkkul {

//---------------------------------------------------------------------------
/*! \brief class for selecting DKKUL by search criteria. final class.
 */
BEGIN_QUERY_BUILDER_DECLARATION(SelectDKKULByPattern)
END_BUILDER_DECLARATION

//----------------------------------------------------------------------------

} // namespace acc_dkkul

//----------------------------------------------------------------------------

#endif // GUARD_DKKULACC_H

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/*! \file	publicholidayacc.h
 *  \brief string builder declarations for publicholiday
 *  \author	Frank Naumann
 *  \date   23.03.2010
 */
//----------------------------------------------------------------------------

#ifndef GUARD_PUBLICHOLIDAYACCACC_H
#define GUARD_PUBLICHOLIDAYACCACC_H

//----------------------------------------------------------------------------

#include <libbasardbaspect_macros.h>

//----------------------------------------------------------------------------
/*! \brief namespace for accessor to relation feiertag.
 */
namespace acc_publicholiday {

//---------------------------------------------------------------------------
/*! \brief Class for selecting all existing public holidays record for a given branchno.
 */
BEGIN_QUERY_BUILDER_DECLARATION(SelectAllPublicHolidaysByBranchno)
END_BUILDER_DECLARATION

//----------------------------------------------------------------------------

} // namespace acc_publicholiday

//----------------------------------------------------------------------------

#endif // GUARD_PUBLICHOLIDAYACCACC_H

//----------------------------------------------------------------------------

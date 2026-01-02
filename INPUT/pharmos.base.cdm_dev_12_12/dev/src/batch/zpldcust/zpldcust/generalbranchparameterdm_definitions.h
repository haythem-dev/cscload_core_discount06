//----------------------------------------------------------------------------
/*! \file   generalbranchparameterdm_definitions.h
 *  \brief  global definitions for generalbranchparameter domain module
 *  \author Frank Naumann
 *  \date   25.03.2010
 */
//----------------------------------------------------------------------------

#ifndef GUARD_GENERALBRANCHPARAMETERDM_DEFINITIONS_H
#define GUARD_GENERALBRANCHPARAMETERDM_DEFINITIONS_H

#include <libbasarproperty_definitions.h>

//----------------------------------------------------------------------------

namespace lit {
namespace pdm_generalbranchparameter {

//----------------------------------------------------------------------------

CONST_PROPERTY_DESCRIPTION(BRANCHNO,              "branchno",              basar::INT16)   //!< property for feiertag.filialnr
CONST_PROPERTY_DESCRIPTION(MODE,                  "mode",                  basar::INT16)   //!< property for feiertag.modus
CONST_PROPERTY_DESCRIPTION(DAY,                   "day",                   basar::INT16)   //!< property for feiertag.tag
CONST_PROPERTY_DESCRIPTION(YEAR_FROM,             "yearfrom",              basar::INT16)   //!< property for feiertag.von_jahr
CONST_PROPERTY_DESCRIPTION(YEAR_TO,               "yearto",                basar::INT16)   //!< property for feiertag.bis_jahr
CONST_PROPERTY_DESCRIPTION(DAY_DESCRIPTION,       "day_description",       basar::STRING)  //!< property for feiertag.tag_name
CONST_PROPERTY_DESCRIPTION(PROPORTION,            "proportion",            basar::FLOAT64) //!< property for feiertag.anteil
CONST_PROPERTY_DESCRIPTION(PREDICTION_START_FLAG, "prediction_start_flag", basar::STRING)  //!< property for feiertag.prognosenja
CONST_PROPERTY_DESCRIPTION(PROPOSAL_START_FLAG,   "proposal_start_flag",   basar::STRING)  //!< property for feiertag.bestvorja

//----------------------------------------------------------------------------

} // namespace pdm_generalbranchparameter
} // namespace lit

//----------------------------------------------------------------------------

#endif // GUARD_GENERALBRANCHPARAMETERDM_DEFINITIONS_H

//----------------------------------------------------------------------------

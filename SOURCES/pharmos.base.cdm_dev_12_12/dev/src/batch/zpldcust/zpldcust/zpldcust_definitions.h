//----------------------------------------------------------------------------
/*! \file   zpldcust_definitions.h
 *  \brief  global definitions for zpldcust
 *  \author Frank Naumann
 *  \date   25.03.2010
 */
//----------------------------------------------------------------------------

#ifndef GUARD_ZPLDCUST_DEFINITIONS_H
#define GUARD_ZPLDCUST_DEFINITIONS_H

//----------------------------------------------------------------------------

#include <libbasarproperty_definitions.h>

//----------------------------------------------------------------------------
/*! \brief Global namespace for zpldcust.
 */
namespace zpldcust
{
ConstString UADM_HOST                   = "HOST";                   //!< parameter in useradministration to read server
ConstString UADM_DB                     = "DB";                     //!< parameter in useradministration to read database
ConstString UADM_HOST_CICS              = "CICS_HOST";              //!< parameter in useradministration to cics server
ConstString UADM_IP_CICS                = "CICS_IP";	              //!< parameter in useradministration to cics server
ConstString UADM_PORT_CICS              = "CICS_PORT";              //!< parameter in useradministration to cics server
ConstString UADM_START_TRANSACTION_CICS = "CICS_START_TRANSACTION"; //!< parameter in useradministration to cics server
ConstString UADM_DKKUL_GRP              = "DKKUL_GRP";              //!< parameter in useradministration for KUL_GRP restriction

ConstString PARAM_VERSION               = "-version";               //!< calling option to retrieve version ifo from executable.
ConstString PARAM_BRANCHNO              = "-branchno";              //!< calling option to set branchno.
ConstString PARAM_MODE                  = "-mode";                  //!< calling option to set mode.

ConstString MODE_FULL                   = "full";                   //!< mode to load all customers of this branch (Urladung).
ConstString MODE_LAST                   = "last";                   //!< mode to load changes since last work day.

enum MULTIPLECUSTFLAG
{
  MULTIPLECUSTFLAG_NEW        = 0, //!< flag 0: new customer status after creation
  MULTIPLECUSTFLAG_UPDATED    = 1, //!< flag 1: customer data was updated in base branch despite differences to other branches
  MULTIPLECUSTFLAG_DIFFERENCE = 2  //!< flag 2: differences in customer data between branches
};

//----------------------------------------------------------------------------

}	// namespace zpldcust

//----------------------------------------------------------------------------

//! namespace containing all database - fieldnames used for matching / accessing properties
namespace lit {
namespace zpldcust {

CONST_PROPERTY_DESCRIPTION(MODE,             "mode",             basar::STRING) //!< property containing the mode of the program (either full or last).

CONST_PROPERTY_DESCRIPTION(CUSTOMERNO,       "customerno",       basar::INT32)  //!< property for db field ccustomermaindata.customerno.
CONST_PROPERTY_DESCRIPTION(CUSTOMER_NAME,    "customer_name",    basar::STRING) //!< property for db field ccustomermaindata.customer_name (length 30).
CONST_PROPERTY_DESCRIPTION(POSTAL_CODE,      "postal_code",      basar::STRING) //!< property for db field ccustomermaindata.postal_code (length 8).
CONST_PROPERTY_DESCRIPTION(CITY,             "city",             basar::STRING) //!< property for db field ccustomermaindata.city (length 30).
CONST_PROPERTY_DESCRIPTION(BRANCHNO,         "branchno",         basar::INT16)  //!< property for db field ccustomermaindata.branchno.
CONST_PROPERTY_DESCRIPTION(MULTIPLECUSTFLAG, "multiplecustflag", basar::INT16)  //!< property for db field ccustomermaindata.multiplecustflag.


CONST_PROPERTY_DESCRIPTION(KUL_FIL1,       "kul_fil1",       basar::INT16)  //!< decimal(2)
CONST_PROPERTY_DESCRIPTION(KUL_IDF,        "kul_idf",        basar::INT32)  //!< decimal(7)
CONST_PROPERTY_DESCRIPTION(KUL_FIL2,       "kul_fil2",       basar::INT16)  //!< decimal(2)
CONST_PROPERTY_DESCRIPTION(KUL_VFIL,       "kul_vfil",       basar::INT16)  //!< decimal(2)
CONST_PROPERTY_DESCRIPTION(KUL_KUBZ,       "kul_kubz",       basar::STRING) //!< char(30)
CONST_PROPERTY_DESCRIPTION(KUL_FIL3,       "kul_fil3",       basar::INT16)  //!< decimal(2)
CONST_PROPERTY_DESCRIPTION(KUL_NAM1,       "kul_nam1",       basar::STRING) //!< char(30)
CONST_PROPERTY_DESCRIPTION(KUL_ORT,        "kul_ort",        basar::STRING) //!< char(30)
CONST_PROPERTY_DESCRIPTION(KUL_PLZ,        "kul_plz",        basar::INT32)  //!< decimal(5)
CONST_PROPERTY_DESCRIPTION(KUL_AEDAT,      "kul_aedat",      basar::INT32)  //!< decimal(6) YYMMDD
CONST_PROPERTY_DESCRIPTION(KUL_KUSEIT,     "kul_kuseit",     basar::INT32)  //!< decimal(6) YYMMDD
CONST_PROPERTY_DESCRIPTION(KUL_GRP,        "kul_grp",        basar::INT16)  //!< decimal(2)
CONST_PROPERTY_DESCRIPTION(KUL_GRP_SEARCH, "kul_grp_search", basar::STRING) //!< char


//----------------------------------------------------------------------------

} // namespace zpldcust
} // namespace lit

/*! \brief Macro allows to clear and release a PropertyTable that contains some data.
 *         If this is not done an ASSERT show up during termination of the program.
 */
#define FREE_ACCESSOR(accessorName) \
  if(false == accessorName.getPropertyTable().isNull()) \
  { \
    accessorName.getPropertyTable().clear(); \
    accessorName.getPropertyTable().reset(); \
  } \
  accessorName.reset();

//----------------------------------------------------------------------------

#endif // GUARD_ZPLDCUST_DEFINITIONS_H

//----------------------------------------------------------------------------

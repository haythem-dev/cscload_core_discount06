/*
 * requestsqlmapper.cpp
 *
 *  Created on: 09.02.2016
 *  Author: sebastian.barth
 */

#include "requestsqlmapper.h"
#include <sstream>

namespace libcsc {
namespace procurementpermission {
namespace repo {

const basar::VarString RequestSqlMapper::getSelectSQL(basar::VarString const& importIfaCountryCode, const basar::Long32 articleNo)
{
    std::stringstream ss;

    ss << "select count('x')::int from imexblock"
       << " where country_ifacode = '" << importIfaCountryCode << "'"
       << " and articleno = " << articleNo
       << " and imex_mode = 1;";

    return ss.str().c_str();
}

} // end namespace repo
} // end namespace procurementpermission
} // end namespace libcsc

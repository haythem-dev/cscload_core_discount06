#ifndef GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FORMATS_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FORMATS_PTR_HRESERVATIONCONFIG_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>

namespace libcsc {
namespace parameter {

class ICSCOrderImportCSVFormats;
typedef boost::shared_ptr<ICSCOrderImportCSVFormats> ICSCOrderImportCSVFormatsPtr;

typedef std::vector<ICSCOrderImportCSVFormatsPtr> ICSCOrderImportCSVFormatsCollection;

typedef boost::shared_ptr<ICSCOrderImportCSVFormatsCollection> ICSCOrderImportCSVFormatsCollectionPtr;

typedef std::map<basar::VarString, ICSCOrderImportCSVFormatsCollectionPtr> ICSCOrderImportCSVFormatsCollectionMap;

typedef boost::shared_ptr<ICSCOrderImportCSVFormatsCollectionMap> ICSCOrderImportCSVFormatsCollectionMapPtr;

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FORMATS_PTR_H

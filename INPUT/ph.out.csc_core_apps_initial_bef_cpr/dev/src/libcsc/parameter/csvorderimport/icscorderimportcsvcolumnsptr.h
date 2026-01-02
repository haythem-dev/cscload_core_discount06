#ifndef GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_CSV_COLUMNS_PTR_H
#define GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_CSV_COLUMNS_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace libcsc {
namespace parameter {

class ICSCOrderImportCSVColumns;
typedef boost::shared_ptr<ICSCOrderImportCSVColumns> ICSCOrderImportCSVColumnsPtr;

typedef std::vector<ICSCOrderImportCSVColumnsPtr> ICSCOrderImportCSVColumnsCollection;

typedef boost::shared_ptr<ICSCOrderImportCSVColumnsCollection> ICSCOrderImportCSVColumnsCollectionPtr;

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_CSV_COLUMNS_PTR_H

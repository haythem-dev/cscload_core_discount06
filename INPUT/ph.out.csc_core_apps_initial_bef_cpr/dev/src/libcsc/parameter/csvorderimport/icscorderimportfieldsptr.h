#ifndef GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FIELDS_PTR_H
#define GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FIELDS_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace libcsc {
namespace parameter {

class ICSCOrderImportFields;
typedef boost::shared_ptr<ICSCOrderImportFields> ICSCOrderImportFieldsPtr;

typedef std::vector<ICSCOrderImportFieldsPtr> ICSCOrderImportFieldsCollection;

typedef boost::shared_ptr<ICSCOrderImportFieldsCollection> ICSCOrderImportFieldsCollectionPtr;

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FIELDS_PTR_H

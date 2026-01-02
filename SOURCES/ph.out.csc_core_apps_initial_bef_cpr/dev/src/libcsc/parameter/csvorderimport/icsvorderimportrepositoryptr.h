#ifndef GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_REPOSITORY_PTR_H
#define GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace parameter {

class ICSVOrderImportRepository;
typedef boost::shared_ptr<ICSVOrderImportRepository> ICSVOrderImportRepositoryPtr;

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_REPOSITORY_PTR_H

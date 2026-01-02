#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_REPOSITORY_PTR_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace parameter {

class CSVOrderImportRepository;
typedef boost::shared_ptr<CSVOrderImportRepository> CSVOrderImportRepositoryPtr;

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_REPOSITORY_PTR_H

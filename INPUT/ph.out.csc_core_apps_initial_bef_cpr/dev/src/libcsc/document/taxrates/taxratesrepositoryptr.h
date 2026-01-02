#ifndef GUARD_LIBCSC_DOCUMENT_TAXRATES_REPOSITORY_PTR_H
#define GUARD_LIBCSC_DOCUMENT_TAXRATES_REPOSITORY_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace document {

class TaxratesRepository;
typedef boost::shared_ptr<TaxratesRepository> TaxratesRepositoryPtr;

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_TAXRATES_REPOSITORY_PTR_H

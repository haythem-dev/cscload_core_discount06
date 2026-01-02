#ifndef GUARD_LIBCSC_DOCUMENT_COMPONENT_MANAGER_PTR_H
#define GUARD_LIBCSC_DOCUMENT_COMPONENT_MANAGER_PTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace document {

class DocumentComponentManager;
typedef boost::shared_ptr<libcsc::document::DocumentComponentManager> DocumentComponentManagerPtr;

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_COMPONENT_MANAGER_PTR_H

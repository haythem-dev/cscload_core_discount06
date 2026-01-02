#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_IBTLINKPTR_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_IBTLINKPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace document {

class DeliveryAdviceLineIbtLink;
typedef boost::shared_ptr<DeliveryAdviceLineIbtLink> DeliveryAdviceLineIbtLinkPtr;

typedef std::list<DeliveryAdviceLineIbtLinkPtr> DeliveryAdviceLineIbtLinkCollection;

typedef boost::shared_ptr<DeliveryAdviceLineIbtLinkCollection> DeliveryAdviceLineIbtLinkCollectionPtr;

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINE_IBTLINKPTR_H

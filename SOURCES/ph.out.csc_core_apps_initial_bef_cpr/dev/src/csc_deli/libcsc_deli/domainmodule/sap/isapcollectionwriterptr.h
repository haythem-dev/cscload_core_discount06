#ifndef GUARD_LIBCSC_DELI_DOMMOD_SAP_ISAPCOLLECTIONWRITERPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_SAP_ISAPCOLLECTIONWRITERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace sap
        {
            class ISAPCollectionWriter;
            typedef boost::shared_ptr< ISAPCollectionWriter > ISAPCollectionWriterPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_SAP_ISAPCOLLECTIONWRITERPTR_H

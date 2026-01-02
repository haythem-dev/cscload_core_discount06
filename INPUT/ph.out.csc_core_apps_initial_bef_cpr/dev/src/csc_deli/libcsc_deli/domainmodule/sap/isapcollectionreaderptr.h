#ifndef GUARD_LIBCSC_DELI_DOMMOD_SAP_ISAPCOLLECTIONREADERPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_SAP_ISAPCOLLECTIONREADERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace sap
        {
            class ISAPCollectionReader;
            typedef boost::shared_ptr< ISAPCollectionReader > ISAPCollectionReaderPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_SAP_ISAPCOLLECTIONREADERPTR_H

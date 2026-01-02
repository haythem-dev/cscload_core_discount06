#ifndef GUARD_LIBCSC_DOCUMENT_TAXRATES_REPOSITORY_H
#define GUARD_LIBCSC_DOCUMENT_TAXRATES_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <parameter/ibranchparametergetterptr.h>
#include <document/taxrates/taxratescollectionptr.h>

namespace basar {
namespace db {
namespace sql {
    class ResultsetRef;
}
}
}

namespace libcsc {
namespace document {

class TaxratesRepository
{
public:
    TaxratesRepository();
    virtual ~TaxratesRepository();

    virtual void injectFindAccessor(persistence::IAccessorPtr accessor);

    virtual TaxratesCollectionPtr getTaxrates();

private:
    persistence::IAccessorPtr m_SelectTaxratesAccessor;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_TAXRATES_REPOSITORY_H

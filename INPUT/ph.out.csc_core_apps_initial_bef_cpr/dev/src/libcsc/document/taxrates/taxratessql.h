#ifndef GUARD_LIBCSC_DOCUMENT_TAXRATESSQL_H
#define GUARD_LIBCSC_DOCUMENT_TAXRATESSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace document {

class TaxratesSql
{
public:
    ~TaxratesSql();

    static const basar::VarString getTaxratesQuery();

private:
    TaxratesSql();
    TaxratesSql& operator=(const TaxratesSql&);
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_TAXRATESSQL_H

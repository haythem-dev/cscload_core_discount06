#ifndef GUARD_LIBCSC_CSCORDERTYPE_COLLECTION_H
#define GUARD_LIBCSC_CSCORDERTYPE_COLLECTION_H

#include <libbasar_definitions.h>
#include <datatypes/int16.h>
#include <datatypes/boolean.h>
#include <datatypes/varstring.h>
#include <base/istreamable.h>

namespace libcsc
{
namespace cscordertype
{
typedef std::vector<libcsc::cscordertype::ICSCOrderTypePtr> CSCOrderTypeCollection;

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_COLLECTION_H

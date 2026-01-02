#ifndef GUARD_LIBCSC_DISCOUNT_LOG_POSITION_COLLECTION_H
#define GUARD_LIBCSC_DISCOUNT_LOG_POSITION_COLLECTION_H

#include <list>
#include <boost/shared_ptr.hpp>
#include <discount/logger/discountlogger/discountlogpositionptr.h>

namespace libcsc
{
namespace discount
{
typedef std::list<libcsc::discount::DiscountLogPositionPtr> DiscountLogPositionCollection;
typedef boost::shared_ptr<libcsc::discount::DiscountLogPositionCollection> DiscountLogPositionCollectionPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_LOG_POSITION_COLLECTION_H

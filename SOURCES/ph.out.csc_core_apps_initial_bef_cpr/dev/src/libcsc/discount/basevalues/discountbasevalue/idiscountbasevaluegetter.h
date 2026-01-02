#ifndef GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_GETTER_H
#define GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_GETTER_H

#include "discount/basevalues/discountbasevalue/discountbasevalueptr.h"	
#include <libbasar_definitions.h>
#include <list>

namespace libcsc
{
namespace discount
{
typedef std::list<libcsc::discount::DiscountBaseValuePtr> DiscountBaseValueList;
typedef DiscountBaseValueList FilteredDiscountBaseValueList;

// TODO: weitere Container mit Filterung nach pzn, kundennr, etc

class IDiscountBaseValueGetter
{
public:
	virtual ~IDiscountBaseValueGetter() {}

	virtual const DiscountBaseValueList & getCollection() const = 0;
	virtual const FilteredDiscountBaseValueList & getCollectionByArticleNo() const = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_DISCOUNT_BASE_VALUE_GETTER_H

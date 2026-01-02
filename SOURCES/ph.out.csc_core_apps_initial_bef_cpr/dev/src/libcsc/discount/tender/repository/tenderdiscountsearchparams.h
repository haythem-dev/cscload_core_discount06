#ifndef GUARD_LIBCSC_TENDER_DISCOUNT_SEARCH_PARAMS_H
#define GUARD_LIBCSC_TENDER_DISCOUNT_SEARCH_PARAMS_H

#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc
{
namespace discount
{
struct TenderDiscountSearchParams
{
	libcsc::Int32		customerNo;
	libcsc::Int32	    articleNo;
	bool				activeOnly;

	TenderDiscountSearchParams( const basar::Int32 _customerNo, const basar::Int32 _articleNo, const bool _activeOnly = true )
	: customerNo( _customerNo ), articleNo( _articleNo ), activeOnly( _activeOnly )
	{
	}
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_DISCOUNT_SEARCH_PARAMS_H

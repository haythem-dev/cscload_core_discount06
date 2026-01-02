#include "orderpositiondiscountmodemapper.h"

namespace libcsc
{
namespace discount
{
std::ostream & OrderPositionDiscountModeMapper::toStream( std::ostream & str, const OrderPositionDiscountModeEnum type )
{
	switch( type )
	{
		case DM_UNSET: str << "DM_UNSET"; break;
		case DM_FIXED_PRICE_MODE: str << "DM_FIXED_PRICE_MODE"; break;
		case DM_RETAIL: str << "DM_RETAIL"; break;
		case DM_WHOLESALE_PERCENT_MODE: str << "DM_WHOLESALE_PERCENT_MODE"; break;
		case DM_WHOLESALE_INDUSTRY_PERCENT_MODE: str << "DM_WHOLESALE_INDUSTRY_PERCENT_MODE"; break;
		case DM_WHOLESALE_REBATE_IN_KIND_MODE: str << "DM_WHOLESALE_REBATE_IN_KIND_MODE"; break;
		case DM_WHOLESALE_INDUSTRY_REBATE_IN_KIND_MODE: str << "DM_WHOLESALE_INDUSTRY_REBATE_IN_KIND_MODE"; break;
		case DM_SURCHARGE_EXF_MODE: str << "DM_SURCHARGE_EXF_MODE"; break;

		default: str << "-UNKNOWN-"; break;
	}

	return str;
}

} // end namespace discount
} // end namespace libcsc


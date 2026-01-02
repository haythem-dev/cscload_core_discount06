#include "discount/resultprocessor/repositoryresultprocessorbase.h"

namespace libcsc
{
namespace discount
{
RepositoryResultProcessorBase::RepositoryResultProcessorBase()
{
}

RepositoryResultProcessorBase::~RepositoryResultProcessorBase()
{
}

OrderPositionDiscountModeEnum RepositoryResultProcessorBase::getDiscountMode( 
	const DiscountCalculatorTypeEnum type,
	const bool isRebateInKind
		) const
{
	switch( type )
	{
		case CT_FIXED_PRICE_TYPE: return DM_FIXED_PRICE_MODE; break;
		case CT_RETAIL_TYPE: return DM_RETAIL; break;

		// fall through
		case CT_WH_CUSTOMER_ARTICLE_TYPE:
		case CT_WH_CUSTOMER_ARTICLE_GROUP_TYPE:
		case CT_WH_CUSTOMER_MANUFACTURER_TYPE:
		case CT_WH_CUSTOMER_MANUFACTURER_GROUP_TYPE:
		case CT_WH_CUSTOMER_GROUP_ARTICLE_TYPE:
		case CT_WH_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE:
		case CT_WH_CUSTOMER_GROUP_MANUFACTURER_TYPE:
		case CT_WH_CUSTOMER_GROUP_MANUFACTURER_GROUP_TYPE:
		case CT_WH_ALL_CUSTOMER_ARTICLE_TYPE:
		case CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE:
		case CT_WH_ALL_CUSTOMER_MANUFACTURER_TYPE:
		case CT_WH_ALL_CUSTOMER_MANUFACTURER_GROUP_TYPE:
		{
			if( isRebateInKind )
			{
				return DM_WHOLESALE_REBATE_IN_KIND_MODE;
			}
			else
			{
				return DM_WHOLESALE_PERCENT_MODE;
			}
			break;
		}

		// fall through
		case CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE:
		case CT_WH_INDUSTRY_CUSTOMER_ARTICLE_GROUP_TYPE:
		case CT_WH_INDUSTRY_CUSTOMER_MANUFACTURER_TYPE:
		case CT_WH_INDUSTRY_CUSTOMER_MANUFACTURER_GROUP_TYPE:
		case CT_WH_INDUSTRY_CUSTOMER_GROUP_ARTICLE_TYPE:
		case CT_WH_INDUSTRY_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE:
		case CT_WH_INDUSTRY_CUSTOMER_GROUP_MANUFACTURER_TYPE:
		case CT_WH_INDUSTRY_CUSTOMER_GROUP_MANUFACTURER_GROUP_TYPE:
		case CT_WH_INDUSTRY_ALL_CUSTOMER_ARTICLE_TYPE:
		case CT_WH_INDUSTRY_ALL_CUSTOMER_ARTICLE_GROUP_TYPE:
		case CT_WH_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_TYPE:
		case CT_WH_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_GROUP_TYPE:
		{
			if( isRebateInKind )
			{
				return DM_WHOLESALE_INDUSTRY_REBATE_IN_KIND_MODE;
			}
			else
			{
				return DM_WHOLESALE_INDUSTRY_PERCENT_MODE;
			}
			break;
		}

		// DEPricing
		case CT_FIXED_PRICE_CONCEPT_DEAP_MODE: return DM_FIXED_PRICE_CONCEPT_DEAP_MODE; break;
		case CT_FIXED_PRICE_CONCEPT_MVDA_MODE: return DM_FIXED_PRICE_CONCEPT_MVDA_MODE; break;
		case CT_SURCHARGE_EXF_MODE: return DM_SURCHARGE_EXF_MODE; break;
		default: break;
	}

	return DM_UNSET;
}

bool RepositoryResultProcessorBase::isPositionDiscountCalculatorType(
	const DiscountCalculatorTypeEnum calcType 
		) const
{
	switch( calcType )
	{
		// fall through
		case CT_FIXED_PRICE_TYPE:
		case CT_RETAIL_TYPE:
		case CT_WH_ALL_CUSTOMER_ARTICLE_TYPE:
		case CT_WH_CUSTOMER_ARTICLE_TYPE:
		case CT_WH_CUSTOMER_GROUP_ARTICLE_TYPE:
		case CT_WH_INDUSTRY_ALL_CUSTOMER_ARTICLE_TYPE:
		case CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE:
		case CT_WH_INDUSTRY_CUSTOMER_GROUP_ARTICLE_TYPE:
		{
			return true;
			break;
		}

		default: break;
	}

	return false;
}


} // end namespace discount
} // end namespace libcsc

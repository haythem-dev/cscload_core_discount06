#include "discount/calculator/commands/dediscountcalculatorcommand.h"
#include <discount/calculator/commands/discountcalculatorcommandbase.h>

#include <discount/resultprocessor/iresultprocessor.h>

#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include <discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h>
#include "discount/basevalues/discountbasevalue/discountbasevalueptr.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"

#include <logger/loggerpool.h>

namespace libcsc {
namespace discount {

	DEDiscountCalculatorCommand::DEDiscountCalculatorCommand() : DiscountCalculatorCommandBase(CT_ROOT, CT_FIXED_PRICE_TYPE) // DEPricing TODO
	{
	}

	DEDiscountCalculatorCommand::~DEDiscountCalculatorCommand()
	{
	}

	const DiscountCalculatorResult& DEDiscountCalculatorCommand::calculate() const
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DEDiscountCalculatorCommand::calculate()");

		DiscountBaseValueList discountWorkingList;

		createDiscountWorkingList( discountWorkingList ); // --> implicit this DiscountBaseValueList discountWorkingList = getDiscountBaseValueGetter()->getCollection();
		
		for ( size_t index = 0; index < m_filters.size(); ++index )
		{
			m_filters[index]->execute(discountWorkingList, getOrderBaseValueGetter());
		}
	
		if (discountWorkingList.size() >= 1)
		{
			DiscountBaseValuePtr discount = *discountWorkingList.begin();
			DiscountCalculatorResult result;

			setResultBaseValues(result);

			DiscountResult& dr(result.getDiscountResult(getOrderBaseValueGetter()->getPositionNo()));

			setDiscountSourceValues(dr.source, discount, ART_CLASS_NONE);

			switch (discount->getDiscountType())
			{
				case DISC_TYPE_OPEN_CONCEPT:
				case DISC_TYPE_OPEN_CONCEPT_HZ:
				{
					dr.discountedArticlePrice = discount->getFixedPrice(); // evtl ändern auf GEP + 70ct bei Taxpflichtige RX Artikel      (IsRezeptPflichtig() && !Sortiment_1()) 
					dr.discountedArticlePriceOrigin = CT_FIXED_PRICE_CONCEPT_DEAP_MODE;
					setDiscountCalculatorType(CT_FIXED_PRICE_CONCEPT_DEAP_MODE);
					break;
				}
				case DISC_TYPE_CLOSED_CONCEPT:
				case DISC_TYPE_CLOSED_CONCEPT_HZ:
				{
					dr.discountedArticlePrice = discount->getFixedPrice(); // evtl ändern auf GEP + 70ct bei Taxpflichtige RX Artikel
					dr.discountedArticlePriceOrigin = CT_FIXED_PRICE_CONCEPT_MVDA_MODE;
					setDiscountCalculatorType(CT_FIXED_PRICE_CONCEPT_MVDA_MODE);
					break;
				}
				case DISC_TYPE_SURCHARGE_EXF:
				{
					dr.discountPercent = discount->getSurchargePct();
					dr.discountPercentOrigin = CT_SURCHARGE_EXF_MODE;
					setDiscountCalculatorType(CT_SURCHARGE_EXF_MODE);
					break;
				}
				default:
				{
					dr.discountedArticlePrice = discount->getFixedPrice(); // evtl ändern auf GEP + 70ct bei Taxpflichtige RX Artikel
					dr.discountedArticlePriceOrigin = CT_FIXED_PRICE_TYPE;
					setDiscountCalculatorType(CT_FIXED_PRICE_TYPE);
					break;
				}
			}
			setResult(result);
		}
		return getResult();
	}

	void DEDiscountCalculatorCommand::injectFilters(DiscountFilterList filters)
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DEDiscountCalculatorCommand::injectFilters()");

		m_filters = filters;
	}

	void DEDiscountCalculatorCommand::createDiscountWorkingList(DiscountBaseValueList& discountWorkingList) const
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DEDiscountCalculatorCommand::createDiscountWorkingList()");

		discountWorkingList.clear();

		DiscountBaseValueList::const_iterator it = getDiscountBaseValueGetter()->getCollection().begin();

		while (it != getDiscountBaseValueGetter()->getCollection().end())
		{
			if (areBaseValuesMatching(*it)) // only when baseqty is matching
			{
				discountWorkingList.push_back(*it);
			}
			++it;
		}
	}

	void DEDiscountCalculatorCommand::processResult() const
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DEDiscountCalculatorCommand::processResult()");

		DiscountCalculatorCommandBase::processResult(); // DEPricing TODO check m_Type of this calculator before processResult()!!!
	}
} // end namespace discount
} // end namespace libcsc

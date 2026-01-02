//-------------------------------------------------------------------------------------------------//
/*! \file	pricelist2pharmacygroupdm.cpp
*   \brief	domain module for mapping price list to pharmacy group
*   \author NTT DATA
*   \date	13.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#include "pricelist2pharmacygroupdm.h"
#include "infrastructure/accessor/pricelist2pharmacygroup/pricelist2pharmacygroupacc.h"
#include "libutil/exception.h"

namespace importpricelist
{
	namespace domMod
	{
		namespace pricelist2pharmacygroup
		{
			PriceList2PharmacyGroupDM::PriceList2PharmacyGroupDM(const log4cplus::Logger& logger)
				: m_Logger(logger)
			{
				METHODNAME_DEF(PriceList2PharmacyGroupDM, PriceList2PharmacyGroupDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			PriceList2PharmacyGroupDM::~PriceList2PharmacyGroupDM()
			{
				METHODNAME_DEF(PriceList2PharmacyGroupDM, ~PriceList2PharmacyGroupDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			void PriceList2PharmacyGroupDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
			{
				m_DbConnection = conn->getCurrentConnection();
			}

			bool PriceList2PharmacyGroupDM::selectPharmacyGroupByPriceListId(const basar::Int32 priceListId, PriceList2PharmacyGroup& priceList2PharmacyGroup)
			{
				METHODNAME_DEF(PriceList2PharmacyGroupDM, selectPharmacyGroupByPriceListId)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceList2PharmacyGroup().insert(basar::FOR_UNKNOWN);
					basar::Decimal decPriceListId(priceListId);

					whereCondition.setDecimal(PRL2PHGRP_PRICELISTID.getName(), decPriceListId);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricelist2pharmacygroup::lit::SelectPharmacyGroupByPriceListId, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricelist2pharmacygroup::lit::SelectPharmacyGroupByPriceListId, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricelist2pharmacygroup::lit::SelectPharmacyGroupByPriceListId, executeResultInfo)
				}
				else
				{
					basar::db::aspect::AccessorPropertyTableRef selectedData = getPriceList2PharmacyGroup();
					basar::db::aspect::AccessorPropertyTable_YIterator dataIterator = selectedData.begin();
					if (!dataIterator.isEnd())
					{
						priceList2PharmacyGroup.priceListId = dataIterator.getDecimal(PRL2PHGRP_PRICELISTID.getName()).toInt32();
						priceList2PharmacyGroup.priceListName = dataIterator.getString(PRL2PHGRP_PRICELISTNAME.getName());
						priceList2PharmacyGroup.pharmacyGroupId = dataIterator.getString(PRL2PHGRP_PHARMACYGROUPID.getName()).stoi();
						priceList2PharmacyGroup.discountType = dataIterator.getInt16(PRL2PHGRP_DISCOUNT_TYPE.getName());
						priceList2PharmacyGroup.discountSpec = dataIterator.getInt16(PRL2PHGRP_DISCOUNT_SPEC.getName());

						// close data iterator so that update / insert statements are possible afterwards
						dataIterator.clear();

						return true;
					}
				}

				return false;
			}

			basar::db::aspect::AccessorPropertyTableRef PriceList2PharmacyGroupDM::getPriceList2PharmacyGroup()
			{
				METHODNAME_DEF(PriceDataDM, getPriceData)
				BLOG_TRACE_METHOD(m_Logger, fun);

				return getAccessor()->getPropertyTable();
			}

			//--------------------------------------------------------------------------------------------------------------------------------------------------------
			// PriceList2PharmacyGroup containing de pricing data for interface usage
			//--------------------------------------------------------------------------------------------------------------------------------------------------------

			PriceList2PharmacyGroup::PriceList2PharmacyGroup()
				: priceListId ( 0 )
				, priceListName ( "" )
				, pharmacyGroupId(0)
				, discountType(0)
				, discountSpec(0)
			{

			}

			PriceList2PharmacyGroup::PriceList2PharmacyGroup(const PriceList2PharmacyGroup& other)
			{
				*this = other;
			}

			PriceList2PharmacyGroup& PriceList2PharmacyGroup::operator=(const PriceList2PharmacyGroup& other)
			{
				priceListId = other.priceListId;
				priceListName = other.priceListName;
				pharmacyGroupId = other.pharmacyGroupId;
				discountType = other.discountType;
				discountSpec = other.discountSpec;
				return *this;
			}
		}
	}
}

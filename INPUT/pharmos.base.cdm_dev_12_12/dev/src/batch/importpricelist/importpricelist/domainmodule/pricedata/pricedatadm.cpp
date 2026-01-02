//-------------------------------------------------------------------------------------------------//
/*! \file	pricedatadm.cpp
*   \brief	domain module für price data (cdiscount)
*   \author NTT Data
*   \date	27.08.2021
*/
//-------------------------------------------------------------------------------------------------//

#include "pricedatadm.h"
#include "infrastructure/accessor/pricedata/pricedataacc.h"
#include "libutil/exception.h"

namespace importpricelist
{
	namespace domMod
	{
		namespace pricedata
		{
			PriceDataDM::PriceDataDM(const log4cplus::Logger& logger)
				:m_Logger(logger)
			{
				METHODNAME_DEF(PriceDataDM, PriceDataDM)
				BLOG_TRACE_METHOD(m_Logger, fun);
			}

			PriceDataDM::~PriceDataDM()
			{
				METHODNAME_DEF(PriceDataDM, ~PriceDataDM)
				BLOG_TRACE_METHOD(m_Logger, fun);

				if (!m_PrepStmtInsert.isNull())
				{
					if (m_PrepStmtInsert.isOpen())
						m_PrepStmtInsert.close();

					m_PrepStmtInsert.reset();
				}
			}

			void PriceDataDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
			{
				m_DbConnection = conn->getCurrentConnection();
				m_DbSqlConnection = conn->getCurrentConnection().getSqlConnection();
			}

			basar::db::aspect::ExecuteResultInfo PriceDataDM::selectPriceDataByPharmacyGroup(const basar::Int32 pharmacyGroupId, const basar::Int32 dateFrom)
			{
				METHODNAME_DEF(PriceDataDM, selectPriceDataByPharmacyGroupId)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceData().insert(basar::FOR_UNKNOWN);

					whereCondition.setString(PRICEDATA_PHARMACYGROUPID.getName(), PriceData::convertInt32ToVarString(pharmacyGroupId, 3));
					whereCondition.setInt32(PRICEDATA_DATEFROM.getName(), dateFrom);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricedata::lit::SelectPriceDataByPharmacyGroup, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricedata::lit::SelectPriceDataByPharmacyGroup, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricedata::lit::SelectPriceDataByPharmacyGroup, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceDataDM::selectArticlesWithValidPrices(const basar::Int32 pharmacyGroupId, const basar::Int32 dateFrom)
			{
				METHODNAME_DEF(PriceDataDM, selectArticlesWithValidPrices)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceData().insert(basar::FOR_UNKNOWN);

					whereCondition.setString(PRICEDATA_PHARMACYGROUPID.getName(), PriceData::convertInt32ToVarString(pharmacyGroupId, 3));
					whereCondition.setInt32(PRICEDATA_DATEFROM.getName(), dateFrom);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricedata::lit::SelectArticlesWithValidPrices, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricedata::lit::SelectArticlesWithValidPrices, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricedata::lit::SelectArticlesWithValidPrices, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceDataDM::selectPriceDataNotInZArtikel(const basar::Int32 pharmacyGroupId, const basar::Int32 dateFrom)
			{
				METHODNAME_DEF(PriceDataDM, selectPriceDataNotInZArtikel)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;
				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceData().insert(basar::FOR_UNKNOWN);

					whereCondition.setString(PRICEDATA_PHARMACYGROUPID.getName(), PriceData::convertInt32ToVarString(pharmacyGroupId, 3));
					whereCondition.setInt32(PRICEDATA_DATEFROM.getName(), dateFrom);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricedata::lit::SelectPriceDataNotInZArtikel, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricedata::lit::SelectPriceDataNotInZArtikel, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricedata::lit::SelectPriceDataNotInZArtikel, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::sql::ExecuteReturnInfo PriceDataDM::insertPriceData(const PriceData& priceData)
			{
				METHODNAME_DEF(PriceDataDM, insertPriceData)
				BLOG_TRACE_METHOD(m_Logger, fun);

				if (m_PrepStmtInsert.isNull() || !m_PrepStmtInsert.isOpen())
				{
					basar::VarString stmtSQL;
					stmtSQL.append("INSERT INTO cdiscount ");
					stmtSQL.append("( ");
					stmtSQL.append("   articleno");
					stmtSQL.append("  ,pharmacygroupid");
					stmtSQL.append("  ,datefrom");
					stmtSQL.append("  ,dateto");
					stmtSQL.append("  ,baseqty");
					stmtSQL.append("  ,fixedprice");
					stmtSQL.append("  ,discounttype");
					stmtSQL.append("  ,discountspec");
					// we have to explicitly set values for some columns where the default values set 
					// by the database are not what the proccessing programs expect (e.g. for 
					// monthlydiscount the db default value is ' ', but programs expect only boolean
					// values '0' or '1')
					stmtSQL.append("  ,pharmgrpexcluded");
					stmtSQL.append("  ,internaldiscount");
					stmtSQL.append("  ,monthlydiscount");
					stmtSQL.append("  ,pharmgrpexcl_2");
					stmtSQL.append("  ,pharmgrpexcl_3");
					stmtSQL.append("  ,no_multiple_qty");
					stmtSQL.append("  ,addondiscountok");
					stmtSQL.append("  ,paymenttermtype");
					stmtSQL.append("  ,turnovercalcimpact");
					stmtSQL.append(") VALUES ( ");
					stmtSQL.append(" ? ");
					stmtSQL.append(", ? ");
					stmtSQL.append(", ? ");
					stmtSQL.append(", ? ");
					stmtSQL.append(", ? ");
					stmtSQL.append(", ? ");
					stmtSQL.append(", ? ");
					stmtSQL.append(", ? ");
					// constant default values
					stmtSQL.append(",'000'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'000'");
					stmtSQL.append(",'000'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'0'");
					stmtSQL.append(",'0'");
					stmtSQL.append(")");

					m_PrepStmtInsert = getDbSqlConnection().createPreparedStatement(stmtSQL);

					std::stringstream ss;
					ss << "prepared INSERT stmt <" << stmtSQL.c_str() << "> created";
					BLOG_INFO(m_Logger, ss.str());
				}

				basar::VarString strPharmacyGroupId = PriceData::convertInt32ToVarString(priceData.pharmacyGroupId, 3);

				m_PrepStmtInsert.setInt32(0, priceData.articleNo);
				m_PrepStmtInsert.setString(1, strPharmacyGroupId.c_str());
				m_PrepStmtInsert.setInt32(2, priceData.dateFrom);
				m_PrepStmtInsert.setInt32(3, priceData.dateTo);
				m_PrepStmtInsert.setInt32(4, priceData.quantity);
				m_PrepStmtInsert.setDecimal(5, priceData.fixedPrice);
				m_PrepStmtInsert.setInt16(6, priceData.discountType);
				m_PrepStmtInsert.setInt16(7, priceData.discountSpec);

				basar::db::sql::ExecuteReturnInfo returnInfo = m_PrepStmtInsert.execute();

				return returnInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceDataDM::invalidatePriceDataByPharmacyGroup(const basar::Int32 pharmacyGroupId, const basar::Int32 dateTo)
			{
				METHODNAME_DEF(PriceDataDM, invalidatePriceDataByPharmacyGroup)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;

				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceData().insert(basar::FOR_UNKNOWN);

					whereCondition.setString(PRICEDATA_PHARMACYGROUPID.getName(), PriceData::convertInt32ToVarString(pharmacyGroupId, 3));
					whereCondition.setInt32(PRICEDATA_DATETO.getName(), dateTo);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricedata::lit::UpdatePriceDataDateToByPharmacyGroup, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricedata::lit::UpdatePriceDataDateToByPharmacyGroup, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricedata::lit::UpdatePriceDataDateToByPharmacyGroup, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceDataDM::deletePriceDataByPharmacyGroup(const basar::Int32 pharmacyGroupId, const basar::Int32 dateFrom)
			{
				METHODNAME_DEF(PriceDataDM, deletePriceDataByPharmacyGroup)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;

				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceData().insert(basar::FOR_UNKNOWN);

					whereCondition.setString(PRICEDATA_PHARMACYGROUPID.getName(), PriceData::convertInt32ToVarString(pharmacyGroupId, 3));
					whereCondition.setInt32(PRICEDATA_DATEFROM, dateFrom);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricedata::lit::DeletePriceDataByPharmacyGroup, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricedata::lit::DeletePriceDataByPharmacyGroup, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricedata::lit::DeletePriceDataByPharmacyGroup, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceDataDM::invalidatePriceDataByPharmacyGroupArticle(const basar::Int32 pharmacyGroupId, const basar::Int32 articleNo, const basar::Int32 dateTo)
			{
				METHODNAME_DEF(PriceDataDM, invalidatePriceDataByPharmacyGroupArticle)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;

				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceData().insert(basar::FOR_UNKNOWN);

					whereCondition.setString(PRICEDATA_PHARMACYGROUPID.getName(), PriceData::convertInt32ToVarString(pharmacyGroupId, 3));
					whereCondition.setInt32(PRICEDATA_ARTICLENO.getName(), articleNo);
					whereCondition.setInt32(PRICEDATA_DATETO.getName(), dateTo);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricedata::lit::UpdatePriceDataDateToByPharmacyGroupArticle, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricedata::lit::UpdatePriceDataDateToByPharmacyGroupArticle, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricedata::lit::UpdatePriceDataDateToByPharmacyGroupArticle, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::aspect::ExecuteResultInfo PriceDataDM::deletePriceDataByPharmacyGroupArticle(const basar::Int32 pharmacyGroupId, const basar::Int32 articleNo, const basar::Int32 dateFrom)
			{
				METHODNAME_DEF(PriceDataDM, deletePriceDataByPharmacyGroupArticle)
				BLOG_TRACE_METHOD(m_Logger, fun);

				basar::db::aspect::ExecuteResultInfo executeResultInfo;

				try
				{
					basar::db::aspect::AccessorPropertyTable_YIterator whereCondition = getPriceData().insert(basar::FOR_UNKNOWN);

					whereCondition.setString(PRICEDATA_PHARMACYGROUPID.getName(), PriceData::convertInt32ToVarString(pharmacyGroupId, 3));
					whereCondition.setInt32(PRICEDATA_ARTICLENO.getName(), articleNo);
					whereCondition.setInt32(PRICEDATA_DATEFROM, dateFrom);
					executeResultInfo = getAccessor()->execute(infrastructure::accessor::pricedata::lit::DeletePriceDataByPharmacyGroupArticle, whereCondition);
				}
				catch (basar::Exception & e)
				{
					libutil::exceptions::ExceptionHandler::processAccessorException(e, m_Logger, fun, infrastructure::accessor::pricedata::lit::DeletePriceDataByPharmacyGroupArticle, __FILE__, __LINE__);
					throw;
				}

				if (executeResultInfo.hasError())
				{
					THROW_ACCESSOR_EXECUTION_EXCEPTION(fun, infrastructure::accessor::pricedata::lit::DeletePriceDataByPharmacyGroupArticle, executeResultInfo)
				}

				return executeResultInfo;
			}

			basar::db::sql::ExecuteReturnInfo PriceDataDM::invalidateByPharmacyGroupArticle(const basar::Int32 pharmacyGroupId, const basar::Int32 articleNo, const basar::Int32 dateTo)
			{
				METHODNAME_DEF(PriceDataDM, invalidateByPharmacyGroupArticle)
				BLOG_TRACE_METHOD(m_Logger, fun);

				if (m_PrepStmtInvalidate.isNull() || !m_PrepStmtInvalidate.isOpen())
				{
					basar::VarString stmtSQL;
					stmtSQL.append("UPDATE cdiscount ");
					stmtSQL.append("   SET dateto = ? ");
					stmtSQL.append(" WHERE pharmacygroupid = ? ");
					stmtSQL.append("   AND articleno = ? ");
					stmtSQL.append("   AND datefrom <= ?");
					stmtSQL.append("   AND dateto > ? ");
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");

					m_PrepStmtInvalidate = getDbSqlConnection().createPreparedStatement(stmtSQL);

					std::stringstream ss;
					ss << "prepared UPDATE stmt <" << stmtSQL.c_str() << "> created";
					BLOG_INFO(m_Logger, ss.str());
				}

				basar::VarString strPharmacyGroupId = PriceData::convertInt32ToVarString(pharmacyGroupId, 3);

				m_PrepStmtInvalidate.setInt32(0, dateTo);
				m_PrepStmtInvalidate.setString(1, strPharmacyGroupId.c_str());
				m_PrepStmtInvalidate.setInt32(2, articleNo);
				m_PrepStmtInvalidate.setInt32(3, dateTo);
				m_PrepStmtInvalidate.setInt32(4, dateTo);

				basar::db::sql::ExecuteReturnInfo returnInfo = m_PrepStmtInvalidate.execute();

				return returnInfo;
			}

			basar::db::sql::ExecuteReturnInfo PriceDataDM::deleteByPharmacyGroupArticle(const basar::Int32 pharmacyGroupId, const basar::Int32 articleNo, const basar::Int32 dateFrom)
			{
				METHODNAME_DEF(PriceDataDM, deleteByPharmacyGroupArticle)
				BLOG_TRACE_METHOD(m_Logger, fun);

				if (m_PrepStmtDelete.isNull() || !m_PrepStmtDelete.isOpen())
				{
					basar::VarString stmtSQL;
					stmtSQL.append("DELETE FROM cdiscount");
					stmtSQL.append(" WHERE pharmacygroupid = ? ");
					stmtSQL.append("   AND articleno = ? ");
					stmtSQL.append("   AND datefrom > ?");
					// discounttype 16 is a special case for a percentage surcharge and is not to be touched
					// by importpricelist
					stmtSQL.append("   AND discounttype <> 16 ");

					m_PrepStmtDelete = getDbSqlConnection().createPreparedStatement(stmtSQL);

					std::stringstream ss;
					ss << "prepared DELETE stmt <" << stmtSQL.c_str() << "> created";
					BLOG_INFO(m_Logger, ss.str());
				}

				basar::VarString strPharmacyGroupId = PriceData::convertInt32ToVarString(pharmacyGroupId, 3);

				m_PrepStmtDelete.setString(0, strPharmacyGroupId.c_str());
				m_PrepStmtDelete.setInt32(1, articleNo);
				m_PrepStmtDelete.setInt32(2, dateFrom);

				basar::db::sql::ExecuteReturnInfo returnInfo = m_PrepStmtDelete.execute();

				return returnInfo;
			}

			basar::db::aspect::AccessorPropertyTableRef PriceDataDM::getPriceData()
			{
				METHODNAME_DEF(PriceDataDM, getPriceData)
				BLOG_TRACE_METHOD(m_Logger, fun);

				return getAccessor()->getPropertyTable();
			}

			void PriceDataDM::beginTransaction()
			{
				getDbConnection().beginTransaction();
			}

			void PriceDataDM::commitTransaction()
			{
				getDbConnection().commitTransaction();
			}

			void PriceDataDM::rollbackTransaction()
			{
				getDbConnection().rollbackTransaction();
			}

			//--------------------------------------------------------------------------------------------------------------------------------------------------------
			// PriceData containing de pricing data for interface usage
			//--------------------------------------------------------------------------------------------------------------------------------------------------------

			PriceData::PriceData()
				:pharmacyGroupId(0)
				, articleNo(0)
				, dateFrom(0)
				, dateTo(0)
				, quantity(0)
				, fixedPrice(0.0)
				, discountType(0)
				, discountSpec(0)
			{

			}

			PriceData::PriceData(const PriceData& other)
			{
				*this = other;
			}

			PriceData& PriceData::operator=(const PriceData& other)
			{
				pharmacyGroupId = other.pharmacyGroupId;
				articleNo = other.articleNo;
				dateFrom = other.dateFrom;
				dateTo = other.dateTo;
				quantity = other.quantity;
				fixedPrice = other.fixedPrice;
				discountType = other.discountType;
				discountSpec = other.discountSpec;
				return *this;
			}

			basar::VarString PriceData::convertInt32ToVarString(const basar::Int32 value, const basar::Int16 length)
			{
				// convert Int32 value to VarString with leading zeroes

				basar::VarString fmt;
				basar::VarString result;

				// if length is 5, fmt is "%05d"
				fmt.format("%%0%dd", length);
				result.format(fmt.c_str(), value);

				return result;
			}

			basar::Int32 PriceData::convertVarStringToInt32(const basar::VarString& value)
			{
				return value.stoi();
			}

			basar::Decimal PriceData::convertVarStringToDecimal(const basar::VarString& value)
			{
				return basar::Decimal(value);
			}
		}
	}
}

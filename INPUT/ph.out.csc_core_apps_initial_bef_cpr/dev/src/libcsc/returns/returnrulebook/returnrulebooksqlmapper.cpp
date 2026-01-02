#include "returnrulebooksqlmapper.h"
#include <logger/loggerpool.h>


namespace libcsc {
namespace returns {

	ReturnRuleBookSQLMapper::ReturnRuleBookSQLMapper(ReturnRuleBookPtr returnRuleBook, const basar::db::sql::ResultsetRef resultSet)
		: ReturnRuleBookMapperBase(returnRuleBook), m_ResultSet(resultSet)
	{
	}

	ReturnRuleBookSQLMapper::~ReturnRuleBookSQLMapper()
	{
	}

	const basar::VarString ReturnRuleBookSQLMapper::getSelectSQL(const basar::VarString& returnreasoncode)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnRuleBookSQLMapper::getSelectSQL()");

		std::stringstream sql;

		sql <<
			"SELECT "
			"acrr.returnreasoncode, "
			"acrr.checksequence, "
			"rr.officialname AS returnreasonofficialname, "
			"rr.defaultacccheckresultcode, "
			"acrr.returnacceptacecheckid, "
			"ract.shortname, "
			"ract.description, "
			"acrr.acccheckresultcode, "
			"racr.officialname AS acccheckofficialname "
			"FROM acceptancechecksbyreturnreason acrr "
			"LEFT JOIN returnreason rr ON rr.returnreasoncode = acrr.returnreasoncode "
			"LEFT JOIN returnacceptancechecktypes ract ON ract.returnacceptancecheckid = acrr.returnacceptacecheckid "
			"LEFT JOIN returnacceptancecheckresult racr ON racr.acccheckresultcode = acrr.acccheckresultcode "
			"WHERE acrr.returnreasoncode = '" << returnreasoncode << "' "
			"ORDER BY acrr.checksequence";

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	void ReturnRuleBookSQLMapper::doMap()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnRuleBookSQLMapper::doMap()");

		if (m_ResultSet.isNull())
		{
			throw;
		}

		setReturnReasonCode(m_ResultSet.getString("returnreasoncode"));
		setCheckSequence(m_ResultSet.getInt32("checksequence"));
		setReturnReasonOfficialName(m_ResultSet.getString("returnreasonofficialname"));
		setDefaultAccCheckResultCode(m_ResultSet.getString("defaultacccheckresultcode"));

		setReturnAccCheckId(static_cast<ReturnAcceptanceCheckEnum>(m_ResultSet.getInt32("returnacceptacecheckid")));
		setReturnAccCheckShortname(m_ResultSet.getString("shortname"));
		setReturnAccCheckDescription(m_ResultSet.getString("description"));

		setAccCheckResultcode(m_ResultSet.getString("acccheckresultcode"));
		setAccCheckOfficialName(m_ResultSet.getString("acccheckofficialname"));
	}

} //returns
} //libcsc

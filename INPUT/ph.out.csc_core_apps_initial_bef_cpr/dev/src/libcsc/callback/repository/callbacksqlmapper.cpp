/*
 * callbacksqlmapper.cpp
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#include "callbacksqlmapper.h"
#include "callbackcustomermapper.h"
#include "callbackdivisionmapper.h"
#include "callbackreasonmapper.h"
#include "callbackstatusmapper.h"
#include "callbackitemmapper.h"
#include "callbackmapper.h"
#include "callbackoverviewitemmapper.h"
#include "callbackposmapper.h"
#include "callback/domainmodule/callbackdivisiondm.h"
#include "callback/domainmodule/callbackitemdm.h"
#include "callback/domainmodule/callbackdm.h"
#include "callback/domainmodule/callbackoverviewitemdm.h"
#include "callback/domainmodule/callbackposdm.h"
#include "callback/domainmodule/callbackcustomerdm.h"
#include "callback/domainmodule/callbackreasondm.h"
#include "callback/domainmodule/callbackstatusdm.h"
#include "callback/domainmodule/critdm.h"
#include "callback/domainmodule/critposdm.h"
#include <base/isqlparameterbinder/idomainmodule.h>
#include <base/isqlparameterbinder/sqlparameterbinder.h>
#include <sstream>
#include <logger/loggerpool.h>

namespace libcsc {
namespace callback {
namespace repo {

CallbackSqlMapper::CallbackSqlMapper()
{
}

CallbackSqlMapper::~CallbackSqlMapper()
{
}

basar::VarString const CallbackSqlMapper::getCallbackItemSelectSQL(basar::Int32 const callbackNo, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select callbackno, kritiknr, kzposart, posnr_done, lockkz, callbackstatusid"
        << " from " << dbName << ":callbackitems"
        << " where callbackno = " << callbackNo;

    return ss.str();
}

domMod::ICallbackItemPtr CallbackSqlMapper::mapCallbackItem(basar::db::sql::ResultsetRef const resultSet)
{
    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapCallbackItem()", "resultSet.isNull", __FILE__, __LINE__), "");
    }

    domMod::ICallbackItemPtr callbackItem = domMod::CallbackItemDM::create();
    CallbackItemMapper mapper(callbackItem);
    mapper.setCallbackNo(resultSet.getInt32("callbackno"));
    mapper.setCritNo(resultSet.getInt32("kritiknr"));
    mapper.setPosTypeTag(resultSet.getString("kzposart"));
    mapper.setPosNoDone(resultSet.getInt32("posnr_done"));
    mapper.setLockTag(resultSet.getString("lockkz"));
    mapper.setCallbackStatus(resultSet.getInt16("callbackstatusid"));

    return callbackItem;
}

basar::VarString const CallbackSqlMapper::getCallbackSelectSQL(basar::Int32 const callbackNo, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select"
        << " k.kritiknr, k.kritiklevel, k.titel, k.filialnr, k.vertriebszentrumnr, k.datum, k.zeit,"
        << " ku.idfnr, ku.kzkdklasse, ku.nameapo, ku.nameinhaber, ku.strasse, ku.ort, ku.postleitzahl, ku.telnr, ku.telkurzwahl, ku.faxnr, cbi.callbackstatusid, cbi.reference"
        << " from " << dbName << ":callbackitems cbi"
        << " inner join " << dbName << ":kdkritik k on k.kritiknr = cbi.kritiknr"
        << " inner join " << dbName << ":kunde ku on ku.filialnr = k.vertriebszentrumnr and ku.idfnr = k.idfnr"
        << " where callbackno = " << callbackNo;

    return ss.str();
}

domMod::ICallbackPtr CallbackSqlMapper::mapCallback(basar::db::sql::ResultsetRef const resultSet)
{
    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapCallback()", "resultSet.isNull", __FILE__, __LINE__), "");
    }

    domMod::ICallbackPtr callback = domMod::CallbackDM::create();
    CallbackMapper mapper(callback);

    mapper.setCritNo(resultSet.getInt32("kritiknr"));
    mapper.setCallbackDate(resultSet.getInt32("datum"));
    mapper.setCallbackTime(resultSet.getInt32("zeit"));
    mapper.setCritLevel(resultSet.getInt16("kritiklevel"));
    mapper.setTitle(resultSet.getString("titel"));
    mapper.setBranchNo(resultSet.getInt16("filialnr"));
    mapper.setCstBranchNo(resultSet.getInt16("vertriebszentrumnr"));
    mapper.setCustomerNo(resultSet.getInt32("idfnr"));
    mapper.setCustomerClassTag(resultSet.getString("kzkdklasse"));
    mapper.setPharmacyName(resultSet.getString("nameapo"));
    mapper.setOwnerName(resultSet.getString("nameinhaber"));
    mapper.setStreet(resultSet.getString("strasse"));
    mapper.setCity(resultSet.getString("ort"));
    mapper.setZipCode(resultSet.getString("postleitzahl"));
    mapper.setTelefonNo(resultSet.getString("telnr"));
    mapper.setSpeedDialNo(resultSet.getString("telkurzwahl"));
    mapper.setFaxNo(resultSet.getString("faxnr"));
    mapper.setCallbackStatus(resultSet.getInt16("callbackstatusid"));
    mapper.setReference(resultSet.getString("reference"));

    return callback;
}

basar::VarString const CallbackSqlMapper::getCallbackPosSelectSQL(basar::Int32 const critNo, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select"
        << " kp.kritiktext, kp.datum, kp.zeit, kp.posnr,"
        << " nvl(pw.username, kp.windowsid) as username,"
        << " nvl(cbi.callbackno, 0) as callbackno, nvl(cbi.posnr_done, 0) as posnr_done, nvl(cbi.callbacktimewished, 0) as callbacktimewished, nvl(cbi.callbackdatewished, 0) as callbackdatewished,"
        << " nvl(cbd.divisionname, '') as divisionname"
        << " from " << dbName << ":kdkritikpos kp"
        << " inner join " << dbName << ":kdkritik kr on kr.kritiknr = kp.kritiknr"
        << " left join " << dbName << ":passwd pw on pw.filialnr = kp.filialnr and pw.uid = kp.uid"
        << " left join " << dbName << ":callbackitems cbi on kp.kritiknr = cbi.kritiknr and kp.posnr = cbi.posnr and kp.kzposart = cbi.kzposart"
        << " left join " << dbName << ":callbackdivision cbd on cbd.callbackdivisionno = cbi.callbackpartno and cbd.branchno = kr.vertriebszentrumnr"
        << " where kp.kritiknr = " << critNo;

    return ss.str();
}

domMod::ICallbackPosPtr CallbackSqlMapper::mapCallbackPos(basar::db::sql::ResultsetRef const resultSet)
{
    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapCallback()", "resultSet.isNull", __FILE__, __LINE__), "");
    }

    domMod::ICallbackPosPtr callbackPos = domMod::CallbackPosDM::create();
    CallbackPosMapper mapper(callbackPos);

    mapper.setText(resultSet.getString("kritiktext"));
    mapper.setCreationDate(resultSet.getInt32("datum"));
    mapper.setCreationTime(resultSet.getInt32("zeit"));
    mapper.setUserName(resultSet.getString("username"));
    mapper.setCallbackNo(resultSet.getInt32("callbackno"));
    mapper.setCallbackPosNo(resultSet.getInt32("posnr"));
    mapper.setCallbackPosNoDone(resultSet.getInt32("posnr_done"));
    mapper.setCallbackTimeWished(resultSet.getInt32("callbacktimewished") * 100);
    mapper.setCallbackDateWished(resultSet.getInt32("callbackdatewished"));
    mapper.setDivisionName(resultSet.getString("divisionname"));

    return callbackPos;
}

basar::VarString const CallbackSqlMapper::getUpdateCallbackItemSQL(basar::VarString const& dbName)
{
    std::stringstream ss;
    ss << "UPDATE "<< dbName << ":callbackitems SET"
       << " posnr_done = ?,"
       << " lockkz = ?,"
       << " callbackstatusid = ?"
       << " WHERE callbackno = ?";

    return ss.str();
}

struct UpdateCallbackItemSqlParameterBinder
{
    void operator()(basar::db::sql::PreparedStatementRef preparedStatement, base::IDomainModulePtr const domainModule) const
    {
        CallbackSqlMapper::bindUpdateCallbackItemSQL(preparedStatement, boost::static_pointer_cast<domMod::ICallbackItem>(domainModule));
    }
};

persistence::ISqlParameterBinderPtr const CallbackSqlMapper::getUpdateCallbackItemSqlParameterBinder(base::IDomainModulePtr const domainModule)
{
    return persistence::ISqlParameterBinderPtr(new base::SqlParameterBinder<UpdateCallbackItemSqlParameterBinder>(domainModule, UpdateCallbackItemSqlParameterBinder()));
}

void CallbackSqlMapper::bindUpdateCallbackItemSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICallbackItemPtr const callbackItem)
{
    //BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "CallbackSqlMapper::bindUpdateCallbackItemSQL()");

    std::stringstream ss;
    ss << "CallbackSqlMapper::bindUpdateCallbackItemSQL(), bind parameter values:" << std::endl;
    basar::UInt32 counter = 0;

    ss << counter << ": " << callbackItem->getPosNoDone() << " (posNoDone)" << std::endl;
    prepStmt.setInt32(counter++, callbackItem->getPosNoDone());
    ss << counter << ": " << callbackItem->getLockTag() << " (lockTag)" << std::endl;
    prepStmt.setString(counter++, callbackItem->getLockTag().c_str());
    ss << counter << ": " << callbackItem->getCallbackStatus() << " (callbackNo)" << std::endl;
    prepStmt.setInt16(counter++, callbackItem->getCallbackStatus());
    ss << counter << ": " << callbackItem->getCallbackNo() << " (callbackNo)" << std::endl;
    prepStmt.setInt32(counter++, callbackItem->getCallbackNo());

    //BLOG_TRACE(LoggerPool::getLoggerCallback(), ss.str().c_str());
}

basar::VarString const CallbackSqlMapper::getUpdateCallbackStatusSQL(basar::VarString const& dbName)
{
    std::stringstream ss;
    ss << "UPDATE " << dbName << ":callbackitems SET"
        << " callbackstatusid = ?,"
        << " lockkz = ?"
        << " WHERE callbackno = ?";

    return ss.str();
}

struct UpdateCallbackStatusSqlParameterBinder
{
    void operator()(basar::db::sql::PreparedStatementRef preparedStatement, base::IDomainModulePtr const domainModule) const
    {
        CallbackSqlMapper::bindUpdateCallbackStatusSQL(preparedStatement, boost::static_pointer_cast<domMod::ICallbackItem>(domainModule));
    }
};

persistence::ISqlParameterBinderPtr const CallbackSqlMapper::getUpdateCallbackStatusSqlParameterBinder(base::IDomainModulePtr const domainModule)
{
    return persistence::ISqlParameterBinderPtr(new base::SqlParameterBinder<UpdateCallbackStatusSqlParameterBinder>(domainModule, UpdateCallbackStatusSqlParameterBinder()));
}

void CallbackSqlMapper::bindUpdateCallbackStatusSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICallbackItemPtr const callbackItem)
{
    std::stringstream ss;
    ss << "CallbackSqlMapper::bindUpdateCallbackStatusSQL(), bind parameter values:" << std::endl;
    basar::UInt32 counter = 0;

    ss << counter << ": " << callbackItem->getCallbackStatus() << " (callbackstatusid)" << std::endl;
    prepStmt.setInt16(counter++, callbackItem->getCallbackStatus());
    ss << counter << ": " << callbackItem->getLockTag() << " (lockTag)" << std::endl;
    prepStmt.setString(counter++, callbackItem->getLockTag().c_str());
    ss << counter << ": " << callbackItem->getCallbackNo() << " (callbackno)" << std::endl;
    prepStmt.setInt32(counter++, callbackItem->getCallbackNo());

    BLOG_TRACE(LoggerPool::getLoggerCallback(), ss.str().c_str());
}

basar::VarString const CallbackSqlMapper::getMaxPosSelectSQL(basar::Int32 const critNo, basar::VarString const& posTypeTag, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select max(posnr)"
        << " from " << dbName << ":kdkritikpos"
        << " where kritiknr = " << critNo << " and kzposart = " << posTypeTag;

    return ss.str();
}

basar::VarString const CallbackSqlMapper::getInsertCritPosSQL(basar::VarString const& dbName)
{
    std::stringstream ss;
    ss << "INSERT INTO "<< dbName << ":kdkritikpos "
       << "(kritiknr, posnr, kzposart, kritiktext, uid, filialnr, datum, zeit, windowsid, sourceapplication) "
       << "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    return ss.str();
}

struct InsertCritPosSqlParameterBinder
{
    void operator()(basar::db::sql::PreparedStatementRef preparedStatement, base::IDomainModulePtr const domainModule) const
    {
        CallbackSqlMapper::bindInsertCritPosSQL(preparedStatement, boost::static_pointer_cast<domMod::ICritPos>(domainModule));
    }
};

persistence::ISqlParameterBinderPtr const CallbackSqlMapper::getInsertCritPosSqlParameterBinder(base::IDomainModulePtr const domainModule)
{
    return persistence::ISqlParameterBinderPtr(new base::SqlParameterBinder<InsertCritPosSqlParameterBinder>(domainModule, InsertCritPosSqlParameterBinder()));
}

void CallbackSqlMapper::bindInsertCritPosSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICritPosPtr const critPos)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "CallbackSqlMapper::bindInsertCritPosSQL()");

    std::stringstream ss;
    ss << "CallbackSqlMapper::bindInsertCritPosSQL(), bind parameter values:" << std::endl;
    basar::UInt32 counter = 0;

    ss << counter << ": " << critPos->getCritNo() << " (critNo)" << std::endl;
    prepStmt.setInt32(counter++, critPos->getCritNo());
    ss << counter << ": " << critPos->getPosNo() << " (posNo)" << std::endl;
    prepStmt.setInt32(counter++, critPos->getPosNo());
    ss << counter << ": " << critPos->getPosTypeTag() << " (posTypeTag)" << std::endl;
    prepStmt.setString(counter++, critPos->getPosTypeTag().c_str());
    ss << counter << ": " << critPos->getText() << " (kritiktext)" << std::endl;
    prepStmt.setString(counter++, critPos->getText().c_str());
    ss << counter << ": " << critPos->getUId() << " (uId)" << std::endl;
    prepStmt.setInt32(counter++, critPos->getUId());
    ss << counter << ": " << critPos->getBranchNo() << " (branchNo)" << std::endl;
    prepStmt.setInt16(counter++, critPos->getBranchNo());
    ss << counter << ": " << critPos->getDate() << " (date)" << std::endl;
    prepStmt.setInt32(counter++, critPos->getDate());
    ss << counter << ": " << critPos->getTime() << " (time)" << std::endl;
    prepStmt.setInt32(counter++, critPos->getTime());
    ss << counter << ": " << critPos->getWindowsUserId() << " (windowsUserId)" << std::endl;
    prepStmt.setString(counter++, critPos->getWindowsUserId().c_str());
    ss << counter << ": " << critPos->getSourceApplication() << " (sourceApplication)" << std::endl;
    prepStmt.setInt16(counter++, critPos->getSourceApplication());
}

basar::VarString const CallbackSqlMapper::getCallbackDivisionsSelectSQL(basar::Int16 const branchNo, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select branchno, callbackdivisionno, divisionname, mailinglist"
        << " from " << dbName << ":callbackdivision"
        << " left join parameter p on p.filialnr=branchno AND p.programmname='KSC' AND p.zweck='CALLBACK'"
        << " where branchno = " << branchNo
        << "   and callbackdivisionno >= nvl(p.wert, 0)"
        << "   and callbackdivisionno <  nvl((p.wert + 100), 100)"
        << " order by divisionname";

    return ss.str();
}

basar::VarString const CallbackSqlMapper::getCallbackDivisionSelectSQL(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select branchno, callbackdivisionno, divisionname, mailinglist"
        << " from " << dbName << ":callbackdivision"
        << " where branchno = " << branchNo
        << " and callbackdivisionno = " << divisionNo;

    return ss.str();
}

domMod::ICallbackDivisionPtr CallbackSqlMapper::mapCallbackDivision(basar::db::sql::ResultsetRef const resultSet)
{
    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapCallbackDivision()", "resultSet.isNull", __FILE__, __LINE__), "");
    }

    domMod::ICallbackDivisionPtr callbackDivision = domMod::CallbackDivisionDM::create();
    CallbackDivisionMapper mapper(callbackDivision);
    mapper.setBranchNo(resultSet.getInt16("branchno"));
    mapper.setDivisionNo(resultSet.getInt16("callbackdivisionno"));
    mapper.setDivisionName(resultSet.getString("divisionname"));
    mapper.setMailingList(resultSet.getString("mailinglist"));

    return callbackDivision;
}

basar::VarString const CallbackSqlMapper::getCallbackReasonsSelectSQL(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select branchno, callbackdivisionno, reasonno, callbackreason, mailinglist"
        << " from " << dbName << ":callbackreasons"
        << " where branchno = " << branchNo
        << " and callbackdivisionno = " << divisionNo
        << " order by callbackreason";

    return ss.str();
}

basar::VarString const CallbackSqlMapper::getCallbackReasonSelectSQL(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select branchno, callbackdivisionno, reasonno, callbackreason, mailinglist"
        << " from " << dbName << ":callbackreasons"
        << " where branchno = " << branchNo
        << " and callbackdivisionno = " << divisionNo
        << " and reasonno = " << reasonNo;

    return ss.str();
}

domMod::ICallbackReasonPtr CallbackSqlMapper::mapCallbackReason(basar::db::sql::ResultsetRef const resultSet)
{
    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapCallbackReason()", "resultSet.isNull", __FILE__, __LINE__), "");
    }

    domMod::ICallbackReasonPtr callbackReason = domMod::CallbackReasonDM::create();
    CallbackReasonMapper mapper(callbackReason);
    mapper.setBranchNo(resultSet.getInt16("branchno"));
    mapper.setDivisionNo(resultSet.getInt16("callbackdivisionno"));
    mapper.setReasonNo(resultSet.getInt16("reasonno"));
    mapper.setReasonName(resultSet.getString("callbackreason"));
    mapper.setMailingList(resultSet.getString("mailinglist"));

    return callbackReason;
}

basar::VarString const CallbackSqlMapper::getCallbackStatusesSelectSQL(basar::VarString const& dbName)
{
	std::stringstream ss;
	ss
		<< "select cbs.callbackstatusid, cbs.callbackstatusname, NVL(p.wert,0) as callbackstatusflag"
		<< " from " << dbName << ":callbackstatus cbs"
        << " left join " << dbName << ":parameter p on cbs.callbackstatusid=p.parametername and p.programmname='callbackeditor' and p.zweck='statusinfo'"
		<< " order by cbs.callbackstatusid";

	return ss.str();
}

domMod::ICallbackStatusPtr CallbackSqlMapper::mapCallbackStatus(basar::db::sql::ResultsetRef const resultSet)
{
	if (resultSet.isNull())
	{
		throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapCallbackStatus()", "resultSet.isNull", __FILE__, __LINE__), "");
	}

	domMod::ICallbackStatusPtr callbackStatus = domMod::CallbackStatusDM::create();
	CallbackStatusMapper mapper(callbackStatus);
	mapper.setCallbackStatusNo(resultSet.getInt16("callbackstatusid"));
	mapper.setCallbackStatusName(resultSet.getString("callbackstatusname"));
    mapper.setCallbackStatusFlag(resultSet.getInt32("callbackstatusflag"));

	return callbackStatus;
}

basar::VarString const CallbackSqlMapper::getCallbackStatusVisibilitySelectSQL(basar::VarString const& dbName)
{
	std::stringstream ss;
    ss
        << "select p.wert"
        << " from " << dbName << ":parameter p"
        << " where p.programmname='callbackeditor' and p.zweck='statusvisibility'";
	return ss.str();
}

bool CallbackSqlMapper::mapCallbackStatusVisibility(basar::db::sql::ResultsetRef const resultSet)
{
	if (resultSet.isNull())
	{
		throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapCallbackStatusVisibility()", "resultSet.isNull", __FILE__, __LINE__), "");
	}
	Int32 visible = resultSet.getInt32("wert");
	return ((int)visible);
}

basar::VarString const CallbackSqlMapper::getFindCustomersSelectSQL(FindCustomersRequestPtr const findCustomersRequest, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select first " << findCustomersRequest->MaxResults
        << " k.filialnr,"
        << " case when k.originalfilialnr = 0 then k.filialnr else k.originalfilialnr end as originalfilialnr,"
        << " k.kundennr, k.vertriebszentrumnr, k.nameapo, k.nameinhaber, k.strasse, k.ort, k.telkurzwahl"
        << " from " << dbName << ":kunde k"
        << " inner join " << dbName << ":kundeschalter ks on ks.vertriebszentrumnr = k.vertriebszentrumnr and ks.kundennr = k.kundennr";

    findCustomersRequest->MatchCode.trim();
    if (findCustomersRequest->CustomerNo > 0)
    {
        getSelectSqlByCustomerNoForFindCustomers(ss, findCustomersRequest->CustomerNo);
    }
    else if (findCustomersRequest->MatchCode.length() > 0)
    {
        getSelectSqlByMatchCodeFindCustomers(ss, findCustomersRequest->MatchCode, findCustomersRequest->OwnerName, findCustomersRequest->City);
    }
    else
    {
        getSelectSqlByNameForFindCustomers(ss, findCustomersRequest->PharmacyName, findCustomersRequest->OwnerName, findCustomersRequest->City);
    }

    getCommonWherePartForFindCustomers(ss, findCustomersRequest->LockedCustomers);
    getCommonSelectSqlOutroForFindCustomers(ss, findCustomersRequest->BranchNo, findCustomersRequest->OnlyOwnBranch, dbName);

    ss
        << " order by k.nameapo, k.ort, k.originalfilialnr";

    return ss.str();
}

void CallbackSqlMapper::getSelectSqlByNameForFindCustomers(std::stringstream& ss, basar::VarString pharmacyName, basar::VarString ownerName, basar::VarString city)
{
    pharmacyName.trim();
    ownerName.trim();
    city.trim();

    getWherePartByNameForFindCustomers(ss, pharmacyName, ownerName, city);
}

void CallbackSqlMapper::getSelectSqlByCustomerNoForFindCustomers(std::stringstream& ss, basar::Int32 const customerNo)
{
    getWherePartByCustomerForFindCustomers(ss, customerNo);
}

void CallbackSqlMapper::getSelectSqlByMatchCodeFindCustomers(std::stringstream& ss, basar::VarString matchCode, basar::VarString ownerName, basar::VarString city)
{
    matchCode.trim();
    ownerName.trim();
    city.trim();

    getWherePartByMatchCodeForFindCustomers(ss, matchCode, ownerName, city);
}

basar::VarString const CallbackSqlMapper::getFindCustomersCountSelectSQL(FindCustomersRequestPtr const findCustomersRequest, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select count('x')::int"
        << " from " << dbName << ":kunde k"
        << " inner join " << dbName << ":kundeschalter ks on ks.vertriebszentrumnr = k.vertriebszentrumnr and ks.kundennr = k.kundennr";

    findCustomersRequest->MatchCode.trim();
    if (findCustomersRequest->CustomerNo > 0)
    {
        getSelectSqlByCustomerNoForFindCustomersCount(ss, findCustomersRequest->CustomerNo);
    }
    else if (findCustomersRequest->MatchCode.length() > 0)
    {
        getSelectSqlByMatchCodeForFindCustomersCount(ss, findCustomersRequest->MatchCode, findCustomersRequest->OwnerName, findCustomersRequest->City);
    }
    else
    {
        getSelectSqlByNameForFindCustomersCount(ss, findCustomersRequest->PharmacyName, findCustomersRequest->OwnerName, findCustomersRequest->City);
    }

    getCommonWherePartForFindCustomers(ss, findCustomersRequest->LockedCustomers);
    getCommonSelectSqlOutroForFindCustomers(ss, findCustomersRequest->BranchNo, findCustomersRequest->OnlyOwnBranch, dbName);
    return ss.str();
}

void CallbackSqlMapper::getSelectSqlByNameForFindCustomersCount(std::stringstream& ss, basar::VarString pharmacyName, basar::VarString ownerName, basar::VarString city)
{
    pharmacyName.trim();
    ownerName.trim();
    city.trim();

    getWherePartByNameForFindCustomers(ss, pharmacyName, ownerName, city);
}

void CallbackSqlMapper::getSelectSqlByCustomerNoForFindCustomersCount(std::stringstream& ss, basar::Int32 const customerNo)
{
    getWherePartByCustomerForFindCustomers(ss, customerNo);
}

void CallbackSqlMapper::getSelectSqlByMatchCodeForFindCustomersCount(std::stringstream& ss, basar::VarString matchCode, basar::VarString ownerName, basar::VarString city)
{
    matchCode.trim();
    ownerName.trim();
    city.trim();

    getWherePartByMatchCodeForFindCustomers(ss, matchCode, ownerName, city);
}

void CallbackSqlMapper::getWherePartByNameForFindCustomers(
    std::stringstream& ss, basar::VarString pharmacyName, basar::VarString ownerName, basar::VarString city)
{
    ss
        << " where k.nameapo like '" << pharmacyName << "%'"
        << " and k.nameinhaber like '%" << ownerName << "%'"
        << " and k.ort like '" << city << "%'";
}

void CallbackSqlMapper::getWherePartByCustomerForFindCustomers(std::stringstream& ss, basar::Int32 const customerNo)
{
    ss
        << " where k.kundennr = " << customerNo;
}

void CallbackSqlMapper::getWherePartByMatchCodeForFindCustomers(
    std::stringstream& ss, basar::VarString matchCode, basar::VarString ownerName, basar::VarString city)
{
    ss
        << " where k.matchcode like '" << matchCode << "%'"
        << " and k.nameinhaber like '%" << ownerName << "%'"
        << " and k.ort like '" << city << "%'";
}

void CallbackSqlMapper::getCommonWherePartForFindCustomers(std::stringstream& ss, bool const lockedCustomers)
{
    ss
        << " and ks.skdkundeaegesperrt <= " << (lockedCustomers ? 1 : 0);
}

void CallbackSqlMapper::getCommonSelectSqlOutroForFindCustomers(std::stringstream& ss, basar::Int16 const branchNo, bool const onlyOwnBranch, basar::VarString const& dbName)
{
    basar::Int16 branchNoFrom;
    basar::Int16 branchNoTo;
    getBranchNoRange(branchNo, onlyOwnBranch, branchNoFrom, branchNoTo);

    ss
        << " and k.vertriebszentrumnr <= " << branchNoTo << " and k.vertriebszentrumnr >= " << branchNoFrom
        << " and k.vertriebszentrumnr in (select ra.RegionTeilNr from " << dbName << ":RegionArten ra where ra.RegionNr = " << branchNo << " and ra.RegionenTyp = 1)";
}

void CallbackSqlMapper::getBranchNoRange(basar::Int16 const& branchNo, bool const onlyOwnBranch, basar::Int16& branchNoFrom, basar::Int16& branchNoTo)
{
    if (onlyOwnBranch)
    {
        branchNoFrom = branchNo;
        branchNoTo = branchNo;
    }
    else
    {
        branchNoFrom = 0;
        branchNoTo = 99;
    }
}

domMod::ICallbackCustomerPtr CallbackSqlMapper::mapCustomer(basar::db::sql::ResultsetRef const resultSet)
{
    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapFindCustomer()", "resultSet.isNull", __FILE__, __LINE__), "");
    }

    domMod::ICallbackCustomerPtr callbackCustomer = domMod::CallbackCustomerDM::create();
    CallbackCustomerMapper mapper(callbackCustomer);
    mapper.setBranchNo(resultSet.getInt16("filialnr"));
    mapper.setOrigBranchNo(resultSet.getInt16("originalfilialnr"));
    mapper.setCustomerNo(resultSet.getInt32("kundennr"));
    mapper.setCstBranchNo(resultSet.getInt16("vertriebszentrumnr"));
    mapper.setPharmacyName(resultSet.getString("nameapo"));
    mapper.setOwnerName(resultSet.getString("nameinhaber"));
    mapper.setZipCode("nA"); // unused
    mapper.setCity(resultSet.getString("ort"));
    mapper.setStreet(resultSet.getString("strasse"));
    mapper.setTelefonNo("nA"); // unused
    mapper.setSpeedDialNo(resultSet.getString("telkurzwahl"));

    return callbackCustomer;
}

basar::VarString const CallbackSqlMapper::getMaxCritNoSelectSQL(basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select max(kritiknr)"
        << " from " << dbName << ":kdkritik";

    return ss.str();
}

basar::VarString const CallbackSqlMapper::getInsertCritSQL(basar::VarString const& dbName)
{
    std::stringstream ss;
    ss << "INSERT INTO "<< dbName << ":kdkritik "
       << "(idfnr, datum, zeit, uid, titel, kritiknr, vertriebszentrumnr, kundennr, filialnr, kritiklevel) "
       << "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    return ss.str();
}

struct InsertCritSqlParameterBinder
{
    void operator()(basar::db::sql::PreparedStatementRef preparedStatement, base::IDomainModulePtr const domainModule) const
    {
        CallbackSqlMapper::bindInsertCritItemSQL(preparedStatement, boost::static_pointer_cast<domMod::ICrit>(domainModule));
    }
};

persistence::ISqlParameterBinderPtr const CallbackSqlMapper::getInsertCritSqlParameterBinder(base::IDomainModulePtr const domainModule)
{
    return persistence::ISqlParameterBinderPtr(new base::SqlParameterBinder<InsertCritSqlParameterBinder>(domainModule, InsertCritSqlParameterBinder()));
}

void CallbackSqlMapper::bindInsertCritItemSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICritPtr const crit)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "CallbackSqlMapper::bindInsertCritItemSQL()");

    std::stringstream ss;
    ss << "CallbackSqlMapper::bindInsertCritItemSQL(), bind parameter values:" << std::endl;
    basar::UInt32 counter = 0;

    ss << counter << ": " << crit->getCustomerNo() << " (idfnr)" << std::endl;
    prepStmt.setInt32(counter++, crit->getCustomerNo());
    ss << counter << ": " << crit->getDate() << " (datum)" << std::endl;
    prepStmt.setInt32(counter++, crit->getDate());
    ss << counter << ": " << crit->getTime() << " (zeit)" << std::endl;
    prepStmt.setInt32(counter++, crit->getTime());
    ss << counter << ": " << crit->getUId() << " (uid)" << std::endl;
    prepStmt.setInt32(counter++, crit->getUId());
    ss << counter << ": " << crit->getTitle() << " (titel)" << std::endl;
    prepStmt.setString(counter++, crit->getTitle().c_str());
    ss << counter << ": " << crit->getCritNo() << " (kritiknr)" << std::endl;
    prepStmt.setInt32(counter++, crit->getCritNo());
    ss << counter << ": " << crit->getCstBranchNo() << " (vertriebszentrumnr)" << std::endl;
    prepStmt.setInt16(counter++, crit->getCstBranchNo());
    ss << counter << ": " << crit->getCustomerNo() << " (kundennr)" << std::endl;
    prepStmt.setInt32(counter++, crit->getCustomerNo());
    ss << counter << ": " << crit->getBranchNo() << " (filialnr)" << std::endl;
    prepStmt.setInt16(counter++, crit->getBranchNo());
    ss << counter << ": " << crit->getCritLevel() << " (kritiklevel)" << std::endl;
    prepStmt.setInt16(counter++, crit->getCritLevel());
}

basar::VarString const CallbackSqlMapper::getMaxCallbackNoSelectSQL(basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select max(callbackno)"
        << " from " << dbName << ":callbackitems";

    return ss.str();
}

basar::VarString const CallbackSqlMapper::getInsertCallbackItemSQL(basar::VarString const& dbName)
{
    std::stringstream ss;
    ss << "INSERT INTO "<< dbName << ":callbackitems "
       << "(callbackno, callbackpartno, kritiknr, posnr, kzposart, posnr_done, callbacktimewished, callbackdatewished, callbacktime, state, lockkz, reasonno, callbackstatusid, reference) "
       << "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    return ss.str();
}

struct InsertCallbackItemSqlParameterBinder
{
    void operator()(basar::db::sql::PreparedStatementRef preparedStatement, base::IDomainModulePtr const domainModule) const
    {
        CallbackSqlMapper::bindInsertCallbackItemSQL(preparedStatement, boost::static_pointer_cast<domMod::ICallbackItem>(domainModule));
    }
};

persistence::ISqlParameterBinderPtr const CallbackSqlMapper::getInsertCallbackItemSqlParameterBinder(base::IDomainModulePtr const domainModule)
{
    return persistence::ISqlParameterBinderPtr(new base::SqlParameterBinder<InsertCallbackItemSqlParameterBinder>(domainModule, InsertCallbackItemSqlParameterBinder()));
}

void CallbackSqlMapper::bindInsertCallbackItemSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICallbackItemPtr const callbackItem)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "CallbackSqlMapper::bindInsertCallbackItemSQL()");

    std::stringstream ss;
    ss << "CallbackSqlMapper::bindInsertCallbackItemSQL(), bind parameter values:" << std::endl;
    basar::UInt32 counter = 0;

    //    "(callbackno, callbackpartno, kritiknr, posnr, kzposart, posnr_done, callbacktimewished, callbackdatewished, callbacktime, state, lockkz, reasonno) "
    ss << counter << ": " << callbackItem->getCallbackNo() << " (callbackno)" << std::endl;
    prepStmt.setInt32(counter++, callbackItem->getCallbackNo());
    ss << counter << ": " << callbackItem->getCallbackPartNo() << " (callbackpartno)" << std::endl;
    prepStmt.setInt32(counter++, callbackItem->getCallbackPartNo());
    ss << counter << ": " << callbackItem->getCritNo() << " (kritiknr)" << std::endl;
    prepStmt.setInt32(counter++, callbackItem->getCritNo());
    ss << counter << ": " << callbackItem->getPosNo() << " (posnr)" << std::endl;
    prepStmt.setInt32(counter++, callbackItem->getPosNo());
    ss << counter << ": " << callbackItem->getPosTypeTag() << " (kzposart)" << std::endl;
    prepStmt.setString(counter++, callbackItem->getPosTypeTag().c_str());
    ss << counter << ": " << callbackItem->getPosNoDone() << " (posnr_done)" << std::endl;
    prepStmt.setInt32(counter++, callbackItem->getPosNoDone());
    ss << counter << ": " << (callbackItem->getCallbackTimeWished() / 100) << " (callbacktimewished)" << std::endl;
    prepStmt.setInt32(counter++, (callbackItem->getCallbackTimeWished() / 100));
    ss << counter << ": " << callbackItem->getCallbackDateWished() << " (callbackdatewished)" << std::endl;
    prepStmt.setInt32(counter++, callbackItem->getCallbackDateWished());
    ss << counter << ": " << callbackItem->getCallbackTime() << " (callbacktime)" << std::endl;
    prepStmt.setInt16(counter++, callbackItem->getCallbackTime());
    ss << counter << ": " << callbackItem->getState() << " (state)" << std::endl;
    prepStmt.setString(counter++, callbackItem->getState().c_str());
    ss << counter << ": " << callbackItem->getLockTag() << " (lockkz)" << std::endl;
    prepStmt.setString(counter++, callbackItem->getLockTag().c_str());
    ss << counter << ": " << callbackItem->getReasonNo() << " (reasonno)" << std::endl;
    prepStmt.setInt16(counter++, callbackItem->getReasonNo());
    ss << counter << ": " << callbackItem->getCallbackStatus() << " (callbackstatusid)" << std::endl;
    prepStmt.setInt16(counter++, callbackItem->getCallbackStatus());
    ss << counter << ": " << callbackItem->getReference() << " (reference)" << std::endl;
    prepStmt.setString(counter++, callbackItem->getReference().c_str());
}

basar::VarString const CallbackSqlMapper::getCallbackCustomerSelectSQL(basar::Int16 const branchNo, basar::Int32 const customerNo, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select filialnr, kundennr, nameapo, postleitzahl, ort, telnr, telkurzwahl"
        << " from " << dbName << ":kunde"
        << " where filialnr = " << branchNo
        << " and kundennr = " << customerNo;

    return ss.str();
}

domMod::ICallbackCustomerPtr CallbackSqlMapper::mapCallbackCustomer(basar::db::sql::ResultsetRef const resultSet)
{
    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapCallbackReason()", "resultSet.isNull", __FILE__, __LINE__), "");
    }

    domMod::ICallbackCustomerPtr callbackCustomer = domMod::CallbackCustomerDM::create();
    CallbackCustomerMapper mapper(callbackCustomer);
    mapper.setBranchNo(resultSet.getInt16("filialnr"));
    mapper.setOrigBranchNo(-1); // unused
    mapper.setCustomerNo(resultSet.getInt32("kundennr"));
    mapper.setCstBranchNo(-1); // unused
    mapper.setPharmacyName(resultSet.getString("nameapo"));
    mapper.setOwnerName("nA"); // unused
    mapper.setZipCode(resultSet.getString("postleitzahl"));
    mapper.setCity(resultSet.getString("ort"));
    mapper.setStreet("nA"); // unused
    mapper.setTelefonNo(resultSet.getString("telnr"));
    mapper.setSpeedDialNo(resultSet.getString("telkurzwahl"));

    return callbackCustomer;
}

basar::VarString const CallbackSqlMapper::getCallbackUserNameSelectSQL(basar::Int16 const branchNo, basar::Int32 const uid, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select username"
        << " from " << dbName << ":passwd"
        << " where filialnr = " << branchNo
        << " and uid = " << uid;

    return ss.str();
}

basar::VarString const CallbackSqlMapper::getFindCallbacksSelectSQL(FindCallbacksRequestPtr const findCallbacksRequest, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select first " << findCallbacksRequest->MaxResults
        << " cbi.callbackno,"
        << " cbr.callbackreason, k.filialnr, k.datum, k.zeit, k.kritiklevel,"
        << " ku.nameapo, ku.ort, cbs.callbackstatusname, cbd.divisionname, cbi.reference";

    getCommonFromWherePartForFindCallbacks(ss, findCallbacksRequest, dbName);

    ss
        << " order by k.datum desc, k.zeit desc";

    return ss.str();
}

void CallbackSqlMapper::getCommonFromWherePartForFindCallbacks(std::stringstream& ss, FindCallbacksRequestPtr const findCallbacksRequest, basar::VarString const& dbName)
{
    basar::Int16 branchNoFrom;
    basar::Int16 branchNoTo;
    getBranchNoRange(findCallbacksRequest->BranchNo, findCallbacksRequest->OnlyOwnBranch, branchNoFrom, branchNoTo);

    ss
        << " from " << dbName << ":callbackitems cbi"
        << " inner join " << dbName << ":kdkritik k on k.kritiknr = cbi.kritiknr"
        << " inner join " << dbName << ":kunde ku on ku.filialnr = k.vertriebszentrumnr and ku.idfnr = k.idfnr"
        << " left join " << dbName << ":callbackstatus cbs on cbs.callbackstatusid = cbi.callbackstatusid"
        << " inner join " << dbName << ":callbackdivision cbd on cbd.callbackdivisionno = cbi.callbackpartno and cbd.branchno = ku.filialnr"
        << " inner join " << dbName <<":callbackreasons cbr on cbr.reasonno = cbi.reasonno and cbr.callbackdivisionno = cbi.callbackpartno and cbd.branchno = cbr.branchno"
        << " where k.titel like '" << findCallbacksRequest->Title << "%'"
        << " and k.datum >= " << findCallbacksRequest->DateFrom
        << " and k.datum <= " << findCallbacksRequest->DateTo
        << " and k.vertriebszentrumnr >= " << branchNoFrom << " and k.vertriebszentrumnr <= " << branchNoTo
        << " and k.vertriebszentrumnr in ("
        << "    select ra.RegionTeilNr from " << dbName << ":RegionArten ra where ra.RegionNr = " << findCallbacksRequest->BranchNo << " and ra.RegionenTyp = 1"
        << " )";

    if (findCallbacksRequest->CustomerNo > 0)
    {
        getWherePart4CustomerNoForFindCallbacks(ss, findCallbacksRequest->CustomerNo);
    }

    if (findCallbacksRequest->DivisionNo > 0) {
		getWherePart4DivisionForFindCallbacks(ss, findCallbacksRequest->DivisionNo);
    }

    if (findCallbacksRequest->ReasonNo > 0)
    {
        getWherePart4ReasonsForFindCallbacks(ss, findCallbacksRequest->ReasonNo);
    }

    if (findCallbacksRequest->StatusNo != -1)
    {
		getWherePart4StatusForFindCallbacks(ss, findCallbacksRequest->StatusNo);
	}
}

void CallbackSqlMapper::getWherePart4DivisionForFindCallbacks(std::stringstream& ss, basar::Int16 divisionNo)
{
	ss
		<< " and cbi.callbackpartno = " << divisionNo;
}

void CallbackSqlMapper::getWherePart4ReasonsForFindCallbacks(std::stringstream& ss, basar::Int16 reasonNo)
{
    ss
        << " and cbi.reasonno = " << reasonNo;
}

void CallbackSqlMapper::getWherePart4CustomerNoForFindCallbacks(std::stringstream& ss, basar::Int32 customerNo)
{
    ss
        << " and k.kundennr = " << customerNo;
}

void CallbackSqlMapper::getWherePart4StatusForFindCallbacks(std::stringstream& ss, basar::Int16 statusNo)
{
	ss
		<< " and cbi.callbackstatusid = " << statusNo;
}

domMod::ICallbackOverviewItemPtr CallbackSqlMapper::mapCallback4Overview(basar::db::sql::ResultsetRef const resultSet)
{
    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("CallbackSqlMapper::mapCallback4Overview()", "resultSet.isNull", __FILE__, __LINE__), "");
    }

    domMod::ICallbackOverviewItemPtr callback = domMod::CallbackOverviewItemDM::create();
    CallbackOverviewItemMapper mapper(callback);

    mapper.setCallbackNo(resultSet.getInt32("callbackno"));
    mapper.setBranchNo(resultSet.getInt16("filialnr"));
    mapper.setCallbackDate(resultSet.getInt32("datum"));
    mapper.setCallbackTime(resultSet.getInt32("zeit"));
    mapper.setReasonName(resultSet.getString("callbackreason"));
    mapper.setPharmacyName(resultSet.getString("nameapo"));
    mapper.setCity(resultSet.getString("ort"));
    mapper.setCritLevel(resultSet.getInt16("kritiklevel"));
    mapper.setCallbackStatus(resultSet.getString("callbackstatusname"));
    mapper.setDivisionName(resultSet.getString("divisionname"));
    mapper.setReference(resultSet.getString("reference"));

    return callback;
}

basar::VarString const CallbackSqlMapper::getFindCallbacksCountSelectSQL(FindCallbacksRequestPtr const findCallbacksRequest, basar::VarString const& dbName)
{
    std::stringstream ss;
    ss
        << "select count('x')::int";

    getCommonFromWherePartForFindCallbacks(ss, findCallbacksRequest, dbName);

    return ss.str();
}

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

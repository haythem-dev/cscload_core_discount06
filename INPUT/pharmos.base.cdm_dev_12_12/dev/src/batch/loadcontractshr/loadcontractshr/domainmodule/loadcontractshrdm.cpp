#include "loadcontractshrdm.h"


#include <libutil/misc/metaclassmacro_definitions.h> 
#include <libutil/misc/log_macro_definitions.h>      
#include <loggerpool/loadcontractshr_loggerpool.h>
#include "domainmodule/loadcontractshr_property_definitions.h"
#include <boost/algorithm/string.hpp>
#include <libutil/exception.h>
#include <libbasarcmnutil_exceptions.h>
#include<fstream>
#include<sstream>
#include<string>
#include <iostream>
#include <time.h>
#include <stdio.h>

using namespace std;

//-----------------------------------------------------------------------------------------

namespace loadcontractshr {
namespace domMod {
namespace loadcontractshrdm {

//-----------------------------------------------------------------------------------------
	
LoadContractsHrDM::LoadContractsHrDM(const log4cplus::Logger& logger) :
	m_Logger(logger), m_SqlSelectArticleData (""),
	m_SqlPrepUpdateLoadContractsHr (""), m_SqlPrepInsertLoadContractsHr (""), m_SqlPrepUpdateRebates (""), m_Path (""), m_SqlPrepInsertGrpPfl(""),
	m_CounterContractsAdded(0), m_CounterRebatesUpdated(0), m_CounterRebatesAdded(0), m_CounterRebatesUnchanged(0), m_CounterRebatesUnchangedOutOfDate(0), m_CounterRebatesUnchangedSimilar(0), m_Counter(0), m_CounterBadFormat(0),
	m_ssBADFORMAT(""), m_ssOUTOFDATE(""), m_ssDOES_NOT_EXIST(""), m_ssMATCHING_EXISTS(""), m_ssSIMILAR_EXISTS(""), m_ssUPDATED(""), m_ssNO_MATCHING_FOUND(""), m_ssINSERTED("")
{

}

LoadContractsHrDM::~LoadContractsHrDM()
{
	if( false == m_ArticleResultSet.isNull() )
	{
		if( m_ArticleResultSet.isOpen() )
			m_ArticleResultSet.close();
		
		m_ArticleResultSet.reset();
	}

	if( false == m_StmtSelect.isNull() )
	{
		if( m_StmtSelect.isOpen() )
			m_StmtSelect.close();
		
		m_StmtSelect.reset();
	}

	if( false == m_PrepStmtUpdateRebate.isNull() )
	{
		if(m_PrepStmtUpdateRebate.isOpen() )
			m_PrepStmtUpdateRebate.close();
		
		m_PrepStmtUpdateRebate.reset();
	}

	if( false == m_PrepStmtInsertContract.isNull() )
	{
		if(m_PrepStmtInsertContract.isOpen() )
			m_PrepStmtInsertContract.close();
		
		m_PrepStmtInsertContract.reset();
	}

	if (false == m_PrepStmtInsertRebate.isNull())
	{
		if (m_PrepStmtInsertRebate.isOpen())
			m_PrepStmtInsertRebate.close();

		m_PrepStmtInsertRebate.reset();
	}
}

void LoadContractsHrDM::injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn)
{
	m_Connection = conn->getCurrentConnection().getSqlConnection();
}

void LoadContractsHrDM::createPreparedStmtInsContract( )
{
	if( m_PrepStmtInsertContract.isNull() || false == m_PrepStmtInsertContract.isOpen() )
	{
		ostringstream ss1;
		ss1 << m_NewId + 1;
		m_SqlPrepInsertLoadContractsHr.format("INSERT INTO cpromotions (promotion_no,name,description,promotion_type,addonpromodiscok,addonstddiscok,priority,snotbysaleseweb) VALUES (%s,'%s','',4,'0','0',0,'0') ", ss1.str().c_str(), m_CurrentContractNo.c_str());
		
		m_PrepStmtInsertContract = m_Connection.createPreparedStatement(m_SqlPrepInsertLoadContractsHr);

		stringstream ss;
		ss << "prepared INSERT stmt <" << m_SqlPrepInsertLoadContractsHr.c_str() << "> created";
		BLOG_INFO( m_Logger, ss.str() );
	}
}

void LoadContractsHrDM::createPreparedStmtInsZgrppflege()
{
	if (m_PrepStmtInsertGrpPfl.isNull() || false == m_PrepStmtInsertGrpPfl.isOpen())
	{
		ostringstream ss1;
		ss1 << m_NewId + 1;
		m_SqlPrepInsertGrpPfl.format("INSERT INTO ZGRPPFLEGE(key_gruppe, datum, dezap_sa) VALUES(%s, cast(to_char(current, '%s') as integer), '54'); ", ss1.str().c_str(), "%Y%m%d");

		m_PrepStmtInsertGrpPfl = m_Connection.createPreparedStatement(m_SqlPrepInsertGrpPfl);

		stringstream ss;
		ss << "prepared INSERT stmt <" << m_SqlPrepInsertGrpPfl.c_str() << "> created";
		BLOG_INFO(m_Logger, ss.str());
	}
}

void LoadContractsHrDM::createPreparedStmtUpdRebate()
{
	if (m_PrepStmtUpdateRebate.isNull() || false == m_PrepStmtUpdateRebate.isOpen())
	{
		m_SqlPrepUpdateRebates.format("UPDATE cdiscount set promotion_no = %s where articleno = %s and Pharmacygroupid = %s and dateto = %s; ", m_CurrentPromo.c_str(), m_CurrentPzn.c_str(), m_CurrentPharmacyGrpId.c_str(), m_CurrentDateTo.c_str());
		m_PrepStmtUpdateRebate = m_Connection.createPreparedStatement(m_SqlPrepUpdateRebates);
		stringstream ss;
		ss << "prepared UPDATE stmt <" << m_SqlPrepUpdateRebates.c_str() << "> created";
		BLOG_INFO(m_Logger, ss.str());
	}
}

void LoadContractsHrDM::createPreparedStmtInsRebate()
{
	if (m_PrepStmtInsertRebate.isNull() || false == m_PrepStmtInsertRebate.isOpen())
	{
		m_SqlPrepInsertLoadContractsHr.format("INSERT INTO cdiscount (articleno,discountgrpno,pharmacygroupid,customerno,baseqty,datefrom,dateto,grpdiscounttyp,discounttype,discountspec,discountqty,discountvaluepct,discountqtypct,surchargepct,pharmgrpexcluded,fixedprice,refundpct,internaldiscount,discountarticle,monthlydiscount,pharmgrpexcl_2,pharmgrpexcl_3,base_value,base_mult_std_qty,no_multiple_qty,fixeddiscountvalue,manufacturerno,artcategoryno,paymenttargetno,grossprofitpct,addondiscountok,paymenttermtype,targetqty,exceedancepct,refundtype,article_no_pack,refundvalue,promotion_no,turnovercalcimpact,maxqty,addondiscount) VALUES (%s,0,'%s',0,1,%s,%s,0,0,0,0,0.00,0.00,0.00,'000',%s,0.00,'0',0,'0','000','000',0.00,0,'0',0.00,0,0,0,0.00,'0','0',0,0.00,0,0,0.00,%s,'0',0,' ') "
			, m_CurrentPzn.c_str(), m_CurrentPharmacyGrpId.c_str(), m_CurrentDateFrom.c_str(), m_CurrentDateTo.c_str(), m_CurrentPrice.c_str(), m_CurrentPromo.c_str());

		m_PrepStmtInsertRebate = m_Connection.createPreparedStatement(m_SqlPrepInsertLoadContractsHr);

		stringstream ss;
		ss << "prepared INSERT stmt <" << m_SqlPrepInsertLoadContractsHr.c_str() << "> created";
		BLOG_INFO(m_Logger, ss.str());
	}
}

bool  LoadContractsHrDM::next(  )
{
	if (true == m_ArticleResultSet.isNull() || false == m_ArticleResultSet.isOpen() )
		return false;
	
	return m_ArticleResultSet.next();
}

void LoadContractsHrDM::run()
{
	METHODNAME_DEF(RUN, saveIfNew)
	BLOG_TRACE_METHOD(getLogger(), fun);
	try
	{
		ifstream rfile(m_Path.c_str());
		string line, word;
		string pzn, contractNo, dateFrom, dateTo, pharmacyGrpId, price;
		vector<string> vect;
		list< pair<string, int> > contracts;
		string lineStream;
		int contId;
		int currentDate;
		m_NewId = getDbInitialVars(&currentDate);
		bool isUpdateMode = m_Mode.compare("update") == 0;

		while (getline(rfile, line))
		{
			contId = 0;
			if (line.empty())
			{
				std::stringstream ss;
				ss << "#0# - [[EMPTY LINE]] detected empty line";
				BLOG_DEBUG(m_Logger, ss.str());
				continue;
			}

			m_Counter++;
			vect.clear();
			stringstream ss(line);
			while (ss.good())
			{
				string substr;
				getline(ss, substr, '|');
				vect.push_back(substr);
			}

			if (vect.size() != 6)
			{
				std::stringstream ss;
				ss << "#5# - [[TOO MANY DELIMITERS FOUND]] too many delimiters in the line were found - line begins with: " << vect.size() > 0 ? vect[0] : "";
				BLOG_DEBUG(m_Logger, ss.str());

				m_CounterBadFormat++;
				continue;
			}

			pzn = vect[0];
			contractNo = vect[1];
			dateFrom = ConvertDate(vect[2]);
			dateTo = ConvertDate(vect[3]);
			pharmacyGrpId = vect[4];
			price = vect[5];
			boost::trim(pzn);
			boost::trim(contractNo);
			boost::to_upper(contractNo);
			boost::trim(dateFrom);
			boost::trim(dateTo);
			boost::trim(pharmacyGrpId);
			boost::trim(price);

			if (contractNo.size() < 1)
			{
				std::stringstream ss;
				ss << "#8# - [[UNEXPECTED SIZE]] Unexpected contract no. size. Data of record: articleNo = "
					<< pzn << ", contractNo = " << contractNo << ", pharmacyGrpId = " << pharmacyGrpId << ", price = " << price;
				BLOG_DEBUG(m_Logger, ss.str());
				addToGrp(BADFORMAT, line);
				m_CounterBadFormat++;
				continue;
			}

			std::vector<int> pos;
			if (checkBadContractNo(contractNo, pos))
			{
				std::stringstream ss;
				ss << "#3# - [[UNEXPECTED CHARACTERS]] Found unexpected characters in the contract no. Data of record: articleNo = "
					<< pzn << ", contractNo = " << contractNo << ", pharmacyGrpId = " << pharmacyGrpId << ", price = " << price;
				BLOG_DEBUG(m_Logger, ss.str());

				std::stringstream ln, positions;
				for (std::vector<int>::iterator it = pos.begin(); it != pos.end(); ++it)
					positions << *it << " ";
				line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
				ln << line << "| Unexpected characters in contract no. at position(s) " << positions.str() << '\r';
				addToGrp(BADFORMAT, ln.str());
				m_CounterBadFormat++;
				continue;
			}

			if (pharmacyGrpId.size() > 3)
			{
				std::stringstream ss;
				ss << "#7# - [[UNEXPECTED PHARMACY GROUP ID]] Pharmacy group id has more than three characters. Data of record: articleNo = "
					<< pzn << ", contractNo = " << contractNo << ", pharmacyGrpId = " << pharmacyGrpId << ", price = " << price;
				BLOG_DEBUG(m_Logger, ss.str());
				BLOG_DEBUG(m_Logger, ss.str());
				addToGrp(BADFORMAT, line);
				m_CounterBadFormat++;
				continue;
			}

			if (pzn.empty() || contractNo.empty() || dateFrom.empty() || dateTo.empty() || pharmacyGrpId.empty() || price.empty())
			{
				std::stringstream ss;
				ss << "#4# - [[EMPTY VALUE FOUND]] Found an empty value. Data of record: articleNo ="
					<< pzn << ", contractNo = " << contractNo << ", dateFrom = " << dateFrom << ", dateTo = "
					<< dateTo << ", pharmacyGrpId = " << pharmacyGrpId << ", price = " << price;
				std::stringstream ln;
				line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
				ln << line << "| Missing value found\r";
				addToGrp(BADFORMAT, ln.str());
				m_CounterBadFormat++;
				continue;
			}

			if (price.find('.') != string::npos)
			{
				price.erase(remove(price.begin(), price.end(), '.'), price.end());
			}

			replace(price.begin(), price.end(), ',', '.');
			if (dateFrom == "0" || dateTo == "0")
			{
				std::stringstream ss;
				ss << "#2# - [[BAD FORMATTED DATE]] Could not convert dateFrom/dateTo. Data of record: articleNo ="
					<< pzn << ", contractNo = " << contractNo << ", pharmacyGrpId = " << pharmacyGrpId << ", price = " << price;
				BLOG_DEBUG(m_Logger, ss.str());
				addToGrp(BADFORMAT, line);
				m_CounterBadFormat++;
				continue;
			}

			if (!isUpdateMode)
			{
				int iDateTo = atoi(dateTo.c_str());
				if (iDateTo < currentDate)
				{
					std::stringstream ss;
					ss << "#1# - [[OUT DATED]] 'dateTo' value is out of date; deactivated rebates are not allowed to be added. Data of record: articleNo ="
						<< pzn << ", contractNo = " << contractNo << ", dateFrom = " << dateFrom << ", dateTo = "
						<< dateTo << ", pharmacyGrpId = " << pharmacyGrpId << ", price = " << price;
					BLOG_DEBUG(m_Logger, ss.str());
					addToGrp(OUTOFDATE, line);
					m_CounterRebatesUnchangedOutOfDate++;
					continue;
				}
			}

			bool exists = rebateExists(pzn, pharmacyGrpId, dateTo);

			if (!exists && isUpdateMode)
			{
				std::stringstream ss;
				ss << "[MODE:UPDATE] [[DOES NOT EXIST]] Rebate record does not exist and has not been added due to mode 'update'. Data of record: articleNo ="
					<< pzn << ", contractNo = " << contractNo << ", dateFrom = " << dateFrom << ", dateTo = "
					<< dateTo << ", pharmacyGrpId = " << pharmacyGrpId << ", price = " << price;
				BLOG_DEBUG(m_Logger, ss.str());
				addToGrp(NO_MATCHING_FOUND, line);
				m_CounterRebatesUnchanged++;
				continue;
			}

			if (exists && !isUpdateMode)
			{
				if (matchExists(pzn, pharmacyGrpId, dateTo))
				{
					std::stringstream ss;
					ss << "#9# - [[MATCHING EXISTS]] Rebate record already exists and has not been added. Data of record: articleNo ="
						<< pzn << ", contractNo = " << contractNo << ", dateFrom = " << dateFrom << ", dateTo = "
						<< dateTo << ", pharmacyGrpId = " << pharmacyGrpId << ", price = " << price;
					BLOG_DEBUG(m_Logger, ss.str());
					addToGrp(MATCHING_EXISTS, line);
					m_CounterRebatesUnchanged++;
				}
				else 
				{

					std::stringstream ss;
					ss << "#6# - [[SIMILAR ALREADY EXISTS]] Similar rebate record but with active 'dateto' already exists. Rebate record has not been added due to this. Data of record: articleNo ="
						<< pzn << ", contractNo = " << contractNo << ", dateFrom = " << dateFrom << ", dateTo = "
						<< dateTo << ", pharmacyGrpId = " << pharmacyGrpId << ", price = " << price;
					BLOG_DEBUG(m_Logger, ss.str());
					addToGrp(SIMILAR_EXISTS, line);
					m_CounterRebatesUnchangedSimilar++;
				}
				continue;
			}

			if (exists && isUpdateMode)
			{
				bool matchFound = matchExists(pzn, pharmacyGrpId, dateTo);
				if (matchFound)
				{
					contId = getContractId(contracts, contractNo);
					updateRebate(pzn, pharmacyGrpId, dateTo, contId);
					addToGrp(UPDATED, line);
					m_CounterRebatesUpdated++;
				}
				else
				{
					addToGrp(NO_MATCHING_FOUND, line);
					m_CounterRebatesUnchanged++;
				}
			}
			else
			{
				contId = getContractId(contracts, contractNo);
				addRebate(pzn, contId, dateFrom, dateTo, pharmacyGrpId, price);
				addToGrp(INSERTED, line);
				m_CounterRebatesAdded++;
			}
		}
		contracts.clear();
	}
	catch (const exception& e)
	{
		basar::VarString msg = e.what();
		throw basar::InvalidStateException(basar::ExceptInfo(fun, "Error while reading contracts data: " + msg, __FILE__, __LINE__));
	}
	catch (basar::Exception& e)
	{
		throw;
	}
	catch (...)
	{
		throw basar::InvalidStateException(basar::ExceptInfo(fun, "Error while reading contracts data.", __FILE__, __LINE__));
	}
}

void LoadContractsHrDM::addToGrp(ResultGrp grp, const string& line)
{
	switch (grp)
	{
		case NONE:
			break;
		case BADFORMAT:
			m_ssBADFORMAT << line << std::endl;
			break;
		case OUTOFDATE:
			m_ssOUTOFDATE << line << std::endl;
			break;
		case DOES_NOT_EXIST:
			m_ssDOES_NOT_EXIST << line << std::endl;
			break;
		case MATCHING_EXISTS:
			m_ssMATCHING_EXISTS << line << std::endl;
			break;
		case SIMILAR_EXISTS:
			m_ssSIMILAR_EXISTS << line << std::endl;
			break;
		case UPDATED:
			m_ssUPDATED << line << std::endl;
			break;
		case NO_MATCHING_FOUND:
			m_ssNO_MATCHING_FOUND << line << std::endl;
			break;
		case INSERTED:
			m_ssINSERTED << line << std::endl;
			break;
		default:
			break;
	}
}

bool LoadContractsHrDM::rebateExists(const string& pzn, const string& pharmacyGrpId, const string& dateTo)
{
	basar::VarString sqlSelectExistance;
	basar::db::sql::StatementRef stmtExists = m_Connection.createStatement();
	sqlSelectExistance.format("SELECT articleno, pharmacygroupid, dateto FROM cdiscount where articleno = %s and pharmacygroupid = '%s' and (dateto = %s or dateto >= cast(to_char(current, '%s') as integer)) ", pzn.c_str(), pharmacyGrpId.c_str(), dateTo.c_str(), "%Y%m%d");
	basar::db::sql::ResultsetRef existsResultSet = stmtExists.executeQuery(sqlSelectExistance);
	return existsResultSet.next();
}

bool LoadContractsHrDM::matchExists(const string& pzn, const string& pharmacyGrpId, const string& dateTo)
{
	basar::VarString sqlSelectExistance;
	basar::db::sql::StatementRef stmtExists = m_Connection.createStatement();
	sqlSelectExistance.format("SELECT articleno, pharmacygroupid, dateto FROM cdiscount where articleno = %s and pharmacygroupid = '%s' and dateto = %s ", pzn.c_str(), pharmacyGrpId.c_str(), dateTo.c_str());
	basar::db::sql::ResultsetRef existsResultSet = stmtExists.executeQuery(sqlSelectExistance);
	return existsResultSet.next();
}


bool LoadContractsHrDM::checkBadContractNo(const string& contractNo, std::vector<int>& pos)
{
	int val = 0;
	bool bcFound = false;
	for (int i = 0; i < contractNo.size(); i++)
	{
		val = contractNo[i];
		if (val > 127 || val < 0)
		{
			if (pos.size() > 0 && pos[pos.size()-1] == i)
			{
				break;
			}
			pos.push_back(i+1);
			bcFound = true;
		}
	}

	return bcFound;
}

int LoadContractsHrDM::getContractId(list< pair<string, int> >& contracts, const string& contractNo)
{
	int contId = getNoFromContractsList(contracts, contractNo);

	if (contId == 0)
		contId = getNoFromDb(contractNo);
	else
		return contId;

	if (contId == 0)
	{
		contId = createNewContract(contractNo);
		if (contId != 0)
			m_CounterContractsAdded++;
	}

	if (contId != 0)
		contracts.push_back(make_pair(contractNo, contId));

	return contId;
}

int LoadContractsHrDM::getNoFromDb(const string& contractNo)
{
	basar::VarString sqlSelectExistance;
	basar::db::sql::StatementRef stmtExists = m_Connection.createStatement();
	sqlSelectExistance.format("Select promotion_no from cpromotions where name = '%s'", contractNo.c_str());
	basar::db::sql::ResultsetRef existsResultSet = stmtExists.executeQuery(sqlSelectExistance);
	existsResultSet.next();
	return existsResultSet.getInt16(properties::PROMO_NO);
}

int LoadContractsHrDM::getDbInitialVars(int* currentDate)
{
	basar::VarString sqlSelectExistance;
	basar::db::sql::StatementRef stmtExists = m_Connection.createStatement();
	basar::db::sql::ResultsetRef existsResultSet = stmtExists.executeQuery("Select max(promotion_no), cast(to_char(current, '%Y%m%d') as integer) from cpromotions");
	existsResultSet.next();
	*currentDate = existsResultSet.getInt32(1);
	return existsResultSet.getInt16(0);
}

const string LoadContractsHrDM::ConvertDate(const string& date)
{
	vector<string> vectDate;
	stringstream ss(date);
	while (ss.good())
	{
		string substrDate;
		getline(ss, substrDate, '.');
		vectDate.push_back(substrDate);
	}

	if (vectDate.size() == 3)
	{
		return "20" + vectDate[2] + vectDate[1] + vectDate[0];
	}
	return "0";
}

int LoadContractsHrDM::getNoFromContractsList(list< pair<string, int> >& contracts, const string& contractNo)
{
	for (std::list< pair<string, int> >::iterator it = contracts.begin(); it != contracts.end(); ++it) {
		if (it->first.compare(contractNo) == 0)
			return it->second;
	}
	return 0;
}

int LoadContractsHrDM::createNewContract(const string& contractNo)
{
	m_CurrentContractNo = contractNo;
	createPreparedStmtInsContract();
	m_PrepStmtInsertContract.execute(false); // no exception due to -239
	m_PrepStmtInsertContract.close();
	m_PrepStmtInsertContract.reset();

	createPreparedStmtInsZgrppflege();
	m_PrepStmtInsertGrpPfl.execute(false);
	m_PrepStmtInsertGrpPfl.close();
	m_PrepStmtInsertGrpPfl.reset();

	m_NewId++;

	std::stringstream ss;
	ss << "new cpromotions record inserted for contract no.: " << contractNo << " having id: " << m_NewId ;
	BLOG_DEBUG(m_Logger, ss.str());

	return m_NewId;
}

void LoadContractsHrDM::updateRebate(const string& pzn, const string& pharmacyGrpId, const string& dateTo, int contId)
{
	ostringstream ssId;
	ssId << contId;
	m_CurrentPzn = pzn;
	m_CurrentPharmacyGrpId = pharmacyGrpId;
	m_CurrentDateTo = dateTo;
	m_CurrentPromo = ssId.str();
	createPreparedStmtUpdRebate();
	m_PrepStmtUpdateRebate.execute(false); // no exception due to -239
	m_PrepStmtUpdateRebate.close();
	m_PrepStmtUpdateRebate.reset();

	std::stringstream ss;
	ss << " for ARTICLENO <" << pzn;
	ss << "> cdiscount record updated";
	BLOG_DEBUG(m_Logger, ss.str());
}

void LoadContractsHrDM::addRebate(const string& pzn, int contId, const string& dateFrom, const string& dateTo, const string& purchaseGrp, const string& price)
{
	ostringstream ssId;
	ssId << contId;
	m_CurrentPzn = pzn;
	m_CurrentPharmacyGrpId = purchaseGrp;
	m_CurrentDateFrom = dateFrom;
	m_CurrentDateTo = dateTo;
	m_CurrentPrice = price;
	m_CurrentPromo = ssId.str();
	createPreparedStmtInsRebate();
	m_PrepStmtInsertRebate.execute(false); // no exception due to -239
	m_PrepStmtInsertRebate.close();
	m_PrepStmtInsertRebate.reset();

	std::stringstream ss;
	ss << " for ARTICLENO <" << pzn;
	ss << "> new cdiscount record inserted";
	BLOG_DEBUG(m_Logger, ss.str());
}

void LoadContractsHrDM::setPath(const basar::VarString path)
{
	m_Path = path;

	std::stringstream ss;
	ss << " Path set to <" << m_Path << ">";
	BLOG_INFO( m_Logger, ss.str() );
}

void LoadContractsHrDM::setMode(const basar::VarString mode)
{
	m_Mode = mode;

	std::stringstream ss;
	ss << " Mode set to <" << m_Mode << ">";
	BLOG_INFO(m_Logger, ss.str());
}

basar::VarString LoadContractsHrDM::getMode()
{
	return m_Mode;
}

basar::VarString LoadContractsHrDM::getPath( )
{
	return m_Path;
}

const log4cplus::Logger& LoadContractsHrDM::getLogger() const
{
	return m_Logger;
}

basar::Int32	LoadContractsHrDM::getCounterRebatesUpdated()
{
	return m_CounterRebatesUpdated;
}
basar::Int32	LoadContractsHrDM::getCounterRebatesAdded	( )
{
	return m_CounterRebatesAdded;
}
basar::Int32	LoadContractsHrDM::getCounterContractsAdded()
{
	return m_CounterContractsAdded;
}

basar::Int32	LoadContractsHrDM::getCounterRebatesUnchanged	( )
{
	return m_CounterRebatesUnchanged;
}

basar::Int32	LoadContractsHrDM::getCounterRebatesUnchangedOutOfDate()
{
	return m_CounterRebatesUnchangedOutOfDate;
}

basar::Int32	LoadContractsHrDM::getCounterRebatesUnchangedSimilar()
{
	return m_CounterRebatesUnchangedSimilar;
}

basar::Int32	LoadContractsHrDM::getCounter()
{
	return m_Counter;
}

basar::Int32	LoadContractsHrDM::getCounterBadFormat()
{
	return m_CounterBadFormat;
}

std::stringstream*	LoadContractsHrDM::getResult(ResultGrp grp)
{
	switch (grp)
	{
	case NONE:
		break;
	case BADFORMAT:
		return &m_ssBADFORMAT;
		break;
	case OUTOFDATE:
		return &m_ssOUTOFDATE;
		break;
	case DOES_NOT_EXIST:
		return &m_ssDOES_NOT_EXIST;
		break;
	case MATCHING_EXISTS:
		return &m_ssMATCHING_EXISTS;
		break;
	case SIMILAR_EXISTS:
		return &m_ssSIMILAR_EXISTS;
		break;
	case UPDATED:
		return &m_ssUPDATED;
		break;
	case NO_MATCHING_FOUND:
		return &m_ssNO_MATCHING_FOUND;
		break;
	case INSERTED:
		return &m_ssINSERTED;
		break;
	default:
		break;
	}
}

	
//-----------------------------------------------------------------------------------------
} 
} 
} 

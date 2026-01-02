#include <customer/customersqlmapper.h>
#include <sstream>
#include <iomanip>
#include <libbasarcmnutil_decimal.h>
#include "logger/loggerpool.h"

namespace libcsc {
namespace customer {

CustomerSqlMapper::CustomerSqlMapper(CustomerPtr customer, const basar::db::sql::ResultsetRef resultSet) :
    CustomerMapperBase(customer),
    m_ResultSet(resultSet)
{
}

CustomerSqlMapper::~CustomerSqlMapper()
{
}

const basar::VarString CustomerSqlMapper::getSelectSQL(const basar::Int16 branchNo, const basar::Int32 customerNo,
    bool withTender, bool withCreditLimit, bool withLogisticSurcharge)
{
    std::stringstream sql;
    sql << "SELECT "
                "k.filialnr AS branchno, "
                "k.idfnr AS customerno, "
                "k.nameapo AS pharmacyname, "
                "k.strasse AS street, "
                "k.postleitzahl AS postalcode, "
                "k.ort AS city, "
                "ks.skdkundeaegesperrt AS blocked, "
                "k.kdgruppe AS customergroup, "
                "k.mastercstno AS chaincustomerno, "
                "k.nameinhaber AS pharmacyowner, "
                "k.payment_term AS paymentterm, "
                "CASE k.xmlinfolevel WHEN '1' THEN 1 WHEN '2' THEN 2 WHEN '3' THEN 3 WHEN '4' THEN 4 ELSE 0 END as xmlinfolevel "
                ", k.emailadresse AS MailAddress "
                ", k.faxnr AS FaxNo "
                ", k.kzsprache AS Language "
                ", k.anredekz AS SalutationId "
                ;

    if (true == withTender)
    {
        sql <<	", case when exists(Select tenderno from tenderhead th where tenderstate not in(8, 9) and "
                "((k.filialnr = th.branchno and k.idfnr = th.customerno) or (th.pharmacychainno = k.mastercstno and k.mastercstno > 0 and th.branchno = 0 and th.customerno = 0))) "
                "then 1 else 0 end AS hastender ";
    }
    if (true == withCreditLimit)
    {
        sql << ", d.partnerno, d.limit, d.sum_debitside, d.sum_creditside, d.sum_monturnover, d.sum_dayturnover, d.sum_returns, d.sum_goodsreceipt ";
    }
    if (true == withLogisticSurcharge)
    {
        sql <<	", NVL(au.logistikaufschlag   , 0) as LogisticSurchargePct "
                ", NVL(au.logistikaufschlagmin, 0) as LogisticSurchargeMinValue "
            ;
    }

    sql <<	"FROM kunde k "
            "JOIN kundeschalter ks ON ks.vertriebszentrumnr = k.filialnr AND ks.idfnr = k.idfnr ";
    if (true == withCreditLimit)
    {
        sql <<	"JOIN debtlimit d ON k.partnernr = d.partnerno ";
    }
    if (true == withLogisticSurcharge)
    {
        sql << "LEFT JOIN kndausku au ON au.vertriebszentrumnr = k.filialnr AND au.kundennr = k.idfnr ";
    }

    sql << "WHERE k.filialnr = " << branchNo << " ";
                
    if (customerNo > 0)
    {
        sql <<	"AND k.idfnr = " << customerNo << " ";
    }
    else
    {
        //NEEDED IN CASE NO CUSTOMER NUMBER IS SET TO GET ONLY THE MAIN CUSTOMERS WITH BRANCH BACK
        sql << "AND k.originalfilialnr in (0, " << branchNo << ") ";
    }

    sql <<	"ORDER BY k.filialnr, k.idfnr;";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

void CustomerSqlMapper::doMap(int countryPhoneCode)
{
    if( m_ResultSet.isNull() )
    {
        throw;
    }

    setBranchNo			(m_ResultSet.getInt16("branchno"));
    setCustomerNo		(m_ResultSet.getInt32("customerno"));
    setPharmacyName		(m_ResultSet.getString("pharmacyname"));
    setCity				(m_ResultSet.getString("city"));
    setPostalCode		(m_ResultSet.getString("postalcode"));
    setStreet			(m_ResultSet.getString("street"));
    setPharmacyOwner	(m_ResultSet.getString("pharmacyowner"));
    setCustomerGroup	(m_ResultSet.getString("customergroup"));
    setCustomerNoChain	(m_ResultSet.getInt32("chaincustomerno"));
    setIsActive			(m_ResultSet.getString("blocked") == basar::VarString("0"));
    setXmlInfoLevel		(m_ResultSet.getInt32("xmlinfolevel"));
    setMailAddress		(m_ResultSet.getString("MailAddress"));

    // Handling FaxNo
    basar::VarString faxNo = m_ResultSet.getString("FaxNo");
    faxNo.trim(basar::cmnutil::BString::FIRST_END);

    if (faxNo.empty() ||
        faxNo.find_first_not_of(' ') == std::string::npos // Efficient way to check if std::string has only spaces:
        )
    {
        faxNo = "";
    }
    else if (countryPhoneCode > 0)
    {
        std::stringstream ss;
        ss << "00" << countryPhoneCode << faxNo.substr(1, faxNo.length() - 1);
        faxNo = ss.str().c_str();
    }
    //else --> let the faxNo unchanged...

    setFaxNo			(faxNo);

    setLanguage			(m_ResultSet.getString("Language"));
    setSalutationId		(m_ResultSet.getInt16("SalutationId"));

    //TODO: necessary for Thrift:
    //customerDetails.__set_Salutation("");               // not available! currently no concept to get the correct salutation by ANREDEKZ, Customer Language and Customer Group => TODO
    //customerDetails.__set_SalutationExtension("");      // not available! currently no concept to get the correct salutation by ANREDEKZ, Customer Language and Customer Group => TODO
    /*
    DEUTSCHLAND
    Anrede                              Kundengruppe 01 & 11
    0                   "FIRMA"
    1                   "HERR"          " APOTHEKER"
    2                   "FRL."          " APOTHEKERIN"
    3                   "FRAU"          " APOTHEKERIN"
    4                   "FIRMA"


    SCHWEIZ
    Anrede              DEFAULT         Kundensprache F
    0                   ""
    1                   "HERR"          "MONSIEUR"
    2                   "HERR/FRAU"     ""
    3                   "FRAU"          "MADAME"
    4                   "FIRMA"


    ÖSTERREICH
    Anrede
    2                   "FILIALAPOTHEKE"
    3                   "PARFUEMERIE"
    4                   "REFORMHAUS"
    5                   "APOTHEKE"
    6                   "STADTAPOTHEKE"
    7                   "ANSTALTSAPOTHEKE"
    8                   "DROGERIE"
    9                   "FIRMA"
    */
}

void CustomerSqlMapper::doMapTender()
{
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setHasTender		(m_ResultSet.getInt32("hastender") == 1);
}

void CustomerSqlMapper::doMapCreditLimit()
{
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setPartnerNo		(m_ResultSet.getInt32("partnerno"));
    setLimit			(m_ResultSet.getDecimal("limit"));
    setSumDebitSide		(m_ResultSet.getDecimal("sum_debitside"));
    setSumCreditSide	(m_ResultSet.getDecimal("sum_creditside"));
    setSumMonthTurnover	(m_ResultSet.getDecimal("sum_monturnover"));
    setSumDayTurnover	(m_ResultSet.getDecimal("sum_dayturnover"));
    setSumReturns		(m_ResultSet.getDecimal("sum_returns"));
    setSumGoodsReceipt	(m_ResultSet.getDecimal("sum_goodsreceipt"));
}

void CustomerSqlMapper::doMapLogisticSurcharge()
{
    if (m_ResultSet.isNull())
    {
        throw;
    }

    setLogisticSurchargePct		(m_ResultSet.getDecimal("LogisticSurchargePct"));
    setLogisticSurchargeMinValue(m_ResultSet.getDecimal("LogisticSurchargeMinValue"));
}


const basar::VarString CustomerSqlMapper::getUpdateCreditLimitSQL(const basar::Int32 partnerNo,
    const basar::Decimal& newLimit)
{
    std::stringstream sql;
    sql <<
        "UPDATE debtlimit "
        "SET limit = " << std::fixed << std::setprecision(2) << newLimit.toFloat64() <<
        " WHERE partnerno = " << partnerNo << ";";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

} // end namespace customer
} // end namespace libcsc


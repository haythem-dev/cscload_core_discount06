#include <customer/customerrepository.h>
#include <customer/customersqlmapper.h>
#include <customer/customer.h>
#include <customer/customercondition/customerconditionsqlmapper.h>
#include <customer/customercondition/customercondition.h>
#include <customer/tenderinfo/tenderinfosqlmapper.h>
#include <customer/tenderinfo/tenderinfo.h>
#include <customer/articleinfo/articleinfosqlmapper.h>
#include <customer/articleinfo/articleinfo.h>
#include <customer/articleinfo/articleorderinfosqlmapper.h>
#include <customer/articleinfo/articleorderinfo.h>
#include <customer/orderinfo/orderinfosqlmapper.h>
#include <customer/orderinfo/orderinfo.h>
#include <customer/orderstatus/orderstatussqlmapper.h>
#include <customer/orderstatus/orderstatussql.h>
#include <customer/orderstatus/orderstatus.h>
#include <customer/pricesanddiscounts/pricesanddiscountssqlmapper.h>
#include <customer/pricesanddiscounts/pricesanddiscountssql.h>
#include <customer/pricesanddiscounts/pricesanddiscounts.h>
#include <customer/paymentconditions/paymentconditionssqlmapper.h>
#include <customer/paymentconditions/paymentconditionssql.h>
#include <customer/paymentconditions/paymentconditions.h>
#include <customer/payments/paymentssqlmapper.h>
#include <customer/payments/paymentssql.h>
#include <customer/payments/payments.h>
#include <customer/turnover/turnoversqlmapper.h>
#include <customer/turnover/turnoversql.h>
#include <customer/turnover/turnover.h>
#include <customer/changedquantities/changedquantitiessqlmapper.h>
#include <customer/changedquantities/changedquantitiessql.h>
#include <customer/changedquantities/changedquantities.h>
#include <customer/discountaccount/discountaccountsqlmapper.h>
#include <customer/discountaccount/discountaccountsql.h>
#include <customer/discountaccount/discountaccount.h>
#include <customer/promotions/promotionssqlmapper.h>
#include <customer/promotions/promotionssql.h>
#include <customer/promotions/promotions.h>
#include <customer/routes/routessqlmapper.h>
#include <customer/routes/routessql.h>
#include <customer/routes/routes.h>
#include <customer/tours/tourssqlmapper.h>
#include <customer/tours/tourssql.h>
#include <customer/tours/tours.h>
#include <customer/tours/weektours/weektourssqlmapper.h>
#include <customer/tours/weektours/weektourssql.h>
#include <customer/tours/weektours/weektours.h>

#include <util/loggingutils.h>
#include <libbasarcmnutil_date.h>
#include <logger/loggerpool.h>
#include <parameter/branchparametergetter.h>
#include <persistence/iaccessor.h>
#include <error.hpp>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace customer {

CustomerRepository::CustomerRepository()
{
}

CustomerRepository::~CustomerRepository()
{
    m_FindAccessor.reset();
}  	

void CustomerRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

void CustomerRepository::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "CustomerRepository::injectBranchParameterGetter()");

    m_BranchParameterGetter = parameterGetter;
}

CustomerCollectionPtr CustomerRepository::findCustomer(const basar::Int16 branchNo, const basar::Int32 customerNo,
    bool withTender, bool withCreditLimit, bool withLogisticSurcharge)
{
    METHODNAME_DEF(CustomerRepository, findCustomer);

    try
    {
        // get country phone code
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            "select wert from PARAMETER "
            "where filialnr = 0 and programmname = 'KSC' and zweck = 'Phone' and parametername = 'CountryPhoneCode'; "
        );

        int countryPhoneCode = -1;
        if (resultset.next())
        {
            countryPhoneCode = resultset.getInt32("wert");
        }
        else
        {
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerSession(), fun << "(branchNo: " << branchNo << ", customerNo: " << customerNo << ", " << withTender << ", " << withCreditLimit << ", " << withLogisticSurcharge << ") country phone code is missing in DB. Using fallback!");
        }

        // get customers:
        CustomerCollectionPtr customerColl = CustomerCollectionPtr(new CustomerCollection());
        resultset = m_FindAccessor->select(
            CustomerSqlMapper::getSelectSQL(branchNo, customerNo, withTender, withCreditLimit, withLogisticSurcharge)
        );
        while (resultset.next()) // full caching
        {
            CustomerPtr customer(new Customer());
            CustomerSqlMapper mapper(customer, resultset);
            mapper.map(withTender, withCreditLimit, withLogisticSurcharge, countryPhoneCode);
            customerColl->push_back(customer);
        }
        return customerColl;
    }
    catch( basar::Exception & e)
    {
        std::stringstream s;
        s << "findCustomer: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}



CustomerConditionCollectionPtr CustomerRepository::findCustomerConditions(const basar::Int16 branchNo,
    const basar::Int32 customerNoFrom, const basar::Int32 articleNoFrom, const basar::Int32 maxPriceElements,
    const basar::Int32 customerNoFilter)
{
    try
    {
        CustomerConditionCollectionPtr coll = CustomerConditionCollectionPtr(new CustomerConditionCollection());
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            CustomerConditionSqlMapper::getSelectSQL(branchNo, customerNoFrom, articleNoFrom,
                maxPriceElements, customerNoFilter)
        );
        while (resultset.next()) // full caching
        {
            CustomerConditionPtr customerCondition(new CustomerCondition());
            CustomerConditionSqlMapper mapper(customerCondition, resultset);
            mapper.map();
            coll->push_back(customerCondition);
        }
        return coll;
    }
    catch (basar::Exception & e)
    {
        std::stringstream s;
        s << "findCustomerConditions: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}


TenderInfoCollectionPtr CustomerRepository::findTenderInfo(const basar::Int16 branchNo,
    const basar::Int32 customerNo, const basar::VarString& contractNo, const basar::Int32 articleNo)
{
    try
    {
        TenderInfoCollectionPtr coll = TenderInfoCollectionPtr(new TenderInfoCollection());
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            TenderInfoSqlMapper::getSelectSQL(branchNo, customerNo, contractNo, articleNo)
        );
        while (resultset.next()) // full caching
        {
            TenderInfoPtr tenderInfo(new TenderInfo());
            TenderInfoSqlMapper mapper(tenderInfo, resultset);
            mapper.map();
            coll->push_back(tenderInfo);
        }
        return coll;
    }
    catch (basar::Exception & e)
    {
        std::stringstream s;
        s << "findTenderInfo: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

ArticleInfoCollectionPtr CustomerRepository::findArticleInfo(const basar::Int16 branchNo,
    const basar::Int32 articleNo)
{
    try
    {
        ArticleInfoCollectionPtr coll = ArticleInfoCollectionPtr(new ArticleInfoCollection());
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            ArticleInfoSqlMapper::getSelectSQL(branchNo, articleNo)
        );
        while (resultset.next()) // full caching
        {
            ArticleInfoPtr articleInfo(new ArticleInfo());
            ArticleInfoSqlMapper mapper(articleInfo, resultset);
            mapper.map();
            coll->push_back(articleInfo);
        }

        ArticleInfoCollection::iterator iter = coll->begin();
        for (; iter != coll->end(); ++iter)
        {
            ArticleInfoPtr artInfo(*iter);
            resultset = m_FindAccessor->select(
                ArticleInfoSqlMapper::getSelectArtInfoTextSQL(artInfo->getArticleNo())
            );
            while (resultset.next()) // full caching
            {
                ArticleInfoSqlMapper mapper(artInfo, resultset);
                mapper.mapArtInfoText();
            }
        }

        return coll;
    }
    catch (basar::Exception & e)
    {
        std::stringstream s;
        s << "findArticleInfo: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

std::vector<basar::Int32> CustomerRepository::findArticleNosByPeriod(const basar::Int16& branchNo, const basar::Int32& positionsPerPage,
    const basar::Int32& articleNoFrom, const basar::Date& dateFrom, const basar::Date& dateTo, ArticleInquiryPeriodDateTypeEnum dateType)
{
    std::vector<basar::Int32> result;

    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            ArticleInfoSqlMapper::getSelectArticleNosByPeriodSQL(branchNo, positionsPerPage,
                articleNoFrom, dateFrom.getDate(), dateTo.getDate(), dateType)
        );
        while (resultset.next())
        {
            result.push_back(resultset.getInt32(0));
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findArticleNosByPeriod: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

ArticleOrderInfoPtr CustomerRepository::findArticleOrderInfo(const basar::Int16& branchNo, const basar::Int32& articleNo)
{
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            ArticleOrderInfoSqlMapper::getSelectSQL(branchNo, articleNo)
        );
        ArticleOrderInfoPtr info = ArticleOrderInfoPtr(new ArticleOrderInfo());
        if (resultset.next())
        {
            ArticleOrderInfoSqlMapper mapper(info, resultset);
            mapper.map();
        }

        return info;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findArticleOrderInfo: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

OrderInfoCollectionPtr CustomerRepository::findOrderInfo(const basar::Int16 branchNo,
    const basar::Date& orderDate, const basar::Int32 customerNo, const basar::Int32 articleNo)
{
    try
    {
        OrderInfoCollectionPtr coll = OrderInfoCollectionPtr(new OrderInfoCollection());
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            OrderInfoSqlMapper::getSelectSQL(branchNo, orderDate, customerNo, articleNo)
        );
        while (resultset.next()) // full caching
        {
            OrderInfoPtr orderInfo(new OrderInfo());
            OrderInfoSqlMapper mapper(orderInfo, resultset);
            mapper.map();
            coll->push_back(orderInfo);
        }
        return coll;
    }
    catch (basar::Exception & e)
    {
        std::stringstream s;
        s << "findOrderInfo: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

void CustomerRepository::changeCreditLimit(const basar::Int32 partnerNo, const basar::Decimal& newLimit)
{
    m_FindAccessor->execute(CustomerSqlMapper::getUpdateCreditLimitSQL(partnerNo, newLimit));
}

OrderStatusPtr CustomerRepository::findOrderStatus(
    const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Int32& orderNo, const basar::Date& orderDate)
{
    try
    {
        OrderStatusPtr orderStatus = OrderStatusPtr(new OrderStatus());

        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            OrderStatusSql::GetOrderStatusStatusFlagsQuery(branchNo, customerNo, orderNo, 0));
        if (resultset.next())
        {
            OrderStatusSqlMapper mapper(orderStatus, resultset);
            mapper.map();
            return orderStatus;
        }

        // Nothing found? Look inside archive table!
        resultset = m_FindAccessor->select(
            OrderStatusSql::GetOrderStatusStatusFlagsQuery(branchNo, customerNo, orderNo, orderDate.getDate())
        );
        if (resultset.next())
        {
            OrderStatusSqlMapper mapper(orderStatus, resultset);
            mapper.map();
            return orderStatus;
        }

        return OrderStatusPtr();
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findOrderStatus: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

PricesAndDiscountsCollectionPtr CustomerRepository::findPricesAndDiscounts(
    const basar::Int16& branchNo, const basar::Int32& customerNo)
{
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            PricesAndDiscountsSql::getPdAvailableForBranchQuery(branchNo));
        if (!resultset.next() || (resultset.getDecimal(0).toInt32() == 0))
        {
            nError err;
            err.ExternalError("", 1); // DataNotAvailableAtTheMoment
            throw err;
        }

        bool nzok = false;
        resultset = m_FindAccessor->select(
            PricesAndDiscountsSql::getCustomerNzokNoQuery(branchNo, customerNo));
        if (resultset.next())
        {
            basar::VarString nzokno = resultset.getString(0);
            if (!nzokno.empty() && (nzokno != "000000"))
            {
                nzok = true;
            }
        }
        if (!nzok)
        {
            BLOG_TRACE(LoggerPool::getLoggerSession(), "Customer has no NZOK permission.");
        }

        PricesAndDiscountsCollectionPtr result = PricesAndDiscountsCollectionPtr(new PricesAndDiscountsCollection());
        resultset = m_FindAccessor->selectDirty(
            PricesAndDiscountsSql::getPricesAndDiscountsQuery(branchNo, customerNo, nzok));
        while (resultset.next())
        {
            PricesAndDiscountsPtr pricesAndDiscounts = PricesAndDiscountsPtr(new PricesAndDiscounts());
            PricesAndDiscountsSqlMapper mapper(pricesAndDiscounts, resultset);
            mapper.map();
            result->push_back(pricesAndDiscounts);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findPricesAndDiscounts: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

PaymentsCollectionPtr CustomerRepository::findPayments(
    const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Date& dateFrom, const basar::Date& dateTo, PaymentsFilterEnum filter)
{
    try 
    {
        PaymentsCollectionPtr result = PaymentsCollectionPtr(new PaymentsCollection());
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            PaymentsSql::getPaymentsQuery(branchNo, customerNo, dateFrom.getDate(), dateTo.getDate(), filter));

        while (resultset.next())
        {
            PaymentsPtr payments = PaymentsPtr(new Payments());
            PaymentsSqlMapper mapper(payments, resultset);
            mapper.map();
            result->push_back(payments);
        }

        return result;
    }
   
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findPayments: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }

}

PaymentConditionsPtr CustomerRepository::findPaymentConditions(
    const basar::Int16& branchNo, const basar::Int32& customerNo)
{
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            PaymentConditionsSql::getPaymentConditionsQuery(branchNo, customerNo));
        if (resultset.next())
        {
            PaymentConditionsPtr paymentConditions = PaymentConditionsPtr(new PaymentConditions());
            PaymentConditionsSqlMapper mapper(paymentConditions, resultset);
            mapper.map();
            return paymentConditions;
        }

        return PaymentConditionsPtr();
    }

    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findPaymentConditions: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

TurnoverPtr CustomerRepository::findTurnover(
    const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Date& dateFrom, const basar::Date& dateTo)
{
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            TurnoverSql::GetTurnoverQuery(branchNo, customerNo, dateFrom.getDate(), dateTo.getDate()));
        if (resultset.next())
        {
            TurnoverPtr turnover = TurnoverPtr(new Turnover());
            TurnoverSqlMapper mapper(turnover, resultset);
            mapper.map();
            return turnover;
        }

        return TurnoverPtr();
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findTurnover: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

ChangedQuantitiesCollectionPtr CustomerRepository::findChangedQuantities(
    const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Int32& orderNo, const basar::Date& dateFrom, const basar::Date& dateTo)
{
    try
    {
        ChangedQuantitiesCollectionPtr result = ChangedQuantitiesCollectionPtr(new ChangedQuantitiesCollection());
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            ChangedQuantitiesSql::GetChangedQuantitiesQuery(branchNo, customerNo, orderNo, dateFrom.getDate(), dateTo.getDate()));
        while (resultset.next())
        {
            ChangedQuantitiesPtr changedQuantities = ChangedQuantitiesPtr(new ChangedQuantities());
            ChangedQuantitiesSqlMapper mapper(changedQuantities, resultset);
            mapper.map();
            result->push_back(changedQuantities);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findChangedQuantities: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

DiscountAccountPtr CustomerRepository::findDiscountAccount(
    const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Date& dateFrom, const basar::Date& dateTo, const bool& accNatRebateGroup)
{
    basar::Int32 customerNo_ = customerNo;
    bool accNatRebateGroup_ = false;

    try
    {
        if (accNatRebateGroup)
        {
            basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
                DiscountAccountSql::getDaGroupNoQuery(branchNo, customerNo));
            if (resultset.next())
            {
                const basar::Int32 maincstno = resultset.getInt32(0);
                if (maincstno > 0)
                {
                    customerNo_ = maincstno;
                    accNatRebateGroup_ = true;
                }
            }
        }

        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            DiscountAccountSql::getDiscountAccountQuery(branchNo, customerNo_, dateFrom.getDate(), dateTo.getDate(), accNatRebateGroup_));
        if (resultset.next())
        {
            DiscountAccountPtr discountAccount = DiscountAccountPtr(new DiscountAccount());
            DiscountAccountSqlMapper mapper(discountAccount, resultset);
            mapper.map();
            return discountAccount;
        }

        return DiscountAccountPtr();
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findDiscountAccount: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

PromotionsCollectionPtr CustomerRepository::findPromotions(
    const basar::Int16& branchNo, const basar::Int32& customerNo)
{
    try
    {
        basar::Int32 today = basar::Date::getCurrent().getDate();

        PromotionsCollectionPtr result = PromotionsCollectionPtr(new PromotionsCollection());
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            PromotionsSql::GetPromotionsQuery(branchNo, customerNo, today));
        while (resultset.next())
        {
            PromotionsPtr promotions = PromotionsPtr(new Promotions());
            PromotionsSqlMapper mapper(promotions, resultset);
            mapper.map();
            result->push_back(promotions);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findPromotions: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

RoutesCollectionPtr CustomerRepository::findRoutes(
    const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Int16& weekday)
{
    try
    {
        basar::Int32 today = basar::Date::getCurrent().getDate();

        RoutesCollectionPtr result = RoutesCollectionPtr(new RoutesCollection());
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            RoutesSql::GetRoutesQuery(branchNo, customerNo, weekday, today));
        while (resultset.next())
        {
            RoutesPtr routes = RoutesPtr(new Routes());
            RoutesSqlMapper mapper(routes, resultset);
            mapper.map();
            result->push_back(routes);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findRoutes: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

std::vector<std::string> CustomerRepository::findTours(
    const basar::Int16& branchNo, const basar::Int32& tourDate)
{
    try
    {
        
        
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            ToursSql::getToursQuery(branchNo, tourDate));

        std::vector<std::string> tourIds;
        while (resultset.next())
        {
            const basar::VarString tourid = resultset.getString("tourid");            
            tourIds.push_back(tourid);
        }

        return tourIds;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findTours: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

ToursCollectionPtr CustomerRepository::findCustomerToursInfo(
    const basar::Int16& branchNo, const basar::Int32& tourDate, const std::vector<std::string>& tourIds)
{
    METHODNAME_DEF(CustomerRepository, findCustomerToursInfo);
    try
    {
        basar::VarString dbNameWarehouse = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);
        if (dbNameWarehouse.empty())
        {           
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerSession(), fun << "Name for Warehouse DB not found!");
            ToursCollectionPtr errCaseRetEmptyColl = boost::make_shared<ToursCollection>();
            return errCaseRetEmptyColl;
        }


        ToursCollectionPtr result = ToursCollectionPtr(new ToursCollection());
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            ToursSql::getCustomerToursInfoQuery(branchNo, tourDate, tourIds, dbNameWarehouse));
        while (resultset.next())
        {
            ToursPtr tour = ToursPtr(new Tours());
            ToursSqlMapper mapper(tour, resultset);
            mapper.map();
            result->push_back(tour);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findRoutes: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

WeekToursCollectionPtr CustomerRepository::findCustomerToursForWeek(const basar::Int16& branchNo, const basar::Int32& customerNo)
{
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(
            WeekToursSql::getAllCustomerToursForWeekQuery(branchNo, customerNo));
        WeekToursCollectionPtr result = WeekToursCollectionPtr(new WeekToursCollection());
        while (resultset.next())
        {
            WeekToursPtr tour = WeekToursPtr(new WeekTours());
            WeekToursSqlMapper mapper(tour, resultset);
            mapper.map();
            result->push_back(tour);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "findCustomerToursForWeek: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

} // end namespace customer
} // end namespace libcsc

#include "cscservicehelper.h"
#include <error.hpp>
#include <pxbase/pxconstants.hpp>
#include <pxxmit.hpp>
#include <pxbranch.hpp>
#include <pxorder.hpp>
#include <pxitem.hpp>
#include <pxartbas.hpp>
#include <pxcstbas.hpp>
#include <pxoeparm.hpp>
#include <tourinfo.hpp>
#include <tourmanager.hpp>
#include <tourassignmentutil.hpp>

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_datetime.h>
#include <customerhandlerptr.h>
#include <customerhandler.h>


namespace csc {
namespace service {

csc::base::ReturnStruct Helper::getReturnStructFromError(const nError& error)
{
    csc::base::ReturnStruct retVal;
    basar::VarString    msg     = error.ErrorMsg();
    int32_t             code    = error.ErrorNumber();

    msg.trim(basar::VarString::END);
    if (code > 100000)
    {
        code /= 100;
    }

    retVal.__set_ErrorMessage(msg);
    retVal.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(code));
    return retVal;
}


/*****************************************************************************/
/* versorgen Tourinformationen in Übergabestruktur                           */
/*****************************************************************************/
csc::order::TourInformation Helper::getPositionDeliveryInformation(
    pxOrderItem* orderitem, // TODO make const
    const bool isAvailabilityRequest /*= false*/ )
{
    csc::order::TourInformation info;

    if (NULL == orderitem->ArtBase() || false == orderitem->ArtBase()->IsGoodState())
        return info;

    TourInfo* ti = orderitem->getItemTourInformation();
    if (true == ti->getTourFound())
    {
        info.__set_TourId(ti->getTourID()());
        info.__set_TourDate(Helper::getCscDateFromNDate(ti->getTourDate()));
        info.__set_TourDepartureDate(Helper::getCscDateTimeFromNDate(ti->getTourDepartureDateTimeNormalized()));
        info.__set_DeliveryDate(Helper::getCscDateTimeFromNDate(ti->getCustomerDeliveryDateTimeMin()));
        info.__set_DeliveryTimeBuffer(ti->getDeliveryTimeBuffer());
        info.__set_ActTourClosingDate(Helper::getCscDateTimeFromNDate(ti->getTourClosingDateTime()));
    }
    if (orderitem->TotalIBTQuantity() > 0 || (isAvailabilityRequest && orderitem->MengeMoeglich() > 0))
    {
        ti = orderitem->getItemTourInformation(true);
        if (true == ti->getTourFound())
        {
            info.__set_TourIdIbt(ti->getTourID()());
            info.__set_TourDateIbt(Helper::getCscDateFromNDate(ti->getTourDate()));
            info.__set_TourDepartureDateIbt(Helper::getCscDateTimeFromNDate(ti->getTourDepartureDateTimeNormalized()));
            info.__set_DeliveryDateIbt(Helper::getCscDateTimeFromNDate(ti->getCustomerDeliveryDateTimeMin()));
            info.__set_DeliveryTimeBufferIbt(ti->getDeliveryTimeBuffer());
            info.__set_IbtType(ti->getIBTType());
        }
    }
    return info;
}

/*****************************************************************************/
/* versorgen Tourinformationen in Übergabestruktur auf Orderebene            */
/*****************************************************************************/
csc::order::TourInformation Helper::getOrderDeliveryInformation(
    pxOrder* order) // TODO make const
{
    csc::order::TourInformation info;

    TourInfo* ti = order->getTourInformation();
    if (ti->getTourFound())
    {
        info.__set_TourId(ti->getTourID()());
        info.__set_TourDate(Helper::getCscDateFromNDate(ti->getTourDate()));
        info.__set_TourDepartureDate(Helper::getCscDateTimeFromNDate(ti->getTourDepartureDateTimeNormalized()));
        info.__set_DeliveryDate(Helper::getCscDateTimeFromNDate(ti->getCustomerDeliveryDateTimeMin()));
        info.__set_DeliveryTimeBuffer(ti->getDeliveryTimeBuffer());
        info.__set_ActTourClosingDate(Helper::getCscDateTimeFromNDate(ti->getTourClosingDateTime()));
    }

    TourInfo fti = order->getTourAssignmentUtil()->getTourManager()->determineFollowingTour(ti);
    if (fti.getTourFound())
    {
        info.__set_NextTourClosingDate(Helper::getCscDateTimeFromNDate(fti.getTourClosingDateTime()));
        info.__set_NextTourDeliveryDate(Helper::getCscDateTimeFromNDate(fti.getCustomerDeliveryDateTimeMin()));
    }
    return info;
}

void Helper::getPriceInformation(
    csc::order::OrderPositionResponse& response,
    pxOrderItem* orderitem) // TODO make const
{
    response.ArticleDelivered.__set_PricePharmacyPurchase(orderitem->PreisEKApo());
    response.__set_PricePharmacyPurchase(orderitem->PreisEKApo());
    //response.__set_PriceInvoice(orderitem->PreisFaktur());     // Rabattierter Preis TODO FN orderitem->InvoiceValue() ????
    response.__set_PriceInvoice(orderitem->InvoiceValue());    // Rabattierter Preis

    if (orderitem->PreisEKApoNetto() > nMoney(0.0))
    {
        response.__set_PriceCustomerPurchase(orderitem->PreisEKApoNetto());
        response.ArticleDelivered.__set_PriceCustomerPurchase(orderitem->PreisEKApoNetto());
    }
    else
    {
        response.__set_PriceCustomerPurchase(orderitem->PreisEKApo());
        response.ArticleDelivered.__set_PriceCustomerPurchase(orderitem->PreisEKApo());
    }
    response.__set_PriceBase(orderitem->BasePrice());
    response.__set_Margin(orderitem->getMarginGepAep());

    double dLegallPrice = (double)orderitem->GetLegallBreizhPrice();
    if (dLegallPrice > pxConstants::dZero)
    {
        response.__set_PricePharmacyPurchase(dLegallPrice);
        response.__set_PriceCustomerPurchase(dLegallPrice);
        response.ArticleDelivered.__set_PricePharmacyPurchase(dLegallPrice);
        response.ArticleDelivered.__set_PriceCustomerPurchase(dLegallPrice);
    }

    response.__set_PricePurchase(orderitem->PreisEKGrosso());
    // TODO FN check if we are in EndProforma
    if (orderitem->DiscountValPctProforma() > pxConstants::dZero) // Proforma order
    {
        response.__set_DiscountValuePct(orderitem->DiscountValPctProforma());
    }
    else
    {
        response.__set_DiscountValuePct(orderitem->GetDiscountValuePct());
    }
    response.__set_PricePharmacySell(orderitem->getPharmacySellPrice());
    response.ArticleDelivered.__set_PricePharmacySell(orderitem->getPharmacySellPrice());

    if (orderitem->Session()->isFrance() || orderitem->Session()->isFrancePrewhole())
    {
        nMoney lppr = orderitem->ReimbursementPrice(orderitem->ArtikelNr(), '2');
        response.__set_PriceLppr(lppr);
        response.ArticleDelivered.__set_PriceLppr(lppr);

        nMoney tfr = orderitem->ReimbursementPrice(orderitem->ArtikelNr(), '1');
        response.__set_PriceTfr(tfr);
        response.ArticleDelivered.__set_PriceTfr(tfr);
    }

    if (orderitem->Session()->isSwitzerland())
    {
        if (orderitem->PreisAGP() != pxConstants::mZero)
        {
            response.__set_PriceBaseAmedis(orderitem->PreisAGP());
        }
        else // fallback:
        {
            response.__set_PriceBaseAmedis(orderitem->PreisEKGrosso());
        }
    }

    response.__set_TaxRate(orderitem->SalesTaxRate());

    response.__set_QuantityDelivered(orderitem->MengeGeliefert());
    response.__set_QuantityNatra(orderitem->MengeNatra());
}


int32_t Helper::getIntTimeFromCscDateTime(const csc::base::DateTime& datetime)
{
    return datetime.Hour * 10000 + datetime.Minute * 100 + datetime.Second;
}

int32_t Helper::getIntDateFromCscDateTime(const csc::base::DateTime& datetime)
{
    return datetime.Year * 10000 + datetime.Month * 100 + datetime.Day;
}

int32_t Helper::getIntDateFromCscDate(const csc::base::Date& date)
{
    return date.Year * 10000 + date.Month * 100 + date.Day;
}

basar::Date Helper::getBasarDateFromCscDate(const csc::base::Date& date)
{
    return basar::Date(date.Year, date.Month, date.Day);
}

csc::base::DateTime Helper::getCscDateTimeFromInt(const int32_t date, const int32_t time)
{
    csc::base::DateTime dt;
    dt.__set_Year(static_cast<int16_t>(date / 10000));
    dt.__set_Month(static_cast<int16_t>((date / 100) % 100));
    dt.__set_Day(static_cast<int16_t>(date % 100));
    dt.__set_Hour(static_cast<int16_t>(time / 10000));
    dt.__set_Minute(static_cast<int16_t>((time / 100) % 100));
    dt.__set_Second(static_cast<int16_t>(time % 100));
    return dt;
}

csc::base::DateTime Helper::getCscDateTimeFromCscDateTime(const basar::DateTime& datetime)
{
    csc::base::DateTime dt;
    dt.__set_Year(datetime.getYear());
    dt.__set_Month(datetime.getMonth());
    dt.__set_Day(datetime.getDay());
    dt.__set_Hour(datetime.getHour());
    dt.__set_Minute(datetime.getMinute());
    dt.__set_Second(datetime.getSec());
    return dt;
}

csc::base::Date Helper::getCscDateFromIntDate(const int32_t date)
{
    csc::base::Date d;
    d.__set_Year(static_cast<int16_t>(date / 10000));
    d.__set_Month(static_cast<int16_t>((date / 100) % 100));
    d.__set_Day(static_cast<int16_t>(date % 100));
    return d;
}

csc::base::Time Helper::getCscTimeFromInt(const int32_t time)
{
    csc::base::Time t;
    t.__set_Hour(static_cast<int16_t>(time / 10000));
    t.__set_Minute(static_cast<int16_t>((time / 100) % 100));
    t.__set_Second(static_cast<int16_t>(time % 100));
    return t;
}

csc::base::Date Helper::getCscDateFromNDate(const nDate& date)
{
    csc::base::Date dt;
    dt.__set_Year(static_cast<int16_t>(date.GetYear()));
    dt.__set_Month(static_cast<int16_t>(date.GetMonth()));
    dt.__set_Day(static_cast<int16_t>(date.GetDay()));
    return dt;
}

csc::base::Date Helper::getCscDateFromBasarDate(const basar::Date& date)
{
    csc::base::Date dt;
    dt.__set_Year(date.getYear());
    dt.__set_Month(date.getMonth());
    dt.__set_Day(date.getDay());
    return dt;
}


csc::base::DateTime Helper::getCscDateTimeFromNDate(const nDate& date)
{
    csc::base::DateTime dt;
    dt.__set_Year   (static_cast<int16_t>(date.GetYear()));
    dt.__set_Month  (static_cast<int16_t>(date.GetMonth()));
    dt.__set_Day    (static_cast<int16_t>(date.GetDay()));
    dt.__set_Hour   (static_cast<int16_t>(date.GetHours()));
    dt.__set_Minute (static_cast<int16_t>(date.GetMinutes()));
    dt.__set_Second (static_cast<int16_t>(date.GetSeconds()));
    return dt;
}

csc::base::ReturnStruct Helper::checkBranch(pxOrderTransmitPtr session, const basar::Int16 branchNo)
{
    if (session.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo("Thrift Helper::checkBranch()", "session is Null!", __FILE__, __LINE__), "");
    }

    if (session->Branch()->FilialNr() != branchNo)
    {
        pxBranch CustBranch(session.get(), branchNo);
        if (CustBranch.IsGoodState())
        {
            *(session->Branch()) = CustBranch;
        }
        else
        {
            return Helper::getReturnStructFromError(CustBranch);
        }
    }
    return Helper::getReturnStructFromError(nError());
}

csc::base::ReturnStruct Helper::checkBranchAndCustomer(pxOrderTransmitPtr session, const basar::Int16 branchNo, const basar::Int32 customerNo)
{
    csc::base::ReturnStruct branchCheckResult = Helper::checkBranch(session, branchNo);
    if (branchCheckResult.ErrorCode != nError().ErrorNumber())
    {
        return branchCheckResult;
    }

    pxCustBase pxcustomer(session.get(), branchNo, customerNo);

    if (!pxcustomer.IsGoodState())
    {
        return Helper::getReturnStructFromError(pxcustomer);
    }

    return branchCheckResult; //NOTE: at this line the "branchCheckResult" contains OK inside!
}

csc::base::CustomerDetails Helper::getCustomerDetails(pxOrderTransmitPtr session, const basar::Int16 branchNo, const basar::Int32 customerNo)
{
    csc::base::CustomerDetails customerDetails;

    if (branchNo > 0 && customerNo > 0)
    {
        CustomerHandler customerHandler;
        customerHandler.injectSession(session);

        ::csc::customer::CustomerDetailsResponse response;

        customerHandler.findCustomerDetails(response, branchNo, customerNo, false, false, false);

        if (response.__isset.Customers && response.Customers.size() > 0)
        {
            //return response.Customers.front(); == ERR. Reason: csc::customer::CustomerDetails <== vs. ==> csc::base::CustomerDetails
            csc::customer::CustomerDetails firstCustomer = response.Customers.front();

            if (firstCustomer.__isset.BranchNo)            { customerDetails.__set_BranchNo(firstCustomer.BranchNo); }
            if (firstCustomer.__isset.CustomerNo)          { customerDetails.__set_CustomerNo(firstCustomer.CustomerNo); }
            if (firstCustomer.__isset.PharmacyName)        { customerDetails.__set_PharmacyName(firstCustomer.PharmacyName); }
            if (firstCustomer.__isset.Salutation)          { customerDetails.__set_Salutation(firstCustomer.Salutation); }
            if (firstCustomer.__isset.OwnerName)           { customerDetails.__set_OwnerName(firstCustomer.OwnerName); }
            if (firstCustomer.__isset.CustomerAddress)     { customerDetails.__set_CustomerAddress(firstCustomer.CustomerAddress); }
            if (firstCustomer.__isset.MailAddress)         { customerDetails.__set_MailAddress(firstCustomer.MailAddress); }
            if (firstCustomer.__isset.FaxNo)               { customerDetails.__set_FaxNo(firstCustomer.FaxNo); }
            if (firstCustomer.__isset.Language)            { customerDetails.__set_Language(firstCustomer.Language); }
            if (firstCustomer.__isset.SalutationId)        { customerDetails.__set_SalutationId(firstCustomer.SalutationId); }
            if (firstCustomer.__isset.SalutationExtension) { customerDetails.__set_SalutationExtension(firstCustomer.SalutationExtension); }
            if (firstCustomer.__isset.CustomerGroup)       { customerDetails.__set_CustomerGroup(firstCustomer.CustomerGroup); }
            if (firstCustomer.__isset.TelephoneNo)         { customerDetails.__set_TelephoneNo(firstCustomer.TelephoneNo); }
        }
    }

    return customerDetails;
}

csc::base::BranchDetails Helper::getBranchDetails(pxOrderTransmitPtr session, const basar::Int16 branchNo)
{
    csc::base::BranchDetails branchDetails;
    pxBranch pxbranch(session.get(), branchNo);
    if (pxbranch.IsGoodState())
    {
        basar::VarString tmp;
        branchDetails.__set_BranchNo(pxbranch.FilialNr());

        tmp = pxbranch.Bezeichnung()();
        tmp.trim(basar::VarString::FIRST_END);
        branchDetails.__set_BranchName(tmp);

        csc::base::Address address;
        tmp = pxbranch.Strasse()();
        tmp.trim(basar::VarString::FIRST_END);
        address.__set_Street(tmp);

        tmp = pxbranch.Postleitzahl()();
        tmp.trim(basar::VarString::FIRST_END);
        address.__set_PostalCode(tmp);

        tmp = pxbranch.Ort()();
        tmp.trim(basar::VarString::FIRST_END);
        address.__set_City(tmp);
        branchDetails.__set_BranchAddress(address);
    }
    return branchDetails;
}

csc::types::LanguageEnum::type Helper::getLanguageEnumByString(const basar::VarString& language)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "Helper::getLanguageEnumByString()");

    if ("DE" == language)   return csc::types::LanguageEnum::German;
    if ("EN" == language)   return csc::types::LanguageEnum::English;
    if ("FR" == language)   return csc::types::LanguageEnum::French;
    if ("HR" == language)   return csc::types::LanguageEnum::Croatian;
    if ("I" == language)    return csc::types::LanguageEnum::Italian;

    return csc::types::LanguageEnum::UnknownLanguage;
}


} // namespace service
} // namespace csc

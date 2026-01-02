#ifndef GUARD_CSCSERVICE_HELPER_H
#define GUARD_CSCSERVICE_HELPER_H

#include "cscbase_types.h"
#include "cscorder_types.h"
#include <libbasar_definitions.h>
#include <pxordertransmitptr.h>


class nError;
class nDate;
class pxOrder;
class pxOrderItem;

namespace csc {
namespace service {

class Helper
{
public:
	static csc::base::ReturnStruct getReturnStructFromError(const nError& error);

	static csc::order::TourInformation getPositionDeliveryInformation(
		pxOrderItem* orderitem, // TODO make const
		const bool isAvailabilityRequest = false);

	static csc::order::TourInformation getOrderDeliveryInformation(pxOrder* order); // TODO make const

	static void getPriceInformation(
		csc::order::OrderPositionResponse& _return,
		pxOrderItem* orderitem); // TODO make const

    static int32_t getIntTimeFromCscDateTime(const csc::base::DateTime& datetime);

    static int32_t getIntDateFromCscDateTime(const csc::base::DateTime& datetime);

	static int32_t getIntDateFromCscDate(const csc::base::Date& date);

	static basar::Date getBasarDateFromCscDate(const csc::base::Date& date);

    static csc::base::DateTime getCscDateTimeFromInt(const int32_t date, const int32_t time);
    
    static csc::base::DateTime getCscDateTimeFromCscDateTime(const basar::DateTime& datetime);

	static csc::base::Time getCscTimeFromInt(const int32_t time);

	static csc::base::Date getCscDateFromIntDate(const int32_t date);

	static csc::base::Date getCscDateFromNDate(const nDate& date);

	static csc::base::Date getCscDateFromBasarDate(const basar::Date& date);

	static csc::base::DateTime getCscDateTimeFromNDate(const nDate& date);

	static csc::base::ReturnStruct checkBranch(pxOrderTransmitPtr session, const basar::Int16 branchNo);

	static csc::base::ReturnStruct checkBranchAndCustomer(pxOrderTransmitPtr session, const basar::Int16 branchNo, const basar::Int32 customerNo);

	static csc::base::CustomerDetails getCustomerDetails(pxOrderTransmitPtr session, const basar::Int16 branchNo, const basar::Int32 customerNo);

	static csc::base::BranchDetails getBranchDetails(pxOrderTransmitPtr session, const basar::Int16 branchNo);

	static csc::types::LanguageEnum::type getLanguageEnumByString(const basar::VarString& r);

};

} // namespace service
} // namespace csc

#endif // GUARD_CSCSERVICE_HELPER_HPP

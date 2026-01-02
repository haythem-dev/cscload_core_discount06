#include "inquirybulkhandler.h"
#include "cscservicehelper.h"
#include "cscmsv3_constants.h"

#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include <stockbooking/componentmanager/stockbookingcomponentmanager.h>
#include <stockbooking/bulkrangeselector/ibulkrangeselectorptr.h>
#include <stockbooking/bulkrangeselector/ibulkrangeselector.h>
#include <pxxmit.hpp>
#include <pxbranch.hpp>
#include <pxstockbulkinquiry.hpp>
#include <pxstockbooking.hpp>
#include <pxarticlecharge.hpp>
#include <pxartbas.hpp>
#include <pxarticlecodes.hpp>
#include <pxartreservation.hpp>

namespace csc {
namespace service {

InquiryBulkHandler::InquiryBulkHandler()
{
}

InquiryBulkHandler::~InquiryBulkHandler()
{
}

//-----------------------------------------------------------------------------
// bulk availability
//-----------------------------------------------------------------------------
void InquiryBulkHandler::processArticleAvailabilityBulk(
	inquiry::ArticleAvailabilityBulkResponse& _return,
	const inquiry::ArticleAvailabilityBulkRequest& request)
{
	csc::base::ReturnStruct branchCheckResult = Helper::checkBranch(getSession(), request.BranchNo);
	if (branchCheckResult.ErrorCode != nError().ErrorNumber())
	{
		_return.__set_RetValue(branchCheckResult);
		return;
	}

	pxStockBulkInquiry bulkInquiry(getSession().get());

	bulkInquiry.setBranchAndCustomer(request.BranchNo, request.CustomerNo);
	if (false == bulkInquiry.IsGoodState())
	{
		_return.__set_RetValue(Helper::getReturnStructFromError(bulkInquiry));
		return;
	}

	inquiry::ArticleAvailabilityPositionResponseList positions;
	for (std::vector<std::string>::const_iterator it = request.Positions.begin(); it != request.Positions.end(); ++it )
	{
		const std::string& code = *it;

		csc::inquiry::ArticleAvailabilityPositionResponse pos;
		pos.__set_ArticleCode(code);
		pos.__set_Available(bulkInquiry.getArticleAvailabilitySingle(code));

		positions.push_back(pos);
	}

	_return.__set_BranchNo(request.BranchNo);
	if (request.__isset.CustomerNo)
		_return.__set_CustomerNo(request.CustomerNo);
	_return.__set_Positions(positions);
	_return.__set_RetValue(Helper::getReturnStructFromError(bulkInquiry));
}

//-----------------------------------------------------------------------------
// bulk availability (range)
//-----------------------------------------------------------------------------
bool sortByArticleCode(const std::string& lhs, const std::string& rhs)
{
	try
	{
		int64_t lhsInt = boost::lexical_cast<int64_t>(lhs);
		int64_t rhsInt = boost::lexical_cast<int64_t>(rhs);
		return lhsInt < rhsInt;
	}
	catch (...)
	{
	}
	return lhs < rhs;
}

void InquiryBulkHandler::processArticleAvailabilityBulkRange(
	inquiry::ArticleAvailabilityBulkRangeResponse& _return,
	const inquiry::ArticleAvailabilityBulkRangeRequest& request)
{
	csc::base::ReturnStruct branchCheckResult = Helper::checkBranch(getSession(), request.BranchNo);
	if (branchCheckResult.ErrorCode != nError().ErrorNumber())
	{
		_return.__set_RetValue(branchCheckResult);
		return;
	}

	// determine all articles between request.ArticleNoRangeBegin, request.ArticleNoRangeEnd
	std::vector<std::string> availableArticles;
	libcsc::stockbooking::IBulkRangeSelectorPtr selector = getSession()->getStockBookingComponentManager()->getBulkRangeSelector();
	selector->bulkRangeAvailability(
		request.BranchNo,
		request.ArticleCodeRangeBegin,
		request.ArticleCodeRangeEnd,
		availableArticles);

	std::sort(availableArticles.begin(), availableArticles.end(), sortByArticleCode);

	_return.__set_AvailableArticles(availableArticles);

	_return.__set_BranchNo(request.BranchNo);
	if (request.__isset.CustomerNo)
		_return.__set_CustomerNo(request.CustomerNo);
	_return.__set_ArticleCodeRangeBegin(request.ArticleCodeRangeBegin);
	_return.__set_ArticleCodeRangeEnd(request.ArticleCodeRangeEnd);
	_return.__set_RetValue(Helper::getReturnStructFromError(nError()));
}


//-----------------------------------------------------------------------------
// bulk article stock
//-----------------------------------------------------------------------------
void InquiryBulkHandler::processArticleStockBulk(
	inquiry::ArticleStockBulkResponse& _return,
	const inquiry::ArticleStockBulkRequest& request)
{
	csc::base::ReturnStruct branchCheckResult = Helper::checkBranch(getSession(), request.BranchNo);
	if (branchCheckResult.ErrorCode != nError().ErrorNumber())
	{
		_return.__set_RetValue(branchCheckResult);
		return;
	}
	if (request.__isset.ArticleCodeRangeBegin && request.__isset.ArticleCodeRangeEnd)
	{
		processArticleStockBulkRange(_return, request);
		return;
	}

	pxStockBulkInquiry bulkInquiry(getSession().get());

	bulkInquiry.setBranchAndCustomer(request.BranchNo, request.CustomerNo);
	if (false == bulkInquiry.IsGoodState())
	{
		_return.__set_RetValue(Helper::getReturnStructFromError(bulkInquiry));
		return;
	}

	inquiry::ArticleStockPositionResponseList positions;
	for (std::vector<std::string>::const_iterator it = request.Positions.begin(); it != request.Positions.end(); ++it )
	{
		const std::string& code = *it;

		if (true == request.__isset.GetBatchAndExpiryDate && true == request.GetBatchAndExpiryDate)
		{
			pxArticleChargeList* batchList = bulkInquiry.getArticleStockBatchSingle(code);
			pxArticleChargeListIter iter(*batchList);
			pxArticleCharge* entry;

			while ((entry = (pxArticleCharge*) ++iter) != NULL)
			{
				inquiry::ArticleStockPositionResponse pos;
				pos.__set_ArticleCode(code);
				pos.__set_Quantity(entry->Stock());
				pos.__set_Batch(entry->ChargenNr());
				pos.__set_ExpiryDate(entry->ExpiryDate().getDate());
				pos.__set_BatchStatus(static_cast<csc::types::BatchStatusEnum::type>(entry->StateCharge()));
				positions.push_back(pos);
			}
		}
		else
		{
			inquiry::ArticleStockPositionResponse pos;
			pos.__set_ArticleCode(code);
			pos.__set_Quantity(bulkInquiry.getArticleStockSingle(code));
			positions.push_back(pos);
		}
	}

	_return.__set_BranchNo(request.BranchNo);
	if (request.__isset.CustomerNo)
		_return.__set_CustomerNo(request.CustomerNo);
	_return.__set_Positions(positions);
	_return.__set_RetValue(Helper::getReturnStructFromError(bulkInquiry));
}

void InquiryBulkHandler::processArticleStockBulkRange(
	csc::inquiry::ArticleStockBulkResponse& _return,
	const csc::inquiry::ArticleStockBulkRequest& request)
{
	// determine all articles between request.ArticleNoRangeBegin, request.ArticleNoRangeEnd
	std::vector<libcsc::stockbooking::ReturnArticles> availableArticles;
	libcsc::stockbooking::IBulkRangeSelectorPtr selector = getSession()->getStockBookingComponentManager()->getBulkRangeSelector();
	
	// Calls specific selector for Serbia
	if(getSession()->isSerbia())
	{
		selector->bulkRangeStockAC(
			request.BranchNo,
			request.ArticleCodeRangeBegin,
			request.ArticleCodeRangeEnd,
			availableArticles,
			(request.__isset.GetBatchAndExpiryDate && true == request.GetBatchAndExpiryDate)
		);
	}
	else
	{
	selector->bulkRangeStock(
		request.BranchNo,
		request.ArticleCodeRangeBegin,
		request.ArticleCodeRangeEnd,
		availableArticles,
		(request.__isset.GetBatchAndExpiryDate && true == request.GetBatchAndExpiryDate)
	);
	}

	inquiry::ArticleStockPositionResponseList positions;
	for (std::vector<libcsc::stockbooking::ReturnArticles>::const_iterator it = availableArticles.begin(); it != availableArticles.end(); ++it)
	{
		inquiry::ArticleStockPositionResponse pos;
		pos.__set_ArticleCode((*it).ArticleCode_);
		pos.__set_Quantity((*it).Quantity_);
		pos.__set_Batch((*it).Batch_);
		if (request.__isset.GetBatchAndExpiryDate && true == request.GetBatchAndExpiryDate)
		{
			pos.__set_ExpiryDate((*it).ExpiryDate_);
		}
		positions.push_back(pos);
	}

	_return.__set_BranchNo(request.BranchNo);
	_return.__set_Positions(positions);
	_return.__set_RetValue(Helper::getReturnStructFromError(nError()));
}


//-----------------------------------------------------------------------------
// bulk article details (with reservation info etc.)
//-----------------------------------------------------------------------------
void InquiryBulkHandler::processArticleStockDetails(
	::csc::inquiry::ArticleStockDetailsResponse& _return,
	const  ::csc::inquiry::ArticleStockDetailsRequest& request)
{
	pxStockBulkInquiry bulkInquiry(getSession().get());

	csc::inquiry::ArticleStockDetailInfoList list;
	csc::inquiry::ArticleStockDetailsRequestDataList::const_iterator it = request.RequestDataList.begin();
	while (it != request.RequestDataList.end())
	{
		csc::inquiry::ArticleStockDetailInfo info;
		csc::inquiry::ArticleStockDetailsRequestData requestArticle = (*it);
		bulkInquiry.setBranchAndCustomer(requestArticle.BranchNo);

		info.__set_BranchNo(requestArticle.BranchNo);
		info.__set_ArticleCode(requestArticle.ArticleCode);
		info.__set_QuantityAvailableForAll(bulkInquiry.getArticleStockSingle(requestArticle.ArticleCode));

		csc::inquiry::ArticleReservationInfoList resList;
		pxArtReservationList* reservationList = bulkInquiry.getArticleReservationListSingle(requestArticle.ArticleCode);
		pxArtReservationListIter resIt(*reservationList);
		pxArtReservation* entry;
		while ((entry = (pxArtReservation*) ++resIt) != NULL)
		{
			csc::inquiry::ArticleReservationInfo resInfo;
			resInfo.__set_CustomerPharmacyGroup(entry->GetPharmacyGroupId());
			resInfo.__set_QuantityReserved(entry->GetReservedQty());
			resInfo.__set_ReservationType(static_cast<csc::types::ReservationTypeEnum::type>(entry->GetReservType()));
			resList.push_back(resInfo);
		}
		info.__set_ArticleReservations(resList);
		list.push_back(info);
		++it;
	}
	_return.__set_ArticleStockDetailInfoResponses(list);
	_return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}

} // namespace service
} // namespace csc

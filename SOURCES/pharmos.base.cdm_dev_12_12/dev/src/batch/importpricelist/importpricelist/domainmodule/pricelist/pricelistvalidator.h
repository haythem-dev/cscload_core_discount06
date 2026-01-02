//-------------------------------------------------------------------------------------------------//
/*! \file	pricelistvalidator.h
*   \brief	validator for price list data from price list file
*   \author NTT DATA
*   \date	06.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_PRICELISTVALIDATOR_H  
#define GUARD_PRICELISTVALIDATOR_H

#include <list>
#include <string>

#include <libbasarcmnutil.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace importpricelist
{
	namespace domMod
	{
		namespace pricelist
		{
			typedef enum { RT_UNKNOWN = 0, RT_HEADER, RT_PRICE, RT_CONTROL, RT_DELETION } RECORD_TYPE;

			class ListHeaderData
			{
			public:
				basar::Int32 recordType; 
				basar::VarString protocol;
				basar::Int32 priceListId;
				basar::Int32 dateCalc;    // Format YYYYMMDD
				basar::Int32 dateFrom;    // Format YYYYMMDD
				basar::Int16 calcno;
				basar::VarString contentType;

				bool isCompleteList() const { return contentType == "complete"; };
				bool isPartialList() const { return contentType == "partial"; };

			public:
				ListHeaderData();
				~ListHeaderData() {};
				ListHeaderData(const ListHeaderData& other);
				ListHeaderData& operator=(const ListHeaderData& other);
			};

			class ListPriceData
			{
			public:
				basar::Int32 recordType;
				basar::Int32 articleNo;
				basar::Int32 dateFrom;	// Format YYYYMMDD
				basar::Int32 dateTo;    // Format YYYYMMDD
				basar::Int32 quantity;
				basar::Decimal fixedPrice;

			public:
				ListPriceData();
				~ListPriceData() {};
				ListPriceData(const ListPriceData& other);
				ListPriceData& operator=(const ListPriceData& other);

				basar::VarString getSortKey() const;
			};

			class ListControlData
			{
			public:
				basar::Int32 recordType;
				basar::Int32 articleCount;
				basar::Int32 dataItemCount;

			public:
				ListControlData();
				~ListControlData() {};
				ListControlData(const ListControlData& other);
				ListControlData& operator=(const ListControlData& other);
			};

			class ListDeletionData
			{
			public:
				basar::Int32 recordType;
				basar::Int32 articleNo;

			public:
				ListDeletionData();
				~ListDeletionData() {};
				ListDeletionData(const ListDeletionData& other);
				ListDeletionData& operator=(const ListDeletionData& other);
			};

			class PriceListValidator
			{
			public: 
				static RECORD_TYPE validateRecordType(const basar::VarString& strRecordType, basar::VarString& errMsg);
				static bool validateHeaderData(std::list<std::string>& valueList, ListHeaderData& headerData, basar::VarString& errMsg);
				static bool validatePriceData(std::list<std::string>& valueList, ListPriceData& priceData, basar::Int32 validityDate, basar::VarString& errMsg);
				static bool validateControlData(std::list<std::string>& valueList, ListControlData& controlData, basar::VarString& errMsg);
				static bool validateDeletionData(std::list<std::string>& valueList, ListDeletionData& deletionData, basar::VarString& errMsg);

			private:
				static bool isValidArticleNo(const basar::VarString& str, basar::VarString& errMsg);
				static bool isValidNumString(const basar::VarString& str);
				static bool isValidDecimalString(const basar::VarString& str);
				static bool isValidNumValue(const basar::VarString& str, size_t minLen, size_t maxLen, const basar::VarString& fldName, basar::VarString& errMsg);
				static bool isValidDecimalValue(const basar::VarString& str, size_t integerPlaces, size_t decimalPlaces, const basar::VarString& fldName, basar::VarString& errMsg);
				static bool isValidInt32Value(const basar::VarString& str, const basar::VarString& fldName, basar::Int32 minValue, basar::VarString& errMsg);
				static bool isValidDateValue(const basar::VarString& str, const basar::VarString& fldName, basar::VarString& errMsg);
			};

		} // namespace pricedata
	} // namespace domMod
}// namespace pricelist
#endif
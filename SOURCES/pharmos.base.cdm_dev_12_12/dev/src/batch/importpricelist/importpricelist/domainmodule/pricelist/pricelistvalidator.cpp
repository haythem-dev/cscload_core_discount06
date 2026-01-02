//-------------------------------------------------------------------------------------------------//
/*! \file	pricelistvalidator.cpp
*   \brief	validator for price list data from price list file
*   \author NTT DATA
*   \date	06.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#include "pricelistvalidator.h"

#define NUMBER_OF_FIELDS_HEADER    7
#define NUMBER_OF_FIELDS_PRICE     6
#define NUMBER_OF_FIELDS_CONTROL   3
#define NUMBER_OF_FIELDS_DELETION  2

namespace importpricelist
{
	namespace domMod
	{
		namespace pricelist
		{
			RECORD_TYPE PriceListValidator::validateRecordType(const basar::VarString& strRecordType, basar::VarString& errMsg)
			{
				if (!PriceListValidator::isValidNumValue(strRecordType, 1, 1, "recordtype", errMsg))
				{
					return RT_UNKNOWN;
				}
				else if (strRecordType < "1" || strRecordType > "4")
				{
					std::ostringstream os;
					os << "invalid recordtype >" << strRecordType << "<, must be between 1 and 4";
					errMsg = os.str();
					return RT_UNKNOWN;
				}
				else
				{
					return (RECORD_TYPE)strRecordType.stoi();
				}
			}

			bool PriceListValidator::validateHeaderData(std::list<std::string>& valueList, ListHeaderData& headerData, basar::VarString& errMsg)
			{
				int fldNo = 0;
				std::list<std::string>::iterator i = valueList.begin();

				// we need at least the number of header fields, additional fields are ignored
				if (valueList.size() < NUMBER_OF_FIELDS_HEADER)
				{
					std::ostringstream os;
					os << valueList.size() << " fields found for record type >" << RT_HEADER << "<, " << NUMBER_OF_FIELDS_HEADER << " are required";
					errMsg = os.str();
					return false;
				}

				for (fldNo = 1; fldNo <= NUMBER_OF_FIELDS_HEADER; ++i, ++fldNo)
				{
					basar::VarString value(*i);
					value.trim(basar::VarString::FIRST_END);

					switch (fldNo)
					{
					case 1:     // record type
						headerData.recordType = value.stoi();
						break;
					case 2:     // protocol
						if (! (value == "1.0" || value == "1" || value == "1."))
						{
							std::ostringstream os;
							os << "invalid protocol value >" << value << "<, only '1.0' allowed for now";
							errMsg = os.str();
							return false;
						}
						headerData.protocol = value;
						break;
					case 3:     // pricelistid
						if (!PriceListValidator::isValidNumValue(value, 1, 3, "pricelistid", errMsg))
						{
							return false;
						}
						headerData.priceListId = value.stoi();
						break;
					case 4:     // calcdate
						if (!isValidDateValue(value, "calcdate", errMsg))
						{
							return false;
						}
						headerData.dateCalc = value.stoi();
						break;
					case 5:     // datefrom
						if (!isValidDateValue(value, "datefrom", errMsg))
						{
							return false;
						}
						headerData.dateFrom = value.stoi();
						break;
					case 6:     // calcno
						if (!isValidNumValue(value, 1, 3, "calcno", errMsg))
						{
							return false;
						}
						headerData.calcno = (basar::Int16) value.stoi();
						break;
					case 7:     // contenttype
						value.lower();
						if (!(value == "complete" || value == "partial"))
						{
							std::ostringstream os;
							os << "invalid contenttype >" << value << "<, only 'complete' or 'partial' allowed";
							errMsg = os.str();
							return false;
						}
						headerData.contentType = value;
						break;
					}
				}

				return true;
			}

			bool PriceListValidator::validatePriceData(std::list<std::string>& valueList, ListPriceData& priceData, basar::Int32 validityDate, basar::VarString& errMsg)
			{
				int fldNo = 0;
				std::list<std::string>::iterator i = valueList.begin();

				if (valueList.size() < NUMBER_OF_FIELDS_PRICE)
				{
					std::ostringstream os;
					os << valueList.size() << " fields found for record type >" << RT_PRICE << "<, " << NUMBER_OF_FIELDS_PRICE << " are required";
					errMsg = os.str();
					return false;
				}

				for (fldNo = 1; fldNo <= NUMBER_OF_FIELDS_PRICE; ++i, ++fldNo)
				{
					basar::VarString value(*i);
					value.trim(basar::VarString::FIRST_END);

					switch (fldNo)
					{
					case 1:     // record type
						priceData.recordType = value.stoi();
						break;
					case 2:     // articleno
						if (!PriceListValidator::isValidArticleNo(value, errMsg))
						{
							return false;
						}
						priceData.articleNo = value.stoi();
						break;
					case 3:     // datefrom
						if (!PriceListValidator::isValidDateValue(value, "datefrom", errMsg))
						{
							return false;
						}
						priceData.dateFrom = value.stoi();
						break;
					case 4:     // dateto
						if (!PriceListValidator::isValidDateValue(value, "dateto", errMsg))
						{
							return false;
						}
						priceData.dateTo = value.stoi();
						break;
					case 5:     // quantity
						if (!PriceListValidator::isValidInt32Value(value, "quantity", 0, errMsg))
						{
							return false;
						}
						// check for 0 value explicitly to have consistent error message with price
						if (value.stoi() == 0)
						{
							std::ostringstream os;
							os << "invalid quantity >" << value << "<, value not allowed";
							errMsg = os.str();
							return false;
						}
						priceData.quantity = value.stoi();
						break;
					case 6:     // fixedprice
						if (!PriceListValidator::isValidDecimalValue(value, 7, 2, "fixedprice", errMsg))
						{
							return false;
						}
						basar::Decimal price(value);
						if (price == basar::Decimal(0))
						{
							std::ostringstream os;
							os << "invalid fixedprice >" << value << "<, value not allowed";
							errMsg = os.str();
							return false;
						}
						priceData.fixedPrice = basar::Decimal(value);
						break;
					}
				}

				if (priceData.dateFrom < validityDate)
				{
					std::ostringstream os;
					os << "invalid dateFrom value >" << priceData.dateFrom << "<, must not be before dateFrom >" << validityDate << "< from price list header";
					errMsg = os.str();
					return false;
				}

				if (priceData.dateFrom > priceData.dateTo)
				{
					std::ostringstream os;
					os << "invalid date range, dateFrom >" << priceData.dateFrom << "< is after dateTo >" << priceData.dateTo << "<";
					errMsg = os.str();
					return false;
				}

				basar::Date maxDate;
				maxDate.addMonths(12);

				if (priceData.dateFrom > maxDate.getDate())
				{
					std::ostringstream os;
					os << "invalid datefrom value >" << priceData.dateFrom << "<, must not be after maximum value >" << maxDate.getDate() << "< (12 months from today)";
					errMsg = os.str();
					return false;
				}

				return true;
			}

			bool PriceListValidator::validateControlData(std::list<std::string>& valueList, ListControlData& controlData, basar::VarString& errMsg)
			{
				int fldNo = 0;
				std::list<std::string>::iterator i = valueList.begin();

				if (valueList.size() < NUMBER_OF_FIELDS_CONTROL)
				{
					std::ostringstream os;
					os << valueList.size() << " fields found for record type >" << RT_CONTROL << "<, " << NUMBER_OF_FIELDS_CONTROL << " are required";
					errMsg = os.str();
					return false;
				}

				for (fldNo = 1; fldNo <= NUMBER_OF_FIELDS_CONTROL; ++i, ++fldNo)
				{
					basar::VarString value(*i);
					value.trim(basar::VarString::FIRST_END);

					switch (fldNo)
					{
					case 1:     // record type
						controlData.recordType = value.stoi();
						break;
					case 2:     // numberofarticles
						if (!isValidInt32Value(value, "numberofarticles", 0, errMsg))
						{
							return false;
						}
						controlData.articleCount = value.stoi();
						break;
					case 3:     // numberofrecords
						if (!isValidInt32Value(value, "numberofrecords", 0, errMsg))
						{
							return false;
						}
						controlData.dataItemCount = value.stoi();
						break;
					}
				}

				return true;
			}

			bool PriceListValidator::validateDeletionData(std::list<std::string>& valueList, ListDeletionData& deletionData, basar::VarString& errMsg)
			{
				int fldNo = 0;
				std::list<std::string>::iterator i = valueList.begin();

				if (valueList.size() < NUMBER_OF_FIELDS_DELETION)
				{
					std::ostringstream os;
					os << valueList.size() << " fields found for record type >" << RT_DELETION << "<, " << NUMBER_OF_FIELDS_DELETION << " are required";
					errMsg = os.str();
					return false;
				}

				for (fldNo = 1; fldNo <= NUMBER_OF_FIELDS_DELETION; ++i, ++fldNo)
				{
					basar::VarString value(*i);
					value.trim(basar::VarString::FIRST_END);

					switch (fldNo)
					{
					case 1:     // record type
						deletionData.recordType = value.stoi();
						break;
					case 2:     // articleno
						if (!PriceListValidator::isValidArticleNo(value, errMsg))
						{
							return false;
						}
						deletionData.articleNo = value.stoi();
						break;
					}
				}

				return true;
			}

			bool PriceListValidator::isValidNumString(const basar::VarString& str)
			{
				return str.find_first_not_of("01234567890") == std::string::npos;
			}

			bool PriceListValidator::isValidDecimalString(const basar::VarString& str)
			{
				size_t posSeparator;
				basar::VarString decimalSeparator(",");
				basar::VarString integerPart;
				basar::VarString decimalPart;

				if ((posSeparator = str.find(decimalSeparator)) != std::string::npos)
				{
					integerPart = str.substr(0, posSeparator);
					decimalPart = str.substr(posSeparator + 1);
				}
				else
				{
					integerPart = str;
				}

				if (!PriceListValidator::isValidNumString(integerPart))
					return false;
				else if (!PriceListValidator::isValidNumString(decimalPart))
					return false;
				else
					return true;
			}

			bool PriceListValidator::isValidNumValue(const basar::VarString& str, size_t minLen, size_t maxLen, const basar::VarString& fldName, basar::VarString& errMsg)
			{
				if (str.empty() || !PriceListValidator::isValidNumString(str))
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, not a valid numerical value";
					errMsg = os.str();
					return false;
				}

				if (str.length() < minLen || str.length() > maxLen)
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, outside valid numerical range";
					errMsg = os.str();
					return false;
				}

				return true;
			}

			bool PriceListValidator::isValidDecimalValue(const basar::VarString& str, size_t integerPlaces, size_t decimalPlaces, const basar::VarString& fldName, basar::VarString& errMsg)
			{
				size_t posSeparator;
				basar::VarString decimalSeparator(",");
				basar::VarString integerPart;
				basar::VarString decimalPart;

				if ((posSeparator = str.find(decimalSeparator)) != std::string::npos)
				{
					integerPart = str.substr(0, posSeparator);
					decimalPart = str.substr(posSeparator + 1);
				}
				else
				{
					integerPart = str;
				}

				if (!isValidNumString(integerPart)
					|| !isValidNumString(decimalPart)
					|| (posSeparator == std::string::npos && integerPart.empty())
					|| (integerPart.empty() && decimalPart.empty())
					)
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, not a valid decimal value";
					errMsg = os.str();
					return false;
				}

				if (integerPart.size() > integerPlaces || decimalPart.size() > decimalPlaces)
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, outside valid numerical range";
					errMsg = os.str();
					return false;
				}

				return true;
			}

			bool PriceListValidator::isValidInt32Value(const basar::VarString& str, const basar::VarString& fldName, basar::Int32 minValue, basar::VarString& errMsg)
			{
				if (str.empty() || !isValidNumString(str))
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, not a valid numerical value";
					errMsg = os.str();
					return false;
				}

				if (str.length() > 10
					|| (str.length() == 10 && str > "2147483647")
					)
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, outside valid numerical range";
					errMsg = os.str();
					return false;
				}

				basar::Int32 iValue = str.stoi();
				if (iValue < minValue)
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, outside valid numerical range";
					errMsg = os.str();
					return false;
				}

				return true;
			}

			bool PriceListValidator::isValidDateValue(const basar::VarString& str, const basar::VarString& fldName, basar::VarString& errMsg)
			{
				if (str.length() != 8)
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, not a valid date in format YYYYMMDD";
					errMsg = os.str();
					return false;
				}

				if (!isValidNumString(str))
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, not a valid date in format YYYYMMDD";
					errMsg = os.str();
					return false;
				}

				if (!basar::cmnutil::DateTimeTools::isValidDate(str.stoi()))
				{
					std::ostringstream os;
					os << "invalid " << fldName << " >" << str << "<, not a valid date in format YYYYMMDD";
					errMsg = os.str();
					return false;
				}

				return true;
			}

			bool PriceListValidator::isValidArticleNo(const basar::VarString& str, basar::VarString& errMsg)
			{
				if (!PriceListValidator::isValidNumValue(str, 1, 8, "articleno", errMsg))
				{
					return false;
				}
				if (str.stoi() == 0)
				{
					std::ostringstream os;
					os << "invalid articleno >" << str << "<, value not allowed";
					errMsg = os.str();
					return false;
				}

				return true;
			}

			//--------------------------------------------------------------------------------------------------------------------------------------------------------
			// ListHeaderData containing header data from price list file
			//--------------------------------------------------------------------------------------------------------------------------------------------------------

			ListHeaderData::ListHeaderData()
				: recordType(1)
				, protocol("1.0")
				, priceListId(0)
				, dateCalc(0)
				, dateFrom(0)
				, calcno(0)
				, contentType("")
			{

			}

			ListHeaderData::ListHeaderData(const ListHeaderData& other)
			{
				*this = other;
			}

			ListHeaderData& ListHeaderData::operator=(const ListHeaderData& other)
			{
				recordType = other.recordType;
				protocol = other.protocol;
				priceListId = other.priceListId;
				dateCalc = other.dateCalc;
				dateFrom = other.dateFrom;
				calcno = other.calcno;
				contentType = other.contentType;
				return *this;
			}

			//--------------------------------------------------------------------------------------------------------------------------------------------------------
			// ListPriceData containing de pricing data from price list file
			//--------------------------------------------------------------------------------------------------------------------------------------------------------

			ListPriceData::ListPriceData()
				: recordType(2)
				, articleNo(0)
				, dateFrom(0)
				, dateTo(0)
				, quantity(0)
				, fixedPrice(0.0)
			{

			}

			ListPriceData::ListPriceData(const ListPriceData& other)
			{
				*this = other;
			}

			ListPriceData& ListPriceData::operator=(const ListPriceData& other)
			{
				recordType = other.recordType;
				articleNo = other.articleNo;
				dateFrom = other.dateFrom;
				dateTo = other.dateTo;
				quantity = other.quantity;
				fixedPrice = other.fixedPrice;
				return *this;
			}

			basar::VarString ListPriceData::getSortKey() const
			{
				basar::VarString sortKey;

				sortKey.format("%08d:%08d:%08d:%010d", articleNo, dateFrom, dateTo, quantity);

				return sortKey;
			}

			//--------------------------------------------------------------------------------------------------------------------------------------------------------
			// ListControlData containing control data from price list file
			//--------------------------------------------------------------------------------------------------------------------------------------------------------

			ListControlData::ListControlData()
				: recordType(3)
				, articleCount(0)
				, dataItemCount(0)
			{

			}

			ListControlData::ListControlData(const ListControlData& other)
			{
				*this = other;
			}

			ListControlData& ListControlData::operator=(const ListControlData& other)
			{
				recordType = other.recordType;
				articleCount = other.articleCount;
				dataItemCount = other.dataItemCount;
				return *this;
			}

			//--------------------------------------------------------------------------------------------------------------------------------------------------------
			// ListDeletionData containing control data from price list file
			//--------------------------------------------------------------------------------------------------------------------------------------------------------

			ListDeletionData::ListDeletionData()
				: recordType(4)
				, articleNo(0)
			{

			}

			ListDeletionData::ListDeletionData(const ListDeletionData& other)
			{
				*this = other;
			}

			ListDeletionData& ListDeletionData::operator=(const ListDeletionData& other)
			{
				recordType = other.recordType;
				articleNo = other.articleNo;
				return *this;
			}
		}
	}
}

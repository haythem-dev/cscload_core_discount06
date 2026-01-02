//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author
 *  \date
 */
 //-------------------------------------------------------------------------------------------------//

 //-------------------------------------------------------------------------------------------------//
 // include section
 //-------------------------------------------------------------------------------------------------//
#include "mainuc.h"

#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

// basar
#include <libbasarcmnutil.h>

#include "infrastructure/csvreader/csvreader.h"
#include "componentmanager/importpricelistapplcompmgr.h"
#include "domainmodule/articlecodes/articlecodesdm.h"
#include "domainmodule/pricedata/pricedatadm.h"
#include "domainmodule/pricelist/pricelistvalidator.h"
#include "loggerpool/importpricelist_loggerpool.h"

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace importpricelist
{
	namespace useCase
	{
		//-------------------------------------------------------------------------------------------------//
		// macro for registrating and deregistrating EventHandlers!
		//-------------------------------------------------------------------------------------------------//

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		MainUC::MainUC()
			: m_Logger(importpricelist::LoggerPool::getLoggerUseCases())
		{
			METHODNAME_DEF(MainUC, MainUC)
			BLOG_TRACE_METHOD(m_Logger, fun);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		MainUC::~MainUC()
		{
			METHODNAME_DEF(MainUC, ~MainUC)
			BLOG_TRACE_METHOD(m_Logger, fun);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void MainUC::injectUseCaseGetter(importpricelist::componentManager::IUseCaseGetterPtr useCaseGetter)
		{
			METHODNAME_DEF(MainUC, injectUseCaseGetter)
			BLOG_TRACE_METHOD(m_Logger, fun);

			m_UseCaseGetter = useCaseGetter;
		}

		//-------------------------------------------------------------------------------------------------//
		importpricelist::componentManager::IUseCaseGetterPtr MainUC::getUseCaseGetter()
		{
			METHODNAME_DEF(MainUC, getUseCaseGetter)
			BLOG_TRACE_METHOD(m_Logger, fun);

			CHECK_INSTANCE_EXCEPTION(m_UseCaseGetter.get());
			return m_UseCaseGetter;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectPriceDataDM(domMod::pricedata::PriceDataDMPtr priceDataDM)
		{
			METHODNAME_DEF(MainUC, injectPriceDataDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			m_PriceDataDM = priceDataDM;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectPriceList2PharmacyGroupDM(domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDMPtr priceList2PharmacyGroupDM)
		{
			METHODNAME_DEF(MainUC, injectPriceList2PharmacyGroupDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			m_PriceList2PharmacyGroupDM = priceList2PharmacyGroupDM;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectPriceListProcDM(domMod::pricelistproc::PriceListProcDMPtr priceListProcDM)
		{
			METHODNAME_DEF(MainUC, injectPriceList2PharmacyGroupDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			m_PriceListProcDM = priceListProcDM;
		}

		//-------------------------------------------------------------------------------------------------//
		void MainUC::injectArticleCodesDM(domMod::articlecodes::ArticleCodesDMPtr articleCodesDM)
		{
			METHODNAME_DEF(MainUC, injectArticleCodesDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			m_ArticleCodesDM = articleCodesDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::pricedata::PriceDataDMPtr MainUC::getPriceDataDM()
		{
			CHECK_INSTANCE_EXCEPTION(m_PriceDataDM.get());
			return m_PriceDataDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDMPtr MainUC::getPriceList2PharmacyGroupDM()
		{
			CHECK_INSTANCE_EXCEPTION(m_PriceList2PharmacyGroupDM.get());
			return m_PriceList2PharmacyGroupDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::pricelistproc::PriceListProcDMPtr MainUC::getPriceListProcDM()
		{
			CHECK_INSTANCE_EXCEPTION(m_PriceListProcDM.get());
			return m_PriceListProcDM;
		}

		//-------------------------------------------------------------------------------------------------//
		domMod::articlecodes::ArticleCodesDMPtr MainUC::getArticleCodesDM()
		{
			CHECK_INSTANCE_EXCEPTION(m_ArticleCodesDM.get());
			return m_ArticleCodesDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void MainUC::run()
		{
			METHODNAME_DEF(MainUC, run)
			BLOG_TRACE_METHOD(m_Logger, fun);

			// business logic starts here:
			// ---------------------------------------------------------

			BLOG_INFO(m_Logger, "-------- STARTING file processing ------------");
			std::cout << basar::DateTime() << std::endl;

			domMod::pricelist::ListHeaderData listHeader;
			domMod::pricelist::ListControlData listControl;
			boost::ptr_list<domMod::pricelist::ListPriceData> priceList;
			bool fIsValidList = false;

			// step 1: validate price list
			/* we read the complete price list and make sure it satisfies all plausibility checks
    		   before we write anything to the database */
			fIsValidList = validatePriceList(getInputFileName(), listHeader, priceList, listControl);
			if (!fIsValidList)
			{
				// throw an exception to signal error to calling method(s)
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::run()", "price list could not be validated", __FILE__, __LINE__));
			}

			// step 2: write price list to database
			processPriceList(getInputFileName(), listHeader, priceList, listControl);

			std::cout << basar::DateTime() << std::endl;
			BLOG_INFO(m_Logger, "-------- FINISHED file processing ------------");
		}

		bool MainUC::validatePriceList(const basar::VarString& listPath, domMod::pricelist::ListHeaderData& listHeader, boost::ptr_list<domMod::pricelist::ListPriceData>& listPrices, domMod::pricelist::ListControlData& listControl)
		{
			infrastructure::csvReader::CsvReader csvReader;
			std::list<std::string> valueList;
			basar::VarString errMsg;
			basar::Int32 lineCnt = 0;      // count of lines read from file
			basar::Int32 headerCnt = 0;    // count of header records (type 1) found
			basar::Int32 priceCnt = 0;     // count of price records (type 2) found (valid or invalid)
			basar::Int32 validPriceCnt = 0;     // count of valid price records (type 2) found
			basar::Int32 validDeletionCnt = 0;  // count of valid deletion records (type 4) found
			basar::Int32 controlCnt = 0;   // count of control records (type 3) found
			basar::Int32 articleCnt = 0;   // count of different articles found
			basar::Int32 prevArticleNo = 0;
			basar::Int32 articleNoFromPZN = 0;
			domMod::pricelist::RECORD_TYPE recordType = domMod::pricelist::RT_UNKNOWN;
			domMod::pricelist::ListPriceData currentPrice;
			domMod::pricelist::ListDeletionData currentDeletion;
			domMod::pricelist2pharmacygroup::PriceList2PharmacyGroup priceList2PharmacyGroup;
			std::set<basar::Int32> articlesInList;
			bool fError = false;
			bool fValidHeaderFound = false;

			csvReader.openFile(listPath);
			if (!csvReader.good())
			{
				csvReader.closeFile();
				std::ostringstream os;
				os << "cannot open file: >" << listPath << "<";
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarFileNotAccessibleException(basar::ExceptInfo("MainUC::validatePriceList()", os.str(), __FILE__, __LINE__));
			}
			else
			{
				std::ostringstream os;
				os << "starting validation of price list file >" << listPath << "<";
				BLOG_INFO(m_Logger, os.str());
			}

			while (csvReader.good())
			{
				basar::VarString strRecordType;
				domMod::pricedata::PriceData priceData;

				csvReader.readNextRecord(valueList);
				lineCnt++;

				if (valueList.empty())
				{
					continue;
				}

				// get first element of list, i.e. recordType
				strRecordType = valueList.front();
				strRecordType.trim(basar::VarString::FIRST_END);
				// validate record type
				if ((recordType = domMod::pricelist::PriceListValidator::validateRecordType(strRecordType, errMsg)) == domMod::pricelist::RT_UNKNOWN)
				{
					std::ostringstream os;
					os << "line #" << lineCnt << ": " << errMsg;
					BLOG_INFO(m_Logger, os.str());
					BLOG_INFO(m_Logger, "line with invalid recordtype is ignored");
					continue;
				}

				// a record type other than header is only allowed if we have already processed a header  
				if (recordType > domMod::pricelist::RT_HEADER && headerCnt == 0)
				{
					std::ostringstream os;
					os << "line #" << lineCnt << ": recordtype >" << recordType << "< invalid without a previous header record";
					BLOG_ERROR(m_Logger, os.str());
					fError = true;
					break;
				}

				// after a control record all other record types (with the exception of a 
				// deletion record) are not allowed
				else if (controlCnt > 0 && recordType != domMod::pricelist::RT_DELETION)
				{
					std::ostringstream os;
					os << "line #" << lineCnt << ": recordtype >" << recordType << "< invalid after control record";
					BLOG_ERROR(m_Logger, os.str());
					fError = true;
					break;
				}

				switch (recordType)
				{
				case domMod::pricelist::RT_HEADER:
					headerCnt++;
					if (headerCnt > 1)
					{
						std::ostringstream os;
						os << "line #" << lineCnt << ": additional header record found - more than one header is not allowed";
						BLOG_ERROR(m_Logger, os.str());
						fError = true;
						break;
					}
					// validate the header data
					if (!domMod::pricelist::PriceListValidator::validateHeaderData(valueList, listHeader, errMsg))
					{
						std::ostringstream os;
						os << "line #" << lineCnt << ": " << errMsg;
						BLOG_ERROR(m_Logger, os.str());
						BLOG_ERROR(m_Logger, "invalid price list header found");
						fError = true;
						break;
					}
					else
					{
						// validate the header data (calcdate, validitydate) against previously processed files
						if (!validatePriceListHeader(listPath, listHeader, getProcDate().getDate()))
						{
							fError = true;
							break;
						}

						// make sure we have a pharmacy group mapped to the id of the price list
						if (!getPriceList2PharmacyGroupDM()->selectPharmacyGroupByPriceListId(listHeader.priceListId, priceList2PharmacyGroup))
						{
							std::ostringstream os;
							os << "no pharmacy group found in mapping table for price list id >" << listHeader.priceListId << "<";
							BLOG_ERROR(m_Logger, os.str());
							fError = true;
							break;
						}

						// now we are sure that we have found a valid header record
						// --> we can create/update a pricelistproc entry for the list
						fValidHeaderFound = true;
					}
					break;

				case domMod::pricelist::RT_PRICE:
					priceCnt++;
					if (!domMod::pricelist::PriceListValidator::validatePriceData(valueList, currentPrice, listHeader.dateFrom, errMsg))
					{
						std::ostringstream os;
						os << "line #" << lineCnt << ": " << errMsg;
						BLOG_ERROR(m_Logger, os.str());
						continue;
					}
					else
					{
						if (currentPrice.articleNo != prevArticleNo)
						{
							// do we have already processed the current article?
							if (articlesInList.find(currentPrice.articleNo) != articlesInList.end())
							{
							    // all list entries for an article must be in sequence, there must be not other articles in between
								/* otherwise we would delete the previously inserted prices for this article, see processPricelList() */
								std::ostringstream os;
								os << "line #" << lineCnt << ": article no >" << currentPrice.articleNo << "< has already been processed, the list is not sorted correctly";
								BLOG_ERROR(m_Logger, os.str());
								fError = true;
							}

							articleCnt++;
							articlesInList.insert(currentPrice.articleNo);
							prevArticleNo = currentPrice.articleNo;

							// the price list file contains PZNs, which have to be converted to PHOENIX article numbers
							articleNoFromPZN = getArticleNoFromPZN(currentPrice.articleNo);
						}

						validPriceCnt++;

						// create copy of currently processed price data
						domMod::pricelist::ListPriceData* pNewPrice = new domMod::pricelist::ListPriceData(currentPrice);
						// replace pzn in price data with article number 
						pNewPrice->articleNo = articleNoFromPZN;
						// add price record to list of read prices
						listPrices.push_back(pNewPrice);
					}
					break;

				case domMod::pricelist::RT_CONTROL:
					controlCnt++;
					if (controlCnt > 1)
					{
						std::ostringstream os;
						os << "line #" << lineCnt << ": additional control record found - more than one control record is not allowed";
						BLOG_ERROR(m_Logger, os.str());
						fError = true;
						break;
					}
					if (!domMod::pricelist::PriceListValidator::validateControlData(valueList, listControl, errMsg))
					{
						std::ostringstream os;
						os << "line #" << lineCnt << ": " << errMsg;
						BLOG_ERROR(m_Logger, os.str());
						fError = true;
						break;
					}
					// the control sums are compared after we have read the complete file, because after the 
					// control record there still can be one or more deletion records
					break;

				case domMod::pricelist::RT_DELETION:
					// DELETION record counts as valid price record in control sum
					priceCnt++;
					if (!domMod::pricelist::PriceListValidator::validateDeletionData(valueList, currentDeletion, errMsg))
					{
						std::ostringstream os;
						os << "line #" << lineCnt << ": " << errMsg;
						BLOG_ERROR(m_Logger, os.str());
						continue;
					}
					else
					{
						if (currentDeletion.articleNo != prevArticleNo)
						{
							// do we have already processed the current article?
							if (articlesInList.find(currentDeletion.articleNo) != articlesInList.end())
							{
								// all list entries for an article must be in sequence, there must be not other articles in between
								std::ostringstream os;
								os << "line #" << lineCnt << ": article no >" << currentDeletion.articleNo << "< has already been processed, the list is not sorted correctly";
								BLOG_ERROR(m_Logger, os.str());
								fError = true;
							}

							articleCnt++;
							articlesInList.insert(currentDeletion.articleNo);
							prevArticleNo = currentDeletion.articleNo;

							// the price list file contains PZNs, which have to be converted to PHOENIX article numbers
							articleNoFromPZN = getArticleNoFromPZN(currentDeletion.articleNo);
						}

						validDeletionCnt++;

						// the deletion record is copied into a price record to be able to put it in the same list
						// as article number we use the converted article number from PZN
						domMod::pricelist::ListPriceData* pPrice = new domMod::pricelist::ListPriceData();
						pPrice->recordType = currentDeletion.recordType;
//						pPrice->articleNo = currentDeletion.articleNo;
						pPrice->articleNo = articleNoFromPZN;
						listPrices.push_back(pPrice);
					}
					break;
				case domMod::pricelist::RT_UNKNOWN:
					break; // nothing to do, RT_UNKNOWN cannot not occur
				}

				if (fError)
				{
					break;
				}
			}
			csvReader.closeFile();

			if (!fError)
			{
				if (headerCnt == 0)
				{
					std::ostringstream os;
					os << "price list does not contain a valid header record, the list is not processed";
					BLOG_ERROR(m_Logger, os.str());
					fError = true;
				}
				else if (controlCnt == 0)
				{
					std::ostringstream os;
					os << "price list does not contain a valid control record, the list is not processed";
					BLOG_ERROR(m_Logger, os.str());
					fError = true;
				}
				else if (priceCnt != validPriceCnt + validDeletionCnt)
				{
					std::ostringstream os;
					os << "price list contains at least one invalid price or deletion record, the list is not processed";
					BLOG_ERROR(m_Logger, os.str());
					fError = true;
				}
				else if (validPriceCnt == 0 && validDeletionCnt == 0)
				{
					std::ostringstream os;
					os << "price list does not contain at least one valid price or deletion record, the list is not processed";
					BLOG_ERROR(m_Logger, os.str());
					fError = true;
				}
				else if (controlCnt == 1 && (articleCnt != listControl.articleCount || priceCnt != listControl.dataItemCount))
				{
					if (articleCnt != listControl.articleCount)
					{
						std::ostringstream os;
						os << "count of articles >" << articleCnt << "< differs from control sum >" << listControl.articleCount << "< in control record";
						BLOG_ERROR(m_Logger, os.str());
					}
					if (priceCnt != listControl.dataItemCount)
					{
						std::ostringstream os;
						os << "count of price records >" << priceCnt << "< differs from control sum >" << listControl.dataItemCount << "< in control record";
						BLOG_ERROR(m_Logger, os.str());
					}
					fError = true;
				}
			}

			if (fError)
			{
				if (fValidHeaderFound)
				{
					getPriceDataDM()->beginTransaction();

					// create a cpricelistproc entry with state 'rejected' for the current list
					// this is only possible if we could extract a valid header from the file
					createPriceListProcRejected(listPath, priceList2PharmacyGroup.pharmacyGroupId, getProcDate().getDate(), listHeader);
				}
				
				return false;
			}
			else
			{
				std::ostringstream os;
				os << "price list file >" << listPath << "< has been validated, prices will be imported";
				BLOG_INFO(m_Logger, os.str());
			}

			return true;
		}

		void MainUC::processPriceList(const basar::VarString& filePath, const domMod::pricelist::ListHeaderData& listHeader, const boost::ptr_list<domMod::pricelist::ListPriceData>& listPrices, const domMod::pricelist::ListControlData& listControl)
		{
			domMod::pricelist2pharmacygroup::PriceList2PharmacyGroup priceList2PharmacyGroup;
			domMod::pricelistproc::PriceListProc priceListProc;
			basar::Int32 prevArticleNo = 0;
			std::set<basar::Int32> articles;

			std::ostringstream os;
			os << "import of price list file >" << filePath << "< started";
			BLOG_INFO(m_Logger, os.str());

			// get pharmacy group data for price list id found in header data
			getPharmacyGroupForPriceList(listHeader.priceListId, priceList2PharmacyGroup);

			// get the articles with valid prices
			// --> we need them to clean up the prices that are not included in the current list
			/* this is only needed if we are processing a complete list */
			if (listHeader.isCompleteList())
			{
				selectArticlesWithValidPrices(priceList2PharmacyGroup.pharmacyGroupId, listHeader.dateFrom, articles);
			}

			try
			{
				getPriceDataDM()->beginTransaction();

				// create entry for price list in cpricelistproc
			    createPriceListProcEntry(filePath, priceList2PharmacyGroup.pharmacyGroupId, getProcDate().getDate(), listHeader, listControl, priceListProc);

				// now iterate over all read prices and process them
				for (boost::ptr_list<domMod::pricelist::ListPriceData>::const_iterator iter = listPrices.begin(); iter != listPrices.end(); ++iter)
				{
					domMod::pricelist::ListPriceData price(*iter);
//					std::cout << price.recordType << " - " << price.articleNo << " - " << price.dateFrom << " - " << price.dateTo << " - " << price.quantity << " - " << price.fixedPrice << std::endl;

					if (price.recordType == domMod::pricelist::RT_PRICE)
					{
						domMod::pricedata::PriceData priceData;

						if (price.articleNo != prevArticleNo)
						{
							if (prevArticleNo != 0)
							{
								priceListProc.numProcArticles++;
								updatePriceListProcEntry(priceListProc);

#ifdef ABORTTEST
								// abort type == 1 (i.e. before commit) and specified article is about to be commited?
								if (getAbortType() == 1 && getAbortArticleNo() == prevArticleNo)
								{
									exit(1);
								}
#endif
								getPriceDataDM()->commitTransaction();
								getPriceDataDM()->beginTransaction();

#ifdef ABORTTEST
								// abort type == 2 (i.e. after commit) and specified article has been commited?
								if (getAbortType() == 2 && getAbortArticleNo() == prevArticleNo)
								{
									exit(1);
								}
#endif

								// remove the processed article from the list of articles with valid prices
								if (listHeader.isCompleteList())
								{
									articles.erase(prevArticleNo);
								}
							}

							prevArticleNo = price.articleNo;

							// invalidate all currently valid prices and delete all future prices
							// for the new article
							basar::Int32 invalidationDate = listHeader.isCompleteList() ? listHeader.dateFrom : price.dateFrom;
							cleanupPricesForArticle(priceList2PharmacyGroup.pharmacyGroupId, price.articleNo, invalidationDate);
						}

						// fill structure for storing cdiscount data from current price list entry and the pharmacy group
						priceData.pharmacyGroupId = priceList2PharmacyGroup.pharmacyGroupId;
						priceData.articleNo = price.articleNo;
						priceData.dateFrom = price.dateFrom;
						priceData.dateTo = price.dateTo;
						priceData.quantity = price.quantity;
						priceData.fixedPrice = price.fixedPrice;
						priceData.discountType = priceList2PharmacyGroup.discountType;
						priceData.discountSpec = priceList2PharmacyGroup.discountSpec;
						basar::db::sql::ExecuteReturnInfo insertResult = getPriceDataDM()->insertPriceData(priceData);
						if (insertResult.hasError())
						{
							os.str(""); os.clear();
							os << "error inserting cdiscounts record - " << insertResult.getError();
							BLOG_ERROR(m_Logger, os.str());
							throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::processPriceList()", os.str(), __FILE__, __LINE__));
						}
						priceListProc.numProcPrices++;
					}
					else    // price.recordType == domMod::pricelist::RT_DELETION
					{
						priceListProc.numDelArticles++;
						priceListProc.numProcPrices++;

						if (price.articleNo != prevArticleNo)
						{
							if (prevArticleNo != 0)
							{
								priceListProc.numProcArticles++;
							}
							prevArticleNo = price.articleNo;
						}

						//std::cout << recordType << " - " << listDeletionData.articleNo << std::endl;
						// invalidate all currently active prices and delete all future prices for 
						// the article specified in record type 4 (DELETION)
						basar::Int32 invalidationDate = 0;
						if (listHeader.isCompleteList())
						{
							invalidationDate = listHeader.dateFrom;
						}
						else
						{
							// ProcDate is normally the current date, but can be specified as a command line parameter
							// we need to add a day to the current date, because cleanupPricesPartial() expects the
							// date to be the date the new prices become valid
							basar::Date tmpDate = getProcDate();
							tmpDate.addDays(1);
							invalidationDate = tmpDate.getDate();
						}
						cleanupPricesForArticle(priceList2PharmacyGroup.pharmacyGroupId, price.articleNo, invalidationDate);
						updatePriceListProcEntry(priceListProc);
						getPriceDataDM()->commitTransaction();
						getPriceDataDM()->beginTransaction();
					}
				}

				if (prevArticleNo != 0)
				{
					priceListProc.numProcArticles++;
					// remove the article from the list of articles with valid prices
					if (listHeader.isCompleteList())
					{
						articles.erase(prevArticleNo);
					}
				}

				// the list of articles with valid prices now contains only those articles that
				// were NOT included in the current price list
				// --> these have to be invalidated
				if (listHeader.isCompleteList())
				{
					cleanupPricesForNotIncludedArticles(priceList2PharmacyGroup.pharmacyGroupId, listHeader.dateFrom, articles);
				}

				// we have now successfully processed the price list
				// --> set processing status to 'processed'
				priceListProc.procState = "processed";
				priceListProc.procInfoMsg = "";
				updatePriceListProcEntry(priceListProc);
				getPriceDataDM()->commitTransaction();

				// after processing the list, we make a report (in the log file) of imported prices 
				// for which the articleNo does not exist in table zartikel
				if (listHeader.isCompleteList())
				{
					reportPricesNotInZArtikel(listHeader.priceListId, priceList2PharmacyGroup.pharmacyGroupId, listHeader.dateFrom);
				}

				os.str(""); os.clear();
				os << "import of price list file >" << filePath << "< for price list id >" << priceListProc.priceListId << "< / pharmacy group id >" << priceListProc.pharmacyGroupId << "< successfully finished";
				BLOG_INFO(m_Logger, os.str());
				os.str(""); os.clear();
				os << priceListProc.numProcPrices << " price records for " << priceListProc.numArticles << " articles have been imported";
				BLOG_INFO(m_Logger, os.str());
			}
			catch (basar::Exception e)
			{
				getPriceDataDM()->rollbackTransaction();

				getPriceDataDM()->beginTransaction();
				priceListProc.procInfoMsg = e.what();
				getPriceListProcDM()->updateStatusAndInfoMsg(priceListProc);
				getPriceDataDM()->commitTransaction();

				throw;
			}
		}

		bool MainUC::validatePriceListHeader(const basar::VarString& filePath, const domMod::pricelist::ListHeaderData& listHeaderData, basar::Int32 procDate)
		{
			METHODNAME_DEF(MainUC, validatePriceListHeader)
			BLOG_TRACE_METHOD(m_Logger, fun);

			domMod::pricelistproc::PriceListProc priceListProc;
			basar::Int32 maxCalcDate;
			basar::Int32 maxDateFrom;
			basar::Int16 maxSeqNo;

			// remove directory information from path, only filename is needed
			boost::filesystem::path p(filePath.c_str());
			basar::VarString fileName(p.filename().string());

			// if a pricelist with the same file name has already been processed (or been tried to process), it must 
			// have the same logical key ( pricelistid / calcdate / seqno ), otherwise it can not be processed
			if (getPriceListProcDM()->selectPriceListProcByFileName(fileName, priceListProc))
			{
				if (! (   priceListProc.priceListId == listHeaderData.priceListId
					   && priceListProc.calcDate == listHeaderData.dateCalc
					   && priceListProc.seqNo == listHeaderData.calcno))
				{
					std::ostringstream os;
					os << "price list with file name >" << fileName << "< but different logical key pricelistid/calcdate/seqno >" << priceListProc.priceListId << "/" << priceListProc.calcDate << "/" << priceListProc.seqNo << "< was already received";
					BLOG_ERROR(m_Logger, os.str());
					return false;
				}
			}

			// calcdate must be greater or equal to the highest previously processed value
			if (getPriceListProcDM()->selectMaxDates(listHeaderData.priceListId, maxCalcDate, maxDateFrom))
			{
				if (listHeaderData.dateCalc < maxCalcDate)
				{
					std::ostringstream os;
					os << "calc date >" << listHeaderData.dateCalc << "< of price list is before previously processed calc date >" << maxCalcDate << "<";
					BLOG_ERROR(m_Logger, os.str());
					return false;
				}
				// if the calcdate is equal to the highest previously processed value, 
				// the sequence number must be greater than the highest previously processed value
				else if (maxCalcDate == listHeaderData.dateCalc)
				{
					if (getPriceListProcDM()->selectMaxSeqNo(listHeaderData.priceListId, maxCalcDate, maxSeqNo))
					{
						if (listHeaderData.calcno < maxSeqNo)
						{
							std::ostringstream os;
							os << "sequence no >" << listHeaderData.calcno << "< of price list is less than previously processed sequence no >" << maxSeqNo << "< for calc date >" << listHeaderData.dateCalc << "<";
							BLOG_ERROR(m_Logger, os.str());
							return false;
						}
						else if (listHeaderData.calcno == maxSeqNo)
						{
							// read the processing status for the price list
							// if the previous processing of the list was aborted, we can restart processing for this list
							// if the previous processing of the list was successful, reprocessing the list is not allowed
							priceListProc.priceListId = listHeaderData.priceListId;
							priceListProc.calcDate = listHeaderData.dateCalc;
							priceListProc.seqNo = listHeaderData.calcno;
							if (getPriceListProcDM()->selectPriceListProcByKey(priceListProc))
							{
								if (priceListProc.procState != "processing" && priceListProc.procState != "rejected")
								{
									std::ostringstream os;
									os << "price list >" << listHeaderData.priceListId << "< for calc date >" << listHeaderData.dateCalc << "< and sequence no >" << listHeaderData.calcno << "< has already been processed";
									BLOG_ERROR(m_Logger, os.str());
									return false;
								}
							}
						}
						else if (listHeaderData.calcno > maxSeqNo)
						{
							// if we have a new list, we update the processing status of previously 
							// aborted lists to 'failed'
							/* this actually happens in processPriceList(), when we are creating the 
							   processing entry for the new list, because only there we do changes
							   do the database */
						}
					}
				}
			}

			if (listHeaderData.dateCalc < procDate)
			{
				std::ostringstream os;
				os << "calc date >" << listHeaderData.dateCalc << "< of price list must be the current date >" << procDate << "< or later";
				BLOG_ERROR(m_Logger, os.str());
				return false;
			}

			if (listHeaderData.dateFrom <= procDate)
			{
				std::ostringstream os;
				os << "validity date >" << listHeaderData.dateFrom << "< of price list must be later than the current date >" << procDate << "<";
				BLOG_ERROR(m_Logger, os.str());
				return false;
			}

			basar::Date maxDate(procDate);
			maxDate.addMonths(12);

			if (listHeaderData.dateFrom > maxDate.getDate())
			{
				std::ostringstream os;
				os << "validity date >" << listHeaderData.dateFrom << "< of price list must not be after the maximum date >" << maxDate << "< (12 months from now)";
				BLOG_ERROR(m_Logger, os.str());
				return false;
			}

			return true;
		}

		void MainUC::selectArticlesWithValidPrices(basar::Int32 pharmacyGroupId, basar::Int32 newValidityDate, std::set<basar::Int32>& articles)
		{
			METHODNAME_DEF(MainUC, selectArticlesWithValidPrices)
			BLOG_TRACE_METHOD(m_Logger, fun);

			basar::db::aspect::ExecuteResultInfo selectResult = getPriceDataDM()->selectArticlesWithValidPrices(pharmacyGroupId, newValidityDate);
			if (selectResult.hasError())
			{
				std::ostringstream os;
				os << "error reading valid prices from cdiscount - " << selectResult.getError();
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::selectArticlesWithValidPrices()", os.str(), __FILE__, __LINE__));
			}
			basar::db::aspect::AccessorPropertyTableRef selectedData = getPriceDataDM()->getPriceData();
			basar::db::aspect::AccessorPropertyTable_YIterator priceDataIterator = selectedData.begin();
			while (!priceDataIterator.isEnd())
			{
				articles.insert(priceDataIterator.getInt32(domMod::pricedata::PRICEDATA_ARTICLENO.getName()));
				priceDataIterator++;
			}
		}

		void MainUC::cleanupPrices(basar::Int32 pharmacyGroupId, basar::Int32 newValidityDate)
		{
			METHODNAME_DEF(MainUC, invalidatePrices)
			BLOG_TRACE_METHOD(m_Logger, fun);

			// parameter newValidityDate is the day the new prices become valid
			// --> the validTo date of the prices currently in the database
			//     must be set to the day before the newValidityDate
			basar::Date newValidToDate(newValidityDate);
			newValidToDate.addDays(-1);

			// invalidate all currently valid prices, i.e. prices with a dateto date greater 
			// than the new validTo date
			invalidatePrices(pharmacyGroupId, newValidToDate.getDate());

			// delete all future prices, i.e. prices with a datefrom date greater
			// than the new validTo date
			deleteFuturePrices(pharmacyGroupId, newValidToDate.getDate());
		}

		void MainUC::cleanupPricesForNotIncludedArticles(basar::Int32 pharmacyGroupId, basar::Int32 newValidityDate, const std::set<basar::Int32>& articles)
		{
			METHODNAME_DEF(MainUC, cleanupPricesForNotIncludedArticles)
			BLOG_TRACE_METHOD(m_Logger, fun);

			/* parameter newValidityDate is the day the new prices become valid */

			// cleanup prices of articles contained in the article set
			std::set<basar::Int32>::iterator articleIterator;
			for (articleIterator = articles.begin(); articleIterator != articles.end(); articleIterator++)
			{
				cleanupPricesForArticle(pharmacyGroupId, *articleIterator, newValidityDate);
			}
		}

		void MainUC::invalidatePrices(basar::Int32 pharmacyGroupId, basar::Int32 newValidToDate)
		{
			METHODNAME_DEF(MainUC, invalidatePrices)
			BLOG_TRACE_METHOD(m_Logger, fun);

			/* parameter newValidToDate is the date the current prices become invalid,
			   that is one day before the new prices become valid */

			basar::db::aspect::ExecuteResultInfo updateResult = getPriceDataDM()->invalidatePriceDataByPharmacyGroup(pharmacyGroupId, newValidToDate);
			if (updateResult.hasError())
			{
				std::ostringstream os;
				os << "error invalidating prices in cdiscount - " << updateResult.getError();
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::invalidatePrices()", os.str(), __FILE__, __LINE__));
			}
		}

		void MainUC::deleteFuturePrices(basar::Int32 pharmacyGroupId, basar::Int32 dateDeleteAfter)
		{
			METHODNAME_DEF(MainUC, deleteFuturePrices)
			BLOG_TRACE_METHOD(m_Logger, fun);

			/* parameter dateDeleteAfter is the date the current prices become invalid, 
			   that is one day before the new prices become valid
			   future prices, i.e. prices with dateFrom greater dateDeleteAfter are
			   deleted from cdiscount */

			basar::db::aspect::ExecuteResultInfo deleteResult = getPriceDataDM()->deletePriceDataByPharmacyGroup(pharmacyGroupId, dateDeleteAfter);
			if (deleteResult.hasError())
			{
				std::ostringstream os;
				os << "error deleting future prices in cdiscount - " << deleteResult.getError();
				BLOG_INFO(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::deleteFuturePrices()", os.str(), __FILE__, __LINE__));
			}
		}

		void MainUC::cleanupPricesForArticle(basar::Int32 pharmacyGroupId, basar::Int32 articleNo, basar::Int32 newValidityDate)
		{
			METHODNAME_DEF(MainUC, cleanupPricesForArticle)
			BLOG_TRACE_METHOD(m_Logger, fun);

			// parameter newValidityDate is the day the new prices become valid
			// --> the validTo date of the prices currently in the database
			//     must be set to the day before the newValidityDate
			basar::Date newValidToDate(newValidityDate);
			newValidToDate.addDays(-1);

			// invalidate all currently valid prices, i.e. prices with a dateto date greater 
			// than the new validTo date
			invalidatePricesForArticle(pharmacyGroupId, articleNo, newValidToDate.getDate());

			// delete all future prices, i.e. prices with a datefrom date greater
			// than the new validTo date
			deleteFuturePricesForArticle(pharmacyGroupId, articleNo, newValidToDate.getDate());
		}

		void MainUC::invalidatePricesForArticle(basar::Int32 pharmacyGroupId, basar::Int32 articleNo, basar::Int32 newValidToDate)
		{
			METHODNAME_DEF(MainUC, invalidatePricesForArticle)
			BLOG_TRACE_METHOD(m_Logger, fun);

			/* parameter newValidToDate is the date the current prices become invalid,
  			   that is one day before the new prices become valid */

			basar::db::sql::ExecuteReturnInfo updateResult = getPriceDataDM()->invalidateByPharmacyGroupArticle(pharmacyGroupId, articleNo, newValidToDate);
			if (updateResult.hasError())
			{
				std::ostringstream os;
				os << "error invalidating prices in cdiscount - " << updateResult.getError();
				BLOG_INFO(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::run()", os.str(), __FILE__, __LINE__));
			}
		}

		void MainUC::deleteFuturePricesForArticle(basar::Int32 pharmacyGroupId, basar::Int32 articleNo, basar::Int32 dateDeleteAfter)
		{
			METHODNAME_DEF(MainUC, deleteFuturePricesForArticle)
			BLOG_TRACE_METHOD(m_Logger, fun);

			/* parameter dateDeleteAfter is the date the current prices become invalid,
			   that is one day before the new prices become valid
			   future prices, i.e. prices with dateFrom greater dateDeleteAfter are
			   deleted from cdiscount */

			basar::db::sql::ExecuteReturnInfo deleteResult = getPriceDataDM()->deleteByPharmacyGroupArticle(pharmacyGroupId, articleNo, dateDeleteAfter);
			if (deleteResult.hasError())
			{
				std::ostringstream os;
				os << "error deleting future prices in cdiscount - " << deleteResult.getError();
				BLOG_INFO(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::deleteFuturePricesPartial()", os.str(), __FILE__, __LINE__));
			}
		}

		void MainUC::getPharmacyGroupForPriceList(basar::Int32 priceListId, domMod::pricelist2pharmacygroup::PriceList2PharmacyGroup& priceList2PharmacyGroup)
		{
			if (! getPriceList2PharmacyGroupDM()->selectPharmacyGroupByPriceListId(priceListId, priceList2PharmacyGroup))
			{
				std::ostringstream os;
				os << "no mapping price list to pharmacy group found for price list id >" << priceListId << "<";
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::getPharmacyGroupForPriceList()", os.str(), __FILE__, __LINE__));
			}
		}

		void MainUC::createPriceListProcRejected(const basar::VarString& filePath,
			                                     const basar::Int32 pharmacyGroupId,
			                                     const basar::Int32 procDate,
			                                     const domMod::pricelist::ListHeaderData& listHeaderData)
		{
			domMod::pricelistproc::PriceListProc priceListProc;

			// we delete a currently present proc entry for the price list and create a new one afterwards
			priceListProc.priceListId = listHeaderData.priceListId;
			priceListProc.calcDate = listHeaderData.dateCalc;
			priceListProc.seqNo = listHeaderData.calcno;
			basar::db::aspect::ExecuteResultInfo deleteResult = getPriceListProcDM()->deletePriceListProcByKey(priceListProc);
			if (deleteResult.hasError())
			{
				std::ostringstream os;
				os << "error deleting price list processing status - " << deleteResult.getError();
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::getPriceListProcEntry()", os.str(), __FILE__, __LINE__));
			}

			// create new price list processing entry for current priceList

			// remove directory information from path, only filename is stored
			boost::filesystem::path p(filePath.c_str());
			basar::VarString fileName(p.filename().string());

			priceListProc.fileName = fileName;
			priceListProc.priceListType = listHeaderData.contentType;
			priceListProc.priceListId = listHeaderData.priceListId;
			priceListProc.pharmacyGroupId = pharmacyGroupId;
			priceListProc.calcDate = listHeaderData.dateCalc;
			priceListProc.seqNo = listHeaderData.calcno;
			priceListProc.procDate = procDate;
			priceListProc.dateFrom = listHeaderData.dateFrom;
			priceListProc.numArticles = -1;
			priceListProc.numPrices = -1;
			priceListProc.numProcArticles = 0;
			priceListProc.numProcPrices = 0;
			priceListProc.numDelArticles = 0;
			priceListProc.numArticlesError = 0;
			priceListProc.procState = "rejected";
			priceListProc.procInfoMsg = "";

			basar::db::aspect::ExecuteResultInfo insertResult = getPriceListProcDM()->insertPriceListProc(priceListProc);
			if (!insertResult.hasError())
			{
				getPriceDataDM()->commitTransaction();
				getPriceDataDM()->beginTransaction();
			}
			else
			{
				std::ostringstream os;
				os << "error inserting new price list processing status - " << insertResult.getError();
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::getPriceListProcEntry()", os.str(), __FILE__, __LINE__));
			}
		}

		void MainUC::createPriceListProcEntry(const basar::VarString& filePath,
			                                  const basar::Int32 pharmacyGroupId, 
			                                  const basar::Int32 procDate, 
			                                  const domMod::pricelist::ListHeaderData& listHeaderData, 
			                                  const domMod::pricelist::ListControlData& listControlData,
			                                  domMod::pricelistproc::PriceListProc& priceListProc)
		{
			// we set the status of all previously aborted imports to 'Failed'
			basar::db::aspect::ExecuteResultInfo updateResult = getPriceListProcDM()->updateStatusToFailed(listHeaderData.priceListId, listHeaderData.dateCalc, listHeaderData.calcno);
			if (updateResult.hasError())
			{
				std::ostringstream os;
				os << "error updating price list processing status - " << updateResult.getError();
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::getPriceListProcEntry()", os.str(), __FILE__, __LINE__));
			}

			// we delete a currently present proc entry for the price list and create a new one afterwards
			priceListProc.priceListId = listHeaderData.priceListId;
			priceListProc.calcDate = listHeaderData.dateCalc;
			priceListProc.seqNo = listHeaderData.calcno;
			basar::db::aspect::ExecuteResultInfo deleteResult = getPriceListProcDM()->deletePriceListProcByKey(priceListProc);
			if (deleteResult.hasError())
			{
				std::ostringstream os;
				os << "error deleting price list processing status - " << deleteResult.getError();
				BLOG_INFO(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::getPriceListProcEntry()", os.str(), __FILE__, __LINE__));
			}

			// create new price list processing entry for current priceList

			// remove directory information from path, only filename is stored
			boost::filesystem::path p(filePath.c_str());
			basar::VarString fileName(p.filename().string());

			priceListProc.fileName = fileName;
			priceListProc.priceListType = listHeaderData.contentType;
			priceListProc.priceListId = listHeaderData.priceListId;
			priceListProc.pharmacyGroupId = pharmacyGroupId;
			priceListProc.calcDate = listHeaderData.dateCalc;
			priceListProc.seqNo = listHeaderData.calcno;
			priceListProc.procDate = procDate;
			priceListProc.dateFrom = listHeaderData.dateFrom;
			priceListProc.numArticles = listControlData.articleCount;
			priceListProc.numPrices = listControlData.dataItemCount;
			priceListProc.numProcArticles = 0;
			priceListProc.numProcPrices = 0;
			priceListProc.numDelArticles = 0;
			priceListProc.numArticlesError = 0;
			priceListProc.procState = "processing";
			priceListProc.procInfoMsg = "";

			basar::db::aspect::ExecuteResultInfo insertResult = getPriceListProcDM()->insertPriceListProc(priceListProc);
			if (!insertResult.hasError())
			{
				getPriceDataDM()->commitTransaction();
				getPriceDataDM()->beginTransaction();
			}
			else
			{
				std::ostringstream os;
				os << "error inserting new price list processing status - " << insertResult.getError();
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::getPriceListProcEntry()", os.str(), __FILE__, __LINE__));
			}
		}

		void MainUC::updatePriceListProcEntry(const domMod::pricelistproc::PriceListProc& priceListProc)
		{
			basar::db::sql::ExecuteReturnInfo updateResult = getPriceListProcDM()->updatePriceListProcPrep(priceListProc);
			if (updateResult.hasError())
			{
				std::ostringstream os;
				os << "error updating price list processing status - " << updateResult.getError();
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::updatePriceListProcEntry()", os.str(), __FILE__, __LINE__));
			}
		}

		void MainUC::reportPricesNotInZArtikel(basar::Int32 priceListId, basar::Int32 pharmacyGroupId, basar::Int32 dateFrom)
		{
			METHODNAME_DEF(MainUC, reportPricesNotInZArticle)
			BLOG_TRACE_METHOD(m_Logger, fun);
			int priceCnt = 0;

			basar::db::aspect::ExecuteResultInfo selectResult = getPriceDataDM()->selectPriceDataNotInZArtikel(pharmacyGroupId, dateFrom);
			if (selectResult.hasError())
			{
				std::ostringstream os;
				os << "error reading prices not in zarticle from cdiscount - " << selectResult.getError();
				BLOG_ERROR(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("MainUC::selectArticlesWithValidPrices()", os.str(), __FILE__, __LINE__));
			}
			basar::db::aspect::AccessorPropertyTableRef selectedData = getPriceDataDM()->getPriceData();
			basar::db::aspect::AccessorPropertyTable_YIterator priceDataIterator = selectedData.begin();
			while (!priceDataIterator.isEnd())
			{
				domMod::pricedata::PriceData priceData;
				priceCnt++;

				priceData.articleNo = priceDataIterator.getInt32(domMod::pricedata::PRICEDATA_ARTICLENO.getName());
				priceData.dateFrom = priceDataIterator.getInt32(domMod::pricedata::PRICEDATA_DATEFROM.getName());
				priceData.dateTo = priceDataIterator.getInt32(domMod::pricedata::PRICEDATA_DATETO.getName());
				priceData.quantity = priceDataIterator.getInt32(domMod::pricedata::PRICEDATA_QUANTITY.getName());
				priceData.fixedPrice = priceDataIterator.getDecimal(domMod::pricedata::PRICEDATA_FIXEDPRICE.getName());

				if (priceCnt == 1)
				{
					std::ostringstream os;
					os << "list of price data for price list id >" << priceListId << "<, pharmacy group id >" << domMod::pricedata::PriceData::convertInt32ToVarString(pharmacyGroupId, 3) << "< where articleNo not present in zarticle:";
					BLOG_WARN(m_Logger, os.str());
				}
				std::ostringstream os;
				os << priceData.articleNo << ";" << priceData.dateFrom << ";" << priceData.dateTo << ";" << priceData.quantity << ";" << priceData.fixedPrice;
				BLOG_WARN(m_Logger, os.str());

				priceDataIterator++;
			}
		}

		basar::Int32 MainUC::getArticleNoFromPZN(basar::Int32 pzn)
		{
			basar::Int32 articleNo(pzn);

			// 8 or more digits in pzn?
			if (pzn >= 10000000)
			{
				// --> pzn has to be converted to article no

				basar::VarString articleNoAsStr;
				articleNoAsStr.itos(pzn);

				// get article no for pzn (16: code type "PZN 8")
				if (!getArticleCodesDM()->selectArticleNoByCodeAndType(articleNoAsStr, 16, articleNo))
				{
					std::ostringstream os;
					os << "no article number found in carticlecodes for pzn >" << pzn << "<";
					BLOG_WARN(m_Logger, os.str());

					// no article no found for pzn, return pzn instead
					articleNo = pzn;
				}
			}

			return articleNo;
		}
	} // namespace usecase
} // namespace importpricelist

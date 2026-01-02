
#include <locale>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <boost/assign.hpp>
#include <boost/assign/ptr_list_of.hpp>
#include<algorithm>
#include <ctime>

#include "CalculationRules.h"
#include "Utils.h"
#include "../domainmodule/article/articledm.h"
#include <domainmodule/deliveryparam/deliveryparamdm.h>
#include <boost/regex.hpp>

namespace subsequentdeliveryrelevantcalculator
{
	namespace useCase
	{

		using namespace domMod::article;

		// initialize static members

		const log4cplus::Logger& CalculationRules::m_Logger = log4cplus::Logger(subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerUseCases());

		boost::ptr_vector<RuleParameter> CalculationRules::_listOfRules;
		std::vector<basar::Int32> _imTrue;
		std::vector<basar::Int32> _imFalse;
		basar::Int32 _ruleStart;

		/* initialize from db result */
		void CalculationRules::initialize(basar::db::aspect::AccessorPropertyTableRef ruleData)
		{
			bool fErrorFound = false;
			basar::db::aspect::AccessorPropertyTable_YIterator ruleIterator;
			auto imSize = 0;
			for (ruleIterator = ruleData.begin(); ruleIterator != ruleData.end(); ++ruleIterator)
			{
				auto id = ruleIterator.getInt32(domMod::deliveryparam::DELIVERYPARAM_RULEID);
				imSize = std::max<int>((int)id+1, (int)imSize);
			}
			_listOfRules.resize(imSize);
			_imTrue.resize(imSize);
			_imFalse.resize(imSize);

			// iterate over the rule parameters read from DB
			// if necessary, validate the parameters and create a RuleParameter object for each row
			// and create incidence matrix for "true" and "false"
			for (ruleIterator = ruleData.begin(); ruleIterator != ruleData.end(); ++ruleIterator)
			{
				basar::VarString ruleName(ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_RULENAME));
				TInternalRuleId internalRuleId(InternalRuleId::CheckArticleInvalidRule);
				basar::VarString strValue1;
				basar::VarString strValue2;
				basar::VarString strValue3;
				basar::VarString strValue4;
				basar::VarString strValue5;
				basar::VarString strValue6;
				basar::VarString strValue7;
				basar::VarString strValue8;
				basar::VarString strValue9;
				basar::VarString strValue10;
				basar::Int32 intValue1 = 0;
				basar::Int32 intValue2 = 0;

				auto id = ruleIterator.getInt32(domMod::deliveryparam::DELIVERYPARAM_RULEID);
				auto v = ruleIterator.getInt16(domMod::deliveryparam::DELIVERYPARAM_RULESTART);
				auto v1 = ruleIterator.getInt32(domMod::deliveryparam::DELIVERYPARAM_RULETRUE);
				auto v2 = ruleIterator.getInt32(domMod::deliveryparam::DELIVERYPARAM_RULEFALSE);

				{
					std::ostringstream os;
					os << "initialize rule: " << id << ": " << ruleName << " rulestart: " << v << " ruletrue: " << v1 << " rulefalse: " << v2;
					BLOG_DEBUG(m_Logger, os.str());
				}

				if (v != 0)
				{
					//if (ruleStart != 0 ) check if already ruleStart set - then something went wrong!
					_ruleStart = id;
				}
				if (v1 != 0)
				{
					_imTrue[id] = v1;
				}
				if (v2 != 0)
				{
					_imFalse[id] = v2;
				}

				if (ruleName == "CheckArticlePPEState")
				{
					internalRuleId = InternalRuleId::CheckArticlePPEState;
					strValue1 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
				}
				else if (ruleName == "CheckLimitedArticleState")
				{
					internalRuleId = InternalRuleId::CheckLimitedArticleState;

					// verification of parameter - must be valid integer
					basar::VarString paramValue = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
					if (!isValidNumString(paramValue))
					{
						std::ostringstream os;
						os << "invalid parameter value 1>" << paramValue << "< found for rule " << ruleName << " - must be numerical value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					intValue1 = paramValue.stoi();
				}
				else if (ruleName == "CheckNarcoticArticleState")
				{
					internalRuleId = InternalRuleId::CheckNarcoticArticleState;
					strValue1 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
				}
				else if (ruleName == "CheckPeriodForDelivery")
				{
					internalRuleId = InternalRuleId::CheckPeriodForDelivery;

					// verification of parameters - must be valid integers
					basar::VarString paramValue1 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
					if (!isValidNumString(paramValue1))
					{
						std::ostringstream os;
						os << "invalid parameter value 1>" << paramValue1 << "< found for rule " << ruleName << " - must be numerical value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					basar::VarString paramValue2 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE2);
					if (!isValidNumString(paramValue2))
					{
						std::ostringstream os;
						os << "invalid parameter value 2>" << paramValue2 << "< found for rule " << ruleName << " - must be numerical value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}

					intValue1 = paramValue1.stoi();
					intValue2 = paramValue2.stoi();
				}
				else if (ruleName == "CheckArticleCoolingState")
				{
					internalRuleId = InternalRuleId::CheckArticleCoolingState;
					strValue1 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
				}
				else if (ruleName == "CheckArticleActiveStorageLocation")
				{
					internalRuleId = InternalRuleId::CheckArticleActiveStorageLocation;

					// verification of parameter - must be string interval
					basar::VarString paramValue1 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
					basar::VarString paramValue2 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE2);
					if (paramValue1 > paramValue2)
					{
						std::ostringstream os;
						os << "invalid parameter values found for rule " << ruleName << " - parameter 1 must be less or equal to parameter 2";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue1 = paramValue1;
					strValue2 = paramValue2;

					basar::VarString paramValue3 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE3);
					basar::VarString paramValue4 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE4);
					if (paramValue3 >"" && paramValue4 > "")
					{
						strValue3 = paramValue3;
						strValue4 = paramValue4;

						basar::VarString paramValue5 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE5);
						basar::VarString paramValue6 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE6);
						if (paramValue5 > "" && paramValue6 > "")
						{
							strValue5 = paramValue5;
							strValue6 = paramValue6;

							basar::VarString paramValue7 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE7);
							basar::VarString paramValue8 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE8);
							if (paramValue7 > "" && paramValue8 > "")
							{
								strValue7 = paramValue7;
								strValue8 = paramValue8;

								basar::VarString paramValue9 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE9);
								basar::VarString paramValue10 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE10);
								if (paramValue9 > "" && paramValue10 > "")
								{
									strValue9 = paramValue9;
									strValue10 = paramValue10;
								}
							}
						}
					}

				}
				else if (ruleName == "CheckOpenOrderQuantity")
				{
					internalRuleId = InternalRuleId::CheckOpenOrderQuantity;

					// verification of parameter - must be valid signed integer
					basar::VarString paramValue = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
					if (!isValidSignedNumString(paramValue))
					{
						std::ostringstream os;
						os << "invalid parameter value 1>" << paramValue << "< found for rule " << ruleName << " - must be numerical value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					intValue1 = paramValue.stoi();
				}
				else if (ruleName == "CheckOpenOrderQuantityNotEffective")
				{
					internalRuleId = InternalRuleId::CheckOpenOrderQuantityNotEffective;

					// verification of parameter - must be valid signed integer
					basar::VarString paramValue = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
					if (!isValidSignedNumString(paramValue))
					{
						std::ostringstream os;
						os << "invalid parameter value 1>" << paramValue << "< found for rule " << ruleName << " - must be numerical value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					intValue1 = paramValue.stoi();
				}
				else if (ruleName == "CheckArticleGroup")
				{
					internalRuleId = InternalRuleId::CheckArticleGroup;

					basar::VarString paramValue1 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
					if (!isValidNumString(paramValue1))
					{
						std::ostringstream os;
						os << "invalid parameter value 1>" << paramValue1 << "< found for rule " << ruleName << " - must be numerical value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue1 = paramValue1;
				}
				else if (ruleName == "CheckDayOfTheWeek")
				{
					internalRuleId = InternalRuleId::CheckDayOfTheWeek;

					basar::VarString paramValue1 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE1);
					if (!isSingleBinaryCharacter(paramValue1))
					{
						std::ostringstream os;
						os << "invalid parameter value 1>" << paramValue1 << "< found for rule " << ruleName << " - must be 0 or 1 value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue1 = paramValue1;

					basar::VarString paramValue2 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE2);
					if (!isSingleBinaryCharacter(paramValue2))
					{
						std::ostringstream os;
						os << "invalid parameter value 2>" << paramValue2 << "< found for rule " << ruleName << " - must be 0 or 1 value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue2 = paramValue2;

					basar::VarString paramValue3 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE3);
					if (!isSingleBinaryCharacter(paramValue3))
					{
						std::ostringstream os;
						os << "invalid parameter value 3>" << paramValue3 << "< found for rule " << ruleName << " - must be 0 or 1 value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue3 = paramValue3;

					basar::VarString paramValue4 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE4);
					if (!isSingleBinaryCharacter(paramValue4))
					{
						std::ostringstream os;
						os << "invalid parameter value 4>" << paramValue4 << "< found for rule " << ruleName << " - must be 0 or 1 value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue4 = paramValue4;

					basar::VarString paramValue5 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE5);
					if (!isSingleBinaryCharacter(paramValue5))
					{
						std::ostringstream os;
						os << "invalid parameter value 5>" << paramValue5 << "< found for rule " << ruleName << " - must be 0 or 1 value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue5 = paramValue5;

					basar::VarString paramValue6 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE6);
					if (!isSingleBinaryCharacter(paramValue6))
					{
						std::ostringstream os;
						os << "invalid parameter value 6>" << paramValue6 << "< found for rule " << ruleName << " - must be 0 or 1 value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue6 = paramValue6;

					basar::VarString paramValue7 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE7);
					if (!isSingleBinaryCharacter(paramValue7))
					{
						std::ostringstream os;
						os << "invalid parameter value 7>" << paramValue7 << "< found for rule " << ruleName << " - must be 0 or 1 value";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue7 = paramValue7;

					basar::VarString paramValue8 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE8);
					if (!isValidTimeString(paramValue8))
					{
						std::ostringstream os;
						os << "invalid parameter value 8>" << paramValue8 << "< found for rule " << ruleName << " - must be valid time value hh:mm:ss";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue8 = paramValue8;

					basar::VarString paramValue9 = ruleIterator.getString(domMod::deliveryparam::DELIVERYPARAM_VALUE9);
					if (!isValidTimeString(paramValue9))
					{
						std::ostringstream os;
						os << "invalid parameter value 9>" << paramValue9 << "< found for rule " << ruleName << " - must be valid time value hh:mm:ss";
						BLOG_ERROR(m_Logger, os.str());
						fErrorFound = true;
					}
					strValue9 = paramValue9;
				}
				else
				{
				    std::ostringstream os;
					os << "unexpected rule with name "  << ruleName << " found - cannot be processed";
					BLOG_ERROR(m_Logger, os.str());
					fErrorFound = true;
				}

				if (!fErrorFound)
				{
					RuleParameter* pRuleParam = new RuleParameter();
					pRuleParam->setInternalRuleId(internalRuleId);
					pRuleParam->setRuleName(ruleName);
					pRuleParam->setRuleId(ruleIterator.getInt32(domMod::deliveryparam::DELIVERYPARAM_RULEID));
					pRuleParam->setRuleStart(ruleIterator.getInt16(domMod::deliveryparam::DELIVERYPARAM_RULESTART));
					pRuleParam->setRuleTrue(ruleIterator.getInt32(domMod::deliveryparam::DELIVERYPARAM_RULETRUE));
					pRuleParam->setRuleFalse(ruleIterator.getInt32(domMod::deliveryparam::DELIVERYPARAM_RULEFALSE));
					pRuleParam->setRuleActive(ruleIterator.getInt16(domMod::deliveryparam::DELIVERYPARAM_RULEACTIVE));
					pRuleParam->setStrValue1(strValue1);
					pRuleParam->setStrValue2(strValue2);
					pRuleParam->setStrValue3(strValue3);
					pRuleParam->setStrValue4(strValue4);
					pRuleParam->setStrValue5(strValue5);
					pRuleParam->setStrValue6(strValue6);
					pRuleParam->setStrValue7(strValue7);
					pRuleParam->setStrValue8(strValue8);
					pRuleParam->setStrValue9(strValue9);
					pRuleParam->setStrValue10(strValue10);

					pRuleParam->setIntValue1(intValue1);
					pRuleParam->setIntValue2(intValue2);
					
					//_listOfRules.push_back(pRuleParam);
					_listOfRules[id]=*pRuleParam;
				}
			}

			if (fErrorFound)
			{
				// throw an exception to signal error to calling method(s)
				std::ostringstream os;
				os << "Exception thrown: CalculationRules::initialize", "rule parameters could not be validated: ";
				BLOG_DEBUG(m_Logger, os.str());
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("CalculationRules::initialize", "rule parameters could not be validated", __FILE__, __LINE__));
			}
		}

		void CalculationRules::LogRuleResult(const bool res)
		{
			if (res)
			{
				BLOG_TRACE(m_Logger, "\ttrue");
			}
			else
			{
				BLOG_TRACE(m_Logger, "\tfalse");
			}
		}

		/*
		 * Rules 1 & 2
		 */
		bool CalculationRules::PreventManualConfig(basar::db::aspect::AccessorPropertyTable_YIterator ca, const int notChangeable)
		{
			return ca.getInt32("NL") == notChangeable;
		}

		/**
		 * Rule 3
		 */
		bool CalculationRules::CheckArticlePPEState(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckArticlePPEState (3)");//Log("CheckArticlePPEState(%s)", ca.ZA.artNr);
			auto res = ca.getString(ARTICLE_CONTINGENT_PPE) == ruleParam.getStrValue1();
			LogRuleResult(res);

			return res;
		}

		/**
		 * Rule 4
		 */
		bool CalculationRules::CheckLimitedArticleState(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckLimitedArticleState (4)");// << ca.getInt32("artno");
			auto res = ca.getInt16(ARTICLE_ALLOCATED_QUANTITY_CONTROL) == ruleParam.getIntValue1();
			LogRuleResult(res);

			return res;
		}

		/**
		 * Rule 5
		 */
		bool CalculationRules::CheckNarcoticArticleState(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckNarcoticArticleState (5)");
			auto res = ca.getString(ARTICLE_BTM) == ruleParam.getStrValue1();
			LogRuleResult(res);

			return res;
		}

		/**
		 * Rule 6
		 */
		bool CalculationRules::CheckPeriodForDelivery(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckPeriodForDelivery (6)");
			auto availableFrom = ca.getInt32(ARTICLE_DATE_AVAILBLE_FROM);
			
			bool res = false;
			if (availableFrom > 0 && availableFrom != 29991231)
			{
				// 0 date is any date and always deliverable
				// 31.12.2999 is a special date to manually define deliverable PPE contingents.
#ifdef _ORG_RULES
				auto dateMin = AddDayToPhoDate(Utils::today(), -ruleParam.getIntValue1());
				auto dateMax = AddDayToPhoDate(Utils::today(), ruleParam.getIntValue2());
				res = availableFrom > dateMin && availableFrom <= dateMax;
#else
				//auto dateMin = AddDayToPhoDate(Utils::today(), -ruleParam.getIntValue1());
				auto dateMax = AddDayToPhoDate(Utils::today(), ruleParam.getIntValue2());
				res = availableFrom <= dateMax;
#endif
			}
			else
			{
				res = true;
			}
			LogRuleResult(res);

			return res;
		}

		/**
		 * Rule 7
		 */
		bool CalculationRules::CheckArticleCoolingState(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckArticleCoolingState (7)");
			auto res = false;
			auto threshold = ruleParam.getStrValue1();
			
			basar::VarString strNeedCooling(ca.getString(ARTICLE_COOLING));
			if (strNeedCooling < "0" || strNeedCooling > "4")
			{
				std::ostringstream os;
				os << "article " << ca.getInt32(ARTICLE_ARTICLENO) << ": unexpected value >" << strNeedCooling << "< found for column zartikel.kuehlartikel";
				// throw an exception to signal error to calling method(s)
				throw basar::cmnutil::BasarRuntimeException(basar::ExceptInfo("CalculationRules::CheckArticleCoolingState", os.str(), __FILE__, __LINE__));
			}

			// now we know we can safely convert kuehlartikel value to integer
			auto needCooling = strNeedCooling.stoi();
			switch (needCooling)
			{
			case 0:
				res = true;
				break;

			case 1:
				res = threshold == "1" || threshold == "4";
				break;

			case 2:
				res = threshold == "1" || threshold == "2" || threshold == "4";
				break;

			case 3:
				res = threshold == "1" || threshold == "2" || threshold == "3" || threshold == "4";
				break;

			case 4:
				res = threshold == "4";
				break;
			}

			LogRuleResult(res);

			return res;
		}

		/**
		 * Rule 8
		 */
		bool CalculationRules::CheckArticleActiveStorageLocation(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckArticleActiveStorageLocation (8)");
			auto storageLocation = ca.getString(ARTICLE_STORAGE_LOCATION);
			auto res = storageLocation >= ruleParam.getStrValue1() && storageLocation <= ruleParam.getStrValue2();
			if (!res && ruleParam.getStrValue3() > "" && ruleParam.getStrValue4() > "")
			{
				res = res || (storageLocation >= ruleParam.getStrValue3() && storageLocation <= ruleParam.getStrValue4());
				if (!res && ruleParam.getStrValue5() > "" && ruleParam.getStrValue6() > "")
				{
					res = res || (storageLocation >= ruleParam.getStrValue5() && storageLocation <= ruleParam.getStrValue6());
					if (!res && ruleParam.getStrValue7() > "" && ruleParam.getStrValue8() > "")
					{
						res = res || (storageLocation >= ruleParam.getStrValue7() && storageLocation <= ruleParam.getStrValue8());
						if (!res && ruleParam.getStrValue9() > "" && ruleParam.getStrValue10() > "")
						{
							res = res || (storageLocation >= ruleParam.getStrValue9() && storageLocation <= ruleParam.getStrValue10());
						}
					}
				}
			}
			LogRuleResult(res);

			return res;
		}

		/**
		 * Rule 9
		 */
		bool CalculationRules::CheckOpenOrderQuantity(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckOpenOrderQuantity (9)");
			auto res = ca.getInt32(ARTICLE_OPEN_ORDER_QUANTITY) > ruleParam.getIntValue1();
			LogRuleResult(res);

			return res;
		}

		/**
		 * Rule 10
		 */
		bool CalculationRules::CheckOpenOrderQuantityNotEffective(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckOpenOrderQuantityNotEffective (10)");
			auto res = ca.getInt32(ARTICLE_OPEN_ORDER_QUANTITY_NOT_EFFECTIVE) > ruleParam.getIntValue1();
			LogRuleResult(res);

			return res;
		}

	     /**
		 * Rule 11
		 */
		bool CalculationRules::CheckArticleGroup(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckArticleGroup (11)");

			auto articleGroup = ca.getString(ARTICLE_GROUP);
			auto res = articleGroup == ruleParam.getStrValue1();
			LogRuleResult(res);

			return res;
		}

		/**
		* Rule 12
		*/
		bool CalculationRules::CheckDayOfTheWeek(const RuleParameter& ruleParam, const basar::Date calcDate,
			const basar::Time calcTime)
		{
			BLOG_TRACE(m_Logger, "CalculationRules::CheckDayOfTheWeek (12)");

			// init params rule in array
			std::string weekDays[7] = { ruleParam.getStrValue7(), ruleParam.getStrValue1(), ruleParam.getStrValue2(),
				                        ruleParam.getStrValue3(), ruleParam.getStrValue4(), ruleParam.getStrValue5(),
				                        ruleParam.getStrValue6() };

		    
			// Check if the current time is strictly between 05:00:01 and 23:59:59
			int currentDay = calcDate.getDayOfWeek();
			
			std::ostringstream os;
			os << "CalculationRules::CheckDayOfTheWeek - current week day = " << currentDay << " at time: " << calcTime;
			BLOG_TRACE(m_Logger, os.str());

			if (calcTime.getHour() > 5 ||
				(calcTime.getHour() == 5 && calcTime.getMinute() > 0) ||
				(calcTime.getHour() == 5 && calcTime.getMinute() == 0 && calcTime.getSec() > 0)
		       )
			   currentDay = currentDay + 1;

			os.clear();
			os << "CalculationRules::CheckDayOfTheWeek - calculated evaluate param day = " << currentDay;
			BLOG_TRACE(m_Logger, os.str());

			auto res = weekDays[currentDay] == "1";
			LogRuleResult(res);

			return res;
		}

		RuleResult CalculationRules::ApplyRules(const basar::db::aspect::AccessorPropertyTable_YIterator article, const basar::Date calcDate, 
			const basar::Time calcTime)
		{
			auto articelNumber = article.getInt32(ARTICLE_ARTICLENO); article.getInt32(ARTICLE_ARTICLENO);
			std::stringstream ss;
			ss << "CalculationRules::ApplyRules(" << articelNumber << ")";
			BLOG_TRACE(m_Logger, ss.str());

			bool ruleResult = false;
			std::string lastRuleName;
			// iterate over the rules and check if no subsequent rules ("true" or "false") is defined
			auto activeRule = (size_t)_ruleStart;
			do
			//for (boost::ptr_list<RuleParameter>::const_iterator iter = _listOfRules.begin(); iter != _listOfRules.end(); ++iter)
			{
				auto lastActiveRule = activeRule;

				RuleParameter currentRule = _listOfRules[activeRule];

				int expirationDate = article.getInt32(ARTICLE_DATE_EXPIRED);
				if (expirationDate > 0)
				{
					int currentDate = calcDate.getYear() * 10000 + calcDate.getMonth() * 100 + calcDate.getDay();
					if (currentDate >= expirationDate)
					{
						ruleResult = false;
						basar::VarString ruleName;
						ruleName.format("out of trade since: %d", expirationDate);
						lastRuleName = ruleName;
						break; // no further rules to evaluate article has reached expiration date --> no subsequent delivery
					}
				}

				if (currentRule.getRuleActive())
				{
					lastRuleName = currentRule.getRuleName();
				}

				// here we can be sure that only valid rule ids have to be processed
				// the rule id is validated when initializing the rule parameters
				switch (currentRule.getInternalRuleId())
				{
				case InternalRuleId::CheckArticlePPEState:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckArticlePPEState(article, currentRule);
					break;

				case InternalRuleId::CheckLimitedArticleState:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckLimitedArticleState(article, currentRule);
					break;

				case InternalRuleId::CheckNarcoticArticleState:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckNarcoticArticleState(article, currentRule);
					break;

				case InternalRuleId::CheckPeriodForDelivery:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckPeriodForDelivery(article, currentRule);
					break;

				case InternalRuleId::CheckArticleCoolingState:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckArticleCoolingState(article, currentRule);
					break;

				case InternalRuleId::CheckArticleActiveStorageLocation:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckArticleActiveStorageLocation(article, currentRule);
					break;

				case InternalRuleId::CheckOpenOrderQuantity:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckOpenOrderQuantity(article, currentRule);
					break;

				case InternalRuleId::CheckOpenOrderQuantityNotEffective:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckOpenOrderQuantityNotEffective(article, currentRule);
					break;

				case InternalRuleId::CheckArticleGroup:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckArticleGroup(article, currentRule);
					break;

				case InternalRuleId::CheckDayOfTheWeek:
					ruleResult = !currentRule.getRuleActive() ? ruleResult : CalculationRules::CheckDayOfTheWeek(currentRule, calcDate, calcTime);
					break;
				
				default:
					ruleResult = false;
					break;
				}

				//if (ruleResult)
				//{
				//	break;
				//}

				activeRule = ruleResult && _imTrue[lastActiveRule] > 0 ?
					_imTrue[lastActiveRule] : 0;
				if (activeRule == 0)
				{
					activeRule = !ruleResult && _imFalse[lastActiveRule] > 0 ?
						_imFalse[lastActiveRule] : 0;
				}
				
				
				// logging
				ss.str(std::string());
				ss << "result for RULE " << lastActiveRule;
				if (_imTrue[lastActiveRule] > 0)
				{
					ss << " from TRUE rules:" << _imTrue[lastActiveRule];
				}
				else
				{
					if (_imFalse[lastActiveRule] > 0)
					{
						ss << " from FALSE rules : " << _imFalse[lastActiveRule];
					}
					else
					{
						ss << " #end-of-rule-chain, result: " << ruleResult;
					}
				}
				ss << ", # next rule: " << activeRule;
				BLOG_TRACE(m_Logger, ss.str());
				
			} while (activeRule > 0);

			return RuleResult(lastRuleName, ruleResult ? 1 : 0);
			//return RuleResult(ruleResult ? lastRuleName : "NO_MATCHING_RULE", ruleResult ? 1 : 0);
		}

		bool CalculationRules::isValidNumString(const basar::VarString& str)
		{
			basar::VarString testStr(str);
			
			testStr.trim(basar::VarString::FIRST_END);
			// empty string not allowed
			if (testStr.empty())
				return false;

			return testStr.find_first_not_of("0123456789") == std::string::npos;
		}

		bool CalculationRules::isSingleBinaryCharacter(const basar::VarString& str)
		{
			basar::VarString testStr(str);

			testStr.trim(basar::VarString::FIRST_END);

			// empty string not allowed
			if (testStr.empty())
				return false;

			return testStr.size() == 1 && testStr.find_first_not_of("01") == std::string::npos;
		}

		bool CalculationRules::isValidSignedNumString(const basar::VarString& str)
		{
			basar::VarString testStr(str);

			testStr.trim(basar::VarString::FIRST_END);

			// allow for leading minus or plus sign
			if (!testStr.empty() && (testStr[0] == '-' || testStr[0] == '+'))
			{
				testStr = testStr.substr(1);
			}

			// empty string not allowed
			if (testStr.empty())
				return false;

			return testStr.find_first_not_of("0123456789") == std::string::npos;
		}

		bool CalculationRules::isValidTimeString(const basar::VarString& str)
		{
			bool valid = true;

			basar::VarString testStr(str);

			testStr.trim(basar::VarString::FIRST_END);

			// empty string not allowed
			if (testStr.empty())
				return true;  // valid no time specified

			boost::regex timeRegex("^([01]?[0-9]|2[0-3]):([0-5]?[0-9]):([0-5]?[0-9])$");
			valid = boost::regex_match(testStr.c_str(), timeRegex);
			if (!valid)
			{
				std::ostringstream os;
				os << "CalculationRules::isValidTimeString excetion caught for value '" << str.c_str();
				BLOG_ERROR(m_Logger, os.str());
			}
			return valid;
		}
	}
}

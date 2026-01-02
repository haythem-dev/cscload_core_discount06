#ifndef _GUARD_CALCULATION_RULES
#define _GUARD_CALCULATION_RULES

#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <string>

#include <libbasardbaspect.h>
#include "loggerpool/subsequentdeliveryrelevantcalculator_loggerpool.h"

namespace subsequentdeliveryrelevantcalculator
{
	namespace useCase
	{
		typedef enum InternalRuleId {
			CheckArticleInvalidRule,
			CheckArticlePPEState,
			CheckLimitedArticleState,
			CheckNarcoticArticleState,
			CheckPeriodForDelivery,
			CheckArticleCoolingState,
			CheckArticleActiveStorageLocation,
			CheckOpenOrderQuantity,
			CheckOpenOrderQuantityNotEffective,
			CheckArticleGroup,
			CheckDayOfTheWeek
		} TInternalRuleId;

		class RuleParameter
		{
			public:
				void setInternalRuleId(TInternalRuleId aInternalRuleId) { this->internalRuleId = aInternalRuleId; };
				TInternalRuleId getInternalRuleId() const { return this->internalRuleId; };
				
				void setRuleId(basar::Int32 aRuleId) { this->ruleId = aRuleId; };
				basar::Int32 getRuleId() const { return this->ruleId; };
				
				void setRuleStart(basar::Int32 aRuleStart) { this->ruleStart = aRuleStart; };
				basar::Int32 getRuleStart() const { return this->ruleStart; };

				void setRuleTrue(basar::Int32 aRuleTrue) { this->ruleTrue = aRuleTrue; };
				basar::Int32 getRuleTrue() const { return this->ruleTrue; };

				void setRuleFalse(basar::Int32 aRuleFalse) { this->ruleFalse = aRuleFalse; };
				basar::Int32 getRuleFalse() const { return this->ruleFalse; };

				void setRuleName(basar::VarString aRuleName) { this->ruleName = aRuleName; };
				basar::VarString getRuleName() const { return this->ruleName; };

				void setRuleActive(basar::Int16 aRuleActive) { this->ruleActive = aRuleActive != 0; };
				bool getRuleActive() { return this->ruleActive; };

				void setStrValue1(basar::VarString strValue) { this->strValue1 = strValue; };
				basar::VarString getStrValue1() const { return this->strValue1; };

				void setStrValue2(basar::VarString strValue) { this->strValue2 = strValue; };
				basar::VarString getStrValue2() const { return this->strValue2; };

				void setStrValue3(basar::VarString strValue) { this->strValue3 = strValue; };
				basar::VarString getStrValue3() const { return this->strValue3; };

				void setStrValue4(basar::VarString strValue) { this->strValue4 = strValue; };
				basar::VarString getStrValue4() const { return this->strValue4; };

				void setStrValue5(basar::VarString strValue) { this->strValue5 = strValue; };
				basar::VarString getStrValue5() const { return this->strValue5; };

				void setStrValue6(basar::VarString strValue) { this->strValue6 = strValue; };
				basar::VarString getStrValue6() const { return this->strValue6; };

				void setStrValue7(basar::VarString strValue) { this->strValue7 = strValue; };
				basar::VarString getStrValue7() const { return this->strValue7; };

				void setStrValue8(basar::VarString strValue) { this->strValue8 = strValue; };
				basar::VarString getStrValue8() const { return this->strValue8; };

				void setStrValue9(basar::VarString strValue) { this->strValue9 = strValue; };
				basar::VarString getStrValue9() const { return this->strValue9; };

				void setStrValue10(basar::VarString strValue) { this->strValue10 = strValue; };
				basar::VarString getStrValue10() const { return this->strValue10; };

				void setIntValue1(basar::Int32 intValue) { this->intValue1 = intValue; };
				basar::Int32 getIntValue1() const { return this->intValue1; };
				void setIntValue2(basar::Int32 intValue) { this->intValue2 = intValue; };
				basar::Int32 getIntValue2() const { return this->intValue2; };
				void setIntValue3(basar::Int32 intValue) { this->intValue3 = intValue; };
				basar::Int32 getIntValue3() const { return this->intValue3; };

				void setIntValue4(basar::Int32 intValue) { this->intValue4 = intValue; };
				basar::Int32 getIntValue4() const { return this->intValue4; };

				void setIntValue5(basar::Int32 intValue) { this->intValue5 = intValue; };
				basar::Int32 getIntValue5() const { return this->intValue5; };

				void setIntValue6(basar::Int32 intValue) { this->intValue6 = intValue; };
				basar::Int32 getIntValue6() const { return this->intValue6; };

		private:
				TInternalRuleId internalRuleId;
			    basar::Int32 ruleId;
				basar::Int32 ruleStart; // != 0 - rule to start with!
				basar::Int32 ruleTrue; 
				basar::Int32 ruleFalse;
				bool ruleActive;
				basar::VarString ruleName;
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
				basar::Int32 intValue1;
				basar::Int32 intValue2;
				basar::Int32 intValue3;
				basar::Int32 intValue4;
				basar::Int32 intValue5;
				basar::Int32 intValue6;
		};

		class RuleResult
		{
		public:
			RuleResult(basar::VarString ruleName, basar::Int16 subsequentDelivery) {
				this->ruleName = ruleName;
				this->subsequentDelivery = subsequentDelivery;
			};
			basar::VarString getRuleName() const { return this->ruleName; };
			basar::Int16 getSubsequentDelivery() const { return this->subsequentDelivery; };

		private:
			basar::VarString ruleName;
			basar::Int16     subsequentDelivery;

			RuleResult();
		};

		/// <summary>
		/// 
		/// </summary>
		class CalculationRules
		{
		private:
			static boost::ptr_vector<RuleParameter> _listOfRules;

			static const log4cplus::Logger& m_Logger;

			static bool isValidNumString(const basar::VarString& str);
			static bool isValidSignedNumString(const basar::VarString& str);
			static bool isSingleBinaryCharacter(const basar::VarString& str);
			static bool isValidTimeString(const basar::VarString& str);

		public:
			static const int RECCNT_BETWEEN_TRANSACT = 10000;

			static void initialize(basar::db::aspect::AccessorPropertyTableRef iterator);

			static void LogRuleResult(const bool res);

			/**
			 * Rule 1&2
			 */
			static bool PreventManualConfig(basar::db::aspect::AccessorPropertyTable_YIterator ca, const int notChangeable);

			/**
			 * Rule 3
			 */
			static bool CheckArticlePPEState(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam);

			/**
			 * Rule 4
			 */
			static bool CheckLimitedArticleState(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam);

			/**
			 * Rule 5
			 */
			static bool CheckNarcoticArticleState(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam);

			/**
			 * Rule 6
			 */
			static bool CheckPeriodForDelivery(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam);

			/**
			 * Rule 7
			 */
			static bool CheckArticleCoolingState(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam);

			/**
			 * Rule 8
			 */
			static bool CheckArticleActiveStorageLocation(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam);

			/**
			 * Rule 9
			 */
			static bool CheckOpenOrderQuantity(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam);

			/**
			 * Rule 10
			 */
			static bool CheckOpenOrderQuantityNotEffective(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam);

			/*
			* Rule 11
			*/
			static bool CheckArticleGroup(const basar::db::aspect::AccessorPropertyTable_YIterator& ca, const RuleParameter& ruleParam);

			/*
            * Rule 12
            */
			static bool CheckDayOfTheWeek(const RuleParameter& ruleParam, const basar::Date calcDate,
				const basar::Time calcTime);

			static RuleResult ApplyRules(basar::db::aspect::AccessorPropertyTable_YIterator article, const basar::Date calcDate,
				const basar::Time calcTime);
		};
	}
}
#endif

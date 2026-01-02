#include "returnrulebook.h"

namespace libcsc {
namespace returns {

	ReturnRuleBook::ReturnRuleBook()
	{}

	ReturnRuleBook::~ReturnRuleBook()
	{}

	const basar::VarString& ReturnRuleBook::getReturnResonCode() const
	{
		return m_ReturnReasonCode;
	}

	const basar::Int32& ReturnRuleBook::getCheckSequence() const
	{
		return m_CheckSequence;
	}

	const basar::VarString& ReturnRuleBook::getReturnReasonOfficialName() const
	{
		return m_ReturnReasonOfficialName;
	}

	const basar::VarString&	ReturnRuleBook::getDefaultAccCheckResultCode() const
	{
		return m_DefaultAccCheckResultCode;
	}

	ReturnAcceptanceCheckEnum ReturnRuleBook::getReturnAccCheckId() const
	{
		return m_ReturnAccCheckId;
	}

	const basar::VarString&	ReturnRuleBook::getReturnAccCheckShortname() const
	{
		return m_ReturnAccCheckShortname;
	}

	const basar::VarString&	ReturnRuleBook::getReturnAccCheckDescription() const
	{
		return m_ReturnAccCheckDescription;
	}

	const basar::VarString&	ReturnRuleBook::getAccCheckResultCode() const
	{
		return m_AccCheckResultCode;
	}

	const basar::VarString&	ReturnRuleBook::getAccCheckOfficialName() const
	{
		return m_AccCheckOfficialName;
	}

} // returns
} //libcsc

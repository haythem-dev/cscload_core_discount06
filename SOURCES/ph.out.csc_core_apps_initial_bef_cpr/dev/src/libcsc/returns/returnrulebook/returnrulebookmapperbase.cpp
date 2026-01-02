#include "returnrulebookmapperbase.h"
#include "returnrulebook.h"

namespace libcsc {
namespace returns {

	ReturnRuleBookMapperBase::ReturnRuleBookMapperBase(ReturnRuleBookPtr returnRuleBook)
		: m_ReturnRuleBook(returnRuleBook)
	{
	}

	ReturnRuleBookMapperBase::~ReturnRuleBookMapperBase()
	{
	}

	void ReturnRuleBookMapperBase::map()
	{
		doMap();
	}

	void ReturnRuleBookMapperBase::setReturnReasonCode(const basar::VarString& returnReasonCode)
	{
		m_ReturnRuleBook->m_ReturnReasonCode = returnReasonCode;
		m_ReturnRuleBook->m_ReturnReasonCode.setClean();
	}

	void ReturnRuleBookMapperBase::setCheckSequence(const basar::Int32 checkSequence)
	{
		m_ReturnRuleBook->m_CheckSequence = checkSequence;
		m_ReturnRuleBook->m_CheckSequence.setClean();
	}

	void ReturnRuleBookMapperBase::setReturnReasonOfficialName(const basar::VarString& returnReasonOfficialName)
	{
		m_ReturnRuleBook->m_ReturnReasonOfficialName = returnReasonOfficialName;
		m_ReturnRuleBook->m_ReturnReasonOfficialName.setClean();
	}

	void ReturnRuleBookMapperBase::setDefaultAccCheckResultCode(const basar::VarString& defaultAccCheckResultCode)
	{
		m_ReturnRuleBook->m_DefaultAccCheckResultCode = defaultAccCheckResultCode;
		m_ReturnRuleBook->m_DefaultAccCheckResultCode.setClean();
	}

	void ReturnRuleBookMapperBase::setReturnAccCheckId(const ReturnAcceptanceCheckEnum returnAccCheckId)
	{
		m_ReturnRuleBook->m_ReturnAccCheckId = returnAccCheckId;
		m_ReturnRuleBook->m_ReturnAccCheckId.setClean();
	}

	void ReturnRuleBookMapperBase::setReturnAccCheckShortname(const basar::VarString& returnAccCheckShortname)
	{
		m_ReturnRuleBook->m_ReturnAccCheckShortname = returnAccCheckShortname;
		m_ReturnRuleBook->m_ReturnAccCheckShortname.setClean();
	}

	void ReturnRuleBookMapperBase::setReturnAccCheckDescription(const basar::VarString& returnAccCheckDescription)
	{
		m_ReturnRuleBook->m_ReturnAccCheckDescription = returnAccCheckDescription;
		m_ReturnRuleBook->m_ReturnAccCheckDescription.setClean();
	}

	void ReturnRuleBookMapperBase::setAccCheckResultcode(const basar::VarString& accCheckResultCode)
	{
		m_ReturnRuleBook->m_AccCheckResultCode = accCheckResultCode;
		m_ReturnRuleBook->m_AccCheckResultCode.setClean();
	}

	void ReturnRuleBookMapperBase::setAccCheckOfficialName(const basar::VarString& accCheckOfficialName)
	{
		m_ReturnRuleBook->m_AccCheckOfficialName = accCheckOfficialName;
		m_ReturnRuleBook->m_AccCheckOfficialName.setClean();
	}

} //returns
} //libscs

#ifndef GUARD_LIBCSC_RETURNS_RETURNRULEBOOK_H
#define GUARD_LIBCSC_RETURNS_RETURNRULEBOOK_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include "returnacceptancecheckenum.h"

namespace libcsc {
namespace returns {

	class ReturnRuleBook
	{
		// because of OR mapping
		friend class ReturnRuleBookMapperBase;

	public:
		ReturnRuleBook();
		virtual ~ReturnRuleBook();

		virtual const basar::VarString&	getReturnResonCode() const;
		virtual const basar::Int32&		getCheckSequence() const;
		virtual const basar::VarString&	getReturnReasonOfficialName() const;
		virtual const basar::VarString&	getDefaultAccCheckResultCode() const;

		virtual ReturnAcceptanceCheckEnum getReturnAccCheckId() const;
		virtual const basar::VarString&	getReturnAccCheckShortname() const;
		virtual const basar::VarString&	getReturnAccCheckDescription() const;

		virtual const basar::VarString&	getAccCheckResultCode() const;
		virtual const basar::VarString&	getAccCheckOfficialName() const;


	private:
		libcsc::VarString	m_ReturnReasonCode;
		libcsc::Int32		m_CheckSequence;
		libcsc::VarString	m_ReturnReasonOfficialName;
		libcsc::VarString	m_DefaultAccCheckResultCode;

		libcsc::ReturnAcceptanceCheckEnum	m_ReturnAccCheckId;
		libcsc::VarString	m_ReturnAccCheckShortname;
		libcsc::VarString	m_ReturnAccCheckDescription;

		libcsc::VarString	m_AccCheckResultCode;
		libcsc::VarString	m_AccCheckOfficialName;
	};

} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNRULEBOOK_H

#ifndef GUARD_LIBCSC_RETURNS_RETURNRULEBOOKMAPPERBASE_H
#define GUARD_LIBCSC_RETURNS_RETURNRULEBOOKMAPPERBASE_H

#include "returnrulebookptr.h"
#include "returnacceptancecheckenum.h"
#include <libbasar_definitions.h>

namespace libcsc {
namespace returns {

	class ReturnRuleBookMapperBase
	{
	public:
		ReturnRuleBookMapperBase(ReturnRuleBookPtr returnRuleBook);

		void map();

	protected:
		virtual ~ReturnRuleBookMapperBase();

		virtual void doMap() = 0;

		void setReturnReasonCode(const basar::VarString& returnReasonCode);
		void setCheckSequence(const basar::Int32 checkSequence);
		void setReturnReasonOfficialName(const basar::VarString& returnReasonOfficialName);
		void setDefaultAccCheckResultCode(const basar::VarString& defaultAccCheckResultCode);

		void setReturnAccCheckId(const ReturnAcceptanceCheckEnum returnAccCheckId);
		void setReturnAccCheckShortname(const basar::VarString& returnAccCheckShortname);
		void setReturnAccCheckDescription(const basar::VarString& returnAccCheckDescription);

		void setAccCheckResultcode(const basar::VarString& accCheckResultCode);
		void setAccCheckOfficialName(const basar::VarString& accCheckOfficialName);

	private:
		ReturnRuleBookPtr m_ReturnRuleBook;

	};

} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNRULEBOOKMAPPERBASE_H

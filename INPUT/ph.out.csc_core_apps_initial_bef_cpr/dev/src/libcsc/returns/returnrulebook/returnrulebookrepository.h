#ifndef GUARD_LIBCSC_RETURNS_RETURNRULEBOOKREPOSITORY_H
#define GUARD_LIBCSC_RETURNS_RETURNRULEBOOKREPOSITORY_H

#include <returns/returnrulebook/ireturnrulebookrepository.h>
#include <persistence/iaccessorptr.h>
#include <libbasar_definitions.h>
#include "returnrulebookptr.h"

namespace basar {
	namespace db {
		namespace sql {
			class ResultsetRef;
		}
	}
}

namespace libcsc {
namespace returns {

	class ReturnRuleBookRepository : public IReturnRuleBookRepository
	{

	public:
		ReturnRuleBookRepository();
		virtual ~ReturnRuleBookRepository();

		virtual void injectReturnRuleBookAccessor(persistence::IAccessorPtr accessor);

		virtual ReturnRuleBookCollectionPtr findReturnRuleBook(const basar::VarString& returnReasonCode) const;

	private:
		persistence::IAccessorPtr m_SelectReturnRuleBoookAccessor;

	};

} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNRULEBOOKREPOSITORY_H

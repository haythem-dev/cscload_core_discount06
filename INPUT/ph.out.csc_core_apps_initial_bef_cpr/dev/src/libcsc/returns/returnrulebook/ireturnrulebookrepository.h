#ifndef GUARD_LIBCSC_RETURNS_IRETURNRULEBOOKREPOSITORY_H
#define GUARD_LIBCSC_RETURNS_IRETURNRULEBOOKREPOSITORY_H

#include <libbasar_definitions.h>
#include <returns/returnrulebook/returnrulebookptr.h>

namespace libcsc {
namespace returns {

	class IReturnRuleBookRepository
	{
	public:
		virtual ~IReturnRuleBookRepository() {}

		virtual ReturnRuleBookCollectionPtr findReturnRuleBook(const basar::VarString& returnReasonCode) const = 0;
	};

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_IRETURNRULEBOOKREPOSITORY_H

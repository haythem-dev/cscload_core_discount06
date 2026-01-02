#ifndef GUARD_LIBCSC_RETURNS_IRETURNPERIODREPOSITORY_H
#define GUARD_LIBCSC_RETURNS_IRETURNPERIODREPOSITORY_H

#include <libbasar_definitions.h>
#include <returns/returnperiod/returnperiodptr.h>
#include <returns/returnperiod/returnperiodarticletypeenum.h>

namespace libcsc {
namespace returns {

	class IReturnPeriodRepository
	{
	public:
		virtual ~IReturnPeriodRepository() {}

		virtual ReturnPeriodPtr findReturnPeriod(const basar::VarString& returnReasonCode, const ReturnPeriodArticleTypeEnum type) const = 0;
	};

} // namespace returns
} // namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_IRETURNPERIODREPOSITORY_H

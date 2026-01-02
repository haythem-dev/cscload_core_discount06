#ifndef GUARD_LIBCSC_IBT_I_BULKRANGESELECTOR_H
#define GUARD_LIBCSC_IBT_I_BULKRANGESELECTOR_H

#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

#include <set>
#include <vector>

namespace libcsc {
namespace stockbooking {

struct ReturnArticles
{
	basar::VarString ArticleCode_;
	basar::Int32 Quantity_;
	basar::Int32 ExpiryDate_;
	basar::VarString Batch_;
};

class IBulkRangeSelector
{
public:
	virtual ~IBulkRangeSelector() {}	

	virtual void bulkRangeAvailability(
		const basar::Int16 localBranchNo,
		const basar::VarString& articleCodeFrom,
		const basar::VarString& articleCodeTo,
		std::vector<std::string>& returnArticles
	) const = 0;

	virtual void bulkRangeStock(
		const basar::Int16 localBranchNo,
		const basar::VarString& articleCodeFrom,
		const basar::VarString& articleCodeTo,
		std::vector<ReturnArticles>& returnArticles,
		bool getExpiryDate = false
	) const = 0;

	virtual void bulkRangeStockAC(
		const basar::Int16 localBranchNo,
		const basar::VarString& articleCodeFrom,
		const basar::VarString& articleCodeTo,
		std::vector<ReturnArticles>& returnArticles,
		bool getExpiryDate = false
	) const = 0;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_BULKRANGESELECTOR_H

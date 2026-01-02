#ifndef GUARD_LIBCSC_IBT_BULKRANGESELECTOR_H
#define GUARD_LIBCSC_IBT_BULKRANGESELECTOR_H

#include <persistence/iaccessorptr.h>
#include <stockbooking/bulkrangeselector/ibulkrangeselector.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace stockbooking {

class BulkRangeSelector : public IBulkRangeSelector
{
public:
	BulkRangeSelector();
	virtual ~BulkRangeSelector();

	void injectSelectAccessor( persistence::IAccessorPtr accessor );		

	virtual void bulkRangeAvailability(
		const basar::Int16 localBranchNo,
		const basar::VarString& articleCodeFrom,
		const basar::VarString& articleCodeTo,
		std::vector<std::string>& returnArticles
		) const;

	virtual void bulkRangeStock(
		const basar::Int16 localBranchNo,
		const basar::VarString& articleCodeFrom,
		const basar::VarString& articleCodeTo,
		std::vector<ReturnArticles>& returnArticles,
		bool getExpiryDate = false
	) const;

	virtual void bulkRangeStockAC(
		const basar::Int16 localBranchNo,
		const basar::VarString& articleCodeFrom,
		const basar::VarString& articleCodeTo,
		std::vector<ReturnArticles>& returnArticles,
		bool getExpiryDate = false
	) const;

private:

	persistence::IAccessorPtr	m_SelectAccessor;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_BULKRANGESELECTOR_H

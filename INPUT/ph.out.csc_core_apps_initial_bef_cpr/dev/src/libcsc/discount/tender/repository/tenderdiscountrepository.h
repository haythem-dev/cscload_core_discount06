#ifndef GUARD_LIBCSC_TENDER_DISCOUNT_REPOSITORY_H
#define GUARD_LIBCSC_TENDER_DISCOUNT_REPOSITORY_H

#include <discount/tender/repository/itenderdiscountfinder.h>
#include <discount/tender/tenderdiscountcollectionptr.h>
#include <persistence/iaccessorptr.h>

namespace libcsc
{
namespace discount
{
class TenderDiscountRepository : public ITenderDiscountFinder
{
public:
	TenderDiscountRepository();
	virtual ~TenderDiscountRepository();

	void injectSelectAccessor( persistence::IAccessorPtr accessor );

	virtual void reset();
	virtual TenderDiscountListPtr findByPattern( const TenderDiscountSearchParams & params ) const;

private:
	TenderDiscountListPtr				m_TenderDiscounts;
	mutable persistence::IAccessorPtr	m_SelectAccessor;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_DISCOUNT_REPOSITORY_H

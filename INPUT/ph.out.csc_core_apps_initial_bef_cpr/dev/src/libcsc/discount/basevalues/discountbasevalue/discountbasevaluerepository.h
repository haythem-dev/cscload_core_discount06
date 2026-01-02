#ifndef GUARD_LIBCSC_DISCOUNT_BASE_VALUE_REPOSITORY_H
#define GUARD_LIBCSC_DISCOUNT_BASE_VALUE_REPOSITORY_H

#include <discount/basevalues/discountbasevalue/idiscountbasevaluerepository.h>
#include <persistence/iaccessorptr.h>

namespace libcsc
{
namespace discount
{
class DiscountBaseValueRepository : public IDiscountBaseValueRepository
{
public:
	DiscountBaseValueRepository();
	virtual ~DiscountBaseValueRepository();

	void injectSingleSelectAccessor( persistence::IAccessorPtr singleAccessor );
	void injectMultiSelectAccessor( persistence::IAccessorPtr multiAccessor );

	virtual DiscountBaseValueCollectionPtr get();
	virtual DiscountBaseValueCollectionPtr findByArticle( const IOrderBaseValueGetterPtr orderBaseValue ) const;
	virtual DiscountBaseValueCollectionPtr findByOrder( const IOrderBaseValueGetterPtr orderBaseValue ) const;

	void setIsGermany();

private:
	void combineDiscountBaseValues() const;

	mutable DiscountBaseValueCollectionPtr	m_DiscountBaseValues;
	DiscountBaseValueCollectionPtr			m_SingleArticleDiscountBaseValues;
	DiscountBaseValueCollectionPtr			m_MultiArticleDiscountBaseValues;
	persistence::IAccessorPtr				m_SingleAccessor;
	persistence::IAccessorPtr				m_MultiAccessor;
	bool									m_IsGermany;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_DISCOUNT_BASE_VALUE_REPOSITORY_H

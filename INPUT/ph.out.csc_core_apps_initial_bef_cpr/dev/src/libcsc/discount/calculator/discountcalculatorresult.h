#ifndef GUARD_LIBCSC_DISCOUNT_CALCULATOR_RESULT_H
#define GUARD_LIBCSC_DISCOUNT_CALCULATOR_RESULT_H

#include <string>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/decimal.h>
#include <datatypes/varstring.h>
#include <datatypes/property.hpp>
#include <datatypes/propertycollection.h>
#include <iostream>
#include <vector>
#include <map>
#include <discount/calculator/discountcalculatortypeenum.h>

namespace libcsc
{
namespace discount
{
struct DiscountSource
{
	enum DiscountSourceTypeEnum
	{
		DST_POSITION = 1,
		DST_MANUFACTURER,
		DST_ARTICLE_GROUP,
		DST_MANUFACTURER_GROUP
	};
	
	typedef libcsc::Property<DiscountSourceTypeEnum> DiscountSourceType; 

	libcsc::Int32			number;
	DiscountSourceType		type;
	// TODO: DK necessary?
	libcsc::VarString		pharmacyGroup;	// "000" = which pharmacygroup does the discount belong to
	libcsc::Int16			promotionNo;
	libcsc::VarString		promotionName;

	DiscountSource();
	DiscountSource( const DiscountSource & rhs );
	DiscountSource & operator=( const DiscountSource & rhs );
	bool operator==( const DiscountSource & rhs ) const;

	std::ostream & toStream( std::ostream & strm = std::cout ) const;

	bool containsUnset() const;
	bool containsClean() const;
	bool containsDirty() const;

	bool isUnset() const;
	bool isClean() const;
	bool isDirty() const;

private:
	PropertyCollection	m_PropertyCollection;
};

struct RebateInKindValue
{
	DiscountCalculatorTypeEnum	origin;
	libcsc::Int32				articleNo;
	libcsc::Int32				quantity;
	libcsc::Decimal				articlePrice;
	bool						isManufacturerRebate;
	DiscountSource				source;
	
	RebateInKindValue(
		const DiscountCalculatorTypeEnum _origin,
		const basar::Int32 _articleNo,
		const basar::Int32 _quantity,
		const basar::Decimal & _articlePrice,
		const bool _isManufacturerRebate
			);
	RebateInKindValue();
	RebateInKindValue( const RebateInKindValue & rhs );
	RebateInKindValue & operator=( const RebateInKindValue & rhs );

	bool operator==( const RebateInKindValue & rhs ) const;
	bool operator<( const RebateInKindValue & rhs ) const;

	std::ostream & toStream( std::ostream & strm = std::cout ) const;

	bool containsUnset() const;
	bool containsClean() const;
	bool containsDirty() const;

	bool isUnset() const;
	bool isClean() const;
	bool isDirty() const;

private:
	PropertyCollection	m_PropertyCollection;
};


struct DiscountResult
{
	DiscountSource					source;
	libcsc::Decimal					discountPercent;			// 5% = cdiscount.discountpct
	DiscountCalculatorTypeEnum		discountPercentOrigin;
	libcsc::Decimal					discountValue;				// 0.50 Euro = cdiscount.fixeddiscountvalue
	DiscountCalculatorTypeEnum		discountValueOrigin;
	libcsc::Decimal					discountedArticlePrice;		// 9.50 Euro = cdiscount.fixedprice TODO: rename to fixed price?
	DiscountCalculatorTypeEnum		discountedArticlePriceOrigin;

	DiscountResult();
	DiscountResult( const DiscountResult & rhs );
	DiscountResult & operator=( const DiscountResult & rhs );
	bool operator==( const DiscountResult & rhs ) const;

	std::ostream & toStream( std::ostream & strm = std::cout ) const;

	bool containsUnset() const;
	bool containsClean() const;
	bool containsDirty() const;

	bool isUnset() const;
	bool isClean() const;
	bool isDirty() const;

private:
	PropertyCollection	m_PropertyCollection;
};

struct DiscountResultBaseValue
{
	// only for single article result:
	libcsc::Int32					articleNo;					
	libcsc::Int32					quantity;					// = ordered qty
	libcsc::Decimal					baseArticlePrice;			// 10.00 Euro = zartpreis.aep

	DiscountResultBaseValue();
	DiscountResultBaseValue( const DiscountResultBaseValue & rhs );
	DiscountResultBaseValue & operator=( const DiscountResultBaseValue & rhs );
	bool operator==( const DiscountResultBaseValue & rhs ) const;

	std::ostream & toStream( std::ostream & strm = std::cout ) const;

	bool containsUnset() const;
	bool containsClean() const;
	bool containsDirty() const;

	bool isUnset() const;
	bool isClean() const;
	bool isDirty() const;

private:
	PropertyCollection	m_PropertyCollection;
};


typedef std::vector<RebateInKindValue> RebateInKindValueCollection;
typedef std::map<basar::Int32, DiscountResult> DiscountResultCollection;

class DiscountCalculatorResult
{
public:
	// public because of behaviour like a struct
	DiscountResultBaseValue			baseValue;
	DiscountResultCollection		results;				// results for each order position, 1 entry for calculation based on article 
	RebateInKindValueCollection		rebateInKindArticles;	// Natra = cdiscount.discountqty
	
	DiscountResult & getDiscountResult( const basar::Int32 positionNo );
	void addRebateInKind( const RebateInKindValue & rebate );

	bool operator==( const DiscountCalculatorResult & rhs ) const;
	std::ostream & toStream( std::ostream & strm = std::cout ) const;

	bool containsUnset() const;
	bool containsClean() const;
	bool containsDirty() const;

	bool isUnset() const;
	bool isClean() const;
	bool isDirty() const;

private:
	PropertyCollection	m_PropertyCollection;
};

} // end namespace discount
} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::DiscountSource & r )
{
	r.toStream( strm );
	return strm;
}

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::RebateInKindValue & r )
{
	r.toStream( strm );
	return strm;
}

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::DiscountResult & r )
{
	r.toStream( strm );
	return strm;
}

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::DiscountResultBaseValue & r )
{
	r.toStream( strm );
	return strm;
}

inline std::ostream & operator<<( std::ostream & strm, const libcsc::discount::DiscountCalculatorResult & r )
{
	r.toStream( strm );
	return strm;
}

#endif // GUARD_LIBCSC_DISCOUNT_CALCULATOR_RESULT_H


#ifndef GUARD_LIBCSC_DISCOUNT_CALCULATOR_COMMAND_BASE_H
#define GUARD_LIBCSC_DISCOUNT_CALCULATOR_COMMAND_BASE_H

#include <discount/calculator/commands/idiscountcalculatorcommand.h>
#include <discount/calculator/discountcalculatortypeenum.h>
#include <discount/logger/discountlogger/idiscountloggerptr.h>
#include <discount/resultprocessor/iresultprocessorptr.h>
#include <discount/logger/hierarchylogger/ihierarchyloggerptr.h>
#include <discount/basevalues/discountbasevalue/idiscountbasevaluegetterptr.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>
#include <discount/basevalues/discountbasevalue/discountbasevalueptr.h>
#include <discount/basevalues/orderbasevalue/orderitembasevaluecollectionptr.h>
#include <logger/loggerpool.h>
#include <discount/calculator/discountcalculatortypemapper.h>
#include <sstream>

//#include <pxdiscountdef.h>

namespace libcsc
{
namespace discount
{

// siehe --> enum tDiscountSpec in pxdiscountdef.h
enum DiscountSpecificationEnum
{
    DISC_SPEC_DEFAULT               = 0,
    DISC_SPEC_WHOLESALE             = 2,
    DISC_SPEC_RETAIL                = 3,
    DISC_SPEC_WHOLESALE_INDUSTRY    = 7,

    DISC_SPEC_HIGH_PRIORITY_OFFER   = 12 // DE ELAC
};

// siehe --> enum tDiscountType in pxdiscountdef.h
enum DiscountTypeEnum
{
    DISC_TYPE_DEFAULT               = 0,
    DISC_TYPE_OPEN_CONCEPT          = 12,   // DE Deine Apotheke
    DISC_TYPE_CLOSED_CONCEPT        = 13,   // DE MVDA
    DISC_TYPE_OPEN_CONCEPT_HZ       = 14,   // DE Deine Apotheke (Herstellerzuteilung)
    DISC_TYPE_CLOSED_CONCEPT_HZ     = 15,   // DE MVDA (Herstellerzuteilung)
    DISC_TYPE_SURCHARGE_EXF         = 16    // DE Aufschlag auf GEP (ExFactory) (Personal 7%)
};

enum ArticleClassificationEnum
{
    ART_CLASS_NONE,
    ART_CLASS_MANUFACTURER,
    ART_CLASS_MANUFACTURER_GROUP,
    ART_CLASS_ARTICLE_GROUP
};

static libcsc::VarString PHARMACY_GROUP_UNIVERSAL = libcsc::VarString("000");

class DiscountCalculatorCommandBase : public IDiscountCalculatorCommand
{
public:
    DiscountCalculatorCommandBase(
        const DiscountCalculatorTypeEnum parentCalcType,
        const DiscountCalculatorTypeEnum calcType
            );
    virtual ~DiscountCalculatorCommandBase();

    void inject( IDiscountBaseValueGetterPtr baseValueGetter );
    void inject( IOrderBaseValueGetterPtr baseValueGetter );
    void inject( IDiscountLoggerPtr logger );
    void inject( IResultProcessorPtr logger );
    void inject( IHierarchyLoggerPtr logger );

    virtual const DiscountCalculatorResult & calculate() const = 0;
    // log the winning commands results, after calculation on whole hierarchy is done
    virtual void processResult() const;
    virtual void processResult( const DiscountCalculatorResult & result ) const;
    // log the result including hierarchy info
    virtual void logHierarchy() const;

protected:
    const DiscountCalculatorResult & getResult() const;
    // log the results during calculation for traceability purposes
    void logCalculation( const DiscountCalculatorResult & calcResult ) const;
    IDiscountBaseValueGetterPtr getDiscountBaseValueGetter() const;
    IOrderBaseValueGetterPtr getOrderBaseValueGetter() const;
    void setResult( const DiscountCalculatorResult & calcResult ) const;
    void setResultBaseValues (DiscountCalculatorResult & calcResult) const;

    // range discounts
    void calculateDiscounts(
        DiscountCalculatorResult & calcResult,
        DiscountBaseValuePtr discountBaseValue,
        OrderItemBaseValueCollectionPtr articleClassificationList,
        const ArticleClassificationEnum artClass
            ) const;
    // article discount
    void calculateDiscount(
        DiscountCalculatorResult & calcResult,
        DiscountBaseValuePtr discountBaseValue,
        const basar::Int32 positionNo
            ) const;
    // range discounts
    void calculateRebateInKind(
        DiscountCalculatorResult & calcResult,
        DiscountBaseValuePtr discountBaseValue,
        OrderItemBaseValueCollectionPtr orderRangeValue,
        const bool isRangeCalc = false,
        const ArticleClassificationEnum artClass = ART_CLASS_NONE
            ) const;
    // article discount
    void calculateRebateInKind(
        DiscountCalculatorResult & calcResult,
        DiscountBaseValuePtr discountBaseValue,
        const bool isRangeCalc = false,
        const ArticleClassificationEnum artClass = ART_CLASS_NONE
            ) const;

    DiscountCalculatorTypeEnum getType() const;
    void setDiscountCalculatorType(const DiscountCalculatorTypeEnum type) const;
    bool areBaseValuesMatching(DiscountBaseValuePtr discountBaseValue) const;
    bool areBaseValuesMatching(DiscountBaseValuePtr discountBaseValue, OrderItemBaseValueCollectionPtr orderRangeValue) const;
    void setDiscountSourceValues(
        DiscountSource & discountSource,
        DiscountBaseValuePtr discountBaseValue,
        const ArticleClassificationEnum artClass
            ) const;
    void copyBaseValues(
        DiscountResultBaseValue & destination,
        const DiscountResultBaseValue & source
            ) const;

private:
    void calculateRebateInKind(
        DiscountCalculatorResult & calcResult,
        DiscountBaseValuePtr discountBaseValue,
        const libcsc::Int32 & discountQty,
        const bool isRangeCalc = false,
        const ArticleClassificationEnum artClass = ART_CLASS_NONE
            ) const;
    void copyOriginValues(
        DiscountCalculatorResult & destination,
        const DiscountCalculatorResult & source
            ) const;
    void calculateDiscountPct(
        DiscountResult & discountResult,
        DiscountBaseValuePtr discountBaseValue
            ) const;

    DiscountCalculatorTypeEnum          m_ParentType;
    mutable DiscountCalculatorTypeEnum  m_Type;
    mutable DiscountCalculatorResult    m_Result;
    IDiscountBaseValueGetterPtr         m_DiscountBaseValueGetter;
    IOrderBaseValueGetterPtr            m_OrderBaseValueGetter;
    mutable IDiscountLoggerPtr          m_DiscountLogger;
    mutable IResultProcessorPtr         m_ResultLogger;
    mutable IHierarchyLoggerPtr         m_HierarchyLogger;
};

} // end namespace discount
} // end namespace libcsc


#define CALC_BLOG_TRACE_METHOD(logger,message)                  \
    std::stringstream ssLog;                                    \
    ssLog << message << " - ";                                  \
    DiscountCalculatorTypeMapper::toStream( ssLog, getType() ); \
    BLOG_TRACE_METHOD( logger, ssLog.str().c_str() );

#endif // GUARD_LIBCSC_DISCOUNT_CALCULATOR_COMMAND_BASE_H

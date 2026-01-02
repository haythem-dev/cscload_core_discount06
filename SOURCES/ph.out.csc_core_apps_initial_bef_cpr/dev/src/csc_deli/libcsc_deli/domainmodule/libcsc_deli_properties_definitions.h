#ifndef GUARD_LIBCSC_DELI_PROPERTIES_DEFINITIONS_H
#define GUARD_LIBCSC_DELI_PROPERTIES_DEFINITIONS_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasarproperty_definitions.h>
#include <libbasarproperty_propertydescription.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace properties
{
    basar::ConstString NAMESPACE_NAME( "properties" );

    // in alphabetical order
    CONST_PROPERTY_DESCRIPTION( ACCOUNTING_AREA,        "accountingarea",       basar::STRING   ) // BUK: Buchungskreis
    CONST_PROPERTY_DESCRIPTION( AMOUNT,                 "amount",               basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( BRANCH_NO,              "branchno",             basar::INT16    )
    CONST_PROPERTY_DESCRIPTION( CUSTOMER_NO,            "customerno",           basar::INT32    )
    CONST_PROPERTY_DESCRIPTION( DATE,                   "date",                 basar::INT32    )
    CONST_PROPERTY_DESCRIPTION( DELIVERY_VALUE,         "deliveryvalue",        basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( DOC_NO,                 "docno",                basar::STRING   )
    CONST_PROPERTY_DESCRIPTION( DOC_TYPE,               "doctype",              basar::INT16    )
    CONST_PROPERTY_DESCRIPTION( INVOICED,               "invoiced",             basar::INT16    )
    CONST_PROPERTY_DESCRIPTION( LIMIT,                  "limit",                basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( PARTNER_NAME,           "partnername",          basar::STRING   )
    CONST_PROPERTY_DESCRIPTION( PARTNER_NO,             "partnerno",            basar::INT32    )
    CONST_PROPERTY_DESCRIPTION( SUM_CREDIT_SIDE,        "sum_creditside",       basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( SUM_DEBIT_SIDE,         "sum_debitside",        basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( SUM_GOODS_RECEIPT,      "sum_goodsreceipt",     basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( SUM_RETURNS,            "sum_returns",          basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( SUM_TURNOVER_DAY,       "sum_dayturnover",      basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( SUM_TURNOVER_MONTH,     "sum_monturnover",      basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( SUM_TURNOVER,           "sum_turnover",         basar::DECIMAL  )
    CONST_PROPERTY_DESCRIPTION( TEXT_KEY,               "textkey",              basar::STRING   )
} // end namespace properties

#endif // GUARD_LIBCSC_DELI_PROPERTIES_DEFINITIONS_H

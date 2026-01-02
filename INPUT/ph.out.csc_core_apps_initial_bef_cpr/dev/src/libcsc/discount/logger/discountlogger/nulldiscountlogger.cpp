#include "discount/logger/discountlogger/nulldiscountlogger.h"

namespace libcsc
{
namespace discount
{
NullDiscountLogger::NullDiscountLogger()
{
}

NullDiscountLogger::~NullDiscountLogger()
{
}

void NullDiscountLogger::log( const DiscountCalculatorTypeEnum, const DiscountCalculatorResult & )
{
}

void NullDiscountLogger::save()
{
}

} // end namespace discount
} // end namespace libcsc

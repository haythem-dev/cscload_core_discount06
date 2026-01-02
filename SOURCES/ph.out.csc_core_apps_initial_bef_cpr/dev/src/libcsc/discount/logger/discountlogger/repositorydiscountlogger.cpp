#include "discount/logger/discountlogger/repositorydiscountlogger.h"
#include <sstream>
#include <iostream>

namespace libcsc
{
namespace discount
{
RepositoryDiscountLogger::RepositoryDiscountLogger()
{
}

RepositoryDiscountLogger::~RepositoryDiscountLogger()
{
}

void RepositoryDiscountLogger::log( const DiscountCalculatorTypeEnum /*calcType*/, const DiscountCalculatorResult & /*calcResult*/ )
{
	// TODO
}

void RepositoryDiscountLogger::save()
{
	// TODO
}

void RepositoryDiscountLogger::reset()
{
}

} // end namespace discount
} // end namespace libcsc

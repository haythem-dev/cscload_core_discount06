#include "tenderdiscountrepository.h"
#include "persistence/iaccessor.h"
#include <discount/tender/tenderdiscountcollection.h>
#include <discount/tender/sqlmapper/tenderdiscountsqlmapper.h>
#include <sstream>
#include "logger/loggerpool.h"
#include <discount/tender/tenderdiscount.h>

namespace libcsc
{
namespace discount
{
TenderDiscountRepository::TenderDiscountRepository()
: m_TenderDiscounts( new TenderDiscountList() )
{
}

TenderDiscountRepository::~TenderDiscountRepository()
{
	m_SelectAccessor.reset();
}

void TenderDiscountRepository::injectSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_SelectAccessor = accessor;
}

void TenderDiscountRepository::reset()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerTenderDiscount(), "TenderDiscountRepository::reset()" );

	m_TenderDiscounts->clear();
}

TenderDiscountListPtr TenderDiscountRepository::findByPattern( const TenderDiscountSearchParams & params ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerTenderDiscount(), "TenderDiscountRepository::findByPattern()" );

	m_TenderDiscounts->clear();
	try
	{
		basar::db::sql::ResultsetRef resultset;
        resultset = m_SelectAccessor->select( TenderDiscountSQLMapper::getSelectSQL( params ) );

		while( resultset.next() )
		{
			TenderDiscountPtr tenderDiscount( new TenderDiscount() );
			TenderDiscountSQLMapper mapper( tenderDiscount, resultset );
			mapper.map();
			m_TenderDiscounts->push_back( tenderDiscount );
		}

	}
	catch( basar::Exception &e )
	{
        std::stringstream s;
        s << "Error TenderDiscountRepository::findByPattern: " << e.what().c_str() ;
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), s.str());
		throw;
	}

	std::stringstream ss;
	ss << "TenderDiscountRepository::findByPattern(): customerNo<" << params.customerNo << ">, articleNo<" << params.articleNo;
	ss << ">, activeOnly<" << params.activeOnly << "> - " << m_TenderDiscounts->size() << " discounts added";
	BLOG_TRACE( LoggerPool::getLoggerTenderDiscount(), ss.str().c_str() );

	return m_TenderDiscounts;
}

} // end namespace discount
} // end namespace libcsc

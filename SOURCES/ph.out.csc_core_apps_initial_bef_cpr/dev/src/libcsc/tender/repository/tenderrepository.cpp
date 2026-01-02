#include "tenderrepository.h"
#include "persistence/iaccessor.h"
#include <tender/tendercollection.h>
#include <tender/sqlmapper/tendersqlmapper.h>
#include <sstream>
#include "logger/loggerpool.h"
#include <tender/tender.h>
#include <persistence/itransactionfactory.h>
#include <parameter/branchparametergetter.h>

namespace libcsc
{
namespace tender
{
TenderRepository::TenderRepository()
{
}

TenderRepository::~TenderRepository()
{
	m_Accessor.reset();
}

void TenderRepository::injectAccessor( persistence::IAccessorPtr accessor )
{
	m_Accessor = accessor;
}

void TenderRepository::injectBranchParameterGetter(libcsc::parameter::IBranchParameterGetterPtr branchParameterGetter)
{
	m_BranchParameterGetter = branchParameterGetter;
}

TenderPtr TenderRepository::findTender( const basar::Int32 tenderNo ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerTenderDiscount(), "TenderRepository::findTender()" );

	TenderPtr tender;
	try
	{
		basar::db::sql::ResultsetRef resultset = m_Accessor->select( TenderSQLMapper::getTenderSelectSQL( tenderNo ) );
		if( resultset.next() )
		{
			tender = TenderPtr( new Tender() );
			TenderSQLMapper mapper( tender, resultset );
			mapper.map();
		}    
	}
	catch( const basar::Exception & e )
	{
		std::stringstream s;
		s << "Error TenderRepository::findTender(): " << e.what().c_str() ;
		BLOG_ERROR( libcsc::LoggerPool::getLoggerTenderDiscount(), s.str().c_str() );
		throw;
	}

	return tender;
}

TenderPtr TenderRepository::findSuccessorTender( const TenderPtr origTender, const basar::Int32 tenderState ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerTenderDiscount(), "TenderRepository::findSuccessorTender()" );

	TenderPtr tender;
	try
	{
		basar::db::sql::ResultsetRef resultset = m_Accessor->select( TenderSQLMapper::getSuccessorTenderSelectSQL( origTender, tenderState ) );
		if( resultset.next() )
		{
			tender = TenderPtr( new Tender() );
			TenderSQLMapper mapper( tender, resultset );
			mapper.map();
		}    
	}
	catch( const basar::Exception & e )
	{
		std::stringstream s;
		s << "Error TenderRepository::findSuccessorTender(): " << e.what().c_str() ;
		BLOG_ERROR( libcsc::LoggerPool::getLoggerTenderDiscount(), s.str().c_str() );
		throw;
	}

	return tender;
}

void TenderRepository::switchTenderState( const basar::Int32 tenderNo )
{
	TenderPtr tender = findTender( tenderNo );
	if( NULL == tender.get() )
	{
		return;
	}

	bool isActivated = ( 1 == tender->getTenderState() );
	bool hasRemainingQuantity = ( 0 < tender->getRemainingQuantity() );
	TenderPtr tenderToBeActivated;
	TenderPtr tenderToBeDeactivated;
	basar::Int32 tenderState4Activate = 0;
	basar::Int32 tenderState4Deactivate = 0;

	if( isActivated && hasRemainingQuantity )
	{
		return;
	}
	else if( isActivated && false == hasRemainingQuantity )
	{
		// deactivate and activate successor
		tenderToBeDeactivated = tender;
		tenderState4Deactivate = 9;
		tenderToBeActivated = findSuccessorTender( tender, 0 );
		tenderState4Activate = 1;
	}
	else if( false == isActivated && hasRemainingQuantity )
	{
		// activate and deactivate successor
		tenderToBeActivated = tender;
		tenderState4Activate = 1;
		tenderToBeDeactivated = findSuccessorTender( tender, 1 );
		tenderState4Deactivate = 0;
	}
	else if( false == isActivated && false == hasRemainingQuantity )
	{
		return;
	}

	if( NULL != tenderToBeActivated.get() )
	{
		activateTender( tenderToBeActivated, tenderState4Activate );
	}
	if( NULL != tenderToBeDeactivated.get() )
	{
		activateTender( tenderToBeDeactivated, tenderState4Deactivate );
	}
}

void TenderRepository::activateTender( const TenderPtr tender, const basar::Int32 tenderState )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerTenderDiscount(), "TenderRepository::activateTender()" );

	try
	{
		m_Accessor->execute( TenderSQLMapper::getTenderHeadStateUpdateSQL( 
			tender->getTenderNo(), tenderState, tender->getTenderState(), m_BranchParameterGetter->getOMGDuration(tender->getBranchNo() ) ) );
		m_Accessor->execute( TenderSQLMapper::getTenderPosStateUpdateSQL( tender->getTenderNo(), tenderState ) );
	}
	catch( const basar::Exception & e )
	{
		std::stringstream s;
		s << "Error TenderRepository::activateTender(): " << e.what().c_str() ;
		BLOG_ERROR( libcsc::LoggerPool::getLoggerTenderDiscount(), s.str().c_str() );
		throw;
	}
}

} // end namespace tender
} // end namespace libcsc

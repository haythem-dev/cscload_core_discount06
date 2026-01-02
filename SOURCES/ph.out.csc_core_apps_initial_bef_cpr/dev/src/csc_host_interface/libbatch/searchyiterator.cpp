//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasardbaspect.h>
#include <libbasardbaspect_exceptions.h>
#include <libbasardbsql_exceptions.h>
#include <libbasarproperty.h>
#include <libbasardbsql_connectionref.h>

#include "searchyiterator.h"

//--------------------------------------------------------------------------------------------------//
// namepsace section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace searchyiterator
{
//--------------------------------------------------------------------------------------------------//
// using declaration section
//--------------------------------------------------------------------------------------------------//
using basar::db::aspect::AccessorPropertyTable_YIterator;
using basar::db::aspect::AccessorPropertyTable_XIterator;
using basar::db::aspect::AccessorPropertyTableRef;

//--------------------------------------------------------------------------------------------------//
// object definition section
//--------------------------------------------------------------------------------------------------//
SearchYIterator::SearchYIterator( const basar::VarString & valuePairs, const log4cplus::Logger& logger )
: m_Logger( logger )
{
	using namespace basar::db::aspect;
	static basar::Int32 counter = 1;
	basar::VarString strCounter;
	strCounter.itos( counter++ );
	m_AccessorName = "SearchAccessor";
	m_AccessorName.append( strCounter );

	AccessorDefinitionRef adr = Manager::getInstance().createAccessorDefinition( m_AccessorName );
	basar::property::PropertyDescriptionListRef pdl = adr.getPropertyDescriptionList();
	pdl.construct( valuePairs );
}

SearchYIterator::~SearchYIterator()
{
	if( !m_SearchAcc.isNull() ){
		m_SearchAcc.reset();
	}
}

basar::db::aspect::AccessorPropertyTableRef SearchYIterator::getPropTab() const
{
	return getAccessor().getPropertyTable();
}

basar::db::aspect::AccessorPropertyTable_YIterator SearchYIterator::get() const
{
	init();
	return getPropTab().begin();
}

void SearchYIterator::init() const
{
	if( getPropTab().empty() ){
		getPropTab().insert( basar::FOR_UNKNOWN );
	}
}

void SearchYIterator::reset() const
{
	AccessorPropertyTable_YIterator yit = get();
	AccessorPropertyTable_XIterator xit = yit.begin();
	while( !xit.isEnd() )
	{
		xit.setPropertyState( basar::SS_UNSET );
		++xit;
	}
}

basar::db::aspect::AccessorInstanceRef SearchYIterator::getAccessor() const
{
	initAccessor();
	return m_SearchAcc;
}

void SearchYIterator::initAccessor() const
{
	if( m_SearchAcc.isNull() ){
		using namespace basar::db::aspect;
		basar::VarString instanceName = createAccessorInstanceName( m_AccessorName );
		m_SearchAcc = Manager::getInstance().createAccessorInstance( instanceName, m_AccessorName, 
																basar::db::aspect::ConnectionRef(), FULL_CACHING );
	}
}

const basar::VarString SearchYIterator::createAccessorInstanceName( const basar::VarString& accessorName ) const
{
	static basar::Int32 instanceCounter = 1;
    std::stringstream instanceName; instanceName << accessorName << "Instance_" << instanceCounter++;
	return instanceName.str().c_str();
}

} // end namespace searchyiterator
} // end namespace domMod

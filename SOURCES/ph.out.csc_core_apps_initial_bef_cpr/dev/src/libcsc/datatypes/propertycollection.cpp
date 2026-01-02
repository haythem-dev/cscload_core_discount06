#include "propertycollection.h"
#include "exceptions/emptycollectionexception.h"

namespace libcsc
{
PropertyCollection::PropertyCollection()
{
}

PropertyCollection::~PropertyCollection()
{
}

bool PropertyCollection::operator==( const PropertyCollection & rhs ) const
{
	if( m_Collection.size() != rhs.m_Collection.size() )
	{
		return false;
	}

	bool ret = true;
	InnerCollection::const_iterator leftIter = m_Collection.begin();
	InnerCollection::const_iterator rightIter = rhs.m_Collection.begin();
	for( ; ret && leftIter != m_Collection.end() && rightIter != rhs.m_Collection.end(); ++leftIter, ++rightIter )
	{
		const PropertyState & left( **leftIter );
		const PropertyState & right( **rightIter );
		ret &= ( left == right );
	}

	return ret;
}

void PropertyCollection::add( PropertyState & prop )
{
	m_Collection.insert( &prop );
}

void PropertyCollection::clear()
{
	m_Collection.clear();
}

bool PropertyCollection::containsUnset() const
{
	return containsState( UNSET );
}

bool PropertyCollection::containsClean() const
{
	return containsState( CLEAN );
}

bool PropertyCollection::containsDirty() const
{
	return containsState( DIRTY );
}

bool PropertyCollection::isUnset() const
{
	return containsOnlyState( UNSET );
}

bool PropertyCollection::isClean() const
{
	return containsOnlyState( CLEAN );
}

bool PropertyCollection::isDirty() const
{
	return containsOnlyState( DIRTY );
}

bool PropertyCollection::containsState( const PropertyStateEnum state ) const
{
	InnerCollection::const_iterator iter = m_Collection.begin();
	for( ; iter != m_Collection.end(); ++iter )
	{
		if( state == ( *iter )->getState() )
		{
			return true;
		}
	}

	return false;
}

bool PropertyCollection::containsOnlyState( const PropertyStateEnum state ) const
{
	if( m_Collection.empty() )
	{
		throw exceptions::EmptyCollectionException( basar::ExceptInfo( "PropertyCollection::containsOnlyState()", "Property collection is empty!", __FILE__, __LINE__ ) );
	}

	InnerCollection::const_iterator iter = m_Collection.begin();
	for( ; iter != m_Collection.end(); ++iter )
	{
		if( state != ( *iter )->getState() )
		{
			return false;
		}
	}

	return true;
}

void PropertyCollection::setState( const PropertyStateEnum state )
{
	InnerCollection::const_iterator iter = m_Collection.begin();
	for( ; iter != m_Collection.end(); ++iter )
	{
		if( state != ( *iter )->getState() )
		{
			( *iter )->setState( state );
		}
	}
}

void PropertyCollection::setUnset()
{
	setState(UNSET);
}

void PropertyCollection::setClean()
{
	setState(CLEAN);
}

//void PropertyCollection::setDirty()
//{
//	setState(DIRTY);
//}

} // end namespace libcsc

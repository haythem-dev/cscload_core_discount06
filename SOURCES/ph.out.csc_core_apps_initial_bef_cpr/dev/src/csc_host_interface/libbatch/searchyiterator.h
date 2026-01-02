#ifndef GUARD_DOMMOD_SEARCHYITERATOR_SEARCH_DM_H
#define GUARD_DOMMOD_SEARCHYITERATOR_SEARCH_DM_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_connectionref.h>
#include <libbasardbaspect_accessor.h>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace basar
{
	namespace db
	{
		namespace aspect
		{
			class AccessorInstanceRef;
			class AccessorPropertyTable_YIterator;
			class AccessorPropertyTableRef;
		}
	}
}

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace searchyiterator
{
//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
class SearchYIterator
{
public:
	SearchYIterator( const basar::VarString&, const log4cplus::Logger& );
	virtual ~SearchYIterator();

	basar::db::aspect::AccessorPropertyTable_YIterator get() const;
	void reset() const;

private:
    ///////////////////////////////////////////////////
    // methods
    ///////////////////////////////////////////////////
	/*! \brief copy constructor \n no-throw */
	SearchYIterator ( const SearchYIterator & r );
	/*! \brief assign operator \n no-throw */
	SearchYIterator operator = ( const SearchYIterator & r );

	void init() const;

	basar::db::aspect::AccessorPropertyTableRef getPropTab() const;
	basar::db::aspect::AccessorInstanceRef getAccessor() const;
	void initAccessor() const;
	const basar::VarString createAccessorInstanceName(
		const basar::VarString & accessorName
			) const;

    ///////////////////////////////////////////////////
    // members
    ///////////////////////////////////////////////////
	const log4cplus::Logger&					    m_Logger;

	basar::VarString								m_AccessorName;
	mutable basar::db::aspect::AccessorInstanceRef  m_SearchAcc;
};

} // end namespace searchyiterator
} // end namespace domMod

#endif // GUARD_DOMMOD_SEARCHYITERATOR_SEARCH_DM_H

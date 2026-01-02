#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVITERATOR_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVITERATOR_H

#include <iterator>
#include "csvrow.h"

namespace libcsc_deli
{
namespace infrastructure
{
namespace csv
{

    class CSVIterator
    {

    public:
        typedef std::input_iterator_tag     iterator_category;
        typedef CSVRow                      value_type;
        typedef std::size_t                 difference_type;
        typedef CSVRow*                     pointer;
        typedef CSVRow&                     reference;

        CSVIterator( std::istream& str, const char separator ) : m_Row( separator ), m_Str( str.good() ? &str : NULL )
	    {
		    ++(*this);
	    }

        explicit CSVIterator( const char separator ) : m_Row( separator ), m_Str( NULL )
	    {
	    }

        ~CSVIterator()
	    {
	    }

        // Pre Increment
        CSVIterator& operator++()
	    {
		    if( m_Str )
            {
			    (*m_Str) >> m_Row;
			    m_Str = m_Str->good() ? m_Str : NULL;
		    }

		    return *this;
	    }

        // Post increment
        CSVIterator operator++( int )
	    {
		    CSVIterator tmp(*this);
		    ++(*this);

		    return tmp;
	    }

        CSVRow const& operator*() const
        {
		    return m_Row;
	    }

        CSVRow const* operator ->() const
        {
		    return &m_Row;
	    }

        bool operator == ( CSVIterator const& rhs )
	    {
		    return ( (this == &rhs) || ( (m_Str == NULL) && (rhs.m_Str == NULL) ) );
	    }

        bool operator != ( CSVIterator const& rhs )
	    {
		    return !( (*this) == rhs );
	    }

    private:
        CSVIterator& operator = ( const CSVIterator& );

	    CSVRow              m_Row;
	    std::istream*       m_Str;
    };

} // end namespace csv
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVITERATOR_H

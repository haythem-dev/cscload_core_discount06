#include "interval.hpp"

#include <libbasarcmnutil_bstring.h>

template <typename T>
Interval<T>::Interval( const T& from, const T& to )
    : m_From( from ), m_To( to )
{
    assert( m_From < m_To );
}

template <typename T>
Interval<T>::~Interval()
{

}

template <typename T>
const T& Interval<T>::from() const
{
    return m_From;
}

template <typename T>
const T& Interval<T>::to() const
{
    return m_To;
}

template <typename T>
bool Interval<T>::contains( const T& x ) const
{
    return m_From <= x && x <= m_To;
}

// partial specification for strings
template<>
bool Interval< std::basic_string< char > >::contains( const std::basic_string< char >& x ) const
{
    // std::string operators < and > do a pure lexical comparison which isn't sufficient here
    if( x.length() < m_From.length() || x.length() > m_To.length() )
    {
        return false;
    }

    // else do normal lexical comparison
    return m_From <= x && x <= m_To; 
}

template class Interval< basar::cmnutil::BString >;
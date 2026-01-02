#ifndef GUARD_INTERVAL_H
#define GUARD_INTERVAL_H

#include <string>
#include <cassert>

// template class for intervals

template< typename T >
class Interval
{
public:
    Interval( const T& from, const T& to );
    ~Interval();

    const T& from() const;
    const T& to()   const;

    bool contains( const T& x ) const;

private:
    // forbidden
    Interval();

private:
    T           m_From;
    T           m_To;
};

#endif // GUARD_INTERVAL_H

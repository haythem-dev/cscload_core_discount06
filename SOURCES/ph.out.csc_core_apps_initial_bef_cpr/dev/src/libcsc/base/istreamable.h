#ifndef GUARD_LIBCSC_BASE_I_STREAMABLE_H
#define GUARD_LIBCSC_BASE_I_STREAMABLE_H

#include <iostream>

namespace libcsc
{
namespace base
{
class IStreamable
{
public:
    virtual std::ostream & toStream( std::ostream & strm = std::cout ) const = 0;
};

} // end namespace base
} // end namespace libcsc

inline std::ostream & operator<<( std::ostream & strm, libcsc::base::IStreamable const & r )
{
    r.toStream( strm );
    return strm;
}

#endif // GUARD_LIBCSC_BASE_I_STREAMABLE_H


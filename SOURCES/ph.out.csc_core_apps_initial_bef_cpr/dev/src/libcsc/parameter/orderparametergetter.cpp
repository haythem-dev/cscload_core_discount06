#include "orderparametergetter.h"

#ifdef WIN32
    #pragma warning (push)
    #pragma warning(disable: 4244 4430 4806 4996)
#endif

#ifdef __GNUC__
    //#pragma GCC diagnostic push
    //#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <pxorder.hpp>

#ifdef __GNUC__
    //#pragma GCC diagnostic pop
#endif

#ifdef WIN32
    #pragma warning (pop)
#endif

namespace libcsc
{
namespace parameter
{

OrderParameterGetter::OrderParameterGetter( const pxOrder* order )
: m_Order( order )
{
}

OrderParameterGetter::~OrderParameterGetter()
{
}

bool OrderParameterGetter::isInfoOrder() const
{
    return m_Order->IsPseudoLock();
}

} // end namespace parameter
} // end namespace libcsc

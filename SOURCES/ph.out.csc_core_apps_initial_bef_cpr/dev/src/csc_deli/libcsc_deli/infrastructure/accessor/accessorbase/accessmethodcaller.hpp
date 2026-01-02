#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSMETHODCALLER_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSMETHODCALLER_H

#include "exception/methodnotfoundexception.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <map>

#include <libbasardbaspect_definitions.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{

    template <typename T>
    class AccessMethodCaller
    {   
        public:
            template <typename Method, typename Object>
            void registerAccessMethod( const basar::db::aspect::AccessMethodName& name, Method method, Object o )
            {   
                AccessMethod f = boost::bind( method, o, _1, _2 );
                m_CallableMethods[ name ] = f;
            }
        
            const basar::db::aspect::ExecuteResultInfo execute( const basar::db::aspect::AccessMethodName& name, 
                                                                const T& arg, const bool flagExcept )
            {
                METHODNAME_DEF( AccessMethodCaller, execute );

                typename AccessMethodMapping::const_iterator it = m_CallableMethods.find( name );
                if( it != m_CallableMethods.end() )
                {   
                    AccessMethod f = it->second;
                    return f( arg, flagExcept );
                }
            
                basar::VarString msg = "Method '" + name + "' not found!";
                throw exceptions::MethodNotFoundException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
            }

            bool isInitialized() const
            {
                return ! m_CallableMethods.empty();
            }

        private:
            typedef boost::function< basar::db::aspect::ExecuteResultInfo( T, const bool ) > AccessMethod;
            typedef std::map< basar::db::aspect::AccessMethodName, AccessMethod >            AccessMethodMapping;
            AccessMethodMapping                                                              m_CallableMethods;
    };

} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_ACCESSMETHODCALLER_H

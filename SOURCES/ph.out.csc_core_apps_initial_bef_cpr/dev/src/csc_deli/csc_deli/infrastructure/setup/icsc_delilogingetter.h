#ifndef GUARD_CSC_DELI_INFRASTRUCTURE_SETUP_ICSC_DELILOGINGETTER_H
#define GUARD_CSC_DELI_INFRASTRUCTURE_SETUP_ICSC_DELILOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace csc_deli
{
namespace infrastructure
{
namespace setup
{
    //------------------------------------------------------------------------------//
    // class 
    //------------------------------------------------------------------------------//
    class ICSC_DELILoginGetter
    {
        public:
            virtual ~ICSC_DELILoginGetter(){};
            virtual libutil::infrastructure::login::ILoginPtr     getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
    };
} // end namespace setup
} // end namespace infrastructure
} // end namespace csc_deli

#endif // GUARD_CSC_DELI_INFRASTRUCTURE_SETUP_ICSC_DELILOGINGETTER_H

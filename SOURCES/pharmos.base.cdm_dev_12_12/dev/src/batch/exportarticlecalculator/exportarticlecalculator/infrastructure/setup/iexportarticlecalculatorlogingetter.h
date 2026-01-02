//----------------------------------------------------------------------------
/*! \file
 *  \brief
 *  \author Bischof Bjoern
 *  \date   12.07.2015
 */
//----------------------------------------------------------------------------
#ifndef GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_SETUP_IEXPORTARTICLECALCULATORLOGINGETTER_H
#define GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_SETUP_IEXPORTARTICLECALCULATORLOGINGETTER_H

//------------------------------------------------------------------------------//
// includes
//------------------------------------------------------------------------------//
#include <libutil/login.h>

//------------------------------------------------------------------------------//
// namespaces
//------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
    namespace infrastructure
    {
        namespace setup
        {
            //------------------------------------------------------------------------------//
            // class 
            //------------------------------------------------------------------------------//
            class IEXPORTARTICLECALCULATORLoginGetter
            {
                public:
                    virtual ~IEXPORTARTICLECALCULATORLoginGetter(){};
                    virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const = 0;
            };
        }
    }
}

#endif

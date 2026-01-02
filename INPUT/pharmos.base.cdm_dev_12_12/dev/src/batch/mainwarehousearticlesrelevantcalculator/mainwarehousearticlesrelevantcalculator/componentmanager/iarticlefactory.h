#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IARTICLEFACTORY_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IARTICLEFACTORY_H

#include "domainmodule/article/iarticleptr.h"

//------------------------------------------------------------------------------//
// forward declaration
//------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace componentManager
{
    class IArticleFactory
    {
        public:
            virtual ~IArticleFactory() {};

            virtual domMod::article::IArticlePtr   create( basar::db::aspect::AccessorPropertyTable_YIterator ) = 0;
    };
} // end namespace componentManager
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IARTICLEFACTORY_H

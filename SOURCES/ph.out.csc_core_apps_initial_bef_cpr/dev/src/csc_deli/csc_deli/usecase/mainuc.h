#ifndef GUARD_CSC_DELI_USECASE_MAINUC_H
#define GUARD_CSC_DELI_USECASE_MAINUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "componentmanager/iusecasegetterptr.h"

#include <libutil/irunnable.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace appl
    {
        class IEventSource;
        struct EventReturnStruct;
    }
}

namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
            class Manager;
        }
    }
}

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace useCase
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration
    //-------------------------------------------------------------------------------------------------//
    class MainUC : public libutil::useCase::IRunnable
    {
        public:
            MainUC();
            ~MainUC();

            void                                                    injectUseCaseGetter( csc_deli::componentManager::IUseCaseGetterPtr );

            // from IRunnable interface
            void                                                    run();

        private:
            MainUC( const MainUC& );
            MainUC& operator= ( const MainUC& );

            csc_deli::componentManager::IUseCaseGetterPtr           getUseCaseGetter();

            //////////////////////////////////////////////////////////////////////////////////////
            // member variables
            //////////////////////////////////////////////////////////////////////////////////////
            const log4cplus::Logger&                                m_Logger;
            csc_deli::componentManager::IUseCaseGetterPtr           m_UseCaseGetter;
    };
} // namespace useCase
} // namespace csc_deli

#endif // GUARD_CSC_DELI_USECASE_MAINUC_H

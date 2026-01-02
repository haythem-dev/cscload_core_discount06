#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_USECASE_MAINUC_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_USECASE_MAINUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "componentmanager/iusecasegetterptr.h"
#include <libutil/irunnable.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
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

        void                                              injectUseCaseGetter( componentManager::IUseCaseGetterPtr );
        void                                              run();

    private:
        MainUC(const MainUC& );
        MainUC& operator= (const MainUC& );

        componentManager::IUseCaseGetterPtr               getUseCaseGetter();

    private:
        const log4cplus::Logger&                          m_Logger;
        componentManager::IUseCaseGetterPtr               m_UseCaseGetter;
    };
} // namespace useCase
} // namespace mainwarehousearticlesrelevantcalculator

#endif //end GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_USECASE_MAINUC_H

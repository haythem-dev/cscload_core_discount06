#ifndef GUARD_LIBCSC_EXCEPTIONS_EXCEPTION_HANDLER_H
#define GUARD_LIBCSC_EXCEPTIONS_EXCEPTION_HANDLER_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// class declaration section
//-------------------------------------------------------------------------------------------------//
namespace libcsc
{
    namespace exceptions
    {
        class ExceptionHelper
        {
        public:
            static void processAccessorException(
                basar::Exception & e, 
                const log4cplus::Logger & logger,
                basar::ConstString functionName, 
                const basar::VarString & executeMethod, 
                basar::ConstString file, 
                basar::Int32 line 
                    );

            static void processBasarException( basar::Exception & e,  const log4cplus::Logger& logger, basar::ConstString functionName, basar::ConstString file, const basar::Int32 line );

            ~ExceptionHelper();

        private:
            ExceptionHelper();
        };

    } // end namespace exceptions
} // end namespace libcsc

#endif // GUARD_LIBCSC_EXCEPTIONS_EXCEPTION_HANDLER_H

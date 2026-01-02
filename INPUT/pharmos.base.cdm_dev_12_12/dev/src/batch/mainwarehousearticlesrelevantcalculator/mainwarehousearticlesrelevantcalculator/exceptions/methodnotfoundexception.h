#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_METHODNOTFOUNDEXCEPTION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_METHODNOTFOUNDEXCEPTION_H

#include <libutil/exception.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace exceptions
{
    class MethodNotFoundException : public libutil::exceptions::BaseException
    {
    public:
        MethodNotFoundException( const basar::ExceptInfo & sInfo );
        ~MethodNotFoundException();

    private:
        MethodNotFoundException();
    };

} // end namespace exceptions
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_METHODNOTFOUNDEXCEPTION_H

#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_NORULEFOUNDEXCEPTION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_NORULEFOUNDEXCEPTION_H

#include <libutil/exception.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace exceptions
{
    class NoRuleFoundException : public libutil::exceptions::BaseException
    {
    public:
        NoRuleFoundException( const basar::ExceptInfo & sInfo );
        ~NoRuleFoundException();

    private:
        NoRuleFoundException();
    };

} // end namespace exceptions
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_NORULEFOUNDEXCEPTION_H

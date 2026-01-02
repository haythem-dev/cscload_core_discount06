#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_RULEIDOUTOFBOUNDSEXCEPTION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_RULEIDOUTOFBOUNDSEXCEPTION_H

#include <libutil/exception.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace exceptions
{
    class RuleIDOutOfBoundsException : public libutil::exceptions::BaseException
    {
    public:
        RuleIDOutOfBoundsException( const basar::ExceptInfo & sInfo );
        ~RuleIDOutOfBoundsException();

    private:
        RuleIDOutOfBoundsException();
    };

} // end namespace exceptions
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_RULEIDOUTOFBOUNDSEXCEPTION_H

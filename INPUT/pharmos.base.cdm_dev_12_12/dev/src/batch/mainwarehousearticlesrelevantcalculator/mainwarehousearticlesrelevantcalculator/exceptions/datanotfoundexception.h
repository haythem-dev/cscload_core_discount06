#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_DATANOTFOUNDEXCEPTION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_DATANOTFOUNDEXCEPTION_H

#include <libutil/exception.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace exceptions
{
    class DataNotFoundException : public libutil::exceptions::BaseException
    {
    public:
        DataNotFoundException( const basar::ExceptInfo & sInfo );
        ~DataNotFoundException();

    private:
        DataNotFoundException();
    };

} // end namespace exceptions
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_EXCEPTIONS_DATANOTFOUNDEXCEPTION_H

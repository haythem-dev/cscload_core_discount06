#ifndef GUARD_LIBCSC_STOCKBOOKING_ILONGTERMLACK_CHECKER_H
#define GUARD_LIBCSC_STOCKBOOKING_ILONGTERMLACK_CHECKER_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace stockbooking {

class ILongTermLackChecker
{
    public:
        virtual ~ILongTermLackChecker() {}

        virtual bool isLongTermLack( const basar::Int32 articleNo ) const = 0;
};

}
}

#endif


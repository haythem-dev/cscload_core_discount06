#ifndef GUARD_LIBCSC_STOCKBOOKING_ILONGTERMLACK_DELETER_H
#define GUARD_LIBCSC_STOCKBOOKING_ILONGTERMLACK_DELETER_H


#include <libbasar_definitions.h>

namespace libcsc 
{
namespace stockbooking 
{

    class ILongTermLackDeleter
    {
        public:
            virtual ~ILongTermLackDeleter() {}

            virtual void deleteLongTermLack( const basar::Int32 articleNo ) = 0;
    };

}
}

#endif


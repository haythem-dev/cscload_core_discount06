#ifndef GUARD_LIBCSC_IBT_I_IBTREQUESTPROCESSINGSTATEENUM_H
#define GUARD_LIBCSC_IBT_I_IBTREQUESTPROCESSINGSTATEENUM_H

#include <datatypes/property.hpp>

namespace libcsc
{
namespace ibt
{
enum IbtRequestProcessingStateEnum
{
    Open = 0,
    ReadyForProcessing = 1,
    Processed = 2
};

typedef Property<IbtRequestProcessingStateEnum> IbtRequestProcessingState;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUESTPROCESSINGSTATEENUM_H

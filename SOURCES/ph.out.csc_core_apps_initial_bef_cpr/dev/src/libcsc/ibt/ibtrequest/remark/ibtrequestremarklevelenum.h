#ifndef GUARD_LIBCSC_IBT_IBTREQUESTREMARKLEVELENUM_H
#define GUARD_LIBCSC_IBT_IBTREQUESTREMARKLEVELENUM_H

#include <datatypes/property.hpp>

namespace libcsc
{
namespace ibt
{
enum IbtRequestRemarkLevelEnum
{
    OrderHeadRemark,
    OrderPosRemark
};

typedef Property<IbtRequestRemarkLevelEnum> IbtRequestRemarkLevel;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTREMARKLEVELENUM_H

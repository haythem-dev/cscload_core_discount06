#ifndef GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNTTYPEENUM_H
#define GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNTTYPEENUM_H

#include <datatypes/property.hpp>

namespace libcsc
{
namespace ibt
{
enum IbtRequestDiscountTypeEnum // siehe --> enum tDiscountType in pxdiscountdef.h
{
    DiscType_Default,               // default type        = 0
    DiscType_Shortrabatt,           // shortrabatt         = 1
    DiscType_Team,                  // aktionservice       = 2
    DiscType_Diabetes,              // diabetes            = 3
    DiscType_Generika,              // generikarabatt      = 4
    DiscType_Partenariat,           // partenariat         = 5
    DiscType_Overdrive,             // overdrive           = 6
    DiscType_PhoenixMagic,          // phoenix magic       = 7
    DiscType_Promotion,             // promotion rebate    = 8(BG)
    DiscType_Tender,                // Tender conditions   = 9(BG)
    DiscType_ShortLine = 11,        // Short Liner Rebate  = 11(FR)
    DiscType_Last,
    DiscType_CashDiscount           // cashdiscount(barrabatt) = 7
};

typedef Property<IbtRequestDiscountTypeEnum> IbtRequestDiscountType;

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNTTYPEENUM_H

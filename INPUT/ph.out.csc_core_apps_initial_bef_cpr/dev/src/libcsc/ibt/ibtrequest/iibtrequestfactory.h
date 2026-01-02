#ifndef GUARD_LIBCSC_IBT_I_IBTREQUEST_FACTORY_H
#define GUARD_LIBCSC_IBT_I_IBTREQUEST_FACTORY_H

#include <ibt/ibtrequest/ibtrequestptr.h>
#include <ibt/ibtrequest/discount/iibtrequestdiscountptr.h>
#include <ibt/ibtrequest/discount/ibtrequestdiscounttypeenum.h>
#include <ibt/ibtrequest/remark/iibtrequestremarkptr.h>
#include <ibt/ibtrequest/remark/ibtrequestremarklevelenum.h>
#include <types/orderremarktypeenum.inc>

namespace libcsc
{
namespace ibt
{
class IIbtRequestFactory
{
public:
	virtual ~IIbtRequestFactory() {};

	virtual IIbtRequestDiscountPtr createRequestDiscount( IbtRequestPtr ibtRequest, const IbtRequestDiscountTypeEnum discountType, const basar::Int16 paymentTargetNo ) const = 0;
	virtual IIbtRequestRemarkPtr createRequestRemark( IbtRequestPtr ibtRequest, const IbtRequestRemarkLevelEnum remarkLevel, const OrderRemarkTypeEnum remarkType ) const = 0;

};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUEST_FACTORY_H

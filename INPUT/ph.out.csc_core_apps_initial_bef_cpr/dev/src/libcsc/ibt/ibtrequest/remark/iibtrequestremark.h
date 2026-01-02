#ifndef GUARD_LIBCSC_IBT_I_IBTREQUESTREMARK_H
#define GUARD_LIBCSC_IBT_I_IBTREQUESTREMARK_H

#include <libbasar_definitions.h>
#include <base/istreamable.h>
#include <ibt/ibtrequest/remark/ibtrequestremarklevelenum.h>
#include <types/orderremarktypeenum.inc>

typedef libcsc::Property<OrderRemarkTypeEnum> OrderRemarkType;

namespace libcsc
{
namespace ibt
{
class IIbtRequestRemark : public base::IStreamable
{
public:
	virtual ~IIbtRequestRemark(){};

	virtual const IbtRequestRemarkLevel & getRemarkLevel() const = 0;
	virtual const basar::VarString & getRemark() const = 0;
	virtual const OrderRemarkType & getRemarkType() const = 0;

	virtual void setRemarkLevel( const IbtRequestRemarkLevelEnum remarkLevel ) = 0;
	virtual void setRemarkType( const OrderRemarkTypeEnum remarkType ) = 0;
	virtual void setRemark( const basar::VarString & remark ) = 0;

	virtual bool isPosRemark() const = 0;
	virtual bool isHeadRemark() const = 0;

};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUESTREMARK_H

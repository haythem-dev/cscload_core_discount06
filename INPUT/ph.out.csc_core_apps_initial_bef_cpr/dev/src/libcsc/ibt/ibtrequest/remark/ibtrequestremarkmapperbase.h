#ifndef GUARD_LIBCSC_IBT_IBTREQUESTREMARK_MAPPERBASE_H
#define GUARD_LIBCSC_IBT_IBTREQUESTREMARK_MAPPERBASE_H

#include <libbasar_definitions.h>
#include <ibt/ibtrequest/remark/ibtrequestremarkptr.h>
#include <ibt/ibtrequest/remark/ibtrequestremarklevelenum.h>
#include <types/orderremarktypeenum.inc>

namespace libcsc
{
namespace ibt
{
class IbtRequestRemarkMapperBase
{
public:
	IbtRequestRemarkMapperBase( IbtRequestRemarkPtr ibtRequestRemark );

	void map();

protected:
	virtual ~IbtRequestRemarkMapperBase();

	virtual void doMap() = 0;

	void setIbtRequestId( const basar::Int32 ibtRequestId );
	void setRemarkLevel( const IbtRequestRemarkLevelEnum remarkLevel );
	void setRemark( const basar::VarString & remark );
	void setRemarkType( const OrderRemarkTypeEnum remarkType );

private:
	IbtRequestRemarkPtr m_IbtRequestRemark;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTREMARK_MAPPERBASE_H

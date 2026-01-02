#ifndef GUARD_LIBCSC_IBT_IBTREQUESTREMARK_H
#define GUARD_LIBCSC_IBT_IBTREQUESTREMARK_H

#include <ibt/ibtrequest/remark/iibtrequestremark.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <datatypes/propertycollection.h>

namespace libcsc
{
namespace ibt
{
class IbtRequestRemark : public IIbtRequestRemark
{
    // because of OR mapping
    friend class IbtRequestRemarkMapperBase;

public:
	IbtRequestRemark();
	virtual ~IbtRequestRemark();

	const libcsc::Int32 & getIbtRequestId() const;
	virtual const IbtRequestRemarkLevel & getRemarkLevel() const;
	virtual const basar::VarString & getRemark() const;
	virtual const OrderRemarkType & getRemarkType() const;

	void setIbtRequestId( const basar::Int32 ibtRequestId );
	virtual void setRemarkLevel( const IbtRequestRemarkLevelEnum remarkLevel );
	virtual void setRemarkType( const OrderRemarkTypeEnum remarkType );
	virtual void setRemark( const basar::VarString & remark );

	virtual bool isPosRemark() const;
	virtual bool isHeadRemark() const;

	virtual std::ostream & toStream( std::ostream & strm /* = std::cout */ ) const;

	void setClean();
	bool containsDirty() const;

private:
    IbtRequestRemark( const IbtRequestRemark & );
    IbtRequestRemark & operator=( const IbtRequestRemark & );

    libcsc::Int32 m_IbtRequestId;
    IbtRequestRemarkLevel m_RemarkLevel;
	OrderRemarkType m_RemarkType;
    libcsc::VarString m_Remark;
    libcsc::PropertyCollection m_PropertyCollection;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTREMARK_H

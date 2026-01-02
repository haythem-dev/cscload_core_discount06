#ifndef GUARD_LIBCSC_IBT_IBTRESPONSE_MAPPERBASE_H
#define GUARD_LIBCSC_IBT_IBTRESPONSE_MAPPERBASE_H

#include <libbasar_definitions.h>
#include <ibt/ibtresponse/ibtresponseptr.h>

namespace libcsc
{
namespace ibt
{
class IbtResponseMapperBase
{
public:
    IbtResponseMapperBase( IbtResponsePtr ibtResponse );

    void map();

protected:
    virtual ~IbtResponseMapperBase();

    virtual void doMap() = 0;

    void setIbtResponseId( const basar::Int32 ibtResponseId );
    void setIbtRequestId( const basar::Int32 ibtRequestId );
    void setIbtOrderNo( const basar::Int32 ibtOrderNo );
    void setIbtOrderPosNo( const basar::Int32 ibtOrderPosNo );
	void setCreationDateTime( const basar::DateTime & creationDateTime );
    void setIbtConfirmedQuantity( const basar::Int32 quantity );

private:
    IbtResponsePtr	m_IbtResponse;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTRESPONSE_MAPPERBASE_H

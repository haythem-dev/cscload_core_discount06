#ifndef GUARD_LIBCSC_IBT_I_IBTRESPONSE_H
#define GUARD_LIBCSC_IBT_I_IBTRESPONSE_H

#include <libbasar_definitions.h>
#include <base/istreamable.h>
#include <datatypes/int32.h>

namespace libcsc
{
namespace ibt
{
class IIbtResponse : public base::IStreamable
{
public:
	virtual ~IIbtResponse() {};

	virtual const libcsc::Int32 & getIbtResponseId() const = 0;
    virtual const basar::Int32 & getIbtRequestId() const = 0;
    virtual const basar::Int32 & getIbtOrderNo() const = 0;
    virtual const basar::Int32 & getIbtOrderPosNo() const = 0;
    virtual const basar::DateTime & getCreationDateTime() const = 0;
    virtual const basar::Int32 & getIbtConfirmedQuantity() const = 0;

    virtual void setIbtRequestId( const basar::Int32 ibtRequestId ) = 0;
    virtual void setIbtOrderNo( const basar::Int32 ibtOrderNo ) = 0;
    virtual void setIbtOrderPosNo( const basar::Int32 ibtOrderPosNo ) = 0;
    virtual void setIbtConfirmedQuantity( const basar::Int32 quantity ) = 0;
	virtual void setNoBooking() = 0;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTRESPONSE_H


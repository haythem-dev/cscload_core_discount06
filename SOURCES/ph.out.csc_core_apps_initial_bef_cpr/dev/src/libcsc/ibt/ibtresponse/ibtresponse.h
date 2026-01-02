#ifndef GUARD_LIBCSC_IBT_IBTRESPONSE_H
#define GUARD_LIBCSC_IBT_IBTRESPONSE_H

#include <ibt/ibtresponse/iibtresponse.h>
#include <datatypes/int32.h>
#include <datatypes/datetime.h>
#include <datatypes/propertycollection.h>

namespace libcsc
{
namespace ibt
{
class IbtResponse : public IIbtResponse
{
	// because of OR mapping
    friend class IbtResponseMapperBase;
    friend class IbtResponseRepository;
    
public:
    IbtResponse();
    virtual ~IbtResponse();

	virtual const libcsc::Int32 & getIbtResponseId() const;
    virtual const basar::Int32 & getIbtRequestId() const;
    virtual const basar::Int32 & getIbtOrderNo() const;
    virtual const basar::Int32 & getIbtOrderPosNo() const;
    virtual const basar::DateTime & getCreationDateTime() const;
    virtual const basar::Int32 & getIbtConfirmedQuantity() const;

    void setIbtResponseId( const basar::Int32 ibtResponseId );
    virtual void setIbtRequestId( const basar::Int32 ibtRequestId );
    virtual void setIbtOrderNo( const basar::Int32 ibtOrderNo );
    virtual void setIbtOrderPosNo( const basar::Int32 ibtOrderPosNo );
    virtual void setIbtConfirmedQuantity( const basar::Int32 quantity );
	virtual void setNoBooking();

    virtual std::ostream & toStream( std::ostream & strm /* = std::cout */ ) const;
		
	void setClean();
	bool containsDirty() const;

private:
	IbtResponse( const IbtResponse & );
	IbtResponse & operator=( const IbtResponse & );

	libcsc::Int32 m_IbtRequestId;
	libcsc::Int32 m_IbtResponseId;
	libcsc::Int32 m_IbtOrderNo;
	libcsc::Int32 m_IbtOrderPosNo;
	libcsc::DateTime m_CreationDateTime;
	libcsc::Int32 m_IbtConfirmedQuantity;
	libcsc::PropertyCollection		m_PropertyCollection;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTRESPONSE_H

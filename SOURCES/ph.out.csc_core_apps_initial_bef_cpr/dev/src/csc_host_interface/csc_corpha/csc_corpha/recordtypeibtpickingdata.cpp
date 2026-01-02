//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeIBTPickingData
 *  \author Steffen Heinlein
 *  \date   12.11.2018
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <sstream>
#include <iomanip>
#include "recordtypeibtpickingdata.h"
#include "recordtypeformatter.h"
#include "formattingexception.h"

using namespace std;

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace recordtypes
{
	//----------------------------------------------------------------------------//
    RecordTypeIBTPickingData::RecordTypeIBTPickingData( libcsc_utils::ICSC_LoggerPtr logger )
		: RecordTypeBase( "VK", DIRECTION_SEND, logger )
	{
		METHODNAME_DEF(RecordTypeIBTPickingData, RecordTypeIBTPickingData);
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.RecordType = getRecordTypeName();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
    RecordTypeIBTPickingData::~RecordTypeIBTPickingData()
	{
		METHODNAME_DEF(RecordTypeIBTPickingData, ~RecordTypeIBTPickingData);
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeIBTPickingData::setCSCOrderNo(const basar::Long64& value)
    {
        METHODNAME_DEF(RecordTypeIBTPickingData, setCSCOrderNo);
        BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

        m_Values.CSCOrderNo = value;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeIBTPickingData::setCSCOrderPosNo(const basar::Long64& value)
    {
        METHODNAME_DEF(RecordTypeIBTPickingData, setCSCOrderPosNo);
        BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

        m_Values.CSCOrderPosNo = value;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeIBTPickingData::setDeliveryPosNo(const basar::Long64& value)
    {
        METHODNAME_DEF(RecordTypeIBTPickingData, setDeliveryPosNo);
        BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

        m_Values.DeliveryPosNo = value;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeIBTPickingData::setDeliveryQty(const basar::Long64& value)
    {
        METHODNAME_DEF(RecordTypeIBTPickingData, setDeliveryQty);
        BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

        m_Values.DeliveryQty = value;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeIBTPickingData::setBatch(const basar::VarString& value)
    {
        METHODNAME_DEF(RecordTypeIBTPickingData, setBatch);
        BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

        m_Values.Batch = value;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeIBTPickingData::setExpiryDate(const basar::Long64& value)
    {
        METHODNAME_DEF(RecordTypeIBTPickingData, setExpiryDate);
        BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

        m_Values.ExpiryDate = value;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeIBTPickingData::setIBTBranchNo(const basar::Int32& value)
    {
        METHODNAME_DEF(RecordTypeIBTPickingData, setIBTBranchNo);
        BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

        m_Values.IBTBranchNo = value;
    }
    //----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const basar::VarString RecordTypeIBTPickingData::doSerialize() const
	{
		METHODNAME_DEF(RecordTypeIBTPickingData, doSerialize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		stringstream ss;

		try
		{
			RecordTypeFormatter::serialize( m_Values.RecordType, IBTPickingDataFormat::LENGTH_RECORDTYPE, ss );
            RecordTypeFormatter::serialize(m_Values.CSCOrderNo, IBTPickingDataFormat::LENGTH_CSCORDERNO, ss);
            RecordTypeFormatter::serialize(m_Values.CSCOrderPosNo, IBTPickingDataFormat::LENGTH_CSCORDERPOSNO, ss);
            RecordTypeFormatter::serialize(m_Values.DeliveryPosNo, IBTPickingDataFormat::LENGTH_DELIVERYPOSNO, ss);
            RecordTypeFormatter::serialize(m_Values.DeliveryQty, IBTPickingDataFormat::LENGTH_DELIVERYQTY, ss);
            RecordTypeFormatter::serialize(m_Values.Batch, IBTPickingDataFormat::LENGTH_BATCH, ss);
            RecordTypeFormatter::serialize(m_Values.ExpiryDate, IBTPickingDataFormat::LENGTH_EXPIRYDATE, ss);
            RecordTypeFormatter::serialize(m_Values.IBTBranchNo, IBTPickingDataFormat::LENGTH_IBTBRANCHNO, ss);
		}
		catch( FormattingException ex )
		{
			throw FormattingException( basar::ExceptInfo( fun, "RecordTypeIBTPickingData: Formatting exception!", __FILE__, __LINE__ ) );
		}

		return ss.str().c_str();
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

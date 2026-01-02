//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeBase
 *  \author Steffen Heinlein
 *  \date   04.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include "methodcallnotsupportedexception.h"
#include "recordtypebase.h"

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
    RecordTypeBase::RecordTypeBase( const basar::VarString& recordtypename, const basar::VarString& direction, libcsc_utils::ICSC_LoggerPtr logger )
        : m_RecordTypeName( recordtypename ), m_Direction( direction ), m_Status( "  " ), m_Logger( logger )
    {
        METHODNAME_DEF( RecordTypeBase, RecordTypeBase );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    RecordTypeBase::~RecordTypeBase()
    {
        METHODNAME_DEF( RecordTypeBase, ~RecordTypeBase );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeBase::setSequentialNo( const size_t& sequentialno )
    {
        METHODNAME_DEF( RecordTypeBase, setSequentialNo );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        m_SequentialNo = sequentialno;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    const size_t& RecordTypeBase::getSequentialNo() const
    {
        METHODNAME_DEF( RecordTypeBase, getSequentialNo );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_SequentialNo;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    const basar::VarString& RecordTypeBase::getDirection() const
    {
        METHODNAME_DEF( RecordTypeBase, getDirection );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_Direction;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    const basar::VarString& RecordTypeBase::getRecordTypeName() const
    {
        METHODNAME_DEF( RecordTypeBase, getRecordTypeName );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_RecordTypeName;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    const basar::VarString& RecordTypeBase::getStatus() const
    {
        METHODNAME_DEF( RecordTypeBase, getStatus );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_Status;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    const basar::VarString RecordTypeBase::serialize() const
    {
        METHODNAME_DEF( RecordTypeBase, serialize );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return doSerialize();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    const OrderResponseValues RecordTypeBase::deserialize() const
    {
        METHODNAME_DEF( RecordTypeBase, deserialize );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return doDeserialize();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void RecordTypeBase::setRecordTypeName( const basar::VarString& recordtypename )
    {
        METHODNAME_DEF( RecordTypeBase, setRecordTypeName );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        m_RecordTypeName = recordtypename;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    const basar::VarString RecordTypeBase::doSerialize() const
    {
        METHODNAME_DEF( RecordTypeBase, doSerialize );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo( fun, "doSerialize not supported for this kind of recordtype", __FILE__, __LINE__ ) );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    const OrderResponseValues RecordTypeBase::doDeserialize() const
    {
        METHODNAME_DEF( RecordTypeBase, doDeserialize );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo( fun, "doDeserialize not supported for this kind of recordtype", __FILE__, __LINE__ ) );
        return OrderResponseValues();
    }
    //----------------------------------------------------------------------------//


} // namespace recordtypes
} // namespace corpha
} // namespace domMod

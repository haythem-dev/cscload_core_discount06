    //-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief Domain module article
 *  \author
 *  \date
 */
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "cicspharmostransactionrecord.h"
#include "pharmostransactionrecord.h"
#include "accessorinstancerefwrapper.h"
#include "property_definitions.h"
#include "methodcallnotsupportedexception.h"
#include <convhelper.h>
#include <icsc_logger.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace preparation
{
	basar::ConstString CICSPharmosTransactionRecord::ProcessingStatus::OPEN = " ";

    //--------------------------------------------------------------------------------------------------//
    // object definition section
    //--------------------------------------------------------------------------------------------------//
	CICSPharmosTransactionRecord::CICSPharmosTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord
		, AccessorInstanceRefWrapper& acc, libcsc_utils::ICSC_LoggerPtr csc_logger )
        : TransactionRecordBase( yitTransactionRecord, acc, csc_logger )
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, TransactionRecordBase )
        BLOG_TRACE_METHOD( getLogger(), fun );
	}

	CICSPharmosTransactionRecord::~CICSPharmosTransactionRecord()
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, ~CICSPharmosTransactionRecord )
        BLOG_TRACE_METHOD( getLogger(), fun );
	}

    void CICSPharmosTransactionRecord::log()
    {
        basar::VarString msg;
        basar::VarString type = getType();
        msg.format("processing CICSPharmosTransactionRecord %d of type %s ", getKbvzOffset(), type.c_str());

        m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, msg);
    }

	basar::VarString CICSPharmosTransactionRecord::getType() const
	{
		return getKbvzArt();
	}

	void CICSPharmosTransactionRecord::startProcessing()
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, startProcessing )
        BLOG_TRACE_METHOD( getLogger(), fun );
		// no implementation needed for preparation phase
	}

	void CICSPharmosTransactionRecord::finishProcessing()
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, finishProcessing )
        BLOG_TRACE_METHOD( getLogger(), fun );
		// no implementation needed for preparation phase
	}

	basar::DateTime CICSPharmosTransactionRecord::getKbvzDX01DateTime() const
	{
		METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzDX01DateTime )
	    BLOG_TRACE_METHOD( getLogger(), fun );

		libcsc_utils::TimeParts time = libcsc_utils::ConvHelper::getTimeParts4NumericTime( getKbvzDX01Time() );
		basar::Date date = libcsc_utils::ConvHelper::getDateFor8DigitsDate( getKbvzDX01Date() );

		basar::DateTime datetime;
		datetime.setDate( date.getYear(), date.getMonth(), date.getDay() );
		datetime.setTime( time.m_Hour, time.m_Minute, time.m_Second );

		return datetime;
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzDX01Date() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzDX01Date )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::DX01DATE );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzDailyClosing() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzDailyClosing )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZTADATUM );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzOffset() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzOffset )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::RECORDOFFSET );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzKSC() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzKSC )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::CSCPROCESSINGSTATUS );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzKSCTime() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzKSCTime )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::CSCPROCESSINGTIME );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzDX01Time() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzDX01Time )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::DX01PROCESSINGTIME );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzLfdNr() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzLfdNr )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::SEQUENCENO );
	}

	basar::Int16 CICSPharmosTransactionRecord::getKbvzFil() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzFil )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::dkbvz::KBVZFIL );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzPZN() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzPZN )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZPZN );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzMeng() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzMeng )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZMENG );
	}

	basar::Int16 CICSPharmosTransactionRecord::getKbvzBukz() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzBukz )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::dkbvz::KBVZBUKZ );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzArt() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzArt )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZART );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzTime() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzTime )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZTIME );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzDate() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzDate )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZDATE );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzLgfnr() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzLgfnr )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZLGFNR );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzKSCAnr() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzKSCAnr )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZKSCANR );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzLgnr() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzLgnr )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZLGNR );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzStat() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzStat )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZSTAT );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzET3() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzET3 )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZET3 );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzWber() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzWber )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZWBER );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzVerf() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzVerf )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZVERF );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzP1Pos() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzP1Pos )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZP1POS );
	}

	basar::Decimal CICSPharmosTransactionRecord::getKbvzGEP() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzGEP )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::dkbvz::KBVZGEP );
	}

	basar::Decimal CICSPharmosTransactionRecord::getKbvzAEP() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzAEP )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::dkbvz::KBVZAEP );
	}

	basar::Decimal CICSPharmosTransactionRecord::getKbvzAVP() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzAVP )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::dkbvz::KBVZAVP );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzKVerf() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzKVerf )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZKVERF );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzKLgfnr() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzKLgfnr )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZKLGFNR );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzKGEP() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzKGEP )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZKGEP );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzKAEP() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzKAEP )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZKAEP );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzKAVP() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzKAVP )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZKAVP );
	}

	basar::Int16 CICSPharmosTransactionRecord::getKbvzMFil() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzMFil )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt16( properties::dkbvz::KBVZMFIL );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzStatus() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzStatus )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZSTATUS );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzExport() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzExport )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZEXPORT );
	}

	basar::Decimal CICSPharmosTransactionRecord::getKbvzWert() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzWert )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getDecimal( properties::dkbvz::KBVZWERT );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzCloSa() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzCloSa )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZCLOSA );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzCloZeit() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzCloZeit )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZCLOZEIT );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzCloAnr() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzCloAnr )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZCLOANR );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzCloPos() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzCloPos )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getInt32( properties::dkbvz::KBVZCLOPOS );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzCharge() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzCharge )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZCHARGE );
	}

	basar::VarString CICSPharmosTransactionRecord::getKbvzBatch() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getKbvzBatch )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		return m_YitTransactionRecord.getString( properties::dkbvz::KBVZBATCH );
	}

	basar::Int32 CICSPharmosTransactionRecord::getKbvzBeslaNr() const
	{
		METHODNAME_DEF(CICSPharmosTransactionRecord, getKbvzBeslaNr)
			BLOG_TRACE_METHOD(getLogger(), fun);
		return m_YitTransactionRecord.getInt32(properties::dkbvz::KBVZBESLANR);
	}

	const basar::VarString& CICSPharmosTransactionRecord::getSaveAccessMethod() const
	{
        METHODNAME_DEF( CICSPharmosTransactionRecord, getSaveAccessMethod )
	    BLOG_TRACE_METHOD( getLogger(), fun );
		throw libcsc_utils::MethodCallNotSupportedException( basar::ExceptInfo(fun, "getSaveAccessMethod not supported!", __FILE__, __LINE__));

		#ifndef WIN32
			return properties::dkbvz::KBVZBATCH.getName(); // BAD EVIL EX ORBITANT HACK Nur um UNIX Warning wegzubekommen...!!!
		#endif
	}

} // namespace preparation
} // namespace pharmosTransaction
} // namespace domMod

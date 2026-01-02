//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeChangeArticleMasterData
 *  \author Frank Naumann
 *  \date   26.01.2015
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypechangearticlemasterdata.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "pharmostransactionrecord.h"

#include <icsc_logger.h>

#include "pxartbaseptr.h"
#include "pvhx01_includes.h"
#include <pxartmas.hpp>

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod {
namespace pharmosTransaction {
namespace processing {

//----------------------------------------------------------------------------//

RecordTypeChangeArticleMasterData::RecordTypeChangeArticleMasterData()
{
}

//----------------------------------------------------------------------------//

RecordTypeChangeArticleMasterData::~RecordTypeChangeArticleMasterData()
{
}

//----------------------------------------------------------------------------//

void RecordTypeChangeArticleMasterData::doTransform(const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target) const
{
    METHODNAME_DEF( RecordTypeChangeArticleMasterData, doTransform );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		target->setBranchNo(0); // -> ZDP
		target->setOrigin(core::PharmosTransactionRecord::Origin::ZDP);
		target->setArticleNo(source->getArticleNo());
		target->setDailyClosing(source->getEntryDateTime().getDate());
		target->setVSEOffset(source->getTransferId());
		if (source->getFieldName() == FIELDNAME_VERTRIEBSSPERRE)
			target->setBookingType(BOOKINGTYPE_VERTRIEBSSPERRE);
		target->setBatch(source->getFieldValue());
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeChangeArticleMasterData::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeChangeArticleMasterData::doTransform...-text generic exception caught", source );
	}
}

//----------------------------------------------------------------------------//

void RecordTypeChangeArticleMasterData::process(const core::TransactionRecordBasePtr record) const
{
    METHODNAME_DEF( RecordTypeChangeArticleMasterData, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	
	switch (record->getBookingType())
	{
		case BOOKINGTYPE_VERTRIEBSSPERRE:
			processVertriebsSperre(record);
			break;
		default:
			break;
	}
}

//----------------------------------------------------------------------------//

void RecordTypeChangeArticleMasterData::processVertriebsSperre(const core::TransactionRecordBasePtr record) const
{
//  Aus tpldzentral.cxx
//	ETARTSCHALTER4 = 0;
//	if ( a.PRODUKTART[0] == '3' )			ETARTSCHALTER4 += 16384;
//	if ( a.NAHRUNGSERGAENZUNG[0] == 'G')	ETARTSCHALTER4 += 2;
	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );
        
		pxArtMaster article(m_PXVBSession->get(), record->getArticleNo(), cDBGET_FORUPDATE);
		
		if (article.IsGoodState())
		{
			switch (record->getBatch().at(0))
			{
				case 'G':
					article.ArtMFlags().SetOhneZertifikat();
					break;
				default:
					article.ArtMFlags().ClearOhneZertifikat();
					break;
			}
			article.Put();
		}

		if (article.IsGoodState())
		{
			m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
		}
		else
		{
			m_PXVBDBConnection->rollbackTransaction();
			m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "record process pxverbund rollback - pxArtMaster not in good state", record );
		}
		record->markAsProcessed();
	}
	catch( basar::Exception& ex )
	{
		m_CSC_Logger->logBasarException("RecordTypeChangeArticleMasterData::processVertriebsSperre-text basar exception caught", ex, record );
	}
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeChangeArticleMasterData::processVertriebsSperre...-text generic exception", record );
	}
}

//----------------------------------------------------------------------------//

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

//----------------------------------------------------------------------------//

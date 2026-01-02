#include "documentprintinfouc.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include "domainmodule/phadextransaction/transactionrecord/documentprintinfo/idocumentprintinfo.h"
#include "domainmodule/csc_phadex_properties_definitions.h"

#include "document/componentmanager/documentcomponentmanager.h"
#include "document/documentprintinfo/documentprintinforepositoryptr.h"
#include "document/documentprintinfo/documentprintinforepository.h"
#include "document/documentprintinfo/documentprintinfo.h"

#include <pxxmit.hpp>

namespace csc_phadex
{
namespace useCase
{
DocumentPrintInfoUC::DocumentPrintInfoUC()
: m_logger( LoggerPool::getLoggerUseCases() )
{
    METHODNAME_DEF( DocumentPrintInfoUC, DocumentPrintInfoUC );
    BLOG_TRACE_METHOD( m_logger, fun );
}

DocumentPrintInfoUC::~DocumentPrintInfoUC()
{
    METHODNAME_DEF( DocumentPrintInfoUC, ~DocumentPrintInfoUC );
    BLOG_TRACE_METHOD( m_logger, fun );
}

void DocumentPrintInfoUC::injectPxOrderTransmit(pxOrderTransmitPtr xmit)
{
    m_pxOrderTransmit = xmit;
}

void DocumentPrintInfoUC::setDocumentPrintInfo(csc_phadex::domMod::phadexTransaction::IDocumentPrintInfoPtr documentPrintInfo)
{
    m_documentPrintInfo = documentPrintInfo;
}

void DocumentPrintInfoUC::run()
{
    METHODNAME_DEF( DocumentPrintInfoUC, run );
    BLOG_TRACE_METHOD( m_logger, fun );

    try
    {
        libcsc::document::DocumentPrintInfoRepositoryPtr repo = m_pxOrderTransmit->getDocumentComponentManager()->getDocumentPrintInfoRepository();

		libcsc::document::DocumentPrintInfoPtr foundDocPrintInfo =
			repo->findDocumentPrintInfo(m_documentPrintInfo->getBranchno(), m_documentPrintInfo->getCustomerNo(),
			static_cast<DocumentTypeEnum>(m_documentPrintInfo->getDocumentType()), m_documentPrintInfo->getDocumentNo(), m_documentPrintInfo->getDocumentDate());

		if (NULL == foundDocPrintInfo.get()) // not yet saved in database
		{
			libcsc::document::DocumentPrintInfoPtr documentPrintInfo = repo->createEmptyDocumentPrintInfo();

			basar::VarString documentNo = m_documentPrintInfo->getDocumentNo();
			documentNo.trim();
			documentNo.erase(0, std::min(documentNo.find_first_not_of('0'), documentNo.size() - 1)); // remove leading zeroes

			documentPrintInfo->setDocumentNo(documentNo);
			documentPrintInfo->setBranchNo(m_documentPrintInfo->getBranchno());
			documentPrintInfo->setCustomerNo(m_documentPrintInfo->getCustomerNo());
			documentPrintInfo->setDocumentType(static_cast<DocumentTypeEnum>(m_documentPrintInfo->getDocumentType()));
			documentPrintInfo->setDocumentDate(m_documentPrintInfo->getDocumentDate());

			repo->saveDocumentPrintInfo(documentPrintInfo);
		}
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( m_logger, e.what() );
    }
}

} // namespace usecase
} // namespace csc_phadex

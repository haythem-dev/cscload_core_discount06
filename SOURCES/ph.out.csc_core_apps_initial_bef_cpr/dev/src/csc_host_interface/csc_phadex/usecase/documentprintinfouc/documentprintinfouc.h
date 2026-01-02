#ifndef GUARD_CSC_PHADEX_USECASE_DOCUMENTPRINTINFO_UC_H
#define GUARD_CSC_PHADEX_USECASE_DOCUMENTPRINTINFO_UC_H

#include "idocumentprintinfouc.h"
#include <pxordertransmitptr.h>
#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>

namespace log4cplus
{
    class Logger;
}

namespace csc_phadex
{
namespace useCase
{
class DocumentPrintInfoUC : public IDocumentPrintInfoUC
{
public:
    DocumentPrintInfoUC();
    virtual ~DocumentPrintInfoUC();

    virtual void run();
    virtual void setDocumentPrintInfo( csc_phadex::domMod::phadexTransaction::IDocumentPrintInfoPtr );
    virtual void injectPxOrderTransmit(pxOrderTransmitPtr xmit);

private:
    DocumentPrintInfoUC( const DocumentPrintInfoUC & );
    DocumentPrintInfoUC & operator= ( const DocumentPrintInfoUC & );

    csc_phadex::domMod::phadexTransaction::IDocumentPrintInfoPtr m_documentPrintInfo;
    pxOrderTransmitPtr											 m_pxOrderTransmit;
    const log4cplus::Logger &									 m_logger;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_DOCUMENTPRINTINFO_UC_H

#ifndef GUARD_CSC_PHADEX_DOMMOD_I_DOCUMENT_PRINT_INFO_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_DOCUMENT_PRINT_INFO_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction 
{
	class IDocumentPrintInfo;
	typedef boost::shared_ptr< csc_phadex::domMod::phadexTransaction::IDocumentPrintInfo > IDocumentPrintInfoPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_I_DOCUMENT_PRINT_INFO_PTR_H

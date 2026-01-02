#ifndef GUARD_CSC_PHADEX_USECASE_NARCPRINTUPDATE_UC_H
#define GUARD_CSC_PHADEX_USECASE_NARCPRINTUPDATE_UC_H

#include "inarcprintupdateuc.h"
#include "domainmodule/narcotics/inarcoticsptr.h"
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
class NarcPrintUpdateUC : public INarcPrintUpdateUC
{
public:
    NarcPrintUpdateUC();
    virtual ~NarcPrintUpdateUC();
    
    virtual void run();
    virtual void setNarcPrintUpdate( csc_phadex::domMod::phadexTransaction::INarcPrintUpdatePtr );
    void injectNarcoticsDM( csc_phadex::domMod::narcotics::INarcoticsPtr );

private:
    NarcPrintUpdateUC( const NarcPrintUpdateUC & );
    NarcPrintUpdateUC & operator= ( const NarcPrintUpdateUC & );
    
    basar::db::aspect::AccessorPropertyTable_YIterator getSearchYIterator();
    
    csc_phadex::domMod::phadexTransaction::INarcPrintUpdatePtr m_NarcPrintUpdate; 
    csc_phadex::domMod::narcotics::INarcoticsPtr m_Narcotics;
    const log4cplus::Logger & m_Logger;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_TENDERCANCELLATION_UC_H

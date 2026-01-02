#ifndef GUARD_CSC_PHADEX_DOMMOD_BLOCKED_ARTICLE_RECORD_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_BLOCKED_ARTICLE_RECORD_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
    class BlockedArticleRecord;
    typedef boost::shared_ptr< csc_phadex::domMod::phadexTransaction::BlockedArticleRecord > BlockedArticleRecordPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_BLOCKED_ARTICLE_RECORD_PTR_H

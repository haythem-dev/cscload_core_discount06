#ifndef GUARD_CSC_PHADEX_DOMMOD_I_BLOCKED_ARTICLE_RECORD_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_BLOCKED_ARTICLE_RECORD_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
	class IBlockedArticleRecord;
	typedef boost::shared_ptr< csc_phadex::domMod::phadexTransaction::IBlockedArticleRecord > IBlockedArticleRecordPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_I_BLOCKED_ARTICLE_RECORD_PTR_H

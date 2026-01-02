#ifndef GUARD_CSC_PHADEX_DOMMOD_BLOCKED_ARTICLE_RECORD_H
#define GUARD_CSC_PHADEX_DOMMOD_BLOCKED_ARTICLE_RECORD_H

#include "iblockedarticlerecord.h"
#include <domainmodule/phadextransaction/transactionrecord/transactionrecordbase.h>

namespace csc_phadex {
namespace domMod {
namespace phadexTransaction {

class BlockedArticleRecord : public IBlockedArticleRecord,
                        public TransactionRecordBase
{
public:
	BlockedArticleRecord( IPhadexTransactionPtr phadexTransaction );
    virtual ~BlockedArticleRecord();
    
	virtual basar::Int16 getBranchno() const;
	virtual const basar::DateTime & getCreationDateTime() const;
	virtual basar::Int16 getRecordType() const;
	virtual basar::Int32 getRecordNo() const;

	virtual basar::Int32 getBlockID() const;
};

}// end namespace phadexTransaction
}// end namespace domMod
}// end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_BLOCKED_ARTICLE_RECORD_H

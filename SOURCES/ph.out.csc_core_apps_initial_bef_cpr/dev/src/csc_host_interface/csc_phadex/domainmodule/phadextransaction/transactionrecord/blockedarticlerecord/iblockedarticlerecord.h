#ifndef GUARD_CSC_PHADEX_DOMMOD_I_BLOCKED_ARTICLE_RECORD_H
#define GUARD_CSC_PHADEX_DOMMOD_I_BLOCKED_ARTICLE_RECORD_H

#include <domainmodule/phadextransaction/transactionrecord/itransactionrecord.h>

namespace csc_phadex {
namespace domMod {
namespace phadexTransaction {

class IBlockedArticleRecord : public ITransactionRecord
{
public:
    virtual ~IBlockedArticleRecord() {}

	virtual basar::Int16 getBranchno() const = 0;
	virtual const basar::DateTime & getCreationDateTime() const = 0;
	virtual basar::Int16 getRecordType() const = 0;
	virtual basar::Int32 getRecordNo() const = 0;

	virtual basar::Int32 getBlockID() const = 0;
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_BLOCKED_ARTICLE_RECORD_H

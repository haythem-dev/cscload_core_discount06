#ifndef GUARD_CSC_PHADEX_DOMMOD_TRANSACTION_RECORD_BASE_H
#define GUARD_CSC_PHADEX_DOMMOD_TRANSACTION_RECORD_BASE_H

#include "itransactionrecord.h"
#include <domainmodule/phadextransaction/iphadextransactionptr.h>
#include "libbasardbaspect_accessorpropertytable_yiterator.h"

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class TransactionRecordBase : public ITransactionRecord
{
public:
	virtual ~TransactionRecordBase();

	virtual basar::Int16 getBranchno() const;
    virtual const basar::DateTime & getCreationDateTime() const;
    virtual basar::Int16 getRecordType() const;
    virtual basar::Int32 getRecordNo() const;

protected:
	// prevent instantiation of abstract class
	TransactionRecordBase( IPhadexTransactionPtr phadexTransaction );

	basar::Int16 getInt16( const basar::Int32 pos, const basar::Int32 len ) const;
	basar::Int32 getInt32( const basar::Int32 pos, const basar::Int32 len ) const;
	const basar::Date getDate( const basar::Int32 pos, const basar::Int32 len ) const;
	const basar::DateTime getDateTime( const basar::Int32 pos, const basar::Int32 len ) const;
	const basar::VarString getString( const basar::Int32 pos, const basar::Int32 len ) const;
	const basar::Decimal getDecimal( const basar::Int32 pos, const basar::Int32 len ) const;

	IPhadexTransactionPtr	m_PhadexTransaction;

private:
	TransactionRecordBase(	const TransactionRecordBase & );
	TransactionRecordBase & operator= ( const TransactionRecordBase & );
    const log4cplus::Logger &           m_Logger;
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_TRANSACTION_RECORD_BASE_H

#ifndef GUARD_CSC_PHADEX_DOMMOD_I_PHADEX_TRANSACTION_H
#define GUARD_CSC_PHADEX_DOMMOD_I_PHADEX_TRANSACTION_H

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class IPhadexTransaction
{
public:
	virtual ~IPhadexTransaction() {}

	virtual basar::db::aspect::AccessorPropertyTable_YIterator getYit() const = 0;

    virtual basar::Int16 getBranchno() const = 0;
    virtual const basar::VarString getData() const = 0;
    virtual basar::Int16 getProcessedFlag() const = 0;
    virtual const basar::DateTime & getCreationDateTime() const = 0;
    virtual const basar::DateTime & getTransferDateTime() const = 0;
    virtual const basar::DateTime & getProcessDateTime() const = 0;
    virtual basar::Int16 getRecordType() const = 0;
    virtual basar::Int32 getRecordNo() const = 0;

    virtual void setBranchno( const basar::Int16 ) = 0;
    virtual void setData( const basar::VarString & ) = 0;
    virtual void setProcessedFlag( const basar::Int16 ) = 0;
    virtual void setCreationDateTime( const basar::DateTime & ) = 0;
    virtual void setTransferDateTime( const basar::DateTime & ) = 0;
    virtual void setProcessDateTime( const basar::DateTime & ) = 0;
    virtual void setRecordType( const basar::Int16 ) = 0;
    virtual void setRecordNo( const basar::Int32 ) = 0;
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_PHADEX_TRANSACTION_H

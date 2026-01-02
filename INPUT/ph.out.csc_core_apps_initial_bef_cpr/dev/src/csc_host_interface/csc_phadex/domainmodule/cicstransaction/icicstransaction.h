#ifndef GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_H
#define GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_H

namespace csc_phadex
{
namespace domMod
{
namespace cicsTransaction
{
class ICICSTransaction
{
public:
	virtual ~ICICSTransaction() {}

    virtual basar::Int16 getBranchno() const = 0;
    virtual const basar::VarString getData() const = 0;
    virtual basar::Int32 getCreationDate() const = 0;
    virtual basar::Int32 getCreationTime() const = 0;
    virtual basar::Int16 getRecordType() const = 0;
    virtual basar::Int32 getRecordNo() const = 0;
};

} // end namespace cicsTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_H

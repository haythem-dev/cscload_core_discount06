#ifndef GUARD_CSC_PHADEX_DOMMOD_CICS_TRANSACTION_DM_H
#define GUARD_CSC_PHADEX_DOMMOD_CICS_TRANSACTION_DM_H

#include "icicstransaction.h"

#include <libutil/util.h>
#include <libutil/domainmodule.h>

namespace csc_phadex
{
namespace domMod
{
namespace cicsTransaction
{
class CICSTransactionDM : public ICICSTransaction
{
public:
    CICSTransactionDM( const basar::db::aspect::AccessorPropertyTable_YIterator );
    virtual ~CICSTransactionDM();

    virtual basar::Int16 getBranchno() const;
    virtual const basar::VarString getData() const;
    virtual basar::Int32  getCreationDate() const;
    virtual basar::Int32  getCreationTime() const;
    virtual basar::Int16 getRecordType() const;
    virtual basar::Int32 getRecordNo() const;

private:
    CICSTransactionDM( const CICSTransactionDM & );
    CICSTransactionDM & operator= ( const CICSTransactionDM & );

    basar::db::aspect::AccessorPropertyTable_YIterator  m_Yit;
    log4cplus::Logger                                   m_Logger;
};

} // end namespace cicsTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_CICS_TRANSACTION_DM_H

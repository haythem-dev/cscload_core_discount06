#ifndef GUARD_CSC_PHADEX_DOMMOD_PHADEX_TRANSACTION_DM_H
#define GUARD_CSC_PHADEX_DOMMOD_PHADEX_TRANSACTION_DM_H

#include "iphadextransaction.h"

#include <libutil/util.h>
#include <libutil/domainmodule.h>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
class PhadexTransactionDM : public IPhadexTransaction
{
public:
    PhadexTransactionDM( const basar::db::aspect::AccessorPropertyTable_YIterator );
    virtual ~PhadexTransactionDM();

	virtual basar::db::aspect::AccessorPropertyTable_YIterator getYit() const;

    virtual basar::Int16 getBranchno() const;
    virtual const basar::VarString getData() const;
    virtual basar::Int16 getProcessedFlag() const;
    virtual const basar::DateTime & getCreationDateTime() const;
    virtual const basar::DateTime & getTransferDateTime() const;
    virtual const basar::DateTime & getProcessDateTime() const;
    virtual basar::Int16 getRecordType() const;
    virtual basar::Int32 getRecordNo() const;

    virtual void setBranchno( const basar::Int16 ) ;
    virtual void setData( const basar::VarString & ) ;
    virtual void setProcessedFlag( const basar::Int16 ) ;
    virtual void setCreationDateTime( const basar::DateTime & ) ;
    virtual void setTransferDateTime( const basar::DateTime & ) ;
    virtual void setProcessDateTime( const basar::DateTime & ) ;
    virtual void setRecordType( const basar::Int16 ) ;
    virtual void setRecordNo( const basar::Int32 ) ;

private:
    PhadexTransactionDM( const PhadexTransactionDM & );
    PhadexTransactionDM & operator= ( const PhadexTransactionDM & );

    basar::db::aspect::AccessorPropertyTable_YIterator  m_Yit;
    log4cplus::Logger                                   m_Logger;
};

} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_PHADEX_TRANSACTION_DM_H

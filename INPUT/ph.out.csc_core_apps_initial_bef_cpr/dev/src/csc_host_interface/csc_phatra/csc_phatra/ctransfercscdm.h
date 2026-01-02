//-------------------------------------------------------------------------------------------------//
/*! \file		ctransfercscdm.h
 *  \brief		main interface to access transaction records from ZDP 
 *  \author		Frank Naumann
 *  \date		23.01.2015
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_CTRANSFERCSCDM_H
#define GUARD_CTRANSFERCSCDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "transactiondmbase.h"
#include "dmbase.h"

//-------------------------------------------------------------------------------------------------//

struct InitCTransferCscDM
{
	basar::VarString m_ZDPHost;
	basar::VarString m_ZDPDatabase;
};

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace domMod {
namespace pharmosTransaction {
namespace preparation {

//-------------------------------------------------------------------------------------------------//
// class declaration section
//-------------------------------------------------------------------------------------------------//

class CTransferCscDM :	public core::TransactionDMBase,
						public domMod::DMBase< InitCTransferCscDM, CTransferCscDM >
{
	public:
		static const char* getClassName() { return "CTransferCscDM"; }

//--------------------------------------------------------------------------------------------------//
// object declaration section
//--------------------------------------------------------------------------------------------------//
public:
	CTransferCscDM ( const basar::db::aspect::ConnectionRef conn, libcsc_utils::ICSC_LoggerPtr csc_logger );
	~CTransferCscDM ();

	virtual void                                                finishQuery() {}

protected:
	virtual const basar::VarString&			                    getFindByPatternAccessMethod() const;
	virtual core::TransactionRecordBasePtr	                    createTransactionRecord(basar::db::aspect::AccessorPropertyTable_YIterator yit,
																						AccessorInstanceRefWrapper& acc );
	virtual basar::db::aspect::AccessorPropertyTable_YIterator  prepareFindOpenSearchCriteria( const domMod::pharmosTransaction::core::OffSetNo );

	virtual void                                                doInit( const InitCTransferCscDM& );
	virtual void                                                doShutdown();

private:
	CTransferCscDM (const CTransferCscDM & );
	CTransferCscDM& operator= (const CTransferCscDM & );
	
	InitCTransferCscDM	m_InitCTransferCscDM;

};

//-------------------------------------------------------------------------------------------------//

} // namespace preparation
} // namespace pharmosTransaction
} // namespace domMod

//-------------------------------------------------------------------------------------------------//

#endif // GUARD_CTRANSFERCSCDM_H

//-------------------------------------------------------------------------------------------------//


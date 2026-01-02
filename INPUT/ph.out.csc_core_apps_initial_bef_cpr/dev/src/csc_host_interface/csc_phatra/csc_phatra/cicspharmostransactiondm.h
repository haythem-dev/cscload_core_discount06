//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module (cics file VSAM.DKBVZ)
 *  \author		Steffen Heinlein
 *  \date		22.06.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_CICSPHARMOSTRANSACTIONDM_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_CICSPHARMOSTRANSACTIONDM_H

#include "transactiondmbase.h"
#include "dmbase.h"
#include "initparamsdm.h"

//-------------------------------------------------------------------------------------------------//
// using declarations section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;                    
			class AccessorPropertyTableRef;
            class ConnectionRef;
        }
    }
}


namespace domMod 
{		
namespace pharmosTransaction
{
namespace preparation
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
    class CICSPharmosTransactionDM : public core::TransactionDMBase, 
                                     public domMod::DMBase< InitParamsDM, CICSPharmosTransactionDM >
    {
        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
        public:
            static const char* getClassName() { return "CICSPharmosTransactionDM"; }

	    public:
			CICSPharmosTransactionDM( const basar::db::aspect::ConnectionRef tcaconnection, libcsc_utils::ICSC_LoggerPtr csc_logger); 
		    virtual ~CICSPharmosTransactionDM(); 

            void                                                        finishQuery();

        protected:
		    virtual const basar::VarString&								getFindByPatternAccessMethod() const;
		    virtual core::TransactionRecordBasePtr						createTransactionRecord(basar::db::aspect::AccessorPropertyTable_YIterator yit, AccessorInstanceRefWrapper& acc);
		    virtual void												evaluatePreconditionFindByPattern();
            virtual void                                                doInit( const InitParamsDM& );
	        virtual void                                                doShutdown();
            virtual basar::db::aspect::AccessorPropertyTable_YIterator  prepareFindOpenSearchCriteria( const domMod::pharmosTransaction::core::OffSetNo offSetNo );

	    private:	
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    CICSPharmosTransactionDM(const CICSPharmosTransactionDM& r);
		    CICSPharmosTransactionDM& operator=(const CICSPharmosTransactionDM& r);				

            

            /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
            InitParamsDM                                                m_InitParamsDM;
    }; 

} // namespace preparation
} // namespace pharmosTransaction
} // namespace domMod

#endif 


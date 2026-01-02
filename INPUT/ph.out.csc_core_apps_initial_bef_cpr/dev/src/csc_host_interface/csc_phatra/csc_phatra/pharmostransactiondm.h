//-------------------------------------------------------------------------------------------------//
/*! \file pharmostransactiondm.h
 *  \brief main interface to access pharmos transaction data on informix side
 *  \author Julian Machata
 *  \date 27.06.2012
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_PHARMOS_TRANSACTIONDM_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_PHARMOS_TRANSACTIONDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <searchyiteratorptr.h>
#include "transactiondmbase.h"
#include "itransferkeygetter.h"
#include "dmbase.h"
#include "initparamsdm.h"
#include <icsc_loggerptr.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
    /*!\brief  */
	class PharmosTransactionDM : public TransactionDMBase, 
								 public util::ITransferKeyGetter,
								 public domMod::DMBase< InitParamsDM, PharmosTransactionDM >
	{                                   
        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
        public:
			static const char* getClassName() { return "PharmosTransactionDM"; }

        //--------------------------------------------------------------------------------------------------//
        // object declaration section
        //--------------------------------------------------------------------------------------------------//
	    public:

			PharmosTransactionDM ( const basar::db::aspect::ConnectionRef conn, libcsc_utils::ICSC_LoggerPtr csc_logger );
		    ~PharmosTransactionDM ();

        protected:
            virtual const basar::VarString&			                    getFindByPatternAccessMethod() const;
			virtual core::TransactionRecordBasePtr	                    createTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yit, 
                                                                                                 AccessorInstanceRefWrapper& acc );
			virtual basar::Int32				                    	getLastKey();
            virtual void                                                doInit( const InitParamsDM& );
	        virtual void                                                doShutdown();

            virtual basar::db::aspect::AccessorPropertyTable_YIterator  prepareFindOpenSearchCriteria( const domMod::pharmosTransaction::core::OffSetNo );

            void                                                        finishQuery(){}; //no explicit finishing needed

	    private:
            /////////////////////////////////////////////////////////////////////////
		    // private member methods
		    /////////////////////////////////////////////////////////////////////////
		    PharmosTransactionDM (const PharmosTransactionDM & );
		    PharmosTransactionDM& operator= (const PharmosTransactionDM & );

		    /////////////////////////////////////////////////////////////////////////
		    // private member variables
		    /////////////////////////////////////////////////////////////////////////
			// ...
            InitParamsDM                                                m_InitParamsDM;
	};
} // namespace core
} // namespace pharmosTransaction
} // end namespace domMod

#endif


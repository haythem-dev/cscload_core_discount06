//-------------------------------------------------------------------------------------------------//
/*! \file pharmostransactiondm.cpp
 *  \brief main interface to access pharmos transaction data on informix side
 *  \author Julian Machata
 *  \date 27.06.2012
 */
//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "pharmostransactiondm.h"
#include "property_definitions.h"
#include "pharmostransactionacc_definitions.h"
#include "pharmostransactionrecord.h"
#include <icsc_logger.h>
#include <exceptionhandler.h>

//-------------------------------------------------------------------------------------------------//
// using declarations section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
    namespace pharmosTransaction
    {
        namespace core
        {
            using basar::db::aspect::AccessorPropertyTable_YIterator;
            using basar::db::aspect::AccessorPropertyTable_XIterator;
            using basar::db::aspect::AccessorPropertyTableRef;
            using basar::db::aspect::ExecuteResultInfo;
            using basar::db::aspect::AccessorInstanceRef;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{
    //--------------------------------------------------------------------------------------------------//
    // object definition section
    //--------------------------------------------------------------------------------------------------//
    PharmosTransactionDM::PharmosTransactionDM( const basar::db::aspect::ConnectionRef conn, libcsc_utils::ICSC_LoggerPtr csc_logger )
	: TransactionDMBase(conn, lit::acc_pharmostransaction::ACC_PHARMOSTRANSACTION, csc_logger) 
	{
        METHODNAME_DEF( TransactionDM, TransactionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
	}

	//-------------------------------------------------------------------------------------------------------------------//
	PharmosTransactionDM::~PharmosTransactionDM()
	{
        METHODNAME_DEF( PharmosTransactionDM, ~PharmosTransactionDM )
        BLOG_TRACE_METHOD( (getLogger()), fun );
	}

	void PharmosTransactionDM::doInit( const InitParamsDM& initParamsDM )
    {
	    METHODNAME_DEF( PharmosTransactionDM, doInit );
	    BLOG_TRACE_METHOD( getLogger(), fun );
        
        m_InitParamsDM = initParamsDM;
    }

    void PharmosTransactionDM::doShutdown()
    {
	    METHODNAME_DEF( PharmosTransactionDM, doShutdown );
	    BLOG_TRACE_METHOD( getLogger(), fun );
        
        clearPropertyTable();
    }

	//-------------------------------------------------------------------------------------------------------------------//
	core::TransactionRecordBasePtr PharmosTransactionDM::createTransactionRecord(basar::db::aspect::AccessorPropertyTable_YIterator yit, AccessorInstanceRefWrapper& acc)
	{
		METHODNAME_DEF( PharmosTransactionDM, createTransactionRecord );
		BLOG_TRACE_METHOD( getLogger(), fun );

		return core::TransactionRecordBasePtr( new PharmosTransactionRecord( yit, acc, getCSC_Logger() ) );
	}

	//-------------------------------------------------------------------------------------------------------------------//
	const basar::VarString& PharmosTransactionDM::getFindByPatternAccessMethod() const
    {
        METHODNAME_DEF( PharmosTransactionDM, getFindByPatternAccessMethod )
	    BLOG_TRACE_METHOD( getLogger(), fun );
        
        //\todo return by reference
		return lit::acc_pharmostransaction::SELECT_OPEN_TRANSACTIONS;
    }

	//-------------------------------------------------------------------------------------------------------------------//
	basar::Int32 PharmosTransactionDM::getLastKey()
    {
        METHODNAME_DEF( PharmosTransactionDM, getLastKey )
	    BLOG_TRACE_METHOD( getLogger(), fun );

        const basar::VarString& accessMethod = lit::acc_pharmostransaction::SELECT_LAST_KEY;
        std::pair<bool, basar::Decimal> res;
	    try 
		{
            resetSearchYit();
			getSearchYit().setInt16( properties::pharmostransaction::BRANCHNO.getName(), m_InitParamsDM.m_Branchno );
			res = getAccessor().get().executeAggregate( accessMethod, getSearchYit() );	 			
        } 
		catch( basar::Exception& e )
		{
            ::util::ExceptionHandler::processAccessorException( e, getLogger(), fun, accessMethod, __FILE__, __LINE__ );
	    }
		// \TODO handling not executable
		return res.second.toInt32();
    }

    basar::db::aspect::AccessorPropertyTable_YIterator PharmosTransactionDM::prepareFindOpenSearchCriteria( const domMod::pharmosTransaction::core::OffSetNo )
    {
        METHODNAME_DEF( PharmosTransactionDM, prepareFindOpenSearchCriteria )
	    BLOG_TRACE_METHOD( getLogger(), fun );
        
        resetSearchYit();
    	basar::db::aspect::AccessorPropertyTable_YIterator yitSearch = getSearchYit();
        yitSearch.setString( properties::pharmostransaction::PROCESSINGSTATUS, domMod::pharmosTransaction::core::PharmosTransactionRecord::ProcessingStatus::OPEN );
		yitSearch.setInt16 ( properties::pharmostransaction::BRANCHNO, m_InitParamsDM.m_Branchno );

        return yitSearch;
    }

} // namespace core
} // namespace pharmosTransaction
} // namespace domMod

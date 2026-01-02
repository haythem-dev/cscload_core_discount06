//-------------------------------------------------------------------------------------------------------------------//
/*! \file	
 *  \brief		implementation of cics module PharmosTransaction
 *  \author		Steffen Heinlein
 *  \date		22.06.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include <icsc_logger.h>
#include <csc_logger.h>

#include "cicspharmostransactiondm.h"
#include "property_definitions.h"
#include "dkbvzacc_definitions.h"
#include "accessorinstancerefwrapper.h"
#include "cicspharmostransactionrecord.h"

namespace domMod 
{		
namespace pharmosTransaction
{
namespace preparation
{
//-------------------------------------------------------------------------------------------------------------------//
CICSPharmosTransactionDM::CICSPharmosTransactionDM(const basar::db::aspect::ConnectionRef tcaconnection, libcsc_utils::ICSC_LoggerPtr csc_logger)
: TransactionDMBase( tcaconnection, lit::acc_dkbvz::ACC_DKBVZ, csc_logger )
{
	METHODNAME_DEF( CICSPharmosTransactionDM, CICSPharmosTransactionDM );
	BLOG_TRACE_METHOD( getCSC_Logger()->getLogger(), fun );

}

//-------------------------------------------------------------------------------------------------------------------//
CICSPharmosTransactionDM::~CICSPharmosTransactionDM()
{		
	METHODNAME_DEF( CICSPharmosTransactionDM, ~CICSPharmosTransactionDM );
	BLOG_TRACE_METHOD( getCSC_Logger()->getLogger(), fun );
}

void CICSPharmosTransactionDM::doInit( const InitParamsDM& initParamsDM )
{
	METHODNAME_DEF( CICSPharmosTransactionDM, doInit );
	BLOG_TRACE_METHOD( getCSC_Logger()->getLogger(), fun );

    m_InitParamsDM = initParamsDM;
}

void CICSPharmosTransactionDM::doShutdown()
{
	METHODNAME_DEF( CICSPharmosTransactionDM, doShutdown );
	BLOG_TRACE_METHOD( getCSC_Logger()->getLogger(), fun );
	
	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSPharmosTransactionDM::finishQuery()
{
	METHODNAME_DEF( CICSPharmosTransactionDM, finishQuery );
	BLOG_TRACE_METHOD( getCSC_Logger()->getLogger(), fun );

	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSPharmosTransactionDM::evaluatePreconditionFindByPattern()
{
    METHODNAME_DEF( CICSPharmosTransactionDM, evaluatePreconditionFindByPattern )
	BLOG_TRACE_METHOD( getCSC_Logger()->getLogger(), fun );

	finishQuery();
}

//-------------------------------------------------------------------------------------------------------------------//
core::TransactionRecordBasePtr CICSPharmosTransactionDM::createTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yit, 
                                                                                  AccessorInstanceRefWrapper& acc )
{
	METHODNAME_DEF( CICSPharmosTransactionDM, createTransactionRecord );
	BLOG_TRACE_METHOD( getCSC_Logger()->getLogger(), fun );

	return core::TransactionRecordBasePtr( new CICSPharmosTransactionRecord( yit, acc, getCSC_Logger() ) );
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString& CICSPharmosTransactionDM::getFindByPatternAccessMethod() const
{
	METHODNAME_DEF( CICSPharmosTransactionDM, getFindByPatternAccessMethod );
	BLOG_TRACE_METHOD( getLogger(), fun );

	return lit::acc_dkbvz::SELECT_DKBVZ_BY_PATTERN;
}

basar::db::aspect::AccessorPropertyTable_YIterator CICSPharmosTransactionDM::prepareFindOpenSearchCriteria( const domMod::pharmosTransaction::core::OffSetNo offSetNo  )
{
    METHODNAME_DEF( CICSPharmosTransactionDM, prepareFindOpenSearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );

    resetSearchYit();
    basar::db::aspect::AccessorPropertyTable_YIterator yitSearch = getSearchYit();
    yitSearch.setString( properties::dkbvz::CSCPROCESSINGSTATUS, domMod::pharmosTransaction::preparation::CICSPharmosTransactionRecord::ProcessingStatus::OPEN );
	yitSearch.setInt32( properties::dkbvz::RECORDOFFSET, offSetNo  );

    return yitSearch;
}

} // namespace preparation
} // namespace pharmosTransaction
} // namespace domMod

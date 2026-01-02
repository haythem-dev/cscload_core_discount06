//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module (cics file VSAM.DKBAZK)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include "cmndm.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include "cicsbatchorderheaddm.h"
#include "property_definitions.h"
#include "dkbazkacc_definitions.h"

namespace domMod 
{		
namespace batchOrder
{
namespace preparation
{
//-------------------------------------------------------------------------------------------------------------------//
CICSBatchOrderHeadDM::CICSBatchOrderHeadDM(const basar::db::aspect::ConnectionRef tcaconnection, libcsc_utils::ICSC_LoggerPtr csc_logger)
: SearchDMBase( tcaconnection, lit::acc_dkbazk::ACC_DKBAZK, csc_logger )
{
	METHODNAME_DEF( CICSBatchOrderHeadDM, CICSBatchOrderHeadDM );
	BLOG_TRACE_METHOD( getLogger(), fun );

}

//-------------------------------------------------------------------------------------------------------------------//
CICSBatchOrderHeadDM::~CICSBatchOrderHeadDM()
{		
	METHODNAME_DEF( CICSBatchOrderHeadDM, ~CICSBatchOrderHeadDM );
	BLOG_TRACE_METHOD( getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderHeadDM::doInit( const InitParamsDMPtr initParamsDM )
{
	METHODNAME_DEF( CICSBatchOrderHeadDM, doInit );
	BLOG_TRACE_METHOD( getLogger(), fun );

    m_InitParamsDMPtr = initParamsDM;
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderHeadDM::doShutdown()
{
	METHODNAME_DEF( CICSBatchOrderHeadDM, doShutdown );
	BLOG_TRACE_METHOD( getLogger(), fun );
	
	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderHeadDM::finishQuery()
{
	METHODNAME_DEF( CICSBatchOrderHeadDM, finishQuery );
	BLOG_TRACE_METHOD( getLogger(), fun );

	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderHeadDM::evaluatePreconditionFindByPattern()
{
    METHODNAME_DEF( CICSBatchOrderHeadDM, evaluatePreconditionFindByPattern )
	BLOG_TRACE_METHOD( getLogger(), fun );

	finishQuery();
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString& CICSBatchOrderHeadDM::getFindByPatternAccessMethod() const
{
	METHODNAME_DEF( CICSBatchOrderHeadDM, getFindByPatternAccessMethod );
	BLOG_TRACE_METHOD( getLogger(), fun );

	return lit::acc_dkbazk::SELECT_DKBAZK_BY_PATTERN;
}

//-------------------------------------------------------------------------------------------------------------------//
searchyiterator::SearchYIteratorPtr CICSBatchOrderHeadDM::getSearchYIterator()
{
    METHODNAME_DEF( CICSBatchOrderHeadDM, getSearchYIterator )
	BLOG_TRACE_METHOD( getLogger(), fun );

	using namespace properties;
    if( NULL == m_SearchYIterator.get() ){
        m_SearchYIterator = domMod::searchyiterator::SearchYIteratorPtr( 
            new domMod::searchyiterator::SearchYIterator( properties::dkbazk::RECORDOFFSET.toDescriptionString(),
														  getLogger()
														)
		);
    }

    return m_SearchYIterator;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator CICSBatchOrderHeadDM::prepareFindOpenSearchCriteria( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch   )
{
    METHODNAME_DEF( CICSBatchOrderHeadDM, prepareFindOpenSearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );

	//basar::db::aspect::AccessorPropertyTable_YIterator yitInternalSearch = yitSearch;

    ///*resetSearchYit();
    
    //yitSearch.setString( properties::dkbazk::CSCPROCESSINGSTATUS, domMod::batchOrder::preparation::CICSPharmosTransactionRecord::ProcessingStatus::OPEN );
	//yitSearch.setInt32( properties::dkbazk::RECORDOFFSET, offSetNo  ); 

    return yitSearch;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator CICSBatchOrderHeadDM::prepareFindLastKeySearchCriteria( const basar::Int16 branchno )
{
    METHODNAME_DEF( CICSBatchOrderHeadDM, prepareFindLastKeySearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );

	resetSearchYit();
	getSearchYit().setInt32( properties::dkbazk::KBAZKFIL, branchno  ); 

	return getSearchYit();
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString&	CICSBatchOrderHeadDM::getSaveAccessMethod() const
{
    METHODNAME_DEF( CICSBatchOrderHeadDM, getSaveAccessMethod )
	BLOG_TRACE_METHOD( getLogger(), fun );
		
	return lit::acc_dkbazk::SAVE_DKBAZK;
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString& CICSBatchOrderHeadDM::getFindLastKeyAccessMethod() const
{
	METHODNAME_DEF( CICSBatchOrderHeadDM, getFindLastKeyAccessMethod );
	BLOG_TRACE_METHOD( getLogger(), fun );

	return lit::acc_dkbazk::ACC_DKBAZK;
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderHeadDM::clearTable()
{
    METHODNAME_DEF( CICSBatchOrderHeadDM, clearTable )
	BLOG_TRACE_METHOD( getLogger(), fun );

	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderHeadDM::setTransfered( basar::db::aspect::AccessorPropertyTable_YIterator yitCicsHead )
{
    METHODNAME_DEF( CICSBatchOrderHeadDM, setTransfered )
	BLOG_TRACE_METHOD( getLogger(), fun );

	yitCicsHead.setString( properties::dkbazk::KBAZKSTATUS, lit::acc_dkbazk::KBAZK_STATUS_TRANSFERED );
}

} // namespace preparation
} // namespace batchOrder
} // namespace domMod

//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module of cicsorderheads (cics file VSAM.DKBAZP)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include "cmndm.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include "cicsbatchorderposdm.h"
#include "property_definitions.h"
#include "dkbazpacc_definitions.h"

namespace domMod 
{		
namespace batchOrder
{
namespace preparation
{
//-------------------------------------------------------------------------------------------------------------------//
CICSBatchOrderPosDM::CICSBatchOrderPosDM(const basar::db::aspect::ConnectionRef tcaconnection, 
										 libcsc_utils::ICSC_LoggerPtr csc_logger )
: SearchDMBase( tcaconnection, 
  lit::acc_dkbazp::ACC_DKBAZP, csc_logger )
{
	METHODNAME_DEF( CICSBatchOrderPosDM, CICSBatchOrderPosDM );
	BLOG_TRACE_METHOD( getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
CICSBatchOrderPosDM::~CICSBatchOrderPosDM()
{		
	METHODNAME_DEF( CICSBatchOrderPosDM, ~CICSBatchOrderPosDM );
	BLOG_TRACE_METHOD( getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderPosDM::doInit( const InitParamsDMPtr initParamsDM )
{
	METHODNAME_DEF( CICSBatchOrderPosDM, doInit );
	BLOG_TRACE_METHOD( getLogger(), fun );

    m_InitParamsDMPtr = initParamsDM;
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderPosDM::doShutdown()
{
	METHODNAME_DEF( CICSBatchOrderPosDM, doShutdown );
	BLOG_TRACE_METHOD( getLogger(), fun );
	
	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderPosDM::finishQuery()
{
	METHODNAME_DEF( CICSBatchOrderPosDM, finishQuery );
	BLOG_TRACE_METHOD( getLogger(), fun );

	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderPosDM::evaluatePreconditionFindByPattern()
{
    METHODNAME_DEF( CICSBatchOrderPosDM, evaluatePreconditionFindByPattern )
	BLOG_TRACE_METHOD( getLogger(), fun );

	finishQuery();
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString& CICSBatchOrderPosDM::getFindByPatternAccessMethod() const
{
	METHODNAME_DEF( CICSBatchOrderPosDM, getFindByPatternAccessMethod );
	BLOG_TRACE_METHOD( getLogger(), fun );

	return lit::acc_dkbazp::SELECT_DKBAZP_BY_PATTERN;
}

//-------------------------------------------------------------------------------------------------------------------//
searchyiterator::SearchYIteratorPtr CICSBatchOrderPosDM::getSearchYIterator()
{
    METHODNAME_DEF( SearchDMBase, getSearchYIterator )
	BLOG_TRACE_METHOD( getLogger(), fun );

    using namespace properties;
    if( NULL == m_SearchYIterator.get() ){
        m_SearchYIterator = domMod::searchyiterator::SearchYIteratorPtr( 
            new domMod::searchyiterator::SearchYIterator( properties::dkbazp::RECORDOFFSET.toDescriptionString() +
														  properties::dkbazp::KBAZPLFDANR.toDescriptionString(),
														  getLogger()
														)
		);
    }

    return m_SearchYIterator;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator CICSBatchOrderPosDM::prepareFindOpenSearchCriteria( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch   )
{
    METHODNAME_DEF( CICSBatchOrderPosDM, prepareFindOpenSearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );

	//basar::db::aspect::AccessorPropertyTable_YIterator yitInternalSearch = yitSearch;

    ///*resetSearchYit();
    
    //yitSearch.setString( properties::dkbazk::CSCPROCESSINGSTATUS, domMod::batchOrder::preparation::CICSPharmosTransactionRecord::ProcessingStatus::OPEN );
	//yitSearch.setInt32( properties::dkbazk::RECORDOFFSET, offSetNo  ); 

    return yitSearch;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator CICSBatchOrderPosDM::prepareFindLastKeySearchCriteria( const basar::Int16 branchno )
{
    METHODNAME_DEF( CICSBatchOrderPosDM, prepareFindLastKeySearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );

	resetSearchYit();
	getSearchYit().setInt32( properties::dkbazp::KBAZPFIL, branchno  ); 

	return getSearchYit();
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString&	CICSBatchOrderPosDM::getSaveAccessMethod() const
{
    METHODNAME_DEF( CICSBatchOrderPosDM, getSaveAccessMethod )
	BLOG_TRACE_METHOD( getLogger(), fun );
		
	return lit::acc_dkbazp::ACC_DKBAZP;
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString& CICSBatchOrderPosDM::getFindLastKeyAccessMethod() const
{
	METHODNAME_DEF( CICSBatchOrderPosDM, getFindLastKeyAccessMethod );
	BLOG_TRACE_METHOD( getLogger(), fun );

	return lit::acc_dkbazp::ACC_DKBAZP;
}

//-------------------------------------------------------------------------------------------------------------------//
void CICSBatchOrderPosDM::clearTable()
{
    METHODNAME_DEF( CICSBatchOrderPosDM, clearTable )
	BLOG_TRACE_METHOD( getLogger(), fun );

	clearPropertyTable();
}

} // namespace preparation
} // namespace batchOrder
} // namespace domMod

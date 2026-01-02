//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module of ifxorderheads (table pharmosbatchorderheads)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include "cmndm.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include "batchorderposdm.h"
#include "property_definitions.h"
#include "pharmosbatchorderposacc_definitions.h"
#include "batchorderdm_definitions.h"

namespace domMod 
{		
namespace batchOrder
{
namespace processing
{
//-------------------------------------------------------------------------------------------------------------------//
BatchOrderPosDM::BatchOrderPosDM(const basar::db::aspect::ConnectionRef tcaconnection, 
										 libcsc_utils::ICSC_LoggerPtr csc_logger )
: SearchDMBase( tcaconnection, 
  lit::acc_pharmosbatchorderpos::ACC_PHARMOSBATCHORDERPOS, csc_logger )
{
	METHODNAME_DEF( BatchOrderPosDM, BatchOrderPosDM );
	BLOG_TRACE_METHOD( getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
BatchOrderPosDM::~BatchOrderPosDM()
{		
	METHODNAME_DEF( BatchOrderPosDM, ~BatchOrderPosDM );
	BLOG_TRACE_METHOD( getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderPosDM::doInit( const InitParamsDMPtr initParamsDM )
{
	METHODNAME_DEF( BatchOrderPosDM, doInit );
	BLOG_TRACE_METHOD( getLogger(), fun );

    m_InitParamsDMPtr = initParamsDM;
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderPosDM::doShutdown()
{
	METHODNAME_DEF( BatchOrderPosDM, doShutdown );
	BLOG_TRACE_METHOD( getLogger(), fun );
	
	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderPosDM::finishQuery()
{
	METHODNAME_DEF( BatchOrderPosDM, finishQuery );
	BLOG_TRACE_METHOD( getLogger(), fun );

	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderPosDM::evaluatePreconditionFindByPattern()
{
    METHODNAME_DEF( BatchOrderPosDM, evaluatePreconditionFindByPattern )
	BLOG_TRACE_METHOD( getLogger(), fun );

	finishQuery();
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString& BatchOrderPosDM::getFindByPatternAccessMethod() const
{
	METHODNAME_DEF( BatchOrderPosDM, getFindByPatternAccessMethod );
	BLOG_TRACE_METHOD( getLogger(), fun );

	return lit::acc_pharmosbatchorderpos::SELECT_PHARMOSBATCHORDERPOS_BY_PATTERN;
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString& BatchOrderPosDM::getFindLastKeyAccessMethod() const
{
	METHODNAME_DEF( BatchOrderPosDM, getFindLastKeyAccessMethod );
	BLOG_TRACE_METHOD( getLogger(), fun );

	return lit::acc_pharmosbatchorderpos::SELECT_LAST_KEY;
}

//-------------------------------------------------------------------------------------------------------------------//
searchyiterator::SearchYIteratorPtr BatchOrderPosDM::getSearchYIterator()
{
    METHODNAME_DEF( SearchDMBase, getSearchYIterator )
	BLOG_TRACE_METHOD( getLogger(), fun );

    using namespace properties;
    if( NULL == m_SearchYIterator.get() ){
        m_SearchYIterator = domMod::searchyiterator::SearchYIteratorPtr( 
            new domMod::searchyiterator::SearchYIterator( properties::pharmosbatchorderpos::BATCHORDERNO.toDescriptionString() +
														  properties::pharmosbatchorderpos::VSEOFFSET.toDescriptionString() + 
														  properties::pharmosbatchorderpos::BRANCHNO.toDescriptionString() +
														  properties::pharmosbatchorderpos::PROCESSINGSTATE.toDescriptionString(),
														  getLogger()
														)
		);
    }

    return m_SearchYIterator;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator BatchOrderPosDM::prepareFindOpenSearchCriteria( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch   )
{
    METHODNAME_DEF( BatchOrderPosDM, prepareFindOpenSearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );

	//basar::db::aspect::AccessorPropertyTable_YIterator yitInternalSearch = yitSearch;

    ///*resetSearchYit();
    
    //yitSearch.setString( properties::dkbazk::CSCPROCESSINGSTATUS, domMod::batchOrder::preparation::CICSPharmosTransactionRecord::ProcessingStatus::OPEN );
	//yitSearch.setInt32( properties::dkbazk::RECORDOFFSET, offSetNo  ); 

    return yitSearch;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator BatchOrderPosDM::prepareFindLastKeySearchCriteria( const basar::Int16 branchno )
{
    METHODNAME_DEF( BatchOrderPosDM, prepareFindLastKeySearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );

	resetSearchYit();
	getSearchYit().setInt16( properties::pharmosbatchorderpos::BRANCHNO, branchno  ); 

	return getSearchYit();
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString&	BatchOrderPosDM::getSaveAccessMethod() const
{
    METHODNAME_DEF( BatchOrderPosDM, getSaveAccessMethod )
	BLOG_TRACE_METHOD( getLogger(), fun );
		
	return lit::acc_pharmosbatchorderpos::SAVE_PHARMOSBATCHORDERPOS;
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderPosDM::setInProcess( basar::db::aspect::AccessorPropertyTable_YIterator yitPos )
{
    METHODNAME_DEF( BatchOrderPosDM, setInProcess )
	BLOG_TRACE_METHOD( getLogger(), fun );

	yitPos.setString( properties::pharmosbatchorderpos::PROCESSINGSTATE, domMod::batchOrder::processing::batchOrderDM::STATUS_IN_PROCESS );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderPosDM::setClosed( basar::db::aspect::AccessorPropertyTable_YIterator yitPos )
{
    METHODNAME_DEF( BatchOrderPosDM, setClosed )
	BLOG_TRACE_METHOD( getLogger(), fun );

	yitPos.setString( properties::pharmosbatchorderpos::PROCESSINGSTATE, domMod::batchOrder::processing::batchOrderDM::STATUS_CLOSED );
	yitPos.setDateTime( properties::pharmosbatchorderpos::PROCESSEDTIMESTAMP, basar::DateTime() );
}

} // namespace processing
} // namespace batchOrder
} // namespace domMod

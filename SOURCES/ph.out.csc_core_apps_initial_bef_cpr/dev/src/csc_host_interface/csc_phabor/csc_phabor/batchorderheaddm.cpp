//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module of ifxorderitems (table pharmosbatchorderpos)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//


#include "cmndm.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include "batchorderheaddm.h"
#include "property_definitions.h"
#include "pharmosbatchorderheadacc_definitions.h"
#include "batchorderdm_definitions.h"

namespace domMod 
{		
namespace batchOrder
{
namespace processing
{
//-------------------------------------------------------------------------------------------------------------------//
BatchOrderHeadDM::BatchOrderHeadDM(const basar::db::aspect::ConnectionRef tcaconnection, libcsc_utils::ICSC_LoggerPtr csc_logger)
: SearchDMBase( tcaconnection, lit::acc_pharmosbatchorderhead::ACC_PHARMOSBATCHORDERHEAD, csc_logger )
{
	METHODNAME_DEF( BatchOrderHeadDM, BatchOrderHeadDM );
	BLOG_TRACE_METHOD( getLogger(), fun );

}

//-------------------------------------------------------------------------------------------------------------------//
BatchOrderHeadDM::~BatchOrderHeadDM()
{		
	METHODNAME_DEF( BatchOrderHeadDM, ~BatchOrderHeadDM );
	BLOG_TRACE_METHOD( getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderHeadDM::doInit( const InitParamsDMPtr initParamsDM )
{
	METHODNAME_DEF( BatchOrderHeadDM, doInit );
	BLOG_TRACE_METHOD( getLogger(), fun );

    m_InitParamsDMPtr = initParamsDM;
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderHeadDM::doShutdown()
{
	METHODNAME_DEF( BatchOrderHeadDM, doShutdown );
	BLOG_TRACE_METHOD( getLogger(), fun );
	
	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderHeadDM::finishQuery()
{
	METHODNAME_DEF( BatchOrderHeadDM, finishQuery );
	BLOG_TRACE_METHOD( getLogger(), fun );

	clearPropertyTable();
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderHeadDM::evaluatePreconditionFindByPattern()
{
    METHODNAME_DEF( BatchOrderHeadDM, evaluatePreconditionFindByPattern )
	BLOG_TRACE_METHOD( getLogger(), fun );

	finishQuery();
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString& BatchOrderHeadDM::getFindByPatternAccessMethod() const
{
	METHODNAME_DEF( BatchOrderHeadDM, getFindByPatternAccessMethod );
	BLOG_TRACE_METHOD( getLogger(), fun );

	return lit::acc_pharmosbatchorderhead::SELECT_PHARMOSBATCHORDERHEAD_BY_PATTERN;
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString& BatchOrderHeadDM::getFindLastKeyAccessMethod() const
{
	METHODNAME_DEF( BatchOrderHeadDM, getFindLastKeyAccessMethod );
	BLOG_TRACE_METHOD( getLogger(), fun );

	return lit::acc_pharmosbatchorderhead::SELECT_LAST_KEY;
}

//-------------------------------------------------------------------------------------------------------------------//
searchyiterator::SearchYIteratorPtr BatchOrderHeadDM::getSearchYIterator()
{
    METHODNAME_DEF( BatchOrderHeadDM, getSearchYIterator )
	BLOG_TRACE_METHOD( getLogger(), fun );

	using namespace properties;
    if( NULL == m_SearchYIterator.get() ){
        m_SearchYIterator = domMod::searchyiterator::SearchYIteratorPtr( 
            new domMod::searchyiterator::SearchYIterator( properties::pharmosbatchorderhead::VSEOFFSET.toDescriptionString() +
														  properties::pharmosbatchorderhead::BRANCHNO.toDescriptionString() +
														  properties::pharmosbatchorderhead::PROCESSINGSTATUS.toDescriptionString(),
														  getLogger()
														)
		);
    }

    return m_SearchYIterator;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator BatchOrderHeadDM::prepareFindOpenSearchCriteria( basar::db::aspect::AccessorPropertyTable_YIterator yitSearch   )
{
    METHODNAME_DEF( BatchOrderHeadDM, prepareFindOpenSearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );

	basar::db::aspect::AccessorPropertyTable_YIterator yitInternalSearch = yitSearch;
	yitSearch.setString( properties::pharmosbatchorderhead::PROCESSINGSTATUS, domMod::batchOrder::processing::batchOrderDM::STATUS_OPEN );

    return yitSearch;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator BatchOrderHeadDM::prepareFindLastKeySearchCriteria( const basar::Int16 branchno )
{
    METHODNAME_DEF( BatchOrderHeadDM, prepareFindLastKeySearchCriteria )
	BLOG_TRACE_METHOD( getLogger(), fun );

	resetSearchYit();
	getSearchYit().setInt16( properties::pharmosbatchorderhead::BRANCHNO, branchno  ); 

	return getSearchYit();
}

//-------------------------------------------------------------------------------------------------------------------//
const basar::VarString&	BatchOrderHeadDM::getSaveAccessMethod() const
{
    METHODNAME_DEF( BatchOrderHeadDM, getSaveAccessMethod )
	BLOG_TRACE_METHOD( getLogger(), fun );
		
    return lit::acc_pharmosbatchorderhead::SAVE_PHARMOSBATCHORDERHEAD;
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderHeadDM::setInProcess( basar::db::aspect::AccessorPropertyTable_YIterator yitHead )
{
    METHODNAME_DEF( BatchOrderHeadDM, setInProcess )
	BLOG_TRACE_METHOD( getLogger(), fun );

	yitHead.setString( properties::pharmosbatchorderhead::PROCESSINGSTATUS, domMod::batchOrder::processing::batchOrderDM::STATUS_IN_PROCESS );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderHeadDM::setClosed( basar::db::aspect::AccessorPropertyTable_YIterator yitHead )
{
    METHODNAME_DEF( BatchOrderHeadDM, setClosed )
	BLOG_TRACE_METHOD( getLogger(), fun );

	yitHead.setString( properties::pharmosbatchorderhead::PROCESSINGSTATUS, domMod::batchOrder::processing::batchOrderDM::STATUS_CLOSED );
	yitHead.setDateTime( properties::pharmosbatchorderhead::PROCESSEDTIMESTAMP, basar::DateTime() );
}

} // namespace processing
} // namespace batchOrder
} // namespace domMod

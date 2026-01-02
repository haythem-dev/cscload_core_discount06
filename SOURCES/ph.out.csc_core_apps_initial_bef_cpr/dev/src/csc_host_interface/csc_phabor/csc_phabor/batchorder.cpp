//-------------------------------------------------------------------------------------------------------------------//
/*! \file		batchorder.cpp
 *  \brief		container for holding batchorder head with it's positions
 *  \author		Julian Machata
 *  \date		25.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include <libbasarproperty.h>
#include <icsc_logger.h>
#include <csc_logger.h>
#include <classinfo_macros.h>
#include <iomanip>

#include "batchorder.h"

namespace domMod 
{		
namespace batchOrder
{
namespace core
{

//-------------------------------------------------------------------------------------------------------------------//
BatchOrder::BatchOrder(  basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead,  
						 basar::db::aspect::AccessorPropertyTableRef orderPositionsPropTab, 
						 libcsc_utils::ICSC_LoggerPtr csc_logger )
: m_CSC_Logger(csc_logger), 
  m_OrderHead(yitOrderHead),
  m_OrderPositions(orderPositionsPropTab)
{
	METHODNAME_DEF( BatchOrder, BatchOrder );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
BatchOrder::~BatchOrder()
{		
	METHODNAME_DEF( BatchOrder, ~BatchOrder );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator BatchOrder::getOrderHead()
{
	METHODNAME_DEF( BatchOrder, getOrderHead );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_OrderHead;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTableRef	BatchOrder::getOrderPositions()
{
	METHODNAME_DEF( BatchOrder, getOrderPositions );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return m_OrderPositions;
}

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString BatchOrder::getLogMessage() const
{
	METHODNAME_DEF( BatchOrder, getLogMessage );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	std::stringstream ss; ss << ": ";                                                        
	if( m_OrderHead.isNull() ){                                                                             
		ss << "YIterator is Null()!";                                                               
	} else if( m_OrderHead.isEnd() ){                                                                       
		ss << "YIterator is empty()!";                                                              
	} else {                                                                                        
		ss << std::endl;                                                                              
		basar::db::aspect::AccessorPropertyTableRef propTab = m_OrderHead.getPropertyTable();               
		basar::db::aspect::PropertyDescriptionListRef descriptList =                                
			propTab.getPropertyDescriptionList();                                                   
		basar::db::aspect::AccessorPropertyTable_XIterator xit = m_OrderHead.begin();                       
		basar::I18nString value = "";                                                               
		for( int i = 1; !xit.isEnd(); ++xit, ++i ){                                                 
			value = "";                                                                             
			if( basar::SS_UNSET != xit.getState().getState() ){                                     
				value = xit.getSQLString();                                                         
			}                                                                                       
			ss << std::left << std::setw(2) << i << ". " << xit.getName() << "(>" << value << "<, " 
				<< xit.getState().toString() << ")" << std::endl;                                     
		}                                                                                           
	}
	
	return ss.str().c_str();
}

} // namespace core
} // namespace batchOrder
} // namespace domMod

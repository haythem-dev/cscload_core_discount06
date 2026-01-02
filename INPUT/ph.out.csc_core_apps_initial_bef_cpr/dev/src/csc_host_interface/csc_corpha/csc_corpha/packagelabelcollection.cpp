//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		18.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include "packagelabelcollection.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	
	//----------------------------------------------------------------------------//
	PackageLabelCollection::PackageLabelCollection()
		: m_CurrentID( 1 )
	{
		//METHODNAME_DEF( PackageLabelCollection, PackageLabelCollection );
		//BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );  // no logger available at this moment

		m_PackageLabelVector.clear();		
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	PackageLabelCollection::~PackageLabelCollection()
	{
		//METHODNAME_DEF( PackageLabelCollection, ~PackageLabelCollection );
		//BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void PackageLabelCollection::injectLogger( libcsc_utils::ICSC_LoggerPtr logger )
	{
		//METHODNAME_DEF( PackageLabelCollection, injectLogger );
		//BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Logger = logger;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	bool PackageLabelCollection::hasItems() const
	{
		METHODNAME_DEF( PackageLabelCollection, hasItems );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		if( m_PackageLabelVector.size() > 0 )
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const PackageLabelCollection::sPackageLabelItem& PackageLabelCollection::getFirst()
	{
		METHODNAME_DEF( PackageLabelCollection, getFirst );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Iterator = m_PackageLabelVector.begin();				
		m_CurrentLabel = (*m_Iterator);
		++m_Iterator;
		return m_CurrentLabel;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const PackageLabelCollection::sPackageLabelItem& PackageLabelCollection::getNext()
	{
		METHODNAME_DEF( PackageLabelCollection, getNext );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		
		m_CurrentLabel = (*m_Iterator);		
		++m_Iterator;
		return m_CurrentLabel;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	bool PackageLabelCollection::isEnd()
	{
		METHODNAME_DEF( PackageLabelCollection, isEnd );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );		
		if( m_PackageLabelVector.end() == m_Iterator )
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	basar::Int32 PackageLabelCollection::addPackageLabel( const basar::VarString& label )
	{
		METHODNAME_DEF( PackageLabelCollection, addPackageLabel );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		basar::Int32 retval = 0;		

		bool LabelFound = false;				

		std::vector<PackageLabelCollection::sPackageLabelItem>::const_iterator it;
		for( it = m_PackageLabelVector.begin(); it != m_PackageLabelVector.end(); ++it )
		{
			if( label == (*it).PackageLabel )
			{
				retval = (*it).PackageLabelID;
				LabelFound = true;
				break;
			}
		}		

		if( !LabelFound )
		{			
			PackageLabelCollection::sPackageLabelItem item;
			item.PackageLabel = label;
			item.PackageLabelID = m_CurrentID;
			m_PackageLabelVector.push_back( item );
			retval = m_CurrentID;
			++m_CurrentID;

			basar::VarString msg;
			msg.format("added PackageLabel to PackageLabelVector: %s (%d)", label.c_str(), retval );
            m_Logger->log(log4cplus::INFO_LOG_LEVEL, msg);
		}

		return retval;
	}
	//----------------------------------------------------------------------------//
}
}
}

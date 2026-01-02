//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Julian Machata
 *  \date		26.10.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_SEARCHDMBASEPTR_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_SEARCHDMBASEPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
	namespace batchOrder
	{
		namespace core
		{
			class SearchDMBase;
			typedef boost::shared_ptr<SearchDMBase> SearchDMBasePtr;    
		}
	}
}

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_SEARCHDMBASEPTR_H

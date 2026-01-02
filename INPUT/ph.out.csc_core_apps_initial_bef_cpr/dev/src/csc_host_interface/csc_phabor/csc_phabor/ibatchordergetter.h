//-------------------------------------------------------------------------------------------------//
/*! \file IBatchOrderGetter.h
 *  \brief 
 *  \author Julian Machata
 *  \date 29.06.2012
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_UTIL_IBATCHORDER_GETTER_H
#define GUARD_UTIL_IBATCHORDER_GETTER_H

#include <libbasardbaspect_accessorpropertytable.h>

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTableRef;
        }
    }
}

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace util
{
	class IBatchOrderGetter
    {
        public:	
            virtual ~IBatchOrderGetter(){};
			virtual basar::db::aspect::AccessorPropertyTable_YIterator getFirstOrderHead() = 0;
			virtual basar::db::aspect::AccessorPropertyTable_YIterator getNextOrderHead() = 0;

			virtual basar::db::aspect::AccessorPropertyTableRef getBatchOrderPositions( basar::db::aspect::AccessorPropertyTable_YIterator yitBatchOrderHead ) = 0;
    };

}
}
} // end namespace util

//----------------------------------------------------------------------------
#endif //GUARD_UTIL_IBATCHORDER_GETTER_H

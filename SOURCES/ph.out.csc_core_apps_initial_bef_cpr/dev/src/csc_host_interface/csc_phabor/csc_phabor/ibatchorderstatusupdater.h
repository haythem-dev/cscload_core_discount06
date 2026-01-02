//-------------------------------------------------------------------------------------------------//
/*! \file ICSCOrderObjectGetter.h
 *  \brief 
 *  \author Julian Machata
 *  \date 29.06.2012
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_UTIL_IBATCHORDERSTATUSUPDATER_H
#define GUARD_UTIL_IBATCHORDERSTATUSUPDATER_H


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace util
{
	class IBatchOrderStatusUpdater
    {
        public:	
            virtual ~IBatchOrderStatusUpdater(){};

			virtual void	setBatchOrderInProcess		( basar::db::aspect::AccessorPropertyTable_YIterator head ) = 0;
			virtual void	setBatchOrderClosed			( basar::db::aspect::AccessorPropertyTable_YIterator head ) = 0;
			virtual void	setBatchOrderPosInProcess	( basar::db::aspect::AccessorPropertyTable_YIterator pos  ) = 0;
			virtual void	setBatchOrderPosClosed		( basar::db::aspect::AccessorPropertyTable_YIterator pos  ) = 0;

    };

}
}
} // end namespace util

//----------------------------------------------------------------------------
#endif //GUARD_UTIL_IBATCHORDERSTATUSUPDATER_H

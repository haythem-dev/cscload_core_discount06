//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitGroup
 *  \author Steffen Heinlein
 *  \date   20.01.2015
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITGROUP_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITGROUP_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecreditlimitbase.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

class RecordTypeCreditLimitGroup : public processing::RecordTypeCreditLimitBase
{
    public:	
        RecordTypeCreditLimitGroup();
        ~RecordTypeCreditLimitGroup();             
		
		virtual void					doProcess( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeCreditLimitGroup( const RecordTypeCreditLimitGroup& );
		RecordTypeCreditLimitGroup& operator= ( const RecordTypeCreditLimitGroup& );		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITGROUP_H


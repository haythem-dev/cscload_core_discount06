//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitChain
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITCHAIN_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITCHAIN_H

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

class RecordTypeCreditLimitChain : public processing::RecordTypeCreditLimitBase
{
    public:	
        RecordTypeCreditLimitChain();
        ~RecordTypeCreditLimitChain();             
		
		virtual void					doProcess( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeCreditLimitChain( const RecordTypeCreditLimitChain& );
		RecordTypeCreditLimitChain& operator= ( const RecordTypeCreditLimitChain& );		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITCHAIN_H


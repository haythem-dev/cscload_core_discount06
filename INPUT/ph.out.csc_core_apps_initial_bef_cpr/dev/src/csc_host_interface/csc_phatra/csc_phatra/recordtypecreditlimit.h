//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimit
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMIT_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMIT_H

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

class RecordTypeCreditLimit : public RecordTypeCreditLimitBase
{
    public:	
        RecordTypeCreditLimit();
        ~RecordTypeCreditLimit();             
		
		virtual void					doProcess( const core::TransactionRecordBasePtr record ) const;		
			
    private:

		bool							processNonChain( const core::TransactionRecordBasePtr record ) const;		
		bool							processChain( const core::TransactionRecordBasePtr record ) const;		

        RecordTypeCreditLimit( const RecordTypeCreditLimit& );
		RecordTypeCreditLimit& operator= ( const RecordTypeCreditLimit& );		
};

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMIT_H


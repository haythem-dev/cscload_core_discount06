//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeNoProcessing
 *  \author Steffen Heinlein
 *  \date   21.01.2014
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPENOPROCESSING_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPENOPROCESSING_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypebase.h"

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
	  
class RecordTypeNoProcessing : public core::RecordTypeBase
{
    public:	
        RecordTypeNoProcessing();
        ~RecordTypeNoProcessing();             
		
		void					process( const core::TransactionRecordBasePtr record ) const;				
	
    private:
        RecordTypeNoProcessing( const RecordTypeNoProcessing& );
		RecordTypeNoProcessing& operator= ( const RecordTypeNoProcessing& );

		void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPENOPROCESSING_H


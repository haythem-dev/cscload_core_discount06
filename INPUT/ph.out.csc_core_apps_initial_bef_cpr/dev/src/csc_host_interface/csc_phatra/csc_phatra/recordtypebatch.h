//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeBatch
 *  \author Steffen Heinlein
 *  \date   04.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEBATCHH
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEBATCHH

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

class RecordTypeBatch : public core::RecordTypeBase
{
    public:	
        RecordTypeBatch();
        ~RecordTypeBatch();             
		
		virtual void					process( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeBatch( const RecordTypeBatch& );
		RecordTypeBatch& operator= ( const RecordTypeBatch& );		

		virtual void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEBATCHH


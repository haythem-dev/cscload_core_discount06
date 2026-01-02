//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeChangeIBTStockLevel
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECHANGEIBTSTOCKLEVEL_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECHANGEIBTSTOCKLEVEL_H

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

class RecordTypeChangeIBTStockLevel : public core::RecordTypeBase
{
    public:	
        RecordTypeChangeIBTStockLevel();
        ~RecordTypeChangeIBTStockLevel();             
		
		virtual void					process( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeChangeIBTStockLevel( const RecordTypeChangeIBTStockLevel& );
		RecordTypeChangeIBTStockLevel& operator= ( const RecordTypeChangeIBTStockLevel& );

		virtual void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;

		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECHANGEIBTSTOCKLEVEL_H


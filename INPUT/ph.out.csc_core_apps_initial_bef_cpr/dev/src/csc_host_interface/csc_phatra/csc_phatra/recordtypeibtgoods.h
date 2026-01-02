//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeExpiryDate
 *  \author Steffen Heinlein
 *  \date   06.03.2013
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEIBTGOODS_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEIBTGOODS_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil.h> 
#include "recordtypebase.h"
#include "recordtypefactory.h"

#include "recordprocesshelperptr.h"
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

class RecordTypeIBTGoods : public core::RecordTypeBase
{
    public:	
        RecordTypeIBTGoods();
        ~RecordTypeIBTGoods();             
		
		virtual void					process( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeIBTGoods( const RecordTypeIBTGoods& );
		RecordTypeIBTGoods& operator= ( const RecordTypeIBTGoods& );

		virtual void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;
		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEEXPIRYDATE_H


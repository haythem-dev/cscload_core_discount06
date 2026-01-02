//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeExpiryDate
 *  \author Steffen Heinlein
 *  \date   06.03.2013
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEEXPIRYDATE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEEXPIRYDATE_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil.h> 
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

class RecordTypeExpiryDate : public core::RecordTypeBase
{
    public:	
        RecordTypeExpiryDate();
        ~RecordTypeExpiryDate();             
		
		virtual void					process( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeExpiryDate( const RecordTypeExpiryDate& );
		RecordTypeExpiryDate& operator= ( const RecordTypeExpiryDate& );

		virtual void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;
		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEEXPIRYDATE_H


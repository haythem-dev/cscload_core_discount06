//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeChangeArticleDetails
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECHANGEARTICLEDETAILS_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECHANGEARTICLEDETAILS_H

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

class RecordTypeChangeArticleDetails : public core::RecordTypeBase
{
    public:	
        RecordTypeChangeArticleDetails();
        ~RecordTypeChangeArticleDetails();             
		
		virtual void					process( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeChangeArticleDetails( const RecordTypeChangeArticleDetails& );
		RecordTypeChangeArticleDetails& operator= ( const RecordTypeChangeArticleDetails& );

		virtual void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;

		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECHANGEARTICLEDETAILS_H


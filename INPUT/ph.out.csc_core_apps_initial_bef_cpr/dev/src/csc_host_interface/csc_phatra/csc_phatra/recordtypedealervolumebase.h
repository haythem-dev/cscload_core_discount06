//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeDealerVolumeBase
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEBASE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEBASE_H

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
	  
class RecordTypeDealerVolumeBase : public core::RecordTypeBase
{
    public:	
        RecordTypeDealerVolumeBase();
        ~RecordTypeDealerVolumeBase();             
		
		void					process( const core::TransactionRecordBasePtr record ) const;		
		virtual void			doProcess( const core::TransactionRecordBasePtr record ) const = 0;


    private:
        RecordTypeDealerVolumeBase( const RecordTypeDealerVolumeBase& );
		RecordTypeDealerVolumeBase& operator= ( const RecordTypeDealerVolumeBase& );

		void							doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEBASE_H


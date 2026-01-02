//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeDealerVolumeExclusiveTotal
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEEXCLUSIVETOTAL_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEEXCLUSIVETOTAL_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypedealervolumebase.h"

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

class RecordTypeDealerVolumeExclusiveTotal : public RecordTypeDealerVolumeBase
{
    public:	
        RecordTypeDealerVolumeExclusiveTotal();
        ~RecordTypeDealerVolumeExclusiveTotal();             
		
		virtual void			doProcess( const core::TransactionRecordBasePtr record ) const;

    private:
        RecordTypeDealerVolumeExclusiveTotal( const RecordTypeDealerVolumeExclusiveTotal& );
		RecordTypeDealerVolumeExclusiveTotal& operator= ( const RecordTypeDealerVolumeExclusiveTotal& );		
};

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEEXCLUSIVETOTAL_H


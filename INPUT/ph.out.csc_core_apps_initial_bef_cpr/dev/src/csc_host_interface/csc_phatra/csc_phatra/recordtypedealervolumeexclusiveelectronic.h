//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeDealerVolumeExclusiveElectronic
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEEXCLUSIVEELECTRONIC_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEEXCLUSIVEELECTRONIC_H

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

class RecordTypeDealerVolumeExclusiveElectronic : public RecordTypeDealerVolumeBase
{
    public:	
        RecordTypeDealerVolumeExclusiveElectronic();
        ~RecordTypeDealerVolumeExclusiveElectronic();             
		
		virtual void			doProcess( const core::TransactionRecordBasePtr record ) const;

    private:
        RecordTypeDealerVolumeExclusiveElectronic( const RecordTypeDealerVolumeExclusiveElectronic& );
		RecordTypeDealerVolumeExclusiveElectronic& operator= ( const RecordTypeDealerVolumeExclusiveElectronic& );		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEEXCLUSIVEELECTRONIC_H


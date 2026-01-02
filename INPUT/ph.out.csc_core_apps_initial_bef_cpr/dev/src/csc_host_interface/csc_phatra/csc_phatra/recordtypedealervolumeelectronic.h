//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeDealerVolumeElectronic
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEELECTRONIC_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEELECTRONIC_H

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

class RecordTypeDealerVolumeElectronic : public RecordTypeDealerVolumeBase
{
    public:	
        RecordTypeDealerVolumeElectronic();
        ~RecordTypeDealerVolumeElectronic();             
		
		virtual void			doProcess( const core::TransactionRecordBasePtr record ) const;

    private:
        RecordTypeDealerVolumeElectronic( const RecordTypeDealerVolumeElectronic& );
		RecordTypeDealerVolumeElectronic& operator= ( const RecordTypeDealerVolumeElectronic& );		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMEELECTRONIC_H


//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeDealerVolumeTotal
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMETOTAL_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMETOTAL_H

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

class RecordTypeDealerVolumeTotal : public RecordTypeDealerVolumeBase
{
    public:	
        RecordTypeDealerVolumeTotal();
        ~RecordTypeDealerVolumeTotal();             
		
		virtual void			doProcess( const core::TransactionRecordBasePtr record ) const;

    private:
        RecordTypeDealerVolumeTotal( const RecordTypeDealerVolumeTotal& );
		RecordTypeDealerVolumeTotal& operator= ( const RecordTypeDealerVolumeTotal& );		
};

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEDEALERVOLUMETOTAL_H


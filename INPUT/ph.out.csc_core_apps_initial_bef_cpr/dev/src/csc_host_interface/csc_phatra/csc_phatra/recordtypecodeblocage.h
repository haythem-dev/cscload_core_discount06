//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCodeBlocage
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECODEBLOCAGE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECODEBLOCAGE_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
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

class RecordTypeCodeBlocage : public core::RecordTypeBase
{
	friend class core::RecordTypeFactory;
	
    public:	
        RecordTypeCodeBlocage();
        ~RecordTypeCodeBlocage();             
		
		virtual void					process( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeCodeBlocage( const RecordTypeCodeBlocage& );
		RecordTypeCodeBlocage& operator= ( const RecordTypeCodeBlocage& );

		void							injectRecordProcessHelper( RecordProcessHelperPtr );

		virtual void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;

		RecordProcessHelperPtr	m_RecordProcessHelperPtr;

		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECODEBLOCAGE_H


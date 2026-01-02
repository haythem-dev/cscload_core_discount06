//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeOther
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEOTHER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEOTHER_H

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

class RecordTypeOther : public core::RecordTypeBase
{
	friend class core::RecordTypeFactory;
    public:	
        RecordTypeOther();
        ~RecordTypeOther();             
		
		virtual void					process( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeOther( const RecordTypeOther& );
		RecordTypeOther& operator= ( const RecordTypeOther& );

		void							injectRecordProcessHelper( RecordProcessHelperPtr );
		
		virtual void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;

		RecordProcessHelperPtr	m_RecordProcessHelperPtr;
		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEOTHER_H


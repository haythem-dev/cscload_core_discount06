
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECODEBLOCKAGEPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECODEBLOCKAGEPTR_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
    namespace pharmosTransaction
    {
		namespace processing
        {
            class RecordTypeCodeBlocage;
            typedef boost::shared_ptr< RecordTypeCodeBlocage > RecordTypeCodeBlocagePtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECODEBLOCKAGEPTR_H


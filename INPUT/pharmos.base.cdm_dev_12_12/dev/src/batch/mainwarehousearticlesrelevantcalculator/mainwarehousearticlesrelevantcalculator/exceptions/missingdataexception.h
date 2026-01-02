//-----------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       27.10.2008
 *  \version    00.00.00.01 first version
 */ 
//-----------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBUTIL_EXCEPTIONS_MISSING_DATA_EXCEPTION_H
#define GUARD_LIBUTIL_EXCEPTIONS_MISSING_DATA_EXCEPTION_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <exceptions/baseexception.h>

namespace libutil  
{
	namespace exceptions
	{
        class MissingDataException : public BaseException
        {
            public:
	            MissingDataException( const basar::ExceptInfo & sInfo );
	            virtual ~MissingDataException();

            private:
	            MissingDataException();					
        };
    }
}

#endif 

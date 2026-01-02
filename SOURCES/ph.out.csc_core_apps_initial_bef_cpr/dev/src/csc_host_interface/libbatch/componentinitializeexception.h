#ifndef GUARD_UTIL_COMPONENT_INITIALIZE_EXCEPTION_H
#define GUARD_UTIL_COMPONENT_INITIALIZE_EXCEPTION_H

#include "baseexception.h"

namespace util
{
	class ComponentInitializeException : public BaseException
	{
		public:
			ComponentInitializeException( const basar::ExceptInfo & sInfo );
			~ComponentInitializeException();

		private:
			ComponentInitializeException();					
	};
}  

#endif 

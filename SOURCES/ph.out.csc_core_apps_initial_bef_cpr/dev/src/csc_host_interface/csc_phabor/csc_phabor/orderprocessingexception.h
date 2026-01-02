//---------------------------------------------------------------------------//
/*! \file
 *  \brief		exception from order processing
 *  \author		Julian Machata
 *  \date		28.04.2013
 *  \version	00.00.00.01 first version
 */ //-----------------------------------------------------------------------//

#ifndef GUARD_CSC_PHABOR_ORDER_PROCESSING_EXCEPTION_H
#define GUARD_CSC_PHABOR_ORDER_PROCESSING_EXCEPTION_H

#include <libbasarcmnutil_exceptions.h>

namespace csc_phabor
{
namespace exception
{
	class OrderProcessingException : public basar::Exception
	{
		public:
			/*! \brief std constructor */
			OrderProcessingException( const basar::ExceptInfo& sInfo )
			: basar::cmnutil::BasarException( sInfo, "OrderProcessingException" )
			{};

			/*! \brief std-destructor */
			~OrderProcessingException(){};

		private:
			//!< forbidden
			OrderProcessingException();		
	};

} // end namespace exception
} // end namespace csc_phabor

#endif // GUARD_CSC_PHABOR_ORDER_PROCESSING_EXCEPTION_H



//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       04.09.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERRESPONSE_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERRESPONSE_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "recordtypebase.h"
#include "recordtypeorderresponse_definitions.h"
#include <classinfo_macros.h>

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	

	class RecordTypeOrderResponse : public RecordTypeBase
	{				
		private:
			RecordTypeOrderResponse( const RecordTypeOrderResponse& );
			RecordTypeOrderResponse& operator= ( const RecordTypeOrderResponse& );

		public:
			RecordTypeOrderResponse( const basar::VarString& serializedbuffer, libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeOrderResponse();						
			
			const OrderResponseValues	doDeserialize() const;

		private:
			const basar::VarString		m_SerializedBuffer;

			RecordType					m_Type;
			static const size_t			LENGTH_RECORDTYPE = 2;

			RecordType					mapRecordType( const basar::VarString& rectype );
			
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERRESPONSE_H

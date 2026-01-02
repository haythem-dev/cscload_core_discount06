//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       04.09.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEBASE_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEBASE_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "recordtypebase_definitions.h"
#include "recordtypeorderresponse_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	class RecordTypeBase
	{		
		public:
			RecordTypeBase( const basar::VarString& recordtypename, const basar::VarString& direction, libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeBase();			
			
			RecordTypeBase( const RecordTypeBase& );
			
		private:			
			RecordTypeBase& operator= ( const RecordTypeBase& );

		public:
			const basar::VarString					serialize() const;					
			const OrderResponseValues				deserialize() const;

			void									setSequentialNo( const size_t& );			

			const size_t&							getSequentialNo() const;
			const basar::VarString&					getDirection() const;
			const basar::VarString&					getRecordTypeName() const;
			const basar::VarString&					getStatus() const;			

		protected:
			virtual const basar::VarString			doSerialize() const; 
			virtual const OrderResponseValues		doDeserialize() const;

		protected:
			void									setRecordTypeName( const basar::VarString& );			

		private:
			basar::VarString						m_RecordTypeName;
			size_t									m_SequentialNo;
			const basar::VarString					m_Direction;
			const basar::VarString					m_Status;			

		protected:
			libcsc_utils::ICSC_LoggerPtr			m_Logger;
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEBASE_H

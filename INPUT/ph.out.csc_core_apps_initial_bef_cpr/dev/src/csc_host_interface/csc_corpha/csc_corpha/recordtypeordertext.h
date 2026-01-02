//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       04.09.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERTEXT_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERTEXT_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "recordtypebase.h"
#include "recordtypeordertext_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	class RecordTypeOrderText : public RecordTypeBase
	{		
		private:
			RecordTypeOrderText( const RecordTypeOrderText& );
			RecordTypeOrderText& operator= ( const RecordTypeOrderText& );

		public:
			RecordTypeOrderText( const TextType, libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeOrderText();

		private:						
			OrderTextValues				m_Values;

		public:

			const basar::VarString		doSerialize() const;

			void						setText( const basar::VarString& );
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERTEXT_H

//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       08.08.2013
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEMSV3INFO_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEMSV3INFO_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>

#include "recordtypebase.h"
#include "recordtypemsv3info_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{		
	class RecordTypeMSV3Info : public RecordTypeBase
	{
		private:
			
			RecordTypeMSV3Info( const RecordTypeMSV3Info& );
			RecordTypeMSV3Info& operator= ( const RecordTypeMSV3Info& );

		public:
			
			RecordTypeMSV3Info( const MSV3InfoTextType&, libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeMSV3Info();

		private:			
			
			MSV3InfoValues				m_Values;

			void						setTextType( const MSV3InfoTextType& );
			
		public:
			
			const basar::VarString		doSerialize() const;
			
			void						setKSCOrderNo( const basar::Long64& );			
			void						setSeqNo( const basar::Long64& );
			void						setText( const basar::VarString& );			
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEMSV3INFO_H

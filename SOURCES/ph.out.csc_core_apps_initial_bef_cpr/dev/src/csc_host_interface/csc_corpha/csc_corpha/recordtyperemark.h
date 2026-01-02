//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       28.05.2014
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEREMARK_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEREMARK_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "recordtypebase.h"
#include "recordtyperemark_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	class RecordTypeRemark : public RecordTypeBase
	{		
		private:
			RecordTypeRemark( const RecordTypeRemark& );
			RecordTypeRemark& operator= ( const RecordTypeRemark& );

		public:
			RecordTypeRemark( libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeRemark();			

		private:		
			RemarkValues				m_Values;			

		public:

			const basar::VarString		doSerialize() const;

			void						setOrderNo( const basar::Long64& );
			void						setPositionNo( const basar::Long64& );
			void						setTextType( const basar::Int32& );
			void						setSequentialNo( const basar::Int32& );								
			void						setText( const basar::VarString& );
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEREMARK_H

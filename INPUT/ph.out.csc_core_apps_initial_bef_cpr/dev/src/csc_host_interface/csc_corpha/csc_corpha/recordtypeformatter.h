//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       04.09.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEFORMATTER_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEFORMATTER_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include <sstream>
#include <iomanip>

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	

	class RecordTypeFormatter
	{
		public:
			RecordTypeFormatter( libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeFormatter();	

			static void						serialize( const basar::Decimal& value, const size_t& length, 
														const size_t& decimalplaces, std::stringstream& out );

			static void						serialize( const basar::Long64& value, const size_t& length, 
														std::stringstream& out );

			static void						serializeLeft( const basar::Long64& value, const size_t& length, 
														std::stringstream& out );

			static void						serialize( const basar::VarString& value, const size_t& length, 
														std::stringstream& out );			

		private:
			RecordTypeFormatter( const RecordTypeFormatter& );
			RecordTypeFormatter& operator= ( const RecordTypeFormatter& );		

			//static basar::Long64		convert( const basar::Decimal&, const size_t& decimalplaces );
	
			static basar::Long64		modifyLength( const basar::Long64& value, const size_t& length );

			static basar::VarString	modifyLength( const basar::VarString& value, const size_t& length );

			libcsc_utils::ICSC_LoggerPtr	m_Logger;
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEFORMATTER_H

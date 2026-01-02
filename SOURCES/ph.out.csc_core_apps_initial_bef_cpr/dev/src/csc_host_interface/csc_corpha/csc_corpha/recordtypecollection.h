//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Heinlein Steffen
 *  \date       04.09.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPECOLLECTION_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPECOLLECTION_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include <boost/shared_ptr.hpp>
#include <queue>
#include "recordtypebaseptr.h"
#include "recordtypebase.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	class RecordTypeCollection
	{		
		private:
			typedef boost::shared_ptr< std::queue< RecordTypeBasePtr > >		RecordTypeQueuePtr;

		public:
			RecordTypeCollection( libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeCollection();						
			
		private:
			RecordTypeCollection( const RecordTypeCollection& );
			RecordTypeCollection& operator= ( const RecordTypeCollection& );		

		public:
			void														clear();
			bool														isEmpty() const;			
			void														addRecord( const RecordTypeBasePtr );
			const RecordTypeBasePtr										getRecord();
			basar::Long64												getCSCOrderNo() const;
			basar::Long64												getTransferTimeID() const;
			void														setCSCOrderNo( const basar::Long64& );
			void														setTransferTimeID( const basar::Long64& );
			size_t														getSize() const; 
			
		private:
			RecordTypeQueuePtr											getRecords() const;		

		private:			
			mutable RecordTypeQueuePtr									m_Records;			
			basar::Long64												m_CSCOrderNo;
			basar::Long64												m_TransferTimeID;
			libcsc_utils::ICSC_LoggerPtr								m_Logger;
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPECOLLECTION_H

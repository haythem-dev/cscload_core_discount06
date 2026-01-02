//---------------------------------------------------------------------------//
/*! \file 
 *  \brief      Encapsulation of creation process of return type
 *  \author     Bjoern Bischof
 *  \date       05.03.2011
 *  \version    00.00.00.01 first version
 */ //-----------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORD_TYPE_FACTORY_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORD_TYPE_FACTORY_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
//#include "pxvbdbconnectionptr.h"
#include "irecordtypetransformerptr.h"
#include "irecordtypeofptr.h"
#include "ipxvbservicelocatorptr.h"
#include "irecordtypetransformercreator.h"
#include "recordtypebaseptr.h"
#include "irecordtypecreator.h"

#include <icsc_loggerptr.h>

#include "recordprocesshelperptr.h"
//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{	

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
	class RecordTypeFactory : public util::IRecordTypeTransformerCreator,
							  public util::IRecordTypeCreator
	{
		public:	
			RecordTypeFactory( pxVerbund::IPXVBServiceLocatorPtr, libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeFactory();
			
			virtual util::IRecordTypeTransformerPtr				createTransformer( const IRecordTypeOfPtr ) const;			
			virtual util::IRecordTypeProcessorPtr				createRecordType( const core::TransactionRecordBasePtr ) const;

		private:
			RecordTypeFactory( const RecordTypeFactory& );
			RecordTypeFactory& operator=( const RecordTypeFactory& );	

			RecordTypeBasePtr									create( const IRecordTypeOfPtr typeOf ) const;

			pxVerbund::IPXVBServiceLocatorPtr				    m_IPXVBServiceLocator;
			libcsc_utils::ICSC_LoggerPtr						m_CSC_Logger;

			processing::RecordProcessHelperPtr					m_RecordProcessHelperPtr;
	};

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod


//----------------------------------------------------------------------------
#endif


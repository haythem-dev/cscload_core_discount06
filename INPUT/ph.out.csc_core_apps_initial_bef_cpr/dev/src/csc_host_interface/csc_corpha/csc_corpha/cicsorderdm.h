//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module (cics file VSAM.DKOTE/VSAM.DKOTO)
 *  \author		Steffen Heinlein
 *  \date		10.09.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERDM_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERDM_H

#include <icsc_loggerptr.h>
#include <searchyiteratorptr.h>
#include "recordtypebaseptr.h"
#include "icicsorderdm.h"
#include "recordtypecollectionptr.h"
#include "cicsrecord.h"
#include "cicsorderaccessormanager.h"

//-------------------------------------------------------------------------------------------------//
// using declarations section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;                    
			class AccessorPropertyTableRef;
            class ConnectionRef;
        }
    }
}

namespace domMod 
{		
namespace corpha
{    
namespace processOrder
{
	class CICSOrderDM : public domMod::corpha::processOrder::ICICSOrderDM
    {
		private:
			static const basar::Int32									NOTINITIALIZED = -1;

	    public:
			CICSOrderDM( const basar::db::aspect::ConnectionRef, libcsc_utils::ICSC_LoggerPtr, libcsc_utils::IApplConfigurationPtr ); 
		    virtual ~CICSOrderDM(); 

	    private:	            
		    CICSOrderDM(const CICSOrderDM& r);
		    CICSOrderDM& operator=(const CICSOrderDM& r);		

		public:
			void														init( const basar::Long64 orderno );
			void														send( recordtypes::RecordTypeCollectionPtr );
			void														retrieve();
			void														shutdown();			
			CICSRecord													getCICSRecord( basar::db::aspect::AccessorPropertyTable_YIterator yit );
			basar::db::aspect::AccessorPropertyTableRef					getPropTab();
			basar::db::aspect::AccessorPropertyTableRef					getResponsePropTab();

        protected:		    

            virtual void                                                doInit();
	        virtual void                                                doShutdown();            			

		private:

			libcsc_utils::ICSC_LoggerPtr								getLogger() const; 

			bool														isInitialized() const; 
			void														prepareForTransfer( recordtypes::RecordTypeCollectionPtr ); 
			
			libcsc_utils::ICSC_LoggerPtr								m_Logger;			
			basar::Long64												m_CSCOrderNo;			
			domMod::searchyiterator::SearchYIteratorPtr					m_SearchYit;		    

			CICSOrderAccessorBasePtr									m_AccessorPtr;
			CICSOrderAccessorBasePtr									m_AccessorResponsePtr;
			CICSOrderAccessorManager									m_CICSOrderAccessorManager;

    }; 
} // namespace processOrder
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDER_CICSORDERDM_H

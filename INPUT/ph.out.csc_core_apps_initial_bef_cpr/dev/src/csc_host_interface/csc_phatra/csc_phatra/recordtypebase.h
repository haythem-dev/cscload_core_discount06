//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeBase
 *  \author Steffen Heinlein
 *  \date   04.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORDTYPEBASE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORDTYPEBASE_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "irecordtypetransformer.h"
#include "irecordtypeprocessor.h"
#include <libbasarcmnutil.h>
#include "ipxvbdbconnectionptr.h"
#include "ipxvbsessionptr.h"

#include <icsc_loggerptr.h>

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
	namespace pharmosTransaction
	{
		namespace core
		{
			class TransactionRecordBase;
		}		
	}
}

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace core
{		
static const basar::VarString PHARMOS_YES( "J" );
static const basar::VarString PHARMOS_NO( "N" );
static const basar::Int16 IFX_YES( 1 );
static const basar::Int16 IFX_NO( 0 );

static const basar::Int32 PXVB_RECORDTYPE_BATCH_INVALID_DATE( 20000001 );
static const basar::Int32 PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_DATE( 0 );

static const basar::Int32 PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_MINDATE( 0 );
static const basar::Date PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_MINDATE( 1900, 1, 1 );
static const basar::Int32 PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_INVALID_MAXDATE( 9999 );
static const basar::Date PXVB_RECORDTYPE_CHANGEARTICLEDETAILS_MAXDATE( 9999, 12, 30 );

static const basar::Int32 PXVB_RECORDTYPE_EXPIRYDATE_INVALID_MINDATE( 0 );
static const basar::Date PXVB_RECORDTYPE_EXPIRYDATE_MINDATE( 1900, 1, 1 );
static const basar::Int32 PXVB_RECORDTYPE_EXPIRYDATE_INVALID_MAXDATE( 9999 );
static const basar::Date PXVB_RECORDTYPE_EXPIRYDATE_MAXDATE( 9999, 12, 30 );

class RecordTypeBase : public util::IRecordTypeTransformer,
					   public util::IRecordTypeProcessor
{			
	friend class RecordTypeFactory;

	////////////////////////////////////
	// member methods
	////////////////////////////////////
    public:		
		RecordTypeBase();        
        ~RecordTypeBase();             

		void							transform( const TransactionRecordBasePtr source, TransactionRecordBasePtr target ) const;
		virtual void					process( const TransactionRecordBasePtr record ) const = 0;

		//enum made according to pvhx01\debvz.h of lu62 project (lines 104-119)
		enum GoodsInBookingType
		{
			ACCOUNT_ADD_QUANTITY			= 1, // Bestand zubuchen
			ACCOUNT_SUB_QUANTITY			= 2, // Bestand abbuchen
			ACCOUNT_SET_QUANTITY			= 8, // Bestand auf festen Wert setzen

			CERTIFICATE_NOT_AVAILABLE		= 3, // freien Bestand für "fehlendes Zertifikat" reservieren
			CERTIFICATE_AVAILABLE			= 4, // Auflösung "fehlendes Zertifikat" Reservierung -> freier Bestand
			CERTIFICATE_UPDATE				= 7, // "fehlendes Zertifikat" Reservierung	absolut setzen -> Differenz +/- freier Bestand

			BATCH_RECALL					= 6, // freien Bestand für "Chargenrückruf" reservieren
			CANCEL_BATCH_RECALL				= 9, // Auflösung "Chargenrückruf" Reservierung -> freier Bestand

			PACKAGE_INSERT_NOT_AVAILABLE	= 5	 // freien Bestand für "fehlender Beipack" reservieren
		};

    private:
        RecordTypeBase( const RecordTypeBase& );
		RecordTypeBase& operator= ( const RecordTypeBase& );        		

		virtual void					doTransform( const TransactionRecordBasePtr source, TransactionRecordBasePtr target ) const = 0;
		
		void							injectPXVBDBConnection( pxVerbund::IPXVBDBConnectionPtr );
		void							injectPXVBSession( pxVerbund::IPXVBSessionPtr );
		void							injectCSC_Logger( libcsc_utils::ICSC_LoggerPtr );
		

	////////////////////////////////////
	// member variables
	////////////////////////////////////
	protected:		
		pxVerbund::IPXVBDBConnectionPtr	m_PXVBDBConnection;
		pxVerbund::IPXVBSessionPtr		m_PXVBSession;
		libcsc_utils::ICSC_LoggerPtr	m_CSC_Logger;
};

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_CORE_RECORDTYPEBASE_H


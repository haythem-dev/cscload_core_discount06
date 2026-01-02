//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Heinlein Steffen
 *  \date       04.09.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERHEADER_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERHEADER_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>
#include "recordtypebase.h"
#include "recordtypeorderheader_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{

	class RecordTypeOrderHeader : public RecordTypeBase
	{
		private:
			RecordTypeOrderHeader( const RecordTypeOrderHeader& );
			RecordTypeOrderHeader& operator= ( const RecordTypeOrderHeader& );

		public:
			RecordTypeOrderHeader( libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeOrderHeader();

		private:
			OrderHeaderValues			m_Values;

		public:
			const basar::VarString		doSerialize() const;

			void						setPaymentType( const basar::VarString& );
			void						setMandant( const basar::Int32 );
			void						setOrderNo( const basar::Long64& );
			void						setCustomerNo( const basar::Long64& );
			void						setTerminalId( const basar::VarString& );
			void						setTourId( const basar::VarString& );
			void						setTourIdOld( const basar::VarString& );
			void						setUserId( const basar::Long64& );
			void						setBranchNo( const basar::Int32 );
			void						setET1Flags( const basar::Long64& );
			void						setET2Flags( const basar::Long64& );
			void						setET3Flags( const basar::Long64& );
			void						setET4Flags( const basar::Long64& );
			void						setOrderType( const basar::VarString& );
			void						setPickingType( const basar::VarString& );
			void						setBookingType( const basar::VarString& );
			void						setValidationDate( const basar::Long64& );
			void						setOrderValue( basar::Decimal& );
			void						setDeliveryValue( basar::Decimal& );
			void						setAvgLineValue( basar::Decimal& );
			void						setLines( const basar::Long64& );
			void						setLinesNoCalc( const basar::Long64& );
			void						setLinesDialUp( const basar::Long64& );
			void						setLinesDialUpErrors( const basar::Long64& );
			void						setLinesAlphaTxt( const basar::Long64& );
			void						setLinesNarcotics( const basar::Long64& );
			void						setCashDiscountPercentage( basar::Decimal& );
			void						setOrigin( const basar::VarString& );
			void						setOriginBranchNo( const basar::Int32 );
			void						setNextTourId( const basar::VarString& );
			void						setLastTourId( const basar::VarString& );
			void						setDialUpOrderNo( const basar::Long64& );
			void						setDialUpDeviceType( const basar::VarString& );
			void						setHint( const basar::VarString& );
			void						setParentBranchFlag( const basar::VarString& );
			void						setBatchOrderNo( const basar::Long64& );
			void						setSubOrderType( const basar::VarString& );
			void						setPaymentTerm( const basar::VarString& );
			void						setValueMonthManual( const basar::Int32 );
			void						setValueMonthAuto( const basar::Int32 );
			void						setPartialOrder( const basar::Int32 );
			void						setTenderNo( const basar::Long64& );
			void						setContractNo( const basar::VarString& );
			void						setShipmentDate( const basar::Long64& );
			void						setDiscountAccFromDate( const basar::Long64& );
			void						setDiscountAccToDate( const basar::Long64& );
			void						setChainMember( const basar::VarString& );
			void						setNarcoticsFormNo( const basar::VarString& );
			void						setValueDateDays( const basar::Long64& );
			void						setPrintPriceProposal( const basar::VarString& );
			void						setDeductionPharmacyPurchasePrice( const basar::VarString& );
			void						setDeductionPharmacySellPrice( const basar::VarString& );
			void						setDeductionColumnNo( const basar::VarString& );
			void						setEmailInvoice( const basar::VarString& );
			void						setET5Flags( const basar::Long64& );
			void						setET6Flags( const basar::Long64& );
			void						setXMLReference( const basar::VarString& );
			void						setPseudoInvoiceNo( const basar::Int32 );
			void						setMSV3Order( const basar::VarString& );
			void						setTenderType( const basar::Int32 );
			void						setNumberOfDiscountRecords( const basar::Int16 );
			void						setPurchaseOrderNo( const basar::Int32 );
			void						setExpressDeliveryCharge( const basar::VarString& );
            void                        setProformaOrderDate(const basar::Long64&);
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERHEADER_H

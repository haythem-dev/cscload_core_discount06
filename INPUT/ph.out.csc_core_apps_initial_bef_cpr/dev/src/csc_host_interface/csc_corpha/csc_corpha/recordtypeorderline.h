//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Heinlein Steffen
 *  \date       04.09.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERLINE_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERLINE_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <icsc_loggerptr.h>

#include "recordtypebase.h"
#include "recordtypeorderline_definitions.h"

namespace domMod
{
namespace corpha
{
namespace recordtypes
{

	class RecordTypeOrderLine : public RecordTypeBase
	{
		private:
			RecordTypeOrderLine( const RecordTypeOrderLine& );
			RecordTypeOrderLine& operator= ( const RecordTypeOrderLine& );

		public:
			RecordTypeOrderLine( libcsc_utils::ICSC_LoggerPtr );
			~RecordTypeOrderLine();

		private:
			OrderLineValues				m_Values;

		public:
			const basar::VarString		doSerialize() const;

			void						setLineNo( const basar::Long64& );
			void 						setArticleNo( const basar::Long64& );
			void 						setLineType( const basar::Int32 );
			void 						setDeviceType( const basar::Int32 );
			void 						setQState( const basar::Int32 );
			void 						setArticleState( const basar::Int32 );
			void 						setET1Flags( const basar::Long64& );
			void 						setET2Flags( const basar::Long64& );
			void 						setET3Flags( const basar::Long64& );
			void 						setET4Flags( const basar::Long64& );
			void 						setET5Flags( const basar::Long64& );
			void 						setET6Flags( const basar::Long64& );
			void 						setOrderQty( const basar::Long64& );
			void 						setDispensingForm( const basar::VarString& );
			void 						setUnit( const basar::VarString& );
			void 						setArticleName( const basar::VarString& );
			void						setDiscountable( const basar::Int32 );
			void 						setCommodityGroup( const basar::VarString& );
			void 						setConfirmedQty( const basar::Long64& );
			void 						setDeliveryQty( const basar::Long64& );
			void 						setBookedQty( const basar::Long64& );
			void 						setQtyRebateInKind( const basar::Long64& );
			void 						setQtyRebateInKindWholesale( const basar::Long64& );
			void 						setQtyRebateInKindManufacturer( const basar::Long64& );
			void 						setPharmacyPurchasePrice( basar::Decimal& );
			void 						setPharmacySellPrice( basar::Decimal& );
			void 						setNetPrice( basar::Decimal& );
			void 						setCostPrice( basar::Decimal& );
			void 						setNetCostPrice( basar::Decimal& );
			void 						setDiscountValue( basar::Decimal& );
			void 						setFixedDiscount( basar::Decimal& );
			void 						setHints( const basar::VarString& );
			void 						setIBTQty( const basar::Long64& );
            basar::Int32			    getIBTBranchNo();
			void 						setIBTBranchNo( const basar::Int32 );
			void 						setIBTBranchNo2( const basar::Int32 );
			void 						setIBTOriginCustomerNo( const basar::Long64& );
			void 						setIBTOriginOrderNo( const basar::Long64& );
			void 						setIBTOriginLineNo( const basar::Long64& );
			void 						setArtET2( const basar::Long64& );
			void 						setPreDeliveryQty( const basar::Long64& );
			void 						setChangeDiscount( basar::Decimal& );
			void 						setBonusAbility( basar::Decimal& );
			void 						setChangeDiscountType( const basar::VarString& );
			void 						setXMLReference( const basar::VarString& );
			void 						setCodeBlocage( const basar::VarString& );
			void 						setTaxLevel( const basar::VarString& );
			void 						setInvoicedPurchaseGroup( const basar::VarString& );
			void 						setOriginalIBTQty( const basar::Long64& );
			void 						setPriceType( const basar::Int32 );
			void 						setPaymentTargetDiscPercentage1( basar::Decimal& );
			void 						setPaymentTargetDiscPercentage2( basar::Decimal& );
			void 						setPaymentTargetDiscPercentage3( basar::Decimal& );
			void 						setPaymentTargetDiscPercentage4( basar::Decimal& );
			void 						setPaymentTargetDiscPercentage5( basar::Decimal& );
			void 						setPaymentTargetDiscPercentage6( basar::Decimal& );
			void 						setInvoicePrice( basar::Decimal& );
			void						setMaxPaymentTarget( const basar::Int32 );
			void 						setContLevel( const basar::VarString& );
			void 						setMaxPharmacySellPrice( basar::Decimal& );
			void 						setSkontoAbility( basar::Decimal& );
			void 						setDesiredBatch( const basar::VarString& );
			void						setAmedisPriceDifference( basar::Decimal& );
			void 						setCalcPharmacySellPrice( basar::Decimal& );
			void 						setArticleCode( const basar::VarString& );
			void						setCodeType( const basar::Int32 );
			void						setServiceNo( const basar::Int32 );
			void						setET7Flags( const basar::Long64& );
			void						setMarginCluster( basar::Decimal& );
			void						setBusinessType( const basar::Int16 );
			void						setTourIdIbt( const basar::VarString& );
			void						setSubDeviceType( const basar::Int16 );
			void						setIBTWeekday( const basar::Int16 );
			void						setNumberOfDiscountRecords( const basar::Int16 );
			void						setPurchaseRelevantQuantity( const basar::Long64& );
			void						setOriginalOrderedQuantity( const basar::Long64& );
			void						setIBTDeliveryDate( const basar::Long64& );
            void                        setFixBatch(const bool value);
            void                        setIBTOriginFMDCustomer(const bool value);
			void						setPromotionNo(const basar::Int32);
	};

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERLINE_H

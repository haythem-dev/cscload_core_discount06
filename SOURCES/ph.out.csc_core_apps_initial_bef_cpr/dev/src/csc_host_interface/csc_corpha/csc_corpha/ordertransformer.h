//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Heinlein Steffen
 *  \date       18.09.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PROCESSORDERDM_ORDERTRANSFORMER_H
#define GUARD_DOMMOD_CORPHA_PROCESSORDERDM_ORDERTRANSFORMER_H

#include <icsc_loggerptr.h>
#include <iapplconfigurationptr.h>

#include "pxvborderdmptr.h"
#include "pxvborderitemptr.h"
#include "recordtypecollectionptr.h"
#include "recordtypebaseptr.h"
#include "recordtypeorderlineptr.h"
#include "recordtypediscountptr.h"
#include "recordtypeorderheaderptr.h"
#include "icicsorderdmptr.h"

#include "pxvborderheaderptr.h"
#include "pxvborderheader.h"

#include "pxvborderitemptr.h"
#include "pxvborderitem.h"
#include <discount/orderpositiondiscount/orderpositiondiscountmodeenum.h>

namespace domMod
{
namespace corpha
{
namespace ProcessOrderDM
{
	class OrderTransformer
	{
		private:
			struct DiscountDetails
			{
				basar::Decimal DiscountPercentage;					// tDECIMAL Barrab     = 0.0;
				basar::Decimal PaymentTargetDiscPercentage1;		// tDECIMAL pBarrab1   = 0.0;
				basar::Decimal PaymentTargetDiscPercentage2;		// tDECIMAL pBarrab2   = 0.0;
				basar::Decimal PaymentTargetDiscPercentage3;		// tDECIMAL pBarrab3   = 0.0;
				basar::Decimal PaymentTargetDiscPercentage4;		// tDECIMAL pBarrab4   = 0.0;
				basar::Decimal PaymentTargetDiscPercentage5;		// tDECIMAL pBarrab5   = 0.0;
				basar::Decimal PaymentTargetDiscPercentage6;		// tDECIMAL pBarrab6   = 0.0;
				basar::Decimal SurchargePercentage;					// tDECIMAL pSurchargePct = 0.0;
				basar::Decimal LogisticSurcharge;					// tDECIMAL Logistik   = 0.0;
				basar::Decimal MISK;								// tDECIMAL pMISK      = 0.0;
				basar::Decimal PDIFF;								// tDECIMAL pPDIFF     = 0.0;
				basar::Decimal KAVP2;								// tDECIMAL pKAVP2     = 0.0;
				basar::VarString DiscountType;						// char    cBarrabTyp = '0';
				basar::VarString CustomerPurchaseGroupDiscount;		// nString  cFakEkgr;

				DiscountDetails()
				{
					DiscountType = "0";
					CustomerPurchaseGroupDiscount = "";
				}
			};

		private:
			OrderTransformer( const OrderTransformer& );
			OrderTransformer& operator= ( const OrderTransformer& );

		public:
			OrderTransformer( libcsc_utils::ICSC_LoggerPtr, libcsc_utils::IApplConfigurationPtr );
			~OrderTransformer();

		public:
			recordtypes::RecordTypeCollectionPtr			transform( pxVerbund::PXVBOrderDMPtr );
			recordtypes::RecordTypeCollectionPtr			transform( domMod::corpha::processOrder::ICICSOrderDMPtr );

		private:
			recordtypes::RecordTypeCollectionPtr			getCollection();

			void											addOrderHeader( pxVerbund::PXVBOrderDMPtr );
			void											addRemarks( pxVerbund::PXVBOrderDMPtr );
			void											addHeaderTexts( pxVerbund::PXVBOrderDMPtr );
			void											addFooterTexts( pxVerbund::PXVBOrderDMPtr );
			void											addOrderInfo( pxVerbund::PXVBOrderDMPtr );
			void											addOrderItems( pxVerbund::PXVBOrderDMPtr );
			void											addOrderItem( pxVerbund::PXVBOrderItemPtr item, pxVerbund::PXVBOrderDMPtr order );
			void											addMSV3PackageLabelItemInfo( pxVerbund::PXVBOrderItemPtr item, recordtypes::RecordTypeOrderLinePtr record, pxVerbund::PXVBOrderDMPtr order );
			void                                            addInterBranchTransferInfo( pxVerbund::PXVBOrderDMPtr, pxVerbund::PXVBOrderItemPtr, recordtypes::RecordTypeOrderLinePtr);
			void											addMSV3InfoItems( pxVerbund::PXVBOrderDMPtr );
			void											addMSV3OrderLabel( pxVerbund::PXVBOrderDMPtr );
			void											addMSV3PackageLabels( pxVerbund::PXVBOrderDMPtr );
			void											addMSV3PackageLabel( pxVerbund::PXVBOrderDMPtr, const basar::Int32, const basar::VarString& );
			void											addDiscountRecords( pxVerbund::PXVBOrderHeaderPtr, recordtypes::RecordTypeOrderHeaderPtr record );
			void											addDiscountRecords( pxVerbund::PXVBOrderItemPtr, recordtypes::RecordTypeOrderLinePtr record );
			void											addOldDiscountRecords( pxVerbund::PXVBOrderItemPtr, recordtypes::RecordTypeOrderLinePtr record );
			void											addOldDiscountRecordsHR( pxVerbund::PXVBOrderItemPtr, recordtypes::RecordTypeOrderLinePtr record );
			void											addOldDiscountRecordsFR( pxVerbund::PXVBOrderItemPtr, recordtypes::RecordTypeOrderLinePtr record );
			void											addOldDiscountRecordsCH( pxVerbund::PXVBOrderItemPtr orderitem, recordtypes::RecordTypeOrderLinePtr recordItem );
			recordtypes::RecordTypeDiscountPtr				addOldDiscountRecord( pxVerbund::PXVBOrderItemPtr orderitem,
																libcsc::discount::OrderPositionDiscountMode discMode,
																basar::Decimal discountValue,
																basar::Int16 & discountCounter );

            void                                            addIBTPickingInformationForIBT(pxVerbund::PXVBOrderItemPtr item);

			const basar::Decimal							getCashRebate(pxVerbund::PXVBOrderItemPtr orderitem, libcsc::discount::OrderPositionDiscountModeEnum mode);
			basar::Int16									getCashRebateCalcFromFlag(pxVerbund::PXVBOrderItemPtr orderitem);
			basar::Int16									getCashRebateApplyToFlag(pxVerbund::PXVBOrderItemPtr orderitem);
			const basar::Decimal							taxSpannenCheckGermany(pxVerbund::PXVBOrderItemPtr orderitem, const basar::Decimal& discountPct);

			void											setStdItemValues( pxVerbund::PXVBOrderItemPtr, recordtypes::RecordTypeOrderLinePtr );
			void											setNormalOrderItemValues( pxVerbund::PXVBOrderItemPtr, recordtypes::RecordTypeOrderLinePtr );
			void											setDispoItemValues( pxVerbund::PXVBOrderItemPtr, recordtypes::RecordTypeOrderLinePtr );
//			void											setNumberOfDiscountRecords( recordtypes::RecordTypeOrderLinePtr record, pxVerbund::PXVBOrderItemPtr item );

			bool											isSetInvoicePrice(const int branchno) const;

			const basar::VarString							getArticleHint( pxVerbund::PXVBOrderItemPtr ) const;
			bool											transformArticleHint(basar::VarString hintText, basar::VarString& hintType, basar::Decimal& discountVal, basar::Int16& discountCalcFrom, basar::Int16& discountApplyTo);
			const OrderTransformer::DiscountDetails			getDiscountDetails( pxVerbund::PXVBOrderItemPtr ) const;

			recordtypes::RecordTypeDiscountPtr				createRecordTypeDiscount( pxVerbund::PXVBOrderItemPtr orderitem );

		private:
			recordtypes::RecordTypeCollectionPtr			m_RecordTypeCollection;
			libcsc_utils::ICSC_LoggerPtr					m_Logger;
			libcsc_utils::IApplConfigurationPtr				m_ApplConfiguration;
	};

} // namespace ProcessOrderDM
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PROCESSORDERDM_ORDERTRANSFORMER_H

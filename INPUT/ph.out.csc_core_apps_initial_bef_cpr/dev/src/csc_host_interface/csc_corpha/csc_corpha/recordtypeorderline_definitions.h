//----------------------------------------------------------------------------
/*! \file
 *  \brief		definitions for RecordTypeOrderLine
 *  \author		Steffen Heinlein
 *  \date		06.09.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERLINE_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERLINE_DEFINITIONS_H

#include <libbasarcmnutil.h>

namespace domMod
{
namespace corpha
{
namespace recordtypes
{
	struct OrderLineValues													// DX04P1:
	{																		// ..................................
		basar::VarString			RecordType;								// POS-NAME
		basar::Long64				LineNo;									// POS-NUMMER
		basar::Long64				ArticleNo;								// POS-ARTIKELNR
		basar::Int32				LineType;								// POS-TYP
		basar::Int32				DeviceType;								// POS-GERAETTYP
		basar::Int32				QState;									// POS-QSTATE
		basar::Int32				ArticleState;							// POS-ARTSTATE
		basar::Long64				ET1Flags;								// POS-ET1
		basar::Long64				ET2Flags;								// POS-ET2
		basar::Long64				ET3Flags;								// POS-ET3
		basar::Long64				ET4Flags;								// POS-ET4
		basar::Long64				ET5Flags;								// POS-ET5
		basar::Long64				ET6Flags;								// POS-ET6
		basar::Long64				OrderQty;								// POS-BESMG
		basar::VarString			DispensingForm;							// POS-DRFO
		basar::VarString			Unit;									// POS-EINHEIT
		basar::VarString			ArticleName;							// POS-ABEZ
		basar::Int32				Discountable;							// POS-KRAB
		basar::VarString			CommodityGroup;							// POS-WGR
		basar::VarString			FILLER_01;								// POS-FIL1
		basar::Long64				ConfirmedQty;							// POS-BSTMG
		basar::Long64				DeliveryQty;							// POS-MGLFG
		basar::Long64				BookedQty;								// POS-MGAB
		basar::Long64				QtyRebateInKind;						// POS-MGOB
		basar::VarString			FILLER_02;								// POS-NRBA --> FILLER_02 C8
		basar::Long64				QtyRebateInKindWholesale;				// POS-NRGR
		basar::Long64				QtyRebateInKindManufacturer;			// POS-NRHE
		basar::Decimal				PharmacyPurchasePrice;					// POS-AEP
		basar::Decimal				PharmacySellPrice;						// POS-AVP
		basar::Decimal				NetPrice;								// POS-NEP
		basar::Decimal				CostPrice;								// POS-GEP
		basar::Decimal				NetCostPrice;							// POS-NGEP
		basar::VarString			DiscountValueSign;						// POS-RBDMVZ
		basar::Decimal				DiscountValue;							// POS-RBDM
		basar::VarString			FILLER_03;								// POS-FESTDM --> FILLER_03 C15
		basar::Decimal				FixedDiscount;							// POS-FERA
		basar::VarString			FILLER_04;								// POS-FESTPREIS --> FILLER_04 C15
		basar::VarString			Hints;									// POS-TEXT
		basar::Long64				IBTQty;									// POS-VBMENGE
		basar::Int32				IBTBranchNo;							// POS-VBFIL1
		basar::Int32				IBTBranchNo2;							// POS-VBFIL2
		basar::Long64				IBTOriginCustomerNo;					// POS-VBURIDF
		basar::Long64				IBTOriginOrderNo;						// POS-VBUKAUF
		basar::Long64				IBTOriginLineNo;						// POS-VBUPOSNR
		basar::VarString			FILLER_05;								// POS-AHW --> FILLER_05 C2
		basar::Long64				ArtET2;									// POS-ARTET2
		basar::Long64				PreDeliveryQty;							// POS-NME
		basar::Decimal				ChangeDiscount;							// POS-ZURA
		basar::Decimal				BonusAbility;							// POS-MIBO
		basar::VarString			ChangeDiscountType;						// POS-ZURATYP
		basar::VarString			XMLReference;							// POS-REFNR
		basar::VarString			CodeBlocage;							// POS-CBL
		basar::VarString			TaxLevel;								// POS-TAXLEVEL
		basar::VarString			InvoicedPurchaseGroup;					// POS-FAKEKGR
		basar::Long64				OriginalIBTQty;							// POS-VBMGOP
		basar::Int32				PriceType;								// POS-PREISTYP
		basar::Decimal				PaymentTargetDiscPercentage1;			// POS-ZZPCT1				=> P1ZZRAB(1)
		basar::Decimal				PaymentTargetDiscPercentage2;			// POS-ZZPCT2				=> P1ZZRAB(2)
		basar::Decimal				PaymentTargetDiscPercentage3;			// POS-ZZPCT3				=> P1ZZRAB(3)
		basar::Decimal				PaymentTargetDiscPercentage4;			// POS-ZZPCT4				=> P1ZZRAB(4)
		basar::Decimal				PaymentTargetDiscPercentage5;			// POS-ZZPCT5				=> P1ZZRAB(5)
		basar::Decimal				PaymentTargetDiscPercentage6;			// POS-ZZPCT6				=> P1ZZRAB(6)
		basar::Decimal				InvoicePrice;							// POS-FAP					=> P1FAP
		basar::Int32				MaxPaymentTarget;						// POS-LZAHLZ				=> P1LZAHLZ
		basar::VarString			ContLevel;								// POS-CONTLEVEL			=> P1LGNR
		basar::Decimal				MaxPharmacySellPrice;					// POS-MAVP					=> P1MAVP
		basar::Decimal				SkontoAbility;							// POS-MISK					=> P1MISK
		basar::VarString			DesiredBatch;							// POS-VORCHA				=> P1VORCHA
		basar::Decimal				AmedisPriceDifference;					// POS-PDIFF				=> P1PDIFF
		basar::Decimal				CalcPharmacySellPrice;					// POS-KAVP2				=> P1KAVP2
		basar::VarString			ArticleCode;							// POS-ACODE				=> P1ACODE
		basar::Int32				CodeType;								// POS-CTYP					=> P1CTYP
		basar::Int32				ServiceNo;								// POS-SERVICENR
		basar::Long64				ET7Flags;								// POS-ET7					=> P1ET7
		basar::Decimal				MarginCluster;							// POS-ZSPCT
		basar::Int16				BusinessType;							// POS-BTYP
		basar::VarString			TourIdIbt;								// POS-VBTOUR
		basar::Int16                SubDeviceType;							// POS-SUBGTYP
		basar::Int16				IBTWeekday;								// POS-IBTWEEKDAY
		basar::Int16				NumberOfDiscountRecords;				// POS-ANZPRA
		basar::Long64				PurchaseRelevantQuantity;				// POS-ABVWMG
		basar::Long64				OriginalOrderedQuantity;				// POS-URBMG
		basar::Long64				IBTDeliveryDate;						// POS-VBLIEFDAT
        basar::VarString            FixBatch;                               // POS-FIXBATCH
        basar::VarString            IBTOriginFMDCustomer;                   // POS-URIDFFMD
		basar::Int32				PromotionNo;							// POS-PROMONR

		OrderLineValues()
		{
			init();
		}

		void init()
		{
			LineNo = 0;
			ArticleNo = 0;
			LineType = 0;
			DeviceType = 0;
			QState = 0;
			ArticleState = 0;
			ET1Flags = 0;
			ET2Flags = 0;
			ET3Flags = 0;
			ET4Flags = 0;
			ET5Flags = 0;
			ET6Flags = 0;
			OrderQty = 0;
			Discountable = 0;
			ConfirmedQty = 0;
			DeliveryQty = 0;
			BookedQty = 0;
			QtyRebateInKind = 0;
			FILLER_02 = "00000000";
			QtyRebateInKindWholesale = 0;
			QtyRebateInKindManufacturer = 0;
			IBTQty = 0;
			IBTBranchNo = 0;
			IBTBranchNo2 = 0;
			IBTOriginCustomerNo = 0;
			IBTOriginOrderNo = 0;
			IBTOriginLineNo = 0;
			ArtET2 = 0;
			PreDeliveryQty = 0;
			OriginalIBTQty = 0;
			PriceType = 0;
			MaxPaymentTarget = 0;
			CodeType = 0;
			ServiceNo = 0;
			ET7Flags = 0;
			RecordType = "P1";
			ChangeDiscountType = "0";
			TaxLevel = "0";
			ContLevel = "0";
			BusinessType = 0;
			TourIdIbt = "000000";
			SubDeviceType = 0;
			IBTWeekday = 0;
			NumberOfDiscountRecords = 0;
			PurchaseRelevantQuantity = 0;
			OriginalOrderedQuantity = 0;
			IBTDeliveryDate = 0;
            FixBatch = "N";
            IBTOriginFMDCustomer = "N";
			PromotionNo = 0;
		}
	};

	namespace OrderLineFormat
	{
		static const size_t LENGTH_RECORDTYPE = 2;
		static const size_t LENGTH_LINENO = 7;
		static const size_t LENGTH_ARTICLENO = 7;
		static const size_t LENGTH_LINETYPE = 2;
		static const size_t LENGTH_DEVICETYPE = 2;
		static const size_t LENGTH_QSTATE = 2;
		static const size_t LENGTH_ARTICLESTATE = 2;
		static const size_t LENGTH_ET1FLAGS = 8;
		static const size_t LENGTH_ET2FLAGS = 8;
		static const size_t LENGTH_ET3FLAGS = 8;
		static const size_t LENGTH_ET4FLAGS = 8;
		static const size_t LENGTH_ET5FLAGS = 8;
		static const size_t LENGTH_ET6FLAGS = 8;
		static const size_t LENGTH_ORDERQTY = 8;
		static const size_t LENGTH_DISPENSINGFORM = 3;
		static const size_t LENGTH_UNIT = 9;
		static const size_t LENGTH_ARTICLENAME = 30;
		static const size_t LENGTH_DISCOUNTABLE = 2;
		static const size_t LENGTH_COMMODITYGROUP = 5;
		static const size_t LENGTH_FILLER_01 = 7;
		static const size_t LENGTH_CONFIRMEDQTY = 8;
		static const size_t LENGTH_DELIVERYQTY = 8;
		static const size_t LENGTH_BOOKEDQTY = 8;
		static const size_t LENGTH_QTYREBATEINKIND = 8;
		static const size_t LENGTH_FILLER_02 = 8;
		static const size_t LENGTH_QTYREBATEINKINDWHOLESALE = 8;
		static const size_t LENGTH_QTYREBATEINKINDMANUFACTURER = 8;
		static const size_t LENGTH_PHARMACYPURCHASEPRICE = 13;
			static const size_t DECPLACES_PHARMACYPURCHASEPRICE = 4;
		static const size_t LENGTH_PHARMACYSELLPRICE = 13;
			static const size_t DECPLACES_PHARMACYSELLPRICE = 4;
		static const size_t LENGTH_NETPRICE = 13;
			static const size_t DECPLACES_NETPRICE = 4;
		static const size_t LENGTH_COSTPRICE = 13;
			static const size_t DECPLACES_COSTPRICE = 4;
		static const size_t LENGTH_NETCOSTPRICE = 13;
			static const size_t DECPLACES_NETCOSTPRICE = 4;
		static const size_t LENGTH_DISCOUNTVALUESIGN = 1;
		static const size_t LENGTH_DISCOUNTVALUE = 15;
			static const size_t DECPLACES_DISCOUNTVALUE = 4;

		static const size_t LENGTH_FILLER_03 = 15;

		static const size_t LENGTH_FIXEDDISCOUNT = 15;
			static const size_t DECPLACES_FIXEDDISCOUNT = 4;

			static const size_t LENGTH_FILLER_04 = 15;

		static const size_t LENGTH_HINTS = 30;
		static const size_t LENGTH_IBTQTY = 5;
		static const size_t LENGTH_IBTBRANCHNO = 2;
		static const size_t LENGTH_IBTBRANCHNO2 = 2;
		static const size_t LENGTH_IBTORIGINCUSTOMERNO = 7;
		static const size_t LENGTH_IBTORIGINORDERNO = 6;
		static const size_t LENGTH_IBTORIGINLINENO = 5;
		static const size_t LENGTH_FILLER_05 = 2;
		static const size_t LENGTH_ARTET2 = 8;
		static const size_t LENGTH_PREDELIVERYQTY = 8;
		static const size_t LENGTH_CHANGEDISCOUNT = 15;
			static const size_t DECPLACES_CHANGEDISCOUNT = 4;
		static const size_t LENGTH_BONUSABILITY = 15;
			static const size_t DECPLACES_BONUSABILITY = 4;
		static const size_t LENGTH_CHANGEDISCOUNTTYPE = 1;
		static const size_t LENGTH_XMLREFERENCE = 9;
		static const size_t LENGTH_CODEBLOCAGE = 1;
		static const size_t LENGTH_TAXLEVEL = 1;
		static const size_t LENGTH_INVOICEDPURCHASEGROUP = 3;
		static const size_t LENGTH_ORIGINALIBTQTY = 5;
		static const size_t LENGTH_PRICETYPE = 7;
		static const size_t LENGTH_PAYMENTTARGETDISCPERCENTAGE1 = 5;
			static const size_t DECPLACES_PAYMENTTARGETDISCPERCENTAGE1 = 2;
		static const size_t LENGTH_PAYMENTTARGETDISCPERCENTAGE2 = 5;
			static const size_t DECPLACES_PAYMENTTARGETDISCPERCENTAGE2 = 2;
		static const size_t LENGTH_PAYMENTTARGETDISCPERCENTAGE3 = 5;
			static const size_t DECPLACES_PAYMENTTARGETDISCPERCENTAGE3 = 2;
		static const size_t LENGTH_PAYMENTTARGETDISCPERCENTAGE4 = 5;
			static const size_t DECPLACES_PAYMENTTARGETDISCPERCENTAGE4 = 2;
		static const size_t LENGTH_PAYMENTTARGETDISCPERCENTAGE5 = 5;
			static const size_t DECPLACES_PAYMENTTARGETDISCPERCENTAGE5 = 2;
		static const size_t LENGTH_PAYMENTTARGETDISCPERCENTAGE6 = 5;
			static const size_t DECPLACES_PAYMENTTARGETDISCPERCENTAGE6 = 2;
		static const size_t LENGTH_INVOICEPRICE = 13;
			static const size_t DECPLACES_INVOICEPRICE = 4;
		static const size_t LENGTH_MAXPAYMENTTARGET = 2;
		static const size_t LENGTH_CONTLEVEL = 1;
		static const size_t LENGTH_MAXPHARMACYSELLPRICE = 13;
			static const size_t DECPLACES_MAXPHARMACYSELLPRICE = 4;
		static const size_t LENGTH_SKONTOABILITY = 7;
			static const size_t DECPLACES_SKONTOABILITY = 2;
		static const size_t LENGTH_DESIREDBATCH = 15;
		static const size_t LENGTH_AMEDISPRICEDIFFERENCE = 7;
			static const size_t DECPLACES_AMEDISPRICEDIFFERENCE = 2;
		static const size_t LENGTH_CALCPHARMACYSELLPRICE = 9;
			static const size_t DECPLACES_CALCPHARMACYSELLPRICE = 4;
		static const size_t LENGTH_ARTICLECODE = 25;
		static const size_t LENGTH_CODETYPE = 3;
		static const size_t LENGTH_SERVICENO = 5;
		static const size_t LENGTH_ET7FLAGS = 8;
		static const size_t LENGTH_MARGINCLUSTER = 5;
			static const size_t DECPLACES_MARGINCLUSTER = 2;
		static const size_t LENGTH_BUSINESSTYPE = 3;
		static const size_t LENGTH_TOURIDIBT = 6;
		static const size_t LENGTH_SUBDEVICETYPE = 2;
		static const size_t LENGTH_IBTWEEKDAY = 1;
		static const size_t LENGTH_NUMBEROFDISCOUNTRECORDS = 2;
		static const size_t LENGTH_PURCHASERELEVANTQUANTITY = 8;
		static const size_t LENGTH_ORIGINALORDEREDQUANTITY = 8;
		static const size_t LENGTH_IBTDELIVERYDATE = 8;
        static const size_t LENGTH_FIXBATCH = 1;
        static const size_t LENGTH_IBTORIGINFMDCUSTOMER = 1;
		static const size_t LENGTH_PROMOTIONNO = 5;
	}

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERLINE_DEFINITIONS_H

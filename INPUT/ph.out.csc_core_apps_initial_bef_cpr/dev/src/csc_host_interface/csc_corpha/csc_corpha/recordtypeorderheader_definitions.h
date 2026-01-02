//----------------------------------------------------------------------------
/*! \file
 *  \brief		definitions for RecordTypeOrderHeader
 *  \author		Steffen Heinlein
 *  \date		06.09.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERHEADER_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERHEADER_DEFINITIONS_H

#include <libbasarcmnutil.h>

namespace domMod
{
namespace corpha
{
namespace recordtypes
{
	struct OrderHeaderValues
	{
		basar::VarString					RecordType;
		basar::Int32						Mandant;
		basar::Long64						OrderNo;
		basar::Long64						CustomerNo;
		basar::VarString					TerminalId;
		basar::VarString					TourId;
		basar::VarString					TourIdOld;
		basar::Long64						UserId;
		basar::Int32						BranchNo;
		basar::Long64						ET1Flags;
		basar::Long64						ET2Flags;
		basar::Long64						ET3Flags;
		basar::Long64						ET4Flags;
		basar::VarString					OrderType;
		basar::VarString					PickingType;
		basar::VarString					BookingType;
		basar::Long64						ValidationDate;
		basar::Decimal						OrderValue;
		basar::Decimal						DeliveryValue;
		basar::Decimal						AvgLineValue;
		basar::Long64						Lines;
		basar::Long64						LinesNoCalc;
		basar::Long64						LinesDialUp;
		basar::Long64						LinesDialUpErrors;
		basar::Long64						LinesAlphaTxt;
		basar::Long64						LinesNarcotics;
		basar::Decimal						CashDiscountPercentage;
		basar::VarString					Origin;
		basar::Int32						OriginBranchNo;
		basar::VarString					NextTourId;
		basar::VarString					LastTourId;
		basar::Long64						DialUpOrderNo;
		basar::VarString					DialUpDeviceType;
		basar::VarString					Hint;
		basar::VarString					ParentBranchFlag;
		basar::Long64						BatchOrderNo;
		basar::VarString					SubOrderType;
		basar::VarString					PaymentTerm;
		basar::Int32						ValueMonthManual;
		basar::Int32						ValueMonthAuto;
		basar::Int32						PartialOrder;
		basar::Long64						TenderNo;
		basar::VarString					ContractNo;
		basar::Long64						ShipmentDate;
		basar::Long64						DiscountAccFromDate;
		basar::Long64						DiscountAccToDate;
		basar::VarString					ChainMember;
		basar::VarString					NarcoticsFormNo;
		basar::Long64						ValueDateDays;
		basar::VarString					PrintPriceProposal;
		basar::VarString					DeductionPharmacyPurchasePrice;
		basar::VarString					DeductionPharmacySellPrice;
		basar::VarString					DeductionColumnNo;
		basar::VarString					EmailInvoice;
		basar::Long64						ET5Flags;
		basar::Long64						ET6Flags;
		basar::VarString					XMLReference;
		basar::Int32						PseudoInvoiceNo;
		basar::VarString					MSV3Order;
		basar::Int32						TenderType;
		basar::Int16						NumberOfDiscountRecords;
		basar::VarString					PaymentType;
		basar::Int32                        PurchaseOrderNo;
		basar::VarString					ExpressDeliveryCharge;
        basar::Long64                       ProformaOrderDate;

		OrderHeaderValues()
		{
			init();
		}

		void init()
		{
			Mandant = 0;
			OrderNo = 0;
			CustomerNo = 0;
			UserId = 0;
			BranchNo = 0;
			ET1Flags = 0;
			ET2Flags = 0;
			ET3Flags = 0;
			ET4Flags = 0;
			ValidationDate = 0;
			Lines = 0;
			LinesNoCalc = 0;
			LinesDialUp = 0;
			LinesDialUpErrors = 0;
			LinesAlphaTxt = 0;
			LinesNarcotics = 0;
			OriginBranchNo = 0;
			DialUpOrderNo = 0;
			BatchOrderNo = 0;
			ValueMonthManual = 0;
			ValueMonthAuto = 0;
			PartialOrder = 0;
			TenderNo = 0;
			ShipmentDate = 0;
			DiscountAccFromDate = 0;
			DiscountAccToDate = 0;
			ValueDateDays = 0;
			ET5Flags = 0;
			ET6Flags = 0;
			PseudoInvoiceNo = 0;
			RecordType = "A1";
			ChainMember = "N";
			PrintPriceProposal = "N";
			DeductionPharmacyPurchasePrice = "N";
			DeductionPharmacySellPrice = "N";
			DeductionColumnNo = "0";
			EmailInvoice = "N";
			MSV3Order = "N";
			TenderType = 0;
			NumberOfDiscountRecords = 0;
			PaymentType = " ";
			PurchaseOrderNo = 0;
			ExpressDeliveryCharge = "N";
            ProformaOrderDate = 0;
		}
	};

	namespace OrderHeaderFormat
	{
		static const size_t LENGTH_RECORDTYPE = 2;
		static const size_t LENGTH_MANDANT = 3;
		static const size_t LENGTH_ORDERNO	= 7;
		static const size_t LENGTH_CUSTOMERNO = 7;
		static const size_t LENGTH_TERMINALID = 8;
		static const size_t LENGTH_TOURID = 6;
		static const size_t LENGTH_TOURIDOLD = 6;
		static const size_t LENGTH_USERID = 8;
		static const size_t LENGTH_BRANCHNO = 2;
		static const size_t LENGTH_ET1FLAGS = 8;
		static const size_t LENGTH_ET2FLAGS = 8;
		static const size_t LENGTH_ET3FLAGS = 8;
		static const size_t LENGTH_ET4FLAGS = 8;
		static const size_t LENGTH_ORDERTYPE = 2;
		static const size_t LENGTH_PICKINGTYPE = 1;
		static const size_t LENGTH_BOOKINGTYPE = 1;
		static const size_t LENGTH_VALIDATIONDATE = 8;
		static const size_t LENGTH_ORDERVALUE = 15;
		static const size_t DECPLACES_ORDERVALUE = 4;
		static const size_t LENGTH_DELIVERYVALUE = 15;
		static const size_t DECPLACES_DELIVERYVALUE = 4;
		static const size_t LENGTH_AVGLINEVALUE = 15;
		static const size_t DECPLACES_AVGLINEVALUE = 4;
		static const size_t LENGTH_LINES = 8;
		static const size_t LENGTH_LINESNOCALC = 8;
		static const size_t LENGTH_LINESDIALUP = 8;
		static const size_t LENGTH_LINESDIALUPERRORS = 8;
		static const size_t LENGTH_LINESALPHATXT = 8;
		static const size_t LENGTH_LINESNARCOTICS = 8;
		static const size_t LENGTH_CASHDISCOUNTPERCENTAGE = 15;
		static const size_t DECPLACES_CASHDISCOUNTPERCENTAGE = 4;
		static const size_t LENGTH_ORIGIN = 2;
		static const size_t LENGTH_ORIGINBRANCHNO = 2;
		static const size_t LENGTH_NEXTTOURID = 6;
		static const size_t LENGTH_LASTTOURID = 6;
		static const size_t LENGTH_DIALUPORDERNO = 8;
		static const size_t LENGTH_DIALUPDEVICETYPE = 2;
		static const size_t LENGTH_HINT = 30;
		static const size_t LENGTH_PARENTBRANCHFLAG = 1;
		static const size_t LENGTH_BATCHORDERNO = 5;
		static const size_t LENGTH_SUBORDERTYPE = 3;
		static const size_t LENGTH_PAYMENTTERM = 4;
		static const size_t LENGTH_VALUEMONTHMANUAL = 4;
		static const size_t LENGTH_VALUEMONTHAUTO = 4;
		static const size_t LENGTH_PARTIALORDER = 3;
		static const size_t LENGTH_TENDERNO = 7;
		static const size_t LENGTH_CONTRACTNO = 20;
		static const size_t LENGTH_SHIPMENTDATE = 8;
		static const size_t LENGTH_DISCOUNTACCFROMDATE = 8;
		static const size_t LENGTH_DISCOUNTACCTODATE = 8;
		static const size_t LENGTH_CHAINMEMBER = 1;
		static const size_t LENGTH_NARCOTICSFORMNO = 10;
		static const size_t LENGTH_VALUEDATEDAYS = 3;
		static const size_t LENGTH_PRINTPRICEPROPOSAL = 1;
		static const size_t LENGTH_DEDUCTIONPHARMACYPURCHASEPRICE = 1;
		static const size_t LENGTH_DEDUCTIONPHARMACYSELLPRICE = 1;
		static const size_t LENGTH_DEDUCTIONCOLUMNNO = 1;
		static const size_t LENGTH_EMAILINVOICE = 1;
		static const size_t LENGTH_ET5FLAGS = 8;
		static const size_t LENGTH_ET6FLAGS = 8;
		static const size_t LENGTH_XMLREFERENCE = 9;
		static const size_t LENGTH_PSEUDOINVOICENO = 7;
		static const size_t LENGTH_MSV3ORDER = 1;
		static const size_t LENGTH_TENDERTYPE = 3;
		static const size_t LENGTH_NUMBEROFDISCOUNTRECORDS = 2;
		static const size_t LENGTH_PAYMENTTYPE = 1;
		static const size_t LENGTH_PURCHASEORDERNO = 5;
		static const size_t LENGTH_EXPRESSDELIVERYCHARGE = 1;
        static const size_t LENGTH_PROFORMAORDERDATE = 8;
	}

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEORDERHEADER_DEFINITIONS_H

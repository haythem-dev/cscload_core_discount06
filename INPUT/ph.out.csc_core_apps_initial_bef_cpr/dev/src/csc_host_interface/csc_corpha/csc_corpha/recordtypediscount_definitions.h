//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions for RecordTypeDiscount
 *  \author		Steffen Heinlein
 *  \date		10.09.2014
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEDISCOUNT_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEDISCOUNT_DEFINITIONS_H

#include <libbasarcmnutil.h>

namespace domMod
{
namespace corpha
{
namespace recordtypes
{	
	struct DiscountValues
	{
		basar::VarString					RecordType;
		basar::Int16						BranchNo;
		basar::Long64						PharmosOrderNo;
		basar::Long64						OrderPosNo;
		basar::Int32						DiscountMode;
		basar::Long64						OrderNo;
		basar::Long64						CurrentDate;
		basar::Decimal						Discount;
		basar::Int16						Origin;
		basar::Int16						InternalRebate;	// TODO INTRAB		N1			pxOrderItem::IsNaturalRabattIntern() // muss nach kdauftragposrab!!!
		basar::Decimal						RefundPercent;	// TODO ERSTATT		N5,2		pxOrderItem::PreisEKGrossoNA()  // muss nach kdauftragposrab!!!
		basar::Int16						DiscountBase;	// TODO RABBAS		N1			RABATTBASIS 0 = ALLGEMEINGUELTIG, 1 = EINKAUFSGRUPPE, 2 = IDF, 3 = ERFASST(Z.B.UW)  // muss nach kdauftragposrab!!!
		basar::VarString					PharmacyGroup;	// TODO	EGR			C3			EINKAUFSGRUPPE (RABBAS = 1)  // gibt es schon in kdauftragposrab!!!
		basar::Int16						DiscountCalcFrom; // 0=GEP, 1=AGP, default=0, specifically needed for CH
		basar::Int16						DiscountApplyTo;  // 0=GEP, 1=AGP, default=1, specifically needed for CH
		basar::Int16						DiscountSortBase; // 0=no assorted cash discount, 1 = assorted cash discount, specifically needed for CH

		DiscountValues()
		{
			init();
		}

		void init()
		{
			RecordType = "PR";
			BranchNo = 0;
			PharmosOrderNo = 0;
			OrderPosNo = 0;
			DiscountMode = 0;
			OrderNo = 0;
			CurrentDate = 0;
			Origin = 1;
			InternalRebate = 0;
			DiscountBase = 0;
			PharmacyGroup = "000";
			DiscountCalcFrom = 0;
			DiscountApplyTo = 1;
			DiscountSortBase = 0;
		}
	};

	namespace DiscountFormat
	{				
		static const size_t LENGTH_RECORDTYPE = 2;
		static const size_t LENGTH_BRANCHNO = 2;
		static const size_t LENGTH_PHARMOSORDERNO = 7;
		static const size_t LENGTH_ORDERPOSNO = 7;
		static const size_t LENGTH_DISCOUNTMODE = 5;
		static const size_t LENGTH_ORDERNO = 7;
		static const size_t LENGTH_CURRENTDATE = 7;
		static const size_t LENGTH_DISCOUNT = 15;
		static const size_t DECPLACES_DISCOUNT = 4;
		static const size_t LENGTH_ORIGIN = 1;
		static const size_t LENGTH_INTERNALREBATE = 1;
		static const size_t LENGTH_REFUNDPERCENT = 5;
		static const size_t DECPLACES_REFUNDPERCENT = 2;
		static const size_t LENGTH_DISCOUNTBASE = 1;
		static const size_t LENGTH_PHARMACYGROUP = 3;
		static const size_t LENGTH_DISCOUNTCALCFROM = 1;
		static const size_t LENGTH_DISCOUNTAPPLYTO = 1;
		static const size_t LENGTH_DISCOUNTSORTBASE = 1;
	}
	
} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEDISCOUNT_DEFINITIONS_H

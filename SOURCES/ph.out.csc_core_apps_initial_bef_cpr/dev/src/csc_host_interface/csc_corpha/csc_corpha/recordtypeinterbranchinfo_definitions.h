//----------------------------------------------------------------------------
/*! \file
 *  \brief		definitions for RecordTypeInterBranchInfo
 *  \author		Steffen Heinlein
 *  \date		06.09.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEINTERBRANCHINFO_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEINTERBRANCHINFO_DEFINITIONS_H

namespace domMod
{
namespace corpha
{
namespace recordtypes
{
	struct InterBranchInfoValues
	{
		basar::VarString			RecordType;
		basar::Int32				BranchNo;
		basar::Int32				OriginBranchNo;
		basar::Long64				CustomerNo;
		basar::VarString			PharmacyName;
		basar::VarString			OwnerName;
		basar::VarString			Street;
		basar::Int32				PostalCode;
		basar::VarString			City;
		basar::VarString			PhoneNo;
		basar::Int32				TourId;
		basar::Long64				DecTourId;
		basar::VarString			DialUpPhoneNo;
		basar::VarString			Fax;
		basar::VarString			SalutationId;
		basar::Long64				SalesRepNo;
		basar::Long64				DistrictNo;
		basar::Long64				DistrictNo2;
		basar::VarString			CustomerGroup;
		basar::Int32				WeekdayId;
		basar::VarString			WebShopFlag;
		basar::VarString			Language;
		basar::Int32				OrderChannel;

		InterBranchInfoValues()
		{
			init();
		}

		void init()
		{
			BranchNo = 0;
			OriginBranchNo = 0;
			CustomerNo = 0;
			PostalCode = 0;
			TourId = 0;
			DecTourId = 0;
			SalesRepNo = 0;
			DistrictNo = 0;
			DistrictNo2 = 0;
			WeekdayId = 0;
			OrderChannel = 0;

			RecordType = "SK";
		}
	};

	namespace InterBranchInfoFormat
	{
		static const size_t LENGTH_RECORDTYPE = 2;
		static const size_t LENGTH_BRANCHNO = 2;
		static const size_t LENGTH_ORIGINBRANCHNO = 2;
		static const size_t LENGTH_CUSTOMERNO = 7;
		static const size_t LENGTH_PHARMACYNAME = 30;
		static const size_t LENGTH_OWNERNAME = 30;
		static const size_t LENGTH_STREET = 30;
		static const size_t LENGTH_POSTALCODE = 5;
		static const size_t LENGTH_CITY = 30;
		static const size_t LENGTH_PHONENO = 15;
		static const size_t LENGTH_TOURID = 6;
		static const size_t LENGTH_DECTOURID = 4;
		static const size_t LENGTH_DIALUPPHONENO = 15;
		static const size_t LENGTH_FAX = 15;
		static const size_t LENGTH_SALUTATIONID = 1;
		static const size_t LENGTH_SALESREPNO = 3;
		static const size_t LENGTH_DISTRICTNO = 5;
		static const size_t LENGTH_DISTRICTNO2 = 2;
		static const size_t LENGTH_CUSTOMERGROUP = 2;
		static const size_t LENGTH_WEEKDAYID = 4;
		static const size_t LENGTH_WEBSHOPFLAG = 1;
		static const size_t LENGTH_LANGUAGE = 1;
		static const size_t LENGTH_ORDERCHANNEL = 3;
	}

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_RECORDTYPES_RECORDTYPEINTERBRANCHINFO_DEFINITIONS_H

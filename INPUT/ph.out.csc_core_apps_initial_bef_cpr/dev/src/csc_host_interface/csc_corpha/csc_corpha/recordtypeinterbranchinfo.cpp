//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeInterBranchInfo
 *  \author Steffen Heinlein
 *  \date   04.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include "recordtypeinterbranchinfo.h"
#include "recordtypeformatter.h"
#include "formattingexception.h"

#include <sstream>
#include <iomanip>

using namespace std;

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace recordtypes
{

	//----------------------------------------------------------------------------//
	RecordTypeInterBranchInfo::RecordTypeInterBranchInfo( libcsc_utils::ICSC_LoggerPtr logger )
		: RecordTypeBase( "SK", DIRECTION_SEND, logger )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, RecordTypeInterBranchInfo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.RecordType = getRecordTypeName();
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	RecordTypeInterBranchInfo::~RecordTypeInterBranchInfo()
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, ~RecordTypeInterBranchInfo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setBranchNo( const basar::Int32 branchno )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setBranchNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.BranchNo = branchno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setOriginBranchNo( const basar::Int32 originbranchno )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setOriginBranchNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.OriginBranchNo = originbranchno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setCustomerNo( const basar::Long64& customerno )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setCustomerNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.CustomerNo = customerno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setPharmacyName( const basar::VarString& pharmacyname )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setPharmacyName );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.PharmacyName = pharmacyname;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setOwnerName( const basar::VarString& ownername )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setOwnerName );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.OwnerName = ownername;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setStreet( const basar::VarString& street )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setStreet );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.Street = street;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setPostalCode( const basar::Int32 postalcode )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setPostalCode );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.PostalCode = postalcode;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setCity( const basar::VarString& city )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setCity );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.City = city;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setPhoneNo( const basar::VarString& phoneno )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setPhoneNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.PhoneNo = phoneno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setTourId( const basar::Int32 tourid )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setTourId );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.TourId = tourid;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setDecTourId( const basar::Long64& dectourid )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setDecTourId );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.DecTourId = dectourid;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setDialUpPhoneNo( const basar::VarString& dialupphoneno )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setDialUpPhoneNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.DialUpPhoneNo = dialupphoneno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setFax( const basar::VarString& fax )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setFax );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.Fax = fax;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setSalutationId( const basar::VarString& salutationid )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setSalutationId );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.SalutationId = salutationid;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setSalesRepNo( const basar::Long64& salesrepno )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setSalesRepNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.SalesRepNo = salesrepno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setDistrictNo( const basar::Long64& districtno )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setDistrictNo );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.DistrictNo = districtno;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setDistrictNo2( const basar::Long64& districtno2 )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setDistrictNo2 );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.DistrictNo2 = districtno2;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setCustomerGroup( const basar::VarString& customergroup )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setCustomerGroup );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.CustomerGroup = customergroup;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setWeekdayId( const basar::Int32 weekdayid )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setWeekdayId );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.WeekdayId = weekdayid;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setWebShopFlag( const basar::VarString& webshopflag )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setWebShopFlag );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.WebShopFlag = webshopflag;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setLanguage( const basar::VarString& language )
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, setLanguage );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		m_Values.Language = language;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	void RecordTypeInterBranchInfo::setOrderChannel(const basar::Int32 orderChannel)
	{
		METHODNAME_DEF(RecordTypeInterBranchInfo, setOrderChannel);
		BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

		m_Values.OrderChannel = orderChannel;
	}
	//----------------------------------------------------------------------------//

	//----------------------------------------------------------------------------//
	const basar::VarString RecordTypeInterBranchInfo::doSerialize() const
	{
		METHODNAME_DEF( RecordTypeInterBranchInfo, doSerialize );
		BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

		stringstream ss;

		try
		{
			RecordTypeFormatter::serialize( m_Values.RecordType, InterBranchInfoFormat::LENGTH_RECORDTYPE, ss );
			RecordTypeFormatter::serialize( m_Values.BranchNo, InterBranchInfoFormat::LENGTH_BRANCHNO, ss );
			RecordTypeFormatter::serialize( m_Values.OriginBranchNo, InterBranchInfoFormat::LENGTH_ORIGINBRANCHNO, ss );
			RecordTypeFormatter::serialize( m_Values.CustomerNo, InterBranchInfoFormat::LENGTH_CUSTOMERNO, ss );
			RecordTypeFormatter::serialize( m_Values.PharmacyName, InterBranchInfoFormat::LENGTH_PHARMACYNAME, ss );
			RecordTypeFormatter::serialize( m_Values.OwnerName, InterBranchInfoFormat::LENGTH_OWNERNAME, ss );
			RecordTypeFormatter::serialize( m_Values.Street, InterBranchInfoFormat::LENGTH_STREET, ss );
			RecordTypeFormatter::serialize( m_Values.PostalCode, InterBranchInfoFormat::LENGTH_POSTALCODE, ss );
			RecordTypeFormatter::serialize( m_Values.City, InterBranchInfoFormat::LENGTH_CITY, ss );
			RecordTypeFormatter::serialize( m_Values.PhoneNo, InterBranchInfoFormat::LENGTH_PHONENO, ss );
			RecordTypeFormatter::serialize( m_Values.TourId, InterBranchInfoFormat::LENGTH_TOURID, ss );
			RecordTypeFormatter::serialize( m_Values.DecTourId, InterBranchInfoFormat::LENGTH_DECTOURID, ss );
			RecordTypeFormatter::serialize( m_Values.DialUpPhoneNo, InterBranchInfoFormat::LENGTH_DIALUPPHONENO, ss );
			RecordTypeFormatter::serialize( m_Values.Fax, InterBranchInfoFormat::LENGTH_FAX, ss );
			RecordTypeFormatter::serialize( m_Values.SalutationId, InterBranchInfoFormat::LENGTH_SALUTATIONID, ss );
			RecordTypeFormatter::serialize( m_Values.SalesRepNo, InterBranchInfoFormat::LENGTH_SALESREPNO, ss );
			RecordTypeFormatter::serialize( m_Values.DistrictNo, InterBranchInfoFormat::LENGTH_DISTRICTNO, ss );
			RecordTypeFormatter::serialize( m_Values.DistrictNo2, InterBranchInfoFormat::LENGTH_DISTRICTNO2, ss );
			RecordTypeFormatter::serialize( m_Values.CustomerGroup, InterBranchInfoFormat::LENGTH_CUSTOMERGROUP, ss );
			RecordTypeFormatter::serialize( m_Values.WeekdayId, InterBranchInfoFormat::LENGTH_WEEKDAYID, ss );
			RecordTypeFormatter::serialize( m_Values.WebShopFlag, InterBranchInfoFormat::LENGTH_WEBSHOPFLAG, ss );
			RecordTypeFormatter::serialize( m_Values.Language, InterBranchInfoFormat::LENGTH_LANGUAGE, ss );
			RecordTypeFormatter::serialize( m_Values.OrderChannel, InterBranchInfoFormat::LENGTH_ORDERCHANNEL, ss);
		}
		catch( FormattingException ex )
		{
			throw FormattingException( basar::ExceptInfo( fun, "RecordTypeInterBranchInfo: Formatting exception!", __FILE__, __LINE__ ) );
		}

		return ss.str().c_str();
	}
	//----------------------------------------------------------------------------//

} // namespace recordtypes
} // namespace corpha
} // namespace domMod

	#include "transportexclusionchecker.h"
#include "persistence/iaccessor.h"
#include <sstream>
#include "logger/loggerpool.h"
#include <libbasarcmnutil_datetime.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_datetimetools.h>

namespace libcsc
{
namespace ibt
{

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TransportExclusionChecker::TransportExclusionChecker()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TransportExclusionChecker::~TransportExclusionChecker()
{
	m_SelectAccessor.reset();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TransportExclusionChecker::injectSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_SelectAccessor = accessor;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TransportExclusionChecker::isTransportPossible( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo ) const
{			
	return isTransportPossibleByDeliveryType( branchNo, ibtBranchNo, articleNo );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TransportExclusionChecker::isTransportPossibleForSameDayDelivery( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo ) const
{
	return isTransportPossibleByDeliveryType( branchNo, ibtBranchNo, articleNo, TransportExclusionChecker::SameDayDelivery );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TransportExclusionChecker::isTransportPossibleForOvernightDelivery( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo ) const
{
	return isTransportPossibleByDeliveryType( branchNo, ibtBranchNo, articleNo, TransportExclusionChecker::OverNightDelivery );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TransportExclusionChecker::isTransportPossibleForCustomer( const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::Int32 articleNo ) const
{
	/*
	This method returns false if the customer has no tour with permission to transport the article!
	True is returned if there is at least one tour with permission to transport the article and defined as ibttour.
	*/
	long currentdate = basar::cmnutil::Date::getCurrent().getDate();

	std::stringstream sql;
	sql <<	"SELECT CAST( case count(*) when 0 then 0 else 1 end AS smallint) as deliverable FROM kunde k "
			"LEFT JOIN tourplantag tt on tt.vertriebszentrumnr=k.filialnr and tt.idfnr=k.idfnr "
			"and tt.datumkommi=" << currentdate << " and tt.tourinaktiv='0' and tt.kzautozuord='1' and tt.istverbundtour='1' "
			"LEFT JOIN tourplantagwoche tw on tw.vertriebszentrumnr=k.filialnr and tw.kundennr=k.idfnr and tw.istverbundtour='1' "
			"JOIN artikellokal l on l.filialnr=k.vertriebszentrumnr "
			"JOIN artikelzentral z on z.artikel_nr=l.artikel_nr "
			"WHERE k.idfnr=" << customerNo << " and k.filialnr=" << branchNo << " and l.artikel_nr=" << articleNo << " "
			"and ( "
			"( ( (trunc(l.etartschalter1 / 32) - 2 * trunc(l.etartschalter1 / (32*2)))=1 AND tt.iskk=1 ) "
				"or ( (trunc(l.etartschalter1 / 32) - 2 * trunc(l.etartschalter1 / (32*2)))=1 AND tw.iskk=1 ) ) "
			"or ( ( (trunc(l.etartschalter1 / 128) - 2 * trunc(l.etartschalter1 / (128*2)))=1 AND tt.isk08=1 ) "
				"or ( (trunc(l.etartschalter1 / 128) - 2 * trunc(l.etartschalter1 / (128*2)))=1 AND tw.isk08=1 ) ) "
			"or ( ( (trunc(l.etartschalter1 / 64) - 2 * trunc(l.etartschalter1 / (64*2)))=1 AND tt.isk20=1 ) "
				"or ( (trunc(l.etartschalter1 / 64) - 2 * trunc(l.etartschalter1 / (64*2)))=1 AND tw.isk20=1 ) ) "
			"or ( ( (trunc(z.etartklasse1 / 512) - 2 * trunc(z.etartklasse1 / (512*2)))=1 AND tt.isbtm=1 ) "
				"or ( (trunc(z.etartklasse1 / 512) - 2 * trunc(z.etartklasse1 / (512*2)))=1 AND tw.isbtm=1 ) ) "
			"or ( ( z.kzpsychostoffe in ('J', 'P', 'B', 'C', 'D', 'E', 'F', 'T') and tt.transpexclpsycho = 0 ) "
				"or ( z.kzpsychostoffe in ('J', 'P', 'B', 'C', 'D', 'E', 'F', 'T') and tw.transpexclpsycho = 0 ) ) "
			");";

	basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select( sql.str().c_str() );
	bool transportPossible = true;
	if( true == resultset.next() )
	{		
		if( 0 == resultset.getInt16(0) ) // ==> no tour found with transport permission for this article!!!
		{
			transportPossible = false;
		}		
	}
	return transportPossible;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TransportExclusionChecker::isTransportPossibleByDeliveryType(	const basar::Int16 branchNo, 
																	const basar::Int16 ibtBranchNo, 
																	const basar::Int32 articleNo, 
																	const TransportExclusionChecker::DeliveryType type /* = TransportExclusionChecker::GeneralDelivery */ ) const
{
	/*
	This method returns false if the shuttle customer for the specified delivery type has no tour with permission to transport the article!
	True is returned if there is at least one tour with permission to transport the article from the ibtbranch to the local branch on the same day.
	*/

	basar::VarString remoteDb = this->getRemoteDbIfNecessary( branchNo, ibtBranchNo );
	if( !remoteDb.empty() ){ remoteDb = remoteDb + ":"; }	// If the ibt branch is not on the same database, we have to check the tour information on the database of the ibt branch!
	long currentdate = basar::cmnutil::Date::getCurrent().getDate();

	std::stringstream deliveryTypeCondition;
	switch( type )
	{					
		case OverNightDelivery:
		case SameDayDelivery:
			deliveryTypeCondition << "and i.dayibt= " << (int)type << " ";
			break;
		case GeneralDelivery:
		default:
			deliveryTypeCondition << " ";
			break;
	}
	
	std::stringstream sql;
	sql <<  "SELECT CAST( case count(*) when 0 then 0 else 1 end AS smallint) as deliverable "
			"FROM ibtbranches i "
			"JOIN filiale f on f.filialnr=i.branchno "
			"LEFT JOIN " << remoteDb.c_str() << "tourplantag tt on tt.vertriebszentrumnr=i.ibtbranchno and tt.idfnr=(case i.ibtcustomerno when 0 then f.bganr_ek else i.ibtcustomerno end) "
			"and tt.datumkommi=" << currentdate << " and tt.tourinaktiv='0' and tt.kzautozuord='1' "
			"LEFT JOIN " << remoteDb.c_str() << "tourplantagwoche tw on tw.vertriebszentrumnr=i.ibtbranchno and tw.kundennr=(case i.ibtcustomerno when 0 then f.bganr_ek else i.ibtcustomerno end) "
			"JOIN artikellokal l on l.filialnr=i.branchno "
			"JOIN artikelzentral z on z.artikel_nr=l.artikel_nr "
			"WHERE i.branchno=" << branchNo << " and i.ibtbranchno=" << ibtBranchNo << " and l.artikel_nr=" << articleNo << " " << deliveryTypeCondition.str().c_str() << " "
			"and ( "
			"( ( (trunc(l.etartschalter1 / 32) - 2 * trunc(l.etartschalter1 / (32*2)))=1 AND tt.iskk=1 ) "
				"or ( (trunc(l.etartschalter1 / 32) - 2 * trunc(l.etartschalter1 / (32*2)))=1 AND tw.iskk=1 ) ) "
			"or ( ( (trunc(l.etartschalter1 / 128) - 2 * trunc(l.etartschalter1 / (128*2)))=1 AND tt.isk08=1 ) "
				"or ( (trunc(l.etartschalter1 / 128) - 2 * trunc(l.etartschalter1 / (128*2)))=1 AND tw.isk08=1 ) ) "
			"or ( ( (trunc(l.etartschalter1 / 64) - 2 * trunc(l.etartschalter1 / (64*2)))=1 AND tt.isk20=1 ) "
				"or ( (trunc(l.etartschalter1 / 64) - 2 * trunc(l.etartschalter1 / (64*2)))=1 AND tw.isk20=1 ) ) "
			"or ( ( (trunc(z.etartklasse1 / 512) - 2 * trunc(z.etartklasse1 / (512*2)))=1 AND tt.isbtm=1 ) "
				"or ( (trunc(z.etartklasse1 / 512) - 2 * trunc(z.etartklasse1 / (512*2)))=1 AND tw.isbtm=1 ) ) "
			"or ( ( z.kzpsychostoffe in ('J', 'P', 'B', 'C', 'D', 'E', 'F', 'T') and tt.transpexclpsycho = 0 ) "
				"or ( z.kzpsychostoffe in ('J', 'P', 'B', 'C', 'D', 'E', 'F', 'T') and tw.transpexclpsycho = 0 ) ) "
			");";	

	basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select( sql.str().c_str() );
	bool transportPossible = true;
	if( true == resultset.next() )
	{		
		if( 0 == resultset.getInt16(0) ) // ==> no tour found with transport permission for this article!!!
		{
			transportPossible = false;
		}		
	}
	return transportPossible;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
basar::VarString TransportExclusionChecker::getRemoteDbIfNecessary( const basar::Int16 branchNo, const basar::Int16 ibtBranchNo ) const
{		
	/*
	This method checks if both branches are on the same database.
	If not, it returns the database string (database@informixserver).
	*/
	std::stringstream sql;
	sql <<  "select first 1 ibt.datenbank_name from rechner loc, rechner ibt "
			"where loc.filialnr=" << branchNo << " and loc.datenbank_name!=ibt.datenbank_name and ibt.filialnr=" << ibtBranchNo << ";";	

	basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select( sql.str().c_str() );	

	basar::VarString retval("");
	if( true == resultset.next() )
	{		
		retval = resultset.getString(0);
		retval.trim();
	}

	return retval;
}

} // end namespace ibt
} // end namespace libcsc

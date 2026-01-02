//----------------------------------------------------------------------------
/*! \file
 *  \brief		string builder definition for VSAM.DKBVZ
 *  \author		Steffen Heinlein
 *  \date		22.06.2012
 */
//----------------------------------------------------------------------------

#include "dkbvzacc.h"
#include "property_definitions.h"
#include "columnname_definitions.h"
#include "dkbvzacc_definitions.h"
#include "csc_phatra_table_definitions.h"
#include <loggerpool.h>
#include <iostream>

using std::cout;
using std::endl;

//----------------------------------------------------------------------------

namespace acc_dkbvz
{

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_dkbvz::ACC_DKBVZ)

	BEGIN_PROPERTY_DESCRIPTION_LIST

		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::DX01DATE );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::RECORDOFFSET );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::CSCPROCESSINGSTATUS );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::CSCPROCESSINGTIME );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::DX01PROCESSINGTIME );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::SEQUENCENO );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZFIL );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZPZN );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZMENG );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZBUKZ );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZART );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZTIME );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZDATE );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZLGFNR );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZKSCANR );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZLGNR );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZSTAT );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZET3 );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZWBER );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZVERF );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZP1POS );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZGEP );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZAEP );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZAVP );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZKVERF );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZKLGFNR );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZKGEP );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZKAEP );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZKAVP );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZMFIL );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZSTATUS );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZEXPORT );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZWERT );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZCLOSA );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZCLOZEIT );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZCLOANR );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZCLOPOS );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZCHARGE );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZBATCH );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZTADATUM );
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbvz::KBVZBESLANR );

	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_dkbvz::SELECT_DKBVZ_BY_PATTERN )
		SQL_BUILDER_CREATE(SelectDKBVZByPattern)
		SQL_BUILDER_PUSH_BACK(SelectDKBVZByPattern)

END_ACCESSOR_DEFINITION

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectDKBVZByPattern)

	bool SelectDKBVZByPattern::isExecutable() const
	{
		basar::cmnutil::ParameterList searchValues;
		searchValues.push_back( properties::dkbvz::RECORDOFFSET.getName() );
		searchValues.push_back( properties::dkbvz::CSCPROCESSINGSTATUS.getName() );

		return arePropertiesSet( searchValues );
	}

	void SelectDKBVZByPattern::buildSQLString()
	{
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;

		static const basar::I18nString	stmt(
			"SELECT "
				"  " + columnnames::dkbvz::KBVZ_DX01DATE	+ " AS " + properties::dkbvz::DX01DATE.getName() + " "
				", " + columnnames::dkbvz::KBVZ_OFFSET		+ " AS " + properties::dkbvz::RECORDOFFSET.getName() + " "
				", " + columnnames::dkbvz::KBVZ_KSC			+ " AS " + properties::dkbvz::CSCPROCESSINGSTATUS.getName() + " "
				", " + columnnames::dkbvz::KBVZ_KSCTIME		+ " AS " + properties::dkbvz::CSCPROCESSINGTIME.getName() + " "
				", " + columnnames::dkbvz::KBVZ_DX01TIME	+ " AS " + properties::dkbvz::DX01PROCESSINGTIME.getName() + " "
				", " + columnnames::dkbvz::KBVZ_LFDNR		+ " AS " + properties::dkbvz::SEQUENCENO.getName() + " "
				", " + columnnames::dkbvz::KBVZ_FIL			+ " AS " + properties::dkbvz::KBVZFIL.getName() + " "
				", " + columnnames::dkbvz::KBVZ_PZN			+ " AS " + properties::dkbvz::KBVZPZN.getName() + " "
				", " + columnnames::dkbvz::KBVZ_MENG		+ " AS " + properties::dkbvz::KBVZMENG.getName() + " "
				", " + columnnames::dkbvz::KBVZ_BUKZ		+ " AS " + properties::dkbvz::KBVZBUKZ.getName() + " "
				", " + columnnames::dkbvz::KBVZ_ART			+ " AS " + properties::dkbvz::KBVZART.getName() + " "
				", " + columnnames::dkbvz::KBVZ_TIME		+ " AS " + properties::dkbvz::KBVZTIME.getName() + " "
				", " + columnnames::dkbvz::KBVZ_DATE		+ " AS " + properties::dkbvz::KBVZDATE.getName() + " "
				", " + columnnames::dkbvz::KBVZ_LGFNR		+ " AS " + properties::dkbvz::KBVZLGFNR.getName() + " "
				", " + columnnames::dkbvz::KBVZ_KSCANR		+ " AS " + properties::dkbvz::KBVZKSCANR.getName() + " "
				", " + columnnames::dkbvz::KBVZ_LGNR		+ " AS " + properties::dkbvz::KBVZLGNR.getName() + " "
				", " + columnnames::dkbvz::KBVZ_STAT		+ " AS " + properties::dkbvz::KBVZSTAT.getName() + " "
				", " + columnnames::dkbvz::KBVZ_ET3			+ " AS " + properties::dkbvz::KBVZET3.getName() + " "
				", " + columnnames::dkbvz::KBVZ_WBER		+ " AS " + properties::dkbvz::KBVZWBER.getName() + " "
				", " + columnnames::dkbvz::KBVZ_VERF		+ " AS " + properties::dkbvz::KBVZVERF.getName() + " "
				", " + columnnames::dkbvz::KBVZ_P1POS		+ " AS " + properties::dkbvz::KBVZP1POS.getName() + " "
				", " + columnnames::dkbvz::KBVZ_GEP			+ " AS " + properties::dkbvz::KBVZGEP.getName() + " "
				", " + columnnames::dkbvz::KBVZ_AEP			+ " AS " + properties::dkbvz::KBVZAEP.getName() + " "
				", " + columnnames::dkbvz::KBVZ_AVP			+ " AS " + properties::dkbvz::KBVZAVP.getName() + " "
				", " + columnnames::dkbvz::KBVZ_KVERF		+ " AS " + properties::dkbvz::KBVZKVERF.getName() + " "
				", " + columnnames::dkbvz::KBVZ_KLGFNR		+ " AS " + properties::dkbvz::KBVZKLGFNR.getName() + " "
				", " + columnnames::dkbvz::KBVZ_KGEP 		+ " AS " + properties::dkbvz::KBVZKGEP.getName() + " "
				", " + columnnames::dkbvz::KBVZ_KAEP 		+ " AS " + properties::dkbvz::KBVZKAEP.getName() + " "
				", " + columnnames::dkbvz::KBVZ_KAVP 		+ " AS " + properties::dkbvz::KBVZKAVP.getName() + " "
				", " + columnnames::dkbvz::KBVZ_MFIL 		+ " AS " + properties::dkbvz::KBVZMFIL.getName() + " "
				", " + columnnames::dkbvz::KBVZ_STATUS 		+ " AS " + properties::dkbvz::KBVZSTATUS.getName() + " "
				", " + columnnames::dkbvz::KBVZ_EXPORT 		+ " AS " + properties::dkbvz::KBVZEXPORT.getName() + " "
				", " + columnnames::dkbvz::KBVZ_WERT		+ " AS " + properties::dkbvz::KBVZWERT.getName() + " "
				", " + columnnames::dkbvz::KBVZ_CLO_SA		+ " AS " + properties::dkbvz::KBVZCLOSA.getName() + " "
				", " + columnnames::dkbvz::KBVZ_CLO_ZEIT	+ " AS " + properties::dkbvz::KBVZCLOZEIT.getName() + " "
				", " + columnnames::dkbvz::KBVZ_CLO_ANR		+ " AS " + properties::dkbvz::KBVZCLOANR.getName() + " "
				", " + columnnames::dkbvz::KBVZ_CLO_POS		+ " AS " + properties::dkbvz::KBVZCLOPOS.getName() + " "
				", " + columnnames::dkbvz::KBVZ_CHARGE		+ " AS " + properties::dkbvz::KBVZCHARGE.getName() + " "
				", " + columnnames::dkbvz::KBVZ_BATCH		+ " AS " + properties::dkbvz::KBVZBATCH.getName() + " "
				", " + columnnames::dkbvz::KBVZ_TADATUM		+ " AS " + properties::dkbvz::KBVZTADATUM.getName() + " "
				", " + columnnames::dkbvz::KBVZ_BESLANR		+ " AS " + properties::dkbvz::KBVZBESLANR.getName() + " "
				" FROM " + domMod::TABLE_DKBVZ + " "
				" WHERE " + columnnames::dkbvz::KBVZ_OFFSET + " > " + properties::dkbvz::RECORDOFFSET.toSQLReplacementString() + " "
				" AND " + columnnames::dkbvz::KBVZ_KSC + " = '" + properties::dkbvz::CSCPROCESSINGSTATUS.toSQLReplacementString() + "' "
				" ORDER BY " + columnnames::dkbvz::KBVZ_LFDNR + " ASC; "
				);

		resolve(stmt);

		BLOG_TRACE( logger, getSQLString() );
	}

} // namespace acc_dkbvz

//----------------------------------------------------------------------------

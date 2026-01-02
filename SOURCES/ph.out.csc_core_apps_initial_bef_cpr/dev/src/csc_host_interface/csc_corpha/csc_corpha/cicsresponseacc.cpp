//----------------------------------------------------------------------------
/*! \file		
 *  \brief		string builder definition for VSAM.DKOTR
 *  \author		Steffen Heinlein
 *  \date		24.05.2013
 */
//----------------------------------------------------------------------------

#include "cicsresponseacc.h"
#include "property_definitions.h"
#include "columnname_definitions.h"
#include "cicsresponseacc_definitions.h"
#include "csc_corpha_table_definitions.h"
#include "loggerpool.h"
#include <iostream>
#include <libbasardbaspect.h>

using std::cout;
using std::endl;

//----------------------------------------------------------------------------

namespace acc_dkotr
{ 

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_dkotr::ACC_DKOTR)

	BEGIN_PROPERTY_DESCRIPTION_LIST					
		
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkotr::KSCANR );		
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkotr::LFDNR );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkotr::SA );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkotr::DIRECTION );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkotr::STATUS );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkotr::ZEIT );			
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkotr::BUFFER );			

	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_dkotr::SELECT_DKOTR_BY_PATTERN )	
		SQL_BUILDER_CREATE(SelectDKOTRByPattern)
		SQL_BUILDER_PUSH_BACK(SelectDKOTRByPattern)				

END_ACCESSOR_DEFINITION

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectDKOTRByPattern)

	bool SelectDKOTRByPattern::isExecutable() const
	{   				
		basar::cmnutil::ParameterList searchValues;
		searchValues.push_back( properties::dkotr::KSCANR.getName() );
		searchValues.push_back( properties::dkotr::DIRECTION.getName() );

		return arePropertiesSet( searchValues );		
	}
		
	void SelectDKOTRByPattern::buildSQLString()
	{			
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;
		(void) logger;

		static const basar::I18nString	stmt(
			"SELECT "				
				+ columnnames::dkotr::OTR_KSCANR 		+ " AS " + properties::dkotr::KSCANR.getName()		+ ", "
				+ columnnames::dkotr::OTR_LFDNR 		+ " AS " + properties::dkotr::LFDNR.getName()		+ ", "
				+ columnnames::dkotr::OTR_SA 			+ " AS " + properties::dkotr::SA.getName()			+ ", "
				+ columnnames::dkotr::OTR_DIRECTION 	+ " AS " + properties::dkotr::DIRECTION.getName()	+ ", "
				+ columnnames::dkotr::OTR_STATUS 		+ " AS " + properties::dkotr::STATUS.getName()		+ ", "
				+ columnnames::dkotr::OTR_ZEIT 			+ " AS " + properties::dkotr::ZEIT.getName()		+ ", "
				+ columnnames::dkotr::OTR_BUFFER 		+ " AS " + properties::dkotr::BUFFER.getName()		+ " "
			"FROM "
				+ domMod::TABLE_DKOTR					+ " "
			"WHERE "
				+ columnnames::dkotr::OTR_KSCANR + " = " + properties::dkotr::KSCANR.toSQLReplacementString() + " "
			"ORDER BY "
				+ columnnames::dkotr::OTR_SA			+ ", "
				+ columnnames::dkotr::OTR_LFDNR 		+ " "
			";"
			);

		resolve(stmt);

		BLOG_TRACE( logger, getSQLString() );
	}

} // namespace acc_dkotr

//----------------------------------------------------------------------------
/*! \file
 *  \brief		
 *  \author		Steffen Heinlein
 *  \date		21.06.2012
 */
//----------------------------------------------------------------------------
#include <libbasardbaspect.h>
#include <libbasarproperty.h>
#include "remoteprocedureacc.h"
#include "remoteprocedureacc_definitions.h"
#include "loggerpool.h"


//----------------------------------------------------------------------------
namespace acc_remoteprocedure
{

//---------------------------------------------------------------------------
        
BEGIN_ACCESSOR_DEFINITION( lit::acc_remoteprocedure::ACC_REMOTEPROCEDURE )

	BEGIN_PROPERTY_DESCRIPTION_LIST

		PROPERTY_DESCRIPTION_LIST_ADD( lit::acc_remoteprocedure::REMOTEPROCEDURENAME );
		PROPERTY_DESCRIPTION_LIST_ADD( lit::acc_remoteprocedure::REMOTEPROCEDUREQUERY );
		PROPERTY_DESCRIPTION_LIST_ADD( lit::acc_remoteprocedure::STOREDPROCEDURE );

	END_PROPERTY_DESCRIPTION_LIST
	
	ACCESS_METHOD( lit::acc_remoteprocedure::CALL_REMOTEPROCEDURE )
		SQL_BUILDER_CREATE(CallRemoteProcedure)
		SQL_BUILDER_PUSH_BACK(CallRemoteProcedure)
        
END_ACCESSOR_DEFINITION

//---------------------------------------------------------------------------

BUILDER_DEFINITION(CallRemoteProcedure)

	ENSURE_PROPERTIES_ARE_SET( CallRemoteProcedure, 
		lit::acc_remoteprocedure::REMOTEPROCEDURENAME.toPropertyString() + 
		lit::acc_remoteprocedure::REMOTEPROCEDUREQUERY.toPropertyString() +
		lit::acc_remoteprocedure::STOREDPROCEDURE.toPropertyString()
	)

	void CallRemoteProcedure::buildSQLString()
	{
		using namespace lit::acc_remoteprocedure;
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;

		static const basar::I18nString	statement(
				"CALL STP." + STOREDPROCEDURE.toSQLReplacementString() + "("
				"'" + REMOTEPROCEDURENAME.toSQLReplacementString() + "', "
				"'" + REMOTEPROCEDUREQUERY.toSQLReplacementString() + "'"
				") " 
			);

		resolve( statement );		

		BLOG_TRACE( logger, getSQLString() );
	}
				
//----------------------------------------------------------------------------
} //acc_remoteprocedure


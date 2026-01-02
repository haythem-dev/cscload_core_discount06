//----------------------------------------------------------------------------
/*! \file		
 *  \brief		string builder definition for VSAM.DKBAZP
 *  \author		Julian Machata
 *  \date		22.06.2012
 */
//----------------------------------------------------------------------------

#include "cmndm.h"
#include "dkbazpacc.h"
#include "property_definitions.h"
#include "columnname_definitions.h"
#include "dkbazpacc_definitions.h"
#include "csc_phabor_table_definitions.h"
#include <loggerpool.h>
#include <iostream>

using std::cout;
using std::endl;

//----------------------------------------------------------------------------

namespace acc_dkbazp
{ 

//----------------------------------------------------------------------------
BEGIN_ACCESSOR_DEFINITION(lit::acc_dkbazp::ACC_DKBAZP)

	BEGIN_PROPERTY_DESCRIPTION_LIST

		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::RECORDOFFSET		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPFIL			)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPPOS 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPLFDANR		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPDX05DATE	)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPLFDPOS		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPKSC			)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPPZN			)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPBESMG		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPMGOB 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPUFIL 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPUIDF 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPPTEXT 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPVBSART 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPVBPART2		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPVBPART3 	)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPABVKE 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPKAUFNR 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPKPOSNR		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPVBA 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPNLMG 		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPNULLKZ		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPBATCHNR		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPARTCODE		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPARTTYPE		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZSA    		)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZSALEPRICE	)
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZDISCRATE		)	
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZINVPRICE		)	
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZLINEVAL		)	
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZREBATEVAL	)	
		PROPERTY_DESCRIPTION_LIST_ADD( properties::dkbazp::KBAZPREISNULL	)  

	END_PROPERTY_DESCRIPTION_LIST

	ACCESS_METHOD( lit::acc_dkbazp::SELECT_DKBAZP_BY_PATTERN )
		SQL_BUILDER_CREATE(SelectDKBAZPByPattern)
		SQL_BUILDER_PUSH_BACK(SelectDKBAZPByPattern)
	
END_ACCESSOR_DEFINITION

//----------------------------------------------------------------------------
BUILDER_DEFINITION(SelectDKBAZPByPattern)

	bool SelectDKBAZPByPattern::isExecutable() const
	{   				
		basar::cmnutil::ParameterList searchValues;		
		searchValues.push_back( properties::dkbazp::RECORDOFFSET.getName() );
		searchValues.push_back( properties::dkbazp::KBAZPLFDANR.getName() );		
		
		return arePropertiesSet( searchValues );
	}
		
	void SelectDKBAZPByPattern::buildSQLString()
	{			
		static log4cplus::Logger& logger = libcsc_utils::LoggerPool::LoggerCSC;

		static const basar::I18nString	stmt(
			"SELECT "
				"  " + columnnames::dkbazp::KBAZP_OFFSET	+ " AS " + properties::dkbazp::RECORDOFFSET.getName()	+ " "	
				", " + columnnames::dkbazp::KBAZP_FIL		+ " AS " + properties::dkbazp::KBAZPFIL.getName()		+ " "			
				", " + columnnames::dkbazp::KBAZP_POS		+ " AS " + properties::dkbazp::KBAZPPOS.getName()		+ " "			
				", " + columnnames::dkbazp::KBAZP_LFDANR	+ " AS " + properties::dkbazp::KBAZPLFDANR.getName()	+ " "		
				", " + columnnames::dkbazp::KBAZP_DX50DATE	+ " AS " + properties::dkbazp::KBAZPDX05DATE.getName()	+ " "		
				", " + columnnames::dkbazp::KBAZP_LFDPOS	+ " AS " + properties::dkbazp::KBAZPLFDPOS.getName()	+ " "		
				", " + columnnames::dkbazp::KBAZP_KSC		+ " AS " + properties::dkbazp::KBAZPKSC.getName()		+ " "		
				", " + columnnames::dkbazp::KBAZP_PZN		+ " AS " + properties::dkbazp::KBAZPPZN.getName()		+ " "		
				", " + columnnames::dkbazp::KBAZP_BESMG		+ " AS " + properties::dkbazp::KBAZPBESMG.getName()		+ " "		
				", " + columnnames::dkbazp::KBAZP_MGOB		+ " AS " + properties::dkbazp::KBAZPMGOB.getName()		+ " "		
				", " + columnnames::dkbazp::KBAZP_UFIL		+ " AS " + properties::dkbazp::KBAZPUFIL.getName()		+ " "		
				", " + columnnames::dkbazp::KBAZP_UIDF		+ " AS " + properties::dkbazp::KBAZPUIDF.getName()		+ " "		
				", " + columnnames::dkbazp::KBAZP_PTEXT		+ " AS " + properties::dkbazp::KBAZPPTEXT.getName()		+ " "		
				", " + columnnames::dkbazp::KBAZP_VBSART	+ " AS " + properties::dkbazp::KBAZPVBSART.getName()	+ " "		
				", " + columnnames::dkbazp::KBAZP_VBPART2	+ " AS " + properties::dkbazp::KBAZPVBPART2.getName()	+ " "	
				", " + columnnames::dkbazp::KBAZP_VBPART3	+ " AS " + properties::dkbazp::KBAZPVBPART3.getName()	+ " "	
				", " + columnnames::dkbazp::KBAZP_ABVKE		+ " AS " + properties::dkbazp::KBAZPABVKE.getName()		+ " "		
				", " + columnnames::dkbazp::KBAZP_KAUFNR	+ " AS " + properties::dkbazp::KBAZPKAUFNR.getName()	+ " "			
				", " + columnnames::dkbazp::KBAZP_KPOSNR	+ " AS " + properties::dkbazp::KBAZPKPOSNR.getName()	+ " "		
				", " + columnnames::dkbazp::KBAZP_VBA		+ " AS " + properties::dkbazp::KBAZPVBA.getName()		+ " "			
				", " + columnnames::dkbazp::KBAZP_NLMG		+ " AS " + properties::dkbazp::KBAZPNLMG.getName()		+ " "			
				", " + columnnames::dkbazp::KBAZP_NULLKZ	+ " AS " + properties::dkbazp::KBAZPNULLKZ.getName()	+ " "				
				", " + columnnames::dkbazp::KBAZP_BATCHNR	+ " AS " + properties::dkbazp::KBAZPBATCHNR.getName()	+ " "	
				", " + columnnames::dkbazp::KBAZP_ARTCODE	+ " AS " + properties::dkbazp::KBAZPARTCODE.getName()	+ " "	
				", " + columnnames::dkbazp::KBAZP_ARTTYPE	+ " AS " + properties::dkbazp::KBAZPARTTYPE.getName()	+ " "	
				", " + columnnames::dkbazp::KBAZP_SA    	+ " AS " + properties::dkbazp::KBAZSA.getName()	        + " "	
				", " + columnnames::dkbazp::KBAZP_SALEPRICE	+ " AS " + properties::dkbazp::KBAZSALEPRICE.getName()	        + " "	
				", " + columnnames::dkbazp::KBAZP_DISCRATE 	+ " AS " + properties::dkbazp::KBAZDISCRATE.getName()	        + " "	
				", " + columnnames::dkbazp::KBAZP_INVPRICE 	+ " AS " + properties::dkbazp::KBAZINVPRICE.getName()	        + " "	
				", " + columnnames::dkbazp::KBAZP_LINEVAL 	+ " AS " + properties::dkbazp::KBAZLINEVAL.getName()	        + " "	
				", " + columnnames::dkbazp::KBAZP_REBATEVAL	+ " AS " + properties::dkbazp::KBAZREBATEVAL.getName()	        + " "	
				", " + columnnames::dkbazp::KBAZP_PREISNULL	+ " AS " + properties::dkbazp::KBAZPREISNULL.getName()	        + " "	
				" FROM " + domMod::TABLE_DKBAZP + " "
				" WHERE " + columnnames::dkbazp::KBAZP_OFFSET + " > " + properties::dkbazp::RECORDOFFSET.toSQLReplacementString() + " "
                " AND " + columnnames::dkbazp::KBAZP_LFDANR + " = '" + properties::dkbazp::KBAZPLFDANR.toSQLReplacementString() + "' " 
				" AND " + columnnames::dkbazp::KBAZP_SA + " <> 01 " // \TODO DEFINES FUER SATZARTEN
				" ORDER BY " + columnnames::dkbazp::KBAZP_OFFSET + " ASC "
				";"
				);

		resolve(stmt);

		BLOG_TRACE( logger, getSQLString() );
	}

} // namespace acc_dkbazp

//----------------------------------------------------------------------------

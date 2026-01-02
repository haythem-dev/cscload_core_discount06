#ifndef GUARD_FMDRELEVANTCALCULATOR_DOMMOD_FMDRELEVANTDM_DEFINITIONS_H
#define GUARD_FMDRELEVANTCALCULATOR_DOMMOD_FMDRELEVANTDM_DEFINITIONS_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//--------------------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace domMod
    {
        namespace fmdarticle
        {
			static basar::Int16 FLAG_ON		= 1;
            static basar::Int16 FLAG_OFF	= 0;
        }

		enum FMD_EXCLUSION_RULE_ID
		{
			RULE1	= 1, // A11VERIHOC
			RULE2	= 2, // DC_FAELSCHSICHER
			RULE3	= 3, // BLACKLIST
			RULE4	= 4, // rezeptpfl
			RULE5	= 5, // Arzneimittel
			RULE6	= 6, // WHITELIST
			RULE7	= 7, // Tierznei
			RULE8	= 8, // Homeo
			RULE9	= 9, // med. Gase
			RULE10	= 10 // ATC
		};
    }
}

#endif
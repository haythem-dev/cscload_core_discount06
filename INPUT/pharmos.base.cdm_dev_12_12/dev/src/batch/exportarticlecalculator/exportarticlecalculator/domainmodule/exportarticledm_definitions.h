#ifndef GUARD_EXPORTARTICLECALCULATOR_DOMMOD_EXPORTARTICLEDM_DEFINITIONS_H
#define GUARD_EXPORTARTICLECALCULATOR_DOMMOD_EXPORTARTICLEDM_DEFINITIONS_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//--------------------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
    namespace domMod
    {
        namespace exportarticle
        {
			static basar::Int16 FLAG_ON		= 1;
            static basar::Int16 FLAG_OFF	= 0;
        }

		enum EXPORT_EXCLUSION_RULE_ID
		{
			NARCOTICS			= 1,
			UN_NO				= 2,
			NOTIFIABLE			= 3,
			EXPLOSION			= 4,
			PSYCHOTROPIC		= 5,
			ANIMAL_MEDICINE		= 6,
			ATC_CODE			= 7,
			NARCOTIC_SUBSTANCE	= 8,
			MEDICINE			= 9,
			DISTRIBUTION_RESTR	= 10,
			INTERNAL_ARTICLE	= 11,
			EXPORT_BLOCK		= 12,
			OUTSALE				= 13,
			EXPIRY				= 14,
			BIOZID				= 15,
			ARTICLE_LOCK		= 16,
			STORAGE_LOCATION	= 17,
			ACTIVE_ARTICLE		= 18,
			COOL_ARTICLE		= 19,
			HAZARDOUS_OLD		= 20,
			HAZARDOUS_NEW		= 21,
			DISTRIBUTION_IFA	= 22
		};
    }
}

#endif
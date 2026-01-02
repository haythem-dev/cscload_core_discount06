#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_IRULEDESCRIPTION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_IRULEDESCRIPTION_H

#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// enum class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    class RuleDescription
    {
    public:
        // Attention: This Rule ID doesn't have to be identical with the ruleid key
        // from the database. Use string-compare instead to find the corresponding rule
        enum RuleID
        {
            RULE_COMPOSITE,
            ADMISSION_PURCHASE_PROGNOSIS,
            EXCLUSION_PURCHASE_PROGNOSIS,
            CREATION_DATE,
            WITHOUT_ACTIVE_BINLOCATION,
            NARCOTIC,
            FIX_MAINWAREHOUSE_LISTING,
            CONSIGNMENT,
            DANGEROUS,
            EXPENSIVE,
            BATCH,
            COOL,
            REGISTRABLE,
            BINLOCATIONRANGE,
            SEASONCATEGORY,
            SPECIALARTICLETYPE,
            HAZARDOUSSUBSTANCE,
            BLOCKEDARTICLE,
            OUTOFTRADEARTICLE,
            NATIONALARTICLE,
            CENTRALPURCHASEBLOCKEDARTICLE,
			UNDERDELIVERYQUOTA,
			REGIONALARTICLE,
			ADMISSION_OPTION_ARTRWE,
			ADMISSION_CONSIDER_GROUPS,

            END_OF_ENUM // end marker - neither delete or move
        };

        RuleDescription();
        RuleDescription( basar::Int64 ruleId );

        static RuleDescription fromString( const basar::VarString& );
        const basar::VarString& toString()           const;

        bool isInitialized()                         const;

        bool operator == ( RuleDescription )         const;
        bool operator != ( RuleDescription )         const;

        bool operator == ( RuleDescription::RuleID ) const;
        bool operator != ( RuleDescription::RuleID ) const;

             operator RuleID()                       const; // conversion to enum

    private:
        bool isValid( basar::Int64 ruleId )          const;

        // prevent automatic conversion for any other built-in type such as bool, int ...
        template <typename T>
        operator T() const;

    private:
        RuleID                  m_Rule;
        static basar::VarString m_RuleDescriptionText[ END_OF_ENUM ];
    };

} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_DOMMOD_RELEVANTRULE_IRULEDESCRIPTION_H

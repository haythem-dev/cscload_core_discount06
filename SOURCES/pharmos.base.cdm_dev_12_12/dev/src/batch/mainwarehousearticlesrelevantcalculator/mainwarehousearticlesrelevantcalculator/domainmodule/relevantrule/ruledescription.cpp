#include "ruledescription.h"

#include "exceptions/ruleidoutofboundsexception.h"
#include "exceptions/norulefoundexception.h"

#include <libutil/util.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace domMod
{
namespace relevantRule
{
    basar::VarString RuleDescription::m_RuleDescriptionText[ END_OF_ENUM ] = { 
        "RULE_COMPOSITE",
        "ADMISSION_PURCHASE_PROGNOSIS",
        "EXCLUSION_PURCHASE_PROGNOSIS",
        "CREATION_DATE",
        "WITHOUT_ACTIVE_BINLOCATION",
        "NARCOTIC",
        "FIX_MAINWAREHOUSE_LISTING",
        "CONSIGNMENT",
        "DANGEROUS",
        "EXPENSIVE",
        "BATCH",
        "COOL",
        "REGISTRABLE",
        "BINLOCATIONRANGE",
        "SEASONCATEGORY",
        "SPECIALARTICLETYPE",
        "HAZARDOUSSUBSTANCE",
        "BLOCKEDARTICLE",
        "OUTOFTRADEARTICLE",
        "NATIONALARTICLE",
        "CENTRALPURCHASEBLOCKEDARTICLE",
		"UNDERDELIVERYQUOTA",
		"REGIONALARTICLE",
		"ADMISSION_OPTION_ARTRWE",
		"ADMISSION_CONSIDER_GROUPS",
    };

    RuleDescription::RuleDescription()
        : m_Rule( END_OF_ENUM )
    {
    }

    RuleDescription::RuleDescription( basar::Int64 ruleId )
    {
        METHODNAME_DEF( RuleDescription, RuleDescription );

        if( isValid( ruleId ) )
        {
            m_Rule = static_cast< RuleID >( ruleId );
        }
        else
        {
            throw exceptions::RuleIDOutOfBoundsException( basar::ExceptInfo( fun, "RuleID out of bounds!", __FILE__, __LINE__ ) );
        }
    }

    // static
    RuleDescription RuleDescription::fromString( const basar::VarString& str )
    {
        METHODNAME_DEF( RuleDescription, fromString );

        const basar::VarString* begin = m_RuleDescriptionText;
        const basar::VarString* end   = m_RuleDescriptionText + END_OF_ENUM;

        const basar::VarString* value = std::find( begin, end, str );
        if( value == end )
        {
            throw exceptions::NoRuleFoundException( basar::ExceptInfo( fun, "No rule defined to handle >" + str + "<!", __FILE__, __LINE__ ) );
        }

        return RuleDescription( value - begin );
    }

    const basar::VarString& RuleDescription::toString() const
    {
        METHODNAME_DEF( RuleDescription, toString );

        if( isInitialized() )
        {
            return m_RuleDescriptionText[ m_Rule ];
        }
        else
        {
            throw exceptions::RuleIDOutOfBoundsException( basar::ExceptInfo( fun, "RuleID isn't initialized yet!", __FILE__, __LINE__ ) );
        }
    }

    bool RuleDescription::isInitialized() const
    {
        return isValid( m_Rule );
    }

    bool RuleDescription::operator==( RuleDescription rhs ) const
    {
        return m_Rule == rhs.m_Rule;
    }

    bool RuleDescription::operator!=( RuleDescription rhs ) const
    {
        return m_Rule != rhs.m_Rule;
    }

    bool RuleDescription::operator==( RuleDescription::RuleID rhs ) const
    {
        return m_Rule == rhs;
    }

    bool RuleDescription::operator!=( RuleDescription::RuleID rhs ) const
    {
        return m_Rule != rhs;
    }

    RuleDescription::operator RuleDescription::RuleID() const
    {
        return m_Rule;
    }

    bool RuleDescription::isValid( basar::Int64 ruleId ) const
    {
        return ( 0 <= ruleId && ruleId < END_OF_ENUM );
    }
} // end namespace relevantRule
} // end namespace domMod
} // end namespace mainwarehousearticlesrelevantcalculator

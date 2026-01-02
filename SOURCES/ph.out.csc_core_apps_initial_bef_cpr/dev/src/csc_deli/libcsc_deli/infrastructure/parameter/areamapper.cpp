//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "areamapper.h"

#include <sstream>

#include <misc/metaclassmacro_definitions.h>
#include <exceptions/invaliddataexception.h>

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace infrastructure
{
namespace parameter
{
    //----------------------------------------------------------------------------------------------//
    // static member declaration section
    //----------------------------------------------------------------------------------------------//
    AreaMapper::CountryCodeDict AreaMapper::m_CountryCodes;


    AreaMapper::AreaMapper( AreaID id ) : m_areaID( id )
    {
        setupCountryCodeDictionary();
    }

    AreaMapper::~AreaMapper()
    {
    }

    AreaMapper::AreaID AreaMapper::getId() const
    {
        return m_areaID;
    }

    basar::VarString AreaMapper::toCountryCode() const
    {
        METHODNAME_DEF( AreaMapper, toCountryCode );

        for( CountryCodeDict::const_iterator it = m_CountryCodes.begin(); it != m_CountryCodes.end(); ++it )
        {
            if( it->second == m_areaID )
            {
                return it->first;
            }
        }

        std::stringstream ss; ss << "ERROR: Cannot map area id <" << m_areaID << "> to country code!";
        throw libutil::exceptions::InvalidDataException( basar::ExceptInfo( fun, ss.str(), __FILE__, __LINE__ ) );
    }

    AreaMapper AreaMapper::fromCountryCode( const basar::VarString& countryCode )
    {
        METHODNAME_DEF( AreaMapper, fromCountryCode );
        setupCountryCodeDictionary(); // ensure country code dict is filled appropriatly

        basar::VarString cc = countryCode;
        cc.upper();

        CountryCodeDict::const_iterator it = m_CountryCodes.find( cc );
        if( it != m_CountryCodes.end() )
        {
            return AreaMapper( it->second );
        }

        std::stringstream ss; ss << "ERROR: Cannot map country code <" << countryCode << "> to area id!";
        throw libutil::exceptions::InvalidDataException( basar::ExceptInfo( fun, ss.str(), __FILE__, __LINE__ ) );
    }

    void AreaMapper::setupCountryCodeDictionary()
    {
        if( m_CountryCodes.empty() )
        {
            m_CountryCodes[ "AT"  ] = AUSTRIA;
            m_CountryCodes[ "CH"  ] = SWITZERLAND;
            m_CountryCodes[ "HR"  ] = CROATIA;
            m_CountryCodes[ "FR"  ] = FRANCE;
            m_CountryCodes[ "BG"  ] = BULGARIA;
            m_CountryCodes[ "RS"  ] = SERBIA;
            m_CountryCodes[ "DE"  ] = GERMANY_NORTH;
        }
    }

} // end namespace parameter
} // end namespace infrastructure
} // end namespace libcsc_deli

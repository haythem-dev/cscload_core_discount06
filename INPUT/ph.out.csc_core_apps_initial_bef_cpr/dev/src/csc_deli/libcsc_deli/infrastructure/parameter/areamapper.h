#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_AREAMAPPER_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_AREAMAPPER_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasarcmnutil_bstring.h>
#include <map>

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
    // class declaration section
    //----------------------------------------------------------------------------------------------//
    class AreaMapper
    {
    public:
        // keep in sync with UserAdm values
        enum AreaID
        {
            SWITZERLAND   = 2002,
            AUSTRIA       = 2003,
            CROATIA       = 2004,
            FRANCE        = 2005,
            BULGARIA      = 2008,
            SERBIA        = 2009,
            GERMANY_NORTH = 2100,
            GERMANY_SOUTH = 2200
        };

        explicit AreaMapper( AreaID id );
        ~AreaMapper();

        AreaID            getId() const;

        basar::VarString  toCountryCode() const;
        static AreaMapper fromCountryCode( const basar::VarString& );

    private:
        AreaMapper(); // no default c'tor

        static void setupCountryCodeDictionary();

    private:
        AreaID                                       m_areaID;
        
        typedef std::map< basar::VarString, AreaID > CountryCodeDict;
        static CountryCodeDict                       m_CountryCodes;
    };

} // end namespace parameter
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_AREAMAPPER_H

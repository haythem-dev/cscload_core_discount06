#include "propertyremapper.h"

#include <libbasar_definitions.h>
#include <libbasarcmnutil_i18nstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_decimal.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace dataProvider
{
    PropertyRemapper::PropertyRemapper( IDataProviderPtr dataProvider )
        : m_DataProvider( dataProvider )
    {
    }

    PropertyRemapper::~PropertyRemapper()
    {
    }

    void PropertyRemapper::map( const basar::VarString& from,
                                const basar::VarString& to )
    {
        m_PropertyMap[ from ] = to;
    }

    basar::I18nString PropertyRemapper::getString( const basar::VarString& prop ) const
    {
        return m_DataProvider->getString( getTransformedProperty( prop ) );
    }

    basar::Int32      PropertyRemapper::getInt32 ( const basar::VarString& prop ) const
    {
        return m_DataProvider->getInt32( getTransformedProperty( prop ) );
    }

    basar::Int16      PropertyRemapper::getInt16 ( const basar::VarString& prop ) const
    {
        return m_DataProvider->getInt16( getTransformedProperty( prop ) );
    }

    basar::Date       PropertyRemapper::getDate   ( const basar::VarString& prop ) const
    {
        return m_DataProvider->getDate( getTransformedProperty( prop ) );
    }

    basar::Decimal    PropertyRemapper::getDecimal( const basar::VarString& prop ) const
    {
        return m_DataProvider->getDecimal( getTransformedProperty( prop ) );
    }

    basar::Float64 PropertyRemapper::getFloat64( const basar::VarString& prop ) const
    {
        return m_DataProvider->getFloat64( getTransformedProperty( prop ) );
    }

    bool             PropertyRemapper::hasPropertySet( const basar::VarString& prop ) const
    {
        return m_DataProvider->hasPropertySet( prop );
    }

    const basar::VarString& PropertyRemapper::getTransformedProperty( const basar::VarString& prop ) const
    {
        PropertyMap::const_iterator it = m_PropertyMap.find( prop );
        if( it != m_PropertyMap.end() ) // found
            return it->second;

        return prop;
    }
} // end namespace dataProvider
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

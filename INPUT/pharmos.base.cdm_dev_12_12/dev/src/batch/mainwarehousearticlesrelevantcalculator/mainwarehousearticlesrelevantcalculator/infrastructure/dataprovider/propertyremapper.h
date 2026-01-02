#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_PROPERTYREMAPPER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_PROPERTYREMAPPER_H

#include "idataprovider.h"
#include "idataproviderptr.h"

#include <map>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace dataProvider
{
    /*
        Maps property to another one, e.g. when getString( property::STORAGE_LOCATION ) is called
        and STORAGE_LOCATION is mapped to STORAGE_LOCATION_MAINWH then getString( property::STORAGE_LOCATION )
        returns the value of getString( property::STORAGE_LOCATION_MAINWH )
    */
    class PropertyRemapper : public IDataProvider
    {
    public:
        PropertyRemapper( IDataProviderPtr );
        ~PropertyRemapper();

        void                 map( const basar::VarString& from,
                                  const basar::VarString& to );

        // from IDataProvider interface
        basar::I18nString    getString     ( const basar::VarString& ) const;
        basar::Int32         getInt32      ( const basar::VarString& ) const;
        basar::Int16         getInt16      ( const basar::VarString& ) const;
        basar::Date          getDate       ( const basar::VarString& ) const;
        basar::Decimal       getDecimal    ( const basar::VarString& ) const;
        basar::Float64       getFloat64    ( const basar::VarString& ) const;

        bool                 hasPropertySet( const basar::VarString& ) const;

    private:
        // forbidden
        PropertyRemapper();
        PropertyRemapper( const PropertyRemapper& );
        PropertyRemapper& operator = ( const PropertyRemapper& );

        const basar::VarString& getTransformedProperty( const basar::VarString& ) const;

    private:
        //                       from              to
        typedef std::map< basar::VarString, basar::VarString > PropertyMap;

        IDataProviderPtr                     m_DataProvider;
        PropertyMap                          m_PropertyMap;
    };

} // end namespace dataProvider
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_PROPERTYREMAPPER_H

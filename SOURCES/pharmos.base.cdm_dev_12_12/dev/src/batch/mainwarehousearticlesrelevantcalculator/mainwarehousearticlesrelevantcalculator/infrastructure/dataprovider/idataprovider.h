#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_IDATAPROVIDER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_IDATAPROVIDER_H

#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace property
    {
        class PropertyDescription;
    }
}


//-------------------------------------------------------------------------------------------------//
// interface definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace dataProvider
{
    class IDataProvider
    {
    public:
        virtual ~IDataProvider() {}

        // add further methods if necessary
        virtual basar::I18nString getString  ( const basar::VarString& ) const = 0;
        virtual basar::Int32      getInt32   ( const basar::VarString& ) const = 0;
        virtual basar::Int16      getInt16   ( const basar::VarString& ) const = 0;
        virtual basar::Date       getDate    ( const basar::VarString& ) const = 0;
        virtual basar::Decimal    getDecimal ( const basar::VarString& ) const = 0;
        virtual basar::Float64    getFloat64 ( const basar::VarString& ) const = 0;
        
        virtual bool              hasPropertySet( const basar::VarString& ) const = 0;
    };

} // end namespace dataProvider
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_IDATAPROVIDER_H

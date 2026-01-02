#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_BASARDBASPECTDATAPROVIDER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_BASARDBASPECTDATAPROVIDER_H

#include "idataprovider.h"

#include <libbasardbaspect_accessorpropertytable_yiterator.h>

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
        Adapter class which takes an AccessorPropertyTable_YIterator and provides the
        IDataProvider interface
    */
    class BasarDBAspectDataProvider : public IDataProvider
    {
    public:
        BasarDBAspectDataProvider( basar::db::aspect::AccessorPropertyTable_YIterator );
        ~BasarDBAspectDataProvider();

        // from IDataProvider interface
        basar::I18nString getString  ( const basar::VarString& ) const;
        basar::Int32      getInt32   ( const basar::VarString& ) const;
        basar::Int16      getInt16   ( const basar::VarString& ) const;
        basar::Date       getDate    ( const basar::VarString& ) const;
        basar::Decimal    getDecimal ( const basar::VarString& ) const;
        basar::Float64    getFloat64 ( const basar::VarString& ) const;

        bool              hasPropertySet( const basar::VarString& ) const;

    private:
        // forbidden
        BasarDBAspectDataProvider();

    private:
        basar::db::aspect::AccessorPropertyTable_YIterator m_Yit;
    };

} // end namespace dataProvider
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATAPROVIDER_BASARDBASPECTDATAPROVIDER_H

#include "basardbaspect_dataprovider.h"

#include <libbasarproperty.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace dataProvider
{
    BasarDBAspectDataProvider::BasarDBAspectDataProvider( basar::db::aspect::AccessorPropertyTable_YIterator yit )
        : m_Yit( yit )
    {
    }

    BasarDBAspectDataProvider::~BasarDBAspectDataProvider()
    {
    }

    basar::I18nString BasarDBAspectDataProvider::getString( const basar::VarString& prop ) const
    {
        return m_Yit.getString( prop );
    }

    basar::Int32      BasarDBAspectDataProvider::getInt32 ( const basar::VarString& prop ) const
    {
        return m_Yit.getInt32( prop );
    }

    basar::Int16      BasarDBAspectDataProvider::getInt16 ( const basar::VarString& prop ) const
    {
        return m_Yit.getInt16( prop );
    }

    basar::Date       BasarDBAspectDataProvider::getDate   ( const basar::VarString& prop ) const
    {
        return m_Yit.getDate( prop );
    }

    basar::Decimal    BasarDBAspectDataProvider::getDecimal( const basar::VarString& prop ) const
    {
        return m_Yit.getDecimal( prop );
    }

    basar::Float64    BasarDBAspectDataProvider::getFloat64 ( const basar::VarString& prop ) const
    {
        return m_Yit.getFloat64( prop );
    }

    bool             BasarDBAspectDataProvider::hasPropertySet( const basar::VarString& prop ) const
    {
        return m_Yit.isContainedAndSet( prop );
    }

} // end namespace dataProvider
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#include "trilean.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace dataType
{
    basar::VarString Trilean::ValueString[ 4 ] = {
        "UNKNOWN",
        "FALSE",
        "TRUE",
        "ACG"
    };

    Trilean::Trilean()
        : m_Value( T_UNKNOWN )
    {
    }

    Trilean::Trilean( bool value )
        : m_Value( value ? T_TRUE : T_FALSE )
    {
    }

    Trilean::Trilean( TrileanEnum value )
        : m_Value( value )
    {
    }

    Trilean::operator Trilean::TrileanEnum() const
    {
        return m_Value;
    }

    bool Trilean::operator == ( Trilean rhs ) const
    {
        return m_Value == rhs.m_Value;
    }

    bool Trilean::operator != ( Trilean rhs ) const
    {
        return m_Value != rhs.m_Value;
    }

    bool Trilean::operator == ( Trilean::TrileanEnum rhs ) const
    {
        return m_Value == rhs;
    }

    bool Trilean::operator !=( Trilean::TrileanEnum rhs ) const
    {
        return m_Value != rhs;
    }

    /*
    std::ostream& Trilean::operator << ( std::ostream& os )
    {
        os << toString();
        return os;
    }
    */

    bool Trilean::isUnknown() const
    {
        return m_Value == T_UNKNOWN;
    }

    bool Trilean::isFalse() const
    {
        return m_Value == T_FALSE;
    }

    bool Trilean::isTrue() const
    {
        return m_Value == T_TRUE;
    }

    bool Trilean::isAcg() const
    {
        return m_Value == T_ACG;
    }

    const basar::VarString& Trilean::toString() const
    {
        return ValueString[ m_Value + 1 ];
    }
} // end namespace dataType
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

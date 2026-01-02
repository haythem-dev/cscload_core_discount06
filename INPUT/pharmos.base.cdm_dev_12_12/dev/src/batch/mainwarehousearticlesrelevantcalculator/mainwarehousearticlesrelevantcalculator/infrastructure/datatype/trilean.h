#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATATYPE_TRILEAN_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATATYPE_TRILEAN_H

#include <libbasarcmnutil_bstring.h>
#include <ostream>

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace dataType
{
    class Trilean
    {
    public:

        // Don't change values
        enum TrileanEnum
        {
            T_UNKNOWN = -1,
            T_FALSE   =  0,
            T_TRUE    =  1,
            T_ACG     = 2
        };

    public:
        // c'tors
        Trilean();
        Trilean( bool );                                        // bool to Trilean
        Trilean( TrileanEnum );

                                operator TrileanEnum()  const;  // conversion to enum
        
        bool                    operator == ( Trilean ) const;
        bool                    operator != ( Trilean ) const;

        bool                    operator == ( Trilean::TrileanEnum ) const;
        bool                    operator != ( Trilean::TrileanEnum ) const;

        bool                    isUnknown()             const;
        bool                    isTrue()                const;
        bool                    isFalse()               const;
        bool                    isAcg()                 const;

        const basar::VarString& toString()              const;

    private:
        TrileanEnum             m_Value;
        static basar::VarString ValueString[ 4 ];
    };

    inline std::ostream & operator<<( std::ostream & strm, Trilean value )
    {
        strm << value.toString();
        return strm;
    }

} // end namespace dataType
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTUCTURE_DATATYPE_TRILEAN_H

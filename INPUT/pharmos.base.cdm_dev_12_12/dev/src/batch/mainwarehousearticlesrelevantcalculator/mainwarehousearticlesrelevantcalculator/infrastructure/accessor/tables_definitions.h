//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      Providing table names
 *  \author     Bischof Bjoern
 *  \date       01.03.2011
 *  \version    00.00.00.01 first version
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_ACCESSOR_TABLES_DEFINITIONS_H
#define GUARD_ACCESSOR_TABLES_DEFINITIONS_H

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
    namespace infrastructure
    {
        namespace accessor
        {
            namespace tables
            {
                static const basar::VarString KUNDE                 = "kunde";
                static const basar::VarString KUNDE_SCHALTER        = "kundeschalter";
                static const basar::VarString C_ARTICLE_CODES       = "carticlecodes";
                static const basar::VarString MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_ORDER_HEADER     = "mainwarehousearticlesrelevantcalculatororderheader";
                static const basar::VarString MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_ORDER_POSITION   = "mainwarehousearticlesrelevantcalculatororderposition";
                static const basar::VarString ZARTIKEL              = "zartikel";
            } // end namespace tables
        } // end namespace accessor
    }   // end namespace infrastructure
}   // end namespace mainwarehousearticlesrelevantcalculator
#endif

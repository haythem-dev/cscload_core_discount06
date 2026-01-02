//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Bjoern Bischof
 *  \date       22.12.2010
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_CMDLINE_EXPORTARTICLECALCULATORCMDLINEEVALUATOR_H
#define GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_CMDLINE_EXPORTARTICLECALCULATORCMDLINEEVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

namespace exportarticlecalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class AppArgs
            {
                public:
                    AppArgs()
                    : m_BranchNo( 0 ), m_Country (""), m_DateFrom ( 0 ), m_UserName( "" ), m_Passwd( "" )
                    {
                    }

                    basar::Int16        m_BranchNo;
                    basar::I18nString	m_Country;
					basar::Int32        m_DateFrom;
                    basar::I18nString   m_UserName;
					basar::I18nString   m_Passwd;
            };
        }
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class EXPORTARTICLECALCULATORCmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
                                                    AppArgs, libutil::infrastructure::cmdLine::NullCmdLineOptionCollection>
            {
                public:
                    EXPORTARTICLECALCULATORCmdLineEvaluator();

                private:
                    virtual bool doEvaluate();

                    EXPORTARTICLECALCULATORCmdLineEvaluator( EXPORTARTICLECALCULATORCmdLineEvaluator& );
                    EXPORTARTICLECALCULATORCmdLineEvaluator& operator=( EXPORTARTICLECALCULATORCmdLineEvaluator& );
            };
        }
    }
}

#endif

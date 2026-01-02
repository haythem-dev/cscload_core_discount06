#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_MAINWAREHOUSEARTICLESRELEVANTCALCULATORCMDLINEEVALUATOR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_MAINWAREHOUSEARTICLESRELEVANTCALCULATORCMDLINEEVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>
#include "mainwarehousearticlesrelevantcalculatorcmdlineoptioncollection.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace cmdLine
{
    class AppArgs
    {
        public:
            AppArgs()
            : m_BranchNo( 0 ), m_UserName( "" ), m_Passwd( "" )
            {
            }

            basar::Int16        m_BranchNo;
            basar::I18nString   m_UserName;
            basar::I18nString   m_Passwd;
    };
} // end namespace cmdLine
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace cmdLine
{
    class MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
                                            AppArgs, 
                                            mainwarehousearticlesrelevantcalculator::infrastructure::cmdLine::MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection
                                        >
    {
        public:
            MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator();

        private:
            virtual bool doEvaluate();

            MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator( MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator& );
            MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator& operator=( MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator& );
    };
} // end namespace cmdLine
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_MAINWAREHOUSEARTICLESRELEVANTCALCULATORCMDLINEEVALUATOR_H

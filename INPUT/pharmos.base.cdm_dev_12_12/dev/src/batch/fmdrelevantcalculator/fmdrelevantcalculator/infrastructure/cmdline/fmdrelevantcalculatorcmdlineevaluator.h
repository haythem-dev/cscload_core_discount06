//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Bjoern Bischof
 *  \date       22.12.2010 
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_FMDRELEVANTCALCULATORCMDLINEEVALUATOR_H
#define GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_FMDRELEVANTCALCULATORCMDLINEEVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

namespace fmdrelevantcalculator
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
        }
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class FMDRELEVANTCALCULATORCmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
                                                    AppArgs, libutil::infrastructure::cmdLine::NullCmdLineOptionCollection>
            {
                public:
                    FMDRELEVANTCALCULATORCmdLineEvaluator();

                private:
                    virtual bool doEvaluate();

                    FMDRELEVANTCALCULATORCmdLineEvaluator( FMDRELEVANTCALCULATORCmdLineEvaluator& );
                    FMDRELEVANTCALCULATORCmdLineEvaluator& operator=( FMDRELEVANTCALCULATORCmdLineEvaluator& );
            };
        }
    }
}

#endif

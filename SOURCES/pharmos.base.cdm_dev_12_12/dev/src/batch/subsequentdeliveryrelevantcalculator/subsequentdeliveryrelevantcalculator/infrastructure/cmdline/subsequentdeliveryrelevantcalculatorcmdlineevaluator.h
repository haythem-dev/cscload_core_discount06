//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Michael Helmich
 *  \date       14.10.2022
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_CMDLINEEVALUATOR_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_CMDLINEEVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

namespace subsequentdeliveryrelevantcalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class AppArgs
            {
                public:
                    AppArgs()
                    : m_BranchNo( 0 ), m_AbortType(0), m_AbortArticleNo(0), m_CalcDate(), m_CalcTime()
                    {
                    }

					basar::Int16        m_BranchNo;

                    basar::Int16        m_AbortType;
                    basar::Int32        m_AbortArticleNo;
                    basar::Date         m_CalcDate;
                    basar::Time         m_CalcTime;
            };
        }
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
                                                    AppArgs, libutil::infrastructure::cmdLine::NullCmdLineOptionCollection>
            {
                public:
					SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator();

                private:
                    virtual bool doEvaluate();
                    void ManageDateAndTimeArgs(basar::Date& calcDate, basar::Time& calcTime);

					SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator(SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator& );
					SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator& operator=(SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator& );
            };
        }
    }
}

#endif

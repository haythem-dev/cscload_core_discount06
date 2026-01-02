//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Bjoern Bischof
 *  \date       22.12.2010 
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_CMDLINE_LOADCONTRACTSHRCMDLINEEVALUATOR_H
#define GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_CMDLINE_LOADCONTRACTSHRCMDLINEEVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

namespace loadcontractshr
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class AppArgs
            {
                public:
                    AppArgs()
                    : m_Mode(""), m_Path( "" ), m_UserName( "" ), m_Passwd( "" )
                    {
                    }

					basar::I18nString   m_Mode;
                    basar::I18nString   m_Path;
                    basar::I18nString   m_UserName;
					basar::I18nString   m_Passwd;
            };
        }
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace loadcontractshr
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class LoadContractsHrCmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
                                                    AppArgs, libutil::infrastructure::cmdLine::NullCmdLineOptionCollection>
            {
                public:
                    LoadContractsHrCmdLineEvaluator();

                private:
                    virtual bool doEvaluate();

                    LoadContractsHrCmdLineEvaluator( LoadContractsHrCmdLineEvaluator& );
                    LoadContractsHrCmdLineEvaluator& operator=( LoadContractsHrCmdLineEvaluator& );
            };
        }
    }
}

#endif

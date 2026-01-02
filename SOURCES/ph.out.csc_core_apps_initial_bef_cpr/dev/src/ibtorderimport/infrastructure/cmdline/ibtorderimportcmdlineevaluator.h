//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Bjoern Bischof
 *  \date       22.12.2010
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTORDERIMPORT_INFRASTRUCTURE_CMDLINE_IBTORDERIMPORTCMDLINEEVALUATOR_H
#define GUARD_IBTORDERIMPORT_INFRASTRUCTURE_CMDLINE_IBTORDERIMPORTCMDLINEEVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

namespace ibtorderimport
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
					//basar::I18nString m_LanguageID;
            };
        }
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace ibtorderimport
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class IBTORDERIMPORTCmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
                                                    AppArgs, libutil::infrastructure::cmdLine::NullCmdLineOptionCollection>
            {
                public:
                    IBTORDERIMPORTCmdLineEvaluator();

                private:
                    virtual bool doEvaluate();

                    IBTORDERIMPORTCmdLineEvaluator( IBTORDERIMPORTCmdLineEvaluator& );
                    IBTORDERIMPORTCmdLineEvaluator& operator=( IBTORDERIMPORTCmdLineEvaluator& );
            };
        }
    }
}

#endif

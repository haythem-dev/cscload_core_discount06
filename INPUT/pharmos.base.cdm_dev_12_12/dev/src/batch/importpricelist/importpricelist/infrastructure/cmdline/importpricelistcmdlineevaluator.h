//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Michael Helmich
 *  \date       25.08.2021
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IMPORTPRICELIST_INFRASTRUCTURE_CMDLINE_IMPORTPRICELISTCMDLINEEVALUATOR_H
#define GUARD_IMPORTPRICELIST_INFRASTRUCTURE_CMDLINE_IMPORTPRICELISTCMDLINEEVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

namespace importpricelist
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class AppArgs
            {
                public:
                    AppArgs()
                    : m_InputFile(""), m_BranchNo( 0 ), m_ProcDate(), m_AbortType(0), m_AbortArticleNo(0)
                    {
                    }

					basar::I18nString   m_InputFile;
					basar::Int16        m_BranchNo;
					basar::Date         m_ProcDate;

				    basar::Int16        m_AbortType;
					basar::Int32        m_AbortArticleNo;
			};
        }
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class IMPORTPRICELISTCmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
                                                    AppArgs, libutil::infrastructure::cmdLine::NullCmdLineOptionCollection>
            {
                public:
					IMPORTPRICELISTCmdLineEvaluator();

                private:
                    virtual bool doEvaluate();

					IMPORTPRICELISTCmdLineEvaluator(IMPORTPRICELISTCmdLineEvaluator& );
					IMPORTPRICELISTCmdLineEvaluator& operator=(IMPORTPRICELISTCmdLineEvaluator& );
            };
        }
    }
}

#endif

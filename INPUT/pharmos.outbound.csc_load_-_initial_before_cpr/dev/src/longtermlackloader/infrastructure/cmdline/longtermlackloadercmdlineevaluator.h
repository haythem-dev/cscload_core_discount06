//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Bjoern Bischof
 *  \date       22.12.2010
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_CMDLINE_LONGTERMLACKLOADERCMDLINEEVALUATOR_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_CMDLINE_LONGTERMLACKLOADERCMDLINEEVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>
#include "longtermlackloadercmdlineoptioncollection.h"

namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class AppArgs
            {
				public:
                    AppArgs()
                    : m_AreaID( 0 ), m_UserName(""), m_Passwd("")
                    {
                    }
					basar::Int16     m_AreaID;
                    basar::VarString m_UserName;
                    basar::VarString m_Passwd;
            };
        }
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class LONGTERMLACKLOADERCmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
                                                            AppArgs,
                                                            longtermlackloader::infrastructure::cmdLine::LONGTERMLACKLOADERCmdLineOptionCollection
                                                        >
            {
                public:
                    LONGTERMLACKLOADERCmdLineEvaluator();

                private:
                    virtual bool doEvaluate();

                    LONGTERMLACKLOADERCmdLineEvaluator( LONGTERMLACKLOADERCmdLineEvaluator& );
                    LONGTERMLACKLOADERCmdLineEvaluator& operator=( LONGTERMLACKLOADERCmdLineEvaluator& );
            };
        }
    }
}

#endif

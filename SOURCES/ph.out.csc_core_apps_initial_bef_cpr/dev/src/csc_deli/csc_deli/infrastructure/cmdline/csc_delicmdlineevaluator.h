#ifndef GUARD_CSC_DELI_INFRASTRUCTURE_CMDLINE_CSC_DELICMDLINEEVALUATOR_H
#define GUARD_CSC_DELI_INFRASTRUCTURE_CMDLINE_CSC_DELICMDLINEEVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>
#include "csc_delicmdlineoptioncollection.h"

namespace csc_deli
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class AppArgs
            {
                public:
                    AppArgs()
                    {
                    }

                    basar::I18nString   m_CountryCode;
            };
        }
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace infrastructure
{
namespace cmdLine
{
    class CSC_DELICmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
                                            AppArgs, 
                                            csc_deli::infrastructure::cmdLine::CSC_DELICmdLineOptionCollection
                                        >
    {
        public:
            CSC_DELICmdLineEvaluator();

        private:
            virtual bool doEvaluate();

            CSC_DELICmdLineEvaluator( CSC_DELICmdLineEvaluator& );
            CSC_DELICmdLineEvaluator& operator=( CSC_DELICmdLineEvaluator& );
    };
} // end namespace cmdline
} // end namespace infrastructure
} // end namespace csc_deli

#endif // GUARD_CSC_DELI_INFRASTRUCTURE_CMDLINE_CSC_DELICMDLINEEVALUATOR_H

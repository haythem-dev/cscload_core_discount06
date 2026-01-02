
#include "csc_corphaappinitializerptr.h"
#include "csc_corphaappinitializer.h"
#include "csc_corphacmdlineevaluator.h"

namespace csc_corpha
{
    namespace cmdLine
    {


        CSC_CorphaAppInitializer::CSC_CorphaAppInitializer()
        {
        }

        CSC_CorphaAppInitializer::~CSC_CorphaAppInitializer()
        {
        }

        void CSC_CorphaAppInitializer::doHandleAppConfiguration( libcsc_utils::ApplXMLConfigWrapper* config )
        {
			config->setOrderFilter( m_CSC_CmdLineOptions->getOrderFilter() );
        }	
    }
}
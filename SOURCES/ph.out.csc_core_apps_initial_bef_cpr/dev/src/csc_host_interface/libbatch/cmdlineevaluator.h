//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       22.12.2010
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBBATCH_CMD_LINE_EVALUATOR_H
#define GUARD_LIBBATCH_CMD_LINE_EVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <libbasarcmnutil.h>
#include <vector>
#include "cmdlineparser.h"
#include "cmdlineconfiguration.h"

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace libBatch 
{
    namespace cmdLine
    {
        class CmdLineParser;
    }
}

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace libBatch 
{
namespace cmdLine
{
    class CmdLineEvaluator
    {
        public:
            virtual ~CmdLineEvaluator();
            bool isOptionSet() const;
            const basar::VarString& getOption() const;
            void evaluate();

        protected:
            CmdLineEvaluator( const CmdLineConfiguration& );

        private:
            typedef std::vector<basar::VarString> OptionsCollector;

            virtual bool evaluateAppArgs() = 0; 

            bool             checkNumberParameters()                            const;
            basar::VarString checkCmdLineOptions  ()                            const;
            void                   loadOptions          ( OptionsCollector& options ) const;

            CmdLineEvaluator          ( CmdLineEvaluator& );
            CmdLineEvaluator& operator=( CmdLineEvaluator& );

        /////////////////////////////////////////////////////////////////////
        // members
        /////////////////////////////////////////////////////////////////////
        protected:
            const libBatch::cmdLine::CmdLineParser  m_CmdLineParser;

        private:
            ////////////////////////////////
            // variables
            ////////////////////////////////
            const log4cplus::Logger&                m_Logger;
            basar::VarString                        m_OptionPassed;
    };
} // end namespace cmdLine
} // end namespace libBatch

#endif // end GUARD_LIBBATCH_CMD_LINE_EVALUATOR_H

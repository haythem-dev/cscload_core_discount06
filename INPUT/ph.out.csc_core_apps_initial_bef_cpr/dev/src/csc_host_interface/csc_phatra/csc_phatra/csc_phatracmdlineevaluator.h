//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       24.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHATRA_CMDLINE_COMMAND_LINE_EVALUATOR_H
#define GUARD_CSC_PHATRA_CMDLINE_COMMAND_LINE_EVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <cmdlineevaluator.h>
#include "appargs.h"

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra
{
namespace cmdLine
{

	class CSC_PhatraCmdLineEvaluator : public ::libBatch::cmdLine::CmdLineEvaluator
{
public:
    CSC_PhatraCmdLineEvaluator( const ::libBatch::cmdLine::CmdLineConfiguration& );
    ~CSC_PhatraCmdLineEvaluator();

    //const AppArgs& getAppArgs() const;

	basar::Int16		getBranchNo() const;
	basar::VarString	getConfigFile() const;
	basar::VarString  getApplicationName() const;
    bool              isTestingSet() const;
    bool              isNoMailSet() const;
    bool              isExtendedLoggingSet() const;


private:
    CSC_PhatraCmdLineEvaluator( CSC_PhatraCmdLineEvaluator& );
    CSC_PhatraCmdLineEvaluator& operator=( CSC_PhatraCmdLineEvaluator& );

    virtual bool      evaluateAppArgs                 ();

    void					readInBranchNo                  ();
	void					readInConfigFile				();
    void                    readInTesting                   ();
    void                    readInNoMail                    ();
    void                    readInExtendedLogging           ();
    
	AppArgs                 m_AppArgs;
};

} // end namespace cmdLine
} // end namespace csc_phatra

#endif // end GUARD_CSC_PHATRA_COMMAND_LINE_EVALUATOR_H


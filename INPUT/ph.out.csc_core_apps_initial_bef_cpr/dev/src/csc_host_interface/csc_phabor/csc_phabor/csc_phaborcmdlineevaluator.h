//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       24.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHABOR_CMDLINE_COMMAND_LINE_EVALUATOR_H
#define GUARD_CSC_PHABOR_CMDLINE_COMMAND_LINE_EVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <cmdlineevaluator.h>
#include "appargs.h"

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor
{
namespace cmdLine
{

	class CSC_PhaborCmdLineEvaluator : public ::libBatch::cmdLine::CmdLineEvaluator
{
public:
    CSC_PhaborCmdLineEvaluator( const ::libBatch::cmdLine::CmdLineConfiguration& );
    ~CSC_PhaborCmdLineEvaluator();

    //const AppArgs& getAppArgs() const;

	basar::Int16			getBranchNo() const;
	basar::VarString		getConfigFile() const;
	basar::VarString  		getApplicationName() const;
	bool              		isTestingSet() const;
    bool              		isNoMailSet() const;
	bool					isOnlyOddOrderNumbersSet() const;
	bool					isOnlyEvenOrderNumbersSet() const;
	bool              		isExtendedLoggingSet() const;
	bool					isTransferSet() const;
	bool					isProcessSet() const;

private:
    CSC_PhaborCmdLineEvaluator( CSC_PhaborCmdLineEvaluator& );
    CSC_PhaborCmdLineEvaluator& operator=( CSC_PhaborCmdLineEvaluator& );

    virtual bool      		evaluateAppArgs                 ();

    void                    readInCountryCode               ();
    void					readInBranchNo                  ();
	void					readInConfigFile				();
	void                    readInTesting                   ();
    void                    readInNoMail                    ();
	void                    readInExtendedLogging           ();
	void                    readInProcessFlag               ();
	void                    readInTransferFlag	            ();
    
	AppArgs                 m_AppArgs;
};

} // end namespace cmdLine
} // end namespace csc_phabor

#endif // end GUARD_CSC_PHABOR_COMMAND_LINE_EVALUATOR_H

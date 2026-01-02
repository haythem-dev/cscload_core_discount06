//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       24.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_CORPHA_CMDLINE_COMMAND_LINE_EVALUATOR_H
#define GUARD_CSC_CORPHA_CMDLINE_COMMAND_LINE_EVALUATOR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <cmdlineevaluator.h>
#include "appargs.h"

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_corpha
{
namespace cmdLine
{

class CSC_CorphaCmdLineEvaluator : public ::libBatch::cmdLine::CmdLineEvaluator
{
public:
    CSC_CorphaCmdLineEvaluator( const ::libBatch::cmdLine::CmdLineConfiguration& );
    ~CSC_CorphaCmdLineEvaluator();    

private:
    CSC_CorphaCmdLineEvaluator( CSC_CorphaCmdLineEvaluator& );
    CSC_CorphaCmdLineEvaluator& operator=( CSC_CorphaCmdLineEvaluator& );

public:
	basar::Int16		getBranchNo() const;
	basar::VarString	getConfigFile() const;
	basar::VarString  getOrderFilter() const;
	bool				getTestingMode() const;
	bool				getNoMail() const;
	bool				getExtendedLogging() const;
	basar::VarString  getApplicationName() const;
	bool				isTestingSet() const;
	bool				isNoMailSet() const;	
	bool				isExtendedLoggingSet() const;

private:
    virtual bool      evaluateAppArgs                 ();
    void                    readInCountryCode               ();
    void					readInBranchNo                  ();
	void					readInConfigFile				();
	void					readInTesting					();
	void					readInNoMail					();
	void					readInOrderFilter				();
	void					readInExtendedLogging			();
    
	AppArgs                 m_AppArgs;
};

} // end namespace cmdLine
} // end namespace csc_corpha

#endif // end GUARD_CSC_CORPHA_CMDLINE_COMMAND_LINE_EVALUATOR_H

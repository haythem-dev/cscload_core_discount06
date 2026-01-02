//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       22.12.2010
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "cmndm.h"
#include "csc_phaborcmdlineevaluator.h"
#include "csc_phabor_definitions.h"
#include "csc_phaborcmdlineoption_definitions.h"

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor
{
	namespace cmdLine
	{

		CSC_PhaborCmdLineEvaluator::CSC_PhaborCmdLineEvaluator( const ::libBatch::cmdLine::CmdLineConfiguration& cmdLineConfiguration )
		: ::libBatch::cmdLine::CmdLineEvaluator( cmdLineConfiguration )
		{
		}

		CSC_PhaborCmdLineEvaluator::~CSC_PhaborCmdLineEvaluator()
		{
		}

		basar::Int16	CSC_PhaborCmdLineEvaluator::getBranchNo() const
		{
			return m_AppArgs.m_BranchNo;
		}

		basar::VarString	CSC_PhaborCmdLineEvaluator::getConfigFile() const 
		{
			return m_AppArgs.m_ConfigFile;
		}

		basar::VarString CSC_PhaborCmdLineEvaluator::getApplicationName() const
		{
			return csc_phabor::APPLICATION_NAME;
		}

		bool CSC_PhaborCmdLineEvaluator::evaluateAppArgs()
		{
			readInBranchNo();
			readInConfigFile();
			readInProcessFlag();
			readInTransferFlag();
			readInTesting();
			readInNoMail();
		    
			bool argsValid = m_AppArgs.isBranchNoValid();

			return argsValid; 
		}

		void CSC_PhaborCmdLineEvaluator::readInBranchNo()
		{
			m_CmdLineParser.getMandatoryInt16( cmdLine::BRANCHNO, m_AppArgs.m_BranchNo );
		}

		void CSC_PhaborCmdLineEvaluator::readInConfigFile()
		{
			m_CmdLineParser.getMandatoryVarString( cmdLine::CONFIGFILE, m_AppArgs.m_ConfigFile );
		}

		void CSC_PhaborCmdLineEvaluator::readInTesting()
		{
			m_AppArgs.m_Testing = m_CmdLineParser.isParam( cmdLine::TESTING );
		}

		void CSC_PhaborCmdLineEvaluator::readInNoMail()
		{
			m_AppArgs.m_NoMail = m_CmdLineParser.isParam( cmdLine::NOMAIL );
		}

		void CSC_PhaborCmdLineEvaluator::readInProcessFlag()
		{
			m_AppArgs.m_Process = m_CmdLineParser.isParam( cmdLine::PROCESS );
		}

		void CSC_PhaborCmdLineEvaluator::readInTransferFlag()
		{
			 m_AppArgs.m_Transfer = m_CmdLineParser.isParam( cmdLine::TRANSFER );
		}

		void CSC_PhaborCmdLineEvaluator::readInExtendedLogging()
        {
            m_AppArgs.m_ExtendedLogging = m_CmdLineParser.isParam( cmdLine::EXTENDED_LOGGING );
        }

		bool CSC_PhaborCmdLineEvaluator::isTestingSet() const
		{
            return m_AppArgs.m_Testing;
        }

		bool CSC_PhaborCmdLineEvaluator::isNoMailSet() const
		{
            return m_AppArgs.m_NoMail;
        }

		bool CSC_PhaborCmdLineEvaluator::isOnlyEvenOrderNumbersSet() const
        {
            return false;
        }

        bool CSC_PhaborCmdLineEvaluator::isOnlyOddOrderNumbersSet() const
        {
            return false;
        }

		bool CSC_PhaborCmdLineEvaluator::isExtendedLoggingSet() const
        {
            return m_AppArgs.m_ExtendedLogging;
        }

		bool CSC_PhaborCmdLineEvaluator::isTransferSet() const
		{
			return m_AppArgs.m_Transfer;
		}

		bool CSC_PhaborCmdLineEvaluator::isProcessSet() const
		{
			return m_AppArgs.m_Process;
		}

	} // end namespace cmdLine
} // end namespace csc_phabor

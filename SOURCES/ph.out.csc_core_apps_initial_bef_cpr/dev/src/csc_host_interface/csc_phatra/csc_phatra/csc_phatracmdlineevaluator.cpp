//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       22.12.2010
 *  \version    00.00.00.01
 */ //--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "csc_phatracmdlineevaluator.h"
#include "csc_phatra_definitions.h"
#include "csc_phatracmdlineoption_definitions.h"

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra
{
	namespace cmdLine
	{

		CSC_PhatraCmdLineEvaluator::CSC_PhatraCmdLineEvaluator( const ::libBatch::cmdLine::CmdLineConfiguration& cmdLineConfiguration )
		: ::libBatch::cmdLine::CmdLineEvaluator( cmdLineConfiguration )
		{
		}

		CSC_PhatraCmdLineEvaluator::~CSC_PhatraCmdLineEvaluator()
		{
		}

		basar::Int16	CSC_PhatraCmdLineEvaluator::getBranchNo() const
		{
			return m_AppArgs.m_BranchNo;
		}

		basar::VarString	CSC_PhatraCmdLineEvaluator::getConfigFile() const 
		{
			return m_AppArgs.m_ConfigFile;
		}

		basar::VarString CSC_PhatraCmdLineEvaluator::getApplicationName() const
		{
			return csc_phatra::APPLICATION_NAME;
		}

        bool CSC_PhatraCmdLineEvaluator::isNoMailSet() const
        {
            return m_AppArgs.m_NoMail;
        }

        bool CSC_PhatraCmdLineEvaluator::isTestingSet() const
        {
            return m_AppArgs.m_Testing;
        }

        bool CSC_PhatraCmdLineEvaluator::isExtendedLoggingSet() const
        {
            return m_AppArgs.m_ExtendedLogging;
        }

		bool CSC_PhatraCmdLineEvaluator::evaluateAppArgs()
		{
			readInBranchNo();
			readInConfigFile();
            readInTesting();
            readInNoMail();
		    
			bool argsValid = m_AppArgs.isBranchNoValid();
			argsValid &= m_AppArgs.isConfigFileValid();

			return argsValid; 
		}

        void CSC_PhatraCmdLineEvaluator::readInTesting()
        {
            m_AppArgs.m_Testing = m_CmdLineParser.isParam( cmdLine::TESTING );
        }

        void CSC_PhatraCmdLineEvaluator::readInNoMail()
        {
            m_AppArgs.m_NoMail = m_CmdLineParser.isParam( cmdLine::NO_MAIL );
        }

        void CSC_PhatraCmdLineEvaluator::readInExtendedLogging()
        {
            m_AppArgs.m_ExtendedLogging = m_CmdLineParser.isParam( cmdLine::EXTENDED_LOGGING );
        }

		void CSC_PhatraCmdLineEvaluator::readInBranchNo()
		{
			m_CmdLineParser.getMandatoryInt16( cmdLine::BRANCHNO, m_AppArgs.m_BranchNo );
		}

		void CSC_PhatraCmdLineEvaluator::readInConfigFile()
		{
			m_CmdLineParser.getMandatoryVarString( cmdLine::CONFIGFILE, m_AppArgs.m_ConfigFile );
		}

	} // end namespace cmdLine
} // end namespace csc_phatra

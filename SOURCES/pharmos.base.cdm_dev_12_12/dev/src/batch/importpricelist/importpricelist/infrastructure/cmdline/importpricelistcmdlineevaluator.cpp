//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Michael Helmich
 *  \date       25.08.2021
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

#include "importpricelistcmdlineevaluator.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            IMPORTPRICELISTCmdLineEvaluator::IMPORTPRICELISTCmdLineEvaluator()
            {
            }

            bool IMPORTPRICELISTCmdLineEvaluator::doEvaluate()
            {
                AppArgs& appArgs = getAppArgs();
				basar::VarString tmpVal;

				getCmdLineParser()->getMandatoryInt16    ( "-branchno",   appArgs.m_BranchNo );
				getCmdLineParser()->getMandatoryVarString( "-inputfile",  appArgs.m_InputFile );
				// get value for parameter procdate as a string at first
				/* we don't read the value directly as a date, because for some invalid date values
				   CmdLineParser::getDate() returns false, for others true and the Date object 
				   is set to invalid */
				appArgs.m_ProcDate = basar::Date::getCurrent(); // default value for procdate is current date
				if (getCmdLineParser()->getVarString("-procdate", tmpVal))
				{
					// try to convert procdate value to date
					basar::Date tmpDate;
					try
					{
						basar::Int32 intVal = tmpVal.stoi();
						tmpDate = basar::Date(intVal);
					}
					catch (...)
					{
						// on conversion error set date to invalid 
						/* not all conversion errors are reported as an execption,
						   some simply set the date to invalid */
						tmpDate.setInvalid();
					}
					// throw CmdLineException if entered date is not valid
					if (!tmpDate.isValid())
					{
						basar::ExceptInfo sInfo("importpricelist::infrastructure::cmdLine::IMPORTPRICELISTCmdLineEvaluator::doEvaluate",
							"ERROR: invalid date value specified for parameter <-procdate>",
							__FILE__, __LINE__);
						throw libutil::exceptions::CmdLineException(sInfo);
					}
					else
					{
						appArgs.m_ProcDate = tmpDate;
					}
				}

#ifdef ABORTTEST
				if (getCmdLineParser()->getVarString("-abort", tmpVal))
				{
					size_t posColon = tmpVal.find(':');
					if (posColon != std::string::npos)
					{
						basar::VarString strAbortType(tmpVal.substr(0, posColon));
						basar::VarString strAbortArticleNo(tmpVal.substr(posColon + 1));

						try
						{
							basar::Int16 abortType = (basar::Int16) strAbortType.stoi();
							basar::Int32 abortArticleNo = strAbortArticleNo.stoi();

							appArgs.m_AbortType = abortType;
							appArgs.m_AbortArticleNo = abortArticleNo;
						}
						catch (...)
						{
						}
					}
					if (! (appArgs.m_AbortType == 1 || appArgs.m_AbortType == 2))
					{
						basar::ExceptInfo sInfo("importpricelist::infrastructure::cmdLine::IMPORTPRICELISTCmdLineEvaluator::doEvaluate",
							"ERROR: invalid abortType value specified with parameter <-abort>",
							__FILE__, __LINE__);
						throw libutil::exceptions::CmdLineException(sInfo);
					}
					if (appArgs.m_AbortArticleNo == 0)
					{
						basar::ExceptInfo sInfo("importpricelist::infrastructure::cmdLine::IMPORTPRICELISTCmdLineEvaluator::doEvaluate",
							"ERROR: invalid abortArticleNo value specified with parameter <-abort>",
							__FILE__, __LINE__);
						throw libutil::exceptions::CmdLineException(sInfo);
					}
				}
#endif

                return true;
            }
        } // end namespace cmdLine
    } // end namespace infrastructure
} // end namespace ibtrelevantcalculator

//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Michael Helmich
 *  \date       14.10.2022
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

#include "subsequentdeliveryrelevantcalculatorcmdlineevaluator.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator()
            {
            }

            bool SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator::doEvaluate()
            {
                AppArgs& appArgs = getAppArgs();
				basar::VarString tmpVal;

				getCmdLineParser()->getMandatoryInt16    ( "-branchno",   appArgs.m_BranchNo );

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
						basar::ExceptInfo sInfo("subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator::doEvaluate",
							"ERROR: invalid abortType value specified with parameter <-abort>",
							__FILE__, __LINE__);
						throw libutil::exceptions::CmdLineException(sInfo);
					}
					if (appArgs.m_AbortArticleNo == 0)
					{
						basar::ExceptInfo sInfo("subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator::doEvaluate",
							"ERROR: invalid abortArticleNo value specified with parameter <-abort>",
							__FILE__, __LINE__);
						throw libutil::exceptions::CmdLineException(sInfo);
					}
				}
#endif
                basar::Date calcDate;
                basar::Time calcTime;
                ManageDateAndTimeArgs(calcDate, calcTime);

                appArgs.m_CalcDate = calcDate;
                appArgs.m_CalcTime = calcTime;

                return true;
            }

            void SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator::ManageDateAndTimeArgs(basar::Date& calcDate, 
                basar::Time& calcTime)
            {
                basar::VarString tmpDate;
                basar::VarString tmpTime;
                bool hasCalcDate = getCmdLineParser()->getVarString("-calcDate", tmpDate);
                bool hasCalcTime = getCmdLineParser()->getVarString("-calcTime", tmpTime);

                if (hasCalcDate && hasCalcTime)
                {
                    // try to convert calcDate value
                    bool validDate = true;
                    bool validTime = true;
                    try
                    {
                        basar::Int32 intValDate = tmpDate.stoi();
                        calcDate = basar::Date(intValDate);
                    }
                    catch (...)
                    {
                        basar::ExceptInfo sInfo("subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator::doEvaluate",
                            "WARNING: invalid -calcDate format YYYYMMDD");
                        validDate = false;
                    }

                    // try to convert calcTime value
                    try
                    {
                        basar::Int32 intValDate = tmpDate.stoi();
                        basar::Int32 intValTime = tmpTime.stoi();
                        calcTime = basar::Time(intValDate, intValTime);
                    }
                    catch (...)
                    {
                        basar::ExceptInfo sInfo("subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator::doEvaluate",
                            "WARNING: invalid -CalcTime format hhmmssttt");
                        validTime = false;
                    }

                    //invalid time format or date format => Get current time
                    if (!validTime || !validDate)
                    {
                        calcDate = basar::Date::getCurrent();
                        calcTime = basar::Time::getCurrent();
                    }
                }
                else
                {
                    calcDate = basar::Date::getCurrent();
                    calcTime = basar::Time::getCurrent();

                    if (hasCalcDate && !hasCalcTime)
                    {
                        basar::ExceptInfo sInfo("subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator::doEvaluate",
                            "WARNING: Parameter -calcDate is ignored because -calcTime is not provided",
                            __FILE__, __LINE__);
                    }
                    else if (!hasCalcDate && hasCalcTime)
                    {
                        basar::ExceptInfo sInfo("subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator::doEvaluate",
                            "WARNING: Parameter -calcTime is ignored because -calcDate is not provided",
                            __FILE__, __LINE__);
                    }
                }                
            }
        } // end namespace cmdLine
    } // end namespace infrastructure
} // end namespace ibtrelevantcalculator

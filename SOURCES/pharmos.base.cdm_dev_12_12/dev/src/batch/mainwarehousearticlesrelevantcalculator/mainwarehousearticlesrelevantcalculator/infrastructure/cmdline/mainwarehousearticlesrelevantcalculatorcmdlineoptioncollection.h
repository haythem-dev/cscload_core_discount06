#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_MAINWAREHOUSEARTICLESRELEVANTCALCULATORCMDLINEOPTIONCOLLECTION_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_MAINWAREHOUSEARTICLESRELEVANTCALCULATORCMDLINEOPTIONCOLLECTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace cmdLine
{
    //--------------------------------------------------------------------------------------------------//
    // class declaration section
    //--------------------------------------------------------------------------------------------------//
    class MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection : public libutil::infrastructure::cmdLine::CmdLineOptionCollectionBase
    {
        public:
            MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection();
            virtual ~MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection();

        protected:
            virtual basar::VarString getUsageText() const;
            virtual basar::VarString getVersionText() const;
            virtual basar::VarString getHelpText() const;
            virtual basar::VarString getVersionHistorieText() const;
            virtual basar::VarString getReturnValuesText() const;

        private:
            ////////////////////////////////
            // methods
            ////////////////////////////////
            MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection( const MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection& );
            MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection& operator=( const MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection& );
    };
} // end namespace cmdLine
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif

#ifndef GUARD_CSC_DELI_INFRASTRUCTURE_CMDLINE_CSC_DELICMDLINEOPTIONCOLLECTION_H
#define GUARD_CSC_DELI_INFRASTRUCTURE_CMDLINE_CSC_DELICMDLINEOPTIONCOLLECTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace infrastructure
{
namespace cmdLine
{
    //--------------------------------------------------------------------------------------------------//
    // class declaration section
    //--------------------------------------------------------------------------------------------------//
    class CSC_DELICmdLineOptionCollection : public libutil::infrastructure::cmdLine::CmdLineOptionCollectionBase
    {
        public:
            CSC_DELICmdLineOptionCollection();
            virtual ~CSC_DELICmdLineOptionCollection();

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
            CSC_DELICmdLineOptionCollection( const CSC_DELICmdLineOptionCollection& );
            CSC_DELICmdLineOptionCollection& operator=( const CSC_DELICmdLineOptionCollection& );
    };
} // end namespace cmdLine
} // end namespace infrastructure
} // end namespace csc_deli

#endif

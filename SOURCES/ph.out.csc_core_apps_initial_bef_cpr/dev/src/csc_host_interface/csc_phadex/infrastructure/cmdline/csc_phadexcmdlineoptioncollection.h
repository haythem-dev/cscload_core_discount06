//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       20.08.2010
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHADEX_INFRASTRUCTURE_CMDLINE_CSC_PHADEXCMDLINEOPTIONCOLLECTION_H
#define GUARD_CSC_PHADEX_INFRASTRUCTURE_CMDLINE_CSC_PHADEXCMDLINEOPTIONCOLLECTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace csc_phadex
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            //--------------------------------------------------------------------------------------------------//
            // class declaration section
            //--------------------------------------------------------------------------------------------------//
            class CscPhadexCmdLineOptionCollection : public libutil::infrastructure::cmdLine::CmdLineOptionCollectionBase
            {
                public:
                    CscPhadexCmdLineOptionCollection();
                    virtual ~CscPhadexCmdLineOptionCollection();

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
                    CscPhadexCmdLineOptionCollection( const CscPhadexCmdLineOptionCollection& );
                    CscPhadexCmdLineOptionCollection& operator=( const CscPhadexCmdLineOptionCollection& );
            };
        } // end namespace cmdLine
    } // end namespace infrastructure
} // end namespace csc_phadex

#endif

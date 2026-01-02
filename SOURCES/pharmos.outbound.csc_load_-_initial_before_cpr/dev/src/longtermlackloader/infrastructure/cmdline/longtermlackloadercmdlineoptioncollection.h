//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       20.08.2010
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_CMDLINE_LONGTERMLACKLOADERCMDLINEOPTIONCOLLECTION_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_CMDLINE_LONGTERMLACKLOADERCMDLINEOPTIONCOLLECTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/cmdline.h>

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            //--------------------------------------------------------------------------------------------------//
            // class declaration section
            //--------------------------------------------------------------------------------------------------//
            class LONGTERMLACKLOADERCmdLineOptionCollection : public libutil::infrastructure::cmdLine::CmdLineOptionCollectionBase
            {
                public:
                    LONGTERMLACKLOADERCmdLineOptionCollection();
                    virtual ~LONGTERMLACKLOADERCmdLineOptionCollection();

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
                    LONGTERMLACKLOADERCmdLineOptionCollection( const LONGTERMLACKLOADERCmdLineOptionCollection& );
                    LONGTERMLACKLOADERCmdLineOptionCollection& operator=( const LONGTERMLACKLOADERCmdLineOptionCollection& );
            };
        } // end namespace cmdLine
    } // end namespace infrastructure
} // end namespace longtermlackloader

#endif

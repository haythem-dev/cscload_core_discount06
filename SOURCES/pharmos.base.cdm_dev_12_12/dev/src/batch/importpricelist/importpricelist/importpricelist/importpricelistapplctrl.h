    //------------------------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  application class (main) for IMPORTPRICELIST component (singleton)
 *  \author
 *  \date
 */
//------------------------------------------------------------------------------------------------------------------//
#ifndef GUARD_IMPORTPRICELISTAPPLCTRL_H
#define GUARD_IMPORTPRICELISTAPPLCTRL_H

//------------------------------------------------------------------------------------------------------------------//
// include section
//------------------------------------------------------------------------------------------------------------------//
#include "componentmanager/importpricelistinfrastructurecompmgrptr.h"

// util
#include <libutil/classinfo.h>

// basar
#include <libbasarcmnutil.h>


//------------------------------------------------------------------------------------------------------------------//
// class declaration section
//------------------------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    class ApplCtrlImpl
    {
        //--------------------------------------------------------------------------------------------------//
        // friends
        //--------------------------------------------------------------------------------------------------//
        friend class basar::cmnutil::Singleton<ApplCtrlImpl>;

        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
        public:
            static const libutil::misc::ClassInfo&                  getClassInfo();

        public:
            ~ApplCtrlImpl();

            void                                                    init( int argc, char *argv[] );
            void                                                    run();
            void                                                    shutdown();

        private:
            //---------------------------------------------------------//
            // member methods
            //---------------------------------------------------------//
            ApplCtrlImpl                ();
            ApplCtrlImpl                ( const ApplCtrlImpl& );
            ApplCtrlImpl & operator =    ( const ApplCtrlImpl& );

            const log4cplus::Logger&                                getLogger() const;

            void                                                    createInfrastructureCM( int argc, char *argv[] );
            void                                                    deleteInfrastructureCM();
            componentManager::InfrastructureCompMgrPtr              getInfrastructureCM();

            //---------------------------------------------------------//
            // member variables
            //---------------------------------------------------------//
            const log4cplus::Logger&                                m_Logger;
            componentManager::InfrastructureCompMgrPtr              m_InfrastructureCM;
    };

    //---------------------------------------------------------------------------------------//
    /*! \brief  derived class from IMPORTPRICELISTApplBase.
                This is a final class. Singleton
    *  \note    class is necessary for dll exporting Singleton\<IMPORTPRICELISTApplBase\>  */
    class ApplCtrl : public basar::cmnutil::Singleton< ApplCtrlImpl >
    {
        private:
            ApplCtrl            ();
            ApplCtrl                        ( const ApplCtrl& r );
            ApplCtrl &          operator =  ( const ApplCtrl& r );
    };

}    // end namespace importpricelist

#endif //end GUARD_IMPORTPRICELISTAPPLCTRL_H

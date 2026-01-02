#include "mainwarehousearticlesrelevantcalculator/mainwarehousearticlesrelevantcalculatorapplctrl.h"

int main( int argc, char *argv[] )
{
    //mainwarehousearticlesrelevantcalculator::ApplCtrl::StatusEnum result = mainwarehousearticlesrelevantcalculator::ApplCtrl::ERROR_STATUS

    int result = 0; // Think about a class representing all possible return values and the corresponding texts: mainwarehousearticlesrelevantcalculator::MAINWAREHOUSEARTICLESRELEVANTCALCULATORApplCtrl::OK;
    try
    {
        /* alternative call:
            ==> "mainwarehousearticlesrelevantcalculator::MAINWAREHOUSEARTICLESRELEVANTCALCULATORApplCtrl::init( argc, argv );" <==
            Here the static method 'getInstance()' is called internally.
            Idea is to offer more readable methods.
        */
        mainwarehousearticlesrelevantcalculator::ApplCtrl::getInstance().init( argc, argv );
        mainwarehousearticlesrelevantcalculator::ApplCtrl::getInstance().run();
        mainwarehousearticlesrelevantcalculator::ApplCtrl::getInstance().shutdown();
        mainwarehousearticlesrelevantcalculator::ApplCtrl::clear();

        //result = mainwarehousearticlesrelevantcalculator::ApplCtrl::OK_STATUS;
    }
    catch( ... )
    {
        //result = mainwarehousearticlesrelevantcalculator::ApplCtrl::UNKNOWN_EXCEPTION_CAUGHT;
        result = 99;
    }

    return result;
}

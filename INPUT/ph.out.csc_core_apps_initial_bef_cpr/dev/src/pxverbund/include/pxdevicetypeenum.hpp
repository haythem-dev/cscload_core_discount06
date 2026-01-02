#ifndef GUARD_PP_PXDEVICETYPEENUM_H
#define GUARD_PP_PXDEVICETYPEENUM_H

enum pxDeviceType
{
    pxDVC_UNDEFINED,                    // undefined device type
    pxDVC_VIDEO,                        // Generic video device
    pxDVC_VIDEO_WORKSTATION,            // Video workstation
    pxDVC_VIDEO_TERMINAL,               // Video terminal
    pxDVC_DCT,                          // Generic data communication terminal
    pxDVC_DCT_SERIAL,                   // Data Communication terminal, serial
    pxDVC_DCT_PARALLEL,                 // Data Communication terminal, parallel
    pxDVC_FILE                          // Binary file
};

#endif // GUARD_PP_PXDEVICETYPEENUM_H

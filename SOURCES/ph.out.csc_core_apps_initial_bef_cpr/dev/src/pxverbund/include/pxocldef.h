#ifndef PXOCLDEF_INC
#define PXOCLDEF_INC

/*----------------------------------------------------------------------------*/
/*  Enumeration of close modes                                                */
/*----------------------------------------------------------------------------*/
enum OCLMODE
{
    cOCL_MODE_UNKNOWN   = 0,               //
    cOCL_MODE_IMMEDIATE,                   // mode immediate
    cOCL_MODE_ONCE,                        // mode once
    cOCL_MODE_PERMANENT,                   // mode permanent
    cOCL_MODE_INTERNAL                     // internal use
};

#endif

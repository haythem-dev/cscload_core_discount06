#ifndef GUARD_IMPORTPRICELIST_INFRASTRUCTURE_LOGIN_DEFINITIONS_H
#define GUARD_IMPORTPRICELIST_INFRASTRUCTURE_LOGIN_DEFINITIONS_H

//--------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace infrastructure
    {
        namespace login
        {
			// use login for mainwarehousearticlesrelevantcalculator
			// tbd: define own technical user for importpricelist
            static const char* const    USER   = "wh_artrelcalcuser";
            static const char* const    PASSWD = "TCZiZ;r[";
        }
    }
}

#endif // GUARD_IMPORTPRICELIST_INFRASTRUCTURE_LOGIN_DEFINITIONS_H

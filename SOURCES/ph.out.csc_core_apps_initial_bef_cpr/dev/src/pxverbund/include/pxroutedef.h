/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXROUTEDEF.H
some definitions

REVISION HISTORY
*/

#ifndef PXROUTEDEF_INC
   #define PXROUTEDEF_INC

/*----------------------------------------------------------------------------*/
/*  Change Daytype char to numeric   Table                                    */
/*----------------------------------------------------------------------------*/
struct DAYTabEntry
{
    char  cDayType[3];                 // DayType from Database ( Mo,Di...)
    int   nDayType;                    // Daytype for sort(0,1,2..)
};

static DAYTabEntry cDayTonDayTable[]=
{
    {"SO",0},
    {"MO",1},
    {"DI",2},
    {"MI",3},
    {"DO",4},
    {"FR",5},
    {"SA",6}
};

#endif

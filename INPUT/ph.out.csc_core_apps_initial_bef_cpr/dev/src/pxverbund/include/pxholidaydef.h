/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxholidaydef.h
Common definitions used in pxHoliDay  class

REVISION HISTORY

19 Mar 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXHOLIDAYDEF_INC
   #define PXHOLIDAYDEF_INC


/*----------------------------------------------------------------------------*/
/*  Global definitions for Date Calculation                                   */
/*----------------------------------------------------------------------------*/
#define cHOL_FIX_MODUS              0
#define cHOL_NONFIX_MODUS           1
#define cHOL_FLEXIBLE_MODUS         2

#define cHOL_SUNDAY                 0
#define cHOL_MONDAY                 1
#define cHOL_TUESDAY                2
#define cHOL_WEDNESDAY              3
#define cHOL_THURSDAY               4
#define cHOL_FRIDAY                 5
#define cHOL_SATURDAY               6

#define cHOL_GOODFRI_DAY            -2
#define cHOL_EASTERSUN_DAY           0
#define cHOL_EASTERMON_DAY           1
#define cHOL_ASCENSION_DAY          39
#define cHOL_WITHSUN_DAY            49
#define cHOL_WITHMON_DAY            50
#define cHOL_CORPUS_CHRISTI_DAY     60

//fix dates
#define cHOL_NEWYEARS_DAY           101
#define cHOL_EPIPHANY_DAY           106
#define cHOL_FIRST_OF_MAY           501
#define cHOL_HALLOWEEN             1031
#define cHOL_ALLHALLOWS            1101
#define cHOL_CHRISTMAS_FIRST       1225
#define cHOL_CHRISTMAS_SECOND      1226

#endif

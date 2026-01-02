/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

ZONE.HPP
A zone class which defines locals like week day names and month names.

REVISION HISTORY

18 Sep 1995 V1.00 REV 00 written by Carsten Krabiell.

*/
/*  $History: ZONE.HPP $ */
/*  */
/* *****************  Version 4  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:12 */
/* Updated in $/cxxtools/inc */
/* Final release. */
/* *********************************************** */

#ifndef NZONE_INC
#define NZONE_INC
#ifndef NSTRING_INC
    #include "string.hpp"
#endif
#ifndef STDLIBH_INC
    #define STDLIBH_INC
    #include <stdlib.h>
#endif

/*@DS --------------------------------------------------------------------------
NAME
   nZone - A zone class which defines locals like week day names and month names.

SYNOPSIS
   include "zone.hpp"
   nZone zone = (nZone)GERMANLOCALS;

DESCRIPTION
   Class nZone is an attempt to define locals for string functions; to get the
   name of an week day and month and the local date format.
   (The string format of the date is like in function 'strftime'.)

   To add new locals you define them in the same way as GERMANLOCALS :

      - the week day names started with sunday
      - a number (as string), which is the abbreviation for the week days
      - the month names
      - a number (as string), which is the abbreviation for the month
      - the date format (y : year without century, m : month, d : day)


@DE*/

class nZone {

   nString* local;      // points to locals

public:

/*@DS
PUBLIC CONSTRUCTORS
*/


   ~nZone() {;}
   // Do nothing destructor.

   nZone(nString* zone)
   // Constructor for pointer to nString array containing the locals.
//@DE
      : local(zone) {;}
//@DS


//PUBLIC MEMBERS

   const nString& GetWeekdayName(int wday) const
   // Get the week day name for 'wday' (0 - 6).
//@DE
      { return local[wday]; }
//@DS

   const nSubString GetAbbrWeekdayName(int wday) const
   // Get the abbreviate week day name for 'wday' (0 - 6).
//@DE
      { return local[wday](0,atoi(local[7])); }
//@DS

   const nString& GetMonthName(int month) const
   // Get the month name for 'month' (1 - 12).
//@DE
      { return local[month+7]; }
//@DS

   const nSubString GetAbbrMonthName(int month) const
   // Get the abbreviate month name for 'wday' (1 - 12).
//@DE
      { return local[month+7](0,atoi(local[20])); }
//@DS

   const nString& GetLocalDateFormat() const
   // Get the date format (for 'strftime' or other).
//@DE
      { return local[21]; }
};
//@DS


// GLOBAL DEFINITIONS FOR LOCALS

static nString GERMANLOCALS[] = { "Sonntag", "Montag", "Dienstag", "Mittwoch",
                     "Donnerstag", "Freitag", "Samstag", "3",
                     "Januar", "Februar", "Maerz", "April", "Mai", "Juni",
                     "Juli", "August", "September", "Oktober", "November",
                     "Dezember", "3", "%d.%m.%y" };

static nString ENGLISHLOCALS[] = { "Sunday", "Monday", "Tuesday", "Wednesday",
                     "Thursday", "Friday", "Saturday", "3",
                     "January", "February", "March", "April", "Mai", "June",
                     "July", "August", "September", "October", "November",
                     "December", "3", "%m/%d/%y" };

//@DE

#endif

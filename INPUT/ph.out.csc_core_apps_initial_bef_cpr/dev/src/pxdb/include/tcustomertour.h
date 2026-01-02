#ifndef __PP_CUSTOMERTOUR_H_
#define __PP_CUSTOMERTOUR_H_

/******************************************************************************/
/* c:\tmp\customertour ********************************************************/
/* produced by DADE 6.22.2 ****************************************************/
/******************************************************************************/

/* ppunixc */
#if defined (BUF_DESC) || defined (C_BUF_DESC)
#include <bufkon.h>
#endif

/* Length-Define of CUSTOMERTOUR **********************************************/

#define L_CUSTOMERTOUR_CUSTOMERNO 11
#define L_CUSTOMERTOUR_PICKINGDATE 11
#define L_CUSTOMERTOUR_TOURID 6
#define L_CUSTOMERTOUR_DRIVINGDURATION 11
#define L_CUSTOMERTOUR_ISIBTTOUR 1
#define L_CUSTOMERTOUR_BRANCHNO 6
#define L_CUSTOMERTOUR_DISABLED 1
#define L_CUSTOMERTOUR_TRANSITIONTIME 6
#define L_CUSTOMERTOUR_AUTOASSIGNABLE 1
#define L_CUSTOMERTOUR_CSCORDERTYPE 2
#define L_CUSTOMERTOUR_TOURTRANSITIONTIME 6
#define L_CUSTOMERTOUR_WEEKDAY 6
#define L_CUSTOMERTOUR_TIMEENDOFPICKING 11
#define L_CUSTOMERTOUR_ISCOOLTOUR 6
#define L_CUSTOMERTOUR_ISCOOLBELOW8TOUR 6
#define L_CUSTOMERTOUR_ISCOOLBELOW20TOUR 6
#define L_CUSTOMERTOUR_ISNARCOTICSTOUR 6
#define L_CUSTOMERTOUR_PICKINGTYPE 1
#define L_CUSTOMERTOUR_DELIVERYTIMEBUFFER 6
#define L_CUSTOMERTOUR_LAGRECHTOUR 11
#define L_CUSTOMERTOUR_RETURNSTOUR 6
#define L_CUSTOMERTOUR_ISPSYCHOTROPICTRANSPORTEXCLUDED 6

/* Length/Count-Define of CUSTOMERTOUR ****************************************/

#define LS_CUSTOMERTOUR_CUSTOMERNO 10 + 1
#define LS_CUSTOMERTOUR_PICKINGDATE 10 + 1
#define LS_CUSTOMERTOUR_TOURID 6 + 1
#define LS_CUSTOMERTOUR_DRIVINGDURATION 10 + 1
#define LS_CUSTOMERTOUR_ISIBTTOUR 1 + 1
#define LS_CUSTOMERTOUR_BRANCHNO 5 + 1
#define LS_CUSTOMERTOUR_DISABLED 1 + 1
#define LS_CUSTOMERTOUR_TRANSITIONTIME 5 + 1
#define LS_CUSTOMERTOUR_AUTOASSIGNABLE 1 + 1
#define LS_CUSTOMERTOUR_CSCORDERTYPE 2 + 1
#define LS_CUSTOMERTOUR_TOURTRANSITIONTIME 5 + 1
#define LS_CUSTOMERTOUR_WEEKDAY 5 + 1
#define LS_CUSTOMERTOUR_TIMEENDOFPICKING 10 + 1
#define LS_CUSTOMERTOUR_ISCOOLTOUR 5 + 1
#define LS_CUSTOMERTOUR_ISCOOLBELOW8TOUR 5 + 1
#define LS_CUSTOMERTOUR_ISCOOLBELOW20TOUR 5 + 1
#define LS_CUSTOMERTOUR_ISNARCOTICSTOUR 5 + 1
#define LS_CUSTOMERTOUR_PICKINGTYPE 1 + 1
#define LS_CUSTOMERTOUR_DELIVERYTIMEBUFFER 5 + 1
#define LS_CUSTOMERTOUR_LAGRECHTOUR 10 + 1
#define LS_CUSTOMERTOUR_RETURNSTOUR 5 + 1
#define LS_CUSTOMERTOUR_ISPSYCHOTROPICTRANSPORTEXCLUDED 5 + 1

#define CUSTOMERTOURCUSTOMERNO 0
#define CUSTOMERTOURPICKINGDATE 1
#define CUSTOMERTOURTOURID 2
#define CUSTOMERTOURDRIVINGDURATION 3
#define CUSTOMERTOURISIBTTOUR 4
#define CUSTOMERTOURBRANCHNO 5
#define CUSTOMERTOURDISABLED 6
#define CUSTOMERTOURTRANSITIONTIME 7
#define CUSTOMERTOURAUTOASSIGNABLE 8
#define CUSTOMERTOURCSCORDERTYPE 9
#define CUSTOMERTOURTOURTRANSITIONTIME 10
#define CUSTOMERTOURWEEKDAY 11
#define CUSTOMERTOURTIMEENDOFPICKING 12
#define CUSTOMERTOURISCOOLTOUR 13
#define CUSTOMERTOURISCOOLBELOW8TOUR 14
#define CUSTOMERTOURISCOOLBELOW20TOUR 15
#define CUSTOMERTOURISNARCOTICSTOUR 16
#define CUSTOMERTOURPICKINGTYPE 17
#define CUSTOMERTOURDELIVERYTIMEBUFFER 18
#define CUSTOMERTOURLAGRECHTOUR 19
#define CUSTOMERTOURRETURNSTOUR 20
#define CUSTOMERTOURISPSYCHOTROPICTRANSPORTEXCLUDED 21

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
#define CUSTOMERTOUR_H
#define CUSTOMERTOUR_ANZ ( sizeof(CUSTOMERTOUR_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTOMERTOUR **************************************************/

#define CUSTOMERTOUR_LISTE \
        CUSTOMERTOUR.CUSTOMERNO,\
        CUSTOMERTOUR.PICKINGDATE,\
        CUSTOMERTOUR.TOURID,\
        CUSTOMERTOUR.DRIVINGDURATION,\
        CUSTOMERTOUR.ISIBTTOUR,\
        CUSTOMERTOUR.BRANCHNO,\
        CUSTOMERTOUR.DISABLED,\
        CUSTOMERTOUR.TRANSITIONTIME,\
        CUSTOMERTOUR.AUTOASSIGNABLE,\
        CUSTOMERTOUR.CSCORDERTYPE,\
        CUSTOMERTOUR.TOURTRANSITIONTIME,\
        CUSTOMERTOUR.WEEKDAY,\
        CUSTOMERTOUR.TIMEENDOFPICKING,\
        CUSTOMERTOUR.ISCOOLTOUR,\
        CUSTOMERTOUR.ISCOOLBELOW8TOUR,\
        CUSTOMERTOUR.ISCOOLBELOW20TOUR,\
        CUSTOMERTOUR.ISNARCOTICSTOUR,\
        CUSTOMERTOUR.PICKINGTYPE,\
        CUSTOMERTOUR.DELIVERYTIMEBUFFER,\
        CUSTOMERTOUR.LAGRECHTOUR,\
        CUSTOMERTOUR.RETURNSTOUR,\
        CUSTOMERTOUR.ISPSYCHOTROPICTRANSPORTEXCLUDED
#define CUSTOMERTOUR_LISTE_390 \
        CUSTOMERNO,\
        PICKINGDATE,\
        TOURID,\
        DRIVINGDURATION,\
        ISIBTTOUR,\
        BRANCHNO,\
        DISABLED,\
        TRANSITIONTIME,\
        AUTOASSIGNABLE,\
        CSCORDERTYPE,\
        TOURTRANSITIONTIME,\
        WEEKDAY,\
        TIMEENDOFPICKING,\
        ISCOOLTOUR,\
        ISCOOLBELOW8TOUR,\
        ISCOOLBELOW20TOUR,\
        ISNARCOTICSTOUR,\
        PICKINGTYPE,\
        DELIVERYTIMEBUFFER,\
        LAGRECHTOUR,\
        RETURNSTOUR,\
        ISPSYCHOTROPICTRANSPORTEXCLUDED
#define CUSTOMERTOUR_PLISTE \
        "CUSTOMERTOUR.CUSTOMERNO,"\
        "CUSTOMERTOUR.PICKINGDATE,"\
        "CUSTOMERTOUR.TOURID,"\
        "CUSTOMERTOUR.DRIVINGDURATION,"\
        "CUSTOMERTOUR.ISIBTTOUR,"\
        "CUSTOMERTOUR.BRANCHNO,"\
        "CUSTOMERTOUR.DISABLED,"\
        "CUSTOMERTOUR.TRANSITIONTIME,"\
        "CUSTOMERTOUR.AUTOASSIGNABLE,"\
        "CUSTOMERTOUR.CSCORDERTYPE,"\
        "CUSTOMERTOUR.TOURTRANSITIONTIME,"\
        "CUSTOMERTOUR.WEEKDAY,"\
        "CUSTOMERTOUR.TIMEENDOFPICKING,"\
        "CUSTOMERTOUR.ISCOOLTOUR,"\
        "CUSTOMERTOUR.ISCOOLBELOW8TOUR,"\
        "CUSTOMERTOUR.ISCOOLBELOW20TOUR,"\
        "CUSTOMERTOUR.ISNARCOTICSTOUR,"\
        "CUSTOMERTOUR.PICKINGTYPE,"\
        "CUSTOMERTOUR.DELIVERYTIMEBUFFER,"\
        "CUSTOMERTOUR.LAGRECHTOUR,"\
        "CUSTOMERTOUR.RETURNSTOUR,"\
        "CUSTOMERTOUR.ISPSYCHOTROPICTRANSPORTEXCLUDED"
#define CUSTOMERTOUR_PELISTE \
        "CUSTOMERNO,"\
        "PICKINGDATE,"\
        "TOURID,"\
        "DRIVINGDURATION,"\
        "ISIBTTOUR,"\
        "BRANCHNO,"\
        "DISABLED,"\
        "TRANSITIONTIME,"\
        "AUTOASSIGNABLE,"\
        "CSCORDERTYPE,"\
        "TOURTRANSITIONTIME,"\
        "WEEKDAY,"\
        "TIMEENDOFPICKING,"\
        "ISCOOLTOUR,"\
        "ISCOOLBELOW8TOUR,"\
        "ISCOOLBELOW20TOUR,"\
        "ISNARCOTICSTOUR,"\
        "PICKINGTYPE,"\
        "DELIVERYTIMEBUFFER,"\
        "LAGRECHTOUR,"\
        "RETURNSTOUR,"\
        "ISPSYCHOTROPICTRANSPORTEXCLUDED"
#define CUSTOMERTOUR_UPDLISTE \
        "CUSTOMERNO=?,"\
        "PICKINGDATE=?,"\
        "TOURID=?,"\
        "DRIVINGDURATION=?,"\
        "ISIBTTOUR=?,"\
        "BRANCHNO=?,"\
        "DISABLED=?,"\
        "TRANSITIONTIME=?,"\
        "AUTOASSIGNABLE=?,"\
        "CSCORDERTYPE=?,"\
        "TOURTRANSITIONTIME=?,"\
        "WEEKDAY=?,"\
        "TIMEENDOFPICKING=?,"\
        "ISCOOLTOUR=?,"\
        "ISCOOLBELOW8TOUR=?,"\
        "ISCOOLBELOW20TOUR=?,"\
        "ISNARCOTICSTOUR=?,"\
        "PICKINGTYPE=?,"\
        "DELIVERYTIMEBUFFER=?,"\
        "LAGRECHTOUR=?,"\
        "RETURNSTOUR=?,"\
        "ISPSYCHOTROPICTRANSPORTEXCLUDED=?"
/* SqlMacros-Define of CUSTOMERTOUR *******************************************/

#define CUSTOMERTOUR_ZEIGER(x) \
        :x->CUSTOMERNO,\
        :x->PICKINGDATE,\
        :x->TOURID,\
        :x->DRIVINGDURATION,\
        :x->ISIBTTOUR,\
        :x->BRANCHNO,\
        :x->DISABLED,\
        :x->TRANSITIONTIME,\
        :x->AUTOASSIGNABLE,\
        :x->CSCORDERTYPE,\
        :x->TOURTRANSITIONTIME,\
        :x->WEEKDAY,\
        :x->TIMEENDOFPICKING,\
        :x->ISCOOLTOUR,\
        :x->ISCOOLBELOW8TOUR,\
        :x->ISCOOLBELOW20TOUR,\
        :x->ISNARCOTICSTOUR,\
        :x->PICKINGTYPE,\
        :x->DELIVERYTIMEBUFFER,\
        :x->LAGRECHTOUR,\
        :x->RETURNSTOUR,\
        :x->ISPSYCHOTROPICTRANSPORTEXCLUDED
#define CUSTOMERTOUR_ZEIGERSEL(x) \
        :x->CUSTOMERNO,\
        :x->PICKINGDATE,\
        :x->TOURID,\
        :x->DRIVINGDURATION,\
        :x->ISIBTTOUR,\
        :x->BRANCHNO,\
        :x->DISABLED,\
        :x->TRANSITIONTIME,\
        :x->AUTOASSIGNABLE,\
        :x->CSCORDERTYPE,\
        :x->TOURTRANSITIONTIME,\
        :x->WEEKDAY,\
        :x->TIMEENDOFPICKING,\
        :x->ISCOOLTOUR,\
        :x->ISCOOLBELOW8TOUR,\
        :x->ISCOOLBELOW20TOUR,\
        :x->ISNARCOTICSTOUR,\
        :x->PICKINGTYPE,\
        :x->DELIVERYTIMEBUFFER,\
        :x->LAGRECHTOUR,\
        :x->RETURNSTOUR,\
        :x->ISPSYCHOTROPICTRANSPORTEXCLUDED
#define CUSTOMERTOUR_UPDATE(x) \
        CUSTOMERTOUR.CUSTOMERNO=:x->CUSTOMERNO,\
        CUSTOMERTOUR.PICKINGDATE=:x->PICKINGDATE,\
        CUSTOMERTOUR.TOURID=:x->TOURID,\
        CUSTOMERTOUR.DRIVINGDURATION=:x->DRIVINGDURATION,\
        CUSTOMERTOUR.ISIBTTOUR=:x->ISIBTTOUR,\
        CUSTOMERTOUR.BRANCHNO=:x->BRANCHNO,\
        CUSTOMERTOUR.DISABLED=:x->DISABLED,\
        CUSTOMERTOUR.TRANSITIONTIME=:x->TRANSITIONTIME,\
        CUSTOMERTOUR.AUTOASSIGNABLE=:x->AUTOASSIGNABLE,\
        CUSTOMERTOUR.CSCORDERTYPE=:x->CSCORDERTYPE,\
        CUSTOMERTOUR.TOURTRANSITIONTIME=:x->TOURTRANSITIONTIME,\
        CUSTOMERTOUR.WEEKDAY=:x->WEEKDAY,\
        CUSTOMERTOUR.TIMEENDOFPICKING=:x->TIMEENDOFPICKING,\
        CUSTOMERTOUR.ISCOOLTOUR=:x->ISCOOLTOUR,\
        CUSTOMERTOUR.ISCOOLBELOW8TOUR=:x->ISCOOLBELOW8TOUR,\
        CUSTOMERTOUR.ISCOOLBELOW20TOUR=:x->ISCOOLBELOW20TOUR,\
        CUSTOMERTOUR.ISNARCOTICSTOUR=:x->ISNARCOTICSTOUR,\
        CUSTOMERTOUR.PICKINGTYPE=:x->PICKINGTYPE,\
        CUSTOMERTOUR.DELIVERYTIMEBUFFER=:x->DELIVERYTIMEBUFFER,\
        CUSTOMERTOUR.LAGRECHTOUR=:x->LAGRECHTOUR,\
        CUSTOMERTOUR.RETURNSTOUR=:x->RETURNSTOUR,\
        CUSTOMERTOUR.ISPSYCHOTROPICTRANSPORTEXCLUDED=:x->ISPSYCHOTROPICTRANSPORTEXCLUDED
/* SqlMacros390-Define of CUSTOMERTOUR ****************************************/

#define CUSTOMERTOUR_ZEIGER_390 \
        :CUSTOMERNO,\
        :PICKINGDATE,\
        :TOURID,\
        :DRIVINGDURATION,\
        :ISIBTTOUR,\
        :BRANCHNO,\
        :DISABLED,\
        :TRANSITIONTIME,\
        :AUTOASSIGNABLE,\
        :CSCORDERTYPE,\
        :TOURTRANSITIONTIME,\
        :WEEKDAY,\
        :TIMEENDOFPICKING,\
        :ISCOOLTOUR,\
        :ISCOOLBELOW8TOUR,\
        :ISCOOLBELOW20TOUR,\
        :ISNARCOTICSTOUR,\
        :PICKINGTYPE,\
        :DELIVERYTIMEBUFFER,\
        :LAGRECHTOUR,\
        :RETURNSTOUR,\
        :ISPSYCHOTROPICTRANSPORTEXCLUDED
#define CUSTOMERTOUR_UPDATE_390 \
        CUSTOMERNO=:CUSTOMERNO,\
        PICKINGDATE=:PICKINGDATE,\
        TOURID=:TOURID,\
        DRIVINGDURATION=:DRIVINGDURATION,\
        ISIBTTOUR=:ISIBTTOUR,\
        BRANCHNO=:BRANCHNO,\
        DISABLED=:DISABLED,\
        TRANSITIONTIME=:TRANSITIONTIME,\
        AUTOASSIGNABLE=:AUTOASSIGNABLE,\
        CSCORDERTYPE=:CSCORDERTYPE,\
        TOURTRANSITIONTIME=:TOURTRANSITIONTIME,\
        WEEKDAY=:WEEKDAY,\
        TIMEENDOFPICKING=:TIMEENDOFPICKING,\
        ISCOOLTOUR=:ISCOOLTOUR,\
        ISCOOLBELOW8TOUR=:ISCOOLBELOW8TOUR,\
        ISCOOLBELOW20TOUR=:ISCOOLBELOW20TOUR,\
        ISNARCOTICSTOUR=:ISNARCOTICSTOUR,\
        PICKINGTYPE=:PICKINGTYPE,\
        DELIVERYTIMEBUFFER=:DELIVERYTIMEBUFFER,\
        LAGRECHTOUR=:LAGRECHTOUR,\
        RETURNSTOUR=:RETURNSTOUR,\
        ISPSYCHOTROPICTRANSPORTEXCLUDED=:ISPSYCHOTROPICTRANSPORTEXCLUDED
#ifdef TRANSCLASS
#include <string.h>
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of CUSTOMERTOUR ********************************************/

#ifndef TRANSCLASS
typedef struct N_CUSTOMERTOUR {
    long CUSTOMERNO;
    long PICKINGDATE;
    char TOURID[7];
    long DRIVINGDURATION;
    char ISIBTTOUR[2];
    short BRANCHNO;
    char DISABLED[2];
    short TRANSITIONTIME;
    char AUTOASSIGNABLE[2];
    char CSCORDERTYPE[3];
    short TOURTRANSITIONTIME;
    short WEEKDAY;
    long TIMEENDOFPICKING;
    short ISCOOLTOUR;
    short ISCOOLBELOW8TOUR;
    short ISCOOLBELOW20TOUR;
    short ISNARCOTICSTOUR;
    char PICKINGTYPE[2];
    short DELIVERYTIMEBUFFER;
    long LAGRECHTOUR;
    short RETURNSTOUR;
    short ISPSYCHOTROPICTRANSPORTEXCLUDED;
} customertourS;
#else /* TRANSCLASS */
typedef struct N_CUSTOMERTOUR {
    long CUSTOMERNO;
    long PICKINGDATE;
    char TOURID[7];
    long DRIVINGDURATION;
    char ISIBTTOUR[2];
    short BRANCHNO;
    char DISABLED[2];
    short TRANSITIONTIME;
    char AUTOASSIGNABLE[2];
    char CSCORDERTYPE[3];
    short TOURTRANSITIONTIME;
    short WEEKDAY;
    long TIMEENDOFPICKING;
    short ISCOOLTOUR;
    short ISCOOLBELOW8TOUR;
    short ISCOOLBELOW20TOUR;
    short ISNARCOTICSTOUR;
    char PICKINGTYPE[2];
    short DELIVERYTIMEBUFFER;
    long LAGRECHTOUR;
    short RETURNSTOUR;
    short ISPSYCHOTROPICTRANSPORTEXCLUDED;

    bool operator == (const N_CUSTOMERTOUR& right) const {
        return (
            CUSTOMERNO == right.CUSTOMERNO &&
            PICKINGDATE == right.PICKINGDATE &&
            !strcmp(TOURID, right.TOURID) &&
            DRIVINGDURATION == right.DRIVINGDURATION &&
            !strcmp(ISIBTTOUR, right.ISIBTTOUR) &&
            BRANCHNO == right.BRANCHNO &&
            !strcmp(DISABLED, right.DISABLED) &&
            TRANSITIONTIME == right.TRANSITIONTIME &&
            !strcmp(AUTOASSIGNABLE, right.AUTOASSIGNABLE) &&
            !strcmp(CSCORDERTYPE, right.CSCORDERTYPE) &&
            TOURTRANSITIONTIME == right.TOURTRANSITIONTIME &&
            WEEKDAY == right.WEEKDAY &&
            TIMEENDOFPICKING == right.TIMEENDOFPICKING &&
            ISCOOLTOUR == right.ISCOOLTOUR &&
            ISCOOLBELOW8TOUR == right.ISCOOLBELOW8TOUR &&
            ISCOOLBELOW20TOUR == right.ISCOOLBELOW20TOUR &&
            ISNARCOTICSTOUR == right.ISNARCOTICSTOUR &&
            !strcmp(PICKINGTYPE, right.PICKINGTYPE) &&
            DELIVERYTIMEBUFFER == right.DELIVERYTIMEBUFFER &&
            LAGRECHTOUR == right.LAGRECHTOUR &&
            RETURNSTOUR == right.RETURNSTOUR &&
            ISPSYCHOTROPICTRANSPORTEXCLUDED == right.ISPSYCHOTROPICTRANSPORTEXCLUDED
        );
    }
    void clear() {
#ifdef WIN32
        memset((char*)this, 0, sizeof(*this));
#else
        CUSTOMERNO = 0;
        PICKINGDATE = 0;
        strcpy(TOURID, " " );
        DRIVINGDURATION = 0;
        strcpy(ISIBTTOUR, " " );
        BRANCHNO = 0;
        strcpy(DISABLED, " " );
        TRANSITIONTIME = 0;
        strcpy(AUTOASSIGNABLE, " " );
        strcpy(CSCORDERTYPE, " " );
        TOURTRANSITIONTIME = 0;
        WEEKDAY = 0;
        TIMEENDOFPICKING = 0;
        ISCOOLTOUR = 0;
        ISCOOLBELOW8TOUR = 0;
        ISCOOLBELOW20TOUR = 0;
        ISNARCOTICSTOUR = 0;
        strcpy(PICKINGTYPE, " " );
        DELIVERYTIMEBUFFER = 0;
        LAGRECHTOUR = 0;
        RETURNSTOUR = 0;
        ISPSYCHOTROPICTRANSPORTEXCLUDED = 0;
#endif
    }
} customertourS;
#endif /* TRANSCLASS */

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTOMERTOUR **************************************/

struct S_CUSTOMERTOUR {
    char CUSTOMERNO[11];
    char PICKINGDATE[11];
    char TOURID[6 + 1];
    char DRIVINGDURATION[11];
    char ISIBTTOUR[1 + 1];
    char BRANCHNO[7];
    char DISABLED[1 + 1];
    char TRANSITIONTIME[7];
    char AUTOASSIGNABLE[1 + 1];
    char CSCORDERTYPE[2 + 1];
    char TOURTRANSITIONTIME[7];
    char WEEKDAY[7];
    char TIMEENDOFPICKING[11];
    char ISCOOLTOUR[7];
    char ISCOOLBELOW8TOUR[7];
    char ISCOOLBELOW20TOUR[7];
    char ISNARCOTICSTOUR[7];
    char PICKINGTYPE[1 + 1];
    char DELIVERYTIMEBUFFER[7];
    char LAGRECHTOUR[11];
    char RETURNSTOUR[7];
    char ISPSYCHOTROPICTRANSPORTEXCLUDED[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTOMERTOUR *********************/

struct O_CUSTOMERTOUR {
    char CUSTOMERNO[11];
    char PICKINGDATE[11];
    char TOURID[6];
    char DRIVINGDURATION[11];
    char ISIBTTOUR[1];
    char BRANCHNO[7];
    char DISABLED[1];
    char TRANSITIONTIME[7];
    char AUTOASSIGNABLE[1];
    char CSCORDERTYPE[2];
    char TOURTRANSITIONTIME[7];
    char WEEKDAY[7];
    char TIMEENDOFPICKING[11];
    char ISCOOLTOUR[7];
    char ISCOOLBELOW8TOUR[7];
    char ISCOOLBELOW20TOUR[7];
    char ISNARCOTICSTOUR[7];
    char PICKINGTYPE[1];
    char DELIVERYTIMEBUFFER[7];
    char LAGRECHTOUR[11];
    char RETURNSTOUR[7];
    char ISPSYCHOTROPICTRANSPORTEXCLUDED[7];
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTOMERTOUR ********************************/

struct C_CUSTOMERTOUR {
    long CUSTOMERNO;
    long PICKINGDATE;
    char TOURID[7];
    long DRIVINGDURATION;
    char ISIBTTOUR;
    short BRANCHNO;
    char DISABLED;
    short TRANSITIONTIME;
    char AUTOASSIGNABLE;
    char CSCORDERTYPE[3];
    short TOURTRANSITIONTIME;
    short WEEKDAY;
    long TIMEENDOFPICKING;
    short ISCOOLTOUR;
    short ISCOOLBELOW8TOUR;
    short ISCOOLBELOW20TOUR;
    short ISNARCOTICSTOUR;
    char PICKINGTYPE;
    short DELIVERYTIMEBUFFER;
    long LAGRECHTOUR;
    short RETURNSTOUR;
    short ISPSYCHOTROPICTRANSPORTEXCLUDED;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTOMERTOUR ******************************/

struct I_CUSTOMERTOUR {
    short CUSTOMERNO;
    short PICKINGDATE;
    short TOURID;
    short DRIVINGDURATION;
    short ISIBTTOUR;
    short BRANCHNO;
    short DISABLED;
    short TRANSITIONTIME;
    short AUTOASSIGNABLE;
    short CSCORDERTYPE;
    short TOURTRANSITIONTIME;
    short WEEKDAY;
    short TIMEENDOFPICKING;
    short ISCOOLTOUR;
    short ISCOOLBELOW8TOUR;
    short ISCOOLBELOW20TOUR;
    short ISNARCOTICSTOUR;
    short PICKINGTYPE;
    short DELIVERYTIMEBUFFER;
    short LAGRECHTOUR;
    short RETURNSTOUR;
    short ISPSYCHOTROPICTRANSPORTEXCLUDED;
};
#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTOMERTOUR ****************************************/

#if defined (BUF_DESC)
static struct buf_desc CUSTOMERTOUR_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#elif defined (C_BUF_DESC)
static struct buf_desc CUSTOMERTOUR_BES [] = {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
};
#endif

/* description for datatypes of CUSTOMERTOUR **********************************/

 #define CUSTOMERTOUR_S390 \
         long CUSTOMERNO; \
         long PICKINGDATE; \
         char TOURID[7]; \
         long DRIVINGDURATION; \
         char ISIBTTOUR; \
         short BRANCHNO; \
         char DISABLED; \
         short TRANSITIONTIME; \
         char AUTOASSIGNABLE; \
         char CSCORDERTYPE[3]; \
         short TOURTRANSITIONTIME; \
         short WEEKDAY; \
         long TIMEENDOFPICKING; \
         short ISCOOLTOUR; \
         short ISCOOLBELOW8TOUR; \
         short ISCOOLBELOW20TOUR; \
         short ISNARCOTICSTOUR; \
         char PICKINGTYPE; \
         short DELIVERYTIMEBUFFER; \
         long LAGRECHTOUR; \
         short RETURNSTOUR; \
         short ISPSYCHOTROPICTRANSPORTEXCLUDED; \



/* Copy-Function Struct to single Data CUSTOMERTOUR ***************************/

 #define CUSTOMERTOUR_S390_COPY_TO_SINGLE(_x_) \
         CUSTOMERNO=_x_->CUSTOMERNO;\
         PICKINGDATE=_x_->PICKINGDATE;\
          strcpy(TOURID,_x_->TOURID);\
         DRIVINGDURATION=_x_->DRIVINGDURATION;\
         ISIBTTOUR=_x_->ISIBTTOUR;\
         BRANCHNO=_x_->BRANCHNO;\
         DISABLED=_x_->DISABLED;\
         TRANSITIONTIME=_x_->TRANSITIONTIME;\
         AUTOASSIGNABLE=_x_->AUTOASSIGNABLE;\
          strcpy(CSCORDERTYPE,_x_->CSCORDERTYPE);\
         TOURTRANSITIONTIME=_x_->TOURTRANSITIONTIME;\
         WEEKDAY=_x_->WEEKDAY;\
         TIMEENDOFPICKING=_x_->TIMEENDOFPICKING;\
         ISCOOLTOUR=_x_->ISCOOLTOUR;\
         ISCOOLBELOW8TOUR=_x_->ISCOOLBELOW8TOUR;\
         ISCOOLBELOW20TOUR=_x_->ISCOOLBELOW20TOUR;\
         ISNARCOTICSTOUR=_x_->ISNARCOTICSTOUR;\
         PICKINGTYPE=_x_->PICKINGTYPE;\
         DELIVERYTIMEBUFFER=_x_->DELIVERYTIMEBUFFER;\
         LAGRECHTOUR=_x_->LAGRECHTOUR;\
         RETURNSTOUR=_x_->RETURNSTOUR;\
         ISPSYCHOTROPICTRANSPORTEXCLUDED=_x_->ISPSYCHOTROPICTRANSPORTEXCLUDED;\

 #define CUSTOMERTOUR_S390_COPY_TO_STRUCT(_x_) \
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->PICKINGDATE=PICKINGDATE;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->DRIVINGDURATION=DRIVINGDURATION;\
          _x_->ISIBTTOUR=ISIBTTOUR;\
          _x_->BRANCHNO=BRANCHNO;\
          _x_->DISABLED=DISABLED;\
          _x_->TRANSITIONTIME=TRANSITIONTIME;\
          _x_->AUTOASSIGNABLE=AUTOASSIGNABLE;\
          strcpy(_x_->CSCORDERTYPE,CSCORDERTYPE);\
          _x_->TOURTRANSITIONTIME=TOURTRANSITIONTIME;\
          _x_->WEEKDAY=WEEKDAY;\
          _x_->TIMEENDOFPICKING=TIMEENDOFPICKING;\
          _x_->ISCOOLTOUR=ISCOOLTOUR;\
          _x_->ISCOOLBELOW8TOUR=ISCOOLBELOW8TOUR;\
          _x_->ISCOOLBELOW20TOUR=ISCOOLBELOW20TOUR;\
          _x_->ISNARCOTICSTOUR=ISNARCOTICSTOUR;\
          _x_->PICKINGTYPE=PICKINGTYPE;\
          _x_->DELIVERYTIMEBUFFER=DELIVERYTIMEBUFFER;\
          _x_->LAGRECHTOUR=LAGRECHTOUR;\
          _x_->RETURNSTOUR=RETURNSTOUR;\
          _x_->ISPSYCHOTROPICTRANSPORTEXCLUDED=ISPSYCHOTROPICTRANSPORTEXCLUDED;\



/* FunctionNumber-Define of customertour **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of customertour **********************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS

#include<vector>
using namespace std;

/* ppunixc */
#include <sockclient.h>
#include <ppstring.h>
#include <ppgeneric.h>

/* must be implemented */
void FehlerBehandlung(int rc, const char * const error_msg);

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual {
public:
    virtual    ~ppDadeVirtual() {};
    virtual int SelList      (int FetchRel = 1, int pos = 0) = 0;
    virtual int SelListHist  (int FetchRel = 1, int pos = 0) = 0;
    virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
    virtual int Load         (int pos = 0                  ) = 0;
    virtual int Delete       (int pos = 0                  ) = 0;
    virtual int Save         (int pos = 0                  ) = 0;
};
#endif

class CCUSTOMERTOUR : public ppDadeVirtual {
public:
    customertourS s;
    int  rc;
    char error_msg[81];
private:
    bool bOpenCursor;
    bool bEndOfSelect;
    int  FncNumber;
    int  CursorPos;
    int  AnzPos;
    vector<customertourS> lst; // class list

public:
    unsigned int GetSize() const { return static_cast<unsigned int>(lst.size()); };
    void         ClearStruct() { s.clear(); }
    bool         SetData(unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     s = lst.at(i);
                     return true;
                 }
    bool         SetList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< customertourS >::iterator it = lst.begin() + i;
                     *it = s;
                     return true;
                 }
    bool         InsList() {
                     Strip(s);
                     customertourS c = s;
                     lst.insert(lst.end(), c);
                     AnzPos++;
                     return true;
                 }
    bool         DelList(const unsigned int i) {
                     if (GetSize() <= i)
                         return false;
                     vector< customertourS >::iterator it = lst.begin() + i;
                     if (it != lst.end())
                         lst.erase(it);
                     if (--AnzPos < 0)
                         AnzPos = 0;
                     return true;
                 }

    vector<customertourS>::iterator
                 beginList() { return lst.begin(); }
    vector<customertourS>::iterator
                 endList  () { return lst.end  (); }

    long         GetCustomerno() const { return s.CUSTOMERNO; }
    long         GetPickingdate() const { return s.PICKINGDATE; }
    const char*  GetTourid(ppString & t) const { t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
    long         GetDrivingduration() const { return s.DRIVINGDURATION; }
    char         GetIsibttour() const { return s.ISIBTTOUR[0]; }
    short        GetBranchno() const { return s.BRANCHNO; }
    char         GetDisabled() const { return s.DISABLED[0]; }
    short        GetTransitiontime() const { return s.TRANSITIONTIME; }
    char         GetAutoassignable() const { return s.AUTOASSIGNABLE[0]; }
    const char*  GetCscordertype(ppString & t) const { t = s.CSCORDERTYPE; t.erasespace(ppString::END); return t.c_str(); }
    short        GetTourtransitiontime() const { return s.TOURTRANSITIONTIME; }
    short        GetWeekday() const { return s.WEEKDAY; }
    long         GetTimeendofpicking() const { return s.TIMEENDOFPICKING; }
    short        GetIscooltour() const { return s.ISCOOLTOUR; }
    short        GetIscoolbelow8tour() const { return s.ISCOOLBELOW8TOUR; }
    short        GetIscoolbelow20tour() const { return s.ISCOOLBELOW20TOUR; }
    short        GetIsnarcoticstour() const { return s.ISNARCOTICSTOUR; }
    char         GetPickingtype() const { return s.PICKINGTYPE[0]; }
    short        GetDeliverytimebuffer() const { return s.DELIVERYTIMEBUFFER; }
    long         GetLagrechtour() const { return s.LAGRECHTOUR; }
    short        GetReturnstour() const { return s.RETURNSTOUR; }
    short        GetIspsychotropictransportexcluded() const { return s.ISPSYCHOTROPICTRANSPORTEXCLUDED; }

    const customertourS &
                 GetStruct() const { return s; }
    void         SetCustomerno(long t) { s.CUSTOMERNO = t; }
    void         SetPickingdate(long t) { s.PICKINGDATE = t; }
    void         SetTourid(const ppString & t) { ppGStrCopy(s.TOURID, t.c_str(), L_CUSTOMERTOUR_TOURID); }
    void         SetDrivingduration(long t) { s.DRIVINGDURATION = t; }
    void         SetIsibttour(char t) { s.ISIBTTOUR[0] = t; s.ISIBTTOUR[1] = '\0';}
    void         SetBranchno(short t) { s.BRANCHNO = t; }
    void         SetDisabled(char t) { s.DISABLED[0] = t; s.DISABLED[1] = '\0';}
    void         SetTransitiontime(short t) { s.TRANSITIONTIME = t; }
    void         SetAutoassignable(char t) { s.AUTOASSIGNABLE[0] = t; s.AUTOASSIGNABLE[1] = '\0';}
    void         SetCscordertype(const ppString & t) { ppGStrCopy(s.CSCORDERTYPE, t.c_str(), L_CUSTOMERTOUR_CSCORDERTYPE); }
    void         SetTourtransitiontime(short t) { s.TOURTRANSITIONTIME = t; }
    void         SetWeekday(short t) { s.WEEKDAY = t; }
    void         SetTimeendofpicking(long t) { s.TIMEENDOFPICKING = t; }
    void         SetIscooltour(short t) { s.ISCOOLTOUR = t; }
    void         SetIscoolbelow8tour(short t) { s.ISCOOLBELOW8TOUR = t; }
    void         SetIscoolbelow20tour(short t) { s.ISCOOLBELOW20TOUR = t; }
    void         SetIsnarcoticstour(short t) { s.ISNARCOTICSTOUR = t; }
    void         SetPickingtype(char t) { s.PICKINGTYPE[0] = t; s.PICKINGTYPE[1] = '\0';}
    void         SetDeliverytimebuffer(short t) { s.DELIVERYTIMEBUFFER = t; }
    void         SetLagrechtour(long t) { s.LAGRECHTOUR = t; }
    void         SetReturnstour(short t) { s.RETURNSTOUR = t; }
    void         SetIspsychotropictransportexcluded(short t) { s.ISPSYCHOTROPICTRANSPORTEXCLUDED = t; }

    void         SetStruct(const customertourS & t) { s = t; }


    // virtual functions
public:
    int          Load(int pos = 0) { pos = pos; return 1; }
    int          Save(int pos = 0) { pos = pos; return 1; }
    int          Delete(int pos = 0) { pos = pos; return 1; }
    int          SelList(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListHist(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }
    int          SelListFuture(int FetchRel = 1, int pos = 0) { FetchRel = FetchRel; pos = pos; return 1; }

    // constructor
    CCUSTOMERTOUR() {
        ::buf_default((void *)&s, CUSTOMERTOUR_BES, CUSTOMERTOUR_ANZ);
        bOpenCursor   = false;
        bEndOfSelect  = false;
        FncNumber     = 0;
        CursorPos     = 0;
        AnzPos        = 0;
        rc            = 0;
        s.clear();
    }

    // destructor
    virtual ~CCUSTOMERTOUR() {
    }

    // buffer init
    void buf_default() {
        ::buf_default((void *)&s, CUSTOMERTOUR_BES, CUSTOMERTOUR_ANZ);
    }

    // socket server call
    int Server(int fkt_nr, int pos = 0) {
    #ifdef WIN32
        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTOMERTOUR_BES, (int)CUSTOMERTOUR_ANZ, error_msg);
    #else
        rc = ::Server(fkt_nr, (void *)&s, CUSTOMERTOUR_BES, (int)CUSTOMERTOUR_ANZ, error_msg);
    #endif
        if (rc < 0)
            FehlerBehandlung( rc, error_msg );
        return rc;
    }

private:
    void Strip(N_CUSTOMERTOUR & d) {
        d = d;
    #ifdef WIN32
        ppGStripLast(d.TOURID);
        ppGStripLast(d.CSCORDERTYPE);
    #endif
    }

    int UniqueServerCall(int FncNr, int pos = 0) {
    #ifndef __DADE_LOAD__
       rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERTOUR_BES, (int)CUSTOMERTOUR_ANZ, error_msg);
    #else
       pos = pos;
       rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
    #endif
       if (rc < 0)
           FehlerBehandlung( rc, error_msg );
       return rc;
    }
};
#endif    // TRANSCLASS
/* CreateSqlStatement of CUSTOMERTOUR *****************************************/

 #define CUSTOMERTOUR_CREATE(x) EXEC SQL create table x (\
         CUSTOMERNO integer default 0 not null,\
         PICKINGDATE integer default 0 not null,\
         TOURID char(6) default " " not null,\
         DRIVINGDURATION integer default 0 not null,\
         ISIBTTOUR char(1) default " " not null,\
         BRANCHNO smallint default 0 not null,\
         DISABLED char(1) default " " not null,\
         TRANSITIONTIME smallint default 0 not null,\
         AUTOASSIGNABLE char(1) default " " not null,\
         CSCORDERTYPE char(2) default " " not null,\
         TOURTRANSITIONTIME smallint default 0 not null,\
         WEEKDAY smallint default 0 not null,\
         TIMEENDOFPICKING integer default 0 not null,\
         ISCOOLTOUR smallint default 0 not null,\
         ISCOOLBELOW8TOUR smallint default 0 not null,\
         ISCOOLBELOW20TOUR smallint default 0 not null,\
         ISNARCOTICSTOUR smallint default 0 not null,\
         PICKINGTYPE char(1) default " " not null,\
         DELIVERYTIMEBUFFER smallint default 0 not null,\
         LAGRECHTOUR integer default 0 not null,\
         RETURNSTOUR smallint default 0 not null,\
         ISPSYCHOTROPICTRANSPORTEXCLUDED smallint default 0 not null) in ksc extent size 1020 next size 104 lock mode row;



/* CreateIndexStatement of CUSTOMERTOUR ***************************************/

 #define CUSTOMERTOUR_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of CUSTOMERTOUR ***************************************/

 #define CUSTOMERTOUR_DELETE_INDEX(_X_)\
              _X_ = 0;\


#endif   // GUARD

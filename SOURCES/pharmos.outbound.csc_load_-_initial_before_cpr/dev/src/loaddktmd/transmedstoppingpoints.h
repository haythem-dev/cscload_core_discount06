/* SqlDefine of TRANSMEDSTOPPINGPOINTS **************************************************/

#define TRANSMEDSTOPPINGPOINTS_PELISTE \
        "BRANCHNO,"\
        "CUSTOMERNO,"\
        "STOPPINGPOINT,"\
        "DAYTOUR,"\
        "NIGHTTOUR,"\
        "DEFAULTTOUR,"\
        "SENDERCODE,"\
        "CHECKSUM,"\
        "CREATIONDATE,"\
        "SENDINGDATE,"\
        "LASTRECVDATE,"\
        "TOURTYPE,"\
        "NOTREACHABLE"
#define TRANSMEDSTOPPINGPOINTS_UPDLISTE \
        "BRANCHNO=?,"\
        "CUSTOMERNO=?,"\
        "STOPPINGPOINT=?,"\
        "DAYTOUR=?,"\
        "NIGHTTOUR=?,"\
        "DEFAULTTOUR=?,"\
        "SENDERCODE=?,"\
        "CHECKSUM=?,"\
        "CREATIONDATE=?,"\
        "SENDINGDATE=?,"\
        "LASTRECVDATE=?,"\
        "TOURTYPE=?,"\
        "NOTREACHABLE=?"

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original struct of TRANSMEDSTOPPINGPOINTS ********************************************/

typedef struct N_TRANSMEDSTOPPINGPOINTS {
    short branchno;
    long customerno;
    char stoppingpoint[7];
    char daytour[5];
    char nighttour[5];
    char defaulttour[5];
    short sendercode;
    long checksum;
    char creationdate[11];
    char sendingdate[11];
    char lastrecvdate[11];
    char tourtype[1];
    char notreachable[1];
} transmedstoppingpointsS;

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

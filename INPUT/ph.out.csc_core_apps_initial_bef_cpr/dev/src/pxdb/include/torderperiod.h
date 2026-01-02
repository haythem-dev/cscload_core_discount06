#ifndef __GUARD_ORDERPERIOD_H_
#define __GUARD_ORDERPERIOD_H_


/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the orderperiod for MSV3                         */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdOrderPeriod
{
	cCRSORDERPERIOD_GETCURRENTORDERPERIOD			= 2,
	cCRSORDERPERIOD_GETFIRSTORDERPERIODOFWEEK		= 4,
	cCRSORDERPERIOD_GETORDERPERIODBYWEEKDAY			= 6,
	cCRSORDERPERIOD_GETFIRSTORDERPERIODBYWEEKDAY	= 8,
	cCRSORDERPERIOD_SEL_BY_BRANCHNO_CUSTOMERNO		= 16
}   tCRSID_ORDERPERIOD;

/*----------------------------------------------------------------------------*/
/*                            OrderPeriod                                     */
/*----------------------------------------------------------------------------*/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tORDERPERIOD
{
	long CustomerNo;
	char TourID[7];
	long DatePicking;
	long ConsTime;
	long ID;
	short BranchNo;
	short WeekDay;
	long FromTime;
	long ToTime;
	long OrderPeriodID;
	long MainTime;
	long ChangeDate;
	short KippZeit;
	long Anz_Erfasst;
	long Anz_Faktur;
	long FetchRel;
};

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/*----------------------------------------------------------------------------*/
/* forward declarations for pxverbund                                         */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

int pxOrderPeriodStartBrowse	(struct tORDERPERIOD* record, int browseid, long currenttime);
int pxOrderPeriodGetNext		(struct tORDERPERIOD* record, int browseid);
int pxOrderPeriodEndBrowse		(int browseid);
int pxOrderPeriodRead			(struct tORDERPERIOD* record);

#ifdef __cplusplus
}
#endif

#endif   // __GUARD_ORDERPERIOD_H_

#include "ndefs.h"
#include "torderperiod.h"
#include "pxdatetime.h"
#include "pxdbfunc.h"

extern int functionnr;

/*-------------------------------------------------------------------*/

int pxOrderPeriodStartBrowse(struct tORDERPERIOD* record, int browseid, long timehhmm)
{	
	EXEC SQL BEGIN DECLARE SECTION;
	struct tORDERPERIOD* recordp;	
	long currentweekday;
	long currenttime;
	long currentdate;
	EXEC SQL END   DECLARE SECTION;    

	functionnr = F_ORDERPERIOD * 10 + F_StartBrowse;
	recordp = record;
		
	currenttime = timehhmm;
	currentweekday = basardatetime_getCurrentWeekday();	
	currentdate = basardatetime_getCurrentDateYYYYMMDD();

// Cursor C0
	EXEC SQL DECLARE C0 CURSOR FOR			
		SELECT FIRST 1 opt.id, op.tourid, op.weekday, op.id, opt.fromtime, opt.totime, opt.maintime, opt.changedate
		FROM orderperiodtime opt 
		JOIN orderperiod op ON opt.order_period_id=op.id
		WHERE 
		( 	
			(:currentweekday = op.weekday AND :currenttime < opt.totime)
			OR (:currentweekday < op.weekday)	
		)
		AND op.branchno = :recordp->BranchNo
		AND op.customerno = :recordp->CustomerNo
		ORDER BY op.weekday, opt.totime, op.tourid;

// Cursor C1
	EXEC SQL DECLARE C1 CURSOR FOR			
		SELECT FIRST 1 opt.id, op.tourid, op.weekday, op.id, opt.fromtime, opt.totime, opt.maintime, opt.changedate
		FROM orderperiodtime opt 
		JOIN orderperiod op ON opt.order_period_id=op.id
		WHERE op.branchno = :recordp->BranchNo
		AND op.customerno = :recordp->CustomerNo
		ORDER BY op.weekday, opt.totime, op.tourid;

// Cursor C2
	EXEC SQL DECLARE C2 CURSOR FOR			
		SELECT FIRST 1 opt.id, op.tourid, op.weekday, op.id, opt.fromtime, opt.totime, opt.maintime, opt.changedate
		FROM orderperiodtime opt 
		JOIN orderperiod op ON opt.order_period_id=op.id
		JOIN paraauftragbearb p ON p.filialnr=op.branchno
		JOIN tourplantag tpt ON tpt.vertriebszentrumnr=op.branchno 
								AND tpt.idfnr=op.customerno
								AND tpt.tourid=op.tourid
								AND ( weekday(to_date(cast(tpt.datumkommi as varchar(8)),'%Y%m%d'))=op.weekday OR p.tourweekday=op.weekday )
								AND tpt.datumkommi= :currentdate
								AND tpt.tourinaktiv!='1'
		WHERE op.weekday = :recordp->WeekDay
		AND :currenttime < opt.totime
		AND op.branchno = :recordp->BranchNo
		AND op.customerno = :recordp->CustomerNo		
		AND op.weekday= :currentweekday		
		ORDER BY opt.totime, op.tourid;

// Cursor C3
	EXEC SQL DECLARE C3 CURSOR FOR			
		SELECT FIRST 1 opt.id, op.tourid, op.weekday, op.id, opt.fromtime, opt.totime, opt.maintime, opt.changedate
		FROM orderperiodtime opt 
		JOIN orderperiod op ON opt.order_period_id=op.id
		WHERE op.weekday >= :recordp->WeekDay		
		AND op.branchno = :recordp->BranchNo
		AND op.customerno = :recordp->CustomerNo
		ORDER BY op.weekday, opt.totime, op.tourid;

// Cursor C4
	EXEC SQL DECLARE C4 CURSOR FOR			
		SELECT opt.id, op.tourid, op.weekday, op.id, opt.fromtime, opt.totime, opt.maintime, opt.changedate
		FROM orderperiodtime opt 
		JOIN orderperiod op ON opt.order_period_id=op.id
		WHERE op.branchno = :recordp->BranchNo
		AND op.customerno = :recordp->CustomerNo
		ORDER BY op.weekday, opt.totime, op.tourid;

	// open cursor
	switch (browseid)
	{
		case cCRSORDERPERIOD_GETCURRENTORDERPERIOD:
			EXEC SQL OPEN C0;
			break;
		case cCRSORDERPERIOD_GETFIRSTORDERPERIODOFWEEK:
			EXEC SQL OPEN C1;
			break;
		case cCRSORDERPERIOD_GETORDERPERIODBYWEEKDAY:
			EXEC SQL OPEN C2;
			break;
		case cCRSORDERPERIOD_GETFIRSTORDERPERIODBYWEEKDAY:
			EXEC SQL OPEN C3;
			break;		
		case cCRSORDERPERIOD_SEL_BY_BRANCHNO_CUSTOMERNO:
			EXEC SQL OPEN C4;
			break;		
		default:
			EXEC SQL OPEN C0;
			break;
	}
	if( 0 == SQLCODE )
	{
		return 0;
	}
	if( 100 == SQLCODE )
	{
		return cDBXR_NOTFOUND;
	}
	return cDBXR_IOERROR;
}

/*-------------------------------------------------------------------*/

int pxOrderPeriodGetNext(struct tORDERPERIOD* record, int browseid)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct tORDERPERIOD * recordp;
	EXEC SQL END   DECLARE SECTION;

	functionnr = F_ORDERPERIOD * 10 + F_GetNext;
	recordp = record;

	switch (browseid)
	{    
		case cCRSORDERPERIOD_GETCURRENTORDERPERIOD:
			EXEC SQL FETCH C0 INTO :recordp->ID, :recordp->TourID, :recordp->WeekDay, :recordp->OrderPeriodID, :recordp->FromTime, :recordp->ToTime, :recordp->MainTime, :recordp->ChangeDate; 
			break;       
		case cCRSORDERPERIOD_GETFIRSTORDERPERIODOFWEEK:
			EXEC SQL FETCH C1 INTO :recordp->ID, :recordp->TourID, :recordp->WeekDay, :recordp->OrderPeriodID, :recordp->FromTime, :recordp->ToTime, :recordp->MainTime, :recordp->ChangeDate; 
			break;       
		case cCRSORDERPERIOD_GETORDERPERIODBYWEEKDAY:
			EXEC SQL FETCH C2 INTO :recordp->ID, :recordp->TourID, :recordp->WeekDay, :recordp->OrderPeriodID, :recordp->FromTime, :recordp->ToTime, :recordp->MainTime, :recordp->ChangeDate; 
			break;
		case cCRSORDERPERIOD_GETFIRSTORDERPERIODBYWEEKDAY:
			EXEC SQL FETCH C3 INTO :recordp->ID, :recordp->TourID, :recordp->WeekDay, :recordp->OrderPeriodID, :recordp->FromTime, :recordp->ToTime, :recordp->MainTime, :recordp->ChangeDate;
			break;
		case cCRSORDERPERIOD_SEL_BY_BRANCHNO_CUSTOMERNO:
			EXEC SQL FETCH C4 INTO :recordp->ID, :recordp->TourID, :recordp->WeekDay, :recordp->OrderPeriodID, :recordp->FromTime, :recordp->ToTime, :recordp->MainTime, :recordp->ChangeDate;
			break;
		default:
			EXEC SQL FETCH C0 INTO :recordp->ID, :recordp->TourID, :recordp->WeekDay, :recordp->OrderPeriodID, :recordp->FromTime, :recordp->ToTime, :recordp->MainTime, :recordp->ChangeDate;
			break;
	}
    if( 0 == SQLCODE )
	{
		return 0;
	}
    if( 100 == SQLCODE )  
	{
		return cDBXR_ENDOFDATA;
	}
    return cDBXR_IOERROR;
}

/*-------------------------------------------------------------------*/

int pxOrderPeriodEndBrowse(int browseid)
{
	functionnr = F_ORDERPERIOD * 10 + F_EndBrowse;
	switch (browseid)
	{
		case cCRSORDERPERIOD_GETCURRENTORDERPERIOD:
			EXEC SQL CLOSE C0;
			break;       
		case cCRSORDERPERIOD_GETFIRSTORDERPERIODOFWEEK:
			EXEC SQL CLOSE C1;
			break;       
		case cCRSORDERPERIOD_GETORDERPERIODBYWEEKDAY:
			EXEC SQL CLOSE C2;
			break;
		case cCRSORDERPERIOD_GETFIRSTORDERPERIODBYWEEKDAY:
			EXEC SQL CLOSE C3;
			break;
		case cCRSORDERPERIOD_SEL_BY_BRANCHNO_CUSTOMERNO:
			EXEC SQL CLOSE C4;
			break;
		default:
			EXEC SQL CLOSE C0;
			break;
	}
	return 0;
}

/*-------------------------------------------------------------------*/

int pxOrderPeriodRead(struct tORDERPERIOD* record)
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct tORDERPERIOD* recordp;
	EXEC SQL END DECLARE SECTION;

	functionnr = F_ORDERPERIOD * 10 + F_Read;
	recordp = record;

	EXEC SQL
		SELECT
			op.customerno,
			op.tourid,
			op.id,
			op.branchno,
			op.weekday,
			opt.id,
			opt.fromtime,
			opt.totime,
			opt.maintime,
			opt.changedate
		INTO
			:recordp->CustomerNo,
			:recordp->TourID,
			:recordp->OrderPeriodID,
			:recordp->BranchNo,
			:recordp->WeekDay,
			:recordp->ID,
			:recordp->FromTime,
			:recordp->ToTime,
			:recordp->MainTime,
			:recordp->ChangeDate
		FROM orderperiodtime opt
		JOIN orderperiod op ON opt.order_period_id=op.id
		WHERE opt.id = :recordp->ID;

	if (SQLCODE == 0)
	{
		return 0;
	}
	if (SQLCODE == 1)                /* found, but more than 1 exists */
	{
		return cDBXR_ISDUPLICATE;
	}
	if (SQLCODE == 100)
	{
		return cDBXR_NOTFOUND;
	}
	return cDBXR_IOERROR;
}

/*-------------------------------------------------------------------*/

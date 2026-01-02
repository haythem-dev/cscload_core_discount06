#ifndef __GUARD_TTOURMASTERDATA_H_
#define __GUARD_TTOURMASTERDATA_H_

/*----------------------------------------------------------------------------*/
typedef enum CrsIdTourMasterData
{
	cCRSTOURMASTERDATA_GETBYTOURID = 2 
}   tCRSID_TOURMASTERDATA;

/*----------------------------------------------------------------------------*/
/*                            TourMasterData                                  */
/*----------------------------------------------------------------------------*/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tTOURMASTERDATA
{	
	long PickingDate;	
	short BranchNo;
	char TourID[7];
	long DecTour; // LagRechTour	
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

int TourMasterDataStartBrowse	(struct tTOURMASTERDATA* record, const char* dbName, int browseid);
int TourMasterDataGetNext		(struct tTOURMASTERDATA* record, int browseid);
int TourMasterDataEndBrowse		(int browseid);

#ifdef __cplusplus
}
#endif

#endif   // __GUARD_TTOURMASTERDATA_H_

#ifndef GUARD_SALESMAN_H
#define GUARD_SALESMAN_H

typedef enum CrsIdSalesMan
{
	cCRSSALESMAN_GETDATAFORKEY				= 2,
	cCRSSALESMAN_GETDATAFORPARTNER      	= 3
} tCRSID_SALESMAN;

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tSALESMAN
{
	short BRANCHNO;
	short SALESMANNO;
	char SALESMANNAME[31];
	char SALESMANSTREET[31];
	char SALESMANCITY[31];
	char POSTCODE[6];
	short ACTIVE_FLAG;
	short SPREWHOLE;
	char EMAILADRESS[51];
    long PARTNERNO;
    char SERVER[51];
};

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

#ifdef __cplusplus
extern "C" {
#endif

int pxSalesManStartBrowse             ( struct tSALESMAN* record,int browseid);
int pxSalesManGetNext             	  ( struct tSALESMAN* record,int browseid);
int pxSalesManEndBrowse           	  ( int browseid);
int pxSalesManInsert            	  ( struct tSALESMAN* record);

#ifdef __cplusplus
}
#endif

#endif   // GUARD

#ifndef GUARD_TRANSMISSIONRESPONSE_H
#define GUARD_TRANSMISSIONRESPONSE_H


/*****************************************************************************/
/*  TransmissionResponse                                                     */
/*  orderresponses Tabelle                                                   */
/*****************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tTRANSMISSIONRESPONSE
{
	long	Id;                           /* Serial */
	char	Request_Id[36 + 1];           /* Transmission GUID */
	long	Support_Id;                   /* Support Id */
	short	BranchNo;
	long	CustomerNo;
	short	Is_Offer;
	char*	ResponseAsXml;
	long	Create_Date;
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


int pxTransmissionResponseRead         ( struct tTRANSMISSIONRESPONSE* record);
int pxTransmissionResponseReadLock     ( struct tTRANSMISSIONRESPONSE* record);
int pxTransmissionResponseUpdate       ( struct tTRANSMISSIONRESPONSE* record);
int pxTransmissionResponseInsert       ( struct tTRANSMISSIONRESPONSE* record);
int pxTransmissionResponseDelete       ( struct tTRANSMISSIONRESPONSE* record);


#ifdef __cplusplus
}
#endif

#endif // GUARD_TRANSMISSIONRESPONSE_H

#ifndef __PP_TNUMMER_H_
#define __PP_TNUMMER_H_


/*----------------------------------------------------------------------------*/
/*  Cursor id's for different sequence numbers                                */
/*----------------------------------------------------------------------------*/
enum CrsIdSequenceNumber
{
	cSEQUENCE_ORDERNO = 1,			// get new CSC orderno
	cSEQUENCE_BATCHORDERNO = 7,		// Special FR Prewhole
	cSEQUENCE_BATCHORDERNO2 = 8     // Special FR Prewhole
};

/*****************************************************************************/
/*  Nummernvergabe                                                           */
/*  Vergabe von eindeutigen Nummern                                          */
/*****************************************************************************/

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

struct tNUMMER
{
	short          NummerTyp;                    /* NummerTyp */
	long           NummerWert;                   /* NummerWert */
	long           NummerMindest;                /* NummerMindest */
	long           NummerHoechst;                /* NummerHoechst */
	long           NummerInkrement;              /* NummerInkrement */
	short          NummerModus;                  /* NummerModus */
};

struct tNUMMERSEQUENCE
{
	int		SequenceType;
	long	NextVal;
};

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif

/*----------------------------------------------------------------------------*/
/*  Function prototypes.                                                      */
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {                            /* Assume C declarations for C++      */
#endif

int pxNummerSequence ( struct tNUMMERSEQUENCE* record);
int pxNummerRead    ( struct tNUMMER* record);
int pxNummerReadLock( struct tNUMMER* record);
int pxNummerUpdate  ( struct tNUMMER* record);
int pxNummerInsert  ( struct tNUMMER* record);

#ifdef __cplusplus
}                                       /* close C declarations for C++       */
#endif

#endif

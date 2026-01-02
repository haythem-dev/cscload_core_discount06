/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXXMLDEFS.H
Generic order entry server definitions.

REVISION HISTORY

31 Mar 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXXML_INC
   #define PXXML_INC

/*----------------------------------------------------------------------------*/
/*  Global server function prototypes for XML Usage                           */
/*----------------------------------------------------------------------------*/
short  pxCustomerRouting(pxSession* session, short VZ, const long kdnr);
int    pxCheckReferenceNr(pxSession* session, short VZ, const long kdnr, char* message );
int    pxInsertReferenceNr(pxSession* session, short VZ, const long kdnr, const char* reference );
nString GetOrderZugrund(pxSession* session,  const long KdAuftragNr);
std::string generateUUID();


#endif

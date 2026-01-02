/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Global class-independent utility functions.

REVISION HISTORY

31 Mar 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include <pxrecord.h>
#include <date.hpp>
#include <nntypes.h>
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxcustrouting.hpp"
#include "pxcstonr.hpp"
#include "pxorder.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* pxCustomerRouting: this function looks for an orderchange to another       */
/* company . If an entry fits the destinationbranchnumber will be returned    */
/* otherwise 0 returns                                                        */
/*----------------------------------------------------------------------------*/
short
pxCustomerRouting
(
          pxSession*    session,
          short         vz,
    const long          kdnr
)
{
    short retvz = vz;                  // save vz
    pxCustRoutingList*  routinglist = NULL;
    pxCustRouting*      entry       = NULL;
    nDate   today;

    if (!session->Device()->IsDCT() )   // is not a dct
        return retvz;

    routinglist = new pxCustRoutingList(session);
    routinglist->Select(kdnr, vz, today.GetDayOfWeek());
    pxCustRoutingListIter cursor(*routinglist);
    if (routinglist->Entries())
    {
        while ( (entry = (pxCustRouting*) ++cursor) != NULL )
        {
            if ( entry->TimeInWindow() )
            {
                retvz = entry->DestBranchNo();
            }
        }
    }
    delete routinglist;
    return retvz;
}

/*----------------------------------------------------------------------------*/
/* pxCheckReferenceNr: this functions looks for an existing referencenumber   */
/* within the table CustomerOrderNumber. If exist, an errornumber and an      */
/* errormessage returns, otherwise a zero returns                             */
/* The referencenumber is                                                     */
/*----------------------------------------------------------------------------*/
int
pxCheckReferenceNr
(
          pxSession*    session,
          short         vz,
    const long          kdnr,
          char*         message
)
{
    int retval = 0;
    nString cOrdnum = message;
    cOrdnum.Trim(session->isCroatia() ? 30 : 9);
    cOrdnum.Strip();
    if ( cOrdnum.IsEmpty() )
        return retval;

    if ( session->isFrance() )
    {
        return retval;
    }

    nString cProcessNr = "0";
    pxCustOrderNumber * cnum = new pxCustOrderNumber(session, vz, kdnr, cOrdnum, cProcessNr);

    if ( cnum->IsGoodState() )
    {
        retval = CMSG_ORD_DOUBLE_ORDER;
        nMessage answer (session->CMsgStream(), retval, 0);
        sprintf(message, answer.String());
    }
    delete cnum;
    return retval;
}

/*----------------------------------------------------------------------------*/
/* pxInsertReferenceNr: this functions inserts a referencenumber entry into   */
/* the table CustomerOrderNumber. In the case of an error, the erronumber and */
/* the corresponding errormessage returns                                     */
/*----------------------------------------------------------------------------*/
int
pxInsertReferenceNr
(
          pxSession*    session,
          short         vz,
    const long          kdnr,
    const char*         reference
)
{
    int retval = 0;
    nString cOrdnum = reference;
    cOrdnum.Trim(session->isCroatia() ? 30 : 9);
    cOrdnum.Strip();
    if ( cOrdnum.IsEmpty() )
        return retval;

    if ( session->isFrance() )
    {
        return retval;
    }

    nString cProcessNr = "0";
    pxCustOrderNumber * cnum = new pxCustOrderNumber(session, vz, kdnr, cOrdnum, cProcessNr);

    if ( !cnum->IsGoodState() )
    {
        retval = cnum->Put();
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/* GetOrderZugrund                                                            */
/* the table CustomerOrderNumber. In the case of an error, the erronumber and */
/* the corresponding errormessage returns                                     */
/*----------------------------------------------------------------------------*/
nString
GetOrderZugrund
(
          pxSession*    session,
    const long          KdAuftragNr
)
{
    char Zugrund[mSIZEOF(tKDAUFTRAG, ZuGrund)];
    memset(Zugrund, 0, mSIZEOF(tKDAUFTRAG, ZuGrund));
    nBitMap RCEntry;

    pxOrder* op = new pxOrder(session, KdAuftragNr, cDBGET_READONLY);
    if (op->IsGoodState())
    {
        RCEntry = op->RCEntryDeffered();
        RCEntry.Export(Zugrund, mSIZEOF(tKDAUFTRAG, ZuGrund) - 1);
        //Zugrund.Strip();
    }
    delete op;
    return nString(Zugrund);
}

#ifdef _AIX
#include <uuid.h>
#elif defined WIN32
#include <rpc.h>
#else
#include <uuid/uuid.h>
#endif

std::string generateUUID()
{
	uuid_t   uuid;
#ifdef _AIX
	unsigned32 status = 0;
	unsigned char *uuidBuff = 0;

	uuid_create(&uuid, &status);
	assert(status == uuid_s_ok);
	uuid_to_string(&uuid, &uuidBuff, &status);
	assert(status == uuid_s_ok);
	std::string suuid((char*)uuidBuff);
	free(uuidBuff);

	return suuid;
#elif defined WIN32
	RPC_STATUS status;
	unsigned char* uuidBuff = 0;

	status = UuidCreate(&uuid);
	assert(status == RPC_S_OK);
	status = UuidToString(&uuid, &uuidBuff);
	assert(status == RPC_S_OK);
	std::string suuid((char*)uuidBuff);
	RpcStringFree(&uuidBuff);

	return suuid;
#else // Solaris and thelike
	char uuidBuff[36];
	uuid_generate_random(uuid);
	uuid_unparse(uuid, uuidBuff);

	return std::string(uuidBuff);
#endif
}

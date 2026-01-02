/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Implementation of class pxDeliveryLog  methods.

REVISION HISTORY

23 Nov 1996 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxdellog.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxDeliveryLog :: pxDeliveryLog
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDeliveryLog :: pxDeliveryLog
(
    pxDeliveryLog& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tNACHLIEFPROT structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxDeliveryLog :: pxDeliveryLog
(
    pxSession   *session,
    tNACHLIEFPROT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Use pxOrderItem and pxDeliveryPos to construct this instance.             */
/*----------------------------------------------------------------------------*/
pxDeliveryLog :: pxDeliveryLog
(
    pxOrderItem&   Item,
    pxVerbund::subsequentDelivery::pxDeliveryPos& Dpos
)
    : pxDBRecord( Item.Order().Session())
{
    nDate  today;                       // current date
    nClock ctime;                       // current time
    Init();
    // first items from Dpos
    ArtikelNr_      = Dpos.ArtikelNr();
    IDFNr_          = Dpos.IDFNr();
    MengeAlt_       = Dpos.Menge();
    AenderungsTyp_  = pxDLS_DELIVERY_POSSIBLE;
    PosTyp_         = Dpos.DeliveryPosTyp();
    Datum_          = Dpos.Datum();
    PosNr_          = Dpos.PosNr();
    KdAuftragNr_    = Dpos.KdAuftragNr();
    Zeit_           = ctime;

    // items from Item
    DatumNeu_       = today;
    KdAuftragNrNeu_ = Item.Order().KdAuftragNr();
    MengeAktuell_   = Item.MengeBestellt();
    MengeGeliefert_ = Item.MengeGeliefert();
    MengeNeu_       = 0;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxDeliveryLog :: ~pxDeliveryLog()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tNACHLIEFPROT structure.      */
/*----------------------------------------------------------------------------*/
tNACHLIEFPROT&
Assign
(
    tNACHLIEFPROT&           dest,
    const pxDeliveryLog&       src
)
{
    dest.ArtikelNr                 = src.ArtikelNr_                          ;
    dest.IDFNr                     = src.IDFNr_                              ;
    dest.MengeAlt                  = src.MengeAlt_                           ;
    dest.AenderungsTyp             = src.AenderungsTyp_                      ;
    dest.PosTyp                    = src.PosTyp_                             ;
    dest.Datum                     = src.Datum_.GetYYYYMMDD()                ;
    dest.PosNr                     = src.PosNr_                              ;
    dest.KdAuftragNr               = src.KdAuftragNr_                        ;
    dest.Zeit                      = src.Zeit_.GetHHMMSS()                   ;
    dest.DatumNeu                  = src.DatumNeu_.GetYYYYMMDD()             ;
    dest.KdAuftragNrNeu            = src.KdAuftragNrNeu_                     ;
    dest.MengeAktuell              = src.MengeAktuell_                       ;
    dest.MengeGeliefert            = src.MengeGeliefert_                     ;
    dest.MengeNeu                  = src.MengeNeu_                           ;
    dest.Uid                       = src.Uid_                                ;
    dest.UserBranchNo              = src.UserBranchNo_                       ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tNACHLIEFPROT structure to construct       */
/*  a pxDeliveryLog object.                                                   */
/*----------------------------------------------------------------------------*/
pxDeliveryLog&
Assign
(
    pxDeliveryLog&              dest,
    const tNACHLIEFPROT&        src
)
{
    dest.ArtikelNr_                = src.ArtikelNr                           ;
    dest.IDFNr_                    = src.IDFNr                               ;
    dest.MengeAlt_                 = src.MengeAlt                            ;
    dest.AenderungsTyp_            = src.AenderungsTyp                       ;
    dest.PosTyp_                   = (pxDeliveryLog::pxDelLogTyp)src.PosTyp  ;
    dest.Datum_                    = nDate(src.Datum)                        ;
    dest.PosNr_                    = src.PosNr                               ;
    dest.KdAuftragNr_              = src.KdAuftragNr                         ;
    dest.Zeit_                     = src.Zeit                                ;
    dest.DatumNeu_                 = nDate(src.DatumNeu)                     ;
    dest.KdAuftragNrNeu_           = src.KdAuftragNrNeu                      ;
    dest.MengeAktuell_             = src.MengeAktuell                        ;
    dest.MengeGeliefert_           = src.MengeGeliefert                      ;
    dest.MengeNeu_                 = src.MengeNeu                            ;
    dest.Uid_                      = src.Uid                                 ;
    dest.UserBranchNo_             = src.UserBranchNo                        ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxDeliveryLog :: Init()
{
    tNACHLIEFPROT    record;
    memset(&record, 0 , sizeof(tNACHLIEFPROT));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tNACHLIEFPROT struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxDeliveryLog&
pxDeliveryLog :: operator=( const pxDeliveryLog& src)
{
    tNACHLIEFPROT record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tNACHLIEFPROT structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxDeliveryLog&
pxDeliveryLog :: operator=( const tNACHLIEFPROT& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxDeliveryLog :: Put
(
)
{
    tNACHLIEFPROT record;
    memset(&record, 0, sizeof(tNACHLIEFPROT));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tNACHLIEFPROT));
}


/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxDeliveryLog :: Read
(
    const void  *record
)
{
    return pxNachLiefProtRead((tNACHLIEFPROT*)record);
}

int
pxDeliveryLog :: ReadLock
(
    const void  *record
)
{
    return pxNachLiefProtReadLock((tNACHLIEFPROT*)record);
}

int
pxDeliveryLog :: Update
(
    const void  *record
)
{
    return pxNachLiefProtUpdate((tNACHLIEFPROT*)record);
}

int
pxDeliveryLog :: Insert
(
    const void  *record
)
{
    return pxNachLiefProtInsert((tNACHLIEFPROT*)record);
}

int
pxDeliveryLog :: Delete
(
    const void  *record
)
{
    return pxNachLiefProtDelete((tNACHLIEFPROT*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxDeliveryLog list objects being inserted in the                  */
/*  following ascending sequence:                                             */
/*  ArtikelNr                                                                 */
/*----------------------------------------------------------------------------*/
int
pxDeliveryLog :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
   
    pxDeliveryLog *that = (pxDeliveryLog*)That;
    int retval = (ArtikelNr_ == that->ArtikelNr_) ? 0
               : (ArtikelNr_ > that->ArtikelNr_ ? 1 : -1);
    if ( retval == 0 )
        retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
               : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxDeliveryLogList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxNachLiefProt' object:
    pxDeliveryLog *objectp = new pxDeliveryLog(Session(), *(tNACHLIEFPROT*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxDeliveryLogList :: EndBrowse
(
    const int  cursorid
)
{
    return pxNachLiefProtEndBrowse(cursorid);
}

int
pxDeliveryLogList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxNachLiefProtGetNext((tNACHLIEFPROT*)record, cursorid);
}

int
pxDeliveryLogList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxNachLiefProtStartBrowse((tNACHLIEFPROT*)keys, cursorid);
}
/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDeliveryLogList :: pxDeliveryLogList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxDeliveryLogList :: Select
(
    const int     count_
)
{
    tNACHLIEFPROT fil;
    memset(&fil, 0, sizeof(tNACHLIEFPROT));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via ArtikelNr, KdAuftragNr                    */
/*----------------------------------------------------------------------------*/
size_t
pxDeliveryLogList :: Select
(
    const long    KdAuftragNr,
    const long    ArtikelNr,
    const int     count_
)
{
    tNACHLIEFPROT fil;
    memset(&fil, 0, sizeof(tNACHLIEFPROT));  // zero out entire record buffer
    fil.KdAuftragNr  = KdAuftragNr;
    fil.ArtikelNr    = ArtikelNr;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}



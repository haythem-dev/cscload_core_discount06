#include "pxcustinf.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo :: pxCustOrderInfo
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
pxCustOrderInfo :: pxCustOrderInfo
(
    pxCustOrderInfo& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGINFO structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo :: pxCustOrderInfo
(
    pxSession   *session,
    tKDAUFTRAGINFO& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Construct this instance with variables                 .                  */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo :: pxCustOrderInfo
(
    pxSession   *session,
    nString&     KdAuftragBestellNr,
    nString&     IDFNrIntern,
    nString&     ApoTourId,
    nString&     Versandart,
    nString&     ProcessNr
 )
    : pxDBRecord(session)
{
    Init();

    KdAuftragBestellNr_ = KdAuftragBestellNr;
    IDFNrIntern_        = atol(IDFNrIntern);
    ApoTourId_          = ApoTourId;
    VersandArt_         = Versandart;
    ProcessNr_          = atol(ProcessNr);
    EdiLieferSchein_    = '0';
    BatchAuftragNr_     = 0;
}

/*----------------------------------------------------------------------------*/
/*  Construct this instance with variables                 .                  */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo :: pxCustOrderInfo( 
	pxSession   *session,
	nString&     KdAuftragBestellNr,
    long        IDFNrIntern,
    nString&     ApoTourId,
    nString&     Versandart,
    long		  ProcessNr
 )
    : pxDBRecord(session)
{
    Init();

    KdAuftragBestellNr_ = KdAuftragBestellNr;
    IDFNrIntern_        = IDFNrIntern;
    ApoTourId_          = ApoTourId;
    VersandArt_         = Versandart;
    ProcessNr_          = ProcessNr;
    EdiLieferSchein_    = '0';
    BatchAuftragNr_     = 0;
}

/*----------------------------------------------------------------------------*/
/*  Construct this instance with variables                 .                  */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo :: pxCustOrderInfo
(
    pxSession   *session,
    long        KdAuftragNr,
    nString&     KdAuftragBestellNr,
    DBAccessMode mode
 )
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_        = KdAuftragNr;
    KdAuftragBestellNr_ = KdAuftragBestellNr;
    CheckMembers();
    EdiLieferSchein_    = '0';
    BatchAuftragNr_     = 0;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo :: pxCustOrderInfo
(
    pxSession    *session,
    long        KdAuftragNr,            // Read via this type and
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_ = KdAuftragNr;
    Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo :: ~pxCustOrderInfo()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGINFO structure.      */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGINFO&
Assign
(
    tKDAUFTRAGINFO&           dest,
    const pxCustOrderInfo&       src
)
{
    dest.KdAuftragNr               = src.KdAuftragNr_;
    dest.IDFNrIntern               = src.IDFNrIntern_;
    dest.ProcessNr                 = src.ProcessNr_;
    dest.BatchAuftragNr            = src.BatchAuftragNr_;
    dest.EdiLieferSchein           = src.EdiLieferSchein_;
                              ;
    dest.KdAuftragBestellNr[0] = ' ';
    src.KdAuftragBestellNr_.GetData(dest.KdAuftragBestellNr);
    dest.ApoTourId[0] = ' ';
    src.ApoTourId_.GetData(dest.ApoTourId);
    dest.VersandArt[0] = ' ';
    src.VersandArt_.GetData(dest.VersandArt);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGINFO structure to                */
/*  a pxCustOrderInfo object.                                                   */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo&
Assign
(
    pxCustOrderInfo&              dest,
    const tKDAUFTRAGINFO&    src
)
{
    dest.KdAuftragNr_              = src.KdAuftragNr;
    dest.IDFNrIntern_              = src.IDFNrIntern;
    dest.ProcessNr_                = src.ProcessNr;
    dest.KdAuftragBestellNr_       = src.KdAuftragBestellNr;
    dest.ApoTourId_                = src.ApoTourId;
    dest.VersandArt_               = src.VersandArt;
    dest.BatchAuftragNr_           = src.BatchAuftragNr;
    dest.EdiLieferSchein_          = src.EdiLieferSchein;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustOrderInfo :: Init()
{
    tKDAUFTRAGINFO    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGINFO));
    EdiLieferSchein_ = '0';
    BatchAuftragNr_  = 0;
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Checkmembers     .                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustOrderInfo :: CheckMembers
(
)
{
    IDFNrIntern_ = 0;
    ApoTourId_.Clear();
    VersandArt_.Clear();
    ProcessNr_ = 0;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGINFO struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo&
pxCustOrderInfo :: operator=( const pxCustOrderInfo& src)
{
    tKDAUFTRAGINFO record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGINFO structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustOrderInfo&
pxCustOrderInfo :: operator=( const tKDAUFTRAGINFO& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustOrderInfo :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGINFO record;
    memset(&record, 0, sizeof(tKDAUFTRAGINFO));
    record.KdAuftragNr   = KdAuftragNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGINFO struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_CUSTINFO_ENTRY_NOTFOUND, KdAuftragNr_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustOrderInfo :: Put
(
)
{
    tKDAUFTRAGINFO record;
    memset(&record, 0, sizeof(tKDAUFTRAGINFO));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGINFO));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustOrderInfo :: Read
(
    const void  *record
)
{
    return pxCustOrderInfoRead((tKDAUFTRAGINFO*)record);
}


int
pxCustOrderInfo :: Insert
(
    const void  *record
)
{
    return pxCustOrderInfoInsert((tKDAUFTRAGINFO*)record);
}

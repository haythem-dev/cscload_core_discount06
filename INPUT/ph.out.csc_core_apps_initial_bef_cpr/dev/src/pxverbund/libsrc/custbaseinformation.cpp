/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxCustBaseInformation  methods.

REVISION HISTORY

23 April 2008 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxcustbaseinformation.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustBaseInformation :: pxCustBaseInformation
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
pxCustBaseInformation :: pxCustBaseInformation
(
    pxCustBaseInformation& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKNDAUSKU structure to construct this instance.                    */
/*----------------------------------------------------------------------------*/
pxCustBaseInformation :: pxCustBaseInformation
(
    pxSession   *session,
    tKNDAUSKU& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Construct this object                                                     */
/*----------------------------------------------------------------------------*/
pxCustBaseInformation :: pxCustBaseInformation
(
    pxSession      *session,
    const short         BranchNo,
    const long          KundenNr
)
    : pxDBRecord(session)
{
    Init();
    VertriebszentrumNr_      = BranchNo;
    KundenNr_                = KundenNr;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustBaseInformation :: ~pxCustBaseInformation()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKNDAUSKU structure.      */
/*----------------------------------------------------------------------------*/
tKNDAUSKU&
Assign
(
    tKNDAUSKU&           dest,
    const pxCustBaseInformation&       src
)
{
    dest.VertriebszentrumNr        = src.VertriebszentrumNr_       ;
    dest.KundenNr                  = src.KundenNr_                 ;
    dest.EilbotenZuschlag          = src.EilbotenZuschlag_         ;
    dest.DispoGebuehr              = src.DispoGebuehr_             ;
    dest.BTMGebuehr                = src.BTMGebuehr_               ;
    dest.DokuGebuehr               = src.DokuGebuehr_              ;
    dest.LogistikAufschlag         = src.LogistikAufschlag_        ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKNDAUSKU structure to                    */
/*  a pxCustBaseInformation object.                                                     */
/*----------------------------------------------------------------------------*/
pxCustBaseInformation&
Assign
(
    pxCustBaseInformation&              dest,
    const tKNDAUSKU&    src
)
{
    dest.VertriebszentrumNr_       = src.VertriebszentrumNr       ;
    dest.KundenNr_                 = src.KundenNr                 ;
    dest.EilbotenZuschlag_         = src.EilbotenZuschlag         ;
    dest.DispoGebuehr_             = src.DispoGebuehr             ;
    dest.BTMGebuehr_               = src.BTMGebuehr               ;
    dest.DokuGebuehr_              = src.DokuGebuehr              ;
    dest.LogistikAufschlag_        = src.LogistikAufschlag        ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustBaseInformation :: Init()
{
    tKNDAUSKU    record;
    memset(&record, 0 , sizeof(tKNDAUSKU));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKNDAUSKU struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCustBaseInformation&
pxCustBaseInformation :: operator=( const pxCustBaseInformation& src)
{
    tKNDAUSKU record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKNDAUSKU structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustBaseInformation&
pxCustBaseInformation :: operator=( const tKNDAUSKU& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustBaseInformation :: Get
(
    DBAccessMode mode
)

{
    tKNDAUSKU record;
    memset(&record, 0, sizeof(tKNDAUSKU));
    record.VertriebszentrumNr       = VertriebszentrumNr_;
    record.KundenNr                 = KundenNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKNDAUSKU struct
    //else if ( retval > cDBXR_NORMAL )
    //   ExternalCondition(CMsgStream(),
    //                     CMSG_AD_DELPOS_NOTFOUND, KdAuftragNr_,PosNr_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustBaseInformation :: Read
(
    const void  *record
)
{
    return pxCustBaseInformationRead((tKNDAUSKU*)record);
}

int
pxCustBaseInformation :: ReadLock
(
    const void  *record
)
{
    return pxCustBaseInformationReadLock((tKNDAUSKU*)record);
}


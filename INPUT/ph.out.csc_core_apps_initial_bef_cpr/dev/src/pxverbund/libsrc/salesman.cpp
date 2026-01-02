/*
 * cremamail.cpp
 *
 *  Created on: 02.04.2013
 *      Author: martin.zoephel
 */

#include "pxsalesman.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxSalesMan :: pxSalesMan
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
pxSalesMan :: pxSalesMan
(
        pxSalesMan& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tSALESMAN structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxSalesMan :: pxSalesMan
(
    pxSession   *session,
    tSALESMAN& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

pxSalesMan :: pxSalesMan
(
    pxSession   *session,
    short branchNo,
    short salesmanNo
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_ = branchNo;
    SalesmanNo_ = salesmanNo;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxSalesMan :: ~pxSalesMan()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDISCOUNT structure.           */
/*----------------------------------------------------------------------------*/
tSALESMAN& pxSalesMan :: Assign
(
    tSALESMAN&           dest,
    const pxSalesMan&       src
)
{
    dest.BRANCHNO = src.BranchNo_                       ;
    dest.SALESMANNO = SalesmanNo_                       ;
    src.SalesmanName_.GetData(dest.SALESMANNAME)        ;
    src.SalesmanStreet_.GetData(dest.SALESMANSTREET)    ;
    src.SalesmanCity_.GetData(dest.SALESMANCITY)        ;
    src.PostCode_.GetData(dest.POSTCODE)                ;
    dest.ACTIVE_FLAG = SActive_                         ;
    dest.SPREWHOLE = SPreWhole_                         ;
    src.EmailAdress_.GetData(dest.EMAILADRESS)          ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDISCOUNT structure to                     */
/*  a pxDiscount object.                                                      */
/*----------------------------------------------------------------------------*/
pxSalesMan& pxSalesMan :: Assign
(
    pxSalesMan&              dest,
    const tSALESMAN&    src
)
{

    dest.BranchNo_              = src.BRANCHNO                  ;
    dest.SalesmanNo_            = src.SALESMANNO                ;
    dest.SalesmanName_          = src.SALESMANNAME              ;
    dest.SalesmanStreet_        = src.SALESMANSTREET            ;
    dest.SalesmanCity_          = src.SALESMANCITY              ;
    dest.PostCode_              = src.POSTCODE                  ;
    dest.SActive_               = src.ACTIVE_FLAG               ;
    dest.SPreWhole_             = src.SPREWHOLE                 ;
    dest.EmailAdress_           = src.EMAILADRESS               ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void pxSalesMan :: Init()
{
    tSALESMAN    record;
    memset(&record, 0 , sizeof(tSALESMAN));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDISCOUNT struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxSalesMan& pxSalesMan :: operator=( const pxSalesMan& src)
{
    tSALESMAN record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISCOUNT structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxSalesMan& pxSalesMan :: operator=( const tSALESMAN& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int pxSalesMan :: Get
(
    DBAccessMode /*mode*/
)

{
    tSALESMAN record;
    memset(&record, 0, sizeof(tSALESMAN));
    int retval = nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tSALESMAN struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*----------------------------------------------------------------------------*/
int
pxSalesMan :: CompareTo
(
    const nCollectable*   That,
          void*           /*p*/,
    const long            /*lparm*/
)   const

{
    pxSalesMan *that = (pxSalesMan*)That;

    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
       retval = (SalesmanNo_ == that->SalesmanNo_) ? 0
                : (SalesmanNo_ > that->SalesmanNo_ ? 1 : -1);

    if ( retval == 0 )
        retval = (SalesmanName_ == that->SalesmanName_) ? 0
                  : (SalesmanName_ > that->SalesmanName_ ? 1 : -1);

    if ( retval == 0 )

        retval = (SalesmanStreet_ == that->SalesmanStreet_) ? 0
                  : (SalesmanStreet_ > that->SalesmanStreet_ ? 1 : -1);

    if ( retval == 0 )

        retval = (SalesmanCity_ == that->SalesmanCity_) ? 0
                  : (SalesmanCity_ > that->SalesmanCity_ ? 1 : -1);

    if ( retval == 0 )
       retval = (PostCode_ == that->PostCode_) ? 0
                : (PostCode_ > that->PostCode_ ? 1 : -1);

    if ( retval == 0 )
       retval = (SActive_ == that->SActive_) ? 0
                : (SActive_ > that->SActive_ ? 1 : -1);

    if ( retval == 0 )
       retval = (SPreWhole_ == that->SPreWhole_) ? 0
                : (SPreWhole_ > that->SPreWhole_ ? 1 : -1);

    if ( retval == 0 )
       retval = (EmailAdress_ == that->EmailAdress_) ? 0
                : (EmailAdress_ > that->EmailAdress_ ? 1 : -1);

    return retval;
}

pxSalesManList :: pxSalesManList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

tSALESMAN pxSalesManList :: SelectBySalesManNo
(
    const short     salesManNo,
    const short     branchno
)
{
    tSALESMAN fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tSALESMAN));  // zero out entire record buffer

    fil.SALESMANNO = salesManNo;
    fil.BRANCHNO = branchno;

    int cursorid = cCRSSALESMAN_GETDATAFORKEY;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tSALESMAN pxSalesManList :: SelectByPartnerNo
(
    const int       partnerNo,
    const short     branchno
)
{
    tSALESMAN fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tSALESMAN));  // zero out entire record buffer

    fil.PARTNERNO = partnerNo;
    fil.BRANCHNO = branchno;

    int cursorid = cCRSSALESMAN_GETDATAFORPARTNER;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

int pxSalesManList :: EndBrowse
(
    const int  cursorid
)
{
    return pxSalesManEndBrowse(cursorid);
}

int pxSalesManList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxSalesManGetNext((struct tSALESMAN*)record, cursorid);
}

int pxSalesManList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxSalesManStartBrowse((struct tSALESMAN*)keys, cursorid);
}

nCollectable* pxSalesManList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxDiscount' object:
    pxSalesMan *objectp = new pxSalesMan(Session(), *(struct tSALESMAN*) record);
    InsertAscending(objectp);
    return objectp;
}

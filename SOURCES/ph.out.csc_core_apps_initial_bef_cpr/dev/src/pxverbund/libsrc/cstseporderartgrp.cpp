/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxCstSepOrderArtGroup  methods.

REVISION HISTORY

09 December 2008 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxcstseporderartgrp.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxcustdeldelivery.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroup :: pxCstSepOrderArtGroup
(
    pxSession *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroup :: pxCstSepOrderArtGroup
(
    pxCstSepOrderArtGroup& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCSTSEPORDERARTGRP structure to construct this instance.              */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroup :: pxCstSepOrderArtGroup
(
    pxSession *session,
    tCSTSEPORDERARTGRP& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  "Copy" constructor using a pointer to the source rather than a reference. */
/*  NULL pointer safe.                                                        */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroup :: pxCstSepOrderArtGroup
(
    pxSession *session,
    const pxCstSepOrderArtGroup  *srcp
)
    : pxDBRecord(session)
{
    Init();
    if (srcp != NULL)
        (*this) = *srcp;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroup :: ~pxCstSepOrderArtGroup()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCSTSEPORDERARTGRP structure.  */
/*----------------------------------------------------------------------------*/
tCSTSEPORDERARTGRP&
Assign
(
    tCSTSEPORDERARTGRP&           dest,
    const pxCstSepOrderArtGroup&  src
)
{
    dest.BranchNo                  = src.BranchNo_       ;
    dest.CustomerNo                = src.CustomerNo_     ;
    dest.ArtGrp                    = src.ArtGrp_         ;
    dest.KoArt                     = src.KoArt_          ;
    dest.BuchArt                   = src.BuchArt_        ;
    dest.DeferOrder                = src.DeferOrder_     ;

    strcpy(dest.KdAuftragArt, " ");
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCSTSEPORDERARTGRP structure to            */
/*  a pxCstSepOrderArtGroup object.                                           */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroup&
Assign
(
    pxCstSepOrderArtGroup&       dest,
    const tCSTSEPORDERARTGRP&    src
)
{
    dest.BranchNo_                  = src.BranchNo       ;
    dest.CustomerNo_                = src.CustomerNo     ;
    dest.ArtGrp_                    = src.ArtGrp         ;
    dest.KdAuftragArt_              = src.KdAuftragArt   ;
    dest.KoArt_                     = src.KoArt          ;
    dest.BuchArt_                   = src.BuchArt        ;
    dest.DeferOrder_                = src.DeferOrder     ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCstSepOrderArtGroup :: Init()
{
    tCSTSEPORDERARTGRP record;
    memset(&record, 0, sizeof(tCSTSEPORDERARTGRP));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCSTSEPORDERARTGRP struct and then imported to self.                      */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroup&
pxCstSepOrderArtGroup :: operator=( const pxCstSepOrderArtGroup& src)
{
    tCSTSEPORDERARTGRP record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCSTSEPORDERARTGRP structure 'src' to            */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroup&
pxCstSepOrderArtGroup :: operator=( const tCSTSEPORDERARTGRP& src)
{
    return Assign(*this, src);
}

int
pxCstSepOrderArtGroupList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCstSepOrdArtGrpEndBrowse(cursorid);
}

int
pxCstSepOrderArtGroupList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxCstSepOrdArtGrpGetNext((tCSTSEPORDERARTGRP*)record, cursorid);
}

int
pxCstSepOrderArtGroupList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxCstSepOrdArtGrpStartBrowse((tCSTSEPORDERARTGRP*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCstSepOrderArtGroup list objects being inserted in the          */
/*  following ascending sequence:                                             */
/*  BranchNo, ArtGrp                                                          */
/*----------------------------------------------------------------------------*/
int
pxCstSepOrderArtGroup :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCstSepOrderArtGroup *that = (pxCstSepOrderArtGroup*)That;

    int retval = (BranchNo_ == that->BranchNo_) ? 0
               : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
        retval = (CustomerNo_ == that->CustomerNo_) ? 0
               : (CustomerNo_ > CustomerNo_ ? 1 : -1);

    if ( retval == 0 )
        retval = (ArtGrp_ == that->ArtGrp_) ? 0
               : (ArtGrp_ > that->ArtGrp_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroupList :: pxCstSepOrderArtGroupList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCstSepOrderArtGroupList :: Select
(
    const short   BranchNo,
    const long    CustomerNo,
    const int     count_
)
{
    tCSTSEPORDERARTGRP fil;
    memset(&fil, 0, sizeof(tCSTSEPORDERARTGRP));  // zero out entire record buffer
    fil.BranchNo    = BranchNo;
    fil.CustomerNo  = CustomerNo;
    int cursorid   = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCstSepOrderArtGroupList :: AddToList
(
    const void *record,
    const int  /* row */
)
{
    // construct new 'pxCstSepOrderArtGroup' object:
    pxCstSepOrderArtGroup *objectp = new pxCstSepOrderArtGroup(Session(), *(tCSTSEPORDERARTGRP*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Find: Looks within the list of pxCstSepOrderArtGroup entries for BranchNo */
/*  depend on VZ.                                                             */
/*  Returns: 0 = No entry found, BranchNo = VZ                                */
/*----------------------------------------------------------------------------*/
short
pxCstSepOrderArtGroupList :: Find
(
    const short VZ
)
{
    short BranchNo = 0;
    pxCstSepOrderArtGroupListIter   iter( *this );  // define iterator
    pxCstSepOrderArtGroup          *entryp;        // pointer to listentry
    if ( Entries() == 0 )
        return BranchNo;
    while ( (entryp = (pxCstSepOrderArtGroup*) ++iter) != NULL ) // browse list
    {
        if ( entryp->BranchNo() == VZ )
        {
            BranchNo = entryp->BranchNo();
            break;
        }
    }
    return BranchNo;                   // return BranchNumber
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
pxCstSepOrderArtGroup*
pxCstSepOrderArtGroupList :: Find
(
    const short  BranchNo,
    const long   CustomerNo,
    const short  ArtGroup
)
{
    pxCstSepOrderArtGroupListIter   iter( *this );  // define iterator
    pxCstSepOrderArtGroup          *entryp = NULL;  // pointer to listentry

    if ( Entries() == 0 )
        return entryp;

    while ( (entryp = (pxCstSepOrderArtGroup*) ++iter) != NULL )  // browse list
    {
        if ( entryp->BranchNo() == BranchNo &&
             entryp->CustomerNo() == CustomerNo &&
             entryp->ArtGrp() == ArtGroup  )
        {
            break;
        }
    }
    return entryp;                            // return pointer
}

/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxSepOrderArtGroup  methods.

REVISION HISTORY

16 March 2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxseporderartgrp.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxSepOrderArtGroup :: pxSepOrderArtGroup
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
pxSepOrderArtGroup :: pxSepOrderArtGroup
(
    pxSepOrderArtGroup& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tSEPORDERARTGRP structure to construct this instance.                 */
/*----------------------------------------------------------------------------*/
pxSepOrderArtGroup :: pxSepOrderArtGroup
(
    pxSession   *session,
    tSEPORDERARTGRP& src
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
pxSepOrderArtGroup :: pxSepOrderArtGroup
(
    pxSession *session,
    const pxSepOrderArtGroup *srcp
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
pxSepOrderArtGroup :: ~pxSepOrderArtGroup()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tSEPORDERARTGRP structure.     */
/*----------------------------------------------------------------------------*/
tSEPORDERARTGRP&
Assign
(
    tSEPORDERARTGRP&           dest,
    const pxSepOrderArtGroup&  src
)
{
    dest.BranchNo                  = src.BranchNo_       ;
    dest.ArtGrp                    = src.ArtGrp_         ;
    dest.KoArt                     = src.KoArt_          ;
    dest.BuchArt                   = src.BuchArt_        ;
    dest.DeferOrder                = src.DeferOrder_     ;
    dest.ManufacturerNo            = src.ManufacturerNo_ ;

    strcpy(dest.KdAuftragArt, " ");
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tSEPORDERARTGRP structure to               */
/*  a pxSepOrderArtGroup object.                                              */
/*----------------------------------------------------------------------------*/
pxSepOrderArtGroup&
Assign
(
    pxSepOrderArtGroup&       dest,
    const tSEPORDERARTGRP&    src
)
{
    dest.BranchNo_                  = src.BranchNo       ;
    dest.ArtGrp_                    = src.ArtGrp         ;
    dest.KdAuftragArt_              = src.KdAuftragArt   ;
    dest.KoArt_                     = src.KoArt          ;
    dest.BuchArt_                   = src.BuchArt        ;
    dest.DeferOrder_                = src.DeferOrder     ;
    dest.ManufacturerNo_            = src.ManufacturerNo ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxSepOrderArtGroup :: Init()
{
    tSEPORDERARTGRP record;
    memset(&record, 0, sizeof(tSEPORDERARTGRP));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tSEPORDERARTGRP struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxSepOrderArtGroup&
pxSepOrderArtGroup :: operator=( const pxSepOrderArtGroup& src)
{
    tSEPORDERARTGRP record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tSEPORDERARTGRP structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxSepOrderArtGroup&
pxSepOrderArtGroup :: operator=( const tSEPORDERARTGRP& src)
{
    return Assign(*this, src);
}

int
pxSepOrderArtGroupList :: EndBrowse
(
    const int cursorid
)
{
    return pxSepOrderArtGroupEndBrowse(cursorid);
}

int
pxSepOrderArtGroupList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxSepOrderArtGroupGetNext((tSEPORDERARTGRP*)record, cursorid);
}

int
pxSepOrderArtGroupList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxSepOrderArtGroupStartBrowse((tSEPORDERARTGRP*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxSepOrderArtGroup list objects being inserted in the             */
/*  following ascending sequence:                                             */
/*  BranchNo, ArtGrp                                                          */
/*----------------------------------------------------------------------------*/
int
pxSepOrderArtGroup :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxSepOrderArtGroup *that = (pxSepOrderArtGroup*)That;

    int retval = (BranchNo_ == that->BranchNo_) ? 0
               : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
        retval = (ArtGrp_ == that->ArtGrp_) ? 0
               : (ArtGrp_ > that->ArtGrp_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxSepOrderArtGroupList :: pxSepOrderArtGroupList
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
pxSepOrderArtGroupList :: Select
(
    const short   BranchNo,
    const int     count_
)
{
    tSEPORDERARTGRP fil;
    memset(&fil, 0, sizeof(tSEPORDERARTGRP));  // zero out entire record buffer
    fil.BranchNo    = BranchNo;
    int cursorid   = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxSepOrderArtGroupList :: AddToList
(
    const void *record,
    const int  /* row */
)
{
    // construct new 'pxSepOrderArtGroup' object:
    pxSepOrderArtGroup *objectp = new pxSepOrderArtGroup(Session(), *(tSEPORDERARTGRP*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Find: Looks within the list of pxSepOrderArtGroup entries for BranchNo    */
/*  depend on VZ.                                                             */
/*  Returns: 0 = No entry found, BranchNo = VZ                                */
/*----------------------------------------------------------------------------*/
short
pxSepOrderArtGroupList :: Find
(
    const short  VZ
)
{
    short BranchNo = 0;
    pxSepOrderArtGroupListIter   iter( *this );  // define iterator
    pxSepOrderArtGroup          *entryp;        // pointer to listentry
    if ( Entries() == 0 )
        return BranchNo;
    while ( (entryp = ( pxSepOrderArtGroup*) ++iter) != NULL ) // browse list
    {
        if ( entryp->BranchNo() == VZ )
        {
            BranchNo = entryp->BranchNo();
            break;
        }
    }
    return   BranchNo;                   // return BranchNumber
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
pxSepOrderArtGroup*
pxSepOrderArtGroupList :: Find
(
    const short  BranchNo,
    const short  ArtGroup
)
{
    pxSepOrderArtGroupListIter   iter( *this );  // define iterator
    pxSepOrderArtGroup          *entryp = NULL;  // pointer to listentry

    if ( Entries() == 0 )
        return entryp;

    while ( (entryp = ( pxSepOrderArtGroup*) ++iter) != NULL )  // browse list
    {
        if ( entryp->BranchNo() == BranchNo && entryp->ArtGrp() == ArtGroup )
        {
            break;
        }
    }
    return   entryp;                            // return pointer
}

/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxManufacturerGroup  methods.

REVISION HISTORY

06 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxmanufacturergroup.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxManufacturerGroup :: pxManufacturerGroup
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
pxManufacturerGroup :: pxManufacturerGroup
(
    pxManufacturerGroup& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tMANUFACTURERGROUP structure to construct this instance.             */
/*----------------------------------------------------------------------------*/
pxManufacturerGroup :: pxManufacturerGroup
(
    pxSession   *session,
    tMANUFACTURERGROUP& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxManufacturerGroup :: ~pxManufacturerGroup()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tMANUFACTURERGROUP structure.     */
/*----------------------------------------------------------------------------*/
tMANUFACTURERGROUP&
Assign
(
    tMANUFACTURERGROUP&           dest,
    const pxManufacturerGroup&     src
)
{
    dest.PharmacyGroupID[0] = ' ';
    src.PharmacyGroupID_.GetData(dest.PharmacyGroupID);
    dest.KonsigPartnerNr          = src.KonsigPartnerNr_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tMANUFACTURERGROUP structure to               */
/*  a pxManufacturerGroup object.                                                */
/*----------------------------------------------------------------------------*/
pxManufacturerGroup&
Assign
(
    pxManufacturerGroup&              dest,
    const tMANUFACTURERGROUP&         src
)
{
    dest.PharmacyGroupID_          = src.PharmacyGroupID;
    dest.KonsigPartnerNr_          = src.KonsigPartnerNr;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxManufacturerGroup :: Init()
{
    tMANUFACTURERGROUP    record;
    memset(&record, 0 , sizeof(tMANUFACTURERGROUP));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tMANUFACTURERGROUP struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxManufacturerGroup&
pxManufacturerGroup :: operator=( const pxManufacturerGroup& src)
{
    tMANUFACTURERGROUP record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tMANUFACTURERGROUP structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxManufacturerGroup&
pxManufacturerGroup :: operator=( const tMANUFACTURERGROUP& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxManufacturerGroup list objects being inserted in the            */
/*  following ascending sequence:                                             */
/*----------------------------------------------------------------------------*/
int
pxManufacturerGroup :: CompareTo
(
    const nCollectable   * /* That */,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    return 0;
}

int
pxManufacturerGroupList :: EndBrowse
(
    const int  cursorid
)
{
    return pxManufacturerGroupEndBrowse(cursorid);
}


int
pxManufacturerGroupList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxManufacturerGroupGetNext((tMANUFACTURERGROUP*)record, cursorid);
}

int
pxManufacturerGroupList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxManufacturerGroupStartBrowse((tMANUFACTURERGROUP*)keys, cursorid,BranchNo_,CustomerNo_);
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxManufacturerGroupList :: pxManufacturerGroupList
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
pxManufacturerGroupList :: Select
(
    const int    count_
)
{
    tMANUFACTURERGROUP fil;
    memset(&fil, 0, sizeof(tMANUFACTURERGROUP));  // zero out entire record buffer
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxManufacturerGroupList :: SelectExist
(
    const long   konsigpartnerno,
    const int    count_
)
{
    tMANUFACTURERGROUP fil;
    memset(&fil, 0, sizeof(tMANUFACTURERGROUP));  // zero out entire record buffer
    fil.KonsigPartnerNr = konsigpartnerno;
    int cursorid    = cCRSKONSIGPARTNERNR;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxManufacturerGroupList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxManufacturerGroup' object:
    pxManufacturerGroup *objectp = new pxManufacturerGroup(Session(), *(tMANUFACTURERGROUP*) record);
    InsertAscending(objectp);
    return objectp;
}

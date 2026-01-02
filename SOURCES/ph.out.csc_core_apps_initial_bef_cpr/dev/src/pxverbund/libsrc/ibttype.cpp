#include "ibttype.hpp"
#include "tibttype.h"
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Use tIBTTYPE structure to construct this instance.                        */
/*----------------------------------------------------------------------------*/
pxIBTType::pxIBTType(pxSession* session, tIBTTYPE& src) : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxIBTType::~pxIBTType()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tIBTTYPE structure.            */
/*----------------------------------------------------------------------------*/
tIBTTYPE& Assign(tIBTTYPE& dest, const pxIBTType& src)
{
    dest.IBTTypeId	= src.IBTTypeId_ ;
    dest.Name[0]  = ' ';
    src.Name_.GetData(dest.Name);
    dest.PurchaseRelevanceMode = static_cast<short>(src.PurchaseRelevanceMode_);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tIBTTYPE structure to a pxIBTType object.  */
/*----------------------------------------------------------------------------*/
pxIBTType& Assign(pxIBTType& dest, const tIBTTYPE& src)
{
    dest.IBTTypeId_                = src.IBTTypeId;
    dest.Name_                     = src.Name;
    if (src.PurchaseRelevanceMode < PRM_ORIGINAL_BRANCH || src.PurchaseRelevanceMode > PRM_BOTH_BRANCHES)
    {
        dest.PurchaseRelevanceMode_ = PRM_UNKNOWN;
    }
    else
    {
        dest.PurchaseRelevanceMode_ = static_cast<PURCHASE_RELEVANCE_MODE>(src.PurchaseRelevanceMode);
    }
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void pxIBTType::Init()
{
    tIBTTYPE record;
    memset(&record, 0 , sizeof(tIBTTYPE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tIBTTYPE struct and then imported to self.                                */
/*----------------------------------------------------------------------------*/
pxIBTType& pxIBTType::operator=(const pxIBTType& src)
{
    tIBTTYPE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tIBTTYPE structure 'src' to this instance.       */
/*----------------------------------------------------------------------------*/
pxIBTType& pxIBTType::operator=(const tIBTTYPE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
short pxIBTType::IBTTypeId()
{
    return IBTTypeId_;
}

/*----------------------------------------------------------------------------*/
nString pxIBTType::Name()
{
    return Name_;
}

/*----------------------------------------------------------------------------*/
PURCHASE_RELEVANCE_MODE pxIBTType::PurchaseRelevanceMode()
{
    return PurchaseRelevanceMode_;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxBranchPartner list objects being inserted in the                */
/*  following ascending sequence:                                             */
/*  (IBTTypeId_)                                                                */
/*----------------------------------------------------------------------------*/
int pxIBTType::CompareTo(const nCollectable* That, void* /*p*/, const long /*lparm*/) const
{
    pxIBTType *that = (pxIBTType*)That;
    int retval = (IBTTypeId_ == that->IBTTypeId_) ? 0
               : (IBTTypeId_ > that->IBTTypeId_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxIBTTypeList::pxIBTTypeList(pxSession* session) : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  List Destructor.                                                          */
/*----------------------------------------------------------------------------*/
pxIBTTypeList::~pxIBTTypeList()
{
    Clear();
}

/*----------------------------------------------------------------------------*/
pxSession* pxIBTTypeList::Session()
{
    return (pxSession*) DataBase();
}

/*----------------------------------------------------------------------------*/
void pxIBTTypeList::Clear()
{
    nDBRecordSet::Clear();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t pxIBTTypeList::Select()
{
    tIBTTYPE fil;
    memset(&fil, 0, sizeof(tIBTTYPE));  // zero out entire record buffer
    int cursorid = cCRSIBTTYPE_Default;
    nDBSelect(&fil, cursorid);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable* pxIBTTypeList::AddToList(const void* record, const int /*row*/)
{
    pxIBTType *objectp = new pxIBTType(Session(), *(tIBTTYPE*) record);
    InsertAscending(objectp);
    return objectp;
}

int pxIBTTypeList::EndBrowse(const int /*cursorid*/)
{
    return pxIBTTypeEndBrowse();
}


int pxIBTTypeList::GetNext(const void* record, const int /*cursorid*/)
{
    return pxIBTTypeGetNext((tIBTTYPE*)record);
}

int pxIBTTypeList::StartBrowse(const void* keys, const int /*cursorid*/)
{
    return pxIBTTypeStartBrowse((tIBTTYPE*)keys);
}

/*----------------------------------------------------------------------------*/
/* Returns the pointer to the corresponding entry within the list.            */
/* NULL returns if the wanted entry is not found within the list.             */
/*----------------------------------------------------------------------------*/
pxIBTType* pxIBTTypeList::Find(short typeId)
{
    pxIBTTypeListIter   iter(*this);
    pxIBTType*          entry;

    iter.Reset();
    while ((entry = (pxIBTType*)++iter) != NULL)
    {
        if (typeId == entry->IBTTypeId())
        {
            break;
        }
    }
    return entry;
}

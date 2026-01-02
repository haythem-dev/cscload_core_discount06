#include "pxordtyp.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderType :: pxOrderType
(
    pxSession *session
)
    :pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Construct an instance using 'key' as order category key.                  */
/*----------------------------------------------------------------------------*/
pxOrderType :: pxOrderType
(
    pxSession *session,
    const nString&  key
)
{
    // avoid "unused" compiler warning
    { session = session; }

    Init();
    KdAuftragArt_ = key;
    Translate();
}

/*----------------------------------------------------------------------------*/
/*  Construct an instance using 'key' as order category key and               */
/*  BranchNo                                                                  */
/*----------------------------------------------------------------------------*/
pxOrderType :: pxOrderType
(
    pxSession *session,
    const nString&  key,
    const short    BranchNo
)
{
    // avoid "unused" compiler warning
    { session = session; }

    Init();
    KdAuftragArt_ = key;
    BranchNo_     = BranchNo;
    Translate();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderType :: pxOrderType
(
    const pxOrderType& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  "Copy" constructor using a pointer to the source rather than a reference. */
/*  NULL pointer safe.                                                        */
/*----------------------------------------------------------------------------*/
pxOrderType :: pxOrderType
(
    pxSession *session,
    const pxOrderType  *srcp
)
    : pxDBRecord(session)
{
    Init();
    if (srcp != NULL)
       (*this) = *srcp;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderType :: pxOrderType
(
    pxSession *session,
    const nString&  KdAuftragArt,          // Read via string input
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragArt_ = KdAuftragArt;
    Get(mode);
    Translate();
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderType :: ~pxOrderType()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGART structure.       */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGART&
Assign
(
    tKDAUFTRAGART&     dest,
    const pxOrderType& src
)
{
    dest.KdAuftragArt[0] = ' ';
    src.KdAuftragArt_.GetData(dest.KdAuftragArt,
                              mSIZEOF(tKDAUFTRAGART, KdAuftragArt)-1);
    dest.Bezeichnung[0] = ' ';
    src.Bezeichnung_.GetData(dest.Bezeichnung,
                             mSIZEOF(tKDAUFTRAGART, Bezeichnung)-1);
    dest.BranchNo           =   src.BranchNo_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGART structure to a pxOrderType   */
/*                                                              object.       */
/*----------------------------------------------------------------------------*/
pxOrderType&
Assign
(
    pxOrderType&    dest,
    const tKDAUFTRAGART&  src
)
{

    dest.KdAuftragArt_          = src.KdAuftragArt;
    dest.KdAuftragArt_.Strip();
    dest.Bezeichnung_           = src.Bezeichnung;
    dest.Bezeichnung_.Strip();
    dest.BranchNo_              = src.BranchNo;
    dest.Discountable_          = src.SDiscountable;
    dest.DisInKindEnterable_    = src.DisinkindEnterable;
    dest.Global_                = src.SGlobal;
    dest.ValidViaVideo_         = src.SBildschirm;
    dest.ValidViaDCT_           = src.SDafue;
    dest.Default_               = src.SStandard;
    dest.MustSubOrder_          = src.SMustSubOrder;
    dest.FreePrice_             = src.SFreePrice;
    dest.OrderCons_             = src.SOrderCons;
    dest.RestDel_               = src.SRestDel;
    dest.NoQuota_               = src.SNoQuota;
    dest.NoPartQty_             = src.SNoPartQty;
    dest.DeferOrder_            = src.SDeferOrder;
    dest.ServiceOrder_          = src.SServiceOrder;
    dest.NoDD_                  = src.SNoDD;
    dest.OnlyEH_                = src.SOnlyEH;
    dest.SKdAuftragartNatra_    = src.SKdAuftragartNatra;
    dest.SKdAuftragartNetto_    = src.SKdAuftragartNetto;
    dest.SNoPromotions_         = src.SNoPromotions;
    dest.SDefaultKennung_       = src.SDefaultKennung;
    dest.SAlwaysRestDel_        = src.SAlwaysRestDel;
    dest.SStockreservation_     = src.Stockreservation;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Virtual CompareTo function redefined from nCollectable.                   */
/*----------------------------------------------------------------------------*/
int
pxOrderType :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderType *that = (pxOrderType*)That;
    return (KdAuftragArt_ == that->KdAuftragArt_)
           ? 0 : (KdAuftragArt_ > that->KdAuftragArt_) ? 1 : -1;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderType :: Init()
{

    ValutaMonate_         =  0 ;
    SKdAuftragartNatra_   = '0';
    SKdAuftragartNetto_   = '0';
    SKdAuftragartBANR_    = '0';
    SKdAuftragartMonat_   = '0';
    SKdAuftragartVerbund_ = '0';
    SKdAuftragartValS_    = '0';
    Category_             = NoOrderType;
    Discountable_         = '0';
    DisInKindEnterable_   = '0';
    Default_              = '0';
    Global_               = '0';
    ValidViaDCT_          = '0';
    ValidViaVideo_        = '0';
    MustSubOrder_         = '0';
    FreePrice_            = '0';
    OrderCons_            = '0';
    RestDel_              = '0';
    NoQuota_              = '0';
    NoPartQty_            = '0';
    DeferOrder_           = '0';
    ServiceOrder_         = '0';
    NoDD_                 = '0';
    OnlyEH_               = '0';
    SNoPromotions_        = 0;
    SDefaultKennung_      = 0;
    SAlwaysRestDel_       = 0;
    SStockreservation_    = 0;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxOrderType&
pxOrderType :: operator=( const pxOrderType& src)
{

    KdAuftragArt_         =   src.KdAuftragArt_;
    Bezeichnung_          =   src.Bezeichnung_;
    ValutaMonate_         =   src.ValutaMonate_;
    SKdAuftragartNatra_   =   src.SKdAuftragartNatra_;
    SKdAuftragartNetto_   =   src.SKdAuftragartNetto_;
    SKdAuftragartBANR_    =   src.SKdAuftragartBANR_;
    SKdAuftragartMonat_   =   src.SKdAuftragartMonat_;
    SKdAuftragartVerbund_ =   src.SKdAuftragartVerbund_;
    SKdAuftragartValS_    =   src.SKdAuftragartValS_;
    Discountable_         =   src.Discountable_;
    DisInKindEnterable_   =   src.DisInKindEnterable_;
    Default_              =   src.Default_;
    Global_               =   src.Global_;
    ValidViaDCT_          =   src.ValidViaDCT_;
    ValidViaVideo_        =   src.ValidViaVideo_;
    Category_             =   src.Category_;
    BranchNo_             =   src.BranchNo_;
    MustSubOrder_         =   src.MustSubOrder_;
    FreePrice_            =   src.FreePrice_;
    OrderCons_            =   src.OrderCons_;
    RestDel_              =   src.RestDel_;
    NoQuota_              =   src.NoQuota_;
    NoPartQty_            =   src.NoPartQty_;
    DeferOrder_           =   src.DeferOrder_;
    ServiceOrder_         =   src.ServiceOrder_;
    NoDD_                 =   src.NoDD_;
    OnlyEH_               =   src.OnlyEH_;
    SNoPromotions_        =   src.SNoPromotions_;
    SDefaultKennung_      =   src.SDefaultKennung_;
    SAlwaysRestDel_       =   src.SAlwaysRestDel_;
    SStockreservation_    =   src.SStockreservation_;
    return *this;
}
/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGART structure to this instance.        */
/*----------------------------------------------------------------------------*/
pxOrderType&
pxOrderType :: operator=( const tKDAUFTRAGART& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
bool pxOrderType::IsEqual(const nCollectable *itemp) const
{
    return (CompareTo(itemp,(void*)this,0L) == 0);
}

/*----------------------------------------------------------------------------*/
int pxOrderType::Insert(const void *record)
{
    return pxAuftragArtInsert((tKDAUFTRAGART*)record);
}

/*----------------------------------------------------------------------------*/
int pxOrderType::Update(const void *record)
{
    return pxAuftragArtUpdate((tKDAUFTRAGART*)record);
}

/*----------------------------------------------------------------------------*/
int pxOrderType::Read(const void *record)
{
    return pxAuftragArtRead((tKDAUFTRAGART*)record);
}

/*----------------------------------------------------------------------------*/
int pxOrderType::ReadLock(const void *record)
{
    return pxAuftragArtReadLock((tKDAUFTRAGART*)record);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderType :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGART record;
    memset(&record, 0, sizeof(tKDAUFTRAGART));
    Assign(record, *this);
    int retval = ( mode == cDBGET_FORUPDATE )
                  ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGART struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderType :: Put()
{
    tKDAUFTRAGART record;
    memset(&record, 0, sizeof(tKDAUFTRAGART));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGART));
}

/*----------------------------------------------------------------------------*/
/*  Translate order type key strings. (Temporary function).                   */
/*----------------------------------------------------------------------------*/
void
pxOrderType :: Translate()
{

    struct TrTabEntry
    {
        char     key[3];
        tOrderTypeCode category;
    };

    static TrTabEntry TrTable[] =
    {
        { "NO", Normal              },
        { "SB", SBL                 },
        { "ST", Batch               },
        { "SV", Service             },
        { "TE", Test                },
        { "VR", StockPurchase       },
        { "ZE", Tens                },
        { "ZT", TimeOrdered         },
        { "AN", Query               },
        { "SO", Special             },
        { "DI", ScheduleOrder       },
        { "FU", OverStockBalance    },
        { "NL", AdditionalDelivery  },
        { "OP", Opiate              },
        { "OR", NoDiscounts         },
        { "RK", BuyBack             },
        { "MD", ScheduleQuantity    },
        { "UW", Transfer            },
        { "OM", OmgSwiss            },
        { "ID", IndustrieDispo      },
        { "DT", DispoTransfer       },
        { "S1", Special1            },
        { "S2", Special2            },
        { "S3", Special3            },
        { "S4", Special4            },
        { "S5", Special5            },
        { "S6", Special6            },
        { "S7", Special7            },
        { "S8", Special8            },
        { "S9", Special9            },
        { "AK", Active3000          },
        { "AC", Active4000          },
        { "UN", UnoTransfer         },
        { "SH", ShortBusiness       },
        { "G1", GenerikaOne         },
        { "G2", GenerikaTwo         },
        { "G3", GenerikaThree       },
        { "GE", Generika            },
        { "LO", PrismaOrder         },
        { "OV", OverDrive           },
        { "PM", PhoenixMagic        },
        { "RL", PriceFree           },
        { "NF", OnlyInvoice         },
        { "A0", Automate0           },
        { "A1", Automate1           },
        { "A2", Automate2           },
        { "A3", Automate3           },
        { "A4", Automate4           },
        { "A5", Automate5           },
        { "A6", Automate6           },
        { "A7", Automate7           },
        { "A8", Automate8           },
        { "A9", Automate9           },
        { "EX", Express             },
        { "RO", DiscountAccount     },
        { "TO", TenderOrder         },
        { "TI", TenderInvoice       },
        { "CO", CashOrder           },
        { "MP", ManualPromotion     },
        { "EH", RetailSalesOrder    },
        { "SP", BountyOrder         },
        { "VE", DestructionOrder    },
        { "QA", QuarantineOrder     },
        { "BC", ChargeRecallOrder   },
        { "PR", PrivateProductRange },
        { "CV", CollectiveOrder     },
        { "FC", FreeConditionOrder  },
        { "SL", ShortLineBusiness   },
        { "PO", ProformaOrder       },
        { "CC", ChronicIllness       }
    };

    int x = sizeof(TrTable) / sizeof(TrTabEntry);
    for (int i = 0; i < x; i++)
    {
       if ( KdAuftragArt_ == nString(TrTable[i].key ))
       {
          Category_            = TrTable[i].category;
          break;
       }
    }
}

/*----------------------------------------------------------------------------*/
/*  List constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderTypeList :: pxOrderTypeList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using single string value arguments.                 */
/*----------------------------------------------------------------------------*/
size_t
pxOrderTypeList :: Select
(
    short BranchNo,
    const int     count_                // Max number of records to read
)

{

    tKDAUFTRAGART record;
    memset(&record, 0, sizeof(tKDAUFTRAGART));  // zero out entire record buffer
    record.BranchNo = BranchNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);
    return Entries();

}

/*----------------------------------------------------------------------------*/
/*  Find an object instance with a matching key. Returns a pointer to that    */
/*  instance or NULL if the key could not be found.                           */
/*----------------------------------------------------------------------------*/
pxOrderType*
pxOrderTypeList :: Find
(
    const nString&  kdaufart,
    const short    BranchNo
)
{
    pxOrderType *temp = NULL;
    pxOrderTypeListIter cursor(*this);
    while ( (temp = (pxOrderType*) ++cursor) != NULL )
    {
       if ( temp->KdAuftragArt_ == kdaufart && temp->BranchNo_ == BranchNo )
          break;
    }

    return temp;
}

/*----------------------------------------------------------------------------*/
/*  Find the BranchNo within this list                                        */
/*----------------------------------------------------------------------------*/
short
pxOrderTypeList :: Find
(
    const short    BranchNo
)
{
    short branchno = 0;
    pxOrderTypeListIter cursor(*this);
    pxOrderType *temp;
    while ( (temp = (pxOrderType*) ++cursor) != NULL )
    {
       if ( temp->BranchNo_ == BranchNo )
       {
          branchno = temp->BranchNo_;
          break;
       }
    }

    return branchno;
}

/*----------------------------------------------------------------------------*/
/*  Construct a new item and insert it into the list.                         */
/*  Returns pointer to new object instance or NULL if an instance with the    */
/*  same key is already in the list.                                          */
/*----------------------------------------------------------------------------*/
pxOrderType*
pxOrderTypeList :: NewItem
(
    const nString& key,
    const short BranchNo
)
{
    if ( Find(key,BranchNo) )
       return NULL;                     // avoid duplicates
    pxOrderType *objectp = new pxOrderType(Session(), key);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*                           // Construct a new object and add
pxOrderTypeList :: AddToList            // it to the list
(
    const void  *record,
    const int  /*row*/
)
{
    tKDAUFTRAGART* recordp = (tKDAUFTRAGART*)record;
    pxOrderType *itemp = NewItem(recordp->KdAuftragArt, recordp->BranchNo);
    if (itemp)                          // object constructed,
       Assign(*itemp, *recordp);        // copy values from the record buffer
    return itemp;
}

/*----------------------------------------------------------------------------*/
int pxOrderTypeList::EndBrowse(const int cursorid)
{
    return pxAuftragArtEndBrowse(cursorid);
}

/*----------------------------------------------------------------------------*/
int pxOrderTypeList::GetNext(const void* record, const int cursorid)
{
    return pxAuftragArtGetNext((tKDAUFTRAGART*)record, cursorid);
}

/*----------------------------------------------------------------------------*/
int pxOrderTypeList::StartBrowse(const void *keys, const int cursorid)
{
    return pxAuftragArtStartBrowse((tKDAUFTRAGART*)keys, cursorid);
}

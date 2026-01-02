#include "pxdelpos.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxvartikellokal.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

extern bool pxGlobalDataBaseSort;

namespace pxVerbund
{
    namespace subsequentDelivery
    {

        /*----------------------------------------------------------------------------*/
        /*  Normal constructor.                                                       */
        /*----------------------------------------------------------------------------*/
        pxDeliveryPos :: pxDeliveryPos
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
        pxDeliveryPos :: pxDeliveryPos
        (
            pxDeliveryPos& src
        )
            : pxDBRecord(src.Session())
        {
            Init();
            (*this) = src;
        }

        /*----------------------------------------------------------------------------*/
        /*  Use tNACHLIEFERPOS structure to construct this instance.                  */
        /*----------------------------------------------------------------------------*/
        pxDeliveryPos :: pxDeliveryPos
        (
            pxSession   *session,
            tNACHLIEFERPOS& src
        )
            : pxDBRecord(session)
        {
            Init();
            (*this) = src;
        }
        /*----------------------------------------------------------------------------*/
        /*  Use pxOrderItem to construct this instance.                               */
        /*----------------------------------------------------------------------------*/
        pxDeliveryPos :: pxDeliveryPos
        (
            pxOrderItem& Item,
            pxDelPosTyp  PosTyp
        )
            : pxDBRecord( Item.Order().Session())
        {
            nDate today;
            Init();
            KdAuftragNr_          = Item.Order().KdAuftragNr();
            PosNr_                = Item.PosNr();
            ArtikelNr_            = Item.ArtikelNr();
            Datum_                = today;
            IDFNr_                = Item.Order().IDFNr();
            KundenNr_             = Item.Order().KundenNr();
            VertriebszentrumNr_   = Item.Order().Vertriebszentrum();
            SetArticleCodeValues(Item.CodeType(), Item.ArticleCode());
            if ( PosTyp == pxDPT_RESTDELIVERY_ITEM )
            {
                KdAuftragArt_         = Item.Order().KdAuftragArt();
                KoArt_                = Item.Order().KoArt();
                BuchArt_              = Item.Order().BuchArt();
            }
            PosTyp_               = PosTyp;
            if ( Session()->Device()->IsDCT() )  // DC active
                PosArt_  = cDP_COMING_BY_DCT;
            else
            if  ( Session()->Device()->IsFILE())
                PosArt_  = cDP_COMING_BY_BATCH;
            else
                PosArt_  = cDP_COMING_BY_TELEPHONE;
        }

        /*----------------------------------------------------------------------------*/
        /*  Read constructors.                                                        */
        /*----------------------------------------------------------------------------*/
        pxDeliveryPos :: pxDeliveryPos( pxSession *session, long KdAuftragNr, long PosNr, nDate date, pxDelPosTyp  PosTyp, DBAccessMode mode )
        : pxDBRecord(session)
        {
            Init();
            KdAuftragNr_    = KdAuftragNr;
            PosNr_          = PosNr;
            Datum_          = date;
            PosTyp_         = PosTyp;
            Get(mode);
        }

        /*----------------------------------------------------------------------------*/
        /*  Destructor.                                                               */
        /*----------------------------------------------------------------------------*/
        pxDeliveryPos :: ~pxDeliveryPos()
        {
        }

        /*----------------------------------------------------------------------------*/
        /*  Assign the values of the 'src' object to a tNACHLIEFERPOS structure.      */
        /*----------------------------------------------------------------------------*/
        tNACHLIEFERPOS&
        Assign
        (
            tNACHLIEFERPOS&           dest,
            const pxDeliveryPos&       src
        )
        {
            dest.KdAuftragNr               = src.KdAuftragNr_                        ;
            dest.PosNr                     = src.PosNr_                              ;
            dest.Datum                     = src.Datum_.GetYYYYMMDD()                ;
            dest.PosTyp                    = static_cast<short>(src.PosTyp_)         ;
            dest.IDFNr                     = src.IDFNr_                              ;
            dest.ArtikelNr                 = src.ArtikelNr_                          ;
            dest.Menge                     = src.Menge_                              ;
            dest.FilialNr1                 = src.FilialNr1_                          ;
            dest.FilialNr2                 = src.FilialNr2_                          ;
            dest.FilialNr3                 = src.FilialNr3_                          ;
            dest.Status                    = src.Status_                             ;
            dest.UrsprungAuftragNr         = src.UrsprungAuftragNr_                  ;
            dest.UrsprungPosNr             = src.UrsprungPosNr_                      ;
            dest.KundenNr                  = src.KundenNr_                           ;
            dest.VertriebszentrumNr        = src.VertriebszentrumNr_                 ;
            dest.Erfasst                   = src.Erfasst_                            ;
            dest.KdAuftragArt[0] = ' ';
            src.KdAuftragArt_.GetData(dest.KdAuftragArt);
            dest.PosArt[0] = ' ';
            src.PosArt_.GetData(dest.PosArt);
            dest.PreisEKApoNetto           = src.PreisEKApoNetto_;
            dest.BatchAuftragNr            = src.BatchAuftragNr_                     ;
            dest.BatchPosNr                = src.BatchPosNr_                         ;
            dest.MengeNatra                = src.MengeNatra_                         ;
            dest.Bemerkungen[0] = ' ';
            src.Bemerkungen_.GetData(dest.Bemerkungen, (mSIZEOF(tNACHLIEFERPOS, Bemerkungen)) - 1);
            dest.PreisEKApo                = src.PreisEKApo_                         ;
            dest.PreisVKApo                = src.PreisVKApo_                         ;
            dest.PreisAGP                  = src.PreisAGP_                           ;
            dest.DatumValuta               = src.DatumValuta_.GetYYYYMMDD()          ;
            dest.KoArt                     = src.KoArt_                              ;
            dest.BuchArt                   = src.BuchArt_                            ;
            dest.Code_Type                 = src.CodeType_                           ;
            dest.Preis_Typ                 = static_cast<short>(src.PreisTyp_)       ;

            dest.Article_Code[0] = ' ';
            src.ArticleCode_.GetData(dest.Article_Code, (mSIZEOF(tKDAUFTRAGPOS, Article_Code)) - 1);
            dest.DiscountValuePct          = src.DiscountValuePct_       ;
            dest.MengeBestellt             = src.MengeBestellt_          ;

            return dest;
        }

        /*----------------------------------------------------------------------------*/
        /*  Assign the values of the 'src' tNACHLIEFERPOS structure to                */
        /*  a pxDeliveryPos object.                                                   */
        /*----------------------------------------------------------------------------*/
        pxDeliveryPos&
        Assign
        (
            pxDeliveryPos&              dest,
            const tNACHLIEFERPOS&    src
        )
        {
            dest.KdAuftragNr_              = src.KdAuftragNr                         ;
            dest.PosNr_                    = src.PosNr                               ;
            dest.Datum_                    = nDate(src.Datum)                        ;
            dest.PosTyp_                   = (pxVerbund::subsequentDelivery::pxDelPosTyp)src.PosTyp  ;
            dest.IDFNr_                    = src.IDFNr                               ;
            dest.ArtikelNr_                = src.ArtikelNr                           ;
            dest.Menge_                    = src.Menge                               ;
            dest.FilialNr1_                = src.FilialNr1                           ;
            dest.FilialNr2_                = src.FilialNr2                           ;
            dest.FilialNr3_                = src.FilialNr3                           ;
            dest.Status_                   = src.Status                              ;
            dest.UrsprungAuftragNr_        = src.UrsprungAuftragNr                   ;
            dest.UrsprungPosNr_            = src.UrsprungPosNr                       ;
            dest.KundenNr_                 = src.KundenNr                            ;
            dest.VertriebszentrumNr_       = src.VertriebszentrumNr                  ;
            dest.Erfasst_                  = src.Erfasst                             ;
            dest.KdAuftragArt_             = src.KdAuftragArt                        ;
            dest.PosArt_                   = src.PosArt                              ;
            dest.PosArt_.Compress();
            dest.PreisEKApoNetto_          = src.PreisEKApoNetto;
            dest.BatchAuftragNr_           = src.BatchAuftragNr                      ;
            dest.BatchPosNr_               = src.BatchPosNr                          ;
            dest.MengeNatra_               = src.MengeNatra                          ;
            dest.Bemerkungen_              = src.Bemerkungen                         ;
            dest.Bemerkungen_.Strip();
            dest.PreisEKApo_               = src.PreisEKApo                          ;
            dest.PreisVKApo_               = src.PreisVKApo                          ;
            dest.PreisAGP_                 = src.PreisAGP                            ;
            dest.DatumValuta_              = nDate(src.DatumValuta)                  ;
            dest.KoArt_                    = src.KoArt                               ;
            dest.BuchArt_                  = src.BuchArt                             ;
            dest.CodeType_                 = src.Code_Type                           ;
            dest.ArticleCode_              = src.Article_Code                        ;
            dest.DiscountValuePct_         = src.DiscountValuePct                    ;
            dest.MengeBestellt_            = src.MengeBestellt                       ;
            dest.PreisTyp_                 = static_cast<PriceTypeEnum>(src.Preis_Typ);
            return dest;
        }

        /*----------------------------------------------------------------------------*/
        /*  Initialize object.                                                        */
        /*----------------------------------------------------------------------------*/
        void
        pxDeliveryPos :: Init()
        {
            tNACHLIEFERPOS    record;
            memset(&record, 0 , sizeof(tNACHLIEFERPOS));
            KdAuftragArt_ = ' ';
            Assign(*this, record);
            KdAuftragArt_.Strip();
            Bemerkungen_.Strip();
            KoArt_        = '0';
            BuchArt_      = '0';
        }

        /*----------------------------------------------------------------------------*/
        /*  Assign the values of the 'src' instance to self.                          */
        /*  The values of the source instance are exported to the                     */
        /*  tNACHLIEFERPOS struct and then imported to self.                       */
        /*----------------------------------------------------------------------------*/
        pxDeliveryPos&
        pxDeliveryPos :: operator=( const pxDeliveryPos& src)
        {
            tNACHLIEFERPOS record;               // used to export the data of 'src'
            Assign(*this, Assign(record, src));
            return *this;
        }

        /*----------------------------------------------------------------------------*/
        /*  Assign the values of the tNACHLIEFERPOS structure 'src' to             */
        /*  this instance.                                                            */
        /*----------------------------------------------------------------------------*/
        pxDeliveryPos&
        pxDeliveryPos :: operator=( const tNACHLIEFERPOS& src)
        {
            return Assign(*this, src);
        }

        /*----------------------------------------------------------------------------*/
        /*  Add quantity q from quantity ordered. Returns quantity added.             */
        /*----------------------------------------------------------------------------*/
        long
        pxDeliveryPos :: AddQuantity
        (
            const long q
        )
        {
            Menge_ += q;
            SetDirty();
            return q;
        }

        /*----------------------------------------------------------------------------*/
        /*  Subtract quantity q from quantity ordered. Returns quantity subtracted.   */
        /*----------------------------------------------------------------------------*/
        long
        pxDeliveryPos :: SubQuantity
        (
            const long q                      // quantity to be subtracted
        )
        {
            long retval;
            // avoid negative values in stock:
            retval = ( Menge_ - q < 0 ) ? Menge_ : q;
            Menge_ -= retval;
            SetDirty();
            return retval;
        }


        /*----------------------------------------------------------------------------*/
        /*  UndoQuantityPosting inits the deliverypos entry and returns this          */
        /*----------------------------------------------------------------------------*/
        pxVerbund::subsequentDelivery::pxDeliveryPos*
        pxDeliveryPos :: UndoQuantityPosting
        (
        )
        {
            Menge_            = 0;
            FilialNr1_        = 0;
            FilialNr2_        = 0;
            return this;
        }

        /*----------------------------------------------------------------------------*/
        /*  Convert Postyp                                                            */
        /*----------------------------------------------------------------------------*/
        nString
        pxDeliveryPos :: ConvertPosTyp
        (
        )
        {
            static const char* const REMARKS[] = { "VB", "DS", "NL", "", "NR" };

            nString retvalue;

            if (PosTyp_ > 0 && PosTyp_ <= sizeof(REMARKS) / sizeof(char*))
                retvalue = REMARKS[PosTyp_-1];

            return retvalue;
        }

        /*----------------------------------------------------------------------------*/
        /*  Get an object from the data source.                                       */
        /*----------------------------------------------------------------------------*/
        int
        pxDeliveryPos :: Get
        (
            DBAccessMode mode
        )
        {
            tNACHLIEFERPOS record;
            memset(&record, 0, sizeof(tNACHLIEFERPOS));
            record.KdAuftragNr   = KdAuftragNr_;
            record.PosNr         = PosNr_;
            record.PosTyp        = static_cast<short>(PosTyp_);
            record.Datum         = Datum_.GetYYYYMMDD();

            int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
            if (!retval)
                (*this)= record;        // import the data from tNACHLIEFERPOS struct
            else if ( retval > cDBXR_NORMAL )
                ExternalCondition(CMsgStream(), CMSG_AD_DELPOS_NOTFOUND, KdAuftragNr_, PosNr_);
            return retval;
        }

        /*----------------------------------------------------------------------------*/
        /*  Put this object into the data source.                                     */
        /*----------------------------------------------------------------------------*/
        int
        pxDeliveryPos :: Put
        (
        )
        {
            tNACHLIEFERPOS record;
            memset(&record, 0, sizeof(tNACHLIEFERPOS));
            Assign(record, *this);
            return nDBWrite(&record, sizeof(tNACHLIEFERPOS));
        }

        /*----------------------------------------------------------------------------*/
        /*  Delete this object from the data source.                                  */
        /*----------------------------------------------------------------------------*/
        int
        pxDeliveryPos :: Delete
        (
        )
        {
            tNACHLIEFERPOS record;
            memset(&record, 0, sizeof(tNACHLIEFERPOS));
            Assign(record, *this);
            return nDBDelete(&record);
        }

        /*----------------------------------------------------------------------------*/
        /*  Redefine virtual functions inherited from nDBRecord.                      */
        /*----------------------------------------------------------------------------*/
        int
        pxDeliveryPos :: Read
        (
            const void  *record
        )
        {
            return pxNachLieferPosRead((tNACHLIEFERPOS*)record);
        }

        int
        pxDeliveryPos :: ReadLock
        (
            const void  *record
        )
        {
            return pxNachLieferPosReadLock((tNACHLIEFERPOS*)record);
        }

        int
        pxDeliveryPos :: Update
        (
            const void  *record
        )
        {
            return pxNachLieferPosUpdate((tNACHLIEFERPOS*)record);
        }

        int
        pxDeliveryPos :: Delete
        (
            const void  *record
        )
        {
            return pxNachLieferPosDelete((tNACHLIEFERPOS*)record);
        }

        int
        pxDeliveryPos :: Insert
        (
            const void  *record
        )
        {
            return pxNachLieferPosInsert((tNACHLIEFERPOS*)record);
        }

        /*----------------------------------------------------------------------------*/
        /*  CompareTo function redefined from nCollectable.                           */
        /*  Ensures pxDeliveryPos list objects being inserted in the                  */
        /*  following ascending sequence:                                             */
        /*  KdAuftragNr,PosNr                                                         */
        /*----------------------------------------------------------------------------*/
        int
        pxDeliveryPos :: CompareTo
        (
            const nCollectable   *That,
                  void           * /* p */,
            const long           /* lparm */
        )   const
        {
            if ( pxGlobalDataBaseSort )
                return  0;

            pxDeliveryPos *that = (pxDeliveryPos*)That;
            int retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                       : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);
            if ( retval == 0 )
                retval = (PosNr_ == that->PosNr_) ? 0
                       : (PosNr_ > that->PosNr_ ? 1 : -1);

            return retval;
        }

        /*----------------------------------------------------------------------------*/
        /*  List Constructor.                                                         */
        /*----------------------------------------------------------------------------*/
        pxDeliveryPosList :: pxDeliveryPosList
        (
            pxSession   *session
        )
            : nDBRecordSet(session)
        {
            nDBSetList(this);
        }

        /*----------------------------------------------------------------------------*/
        /*  Initialize and do selection via KdAuftragNr, PosNr                        */
        /*----------------------------------------------------------------------------*/
        size_t
        pxDeliveryPosList ::SelectByOrderPosAndDate
        (
            const long    KdAuftragNr,
            const long    PosNr,
            const nDate&  Datum,
            const int     count_
        )
        {
            tNACHLIEFERPOS fil;
            memset(&fil, 0, sizeof(tNACHLIEFERPOS));  // zero out entire record buffer
            fil.KdAuftragNr  = KdAuftragNr;
            fil.PosNr        = PosNr;
            fil.Datum        = Datum.GetYYYYMMDD(); // store key
            int cursorid    = cCRS_DEFAULT;
            if (PosNr == 0)
                cursorid = cCRSDELPOS_ORDERDATUM;
            nDBSelect(&fil, cursorid, count_);

            return Entries();
        }

        /*----------------------------------------------------------------------------*/
        /*  Initialize and do selection via Customer number                           */
        /*----------------------------------------------------------------------------*/
        size_t
        pxDeliveryPosList::SelectCustomersRestDelivery( const long IDFNr, const short VZ )
        {
            tNACHLIEFERPOS fil;
            memset(&fil, 0, sizeof(tNACHLIEFERPOS));  // zero out entire record buffer
            fil.IDFNr        = IDFNr;
            fil.PosTyp       = static_cast<short>(pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
            fil.VertriebszentrumNr = VZ;
            int cursorid    = cCRSDELPOS_IDFNRPOSTYP;
            //if ( PosTyp == pxVerbund::subsequentDelivery::pxDeliveryPos::pxDPT_UNDEFINED )
            //    cursorid    = cCRSDELPOS_IDFNR;
            pxGlobalDataBaseSort = true;

            nDBSelect(&fil, cursorid, 1000);
            pxGlobalDataBaseSort = false;

            return Entries();
        }

        /*----------------------------------------------------------------------------*/
        /*  Initialize and do selection via Customer number                           */
        /*----------------------------------------------------------------------------*/
        size_t pxDeliveryPosList :: SelectCustomersRestDeliveryAndReserveItems( const long IDFNr, const short VZ )
        {
            tNACHLIEFERPOS fil;
            memset(&fil, 0, sizeof(tNACHLIEFERPOS));  // zero out entire record buffer
            fil.IDFNr = IDFNr;
            fil.VertriebszentrumNr = VZ;

            int cursorid = cCRSDELPOS_IDFNRPOSTYP35;
            pxGlobalDataBaseSort = true;

            nDBSelect( &fil, cursorid, 1000 );
            pxGlobalDataBaseSort = false;

            return Entries();
        }

        /*----------------------------------------------------------------------------*/
        /*  Initialize and do selection via KdAuftragNr, datum, postyp                */
        /*----------------------------------------------------------------------------*/
        size_t
        pxDeliveryPosList ::SelectByOrderAndDate
        (
            const long    KdAuftragNr,
            const nDate&  Datum,
            const pxDelPosTyp   PosTyp,
            const int     count_
        )
        {
            tNACHLIEFERPOS fil;
            memset(&fil, 0, sizeof(tNACHLIEFERPOS));  // zero out entire record buffer
            fil.KdAuftragNr  = KdAuftragNr;
            fil.Datum        = Datum.GetYYYYMMDD(); // store key
            fil.PosTyp       = static_cast<short>(PosTyp);
            int cursorid    = cCRSDELPOS_ORDDATPOSTYP;
            nDBSelect(&fil, cursorid, count_);

            return Entries();
        }

        /*----------------------------------------------------------------------------*/
        /*  Initialize and do selection via VZ, IDFNr,Artikel_Nr and postyp           */
        /*----------------------------------------------------------------------------*/
        size_t
        pxDeliveryPosList ::SelectByCustomerAndArticle
        (
            const short   VZ,
            const long    IDFNr,
            const long    ArtikelNr,
            const pxDelPosTyp PosTyp,
            const int     count_
        )
        {
            tNACHLIEFERPOS fil;
            memset(&fil, 0, sizeof(tNACHLIEFERPOS));  // zero out entire record buffer
            fil.VertriebszentrumNr  = VZ;
            fil.IDFNr        = IDFNr;
            fil.ArtikelNr    = ArtikelNr,
            fil.PosTyp       = static_cast<short>(PosTyp);
            int cursorid    = cCRSDELPOS_VZIDFARTPOSTYP;
            nDBSelect(&fil, cursorid, count_);

            return Entries();
        }

        /*----------------------------------------------------------------------------*/
        /*  Initialize and do selection via BranchNo,ArticleNo, PosTyp                */
        /*----------------------------------------------------------------------------*/
        size_t
        pxDeliveryPosList ::SelectByArticle
        (
            const short   VZ,
            const long    ArtikelNr,
            const pxDelPosTyp   PosTyp,
            const int     count_
        )
        {
            tNACHLIEFERPOS fil;
            memset(&fil, 0, sizeof(tNACHLIEFERPOS));  // zero out entire record buffer
            fil.ArtikelNr    = ArtikelNr;
            fil.PosTyp       = static_cast<short>(PosTyp);
            fil.VertriebszentrumNr = VZ;
            int cursorid    = cCRSDELPOS_ARTPOSTYPVZ;
            nDBSelect(&fil, cursorid, count_);

            return Entries();
        }

        /*----------------------------------------------------------------------------*/
        /*  Initialize and do selection via BranchNo,ArticleNo, PosTyp, OrderType     */
        /*----------------------------------------------------------------------------*/
        size_t
        pxDeliveryPosList ::SelectByOrderAndCustomerAndOrderTyp
        (
            const long    KdAuftragNr,
            const short   VZ,
            const long    IdfNr,
            const nString& KdAuftragArt,
            const int     count_
        )
        {
            tNACHLIEFERPOS fil;
            memset(&fil, 0, sizeof(tNACHLIEFERPOS));  // zero out entire record buffer
            fil.KdAuftragNr = KdAuftragNr;
            fil.VertriebszentrumNr = VZ;
            fil.IDFNr = IdfNr;
            strcpy(fil.KdAuftragArt,  " ");
            KdAuftragArt.GetData(fil.KdAuftragArt);
            int cursorid    = cCRSDELPOS_ORDERVZIDFNROTYPE;
            nDBSelect(&fil, cursorid, count_);

            return Entries();
        }

        /*----------------------------------------------------------------------------*/
        /*  Initialize and do selection via BranchNo,ArticleNo, PosTyp, OrderType     */
        /*----------------------------------------------------------------------------*/
        size_t
        pxDeliveryPosList ::SelectByArticleAndOrderType
        (
            const short   VZ,
            const long    ArtikelNr,
            const short   PosTyp,
            const nString& KdAuftragArt,
            const int     count_
        )
        {
            tNACHLIEFERPOS fil;
            memset(&fil, 0, sizeof(tNACHLIEFERPOS));  // zero out entire record buffer
            fil.ArtikelNr    = ArtikelNr;
            fil.PosTyp       = PosTyp;
            fil.VertriebszentrumNr = VZ;
            strcpy(fil.KdAuftragArt,  " ");
            KdAuftragArt.GetData(fil.KdAuftragArt);
            int cursorid    = cCRSDELPOS_ARTPOSTYPVZOTYPE;
            nDBSelect(&fil, cursorid, count_);

            return Entries();
        }

        /*----------------------------------------------------------------------------*/
        /*  Redefine virtual functions inherited from nDBRecordSet.                   */
        /*----------------------------------------------------------------------------*/
        nCollectable*
        pxDeliveryPosList :: AddToList
        (
            const void  *record,
            const int  /* row */
        )
        {
            // construct new 'pxDeliveryPos' object:
            pxDeliveryPos *objectp = new pxDeliveryPos(Session(), *(tNACHLIEFERPOS*) record);
            InsertAscending(objectp);
            return objectp;
        }

        int
        pxDeliveryPosList :: EndBrowse
        (
            const int  cursorid
        )
        {
            return pxNachLieferPosEndBrowse(cursorid);
        }

        int
        pxDeliveryPosList :: GetNext
        (
            const void  *record,
            const int  cursorid
        )
        {
            return pxNachLieferPosGetNext((tNACHLIEFERPOS*)record, cursorid);
        }

        int
        pxDeliveryPosList :: StartBrowse
        (
            const void  *keys,
            const int  cursorid
        )
        {
            return pxNachLieferPosStartBrowse((tNACHLIEFERPOS*)keys, cursorid);
        }

        /*----------------------------------------------------------------------------*/
        /* Find returns a pxDeliveryPos pointer to the corresponding entry. If the    */
        /* entry is not found within the list , so NULLP will be returned             */
        /*----------------------------------------------------------------------------*/
        pxVerbund::subsequentDelivery::pxDeliveryPos*
        pxDeliveryPosList :: Find
        (
            const long       KdAuftragNr,          // Search for this type and
            const long       PosNr,                // this type
            const pxDelPosTyp PosTyp
        )
        {
            pxDeliveryPosListIter   iter( *this );  // define iterator
            pxDeliveryPos          *entryp;         // pointer to listentry

            iter.Reset();                           // top of list
            while ( ( entryp = ( pxVerbund::subsequentDelivery::pxDeliveryPos*) ++iter) != NULL ) // browse list
            {
                if ( (entryp->KdAuftragNr() == KdAuftragNr) &&
                     (entryp->PosNr()  == PosNr) &&  (entryp->DeliveryPosTyp() == PosTyp) )

                    break;
            }
            return   entryp;                        // return entrypointer
        }

        /*----------------------------------------------------------------------------*/
        /* DeleteDCTEntries: Deletes all entries from Type DCT                        */
        /*----------------------------------------------------------------------------*/
        size_t
        pxDeliveryPosList :: DeleteDCTEntries
        (
        )
        {
            pxDeliveryPosListIter   iter( *this );  // define iterator
            pxDeliveryPos          *entryp;         // pointer to listentry

            iter.Reset();                           // top of list
            while ( ( entryp = ( pxVerbund::subsequentDelivery::pxDeliveryPos*) ++iter) != NULL ) // browse list
            {
                if ( entryp->IsPosArtDCT() )
                {
                    entryp->Delete();
                    delete iter.Remove();
                }
            }
            return   Entries();                     // return count
        }

        /*----------------------------------------------------------------------------*/
        /* GetValutaDays;  Get Difference between DatumValuta and Datum in days       */
        /* Returnvalue is count of Months or zero                                     */
        /*----------------------------------------------------------------------------*/
        long
        pxDeliveryPos :: GetValutaDays
        (
        )
        {
            long retval = 0;
            nDate now;
            if ( DatumValuta_ != pxConstants::NullDate && Datum_ != pxConstants::NullDate )
            {
                // ensure dates are valid
                long  currentdays     =  now.GetAbsday();
                long  DatumDays       =  Datum_.GetAbsday();
                retval  = currentdays - DatumDays;
            }
            return retval;
        }

        /*----------------------------------------------------------------------------*/
        /*  SetArticleCodeValues                                                      */
        /*  This methode sets the values of CodeType and ArticleCode into this object */
        /*----------------------------------------------------------------------------*/
        void pxDeliveryPos::SetArticleCodeValues ( const short   CodeType, const nString& ArticleCode )
        {
            CodeType_      = CodeType;
            ArticleCode_   = ArticleCode;
            SetDirty();
        }

        void pxDeliveryPos::SetArtikelNr(long artikelnr)
        {
            ArtikelNr_ = artikelnr;
        }
        void pxDeliveryPos::SetIDFNr(long idfnr)
        {
            IDFNr_ = idfnr;
        }
        void pxDeliveryPos::SetFirstPartnerNr(short vznr)
        {
            FilialNr1_ = vznr;
        }
        void pxDeliveryPos::SetSecondPartnerNr(short vznr)
        {
            FilialNr2_ = vznr;
        }
        void pxDeliveryPos::SetThirdPartnerNr(short vznr)
        {
            FilialNr3_ = vznr;
        }
        void pxDeliveryPos::SetUrsprungAuftragNr(long aufnr)
        {
            UrsprungAuftragNr_ = aufnr;
        }
        void pxDeliveryPos::SetUrsprungPosNr(long posnr)
        {
            UrsprungPosNr_ = posnr;
        }
        void pxDeliveryPos::SetMenge(long menge)
        {
            Menge_ = menge;
        }
        void pxDeliveryPos::SetDeliveryPosTyp(pxDelPosTyp postyp)
        {
            PosTyp_ = postyp;
        }
        void pxDeliveryPos::SetPreisEKApoNetto(nMoney price)
        {
            PreisEKApoNetto_ = price;
        }

        void pxDeliveryPos::SetBatchAuftragNr(long BatchAuftragNr)
        {
            BatchAuftragNr_ = BatchAuftragNr;
        }

        void pxDeliveryPos::SetBatchPosNr(long BatchPosNr)
        {
            BatchPosNr_ = BatchPosNr;
        }
        void pxDeliveryPos::SetMengeNatra(long MengeNatra)
        {
            MengeNatra_ = MengeNatra;
        }

        void pxDeliveryPos::SetBemerkungen(const nString& s)
        {
            Bemerkungen_ = s; SetDirty();
        }

        void pxDeliveryPos::SetPreisEKApo(double aep)
        {
            PreisEKApo_ = aep; SetDirty();
        }

        void pxDeliveryPos::SetPreisVKApo(double avp)
        {
            PreisVKApo_ = avp;
            SetDirty();
        }

        void pxDeliveryPos::SetPreisAGP(double agp)
        {
            PreisAGP_ = agp;
            SetDirty();
        }

        void pxDeliveryPos::SetDatumValuta(const nDate& date)
        {
            DatumValuta_ = date;
            SetDirty();
        }

        void pxDeliveryPos::SetKoArt(const char koart)
        {
            KoArt_ = koart;
            SetDirty();
        }

        void pxDeliveryPos::SetBuchArt(const char buchart)
        {
            BuchArt_ = buchart;
            SetDirty();
        }

        void pxDeliveryPos::SetDiscountValuePct(double value)
        {
            DiscountValuePct_ = value;
            SetDirty();
        }

        void pxDeliveryPos::SetStatus(const pxDelPosStatus status)
        {
            Status_ = status;
            SetDirty();
        }

        void pxDeliveryPos::SetMengeBestellt(const long mengebestellt)
        {
            MengeBestellt_ = mengebestellt;
            SetDirty();
        }

        void pxDeliveryPos::SetPreisTyp(const PriceTypeEnum preistyp)
        {
            PreisTyp_ = preistyp;
            SetDirty();
        }

        void pxDeliveryPos::ForceUpdate()
        {
            SetActive();
        }

        //bool pxDeliveryPos::IsAuxDeliveryItem()  const
        //{
        //    return (PosTyp_ == pxDPT_AUXDELIVERY_ITEM);
        //}

        bool pxDeliveryPos::IsDisPosalItem()     const
        {
            return (PosTyp_ == pxDPT_DISPOSAL_ITEM);
        }

        bool pxDeliveryPos::IsRestDeliveryItem() const
        {
            return (PosTyp_ == pxDPT_RESTDELIVERY_ITEM);
        }

        //bool pxDeliveryPos::IsBatchItem()       const
        //{
        //    return (PosTyp_ == pxDPT_BATCH_ITEM);
        //}

        bool pxDeliveryPos::IsReserveItem()       const
        {
            return (PosTyp_ == pxDPT_RESERVE_ITEM);
        }

        bool pxDeliveryPos::IsGenerated()       const
        {
            return (Status_ == DP_GENERATED);
        }

        bool pxDeliveryPos::IsReadyForWorkUp()  const
        {
            return (Status_ == DP_READY_FOR_WORKUP);
        }

        bool pxDeliveryPos::IsWorkUpDone()      const
        {
            return (Status_ == DP_WORKUP_DONE);
        }

        bool pxDeliveryPos::IsPosArtDCT()       const
        {
            return (PosArt_ == cDP_COMING_BY_DCT);
        }

        bool pxDeliveryPos::IsPosArtTelefone()  const
        {
            return (PosArt_ == cDP_COMING_BY_TELEPHONE);
        }

        bool pxDeliveryPos::IsPosArtBatch()     const
        {
            return (PosArt_ == cDP_COMING_BY_BATCH);
        }

        long             pxDeliveryPos::KdAuftragNr()        const { return KdAuftragNr_; }
        long             pxDeliveryPos::PosNr()              const { return PosNr_; }
        const nDate&     pxDeliveryPos::Datum()              const { return Datum_; }
        short            pxDeliveryPos::DeliveryPosTyp()             const { return static_cast<short>(PosTyp_); }
        long             pxDeliveryPos::IDFNr()              const { return IDFNr_; }
        long             pxDeliveryPos::ArtikelNr()          const { return ArtikelNr_; }
        long             pxDeliveryPos::Menge()              const { return Menge_; }
        short            pxDeliveryPos::FirstPartnerNr()     const { return FilialNr1_; }
        short            pxDeliveryPos::SecondPartnerNr()    const { return FilialNr2_; }
        short            pxDeliveryPos::ThirthPartnerNr()    const { return FilialNr3_; }
        long             pxDeliveryPos::Status()             const { return Status_; }
        long             pxDeliveryPos::UrsprungAuftragNr()  const { return UrsprungAuftragNr_; }
        long             pxDeliveryPos::UrsprungPosNr()      const { return UrsprungPosNr_; }
        long             pxDeliveryPos::KundenNr()           const { return KundenNr_; }
        short            pxDeliveryPos::VertriebszentrumNr() const { return VertriebszentrumNr_; }
        long             pxDeliveryPos::Erfasst()            const { return Erfasst_; }
        const nString&   pxDeliveryPos::KdAuftragArt()       const { return KdAuftragArt_; }
        const nString&   pxDeliveryPos::PosArt()             const { return PosArt_; }
        nMoney           pxDeliveryPos::PreisEKApoNetto()    const { return PreisEKApoNetto_; }
        long             pxDeliveryPos::BatchAuftragNr()     const { return BatchAuftragNr_; }
        long             pxDeliveryPos::BatchPosNr()         const { return BatchPosNr_; }
        long             pxDeliveryPos::MengeNatra()         const { return MengeNatra_; }
        const nString&   pxDeliveryPos::Bemerkungen()        const { return Bemerkungen_; }
        nMoney           pxDeliveryPos::PreisEKApo()         const { return PreisEKApo_; }
        nMoney           pxDeliveryPos::PreisVKApo()         const { return PreisVKApo_; }
        nMoney           pxDeliveryPos::PreisAGP()           const { return PreisAGP_; }
        const nDate&     pxDeliveryPos::DatumValuta()        const { return DatumValuta_; }
        char             pxDeliveryPos::KoArt()              const { return KoArt_; }
        char             pxDeliveryPos::BuchArt()            const { return BuchArt_; }
        short            pxDeliveryPos::CodeType()           const { return CodeType_; }
        double           pxDeliveryPos::DiscountValuePct()   const { return DiscountValuePct_; }
        long             pxDeliveryPos::MengeBestellt()      const { return MengeBestellt_; }
        PriceTypeEnum    pxDeliveryPos::PreisTyp()           const { return PreisTyp_; }

        const nString&   pxDeliveryPos::ArticleCode()        const { return ArticleCode_; }


    } // end namespace subsequentDelivery
} // end namespace pxVerbund
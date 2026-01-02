#ifndef PXDELPOS_INC
#define PXDELPOS_INC

#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"
#include <date.hpp>
#include <money.hpp>

class pxVartikelLokal;
class pxOrderItem;
struct tNACHLIEFERPOS;

#define cDP_COMING_BY_DCT         "D"
#define cDP_COMING_BY_TELEPHONE   "P"
#define cDP_COMING_BY_BATCH       "B"

namespace pxVerbund
{
    namespace subsequentDelivery
    {

        enum pxDelPosTyp
        {
            pxDPT_UNDEFINED         = 0,         // undefined type
            pxDPT_AUXDELIVERY_ITEM  = 1,         // auxdelivery
            pxDPT_DISPOSAL_ITEM     = 2,         // disposal
            pxDPT_RESTDELIVERY_ITEM = 3,         // restdelivery
            pxDPT_BATCH_ITEM        = 4,         // batchitem
            pxDPT_RESERVE_ITEM      = 5          // reserve quantity for the customer
        };

        enum pxDelPosStatus
        {
            DP_GENERATED,                        // default value
            DP_READY_FOR_WORKUP,                 // ready for worke up
            DP_WORKUP_DONE,                      // workup done
            DP_WORK_INPROGRESS					 // work in progress by another task
        };

        class pxDeliveryPos : public pxDBRecord
        {
            private:
                friend class pxDeliveryPosList;

            public:
                pxDeliveryPos(pxVerbund::subsequentDelivery::pxDeliveryPos& src);
                pxDeliveryPos(pxOrderItem& Item, pxDelPosTyp PosType);
                pxDeliveryPos(pxSession* session);
                pxDeliveryPos(pxSession* session, tNACHLIEFERPOS& src);
                pxDeliveryPos(pxSession* session, long  KdAuftragNr, long  PosNr, nDate date,  pxDelPosTyp Postype, DBAccessMode mode = cDBGET_READONLY);
                
                virtual  ~pxDeliveryPos();
                
                /*@DS PUBLIC MEMBER OPERATORS */
                pxDeliveryPos& operator=(const pxDeliveryPos& src);
                pxDeliveryPos& operator=(const tNACHLIEFERPOS& src);
                

                /*@DS PUBLIC MEMBER FUNCTIONS */
                friend   pxDeliveryPos&     Assign(pxDeliveryPos& dest, const tNACHLIEFERPOS& src);
                friend   tNACHLIEFERPOS&    Assign(tNACHLIEFERPOS& dest, const pxDeliveryPos& src);

                virtual  int                CompareTo(const nCollectable* that, void* p, const long lparm) const;

                virtual  int                Get(DBAccessMode mode = cDBGET_READONLY);
                virtual  int                Put();
                virtual  int                Delete();

                virtual  int                Read(const void* record);
                virtual  int                ReadLock(const void* record);
                virtual  int                Insert(const void* record);
                virtual  int                Update(const void* record);
                virtual  int                Delete(const void* record);

                virtual  long               AddQuantity(const long q);
                virtual  long               SubQuantity(const long q);
                pxDeliveryPos*              UndoQuantityPosting();
                nString                     ConvertPosTyp();

//                bool                        IsAuxDeliveryItem()  const;
                bool                        IsDisPosalItem()     const;
                bool                        IsRestDeliveryItem() const;
//                bool                        IsBatchItem()       const;
                bool                        IsReserveItem()       const;
                bool                        IsGenerated()       const;
                bool                        IsReadyForWorkUp()  const;
                bool                        IsWorkUpDone()      const;
                bool                        IsPosArtDCT()       const;
                bool                        IsPosArtTelefone()  const;
                bool                        IsPosArtBatch()     const;

                void                        SetArtikelNr(long artikelnr);
                void                        SetIDFNr(long idfnr);
                void                        SetFirstPartnerNr(short vznr);
                void                        SetSecondPartnerNr(short vznr);
                void                        SetThirdPartnerNr(short vznr);
                void                        SetUrsprungAuftragNr(long aufnr);
                void                        SetUrsprungPosNr(long posnr);
                void                        SetMenge(long menge);
                void                        SetDeliveryPosTyp(pxDelPosTyp postyp);
                void                        SetPreisEKApoNetto(nMoney price);
                void                        SetBatchAuftragNr(long BatchAuftragNr);
                void                        SetBatchPosNr(long BatchPosNr);
                void                        SetMengeNatra(long MengeNatra);
                void                        SetKoArt(const char koart);
                void                        SetBuchArt(const char buchart);
                void                        SetArticleCodeValues(const short typ, const nString& code);
                void                        SetDiscountValuePct(double value);
                void                        SetStatus(const pxDelPosStatus status);
                void                        SetMengeBestellt(const long mengebestellt);
                void                        SetPreisTyp(const PriceTypeEnum preistyp);
                void                        SetDatumValuta(const nDate& date);
                void                        SetBemerkungen(const nString& s);
                void                        SetPreisEKApo(double aep);
                void                        SetPreisVKApo(double avp);
                void                        SetPreisAGP(double agp);
                
                void                        ForceUpdate(); // { SetActive(); }
                
                //  Queries:
                const nString&              ArticleCode()        const;
                long                        KdAuftragNr()        const;
                long                        PosNr()              const;
                const nDate&                Datum()              const;
                short                       DeliveryPosTyp()     const;
                long                        IDFNr()              const;
                long                        ArtikelNr()          const;
                long                        Menge()              const;
                short                       FirstPartnerNr()     const;
                short                       SecondPartnerNr()    const;
                short                       ThirthPartnerNr()    const;
                long                        Status()             const;
                long                        UrsprungAuftragNr()  const;
                long                        UrsprungPosNr()      const;
                long                        KundenNr()           const;
                short                       VertriebszentrumNr() const;
                long                        Erfasst()            const;
                const nString&              KdAuftragArt()       const;
                const nString&              PosArt()             const;
                nMoney                      PreisEKApoNetto()    const;
                long                        BatchAuftragNr()     const;
                long                        BatchPosNr()         const;
                long                        MengeNatra()         const;
                const nString&              Bemerkungen()        const;
                nMoney                      PreisEKApo()         const;
                nMoney                      PreisVKApo()         const;
                nMoney                      PreisAGP()           const;
                const nDate&                DatumValuta()        const;
                char                        KoArt()              const;
                char                        BuchArt()            const;
                short                       CodeType()           const;
                double                      DiscountValuePct()   const;
                long                        MengeBestellt()      const;
                PriceTypeEnum               PreisTyp()           const;

                // get difference between DatumValuta and Datum in Days
                long                        GetValutaDays();
                
                void                        Init();

            //protected:
            private:

                ////////////////////////////////////////////////////////////////////////////
                // member variables section
                ////////////////////////////////////////////////////////////////////////////
                long            KdAuftragNr_;           // Kunden Auftragsnummer
                long            PosNr_;                 // Positionsnummer
                nDate           Datum_;                 // Datum
                pxDelPosTyp     PosTyp_;                // Position Typ
                long            IDFNr_;                 // Kundennummer
                long            ArtikelNr_;             // Artikelnummer
                long            Menge_;                 // Liefermenge
                short           FilialNr1_;             // Verbundpartner 1
                short           FilialNr2_;             // Verbundpartner 2
                short           FilialNr3_;             // Verbundpartner 3
                long            Status_;                // Status Nachlieferpos
                long            UrsprungAuftragNr_;     // Ursprungsauftragnummer
                long            UrsprungPosNr_;         // Ursprungspositionsnummer
                long            KundenNr_;              // Kunden Nummer VZ
                short           VertriebszentrumNr_;    // Vertriebszentrum
                long            Erfasst_;               // erfasst
                nString         KdAuftragArt_;          // kdauftragart
                nString         PosArt_;                // Posart
                nMoney          PreisEKApoNetto_;       // PreisEKApoNetto
                long            BatchAuftragNr_;        // Batchorder number from VSE Order
                long            BatchPosNr_;            // Batchpos   number from VSE Order
                long            MengeNatra_;            // MengeNatra from Batchpos
                nString         Bemerkungen_;           // Bemerkungen
                nMoney          PreisEKApo_;            // Preis EK Apotheke
                nMoney          PreisVKApo_;            // Preis VK Apotheke
                nMoney          PreisAGP_;              // Spezial Preis Schweiz
                nDate           DatumValuta_;           // DatumValuta
                char            KoArt_;                 // Kommissionierungsart
                char            BuchArt_;               // Buchungsart
                short           CodeType_;              // Articlecodes  Typ
                nString         ArticleCode_;           // Articlecodes  Articlecode
                double          DiscountValuePct_;      // DiscountValue Percent
                long            MengeBestellt_;         // MengeBestellt (original Bestellmenge)
                PriceTypeEnum   PreisTyp_;              // PreisTyp
        };

        class pxDeliveryPosList : public nDBRecordSet, public nDListCollect
        {
            public:
                pxDeliveryPosList(pxSession* session);
                virtual ~pxDeliveryPosList() { Clear(); }
                pxSession* Session() { return (pxSession*)DataBase(); }

                size_t                  SelectByOrderPosAndDate(                    const long KdAuftragNr, const long PosNr, const nDate& Datum, const int count = 500);
                size_t                  SelectCustomersRestDelivery(                const long IDFNr, const short VZ );
                size_t                  SelectCustomersRestDeliveryAndReserveItems( const long IDFNr, const short VZ );
                size_t                  SelectByOrderAndDate(                       const long  KdAuftragNr, const nDate& Datum, 
                                                                                    const pxDelPosTyp PosTyp, const int  count = 1000 );
                size_t                  SelectByCustomerAndArticle(                 const short VZ, const long  IDFNr, const long  Artikel_Nr, 
                                                                                    const pxDelPosTyp PosTyp, const int count = 1000 );
                size_t                  SelectByArticle(                            const short VZ, const long Artikel_Nr, const pxDelPosTyp PosTyp, const int count = 1000 );
                size_t                  SelectByOrderAndCustomerAndOrderTyp(        const long KdAuftragNr, const short VZ,const long IdfNr, const nString& KdAuftragArt, const int count_ = 1000);
                size_t                  SelectByArticleAndOrderType(                const short VZ, const long Artikel_Nr, const short PosTyp, const nString& KdAuftragArt, const int count = 1000 );

                void                    Clear() { nDBRecordSet::Clear(); }

                virtual  nCollectable*  AddToList(const void* record, const int row);
                virtual  int            GetNext(const void* record, const int cursorid);
                virtual  int            StartBrowse(const void* keys, const int cursorid);
                virtual  int            EndBrowse(const int cursorid);

                pxDeliveryPos*          Find(const long KdAuftragNr, const long PosNr, const pxDelPosTyp PosTyp);
                size_t                  DeleteDCTEntries();

            private:
                friend class pxDeliveryPosListIter;
        };

        class pxDeliveryPosListIter : public nDListCollectIter
        {

            public:
                pxDeliveryPosListIter(pxDeliveryPosList& list) : nDListCollectIter(list) { ; }
                virtual  ~pxDeliveryPosListIter() { ; }
        };

    } // end namespace subsequentDelivery
} // end namespace pxVerbund

#endif

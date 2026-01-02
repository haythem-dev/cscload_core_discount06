#ifndef PXORDVTR_INC
   #define PXORDVTR_INC

#include "pxbase/pxrecord.hpp"

class pxCustBase;
class CSCCustomer;
struct tAUFTRAGARTKOMB;

class pxOrderValidTrans : public pxDBRecord
{
	public:
		virtual							~pxOrderValidTrans() {;}

										pxOrderValidTrans(pxSession *session);

										pxOrderValidTrans(pxOrderValidTrans& src);

										pxOrderValidTrans(pxSession *session,tAUFTRAGARTKOMB& src);

										pxOrderValidTrans(pxSession *session, const pxOrderValidTrans* src);

										pxOrderValidTrans(pxSession *session, nString& KdAuftragArt, short VertriebszentrumNr, DBAccessMode mode = cDBGET_READONLY);


		pxOrderValidTrans&				operator=(const pxOrderValidTrans& src);
		virtual  int					Get(DBAccessMode mode = cDBGET_READONLY);
		virtual  int					Put();
		const nString&					KdAuftragArt() const;
		char							BuchArt() const;
		char							KoArt() const;
		const nString&					TourId() const;
		short							VertriebszentrumNr() const;
		bool							isCalcExpressDeliveryCharge() const;

	protected:
		pxOrderValidTrans&				operator=(const tAUFTRAGARTKOMB& src);

		friend pxOrderValidTrans&		Assign(pxOrderValidTrans& dest, const tAUFTRAGARTKOMB& src);

		friend tAUFTRAGARTKOMB&			Assign(tAUFTRAGARTKOMB& dest, const pxOrderValidTrans& src);

		virtual  int					CompareTo(const nCollectable *e, void *p, const long lparm) const;
    
		void							Init();
    
		virtual  int					Insert(const void *record);

		virtual  int					Update(const void *record);

		virtual  int					Read(const void *record);

		virtual  int					ReadLock(const void *record);

		nString							KdAuftragArt_;    
		char							KoArt_;           
		char							BuchArt_;         
		nString							TourId_;          
		short							VertriebszentrumNr_;
		short							CalcExpressDeliveryCharge_;


	private:
		friend class pxOrderValidTransList;
};

class pxOrderValidTransList : public nDListCollect, public nDBRecordSet
{
public:
                      virtual  ~pxOrderValidTransList() {Clear();}
                      pxOrderValidTransList(pxSession *session);

    void              Clear()        {nDBRecordSet::Clear();}
    pxSession*        Session()      {return (pxSession*) DataBase();}
    size_t            Select (const short VertriebszentrumNr);

    bool              IsValidCommiType(const nString& KdAuftragArt, const char KoArt) const
                      {return (Find(KdAuftragArt, KoArt, cDEFAULT) != NULL);}

    bool              IsValidStockTrans(const nString& KdAuftragArt, const char BuchArt) const
                      {return (Find(KdAuftragArt, cDEFAULT, BuchArt) != NULL);}

    bool              IsValidTrans(const nString& KdAuftragArt, const char KoArt, const char BuchArt) const
                      {return (Find(KdAuftragArt, KoArt, BuchArt) != NULL);}

    pxOrderValidTrans* Find(const nString& KdAuftragArt,
                            const int      BuchArt = cDEFAULT,
                            const int      KoArt   = cDEFAULT,
                            const short   VZNr    = 0 ) const;

    pxOrderValidTrans* Find(pxCustBase&    customer,
                            const nString& KdAuftragArt,
                            const int      BuchArt = cDEFAULT,
                            const int      KoArt   = cDEFAULT ) const;    

	pxOrderValidTrans* FindByCustomer( CSCCustomer* customer, const nString& OrderType, const int CommiType = cDEFAULT, const int StockTrans = cDEFAULT );

    short             Find( const short BranchNo);

protected:
    virtual  int     EndBrowse(const int cursorid);
    virtual
    nCollectable*    AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);

private:
    friend class pxOrderValidTransListIter;
};

class pxOrderValidTransListIter : public nDListCollectIter
{
public:
    pxOrderValidTransListIter(pxOrderValidTransList& list) : nDListCollectIter(list) {;}
    virtual  ~pxOrderValidTransListIter() {;}
};

#endif

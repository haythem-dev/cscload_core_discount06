#ifndef CUSTINFO_INC
#define CUSTINFO_INC

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAGINFO;

class pxCustOrderInfo : public pxDBRecord
{

public:
// constructors:
                pxCustOrderInfo(pxCustOrderInfo& src);
                pxCustOrderInfo(pxSession *session);
                pxCustOrderInfo(pxSession *session, tKDAUFTRAGINFO& src);
                pxCustOrderInfo(pxSession *session, nString& KdAuftragBestellNr,
                                nString& IDFNrIntern, nString& ApoTourId, nString& VersandArt,
                                nString& ProcessNr);
                pxCustOrderInfo(pxSession *session, nString& KdAuftragBestellNr,
                                long IDFNrIntern, nString& ApoTourId, nString& VersandArt,
                                long ProcessNr);

                pxCustOrderInfo(pxSession *session,long KdAuftragNr, nString& KdAuftragBestellNr,
                                 DBAccessMode mode = cDBGET_READONLY);

                pxCustOrderInfo(pxSession *session,long  KdAuftragNr,
                         DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxCustOrderInfo();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustOrderInfo&   operator=(const pxCustOrderInfo& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustOrderInfo&   operator=(const tKDAUFTRAGINFO& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustOrderInfo&
                Assign(pxCustOrderInfo& dest, const tKDAUFTRAGINFO& src);
    friend   tKDAUFTRAGINFO&
                Assign(tKDAUFTRAGINFO& dest, const pxCustOrderInfo& src);


    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

    virtual  int     Read(const void *record);
    virtual  int     Insert(const void *record);

    void              CheckMembers();

//  Queries:
    long             KdAuftragNr()        {return KdAuftragNr_        ;}
    nString&          KdAuftragBestellNr() {return KdAuftragBestellNr_ ;}
    long             IDFNrIntern()        {return IDFNrIntern_        ;}
    nString&          ApoTourId()          {return ApoTourId_          ;}
    nString&          VersandArt()         {return VersandArt_         ;}
    long             ProcessNr()          {return ProcessNr_          ;}
    char             EdiLieferSchein()    {return EdiLieferSchein_    ;}
    long             BatchAuftragNr()     {return BatchAuftragNr_     ;}

// Update members

    void              SetOrderNr(long ordernr) { KdAuftragNr_ = ordernr;}
    void              SetKdAuftragBestellNr(nString& BestellNr){KdAuftragBestellNr_ = BestellNr;}
    void              SetBatchOrderNr(long batchordernr) { BatchAuftragNr_ = batchordernr;}
    void              SetEdiLieferSchein(char edils) { EdiLieferSchein_ = edils;}
	void              SetProcessNr(long processno) { ProcessNr_ = processno; }
protected:
    void        Init();

    long       KdAuftragNr_       ;      // Auftragsnummer
    nString     KdAuftragBestellNr_;      // Interne KundenAuftragsnummer
    long       IDFNrIntern_       ;      // Interne Apotheken Kundennummer
    nString     ApoTourId_         ;      // Intern Apotheken TourId
    nString     VersandArt_        ;      // Apotheken Versandart
    long       ProcessNr_         ;      // Apotheken Vorgangsnummer
    char       EdiLieferSchein_   ;      // Edi Lieferschein
    long       BatchAuftragNr_    ;      // Batch Auftragnummer

private:
};

#endif

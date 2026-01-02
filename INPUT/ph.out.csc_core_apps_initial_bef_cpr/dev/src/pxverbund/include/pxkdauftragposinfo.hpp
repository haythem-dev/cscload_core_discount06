/* *********************************************** */

#ifndef PXKDAUFTRAGPOSINFO_DOTH
#define PXKDAUFTRAGPOSINFO_DOTH

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAGPOS;

class pxKdauftragposInfo : public pxDBRecord
{

public:
    virtual           ~pxKdauftragposInfo();
                      pxKdauftragposInfo(pxKdauftragposInfo& src);
                      pxKdauftragposInfo(pxSession *session);
                      pxKdauftragposInfo(pxSession *session, long KdauftragNr, long PosNr, const nString& Computer,
                                DBAccessMode mode = cDBGET_READONLY);

    pxKdauftragposInfo&        operator=(const tKDAUFTRAGPOS& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.
    pxKdauftragposInfo&        operator=(const pxKdauftragposInfo& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    virtual  int     Get(DBAccessMode mode = cDBGET_FORUPDATE);

    virtual  nError& Error() { return nError::Error(); }
	virtual  bool    IsGoodState() {return nError::IsGoodState(); }

    virtual  int     Read(const void *record);

//  Queries:
	void			setDBName( nString& name) { DBName_ = name; }


    long              KdAuftragNr    () const {return KdAuftragNr_            ; }
	long              PosNr          () const {return PosNr_                  ; }
    nString&          TourIdIBT      ()       {return TourIdIBT_              ; }
    short             IBTTourWeekDay (){return IBTTourWeekDay_                ; }


protected:

    friend pxKdauftragposInfo& Assign(pxKdauftragposInfo& dest, const tKDAUFTRAGPOS& src);
    friend tKDAUFTRAGPOS&  Assign(tKDAUFTRAGPOS& dest, const pxKdauftragposInfo& src);

    void              Init();

    nString           DBName_;          // Datenbank, auf dem sich dieser Bestand befindet
    long              KdAuftragNr_;     // KdAuftragNr
    long              PosNr_;           // Positionsnummer
    nString           TourIdIBT_;       // Tourid IBT
    short             IBTTourWeekDay_;  // IBT weekday
};
#endif

/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXCOUNTRYCODES.HPP
Country Codes class(Code_blockage etc).

REVISION HISTORY

27 March 2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCOUNTRYCODES_DOTH
#define PXCOUNTRYCODES_DOTH

#include "pxbase/pxrecord.hpp"

struct tCOUNTRYCODES;

class pxCountryCodes : public pxDBRecord
{

public:
/*----------------------------------------------------------------------------*/
/*  Enumerations and manifest constants.                                      */
/*----------------------------------------------------------------------------*/
    enum CountryCode_Type
    {
       CCT_INFOCODE,                    // 0 for INFOCODE
       CCT_XMLCODE                      // 1 for XMLCODE
    };

    virtual           ~pxCountryCodes();
                      pxCountryCodes(pxCountryCodes& src);
                      pxCountryCodes(pxSession *session);
                      pxCountryCodes(pxSession *session, short BranchNo,nString& InfoCode,
                                 DBAccessMode mode = cDBGET_READONLY);

    pxCountryCodes&       operator=(const pxCountryCodes& src);
    pxCountryCodes&       operator=(const tCOUNTRYCODES& src);

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);

//  Queries:
    short            BranchNo          () {return BranchNo_         ; }
    nString&          InfoCode          () {return InfoCode_         ; }
    char             ArticleActiv      () {return ArticleActiv_     ; }
    char             AuxDelivery       () {return AuxDelivery_      ; }
    nString&          SeraCode          () {return SeraCode_         ; }
    nString&          PrintCode         () {return PrintCode_        ; }
    nString&          XMLCode           () {return XMLCode_          ; }
    nString&          XMLText           () {return XMLText_          ; }

//  Updates:
protected:
                      pxCountryCodes(pxSession *session, tCOUNTRYCODES& src);
    void              Init();
    friend
    pxCountryCodes&       Assign(pxCountryCodes& dest, const tCOUNTRYCODES& src);
    friend
    tCOUNTRYCODES&    Assign(tCOUNTRYCODES& dest, const pxCountryCodes& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    short            BranchNo_;              // BranchNo
    nString           InfoCode_;              // InfoCode(Code_Blockage)
    char             ArticleActiv_;          // Article activ sign
    char             AuxDelivery_;           // Auxdelivery sign
    nString           SeraCode_;              // DcT Code(Seriell)
    nString           PrintCode_;             // PrintCode
    nString           XMLCode_;               // XmlCode(ErrorCode)
    nString           XMLText_;               // XmlText

private:
                      pxCountryCodes();
    friend class pxCountryCodesList;
};

class pxCountryCodesList : public nDListCollect, public nDBRecordSet
{

public:
// constructors:
                pxCountryCodesList(pxSession *session);
// destructor:
                virtual  ~pxCountryCodesList() {Clear();}
// member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}
    size_t      Select ( const short BranchNo,const nString& Code,
                         const short Type = 0,
                         const int   count = 50 );
    size_t      Select ( tCOUNTRYCODES *a, const short Type = 0, const int count = 50 );
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
protected:

private:
    friend class pxCountryCodesListIter;
};

class pxCountryCodesListIter : public nDListCollectIter
{

public:
// constructors:
    pxCountryCodesListIter(pxCountryCodesList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCountryCodesListIter() {;}
};

#endif

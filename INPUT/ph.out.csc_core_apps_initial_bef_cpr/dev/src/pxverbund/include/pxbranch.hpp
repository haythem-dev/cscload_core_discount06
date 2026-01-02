/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXBRANCH.HPP
Branch Class.

REVISION HISTORY

21 Nov 1995 V1.00 REV 00 written by Peter Hoernich.
*/

#ifndef PXBRANCH_INC
#define PXBRANCH_INC

#include "pxbase/pxrecord.hpp"

struct tFILIALE;
struct tFILIALE;

class pxBranch : public pxDBRecord
{

public:
// constructors:
                pxBranch(pxBranch& src);
                pxBranch(pxSession *session);
                pxBranch(pxSession *session, tFILIALE& src);
                pxBranch(pxSession *session,
                         short FilialNr,
                         DBAccessMode mode = cDBGET_READONLY);
// destructor:
                virtual  ~pxBranch();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxBranch&   operator=(const pxBranch& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxBranch&   operator=(const tFILIALE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxBranch&
                      Assign(pxBranch& dest, const tFILIALE& src);
    friend   tFILIALE&
                      Assign(tFILIALE& dest, const pxBranch& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int      Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int      Put();

    virtual  int      Read(const void *record);
    virtual  int      ReadLock(const void *record);
    virtual  int      Insert(const void *record);
    virtual  int      Update(const void *record);

//  Queries:
             short    FilialNr          () {return FilialNr_;                  }
             long     BGANr             () {return BGANr_;                     }
    const    nString& Bezeichnung       () {return Bezeichnung_;               }
    const    nString& Strasse           () {return Strasse_;                   }
    const    nString& Ort               () {return Ort_;                       }
    const    nString& Postleitzahl      () {return Postleitzahl_;              }
    const    nString& Vorwahl           () {return Vorwahl_;                   }
    const    nString& TelNrOVw          () {return TelNrOVw_;                  }
    const    nString& FaxNrOVw          () {return FaxNrOVw_;                  }
             long     BGANr_EK          () {return BGANr_EK_;                  }
             short&   Store             () {return Store_;                     }

protected:
    void        Init();

    short       FilialNr_;              // Filialnummer
    long        BGANr_;                 // BGA-Nummer
    nString     Bezeichnung_;
    nString     Strasse_;
    nString     Ort_;
    nString     Postleitzahl_;
    nString     Vorwahl_;               // Telefonvorwahl
    nString     TelNrOVw_;              // Telefonnummer ohne Vorwahl
    nString     FaxNrOVw_;              // Faxnummer ohne Vorwahl
    long        BGANr_EK_;              // BGA-Nummer (unique für Verbund)
    short       Store_;                 // Filialnr of customer

private:
    friend class pxBranchList;
};

class pxBranchList : public nDBRecordSet, public nDListCollect
{

public:
//  constructors:
                pxBranchList(pxSession *session);
//  destructor:
                virtual ~pxBranchList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int count = 50 );

    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int      GetNext(const void* record, const int cursorid);
    virtual  int      StartBrowse(const void *keys, const int cursorid);
    virtual  int      EndBrowse(const int cursorid);

protected:

private:
    friend class pxBranchListIter;
};

class pxBranchListIter : public nDListCollectIter
{

public:
// constructors:
    pxBranchListIter(pxBranchList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxBranchListIter() {;}
};
#endif

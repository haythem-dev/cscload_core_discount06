/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxItemBatch Class.

REVISION HISTORY

04 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXITEMBATCH_INC
   #define PXITEMBATCH_INC

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAGPOSCHARGE;

class pxItemBatch : public pxDBRecord
{

public:


// constructors:
                pxItemBatch(pxItemBatch& src);
                pxItemBatch(pxSession *session);
                pxItemBatch(pxSession *session, tKDAUFTRAGPOSCHARGE& src);
                pxItemBatch(pxSession *session, const long KdAuftragNr, const long PosNr);
// destructor:
                virtual  ~pxItemBatch();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxItemBatch&   operator=(const pxItemBatch& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxItemBatch&   operator=(const tKDAUFTRAGPOSCHARGE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxItemBatch&
                Assign(pxItemBatch& dest, const tKDAUFTRAGPOSCHARGE& src);
    friend   tKDAUFTRAGPOSCHARGE&
                Assign(tKDAUFTRAGPOSCHARGE& dest, const pxItemBatch& src);

    virtual  int    CompareTo(const nCollectable *that, void *p,
                               const long lparm) const;

    virtual  int    Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int    Put();
    virtual  int    Delete();

    virtual  int    Read(const void *record);
    virtual  int    ReadLock(const void *record);
    virtual  int    Insert(const void *record);
    virtual  int    Update(const void *record);
    virtual  int    Delete(const void *record);

//  Queries:
    long			KdAuftragNr()         {return KdAuftragNr_     ;}
    long			PosNr()               {return PosNr_           ;}
    nString&		BatchNr()			  {return BatchNr_         ;}
    long			QuantityOrdered()     {return QuantityOrdered_ ;}
	short		    FixBatch()			  {return FixBatch_		   ;}

//  Field Updates:
    void			SetBatchNr( nString& num)
					{BatchNr_ = num; SetDirty();}
    void			SetQuantityOrdered( long q)
					{QuantityOrdered_  = q; SetDirty();}
	void			SetFixBatch(const short fixBatch)
					{FixBatch_ = fixBatch; SetDirty();}

protected:
    void			Init();

    long			KdAuftragNr_;       // Ordernumber
    long			PosNr_;             // PosNr
    nString			BatchNr_;			// Chargennummer
    long			QuantityOrdered_;   // Quantity ordered
	short			FixBatch_;			// Wunsch oder Pflichtcharge

private:
    friend class pxItemBatchList;

};

class pxItemBatchList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxItemBatchList(pxSession *session);
//  destructor:
                virtual ~pxItemBatchList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select(const long KdAuftragNr,const long PosNr, const int count = 100);
    void        Clear(){nDBRecordSet::Clear();}

    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int		   GetNext(const void* record, const int cursorid);
    virtual  int		   StartBrowse(const void *keys, const int cursorid);
    virtual  int		   EndBrowse(const int cursorid);

protected:

private:
    friend class pxItemBatchListIter;
};

class pxItemBatchListIter : public nDListCollectIter
{

public:
// constructors:
    pxItemBatchListIter(pxItemBatchList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxItemBatchListIter() {;}
};
#endif

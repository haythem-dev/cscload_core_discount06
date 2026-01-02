#ifndef PXVARTIKELLOKALLIST_HPP
#define PXVARTIKELLOKALLIST_HPP

#include "pxvartikellokal.hpp"
#include "pxorderentryparamptr.h"

class pxVartikelLokalList : public nDListCollect, public nDBRecordSet
{
public:
    enum ASLLAccessMode
    {
        cASLL_NOZEROENTRIES     = 1,    // list no entries with bestand = 0
        cASLL_WITHZEROENTRIES   = 2,    // list also entries with bestand = 0
        cASLL_NOPRIVATPRODUCT   = 4     // list no privatproduct from zentralstore
    };

                            pxVartikelLokalList(pxSession* session, pxOrderEntryParamPtr param);
    virtual                 ~pxVartikelLokalList() {Clear();}

    pxVartikelLokal*        QuantityInList( const long q );
    pxVartikelLokal*        GetPreferedEntry(const long q, const short custfil);
    pxVartikelLokal*        FindArticleNo( const long  ArtikelNr );
    pxVartikelLokal*        QSatisfy( const long q, const short FilialNr );

    pxVartikelLokal*        Find( const short FilialNr );

    pxVartikelLokalList*    getIBTWarehouseStockList(
								const long articleno, const short branchno, long customerno, pxOrder* order );
    pxVartikelLokalList*    getIBTWarehouseStockListWithoutTimeCheck(
                                const long articleno, const short branchno, long customerno, pxOrder* order );
    pxVartikelLokalList*    getIBTWarehouseStockListGeneral(const long articleno, const short branchno);
    pxVartikelLokal*        getNLevelIBTEntryToBeUsed( const long requestedquantity );		

protected:
    pxVartikelLokalList*    getIBTWarehouseStockList(
                                long const articleno, short const branchno, long customerno, short checkTimeTypes, pxOrder* order);

private:

    short                   m_CheckTimeTypes;

    void                    Clear()        {nDBRecordSet::Clear();}
    pxSession*              Session()      { return (pxSession*) DataBase();}

	void					applyArticleQuotas(const short branchno);

    pxVartikelLokal*        getMatchingNLevelIBTEntry( const long requestedquantity );

    int                     ShrinkDoubleEntriesAndBranchesWithoutStock( bool removeStockLevel0 = true );	
	int						ShrinkBranchesWithTransportExclusion(pxOrder* order);	

    int                     CheckArticleQuota( const long ArtikelNr, short  branchfil, const long CustomerNo );
    int                     Shrink(const short FilialNr);
    int                     CountEntries(const short FilialNr, const short NLevelIBTTypeId);
    bool                    hasEntriesWithHigherNLevelIBTType(const short FilialNr, const short NLevelIBTTypeId);

    size_t                  IBTBranchesSelect( const short branchno, const long articleno, const int count = 500 );
    size_t                  IBTBranchesSelectGeneral( const short branchno, const long articleno, const int count = 500 );

    virtual  int            EndBrowse(const int cursorid);
    virtual  nCollectable*  AddToList(const void *record, const int row);
    virtual  int            GetNext(const void* record, const int cursorid);
    virtual  int            StartBrowse(const void *keys, const int cursorid);

    pxOrderEntryParamPtr m_OrderEntryParameter;

    friend class pxVartikelLokalListIter;
};

class pxVartikelLokalListIter : public nDListCollectIter
{
public:
    pxVartikelLokalListIter(pxVartikelLokalList& list) : nDListCollectIter(list) {}
    virtual  ~pxVartikelLokalListIter() {}
};

#endif /* PXVARTIKELLOKALLIST_HPP */

#ifndef GUARD_IBTTYPE_HPP
#define GUARD_IBTTYPE_HPP

/*----------------------------------------------------------------------------*/

#include "pxbase/pxrecord.hpp"

struct tIBTTYPE;

/*----------------------------------------------------------------------------*/

enum PURCHASE_RELEVANCE_MODE
{
	PRM_UNKNOWN 		= -1,
	PRM_ORIGINAL_BRANCH = 0,
	PRM_IBT_BRANCH		= 1,
	PRM_BOTH_BRANCHES	= 2 // ???
};

/*----------------------------------------------------------------------------*/

class pxIBTType : public pxDBRecord
{
public:
	pxIBTType(pxSession *session, tIBTTYPE& src);
	virtual  ~pxIBTType();

	pxIBTType&				operator=(const pxIBTType& src);
    pxIBTType&				operator=(const tIBTTYPE& src);

    friend pxIBTType&		Assign(pxIBTType& dest, const tIBTTYPE& src);
    friend tIBTTYPE&		Assign(tIBTTYPE& dest, const pxIBTType& src);

    virtual  int			CompareTo(const nCollectable* that, void*, const long) const;

	short					IBTTypeId();
	nString					Name();
	PURCHASE_RELEVANCE_MODE	PurchaseRelevanceMode();

protected:
	void					Init();

	short					IBTTypeId_;
	nString					Name_;
	PURCHASE_RELEVANCE_MODE	PurchaseRelevanceMode_;

private:
    friend class pxIBTTypeList;
};

/*----------------------------------------------------------------------------*/

class pxIBTTypeList : public nDBRecordSet, public nDListCollect
{
public:
	pxIBTTypeList(pxSession *session);
	virtual ~pxIBTTypeList();

	pxSession*				Session();
    void        			Clear();

	size_t					Select ();

    pxIBTType*				Find(short typeId);

    virtual  nCollectable*	AddToList(const void *record, const int row);
    virtual int 			GetNext(const void* record, const int cursorid);
    virtual int 			StartBrowse(const void *keys, const int cursorid);
    virtual int 			EndBrowse(const int cursorid);

protected:

private:
    friend class pxIBTTypeListIter;
};

/*----------------------------------------------------------------------------*/

class pxIBTTypeListIter : public nDListCollectIter
{
public:
	pxIBTTypeListIter(pxIBTTypeList& list) : nDListCollectIter(list) {}
	virtual  ~pxIBTTypeListIter() {}
};

/*----------------------------------------------------------------------------*/

#endif // GUARD_IBTTYPE_HPP

/*----------------------------------------------------------------------------*/

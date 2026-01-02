#ifndef IBTASSORTMENTTYPE_H
#define IBTASSORTMENTTYPE_H

#include "pxbase/pxrecord.hpp"
#include "pxrecord.h"

struct tIBTASSORTMENTTYPE;

// --------------------------------------------------------------------------------------------------- //
class IBTAssortmentType : public pxDBRecord
{	
	public:
		enum IBTCustomersOnly
		{
			eIBTCustomersOnly = 1
		};

		enum IBTPeriodNeeded
		{
			eIBTPeriodNeeded = 1
		};
	public:
												IBTAssortmentType( pxSession* session, short ibtassortmenttypeid);
												IBTAssortmentType(pxSession *session, tIBTASSORTMENTTYPE& src);
		virtual									~IBTAssortmentType();

		IBTAssortmentType&					    operator=( const IBTAssortmentType& src );
		IBTAssortmentType&					    operator=( const tIBTASSORTMENTTYPE& src );		
		
		bool 									Get();
		
		bool									isIBTCustomersOnly() const;
		bool									isIBTPeriodNeeded() const;

		short									getIBTCustomersOnly() const;
		short				 					getIBTPeriodNeeded() const;
		
	protected:
		void									Init();		

		short				 					getIBTAssortmentTypeID() const;

	private:		
		short									IBTAssortmentTypeID;

		tIBTASSORTMENTTYPE					    m_Values;

		virtual  int							Read( const void *record );		
		IBTAssortmentType&						Assign( IBTAssortmentType& dest, const tIBTASSORTMENTTYPE& src );
		tIBTASSORTMENTTYPE&						Assign( tIBTASSORTMENTTYPE& dest, const IBTAssortmentType& src);
	    virtual  int			                CompareTo(const nCollectable* that, void*, const long) const;

private:
    friend class IBTAssortmentTypeList;

};
/*----------------------------------------------------------------------------*/

class IBTAssortmentTypeList : public nDBRecordSet, public nDListCollect
{
public:
	IBTAssortmentTypeList(pxSession *session);
	virtual ~IBTAssortmentTypeList();

	pxSession*				Session();
    void        			Clear();

	size_t					Select ();

    IBTAssortmentType*		Find(short IBTAssortmentTypeID);

    virtual  nCollectable*	AddToList(const void *record, const int row);
    virtual int 			GetNext(const void* record, const int cursorid);
    virtual int 			StartBrowse(const void *keys, const int cursorid);
    virtual int 			EndBrowse(const int cursorid);

protected:

private:
    friend class IBTAssortmentTypeListIter;
};

/*----------------------------------------------------------------------------*/

class IBTAssortmentTypeListIter : public nDListCollectIter
{
public:
	IBTAssortmentTypeListIter(IBTAssortmentTypeList& list) : nDListCollectIter(list) {}
	virtual  ~IBTAssortmentTypeListIter() {}
};

#endif // IBTAssortmentType_H

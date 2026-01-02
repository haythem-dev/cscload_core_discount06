#ifndef PXCOMPUT_INC
#define PXCOMPUT_INC

#include "pxbase/pxrecord.hpp"

struct tRECHNER;

class pxComputer : public pxDBRecord
{

public:
// constructors:
				pxComputer(pxSession *session);
				pxComputer(pxComputer& src);
				pxComputer(pxSession *session, const tRECHNER& src);
				pxComputer(pxSession *session, short FilialNr,
						 DBAccessMode mode = cDBGET_READONLY);
// destructor:
				virtual  ~pxComputer();
/*@DS
PUBLIC MEMBER OPERATORS
*/
	pxComputer&   operator=(const pxComputer& src);
//  Assigns the values of 'src' to self and returns a reference to it.

	pxComputer&   operator=(const tRECHNER& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
	friend   pxComputer&
				Assign(pxComputer& dest, const tRECHNER& src);
	friend   tRECHNER&
				Assign(tRECHNER& dest, const pxComputer& src);

	virtual  int      CompareTo(const nCollectable *that, void *p,
								const long lparm) const;
	virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

	virtual  int     Read(const void *record);

//  Queries:
	short				FilialNr()			const { return FilialNr_;			}
	const nString&		ComputerName()		const { return RechnerName_;		}
	const nString&		Location()			const { return StandOrt_;			}
	char				Pflege()			const { return Pflege_;				}
	const nString&		DBName()			const { return DBName_;				}
	const nString&		DBNameWarehouse()   const { return DBNameWarehouse_;	}
	const nString&		DBNameInbound()     const { return DBNameInbound_;		}
	char				Zentral()			const { return S_Zentral_;			}
	bool				IsZentral()			const { return ('1' == S_Zentral_);	}

protected:
	void        Init();

	short		FilialNr_;					// Filialnummer
	nString     RechnerName_;				// Rechnername
	nString     StandOrt_;					// Standort
	char		Pflege_;					// update Kennzeichen
	nString     DBName_;					// connection name of remote DB
	char		S_Zentral_;					// must browse on artilellokal or artikel
	nString     DBNameWarehouse_;           // connection name of remote Warehouse DB
	nString     DBNameInbound_;             // connection name of remote Inbound DB

private:
	friend class pxComputerList;
};

class pxComputerList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
				pxComputerList(pxSession *session);
//  destructor:
				virtual ~pxComputerList() {Clear();}
//  member functions:
				pxSession* Session()       { return (pxSession*) DataBase();}

	size_t      Select ( const int count = 50 );
	int			Shrink();
	void        Clear()        {nDBRecordSet::Clear();}

	virtual  nCollectable*
					  AddToList(const void *record, const int row);
	virtual  int     GetNext(const void* record, const int cursorid);
	virtual  int     StartBrowse(const void *keys, const int cursorid);
	virtual  int     EndBrowse(const int cursorid);

	pxComputer*       Find( const short FilialNr);

protected:

private:
	friend class pxComputerListIter;
};

class pxComputerListIter : public nDListCollectIter
{

public:
// constructors:
	pxComputerListIter(pxComputerList& list) : nDListCollectIter(list) {;}
// destructor:
	virtual  ~pxComputerListIter() {;}
};
#endif

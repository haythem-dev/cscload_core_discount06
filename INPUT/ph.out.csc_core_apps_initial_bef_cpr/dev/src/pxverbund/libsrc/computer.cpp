#include "pxcomput.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxComputer::pxComputer(pxSession* session)
	: pxDBRecord(session)
{
	Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxComputer::pxComputer(pxComputer& src)
	: pxDBRecord(src.Session())
{
	Init();
	(*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tRECHNER structure to construct this instance.                        */
/*----------------------------------------------------------------------------*/
pxComputer::pxComputer(pxSession* session, const tRECHNER& src)
	: pxDBRecord(session)
{
	Init();
	(*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
// Read via this branchnumber
pxComputer::pxComputer(pxSession* session, short FilialNr, DBAccessMode mode)
	: pxDBRecord(session)
{
	Init();
	FilialNr_ = FilialNr;
	Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxComputer::~pxComputer()
{
	;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tRECHNER structure.            */
/*----------------------------------------------------------------------------*/
tRECHNER& Assign(tRECHNER& dest, const pxComputer& src)
{
	dest.FilialNr = src.FilialNr_;
	strcpy(dest.Rechner_Name, " ");
	src.RechnerName_.GetData(dest.Rechner_Name);
	strcpy(dest.Standort,  " ");
	src.StandOrt_.GetData(dest.Standort);
	dest.Pflege = src.Pflege_;

	dest.S_Zentral = src.S_Zentral_;

	strcpy(dest.DBName, " ");
	strcpy(dest.DBNameWarehouse, " ");
	strcpy(dest.DBNameInbound, " ");

	src.DBName_.GetData(dest.DBName);
	src.DBNameWarehouse_.GetData(dest.DBNameWarehouse);
	src.DBNameInbound_.GetData(dest.DBNameInbound);

	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tRECHNER structure to                      */
/*  a pxComputer object.                                                      */
/*----------------------------------------------------------------------------*/
pxComputer& Assign(pxComputer& dest, const tRECHNER& src)
{
	dest.FilialNr_			= src.FilialNr;
	dest.RechnerName_		= src.Rechner_Name;
	dest.StandOrt_			= src.Standort;
	dest.Pflege_			= src.Pflege;
	dest.S_Zentral_			= src.S_Zentral;
	dest.DBName_			= src.DBName;
	dest.DBNameWarehouse_	= src.DBNameWarehouse;
	dest.DBNameInbound_		= src.DBNameInbound;

	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void pxComputer::Init()
{
	tRECHNER record;
	memset(&record, 0 , sizeof(tRECHNER));
	Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tRECHNER struct and then imported to self.                                */
/*----------------------------------------------------------------------------*/
pxComputer& pxComputer::operator=( const pxComputer& src)
{
	tRECHNER record;               // used to export the data of 'src'
	Assign(*this, Assign(record, src));
	return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tRECHNER structure 'src' to                      */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxComputer& pxComputer::operator=( const tRECHNER& src)
{
	return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int pxComputer::Get( DBAccessMode mode )

{
	tRECHNER record;
	memset(&record, 0, sizeof(tRECHNER));
	record.FilialNr      = FilialNr_;
	int retval = ( mode == cDBGET_FORUPDATE ) ?
					nDBReadLock(&record) : nDBRead(&record);
	if (!retval)
	   (*this)= record;        // import the data from tRECHNER struct
	else if ( retval > cDBXR_NORMAL )
	   ExternalCondition(CMsgStream(),
						 CMSG_COMP_ENTRY_NOTFOUND, FilialNr_);
	return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int pxComputer::Read( const void  *record )
{
	return pxComputerRead((tRECHNER*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxComputer list objects being inserted in the                     */
/*  following ascending sequence:                                             */
/*  FilialNr                                                                  */
/*----------------------------------------------------------------------------*/
int pxComputer::CompareTo(const nCollectable* That, void* /* p */, const long /* lparm */)   const
{
	pxComputer *that = (pxComputer*)That;
	int retval = (FilialNr_ == that->FilialNr_) ? 0
				: (FilialNr_ > that->FilialNr_ ? 1 : -1);

	return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxComputerList::pxComputerList(pxSession* session)
	: nDBRecordSet(session)
{
	nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t pxComputerList::Select(const int count_)
{
	tRECHNER fil;
	memset(&fil, 0, sizeof(tRECHNER));  // zero out entire record buffer
	int cursorid = cCRS_NOWHERE;
	nDBSelect(&fil, cursorid, count_);
	return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable* pxComputerList::AddToList(
	const void  *record,
	const int  /* row */
)
{
	// construct new 'pxComputer' object:
	pxComputer *objectp = new pxComputer(Session(), *(tRECHNER*) record);
	InsertAscending(objectp);
	return objectp;
}

int
pxComputerList :: EndBrowse
(
	const int  cursorid
)
{
	return pxComputerEndBrowse(cursorid);
}


int
pxComputerList :: GetNext
(
	const void  *record,
	const int  cursorid
)
{
	return pxComputerGetNext((tRECHNER*)record, cursorid);
}

int
pxComputerList :: StartBrowse
(
	const void  *keys,
	const int  cursorid
)
{
	return pxComputerStartBrowse((tRECHNER*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/* Find returns a pxComputer pointer to the corresponding entry. If the       */
/* entry is not found within the list , so NULLP will be returned             */
/*----------------------------------------------------------------------------*/
pxComputer*
pxComputerList :: Find
(
	const short      FilialNr              // Search for this branchnumber
)
{
	pxComputerListIter   iter( *this );  // define iterator
	pxComputer          *entryp;         // pointer to listentry

	iter.Reset();                           // top of list
	while ( ( entryp = ( pxComputer*) ++iter) != NULL ) // browse list
	{
	   if ( entryp->FilialNr() == FilialNr )
		  break;
	}
	return   entryp;                        // return entrypointer
}


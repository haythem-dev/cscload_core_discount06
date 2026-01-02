#ifndef __PP_NATRASTAFFELN_H_
#define __PP_NATRASTAFFELN_H_

/******************************************************************************/
/* d:\prj\df\unix\tplddrnat\natrastaffeln *************************************/
/******************************************************************************/

/* Length-Define of NATRASTAFFELN *********************************************/

  #define L_NATRASTAFFELN_NATRASTAFFELNR 11
  #define L_NATRASTAFFELN_DATUMGUELTIGAB 11
  #define L_NATRASTAFFELN_DATUMGUELTIGBIS 11
  #define L_NATRASTAFFELN_NATRABASISMENGE 11
  #define L_NATRASTAFFELN_NATRAMENGE 11
  #define L_NATRASTAFFELN_KZUPD 1
  #define L_NATRASTAFFELN_KONDGRUPPENNR 11

/* Length/Count-Define of NATRASTAFFELN ***************************************/

  #define LS_NATRASTAFFELN_NATRASTAFFELNR 10 + 1
  #define LS_NATRASTAFFELN_DATUMGUELTIGAB 10 + 1
  #define LS_NATRASTAFFELN_DATUMGUELTIGBIS 10 + 1
  #define LS_NATRASTAFFELN_NATRABASISMENGE 10 + 1
  #define LS_NATRASTAFFELN_NATRAMENGE 10 + 1
  #define LS_NATRASTAFFELN_KZUPD 1 + 1
  #define LS_NATRASTAFFELN_KONDGRUPPENNR 10 + 1

  #define NATRASTAFFELNNATRASTAFFELNR 0
  #define NATRASTAFFELNDATUMGUELTIGAB 1
  #define NATRASTAFFELNDATUMGUELTIGBIS 2
  #define NATRASTAFFELNNATRABASISMENGE 3
  #define NATRASTAFFELNNATRAMENGE 4
  #define NATRASTAFFELNKZUPD 5
  #define NATRASTAFFELNKONDGRUPPENNR 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define NATRASTAFFELN_H
 #define NATRASTAFFELN_ANZ ( sizeof(NATRASTAFFELN_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of NATRASTAFFELN *************************************************/

 #define NATRASTAFFELN_LISTE \
         NATRASTAFFELN.NATRASTAFFELNR,\
         NATRASTAFFELN.DATUMGUELTIGAB,\
         NATRASTAFFELN.DATUMGUELTIGBIS,\
         NATRASTAFFELN.NATRABASISMENGE,\
         NATRASTAFFELN.NATRAMENGE,\
         NATRASTAFFELN.KZUPD,\
         NATRASTAFFELN.KONDGRUPPENNR

 #define NATRASTAFFELN_LISTE_390 \
         NATRASTAFFELNR,\
         DATUMGUELTIGAB,\
         DATUMGUELTIGBIS,\
         NATRABASISMENGE,\
         NATRAMENGE,\
         KZUPD,\
         KONDGRUPPENNR

 #define NATRASTAFFELN_PLISTE \
         "NATRASTAFFELN.NATRASTAFFELNR,"\
         "NATRASTAFFELN.DATUMGUELTIGAB,"\
         "NATRASTAFFELN.DATUMGUELTIGBIS,"\
         "NATRASTAFFELN.NATRABASISMENGE,"\
         "NATRASTAFFELN.NATRAMENGE,"\
         "NATRASTAFFELN.KZUPD,"\
         "NATRASTAFFELN.KONDGRUPPENNR"

 #define NATRASTAFFELN_PELISTE \
         "NATRASTAFFELNR,"\
         "DATUMGUELTIGAB,"\
         "DATUMGUELTIGBIS,"\
         "NATRABASISMENGE,"\
         "NATRAMENGE,"\
         "KZUPD,"\
         "KONDGRUPPENNR"

 #define NATRASTAFFELN_UPDLISTE \
         "NATRASTAFFELNR=?,"\
         "DATUMGUELTIGAB=?,"\
         "DATUMGUELTIGBIS=?,"\
         "NATRABASISMENGE=?,"\
         "NATRAMENGE=?,"\
         "KZUPD=?,"\
         "KONDGRUPPENNR=?"

/* SqlMacros-Define of NATRASTAFFELN ******************************************/

 #define NATRASTAFFELN_ZEIGER(x) \
         :x->NATRASTAFFELNR,\
         :x->DATUMGUELTIGAB,\
         :x->DATUMGUELTIGBIS,\
         :x->NATRABASISMENGE,\
         :x->NATRAMENGE,\
         :x->KZUPD,\
         :x->KONDGRUPPENNR

 #define NATRASTAFFELN_ZEIGERSEL(x) \
         :x->NATRASTAFFELNR,\
         :x->DATUMGUELTIGAB,\
         :x->DATUMGUELTIGBIS,\
         :x->NATRABASISMENGE,\
         :x->NATRAMENGE,\
         :x->KZUPD,\
         :x->KONDGRUPPENNR

 #define NATRASTAFFELN_UPDATE(x) \
         NATRASTAFFELN.NATRASTAFFELNR=:x->NATRASTAFFELNR,\
         NATRASTAFFELN.DATUMGUELTIGAB=:x->DATUMGUELTIGAB,\
         NATRASTAFFELN.DATUMGUELTIGBIS=:x->DATUMGUELTIGBIS,\
         NATRASTAFFELN.NATRABASISMENGE=:x->NATRABASISMENGE,\
         NATRASTAFFELN.NATRAMENGE=:x->NATRAMENGE,\
         NATRASTAFFELN.KZUPD=:x->KZUPD,\
         NATRASTAFFELN.KONDGRUPPENNR=:x->KONDGRUPPENNR

/* SqlMacros390-Define of NATRASTAFFELN ***************************************/

 #define NATRASTAFFELN_ZEIGER_390 \
         :NATRASTAFFELNR,\
         :DATUMGUELTIGAB,\
         :DATUMGUELTIGBIS,\
         :NATRABASISMENGE,\
         :NATRAMENGE,\
         :KZUPD,\
         :KONDGRUPPENNR

 #define NATRASTAFFELN_UPDATE_390 \
         NATRASTAFFELNR=:NATRASTAFFELNR,\
         DATUMGUELTIGAB=:DATUMGUELTIGAB,\
         DATUMGUELTIGBIS=:DATUMGUELTIGBIS,\
         NATRABASISMENGE=:NATRABASISMENGE,\
         NATRAMENGE=:NATRAMENGE,\
         KZUPD=:KZUPD,\
         KONDGRUPPENNR=:KONDGRUPPENNR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of NATRASTAFFELN ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_NATRASTAFFELN {
         long NATRASTAFFELNR;
         long DATUMGUELTIGAB;
         long DATUMGUELTIGBIS;
         long NATRABASISMENGE;
         long NATRAMENGE;
         char KZUPD[2];
         long KONDGRUPPENNR;
        } natrastaffelnS;
 #else /*TRANSCLASS*/
 typedef struct N_NATRASTAFFELN {
         long NATRASTAFFELNR;
         long DATUMGUELTIGAB;
         long DATUMGUELTIGBIS;
         long NATRABASISMENGE;
         long NATRAMENGE;
         char KZUPD[2];
         long KONDGRUPPENNR;

			bool operator==(const N_NATRASTAFFELN& right) const {
			return(
				NATRASTAFFELNR == right.NATRASTAFFELNR &&
				DATUMGUELTIGAB == right.DATUMGUELTIGAB &&
				DATUMGUELTIGBIS == right.DATUMGUELTIGBIS &&
				NATRABASISMENGE == right.NATRABASISMENGE &&
				NATRAMENGE == right.NATRAMENGE &&
				!strcmp(KZUPD, right.KZUPD) &&
				KONDGRUPPENNR == right.KONDGRUPPENNR
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				NATRASTAFFELNR = 0;
				DATUMGUELTIGAB = 0;
				DATUMGUELTIGBIS = 0;
				NATRABASISMENGE = 0;
				NATRAMENGE = 0;
				strcpy(KZUPD, " " );
				KONDGRUPPENNR = 0;
#endif
			}
         } natrastaffelnS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of NATRASTAFFELN *************************************/

 struct S_NATRASTAFFELN {
         char NATRASTAFFELNR[11];
         char DATUMGUELTIGAB[11];
         char DATUMGUELTIGBIS[11];
         char NATRABASISMENGE[11];
         char NATRAMENGE[11];
         char KZUPD[1 + 1];
         char KONDGRUPPENNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of NATRASTAFFELN ********************/

 struct O_NATRASTAFFELN {
         char NATRASTAFFELNR[11];
         char DATUMGUELTIGAB[11];
         char DATUMGUELTIGBIS[11];
         char NATRABASISMENGE[11];
         char NATRAMENGE[11];
         char KZUPD[1];
         char KONDGRUPPENNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of NATRASTAFFELN ********************************/

 struct C_NATRASTAFFELN {
         long NATRASTAFFELNR;
         long DATUMGUELTIGAB;
         long DATUMGUELTIGBIS;
         long NATRABASISMENGE;
         long NATRAMENGE;
         char KZUPD;
         long KONDGRUPPENNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of NATRASTAFFELN ******************************/

 struct I_NATRASTAFFELN {
         short NATRASTAFFELNR;
         short DATUMGUELTIGAB;
         short DATUMGUELTIGBIS;
         short NATRABASISMENGE;
         short NATRAMENGE;
         short KZUPD;
         short KONDGRUPPENNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of NATRASTAFFELN ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc NATRASTAFFELN_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc NATRASTAFFELN_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of NATRASTAFFELN *********************************/

 #define NATRASTAFFELN_S390 \
         long NATRASTAFFELNR; \
         long DATUMGUELTIGAB; \
         long DATUMGUELTIGBIS; \
         long NATRABASISMENGE; \
         long NATRAMENGE; \
         char KZUPD; \
         long KONDGRUPPENNR; \



/* Copy-Function Struct to single Data NATRASTAFFELN **************************/

 #define NATRASTAFFELN_S390_COPY_TO_SINGLE(_x_) \
         NATRASTAFFELNR=_x_->NATRASTAFFELNR;\
         DATUMGUELTIGAB=_x_->DATUMGUELTIGAB;\
         DATUMGUELTIGBIS=_x_->DATUMGUELTIGBIS;\
         NATRABASISMENGE=_x_->NATRABASISMENGE;\
         NATRAMENGE=_x_->NATRAMENGE;\
         KZUPD=_x_->KZUPD;\
         KONDGRUPPENNR=_x_->KONDGRUPPENNR;\

 #define NATRASTAFFELN_S390_COPY_TO_STRUCT(_x_) \
          _x_->NATRASTAFFELNR=NATRASTAFFELNR;\
          _x_->DATUMGUELTIGAB=DATUMGUELTIGAB;\
          _x_->DATUMGUELTIGBIS=DATUMGUELTIGBIS;\
          _x_->NATRABASISMENGE=NATRABASISMENGE;\
          _x_->NATRAMENGE=NATRAMENGE;\
          _x_->KZUPD=KZUPD;\
          _x_->KONDGRUPPENNR=KONDGRUPPENNR;\



/* FunctionNumber-Define of natrastaffeln *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of natrastaffeln *********************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS
#include<vector>
using namespace std;

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual
{
	public:
		virtual    ~ppDadeVirtual() {};
		virtual int SelList(int FetchRel = 1,int pos=0) = 0;
		virtual int SelListHist(int FetchRel = 1,int pos=0) = 0;
		virtual int SelListFuture(int FetchRel = 1,int pos=0) = 0;
		virtual int Load(int pos=0) = 0;
 		virtual int Delete(int pos=0) = 0;
		virtual int Save(int pos=0) = 0;
};
#endif

class CNATRASTAFFELN : public ppDadeVirtual
{
	//data members
	public:
		natrastaffelnS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<natrastaffelnS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<natrastaffelnS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<natrastaffelnS>; Strip(s); natrastaffelnS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<natrastaffelnS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<natrastaffelnS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<natrastaffelnS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetNatrastaffelnr() const	{ return s.NATRASTAFFELNR; }
		long		GetDatumgueltigab() const	{ return s.DATUMGUELTIGAB; }
		long		GetDatumgueltigbis() const	{ return s.DATUMGUELTIGBIS; }
		long		GetNatrabasismenge() const	{ return s.NATRABASISMENGE; }
		long		GetNatramenge() const	{ return s.NATRAMENGE; }
		char		GetKzupd() const	{ return s.KZUPD[0]; }
		long		GetKondgruppennr() const	{ return s.KONDGRUPPENNR; }
		const natrastaffelnS& GetStruct() const { return s; }
		void 		SetNatrastaffelnr(long t) { s.NATRASTAFFELNR = t; }
		void 		SetDatumgueltigab(long t) { s.DATUMGUELTIGAB = t; }
		void 		SetDatumgueltigbis(long t) { s.DATUMGUELTIGBIS = t; }
		void 		SetNatrabasismenge(long t) { s.NATRABASISMENGE = t; }
		void 		SetNatramenge(long t) { s.NATRAMENGE = t; }
		void 		SetKzupd(char t) { s.KZUPD[0] = t; s.KZUPD[1] = '\0';}
		void 		SetKondgruppennr(long t) { s.KONDGRUPPENNR = t; }
		void 		SetStruct(const natrastaffelnS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CNATRASTAFFELN()  //constructor
		{
			::buf_default((void *)&s,NATRASTAFFELN_BES,NATRASTAFFELN_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CNATRASTAFFELN()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, NATRASTAFFELN_BES, NATRASTAFFELN_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc=::ServerNr(pos, fkt_nr, (void *)&s,NATRASTAFFELN_BES,NATRASTAFFELN_ANZ, error_msg);
			#else
			rc=::Server(fkt_nr, (void *)&s,NATRASTAFFELN_BES,NATRASTAFFELN_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_NATRASTAFFELN& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,NATRASTAFFELN_BES,NATRASTAFFELN_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of NATRASTAFFELN ****************************************/

 #define NATRASTAFFELN_CREATE(x) exec sql create table x (\
         NATRASTAFFELNR integer default 0 not null,\
         DATUMGUELTIGAB integer default 0 not null,\
         DATUMGUELTIGBIS integer default 0 not null,\
         NATRABASISMENGE integer default 0 not null,\
         NATRAMENGE integer default 0 not null,\
         KZUPD char(1) default " " not null,\
         KONDGRUPPENNR integer default 0 not null) in phosix extent size 48 next size 8 lock mode row;



/* CreateIndexStatement of NATRASTAFFELN **************************************/

 #define NATRASTAFFELN_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_natrastaffel_1 on _X_(\
              natrastaffelnr ) in phosix1;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of NATRASTAFFELN **************************************/

 #define NATRASTAFFELN_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_natrastaffel_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

#ifndef __PP_TARTLAG_H_
#define __PP_TARTLAG_H_

/******************************************************************************/
/* u:\artikellagerort *********************************************************/
/******************************************************************************/

/* Length-Define of ARTIKELLAGERORT *******************************************/

  #define L_ARTIKELLAGERORT_FILIALNR 6
  #define L_ARTIKELLAGERORT_ARTIKEL_NR 11
  #define L_ARTIKELLAGERORT_LAGERBEREICHNR 6
  #define L_ARTIKELLAGERORT_STATIONNR 2
  #define L_ARTIKELLAGERORT_LAGERFACHNR 10
  #define L_ARTIKELLAGERORT_DATUMVERFALL 11
  #define L_ARTIKELLAGERORT_BESTAND 11
  #define L_ARTIKELLAGERORT_VERBUNDARTIKEL 1

/* Length/Count-Define of ARTIKELLAGERORT *************************************/

  #define LS_ARTIKELLAGERORT_FILIALNR 5 + 1
  #define LS_ARTIKELLAGERORT_ARTIKEL_NR 10 + 1
  #define LS_ARTIKELLAGERORT_LAGERBEREICHNR 5 + 1
  #define LS_ARTIKELLAGERORT_STATIONNR 2 + 1
  #define LS_ARTIKELLAGERORT_LAGERFACHNR 10 + 1
  #define LS_ARTIKELLAGERORT_DATUMVERFALL 10 + 1
  #define LS_ARTIKELLAGERORT_BESTAND 10 + 1
  #define LS_ARTIKELLAGERORT_VERBUNDARTIKEL 1 + 1

  #define ARTIKELLAGERORTFILIALNR 0
  #define ARTIKELLAGERORTARTIKEL_NR 1
  #define ARTIKELLAGERORTLAGERBEREICHNR 2
  #define ARTIKELLAGERORTSTATIONNR 3
  #define ARTIKELLAGERORTLAGERFACHNR 4
  #define ARTIKELLAGERORTDATUMVERFALL 5
  #define ARTIKELLAGERORTBESTAND 6
  #define ARTIKELLAGERORTVERBUNDARTIKEL 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTIKELLAGERORT_H
 #define ARTIKELLAGERORT_ANZ ( sizeof(ARTIKELLAGERORT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTIKELLAGERORT ***********************************************/

 #define ARTIKELLAGERORT_LISTE \
         ARTIKELLAGERORT.FILIALNR,\
         ARTIKELLAGERORT.ARTIKEL_NR,\
         ARTIKELLAGERORT.LAGERBEREICHNR,\
         ARTIKELLAGERORT.STATIONNR,\
         ARTIKELLAGERORT.LAGERFACHNR,\
         ARTIKELLAGERORT.DATUMVERFALL,\
         ARTIKELLAGERORT.BESTAND,\
         ARTIKELLAGERORT.VERBUNDARTIKEL

 #define ARTIKELLAGERORT_LISTE_390 \
         FILIALNR,\
         ARTIKEL_NR,\
         LAGERBEREICHNR,\
         STATIONNR,\
         LAGERFACHNR,\
         DATUMVERFALL,\
         BESTAND,\
         VERBUNDARTIKEL

 #define ARTIKELLAGERORT_PLISTE \
         "ARTIKELLAGERORT.FILIALNR,"\
         "ARTIKELLAGERORT.ARTIKEL_NR,"\
         "ARTIKELLAGERORT.LAGERBEREICHNR,"\
         "ARTIKELLAGERORT.STATIONNR,"\
         "ARTIKELLAGERORT.LAGERFACHNR,"\
         "ARTIKELLAGERORT.DATUMVERFALL,"\
         "ARTIKELLAGERORT.BESTAND,"\
         "ARTIKELLAGERORT.VERBUNDARTIKEL"

 #define ARTIKELLAGERORT_PELISTE \
         "FILIALNR,"\
         "ARTIKEL_NR,"\
         "LAGERBEREICHNR,"\
         "STATIONNR,"\
         "LAGERFACHNR,"\
         "DATUMVERFALL,"\
         "BESTAND,"\
         "VERBUNDARTIKEL"

 #define ARTIKELLAGERORT_UPDLISTE \
         "FILIALNR=?,"\
         "ARTIKEL_NR=?,"\
         "LAGERBEREICHNR=?,"\
         "STATIONNR=?,"\
         "LAGERFACHNR=?,"\
         "DATUMVERFALL=?,"\
         "BESTAND=?,"\
         "VERBUNDARTIKEL=?"

/* SqlMacros-Define of ARTIKELLAGERORT ****************************************/

 #define ARTIKELLAGERORT_ZEIGER(x) \
         :x->FILIALNR,\
         :x->ARTIKEL_NR,\
         :x->LAGERBEREICHNR,\
         :x->STATIONNR,\
         :x->LAGERFACHNR,\
         :x->DATUMVERFALL,\
         :x->BESTAND,\
         :x->VERBUNDARTIKEL

 #define ARTIKELLAGERORT_ZEIGERSEL(x) \
         :x->FILIALNR,\
         :x->ARTIKEL_NR,\
         :x->LAGERBEREICHNR,\
         :x->STATIONNR,\
         :x->LAGERFACHNR,\
         :x->DATUMVERFALL,\
         :x->BESTAND,\
         :x->VERBUNDARTIKEL

 #define ARTIKELLAGERORT_UPDATE(x) \
         ARTIKELLAGERORT.FILIALNR=:x->FILIALNR,\
         ARTIKELLAGERORT.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ARTIKELLAGERORT.LAGERBEREICHNR=:x->LAGERBEREICHNR,\
         ARTIKELLAGERORT.STATIONNR=:x->STATIONNR,\
         ARTIKELLAGERORT.LAGERFACHNR=:x->LAGERFACHNR,\
         ARTIKELLAGERORT.DATUMVERFALL=:x->DATUMVERFALL,\
         ARTIKELLAGERORT.BESTAND=:x->BESTAND,\
         ARTIKELLAGERORT.VERBUNDARTIKEL=:x->VERBUNDARTIKEL

/* SqlMacros390-Define of ARTIKELLAGERORT *************************************/

 #define ARTIKELLAGERORT_ZEIGER_390 \
         :FILIALNR,\
         :ARTIKEL_NR,\
         :LAGERBEREICHNR,\
         :STATIONNR,\
         :LAGERFACHNR,\
         :DATUMVERFALL,\
         :BESTAND,\
         :VERBUNDARTIKEL

 #define ARTIKELLAGERORT_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         ARTIKEL_NR=:ARTIKEL_NR,\
         LAGERBEREICHNR=:LAGERBEREICHNR,\
         STATIONNR=:STATIONNR,\
         LAGERFACHNR=:LAGERFACHNR,\
         DATUMVERFALL=:DATUMVERFALL,\
         BESTAND=:BESTAND,\
         VERBUNDARTIKEL=:VERBUNDARTIKEL

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTIKELLAGERORT ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTIKELLAGERORT {
         short FILIALNR;
         long ARTIKEL_NR;
         short LAGERBEREICHNR;
         char STATIONNR[3];
         char LAGERFACHNR[11];
         long DATUMVERFALL;
         long BESTAND;
         char VERBUNDARTIKEL[2];
        } artikellagerortS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTIKELLAGERORT {
         short FILIALNR;
         long ARTIKEL_NR;
         short LAGERBEREICHNR;
         char STATIONNR[3];
         char LAGERFACHNR[11];
         long DATUMVERFALL;
         long BESTAND;
         char VERBUNDARTIKEL[2];

			bool operator==(const N_ARTIKELLAGERORT& right) const {
			return(
				FILIALNR == right.FILIALNR &&
				ARTIKEL_NR == right.ARTIKEL_NR &&
				LAGERBEREICHNR == right.LAGERBEREICHNR &&
				!strcmp(STATIONNR, right.STATIONNR) &&
				!strcmp(LAGERFACHNR, right.LAGERFACHNR) &&
				DATUMVERFALL == right.DATUMVERFALL &&
				BESTAND == right.BESTAND &&
				!strcmp(VERBUNDARTIKEL, right.VERBUNDARTIKEL)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				FILIALNR = 0;
				ARTIKEL_NR = 0;
				LAGERBEREICHNR = 0;
				strcpy(STATIONNR, " " );
				strcpy(LAGERFACHNR, " " );
				DATUMVERFALL = 0;
				BESTAND = 0;
				strcpy(VERBUNDARTIKEL, " " );
#endif
			}
         } artikellagerortS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTIKELLAGERORT ***********************************/

 struct S_ARTIKELLAGERORT {
         char FILIALNR[7];
         char ARTIKEL_NR[11];
         char LAGERBEREICHNR[7];
         char STATIONNR[2 + 1];
         char LAGERFACHNR[10 + 1];
         char DATUMVERFALL[11];
         char BESTAND[11];
         char VERBUNDARTIKEL[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTIKELLAGERORT ******************/

 struct O_ARTIKELLAGERORT {
         char FILIALNR[7];
         char ARTIKEL_NR[11];
         char LAGERBEREICHNR[7];
         char STATIONNR[2];
         char LAGERFACHNR[10];
         char DATUMVERFALL[11];
         char BESTAND[11];
         char VERBUNDARTIKEL[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of ARTIKELLAGERORT ******************************/

 struct C_ARTIKELLAGERORT {
         short FILIALNR;
         long ARTIKEL_NR;
         short LAGERBEREICHNR;
         char STATIONNR[3];
         char LAGERFACHNR[11];
         long DATUMVERFALL;
         long BESTAND;
         char VERBUNDARTIKEL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of ARTIKELLAGERORT ****************************/

 struct I_ARTIKELLAGERORT {
         short FILIALNR;
         short ARTIKEL_NR;
         short LAGERBEREICHNR;
         short STATIONNR;
         short LAGERFACHNR;
         short DATUMVERFALL;
         short BESTAND;
         short VERBUNDARTIKEL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTIKELLAGERORT *************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTIKELLAGERORT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELLAGERORT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 10, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of ARTIKELLAGERORT *******************************/

 #define ARTIKELLAGERORT_S390 \
         short FILIALNR; \
         long ARTIKEL_NR; \
         short LAGERBEREICHNR; \
         char STATIONNR[3]; \
         char LAGERFACHNR[11]; \
         long DATUMVERFALL; \
         long BESTAND; \
         char VERBUNDARTIKEL; \



/* Copy-Function Struct to single Data ARTIKELLAGERORT ************************/

 #define ARTIKELLAGERORT_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         LAGERBEREICHNR=_x_->LAGERBEREICHNR;\
          strcpy(STATIONNR,_x_->STATIONNR);\
          strcpy(LAGERFACHNR,_x_->LAGERFACHNR);\
         DATUMVERFALL=_x_->DATUMVERFALL;\
         BESTAND=_x_->BESTAND;\
         VERBUNDARTIKEL=_x_->VERBUNDARTIKEL;\

 #define ARTIKELLAGERORT_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->LAGERBEREICHNR=LAGERBEREICHNR;\
          strcpy(_x_->STATIONNR,STATIONNR);\
          strcpy(_x_->LAGERFACHNR,LAGERFACHNR);\
          _x_->DATUMVERFALL=DATUMVERFALL;\
          _x_->BESTAND=BESTAND;\
          _x_->VERBUNDARTIKEL=VERBUNDARTIKEL;\



/* FunctionNumber-Define of artikellagerort ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of artikellagerort *******************************/


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
		virtual const int SelList(int FetchRel = 1,int pos=0) = 0;
		virtual const int SelListHist(int FetchRel = 1,int pos=0) = 0;
		virtual const int SelListFuture(int FetchRel = 1,int pos=0) = 0;
		virtual const int Load(int pos=0) = 0;
 		virtual const int Delete(int pos=0) = 0;
		virtual const int Save(int pos=0) = 0;
};
#endif

class CARTIKELLAGERORT : public ppDadeVirtual
{
	//data members
	public:
		artikellagerortS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<artikellagerortS> *pl; // pointer to class list

	//functions
	public:

		const int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		const bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		const bool 		SetList(const unsigned int i) {	if (GetSize() <= i)	return false; vector<artikellagerortS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		const bool 		InsList() { if ( !pl ) pl = new vector<artikellagerortS>; Strip(s); artikellagerortS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		const bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikellagerortS>::iterator itPtr = pl->begin() + i; if ( itPtr ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<artikellagerortS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<artikellagerortS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const short		GetFilialnr() const	{ return s.FILIALNR; }
		const long		GetArtikel_nr() const	{ return s.ARTIKEL_NR; }
		const short		GetLagerbereichnr() const	{ return s.LAGERBEREICHNR; }
		const char*	GetStationnr(ppString& t) const 	{ t = s.STATIONNR; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetLagerfachnr(ppString& t) const 	{ t = s.LAGERFACHNR; t.erasespace(ppString::END); return t.c_str(); }
		const long		GetDatumverfall() const	{ return s.DATUMVERFALL; }
		const long		GetBestand() const	{ return s.BESTAND; }
		const char		GetVerbundartikel() const	{ return s.VERBUNDARTIKEL[0]; }
		const artikellagerortS& GetStruct() const { return s; }
		void 		SetFilialnr(short t) { s.FILIALNR = t; }
		void 		SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
		void 		SetLagerbereichnr(short t) { s.LAGERBEREICHNR = t; }
		void 		SetStationnr(const ppString& t) { ppGStrCopy(s.STATIONNR,t.c_str() ,L_ARTIKELLAGERORT_STATIONNR); }
		void 		SetLagerfachnr(const ppString& t) { ppGStrCopy(s.LAGERFACHNR,t.c_str() ,L_ARTIKELLAGERORT_LAGERFACHNR); }
		void 		SetDatumverfall(long t) { s.DATUMVERFALL = t; }
		void 		SetBestand(long t) { s.BESTAND = t; }
		void 		SetVerbundartikel(char t) { s.VERBUNDARTIKEL[0] = t; s.VERBUNDARTIKEL[1] = '\0';}
		void 		SetStruct(const artikellagerortS& t) { s = t; }

	//virtual functions
	public:

		const int	Load(int pos=0) { return 1; }
		const int	Save(int pos=0) { return 1; }
		const int	Delete(int pos=0) { return 1; }
		const int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		const int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		const int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CARTIKELLAGERORT()  //constructor
		{
			::buf_default((void *)&s,ARTIKELLAGERORT_BES,ARTIKELLAGERORT_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		~CARTIKELLAGERORT()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ARTIKELLAGERORT_BES, ARTIKELLAGERORT_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_ARTIKELLAGERORT& d)
		{
#ifdef WIN32
			ppGStripLast(d.STATIONNR);
			ppGStripLast(d.LAGERFACHNR);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,ARTIKELLAGERORT_BES,ARTIKELLAGERORT_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of ARTIKELLAGERORT **************************************/

 #define ARTIKELLAGERORT_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         ARTIKEL_NR integer default 0 not null,\
         LAGERBEREICHNR smallint default 0 not null,\
         STATIONNR char(2) default " " not null,\
         LAGERFACHNR char(10) default " " not null,\
         DATUMVERFALL integer default 0 not null,\
         BESTAND integer default 0 not null,\
         VERBUNDARTIKEL char(1) default " " not null) in zp extent size 750395 lock mode row;



/* CreateIndexStatement of ARTIKELLAGERORT ************************************/

 #define ARTIKELLAGERORT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_artikellageror_2 on _X_(\
              filialnr,\
              artikel_nr ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_artikellageror_4 on _X_(\
              artikel_nr ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_artikellageror_5 on _X_(\
              filialnr,\
              lagerfachnr ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create unique index i_artikellagerort_ on _X_(\
              filialnr,\
              artikel_nr,\
              lagerbereichnr,\
              stationnr,\
              lagerfachnr ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTIKELLAGERORT ************************************/

 #define ARTIKELLAGERORT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_artikellageror_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_artikellageror_4;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_artikellageror_5;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_artikellagerort_;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

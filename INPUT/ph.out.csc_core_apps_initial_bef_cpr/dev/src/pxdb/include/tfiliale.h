#ifndef __PP_TFILIALE_H_
#define __PP_TFILIALE_H_

/******************************************************************************/
/* c:\phosix\tfiliale *********************************************************/
/******************************************************************************/

/* Length-Define of FILIALE ***************************************************/

  #define L_FILIALE_FILIALNR 6
  #define L_FILIALE_NAME 30
  #define L_FILIALE_STRASSE 30
  #define L_FILIALE_POSTLEITZAHL 7
  #define L_FILIALE_ORT 30
  #define L_FILIALE_VORWAHL 10
  #define L_FILIALE_TELNR 20
  #define L_FILIALE_FAXNR 20
  #define L_FILIALE_BGANR 11
  #define L_FILIALE_BGANR_EK 11

/* Length/Count-Define of FILIALE *********************************************/

  #define LS_FILIALE_FILIALNR 5 + 1
  #define LS_FILIALE_NAME 30 + 1
  #define LS_FILIALE_STRASSE 30 + 1
  #define LS_FILIALE_POSTLEITZAHL 7 + 1
  #define LS_FILIALE_ORT 30 + 1
  #define LS_FILIALE_VORWAHL 10 + 1
  #define LS_FILIALE_TELNR 20 + 1
  #define LS_FILIALE_FAXNR 20 + 1
  #define LS_FILIALE_BGANR 10 + 1
  #define LS_FILIALE_BGANR_EK 10 + 1

  #define FILIALEFILIALNR 0
  #define FILIALENAME 1
  #define FILIALESTRASSE 2
  #define FILIALEPOSTLEITZAHL 3
  #define FILIALEORT 4
  #define FILIALEVORWAHL 5
  #define FILIALETELNR 6
  #define FILIALEFAXNR 7
  #define FILIALEBGANR 8
  #define FILIALEBGANR_EK 9

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define FILIALE_H
 #define FILIALE_ANZ ( sizeof(FILIALE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of FILIALE *******************************************************/

 #define FILIALE_LISTE \
         FILIALE.FILIALNR,\
         FILIALE.NAME,\
         FILIALE.STRASSE,\
         FILIALE.POSTLEITZAHL,\
         FILIALE.ORT,\
         FILIALE.VORWAHL,\
         FILIALE.TELNR,\
         FILIALE.FAXNR,\
         FILIALE.BGANR,\
         FILIALE.BGANR_EK

 #define FILIALE_LISTE_390 \
         FILIALNR,\
         NAME,\
         STRASSE,\
         POSTLEITZAHL,\
         ORT,\
         VORWAHL,\
         TELNR,\
         FAXNR,\
         BGANR,\
         BGANR_EK

 #define FILIALE_PLISTE \
         "FILIALE.FILIALNR,"\
         "FILIALE.NAME,"\
         "FILIALE.STRASSE,"\
         "FILIALE.POSTLEITZAHL,"\
         "FILIALE.ORT,"\
         "FILIALE.VORWAHL,"\
         "FILIALE.TELNR,"\
         "FILIALE.FAXNR,"\
         "FILIALE.BGANR,"\
         "FILIALE.BGANR_EK"

 #define FILIALE_PELISTE \
         "FILIALNR,"\
         "NAME,"\
         "STRASSE,"\
         "POSTLEITZAHL,"\
         "ORT,"\
         "VORWAHL,"\
         "TELNR,"\
         "FAXNR,"\
         "BGANR,"\
         "BGANR_EK"

 #define FILIALE_UPDLISTE \
         "FILIALNR=?,"\
         "NAME=?,"\
         "STRASSE=?,"\
         "POSTLEITZAHL=?,"\
         "ORT=?,"\
         "VORWAHL=?,"\
         "TELNR=?,"\
         "FAXNR=?,"\
         "BGANR=?,"\
         "BGANR_EK=?"

/* SqlMacros-Define of FILIALE ************************************************/

 #define FILIALE_ZEIGER(x) \
         :x->FILIALNR,\
         :x->NAME,\
         :x->STRASSE,\
         :x->POSTLEITZAHL,\
         :x->ORT,\
         :x->VORWAHL,\
         :x->TELNR,\
         :x->FAXNR,\
         :x->BGANR,\
         :x->BGANR_EK

 #define FILIALE_UPDATE(x) \
         FILIALE.FILIALNR=:x->FILIALNR,\
         FILIALE.NAME=:x->NAME,\
         FILIALE.STRASSE=:x->STRASSE,\
         FILIALE.POSTLEITZAHL=:x->POSTLEITZAHL,\
         FILIALE.ORT=:x->ORT,\
         FILIALE.VORWAHL=:x->VORWAHL,\
         FILIALE.TELNR=:x->TELNR,\
         FILIALE.FAXNR=:x->FAXNR,\
         FILIALE.BGANR=:x->BGANR,\
         FILIALE.BGANR_EK=:x->BGANR_EK

/* SqlMacros390-Define of FILIALE *********************************************/

 #define FILIALE_ZEIGER_390 \
         :FILIALNR,\
         :NAME,\
         :STRASSE,\
         :POSTLEITZAHL,\
         :ORT,\
         :VORWAHL,\
         :TELNR,\
         :FAXNR,\
         :BGANR,\
         :BGANR_EK

 #define FILIALE_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         NAME=:NAME,\
         STRASSE=:STRASSE,\
         POSTLEITZAHL=:POSTLEITZAHL,\
         ORT=:ORT,\
         VORWAHL=:VORWAHL,\
         TELNR=:TELNR,\
         FAXNR=:FAXNR,\
         BGANR=:BGANR,\
         BGANR_EK=:BGANR_EK

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of FILIALE ************************************************/

 #ifndef TRANSCLASS
 typedef struct N_FILIALE {
         short FILIALNR;
         char NAME[31];
         char STRASSE[31];
         char POSTLEITZAHL[8];
         char ORT[31];
         char VORWAHL[11];
         char TELNR[21];
         char FAXNR[21];
         long BGANR;
         long BGANR_EK;
        } filialeS;
 #else /*TRANSCLASS*/
 typedef struct N_FILIALE {
         short FILIALNR;
         char NAME[31];
         char STRASSE[31];
         char POSTLEITZAHL[8];
         char ORT[31];
         char VORWAHL[11];
         char TELNR[21];
         char FAXNR[21];
         long BGANR;
         long BGANR_EK;

			bool operator==(const N_FILIALE& right) const {
			return(
				FILIALNR == right.FILIALNR &&
				!strcmp(NAME, right.NAME) &&
				!strcmp(STRASSE, right.STRASSE) &&
				!strcmp(POSTLEITZAHL, right.POSTLEITZAHL) &&
				!strcmp(ORT, right.ORT) &&
				!strcmp(VORWAHL, right.VORWAHL) &&
				!strcmp(TELNR, right.TELNR) &&
				!strcmp(FAXNR, right.FAXNR) &&
				BGANR == right.BGANR &&
				BGANR_EK == right.BGANR_EK
				);
			}
			void clear() { memset((char*)this,0,sizeof(*this)); }
         } filialeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of FILIALE *******************************************/

 struct S_FILIALE {
         char FILIALNR[7];
         char NAME[30 + 1];
         char STRASSE[30 + 1];
         char POSTLEITZAHL[7 + 1];
         char ORT[30 + 1];
         char VORWAHL[10 + 1];
         char TELNR[20 + 1];
         char FAXNR[20 + 1];
         char BGANR[11];
         char BGANR_EK[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of FILIALE **************************/

 struct O_FILIALE {
         char FILIALNR[7];
         char NAME[30];
         char STRASSE[30];
         char POSTLEITZAHL[7];
         char ORT[30];
         char VORWAHL[10];
         char TELNR[20];
         char FAXNR[20];
         char BGANR[11];
         char BGANR_EK[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of FILIALE **************************************/

 struct C_FILIALE {
         short FILIALNR;
         char NAME[31];
         char STRASSE[31];
         char POSTLEITZAHL[8];
         char ORT[31];
         char VORWAHL[11];
         char TELNR[21];
         char FAXNR[21];
         long BGANR;
         long BGANR_EK;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of FILIALE ************************************/

 struct I_FILIALE {
         short FILIALNR;
         short NAME;
         short STRASSE;
         short POSTLEITZAHL;
         short ORT;
         short VORWAHL;
         short TELNR;
         short FAXNR;
         short BGANR;
         short BGANR_EK;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of FILIALE *********************************************/

#if defined (BUF_DESC)
 static struct buf_desc FILIALE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc FILIALE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 7, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of FILIALE ***************************************/

 #define FILIALE_S390 \
         short FILIALNR; \
         char NAME[31]; \
         char STRASSE[31]; \
         char POSTLEITZAHL[8]; \
         char ORT[31]; \
         char VORWAHL[11]; \
         char TELNR[21]; \
         char FAXNR[21]; \
         long BGANR; \
         long BGANR_EK; \



/* Copy-Function Struct to single Data FILIALE ********************************/

 #define FILIALE_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
          strcpy(NAME,_x_->NAME);\
          strcpy(STRASSE,_x_->STRASSE);\
          strcpy(POSTLEITZAHL,_x_->POSTLEITZAHL);\
          strcpy(ORT,_x_->ORT);\
          strcpy(VORWAHL,_x_->VORWAHL);\
          strcpy(TELNR,_x_->TELNR);\
          strcpy(FAXNR,_x_->FAXNR);\
         BGANR=_x_->BGANR;\
         BGANR_EK=_x_->BGANR_EK;\

 #define FILIALE_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          strcpy(_x_->NAME,NAME);\
          strcpy(_x_->STRASSE,STRASSE);\
          strcpy(_x_->POSTLEITZAHL,POSTLEITZAHL);\
          strcpy(_x_->ORT,ORT);\
          strcpy(_x_->VORWAHL,VORWAHL);\
          strcpy(_x_->TELNR,TELNR);\
          strcpy(_x_->FAXNR,FAXNR);\
          _x_->BGANR=BGANR;\
          _x_->BGANR_EK=BGANR_EK;\



/* FunctionNumber-Define of filiale *******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of filiale ***************************************/


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
		virtual int SelList(int FetchRel = 1,int pos=0)	{ return 1; }
		virtual int SelListHist(int FetchRel = 1,int pos=0)	{ return 1; }
		virtual int SelListFuture(int FetchRel = 1,int pos=0)	{ return 1; }
};
#endif

class CFILIALE : public ppDadeVirtual
{
	//data members
	public:
		filialeS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<filialeS> *pl; // pointer to class list

	//functions
	public:

		const int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) {	if (GetSize() <= i)	return false; vector<filialeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<filialeS>; Strip(s); filialeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<filialeS>::iterator itPtr = pl->begin() + i; if ( itPtr ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<filialeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<filialeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const short&		GetFilialnr() const	{ return s.FILIALNR; }
		const char*	GetName(ppString& t) const 	{ t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetStrasse(ppString& t) const 	{ t = s.STRASSE; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetPostleitzahl(ppString& t) const 	{ t = s.POSTLEITZAHL; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetOrt(ppString& t) const 	{ t = s.ORT; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetVorwahl(ppString& t) const 	{ t = s.VORWAHL; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetTelnr(ppString& t) const 	{ t = s.TELNR; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetFaxnr(ppString& t) const 	{ t = s.FAXNR; t.erasespace(ppString::END); return t.c_str(); }
		const long&		GetBganr() const	{ return s.BGANR; }
		const long&		GetBganr_ek() const	{ return s.BGANR_EK; }
		const filialeS& GetStruct() const { return s; }
		void 		SetFilialnr(short t) { s.FILIALNR = t; }
		void 		SetName(const ppString& t) { ppGStrCopy(s.NAME,t.c_str() ,L_FILIALE_NAME); }
		void 		SetStrasse(const ppString& t) { ppGStrCopy(s.STRASSE,t.c_str() ,L_FILIALE_STRASSE); }
		void 		SetPostleitzahl(const ppString& t) { ppGStrCopy(s.POSTLEITZAHL,t.c_str() ,L_FILIALE_POSTLEITZAHL); }
		void 		SetOrt(const ppString& t) { ppGStrCopy(s.ORT,t.c_str() ,L_FILIALE_ORT); }
		void 		SetVorwahl(const ppString& t) { ppGStrCopy(s.VORWAHL,t.c_str() ,L_FILIALE_VORWAHL); }
		void 		SetTelnr(const ppString& t) { ppGStrCopy(s.TELNR,t.c_str() ,L_FILIALE_TELNR); }
		void 		SetFaxnr(const ppString& t) { ppGStrCopy(s.FAXNR,t.c_str() ,L_FILIALE_FAXNR); }
		void 		SetBganr(long t) { s.BGANR = t; }
		void 		SetBganr_ek(long t) { s.BGANR_EK = t; }
		void 		SetStruct(const filialeS& t) { s = t; }

		CFILIALE()  //constructor
		{
			::buf_default((void *)&s,FILIALE_BES,FILIALE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		~CFILIALE()  //destructor
		{
			if(pl) delete pl;
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, FILIALE_BES, FILIALE_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_FILIALE& d)
		{
			ppGStripLast(d.NAME);
			ppGStripLast(d.STRASSE);
			ppGStripLast(d.POSTLEITZAHL);
			ppGStripLast(d.ORT);
			ppGStripLast(d.VORWAHL);
			ppGStripLast(d.TELNR);
			ppGStripLast(d.FAXNR);
		}

		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,FILIALE_BES,FILIALE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of FILIALE **********************************************/

 #define FILIALE_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         NAME char(30) default " " not null,\
         STRASSE char(30) default " " not null,\
         POSTLEITZAHL char(7) default " " not null,\
         ORT char(30) default " " not null,\
         VORWAHL char(10) default " " not null,\
         TELNR char(20) default " " not null,\
         FAXNR char(20) default " " not null,\
         BGANR integer default 0 not null,\
         BGANR_EK integer default 0 not null) in zp extent size 8 lock mode row;



/* CreateIndexStatement of FILIALE ********************************************/

 #define FILIALE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_filiale_1 on _X_(\
              filialnr ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of FILIALE ********************************************/

 #define FILIALE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_filiale_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\


#endif

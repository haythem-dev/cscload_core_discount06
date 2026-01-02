#ifndef __PP_ZARTSEKBEZ_H_
#define __PP_ZARTSEKBEZ_H_

/******************************************************************************/
/* d:\prj\df\unix\tpldzentral\zartsekbez **************************************/
/******************************************************************************/

/* Length-Define of ZARTSEKBEZ ************************************************/

  #define L_ZARTSEKBEZ_ARTIKEL_MC 12
  #define L_ZARTSEKBEZ_ARTIKEL_NR 11
  #define L_ZARTSEKBEZ_ARTIKEL_NAME 30
  #define L_ZARTSEKBEZ_BEMERKUNGEN 240

/* Length/Count-Define of ZARTSEKBEZ ******************************************/

  #define LS_ZARTSEKBEZ_ARTIKEL_MC 12 + 1
  #define LS_ZARTSEKBEZ_ARTIKEL_NR 10 + 1
  #define LS_ZARTSEKBEZ_ARTIKEL_NAME 30 + 1
  #define LS_ZARTSEKBEZ_BEMERKUNGEN 240 + 1

  #define ZARTSEKBEZARTIKEL_MC 0
  #define ZARTSEKBEZARTIKEL_NR 1
  #define ZARTSEKBEZARTIKEL_NAME 2
  #define ZARTSEKBEZBEMERKUNGEN 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ZARTSEKBEZ_H
 #define ZARTSEKBEZ_ANZ ( sizeof(ZARTSEKBEZ_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ZARTSEKBEZ ****************************************************/

 #define ZARTSEKBEZ_LISTE \
         ZARTSEKBEZ.ARTIKEL_MC,\
         ZARTSEKBEZ.ARTIKEL_NR,\
         ZARTSEKBEZ.ARTIKEL_NAME,\
         ZARTSEKBEZ.BEMERKUNGEN

 #define ZARTSEKBEZ_LISTE_390 \
         ARTIKEL_MC,\
         ARTIKEL_NR,\
         ARTIKEL_NAME,\
         BEMERKUNGEN

 #define ZARTSEKBEZ_PLISTE \
         "ZARTSEKBEZ.ARTIKEL_MC,"\
         "ZARTSEKBEZ.ARTIKEL_NR,"\
         "ZARTSEKBEZ.ARTIKEL_NAME,"\
         "ZARTSEKBEZ.BEMERKUNGEN"

 #define ZARTSEKBEZ_PELISTE \
         "ARTIKEL_MC,"\
         "ARTIKEL_NR,"\
         "ARTIKEL_NAME,"\
         "BEMERKUNGEN"

 #define ZARTSEKBEZ_UPDLISTE \
         "ARTIKEL_MC=?,"\
         "ARTIKEL_NR=?,"\
         "ARTIKEL_NAME=?,"\
         "BEMERKUNGEN=?"

/* SqlMacros-Define of ZARTSEKBEZ *********************************************/

 #define ZARTSEKBEZ_ZEIGER(x) \
         :x->ARTIKEL_MC,\
         :x->ARTIKEL_NR,\
         :x->ARTIKEL_NAME,\
         :x->BEMERKUNGEN

 #define ZARTSEKBEZ_ZEIGERSEL(x) \
         :x->ARTIKEL_MC,\
         :x->ARTIKEL_NR,\
         :x->ARTIKEL_NAME,\
         :x->BEMERKUNGEN

 #define ZARTSEKBEZ_UPDATE(x) \
         ZARTSEKBEZ.ARTIKEL_MC=:x->ARTIKEL_MC,\
         ZARTSEKBEZ.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ZARTSEKBEZ.ARTIKEL_NAME=:x->ARTIKEL_NAME,\
         ZARTSEKBEZ.BEMERKUNGEN=:x->BEMERKUNGEN

/* SqlMacros390-Define of ZARTSEKBEZ ******************************************/

 #define ZARTSEKBEZ_ZEIGER_390 \
         :ARTIKEL_MC,\
         :ARTIKEL_NR,\
         :ARTIKEL_NAME,\
         :BEMERKUNGEN

 #define ZARTSEKBEZ_UPDATE_390 \
         ARTIKEL_MC=:ARTIKEL_MC,\
         ARTIKEL_NR=:ARTIKEL_NR,\
         ARTIKEL_NAME=:ARTIKEL_NAME,\
         BEMERKUNGEN=:BEMERKUNGEN

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ZARTSEKBEZ *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ZARTSEKBEZ {
         char ARTIKEL_MC[13];
         long ARTIKEL_NR;
         char ARTIKEL_NAME[31];
         char BEMERKUNGEN[241];
        } zartsekbezS;
 #else /*TRANSCLASS*/
 typedef struct N_ZARTSEKBEZ {
         char ARTIKEL_MC[13];
         long ARTIKEL_NR;
         char ARTIKEL_NAME[31];
         char BEMERKUNGEN[241];

			bool operator==(const N_ZARTSEKBEZ& right) const {
			return(
				!strcmp(ARTIKEL_MC, right.ARTIKEL_MC) &&
				ARTIKEL_NR == right.ARTIKEL_NR &&
				!strcmp(ARTIKEL_NAME, right.ARTIKEL_NAME) &&
				!strcmp(BEMERKUNGEN, right.BEMERKUNGEN)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				strcpy(ARTIKEL_MC, " " );
				ARTIKEL_NR = 0;
				strcpy(ARTIKEL_NAME, " " );
				strcpy(BEMERKUNGEN, " " );
#endif
			}
         } zartsekbezS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ZARTSEKBEZ ****************************************/

 struct S_ZARTSEKBEZ {
         char ARTIKEL_MC[12 + 1];
         char ARTIKEL_NR[11];
         char ARTIKEL_NAME[30 + 1];
         char BEMERKUNGEN[240 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ZARTSEKBEZ ***********************/

 struct O_ZARTSEKBEZ {
         char ARTIKEL_MC[12];
         char ARTIKEL_NR[11];
         char ARTIKEL_NAME[30];
         char BEMERKUNGEN[240];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of ZARTSEKBEZ ***********************************/

 struct C_ZARTSEKBEZ {
         char ARTIKEL_MC[13];
         long ARTIKEL_NR;
         char ARTIKEL_NAME[31];
         char BEMERKUNGEN[241];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of ZARTSEKBEZ *********************************/

 struct I_ZARTSEKBEZ {
         short ARTIKEL_MC;
         short ARTIKEL_NR;
         short ARTIKEL_NAME;
         short BEMERKUNGEN;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ZARTSEKBEZ ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc ZARTSEKBEZ_BES [] =
 {
   { TYP_C, 12, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 240, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ZARTSEKBEZ_BES [] =
 {
   { TYP_C, 12, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 240, 0 },
 };
#endif

/* description for datatypes of ZARTSEKBEZ ************************************/

 #define ZARTSEKBEZ_S390 \
         char ARTIKEL_MC[13]; \
         long ARTIKEL_NR; \
         char ARTIKEL_NAME[31]; \
         char BEMERKUNGEN[241]; \



/* Copy-Function Struct to single Data ZARTSEKBEZ *****************************/

 #define ZARTSEKBEZ_S390_COPY_TO_SINGLE(_x_) \
          strcpy(ARTIKEL_MC,_x_->ARTIKEL_MC);\
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
          strcpy(ARTIKEL_NAME,_x_->ARTIKEL_NAME);\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\

 #define ZARTSEKBEZ_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->ARTIKEL_MC,ARTIKEL_MC);\
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          strcpy(_x_->ARTIKEL_NAME,ARTIKEL_NAME);\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\



/* FunctionNumber-Define of zartsekbez ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of zartsekbez ************************************/


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

class CZARTSEKBEZ : public ppDadeVirtual
{
	//data members
	public:
		zartsekbezS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<zartsekbezS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<zartsekbezS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<zartsekbezS>; Strip(s); zartsekbezS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<zartsekbezS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<zartsekbezS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<zartsekbezS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const char*	GetArtikel_mc(ppString& t) const 	{ t = s.ARTIKEL_MC; t.erasespace(ppString::END); return t.c_str(); }
		long		GetArtikel_nr() const	{ return s.ARTIKEL_NR; }
		const char*	GetArtikel_name(ppString& t) const 	{ t = s.ARTIKEL_NAME; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetBemerkungen(ppString& t) const 	{ t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
		const zartsekbezS& GetStruct() const { return s; }
		void 		SetArtikel_mc(const ppString& t) { ppGStrCopy(s.ARTIKEL_MC,t.c_str() ,L_ZARTSEKBEZ_ARTIKEL_MC); }
		void 		SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
		void 		SetArtikel_name(const ppString& t) { ppGStrCopy(s.ARTIKEL_NAME,t.c_str() ,L_ZARTSEKBEZ_ARTIKEL_NAME); }
		void 		SetBemerkungen(const ppString& t) { ppGStrCopy(s.BEMERKUNGEN,t.c_str() ,L_ZARTSEKBEZ_BEMERKUNGEN); }
		void 		SetStruct(const zartsekbezS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CZARTSEKBEZ()  //constructor
		{
			::buf_default((void *)&s,ZARTSEKBEZ_BES,ZARTSEKBEZ_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CZARTSEKBEZ()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ZARTSEKBEZ_BES, ZARTSEKBEZ_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_ZARTSEKBEZ& d)
		{
#ifdef WIN32
			ppGStripLast(d.ARTIKEL_MC);
			ppGStripLast(d.ARTIKEL_NAME);
			ppGStripLast(d.BEMERKUNGEN);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,ZARTSEKBEZ_BES,ZARTSEKBEZ_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of ZARTSEKBEZ *******************************************/

 #define ZARTSEKBEZ_CREATE(x) exec sql create table x (\
         ARTIKEL_MC char(12) default " " not null,\
         ARTIKEL_NR integer default 0 not null,\
         ARTIKEL_NAME char(30) default " " not null,\
         BEMERKUNGEN varchar(240,0) default " " not null) in phosix extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of ZARTSEKBEZ *****************************************/

 #define ZARTSEKBEZ_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_zartsekbez_1 on _X_(\
              artikel_nr,\
              artikel_name ) in phosix1;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ZARTSEKBEZ *****************************************/

 #define ZARTSEKBEZ_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_zartsekbez_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

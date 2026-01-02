#ifndef __PP_ZARTICLECATEGORY_H_
#define __PP_ZARTICLECATEGORY_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\setarticlecategory\zarticlecategory *************************/
/******************************************************************************/

/* Length-Define of ZARTICLECATEGORY ******************************************/

  #define L_ZARTICLECATEGORY_ARTCATEGORYNO 11
  #define L_ZARTICLECATEGORY_NAME 30
  #define L_ZARTICLECATEGORY_SQL_STATEMENT 255

/* Length/Count-Define of ZARTICLECATEGORY ************************************/

  #define LS_ZARTICLECATEGORY_ARTCATEGORYNO 10 + 1
  #define LS_ZARTICLECATEGORY_NAME 30 + 1
  #define LS_ZARTICLECATEGORY_SQL_STATEMENT 255 + 1

  #define ZARTICLECATEGORYARTCATEGORYNO 0
  #define ZARTICLECATEGORYNAME 1
  #define ZARTICLECATEGORYSQL_STATEMENT 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ZARTICLECATEGORY_H
 #define ZARTICLECATEGORY_ANZ ( sizeof(ZARTICLECATEGORY_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ZARTICLECATEGORY **********************************************/

 #define ZARTICLECATEGORY_LISTE \
         CARTICLECATEGORY.ARTCATEGORYNO,\
         CARTICLECATEGORY.NAME,\
         CARTICLECATEGORY.SQL_STATEMENT

 #define ZARTICLECATEGORY_LISTE_390 \
         ARTCATEGORYNO,\
         NAME,\
         SQL_STATEMENT

 #define ZARTICLECATEGORY_PLISTE \
         "CARTICLECATEGORY.ARTCATEGORYNO,"\
         "CARTICLECATEGORY.NAME,"\
         "CARTICLECATEGORY.SQL_STATEMENT"

 #define ZARTICLECATEGORY_PELISTE \
         "ARTCATEGORYNO,"\
         "NAME,"\
         "SQL_STATEMENT"

 #define ZARTICLECATEGORY_UPDLISTE \
         "ARTCATEGORYNO=?,"\
         "NAME=?,"\
         "SQL_STATEMENT=?"

/* SqlMacros-Define of ZARTICLECATEGORY ***************************************/

 #define ZARTICLECATEGORY_ZEIGER(x) \
         :x->ARTCATEGORYNO,\
         :x->NAME,\
         :x->SQL_STATEMENT

 #define ZARTICLECATEGORY_ZEIGERSEL(x) \
         :x->ARTCATEGORYNO,\
         :x->NAME,\
         :x->SQL_STATEMENT

 #define ZARTICLECATEGORY_UPDATE(x) \
         CARTICLECATEGORY.ARTCATEGORYNO=:x->ARTCATEGORYNO,\
         CARTICLECATEGORY.NAME=:x->NAME,\
         CARTICLECATEGORY.SQL_STATEMENT=:x->SQL_STATEMENT

/* SqlMacros390-Define of ZARTICLECATEGORY ************************************/

 #define ZARTICLECATEGORY_ZEIGER_390 \
         :ARTCATEGORYNO,\
         :NAME,\
         :SQL_STATEMENT

 #define ZARTICLECATEGORY_UPDATE_390 \
         ARTCATEGORYNO=:ARTCATEGORYNO,\
         NAME=:NAME,\
         SQL_STATEMENT=:SQL_STATEMENT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ZARTICLECATEGORY ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_ZARTICLECATEGORY {
         long ARTCATEGORYNO;
         char NAME[31];
         char SQL_STATEMENT[256];
        } zarticlecategoryS;
 #else /*TRANSCLASS*/
 typedef struct N_ZARTICLECATEGORY {
         long ARTCATEGORYNO;
         char NAME[31];
         char SQL_STATEMENT[256];

			bool operator==(const N_ZARTICLECATEGORY& right) const {
			return(
				ARTCATEGORYNO == right.ARTCATEGORYNO &&
				!strcmp(NAME, right.NAME) &&
				!strcmp(SQL_STATEMENT, right.SQL_STATEMENT)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				ARTCATEGORYNO = 0;
				strcpy(NAME, " " );
				strcpy(SQL_STATEMENT, " " );
#endif
			}
         } zarticlecategoryS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ZARTICLECATEGORY **********************************/

 struct S_ZARTICLECATEGORY {
         char ARTCATEGORYNO[11];
         char NAME[30 + 1];
         char SQL_STATEMENT[255 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ZARTICLECATEGORY *****************/

 struct O_ZARTICLECATEGORY {
         char ARTCATEGORYNO[11];
         char NAME[30];
         char SQL_STATEMENT[255];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ZARTICLECATEGORY ****************************/

 struct C_ZARTICLECATEGORY {
         long ARTCATEGORYNO;
         char NAME[31];
         char SQL_STATEMENT[256];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ZARTICLECATEGORY **************************/

 struct I_ZARTICLECATEGORY {
         short ARTCATEGORYNO;
         short NAME;
         short SQL_STATEMENT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ZARTICLECATEGORY ************************************/

#if defined (BUF_DESC)
 static struct buf_desc ZARTICLECATEGORY_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 255, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ZARTICLECATEGORY_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 255, 0 },
 };
#endif

/* description for datatypes of ZARTICLECATEGORY ******************************/

 #define ZARTICLECATEGORY_S390 \
         long ARTCATEGORYNO; \
         char NAME[31]; \
         char SQL_STATEMENT[256]; \



/* Copy-Function Struct to single Data ZARTICLECATEGORY ***********************/

 #define ZARTICLECATEGORY_S390_COPY_TO_SINGLE(_x_) \
         ARTCATEGORYNO=_x_->ARTCATEGORYNO;\
          strcpy(NAME,_x_->NAME);\
          strcpy(SQL_STATEMENT,_x_->SQL_STATEMENT);\

 #define ZARTICLECATEGORY_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTCATEGORYNO=ARTCATEGORYNO;\
          strcpy(_x_->NAME,NAME);\
          strcpy(_x_->SQL_STATEMENT,SQL_STATEMENT);\



/* FunctionNumber-Define of zarticlecategory **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of zarticlecategory ******************************/


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
		virtual int SelList      (int FetchRel = 1, int pos = 0) = 0;
		virtual int SelListHist  (int FetchRel = 1, int pos = 0) = 0;
		virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
		virtual int Load         (int pos = 0                  ) = 0;
 		virtual int Delete       (int pos = 0                  ) = 0;
		virtual int Save         (int pos = 0                  ) = 0;
};
#endif

class CZARTICLECATEGORY : public ppDadeVirtual
{
	//data members
	public:
		zarticlecategoryS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<zarticlecategoryS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<zarticlecategoryS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<zarticlecategoryS>; Strip(s); zarticlecategoryS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<zarticlecategoryS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<zarticlecategoryS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<zarticlecategoryS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetArtcategoryno() const	{ return s.ARTCATEGORYNO; }
		const char*	GetName(ppString& t) const 	{ t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetSql_statement(ppString& t) const 	{ t = s.SQL_STATEMENT; t.erasespace(ppString::END); return t.c_str(); }
		const zarticlecategoryS& GetStruct() const { return s; }
		void 		SetArtcategoryno(long t) { s.ARTCATEGORYNO = t; }
		void 		SetName(const ppString& t) { ppGStrCopy(s.NAME,t.c_str() ,L_ZARTICLECATEGORY_NAME); }
		void 		SetSql_statement(const ppString& t) { ppGStrCopy(s.SQL_STATEMENT,t.c_str() ,L_ZARTICLECATEGORY_SQL_STATEMENT); }
		void 		SetStruct(const zarticlecategoryS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CZARTICLECATEGORY()  //constructor
		{
			::buf_default((void *)&s, ZARTICLECATEGORY_BES, ZARTICLECATEGORY_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CZARTICLECATEGORY()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ZARTICLECATEGORY_BES, ZARTICLECATEGORY_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, ZARTICLECATEGORY_BES, ZARTICLECATEGORY_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, ZARTICLECATEGORY_BES, ZARTICLECATEGORY_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_ZARTICLECATEGORY& d)
		{
#ifdef WIN32
			ppGStripLast(d.NAME);
			ppGStripLast(d.SQL_STATEMENT);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, ZARTICLECATEGORY_BES, ZARTICLECATEGORY_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of ZARTICLECATEGORY *************************************/

 #define ZARTICLECATEGORY_CREATE(x) exec sql create table x (\
         ARTCATEGORYNO integer default 0 not null,\
         NAME char(30) default " " not null,\
         SQL_STATEMENT char(255) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ZARTICLECATEGORY ***********************************/

 #define ZARTICLECATEGORY_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_carticlecategory on _X_(\
              artcategoryno );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ZARTICLECATEGORY ***********************************/

 #define ZARTICLECATEGORY_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_carticlecategory;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

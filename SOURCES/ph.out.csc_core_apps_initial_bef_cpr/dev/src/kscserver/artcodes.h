#ifndef __PP_ARTCODES_H_
#define __PP_ARTCODES_H_

/******************************************************************************/
/* d:\prj\AA\UNIX\kscserver\server\artcodes ***********************************/
/******************************************************************************/

/* Length-Define of ARTCODES **************************************************/

  #define L_ARTCODES_ARTICLENO 11
  #define L_ARTCODES_CODE_TYPE 6
  #define L_ARTCODES_ARTICLE_CODE 25

/* Length/Count-Define of ARTCODES ********************************************/

  #define LS_ARTCODES_ARTICLENO 10 + 1
  #define LS_ARTCODES_CODE_TYPE 5 + 1
  #define LS_ARTCODES_ARTICLE_CODE 25 + 1

  #define ARTCODESARTICLENO 0
  #define ARTCODESCODE_TYPE 1
  #define ARTCODESARTICLE_CODE 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTCODES_H
 #define ARTCODES_ANZ ( sizeof(ARTCODES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTCODES ******************************************************/

 #define ARTCODES_LISTE \
         ARTICLECODES.ARTICLENO,\
         ARTICLECODES.CODE_TYPE,\
         ARTICLECODES.ARTICLE_CODE

 #define ARTCODES_LISTE_390 \
         ARTICLENO,\
         CODE_TYPE,\
         ARTICLE_CODE

 #define ARTCODES_PLISTE \
         "ARTICLECODES.ARTICLENO,"\
         "ARTICLECODES.CODE_TYPE,"\
         "ARTICLECODES.ARTICLE_CODE"

 #define ARTCODES_PELISTE \
         "ARTICLENO,"\
         "CODE_TYPE,"\
         "ARTICLE_CODE"

 #define ARTCODES_UPDLISTE \
         "ARTICLENO=?,"\
         "CODE_TYPE=?,"\
         "ARTICLE_CODE=?"

/* SqlMacros-Define of ARTCODES ***********************************************/

 #define ARTCODES_ZEIGER(x) \
         :x->ARTICLENO,\
         :x->CODE_TYPE,\
         :x->ARTICLE_CODE

 #define ARTCODES_ZEIGERSEL(x) \
         :x->ARTICLENO,\
         :x->CODE_TYPE,\
         :x->ARTICLE_CODE

 #define ARTCODES_UPDATE(x) \
         ARTICLECODES.ARTICLENO=:x->ARTICLENO,\
         ARTICLECODES.CODE_TYPE=:x->CODE_TYPE,\
         ARTICLECODES.ARTICLE_CODE=:x->ARTICLE_CODE

/* SqlMacros390-Define of ARTCODES ********************************************/

 #define ARTCODES_ZEIGER_390 \
         :ARTICLENO,\
         :CODE_TYPE,\
         :ARTICLE_CODE

 #define ARTCODES_UPDATE_390 \
         ARTICLENO=:ARTICLENO,\
         CODE_TYPE=:CODE_TYPE,\
         ARTICLE_CODE=:ARTICLE_CODE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTCODES ***********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTCODES {
         long ARTICLENO;
         short CODE_TYPE;
         char ARTICLE_CODE[26];
        } artcodesS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTCODES {
         long ARTICLENO;
         short CODE_TYPE;
         char ARTICLE_CODE[26];

			bool operator==(const N_ARTCODES& right) const {
			return(
				ARTICLENO == right.ARTICLENO &&
				CODE_TYPE == right.CODE_TYPE &&
				!strcmp(ARTICLE_CODE, right.ARTICLE_CODE)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				ARTICLENO = 0;
				CODE_TYPE = 0;
				strcpy(ARTICLE_CODE, " " );
#endif
			}
         } artcodesS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTCODES ******************************************/

 struct S_ARTCODES {
         char ARTICLENO[11];
         char CODE_TYPE[7];
         char ARTICLE_CODE[25 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTCODES *************************/

 struct O_ARTCODES {
         char ARTICLENO[11];
         char CODE_TYPE[7];
         char ARTICLE_CODE[25];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTCODES ************************************/

 struct C_ARTCODES {
         long ARTICLENO;
         short CODE_TYPE;
         char ARTICLE_CODE[26];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTCODES **********************************/

 struct I_ARTCODES {
         short ARTICLENO;
         short CODE_TYPE;
         short ARTICLE_CODE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTCODES ********************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTCODES_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 25, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTCODES_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 25, 0 },
 };
#endif

/* description for datatypes of ARTCODES **************************************/

 #define ARTCODES_S390 \
         long ARTICLENO; \
         short CODE_TYPE; \
         char ARTICLE_CODE[26]; \



/* Copy-Function Struct to single Data ARTCODES *******************************/

 #define ARTCODES_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         CODE_TYPE=_x_->CODE_TYPE;\
          strcpy(ARTICLE_CODE,_x_->ARTICLE_CODE);\

 #define ARTCODES_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->CODE_TYPE=CODE_TYPE;\
          strcpy(_x_->ARTICLE_CODE,ARTICLE_CODE);\



/* FunctionNumber-Define of artcodes ******************************************/

  #define ARTCODES_SELARTBYCODE 1

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of artcodes **************************************/

  #define SelArtByCode 1

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

class CARTCODES : public ppDadeVirtual
{
	//data members
	public:
		artcodesS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<artcodesS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artcodesS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<artcodesS>; Strip(s); artcodesS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artcodesS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<artcodesS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<artcodesS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetArticleno() const	{ return s.ARTICLENO; }
		short		GetCode_type() const	{ return s.CODE_TYPE; }
		const char*	GetArticle_code(ppString& t) const 	{ t = s.ARTICLE_CODE; t.erasespace(ppString::END); return t.c_str(); }
		const artcodesS& GetStruct() const { return s; }
		void 		SetArticleno(long t) { s.ARTICLENO = t; }
		void 		SetCode_type(short t) { s.CODE_TYPE = t; }
		void 		SetArticle_code(const ppString& t) { ppGStrCopy(s.ARTICLE_CODE,t.c_str() ,L_ARTCODES_ARTICLE_CODE); }
		void 		SetStruct(const artcodesS& t) { s = t; }
		int 		SelArtByCode(int pos=0)	{ int rc = UniqueServerCall(1,pos); Strip(s); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CARTCODES()  //constructor
		{
			::buf_default((void *)&s, ARTCODES_BES, ARTCODES_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CARTCODES()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ARTCODES_BES, ARTCODES_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1 ) 	return UniqueServerCall(1,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_ARTCODES& d)
		{
#ifdef WIN32
			ppGStripLast(d.ARTICLE_CODE);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, ARTCODES_BES, ARTCODES_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of ARTCODES *********************************************/

 #define ARTCODES_CREATE(x) exec sql create table x (\
         ARTICLENO integer default 0 not null,\
         CODE_TYPE smallint default 0 not null,\
         ARTICLE_CODE char(25) default " " not null) extent size 7844 next size 788 lock mode row;



/* CreateIndexStatement of ARTCODES *******************************************/

 #define ARTCODES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_artcodes_1 on _X_(\
              article_code );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_artcodes_2 on _X_(\
              ArticleNo,\
              preferred_flag );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTCODES *******************************************/

 #define ARTCODES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_artcodes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_artcodes_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

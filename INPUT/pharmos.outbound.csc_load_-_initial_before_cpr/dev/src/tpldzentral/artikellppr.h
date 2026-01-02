#ifndef __PP_ARTIKELLPPR_H_
#define __PP_ARTIKELLPPR_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\tpldzentral\ArtikelLPPR *************************************/
/******************************************************************************/

/* Length-Define of ARTIKELLPPR ***********************************************/

  #define L_ARTIKELLPPR_ARTICLENO 11
  #define L_ARTIKELLPPR_REIMBURSEMENT_TYPE 1
  #define L_ARTIKELLPPR_REIMBURSEMENTPRICE 9
  #define N_ARTIKELLPPR_REIMBURSEMENTPRICE 3
  #define L_ARTIKELLPPR_CODE_LPPR 15
  #define L_ARTIKELLPPR_REIMBURSEMENT_PERC 5
  #define N_ARTIKELLPPR_REIMBURSEMENT_PERC 2

/* Length/Count-Define of ARTIKELLPPR *****************************************/

  #define LS_ARTIKELLPPR_ARTICLENO 10 + 1
  #define LS_ARTIKELLPPR_REIMBURSEMENT_TYPE 1 + 1
  #define LS_ARTIKELLPPR_REIMBURSEMENTPRICE 9 + 2
  #define LS_ARTIKELLPPR_CODE_LPPR 15 + 1
  #define LS_ARTIKELLPPR_REIMBURSEMENT_PERC 5 + 2

  #define ARTIKELLPPRARTICLENO 0
  #define ARTIKELLPPRREIMBURSEMENT_TYPE 1
  #define ARTIKELLPPRREIMBURSEMENTPRICE 2
  #define ARTIKELLPPRCODE_LPPR 3
  #define ARTIKELLPPRREIMBURSEMENT_PERC 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTIKELLPPR_H
 #define ARTIKELLPPR_ANZ ( sizeof(ARTIKELLPPR_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTIKELLPPR ***************************************************/

 #define ARTIKELLPPR_LISTE \
         ARTICLELPPR.ARTICLENO,\
         ARTICLELPPR.REIMBURSEMENT_TYPE,\
         ARTICLELPPR.REIMBURSEMENTPRICE,\
         ARTICLELPPR.CODE_LPPR,\
         ARTICLELPPR.REIMBURSEMENT_PERC

 #define ARTIKELLPPR_LISTE_390 \
         ARTICLENO,\
         REIMBURSEMENT_TYPE,\
         REIMBURSEMENTPRICE,\
         CODE_LPPR,\
         REIMBURSEMENT_PERC

 #define ARTIKELLPPR_PLISTE \
         "ARTICLELPPR.ARTICLENO,"\
         "ARTICLELPPR.REIMBURSEMENT_TYPE,"\
         "ARTICLELPPR.REIMBURSEMENTPRICE,"\
         "ARTICLELPPR.CODE_LPPR,"\
         "ARTICLELPPR.REIMBURSEMENT_PERC"

 #define ARTIKELLPPR_PELISTE \
         "ARTICLENO,"\
         "REIMBURSEMENT_TYPE,"\
         "REIMBURSEMENTPRICE,"\
         "CODE_LPPR,"\
         "REIMBURSEMENT_PERC"

 #define ARTIKELLPPR_UPDLISTE \
         "ARTICLENO=?,"\
         "REIMBURSEMENT_TYPE=?,"\
         "REIMBURSEMENTPRICE=?,"\
         "CODE_LPPR=?,"\
         "REIMBURSEMENT_PERC=?"

/* SqlMacros-Define of ARTIKELLPPR ********************************************/

 #define ARTIKELLPPR_ZEIGER(x) \
         :x->ARTICLENO,\
         :x->REIMBURSEMENT_TYPE,\
         :x->REIMBURSEMENTPRICE,\
         :x->CODE_LPPR,\
         :x->REIMBURSEMENT_PERC

 #define ARTIKELLPPR_ZEIGERSEL(x) \
         :x->ARTICLENO,\
         :x->REIMBURSEMENT_TYPE,\
         :x->REIMBURSEMENTPRICE,\
         :x->CODE_LPPR,\
         :x->REIMBURSEMENT_PERC

 #define ARTIKELLPPR_UPDATE(x) \
         ARTICLELPPR.ARTICLENO=:x->ARTICLENO,\
         ARTICLELPPR.REIMBURSEMENT_TYPE=:x->REIMBURSEMENT_TYPE,\
         ARTICLELPPR.REIMBURSEMENTPRICE=:x->REIMBURSEMENTPRICE,\
         ARTICLELPPR.CODE_LPPR=:x->CODE_LPPR,\
         ARTICLELPPR.REIMBURSEMENT_PERC=:x->REIMBURSEMENT_PERC

/* SqlMacros390-Define of ARTIKELLPPR *****************************************/

 #define ARTIKELLPPR_ZEIGER_390 \
         :ARTICLENO,\
         :REIMBURSEMENT_TYPE,\
         :REIMBURSEMENTPRICE,\
         :CODE_LPPR,\
         :REIMBURSEMENT_PERC

 #define ARTIKELLPPR_UPDATE_390 \
         ARTICLENO=:ARTICLENO,\
         REIMBURSEMENT_TYPE=:REIMBURSEMENT_TYPE,\
         REIMBURSEMENTPRICE=:REIMBURSEMENTPRICE,\
         CODE_LPPR=:CODE_LPPR,\
         REIMBURSEMENT_PERC=:REIMBURSEMENT_PERC

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTIKELLPPR ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTIKELLPPR {
         long ARTICLENO;
         char REIMBURSEMENT_TYPE[2];
         double REIMBURSEMENTPRICE;
         char CODE_LPPR[16];
         double REIMBURSEMENT_PERC;
         long FETCH_REL;
        } artikellpprS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTIKELLPPR {
         long ARTICLENO;
         char REIMBURSEMENT_TYPE[2];
         double REIMBURSEMENTPRICE;
         char CODE_LPPR[16];
         double REIMBURSEMENT_PERC;
         long FETCH_REL;
			bool operator==(const N_ARTIKELLPPR& right) const {
			return(
				ARTICLENO == right.ARTICLENO &&
				!strcmp(REIMBURSEMENT_TYPE, right.REIMBURSEMENT_TYPE) &&
				REIMBURSEMENTPRICE == right.REIMBURSEMENTPRICE &&
				!strcmp(CODE_LPPR, right.CODE_LPPR) &&
				REIMBURSEMENT_PERC == right.REIMBURSEMENT_PERC
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				ARTICLENO = 0;
				strcpy(REIMBURSEMENT_TYPE, " " );
				REIMBURSEMENTPRICE = 0;
				strcpy(CODE_LPPR, " " );
				REIMBURSEMENT_PERC = 0;
#endif
			}
         } artikellpprS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTIKELLPPR ***************************************/

 struct S_ARTIKELLPPR {
         char ARTICLENO[11];
         char REIMBURSEMENT_TYPE[1 + 1];
         char REIMBURSEMENTPRICE[9 + 2];
         char CODE_LPPR[15 + 1];
         char REIMBURSEMENT_PERC[5 + 2];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTIKELLPPR **********************/

 struct O_ARTIKELLPPR {
         char ARTICLENO[11];
         char REIMBURSEMENT_TYPE[1];
         char REIMBURSEMENTPRICE[9];
         char CODE_LPPR[15];
         char REIMBURSEMENT_PERC[5];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTIKELLPPR *********************************/

 struct C_ARTIKELLPPR {
         long ARTICLENO;
         char REIMBURSEMENT_TYPE;
         double REIMBURSEMENTPRICE;
         char CODE_LPPR[16];
         double REIMBURSEMENT_PERC;
         long FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTIKELLPPR *******************************/

 struct I_ARTIKELLPPR {
         short ARTICLENO;
         short REIMBURSEMENT_TYPE;
         short REIMBURSEMENTPRICE;
         short CODE_LPPR;
         short REIMBURSEMENT_PERC;
         short FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTIKELLPPR *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTIKELLPPR_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 9, 3 },
   { TYP_C, 15, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELLPPR_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 9, 3 },
   { TYP_C, 15, 0 },
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of ARTIKELLPPR ***********************************/

 #define ARTIKELLPPR_S390 \
         long ARTICLENO; \
         char REIMBURSEMENT_TYPE; \
         double REIMBURSEMENTPRICE; \
         char CODE_LPPR[16]; \
         double REIMBURSEMENT_PERC; \
         long FETCH_REL;



/* Copy-Function Struct to single Data ARTIKELLPPR ****************************/

 #define ARTIKELLPPR_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         REIMBURSEMENT_TYPE=_x_->REIMBURSEMENT_TYPE;\
         REIMBURSEMENTPRICE=_x_->REIMBURSEMENTPRICE;\
          strcpy(CODE_LPPR,_x_->CODE_LPPR);\
         REIMBURSEMENT_PERC=_x_->REIMBURSEMENT_PERC;\
          FETCH_REL=_x_->FETCH_REL;\

 #define ARTIKELLPPR_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->REIMBURSEMENT_TYPE=REIMBURSEMENT_TYPE;\
          _x_->REIMBURSEMENTPRICE=REIMBURSEMENTPRICE;\
          strcpy(_x_->CODE_LPPR,CODE_LPPR);\
          _x_->REIMBURSEMENT_PERC=REIMBURSEMENT_PERC;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of ArtikelLPPR ***************************************/

  #define ARTIKELLPPR_SELLIST 1439

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArtikelLPPR ***********************************/

  #define SelList 1439

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

class CARTIKELLPPR : public ppDadeVirtual
{
	//data members
	public:
		artikellpprS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<artikellpprS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikellpprS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<artikellpprS>; Strip(s); artikellpprS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikellpprS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<artikellpprS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<artikellpprS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetArticleno() const	{ return s.ARTICLENO; }
		char		GetReimbursement_type() const	{ return s.REIMBURSEMENT_TYPE[0]; }
		double		GetReimbursementprice() const	{ return s.REIMBURSEMENTPRICE; }
		const char*	GetCode_lppr(ppString& t) const 	{ t = s.CODE_LPPR; t.erasespace(ppString::END); return t.c_str(); }
		double		GetReimbursement_perc() const	{ return s.REIMBURSEMENT_PERC; }
		const artikellpprS& GetStruct() const { return s; }
		long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetArticleno(long t) { s.ARTICLENO = t; }
		void 		SetReimbursement_type(char t) { s.REIMBURSEMENT_TYPE[0] = t; s.REIMBURSEMENT_TYPE[1] = '\0';}
		void 		SetReimbursementprice(double t) { s.REIMBURSEMENTPRICE = t; }
		void 		SetCode_lppr(const ppString& t) { ppGStrCopy(s.CODE_LPPR,t.c_str() ,L_ARTIKELLPPR_CODE_LPPR); }
		void 		SetReimbursement_perc(double t) { s.REIMBURSEMENT_PERC = t; }
		void 		SetStruct(const artikellpprS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }
		int 		SelList(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1439,FetchRel,pos); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CARTIKELLPPR()  //constructor
		{
			::buf_default((void *)&s, ARTIKELLPPR_BES, ARTIKELLPPR_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CARTIKELLPPR()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ARTIKELLPPR_BES, ARTIKELLPPR_ANZ);
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s,ARTIKELLPPR_BES,ARTIKELLPPR_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			bOpenCursor  = false;
			bEndOfSelect = false;
			FncNumber    = 0;
			CursorPos    = 0;
			AnzPos       = 0;
			if(pl)
			{
				delete pl;
				pl = NULL;
			}
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1439 ) 	return CursorServerCall(1439,s.FETCH_REL,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_ARTIKELLPPR& d)
		{
#ifdef WIN32
			ppGStripLast(d.CODE_LPPR);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, ARTIKELLPPR_BES, ARTIKELLPPR_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int CursorServerCall(int FncNr,int FetchRel = 1, int pos=0)
		{
			if		( FetchRel == 0 ) return CloseCursor(pos);
			else if	( FetchRel == 1 ) return GetNext(pos,FncNr);
			else if	( FetchRel <  0 ) return ChangeCursor(FetchRel);
			else 
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
		}

		int GetNext(int pos, int FncNr)
		{
			CARTIKELLPPR c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber   = FncNr;
				AnzPos      = 0;
				if ( pl ) delete pl;
				pl = new vector<artikellpprS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s, ARTIKELLPPR_BES, ARTIKELLPPR_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			if (rc == 0)
			{
				Strip(s);
				c.s = s;
				pl->insert(pl->end(),c.s);
				bEndOfSelect = false;
				CursorPos++;
				AnzPos++;
			}
			else if (rc == 1) bEndOfSelect = true;
			else if (rc < 0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int ChangeCursor(int FetchRel) // FetchRel is a negative value
		{
			CursorPos = CursorPos + FetchRel < 0 ? 0 : CursorPos + FetchRel - 1;
			if ( CursorPos >= AnzPos )
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
			s = pl->at(CursorPos);
			CursorPos++;
			rc = 0;
			return 0;
		}

};

#endif

/* CreateSqlStatement of ARTIKELLPPR ******************************************/

 #define ARTIKELLPPR_CREATE(x) exec sql create table x (\
         ARTICLENO integer default 0 not null,\
         REIMBURSEMENT_TYPE char(1) default " " not null,\
         REIMBURSEMENTPRICE decimal(9,3) default 0 not null,\
         CODE_LPPR char(15) default " " not null,\
         REIMBURSEMENT_PERC decimal(5,2) default 0 not null) extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of ARTIKELLPPR ****************************************/

 #define ARTIKELLPPR_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_articlelppr_1 on _X_(\
              ArticleNo,\
              reimbursement_type );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTIKELLPPR ****************************************/

 #define ARTIKELLPPR_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_articlelppr_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

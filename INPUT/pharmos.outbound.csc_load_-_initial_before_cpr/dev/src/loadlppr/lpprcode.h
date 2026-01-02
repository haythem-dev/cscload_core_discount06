#ifndef __PP_LPPRCODE_H_
#define __PP_LPPRCODE_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadlppr\LpprCode *******************************************/
/******************************************************************************/

/* Length-Define of LPPRCODE **************************************************/

  #define L_LPPRCODE_CODE_LPPR 15
  #define L_LPPRCODE_REIMBURSEMENT_VAL 9
  #define N_LPPRCODE_REIMBURSEMENT_VAL 2

/* Length/Count-Define of LPPRCODE ********************************************/

  #define LS_LPPRCODE_CODE_LPPR 15 + 1
  #define LS_LPPRCODE_REIMBURSEMENT_VAL 9 + 2

  #define LPPRCODECODE_LPPR 0
  #define LPPRCODEREIMBURSEMENT_VAL 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define LPPRCODE_H
 #define LPPRCODE_ANZ ( sizeof(LPPRCODE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of LPPRCODE ******************************************************/

 #define LPPRCODE_LISTE \
         LPPRCODE.CODE_LPPR,\
         LPPRCODE.REIMBURSEMENT_VAL

 #define LPPRCODE_LISTE_390 \
         CODE_LPPR,\
         REIMBURSEMENT_VAL

 #define LPPRCODE_PLISTE \
         "LPPRCODE.CODE_LPPR,"\
         "LPPRCODE.REIMBURSEMENT_VAL"

 #define LPPRCODE_PELISTE \
         "CODE_LPPR,"\
         "REIMBURSEMENT_VAL"

 #define LPPRCODE_UPDLISTE \
         "CODE_LPPR=?,"\
         "REIMBURSEMENT_VAL=?"

/* SqlMacros-Define of LPPRCODE ***********************************************/

 #define LPPRCODE_ZEIGER(x) \
         :x->CODE_LPPR,\
         :x->REIMBURSEMENT_VAL

 #define LPPRCODE_ZEIGERSEL(x) \
         :x->CODE_LPPR,\
         :x->REIMBURSEMENT_VAL

 #define LPPRCODE_UPDATE(x) \
         LPPRCODE.CODE_LPPR=:x->CODE_LPPR,\
         LPPRCODE.REIMBURSEMENT_VAL=:x->REIMBURSEMENT_VAL

/* SqlMacros390-Define of LPPRCODE ********************************************/

 #define LPPRCODE_ZEIGER_390 \
         :CODE_LPPR,\
         :REIMBURSEMENT_VAL

 #define LPPRCODE_UPDATE_390 \
         CODE_LPPR=:CODE_LPPR,\
         REIMBURSEMENT_VAL=:REIMBURSEMENT_VAL

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of LPPRCODE ***********************************************/

 #ifndef TRANSCLASS
 typedef struct N_LPPRCODE {
         char CODE_LPPR[16];
         double REIMBURSEMENT_VAL;
        } lpprcodeS;
 #else /*TRANSCLASS*/
 typedef struct N_LPPRCODE {
         char CODE_LPPR[16];
         double REIMBURSEMENT_VAL;

			bool operator==(const N_LPPRCODE& right) const {
			return(
				!strcmp(CODE_LPPR, right.CODE_LPPR) &&
				REIMBURSEMENT_VAL == right.REIMBURSEMENT_VAL
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				strcpy(CODE_LPPR, " " );
				REIMBURSEMENT_VAL = 0;
#endif
			}
         } lpprcodeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of LPPRCODE ******************************************/

 struct S_LPPRCODE {
         char CODE_LPPR[15 + 1];
         char REIMBURSEMENT_VAL[9 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of LPPRCODE *************************/

 struct O_LPPRCODE {
         char CODE_LPPR[15];
         char REIMBURSEMENT_VAL[9];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of LPPRCODE ************************************/

 struct C_LPPRCODE {
         char CODE_LPPR[16];
         double REIMBURSEMENT_VAL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of LPPRCODE **********************************/

 struct I_LPPRCODE {
         short CODE_LPPR;
         short REIMBURSEMENT_VAL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of LPPRCODE ********************************************/

#if defined (BUF_DESC)
 static struct buf_desc LPPRCODE_BES [] =
 {
   { TYP_C, 15, 0 },
   { TYP_D, 9, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc LPPRCODE_BES [] =
 {
   { TYP_C, 15, 0 },
   { TYP_D, 9, 2 },
 };
#endif

/* description for datatypes of LPPRCODE **************************************/

 #define LPPRCODE_S390 \
         char CODE_LPPR[16]; \
         double REIMBURSEMENT_VAL; \



/* Copy-Function Struct to single Data LPPRCODE *******************************/

 #define LPPRCODE_S390_COPY_TO_SINGLE(_x_) \
          strcpy(CODE_LPPR,_x_->CODE_LPPR);\
         REIMBURSEMENT_VAL=_x_->REIMBURSEMENT_VAL;\

 #define LPPRCODE_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->CODE_LPPR,CODE_LPPR);\
          _x_->REIMBURSEMENT_VAL=REIMBURSEMENT_VAL;\



/* FunctionNumber-Define of LpprCode ******************************************/

  #define LPPRCODE_SEL 1444

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of LpprCode **************************************/

  #define Sel 1444

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

class CLPPRCODE : public ppDadeVirtual
{
	//data members
	public:
		lpprcodeS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<lpprcodeS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<lpprcodeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<lpprcodeS>; Strip(s); lpprcodeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<lpprcodeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<lpprcodeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<lpprcodeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const char*	GetCode_lppr(ppString& t) const 	{ t = s.CODE_LPPR; t.erasespace(ppString::END); return t.c_str(); }
		double		GetReimbursement_val() const	{ return s.REIMBURSEMENT_VAL; }
		const lpprcodeS& GetStruct() const { return s; }
		void 		SetCode_lppr(const ppString& t) { ppGStrCopy(s.CODE_LPPR,t.c_str() ,L_LPPRCODE_CODE_LPPR); }
		void 		SetReimbursement_val(double t) { s.REIMBURSEMENT_VAL = t; }
		void 		SetStruct(const lpprcodeS& t) { s = t; }
		int 		Sel(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1444,FetchRel,pos); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CLPPRCODE()  //constructor
		{
			::buf_default((void *)&s, LPPRCODE_BES, LPPRCODE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CLPPRCODE()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, LPPRCODE_BES, LPPRCODE_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			if( fkt_nr == 1444 ) 	return CursorServerCall(1444,s.FETCH_REL,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_LPPRCODE& d)
		{
#ifdef WIN32
			ppGStripLast(d.CODE_LPPR);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, LPPRCODE_BES, LPPRCODE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of LPPRCODE *********************************************/

 #define LPPRCODE_CREATE(x) exec sql create table x (\
         CODE_LPPR char(15) default " " not null,\
         REIMBURSEMENT_VAL decimal(9,2) default 0 not null) in ksc extent size 16 next size 8 lock mode row;



/* CreateIndexStatement of LPPRCODE *******************************************/

 #define LPPRCODE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_lpprcode_1 on _X_(\
              code_lppr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of LPPRCODE *******************************************/

 #define LPPRCODE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_lpprcode_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

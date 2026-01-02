#ifndef __PP_PAYTERM_H_
#define __PP_PAYTERM_H_

/******************************************************************************/
/* d:\prj\aa\UNIX\AAPSERV\PayTerm *********************************************/
/******************************************************************************/

/* Length-Define of PAYTERM ***************************************************/

  #define L_PAYTERM_PAYMENT_TERM 4
  #define L_PAYTERM_PAYMENTARGET 6
  #define L_PAYTERM_CASHDISOUNT 5
  #define N_PAYTERM_CASHDISOUNT 2
  #define L_PAYTERM_UPD_FLAG 1

/* Length/Count-Define of PAYTERM *********************************************/

  #define LS_PAYTERM_PAYMENT_TERM 4 + 1
  #define LS_PAYTERM_PAYMENTARGET 5 + 1
  #define LS_PAYTERM_CASHDISOUNT 5 + 2
  #define LS_PAYTERM_UPD_FLAG 1 + 1

  #define PAYTERMPAYMENT_TERM 0
  #define PAYTERMPAYMENTARGET 1
  #define PAYTERMCASHDISOUNT 2
  #define PAYTERMUPD_FLAG 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define PAYTERM_H
 #define PAYTERM_ANZ ( sizeof(PAYTERM_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PAYTERM *******************************************************/

 #define PAYTERM_LISTE \
         PAYMENTTERMS.PAYMENT_TERM,\
         PAYMENTTERMS.PAYMENTARGET,\
         PAYMENTTERMS.CASHDISOUNT,\
         PAYMENTTERMS.UPD_FLAG

 #define PAYTERM_LISTE_390 \
         PAYMENT_TERM,\
         PAYMENTARGET,\
         CASHDISOUNT,\
         UPD_FLAG

 #define PAYTERM_PLISTE \
         "PAYMENTTERMS.PAYMENT_TERM,"\
         "PAYMENTTERMS.PAYMENTARGET,"\
         "PAYMENTTERMS.CASHDISOUNT,"\
         "PAYMENTTERMS.UPD_FLAG"

 #define PAYTERM_PELISTE \
         "PAYMENT_TERM,"\
         "PAYMENTARGET,"\
         "CASHDISOUNT,"\
         "UPD_FLAG"

 #define PAYTERM_UPDLISTE \
         "PAYMENT_TERM=?,"\
         "PAYMENTARGET=?,"\
         "CASHDISOUNT=?,"\
         "UPD_FLAG=?"

/* SqlMacros-Define of PAYTERM ************************************************/

 #define PAYTERM_ZEIGER(x) \
         :x->PAYMENT_TERM,\
         :x->PAYMENTARGET,\
         :x->CASHDISOUNT,\
         :x->UPD_FLAG

 #define PAYTERM_ZEIGERSEL(x) \
         :x->PAYMENT_TERM,\
         :x->PAYMENTARGET,\
         :x->CASHDISOUNT,\
         :x->UPD_FLAG

 #define PAYTERM_UPDATE(x) \
         PAYMENTTERMS.PAYMENT_TERM=:x->PAYMENT_TERM,\
         PAYMENTTERMS.PAYMENTARGET=:x->PAYMENTARGET,\
         PAYMENTTERMS.CASHDISOUNT=:x->CASHDISOUNT,\
         PAYMENTTERMS.UPD_FLAG=:x->UPD_FLAG

/* SqlMacros390-Define of PAYTERM *********************************************/

 #define PAYTERM_ZEIGER_390 \
         :PAYMENT_TERM,\
         :PAYMENTARGET,\
         :CASHDISOUNT,\
         :UPD_FLAG

 #define PAYTERM_UPDATE_390 \
         PAYMENT_TERM=:PAYMENT_TERM,\
         PAYMENTARGET=:PAYMENTARGET,\
         CASHDISOUNT=:CASHDISOUNT,\
         UPD_FLAG=:UPD_FLAG

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of PAYTERM ************************************************/

 #ifndef TRANSCLASS
 typedef struct N_PAYTERM {
         char PAYMENT_TERM[5];
         short PAYMENTARGET;
         double CASHDISOUNT;
         char UPD_FLAG[2];
         long FETCH_REL;
        } paytermS;
 #else /*TRANSCLASS*/
 typedef struct N_PAYTERM {
         char PAYMENT_TERM[5];
         short PAYMENTARGET;
         double CASHDISOUNT;
         char UPD_FLAG[2];
         long FETCH_REL;
			bool operator==(const N_PAYTERM& right) const {
			return(
				!strcmp(PAYMENT_TERM, right.PAYMENT_TERM) &&
				PAYMENTARGET == right.PAYMENTARGET &&
				CASHDISOUNT == right.CASHDISOUNT &&
				!strcmp(UPD_FLAG, right.UPD_FLAG)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				strcpy(PAYMENT_TERM, " " );
				PAYMENTARGET = 0;
				CASHDISOUNT = 0;
				strcpy(UPD_FLAG, " " );
#endif
			}
         } paytermS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PAYTERM *******************************************/

 struct S_PAYTERM {
         char PAYMENT_TERM[4 + 1];
         char PAYMENTARGET[7];
         char CASHDISOUNT[5 + 2];
         char UPD_FLAG[1 + 1];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PAYTERM **************************/

 struct O_PAYTERM {
         char PAYMENT_TERM[4];
         char PAYMENTARGET[7];
         char CASHDISOUNT[5];
         char UPD_FLAG[1];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PAYTERM *************************************/

 struct C_PAYTERM {
         char PAYMENT_TERM[5];
         short PAYMENTARGET;
         double CASHDISOUNT;
         char UPD_FLAG;
         long FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PAYTERM ***********************************/

 struct I_PAYTERM {
         short PAYMENT_TERM;
         short PAYMENTARGET;
         short CASHDISOUNT;
         short UPD_FLAG;
         short FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PAYTERM *********************************************/

#if defined (BUF_DESC)
 static struct buf_desc PAYTERM_BES [] =
 {
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc PAYTERM_BES [] =
 {
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of PAYTERM ***************************************/

 #define PAYTERM_S390 \
         char PAYMENT_TERM[5]; \
         short PAYMENTARGET; \
         double CASHDISOUNT; \
         char UPD_FLAG; \
         long FETCH_REL;



/* Copy-Function Struct to single Data PAYTERM ********************************/

 #define PAYTERM_S390_COPY_TO_SINGLE(_x_) \
          strcpy(PAYMENT_TERM,_x_->PAYMENT_TERM);\
         PAYMENTARGET=_x_->PAYMENTARGET;\
         CASHDISOUNT=_x_->CASHDISOUNT;\
         UPD_FLAG=_x_->UPD_FLAG;\
          FETCH_REL=_x_->FETCH_REL;\

 #define PAYTERM_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->PAYMENT_TERM,PAYMENT_TERM);\
          _x_->PAYMENTARGET=PAYMENTARGET;\
          _x_->CASHDISOUNT=CASHDISOUNT;\
          _x_->UPD_FLAG=UPD_FLAG;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of PayTerm *******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of PayTerm ***************************************/


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

class CPAYTERM : public ppDadeVirtual
{
	//data members
	public:
		paytermS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<paytermS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<paytermS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<paytermS>; Strip(s); paytermS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<paytermS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<paytermS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<paytermS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const char*	GetPayment_term(ppString& t) const 	{ t = s.PAYMENT_TERM; t.erasespace(ppString::END); return t.c_str(); }
		short		GetPaymentarget() const	{ return s.PAYMENTARGET; }
		double		GetCashdisount() const	{ return s.CASHDISOUNT; }
		char		GetUpd_flag() const	{ return s.UPD_FLAG[0]; }
		const paytermS& GetStruct() const { return s; }
		long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetPayment_term(const ppString& t) { ppGStrCopy(s.PAYMENT_TERM,t.c_str() ,L_PAYTERM_PAYMENT_TERM); }
		void 		SetPaymentarget(short t) { s.PAYMENTARGET = t; }
		void 		SetCashdisount(double t) { s.CASHDISOUNT = t; }
		void 		SetUpd_flag(char t) { s.UPD_FLAG[0] = t; s.UPD_FLAG[1] = '\0';}
		void 		SetStruct(const paytermS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CPAYTERM()  //constructor
		{
			::buf_default((void *)&s, PAYTERM_BES, PAYTERM_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CPAYTERM()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, PAYTERM_BES, PAYTERM_ANZ);
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s,PAYTERM_BES,PAYTERM_ANZ, error_msg);
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
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, PAYTERM_BES, PAYTERM_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, PAYTERM_BES, PAYTERM_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_PAYTERM& d)
		{
#ifdef WIN32
			ppGStripLast(d.PAYMENT_TERM);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, PAYTERM_BES, PAYTERM_ANZ, error_msg);
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
			CPAYTERM c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber   = FncNr;
				AnzPos      = 0;
				if ( pl ) delete pl;
				pl = new vector<paytermS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s, PAYTERM_BES, PAYTERM_ANZ, error_msg);
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

/* CreateSqlStatement of PAYTERM **********************************************/

 #define PAYTERM_CREATE(x) exec sql create table x (\
         PAYMENT_TERM char(4) default " " not null,\
         PAYMENTARGET smallint default 0 not null,\
         CASHDISOUNT decimal(5,2) default 0 not null,\
         UPD_FLAG char(1) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of PAYTERM ********************************************/

 #define PAYTERM_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_payterm_1 on _X_(\
              payment_term,\
              paymentarget );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PAYTERM ********************************************/

 #define PAYTERM_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_payterm_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

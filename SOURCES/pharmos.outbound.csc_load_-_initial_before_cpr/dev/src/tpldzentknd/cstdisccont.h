#ifndef __PP_CSTDISCCONT_H_
#define __PP_CSTDISCCONT_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\tpldzentknd\CstDiscCont *************************************/
/******************************************************************************/

/* Length-Define of CSTDISCCONT ***********************************************/

  #define L_CSTDISCCONT_BRANCHNO 6
  #define L_CSTDISCCONT_CUSTOMERNO 11
  #define L_CSTDISCCONT_ORDER_TYPE 2
  #define L_CSTDISCCONT_PHARMACYGROUPID 3
  #define L_CSTDISCCONT_SUB_ORDER_TYPE 3
  #define L_CSTDISCCONT_PAYMENT_TERM 4
  #define L_CSTDISCCONT_VALUTA_DAYS 6
  #define L_CSTDISCCONT_MIN_ORDER_VALUE 9
  #define N_CSTDISCCONT_MIN_ORDER_VALUE 2
  #define L_CSTDISCCONT_MIN_TUBES 6
  #define L_CSTDISCCONT_LOSS_IN_DISCOUNT 5
  #define N_CSTDISCCONT_LOSS_IN_DISCOUNT 2
  #define L_CSTDISCCONT_UPD_FLAG 1

/* Length/Count-Define of CSTDISCCONT *****************************************/

  #define LS_CSTDISCCONT_BRANCHNO 5 + 1
  #define LS_CSTDISCCONT_CUSTOMERNO 10 + 1
  #define LS_CSTDISCCONT_ORDER_TYPE 2 + 1
  #define LS_CSTDISCCONT_PHARMACYGROUPID 3 + 1
  #define LS_CSTDISCCONT_SUB_ORDER_TYPE 3 + 1
  #define LS_CSTDISCCONT_PAYMENT_TERM 4 + 1
  #define LS_CSTDISCCONT_VALUTA_DAYS 5 + 1
  #define LS_CSTDISCCONT_MIN_ORDER_VALUE 9 + 2
  #define LS_CSTDISCCONT_MIN_TUBES 5 + 1
  #define LS_CSTDISCCONT_LOSS_IN_DISCOUNT 5 + 2
  #define LS_CSTDISCCONT_UPD_FLAG 1 + 1

  #define CSTDISCCONTBRANCHNO 0
  #define CSTDISCCONTCUSTOMERNO 1
  #define CSTDISCCONTORDER_TYPE 2
  #define CSTDISCCONTPHARMACYGROUPID 3
  #define CSTDISCCONTSUB_ORDER_TYPE 4
  #define CSTDISCCONTPAYMENT_TERM 5
  #define CSTDISCCONTVALUTA_DAYS 6
  #define CSTDISCCONTMIN_ORDER_VALUE 7
  #define CSTDISCCONTMIN_TUBES 8
  #define CSTDISCCONTLOSS_IN_DISCOUNT 9
  #define CSTDISCCONTUPD_FLAG 10

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CSTDISCCONT_H
 #define CSTDISCCONT_ANZ ( sizeof(CSTDISCCONT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSTDISCCONT ***************************************************/

 #define CSTDISCCONT_LISTE \
         CSTDISCOUNTCONT.BRANCHNO,\
         CSTDISCOUNTCONT.CUSTOMERNO,\
         CSTDISCOUNTCONT.ORDER_TYPE,\
         DISCOUNTLIST.PHARMACYGROUPID,\
         CSTDISCOUNTCONT.SUB_ORDER_TYPE,\
         CSTDISCOUNTCONT.PAYMENT_TERM,\
         CSTDISCOUNTCONT.VALUTA_DAYS,\
         CSTDISCOUNTCONT.MIN_ORDER_VALUE,\
         CSTDISCOUNTCONT.MIN_TUBES,\
         CSTDISCOUNTCONT.LOSS_IN_DISCOUNT,\
         CSTDISCOUNTCONT.UPD_FLAG

 #define CSTDISCCONT_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         ORDER_TYPE,\
         PHARMACYGROUPID,\
         SUB_ORDER_TYPE,\
         PAYMENT_TERM,\
         VALUTA_DAYS,\
         MIN_ORDER_VALUE,\
         MIN_TUBES,\
         LOSS_IN_DISCOUNT,\
         UPD_FLAG

 #define CSTDISCCONT_PLISTE \
         "CSTDISCOUNTCONT.BRANCHNO,"\
         "CSTDISCOUNTCONT.CUSTOMERNO,"\
         "CSTDISCOUNTCONT.ORDER_TYPE,"\
         "DISCOUNTLIST.PHARMACYGROUPID,"\
         "CSTDISCOUNTCONT.SUB_ORDER_TYPE,"\
         "CSTDISCOUNTCONT.PAYMENT_TERM,"\
         "CSTDISCOUNTCONT.VALUTA_DAYS,"\
         "CSTDISCOUNTCONT.MIN_ORDER_VALUE,"\
         "CSTDISCOUNTCONT.MIN_TUBES,"\
         "CSTDISCOUNTCONT.LOSS_IN_DISCOUNT,"\
         "CSTDISCOUNTCONT.UPD_FLAG"

 #define CSTDISCCONT_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "ORDER_TYPE,"\
         "PHARMACYGROUPID,"\
         "SUB_ORDER_TYPE,"\
         "PAYMENT_TERM,"\
         "VALUTA_DAYS,"\
         "MIN_ORDER_VALUE,"\
         "MIN_TUBES,"\
         "LOSS_IN_DISCOUNT,"\
         "UPD_FLAG"

 #define CSTDISCCONT_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "ORDER_TYPE=?,"\
         "PHARMACYGROUPID=?,"\
         "SUB_ORDER_TYPE=?,"\
         "PAYMENT_TERM=?,"\
         "VALUTA_DAYS=?,"\
         "MIN_ORDER_VALUE=?,"\
         "MIN_TUBES=?,"\
         "LOSS_IN_DISCOUNT=?,"\
         "UPD_FLAG=?"

/* SqlMacros-Define of CSTDISCCONT ********************************************/

 #define CSTDISCCONT_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ORDER_TYPE,\
         :x->PHARMACYGROUPID,\
         :x->SUB_ORDER_TYPE,\
         :x->PAYMENT_TERM,\
         :x->VALUTA_DAYS,\
         :x->MIN_ORDER_VALUE,\
         :x->MIN_TUBES,\
         :x->LOSS_IN_DISCOUNT,\
         :x->UPD_FLAG

 #define CSTDISCCONT_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ORDER_TYPE,\
         :x->PHARMACYGROUPID,\
         :x->SUB_ORDER_TYPE,\
         :x->PAYMENT_TERM,\
         :x->VALUTA_DAYS,\
         :x->MIN_ORDER_VALUE,\
         :x->MIN_TUBES,\
         :x->LOSS_IN_DISCOUNT,\
         :x->UPD_FLAG

 #define CSTDISCCONT_UPDATE(x) \
         CSTDISCOUNTCONT.BRANCHNO=:x->BRANCHNO,\
         CSTDISCOUNTCONT.CUSTOMERNO=:x->CUSTOMERNO,\
         CSTDISCOUNTCONT.ORDER_TYPE=:x->ORDER_TYPE,\
         DISCOUNTLIST.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         CSTDISCOUNTCONT.SUB_ORDER_TYPE=:x->SUB_ORDER_TYPE,\
         CSTDISCOUNTCONT.PAYMENT_TERM=:x->PAYMENT_TERM,\
         CSTDISCOUNTCONT.VALUTA_DAYS=:x->VALUTA_DAYS,\
         CSTDISCOUNTCONT.MIN_ORDER_VALUE=:x->MIN_ORDER_VALUE,\
         CSTDISCOUNTCONT.MIN_TUBES=:x->MIN_TUBES,\
         CSTDISCOUNTCONT.LOSS_IN_DISCOUNT=:x->LOSS_IN_DISCOUNT,\
         CSTDISCOUNTCONT.UPD_FLAG=:x->UPD_FLAG

/* SqlMacros390-Define of CSTDISCCONT *****************************************/

 #define CSTDISCCONT_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :ORDER_TYPE,\
         :PHARMACYGROUPID,\
         :SUB_ORDER_TYPE,\
         :PAYMENT_TERM,\
         :VALUTA_DAYS,\
         :MIN_ORDER_VALUE,\
         :MIN_TUBES,\
         :LOSS_IN_DISCOUNT,\
         :UPD_FLAG

 #define CSTDISCCONT_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         ORDER_TYPE=:ORDER_TYPE,\
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         SUB_ORDER_TYPE=:SUB_ORDER_TYPE,\
         PAYMENT_TERM=:PAYMENT_TERM,\
         VALUTA_DAYS=:VALUTA_DAYS,\
         MIN_ORDER_VALUE=:MIN_ORDER_VALUE,\
         MIN_TUBES=:MIN_TUBES,\
         LOSS_IN_DISCOUNT=:LOSS_IN_DISCOUNT,\
         UPD_FLAG=:UPD_FLAG

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CSTDISCCONT ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_CSTDISCCONT {
         short BRANCHNO;
         long CUSTOMERNO;
         char ORDER_TYPE[3];
         char PHARMACYGROUPID[4];
         char SUB_ORDER_TYPE[4];
         char PAYMENT_TERM[5];
         short VALUTA_DAYS;
         double MIN_ORDER_VALUE;
         short MIN_TUBES;
         double LOSS_IN_DISCOUNT;
         char UPD_FLAG[2];
         long FETCH_REL;
        } cstdisccontS;
 #else /*TRANSCLASS*/
 typedef struct N_CSTDISCCONT {
         short BRANCHNO;
         long CUSTOMERNO;
         char ORDER_TYPE[3];
         char PHARMACYGROUPID[4];
         char SUB_ORDER_TYPE[4];
         char PAYMENT_TERM[5];
         short VALUTA_DAYS;
         double MIN_ORDER_VALUE;
         short MIN_TUBES;
         double LOSS_IN_DISCOUNT;
         char UPD_FLAG[2];
         long FETCH_REL;
			bool operator==(const N_CSTDISCCONT& right) const {
			return(
				BRANCHNO == right.BRANCHNO &&
				CUSTOMERNO == right.CUSTOMERNO &&
				!strcmp(ORDER_TYPE, right.ORDER_TYPE) &&
				!strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
				!strcmp(SUB_ORDER_TYPE, right.SUB_ORDER_TYPE) &&
				!strcmp(PAYMENT_TERM, right.PAYMENT_TERM) &&
				VALUTA_DAYS == right.VALUTA_DAYS &&
				MIN_ORDER_VALUE == right.MIN_ORDER_VALUE &&
				MIN_TUBES == right.MIN_TUBES &&
				LOSS_IN_DISCOUNT == right.LOSS_IN_DISCOUNT &&
				!strcmp(UPD_FLAG, right.UPD_FLAG)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				BRANCHNO = 0;
				CUSTOMERNO = 0;
				strcpy(ORDER_TYPE, " " );
				strcpy(PHARMACYGROUPID, " " );
				strcpy(SUB_ORDER_TYPE, " " );
				strcpy(PAYMENT_TERM, " " );
				VALUTA_DAYS = 0;
				MIN_ORDER_VALUE = 0;
				MIN_TUBES = 0;
				LOSS_IN_DISCOUNT = 0;
				strcpy(UPD_FLAG, " " );
#endif
			}
         } cstdisccontS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSTDISCCONT ***************************************/

 struct S_CSTDISCCONT {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ORDER_TYPE[2 + 1];
         char PHARMACYGROUPID[3 + 1];
         char SUB_ORDER_TYPE[3 + 1];
         char PAYMENT_TERM[4 + 1];
         char VALUTA_DAYS[7];
         char MIN_ORDER_VALUE[9 + 2];
         char MIN_TUBES[7];
         char LOSS_IN_DISCOUNT[5 + 2];
         char UPD_FLAG[1 + 1];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSTDISCCONT **********************/

 struct O_CSTDISCCONT {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ORDER_TYPE[2];
         char PHARMACYGROUPID[3];
         char SUB_ORDER_TYPE[3];
         char PAYMENT_TERM[4];
         char VALUTA_DAYS[7];
         char MIN_ORDER_VALUE[9];
         char MIN_TUBES[7];
         char LOSS_IN_DISCOUNT[5];
         char UPD_FLAG[1];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSTDISCCONT *********************************/

 struct C_CSTDISCCONT {
         short BRANCHNO;
         long CUSTOMERNO;
         char ORDER_TYPE[3];
         char PHARMACYGROUPID[4];
         char SUB_ORDER_TYPE[4];
         char PAYMENT_TERM[5];
         short VALUTA_DAYS;
         double MIN_ORDER_VALUE;
         short MIN_TUBES;
         double LOSS_IN_DISCOUNT;
         char UPD_FLAG;
         long FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSTDISCCONT *******************************/

 struct I_CSTDISCCONT {
         short BRANCHNO;
         short CUSTOMERNO;
         short ORDER_TYPE;
         short PHARMACYGROUPID;
         short SUB_ORDER_TYPE;
         short PAYMENT_TERM;
         short VALUTA_DAYS;
         short MIN_ORDER_VALUE;
         short MIN_TUBES;
         short LOSS_IN_DISCOUNT;
         short UPD_FLAG;
         short FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSTDISCCONT *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc CSTDISCCONT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CSTDISCCONT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 4, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of CSTDISCCONT ***********************************/

 #define CSTDISCCONT_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         char ORDER_TYPE[3]; \
         char PHARMACYGROUPID[4]; \
         char SUB_ORDER_TYPE[4]; \
         char PAYMENT_TERM[5]; \
         short VALUTA_DAYS; \
         double MIN_ORDER_VALUE; \
         short MIN_TUBES; \
         double LOSS_IN_DISCOUNT; \
         char UPD_FLAG; \
         long FETCH_REL;



/* Copy-Function Struct to single Data CSTDISCCONT ****************************/

 #define CSTDISCCONT_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
          strcpy(ORDER_TYPE,_x_->ORDER_TYPE);\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
          strcpy(SUB_ORDER_TYPE,_x_->SUB_ORDER_TYPE);\
          strcpy(PAYMENT_TERM,_x_->PAYMENT_TERM);\
         VALUTA_DAYS=_x_->VALUTA_DAYS;\
         MIN_ORDER_VALUE=_x_->MIN_ORDER_VALUE;\
         MIN_TUBES=_x_->MIN_TUBES;\
         LOSS_IN_DISCOUNT=_x_->LOSS_IN_DISCOUNT;\
         UPD_FLAG=_x_->UPD_FLAG;\
          FETCH_REL=_x_->FETCH_REL;\

 #define CSTDISCCONT_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          strcpy(_x_->ORDER_TYPE,ORDER_TYPE);\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          strcpy(_x_->SUB_ORDER_TYPE,SUB_ORDER_TYPE);\
          strcpy(_x_->PAYMENT_TERM,PAYMENT_TERM);\
          _x_->VALUTA_DAYS=VALUTA_DAYS;\
          _x_->MIN_ORDER_VALUE=MIN_ORDER_VALUE;\
          _x_->MIN_TUBES=MIN_TUBES;\
          _x_->LOSS_IN_DISCOUNT=LOSS_IN_DISCOUNT;\
          _x_->UPD_FLAG=UPD_FLAG;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of CstDiscCont ***************************************/

  #define CSTDISCCONT_SELLIST 1431

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CstDiscCont ***********************************/

  #define SelList 1431

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

class CCSTDISCCONT : public ppDadeVirtual
{
	//data members
	public:
		cstdisccontS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<cstdisccontS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstdisccontS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<cstdisccontS>; Strip(s); cstdisccontS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstdisccontS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<cstdisccontS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<cstdisccontS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetBranchno() const	{ return s.BRANCHNO; }
		long		GetCustomerno() const	{ return s.CUSTOMERNO; }
		const char*	GetOrder_type(ppString& t) const 	{ t = s.ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetPharmacygroupid(ppString& t) const 	{ t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetSub_order_type(ppString& t) const 	{ t = s.SUB_ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetPayment_term(ppString& t) const 	{ t = s.PAYMENT_TERM; t.erasespace(ppString::END); return t.c_str(); }
		short		GetValuta_days() const	{ return s.VALUTA_DAYS; }
		double		GetMin_order_value() const	{ return s.MIN_ORDER_VALUE; }
		short		GetMin_tubes() const	{ return s.MIN_TUBES; }
		double		GetLoss_in_discount() const	{ return s.LOSS_IN_DISCOUNT; }
		char		GetUpd_flag() const	{ return s.UPD_FLAG[0]; }
		const cstdisccontS& GetStruct() const { return s; }
		long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetBranchno(short t) { s.BRANCHNO = t; }
		void 		SetCustomerno(long t) { s.CUSTOMERNO = t; }
		void 		SetOrder_type(const ppString& t) { ppGStrCopy(s.ORDER_TYPE,t.c_str() ,L_CSTDISCCONT_ORDER_TYPE); }
		void 		SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_CSTDISCCONT_PHARMACYGROUPID); }
		void 		SetSub_order_type(const ppString& t) { ppGStrCopy(s.SUB_ORDER_TYPE,t.c_str() ,L_CSTDISCCONT_SUB_ORDER_TYPE); }
		void 		SetPayment_term(const ppString& t) { ppGStrCopy(s.PAYMENT_TERM,t.c_str() ,L_CSTDISCCONT_PAYMENT_TERM); }
		void 		SetValuta_days(short t) { s.VALUTA_DAYS = t; }
		void 		SetMin_order_value(double t) { s.MIN_ORDER_VALUE = t; }
		void 		SetMin_tubes(short t) { s.MIN_TUBES = t; }
		void 		SetLoss_in_discount(double t) { s.LOSS_IN_DISCOUNT = t; }
		void 		SetUpd_flag(char t) { s.UPD_FLAG[0] = t; s.UPD_FLAG[1] = '\0';}
		void 		SetStruct(const cstdisccontS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }
		int 		SelList(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1431,FetchRel,pos); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CCSTDISCCONT()  //constructor
		{
			::buf_default((void *)&s, CSTDISCCONT_BES, CSTDISCCONT_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CCSTDISCCONT()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, CSTDISCCONT_BES, CSTDISCCONT_ANZ);
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s,CSTDISCCONT_BES,CSTDISCCONT_ANZ, error_msg);
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
			if( fkt_nr == 1431 ) 	return CursorServerCall(1431,s.FETCH_REL,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_CSTDISCCONT& d)
		{
#ifdef WIN32
			ppGStripLast(d.ORDER_TYPE);
			ppGStripLast(d.PHARMACYGROUPID);
			ppGStripLast(d.SUB_ORDER_TYPE);
			ppGStripLast(d.PAYMENT_TERM);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, CSTDISCCONT_BES, CSTDISCCONT_ANZ, error_msg);
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
			CCSTDISCCONT c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber   = FncNr;
				AnzPos      = 0;
				if ( pl ) delete pl;
				pl = new vector<cstdisccontS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s, CSTDISCCONT_BES, CSTDISCCONT_ANZ, error_msg);
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

/* CreateSqlStatement of CSTDISCCONT ******************************************/

 #define CSTDISCCONT_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ORDER_TYPE char(2) default " " not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         SUB_ORDER_TYPE char(3) default " " not null,\
         PAYMENT_TERM char(4) default " " not null,\
         VALUTA_DAYS smallint default 0 not null,\
         MIN_ORDER_VALUE decimal(9,2) default 0 not null,\
         MIN_TUBES smallint default 0 not null,\
         LOSS_IN_DISCOUNT decimal(5,2) default 0 not null,\
         UPD_FLAG char(1) default " " not null) extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of CSTDISCCONT ****************************************/

 #define CSTDISCCONT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_cstdisccont_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              order_type,\
              sub_order_type );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSTDISCCONT ****************************************/

 #define CSTDISCCONT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_cstdisccont_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

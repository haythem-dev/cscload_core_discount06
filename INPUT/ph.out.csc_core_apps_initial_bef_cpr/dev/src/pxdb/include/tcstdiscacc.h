#ifndef __PP_CSTDISCACC_H_
#define __PP_CSTDISCACC_H_

/******************************************************************************/
/* u:\tCstDiscAcc *************************************************************/
/******************************************************************************/

/* Length-Define of CSTDISCACC ***********************************************/

  #define L_CSTDISCACC_BRANCHNO 6
  #define L_CSTDISCACC_CUSTOMERNO 11
  #define L_CSTDISCACC_MAINCSTNO 11
  #define L_CSTDISCACC_BALANCE 11
  #define N_CSTDISCACC_BALANCE 2
  #define L_CSTDISCACC_KDAUFTRAGNR 11
  #define L_CSTDISCACC_DATE 11
  #define L_CSTDISCACC_INVOICENUMBER 15
  #define L_CSTDISCACC_INVOICEAMOUNT 11
  #define N_CSTDISCACC_INVOICEAMOUNT 2
  #define L_CSTDISCACC_VOUCHERTYP 2
  #define L_CSTDISCACC_PREIS_TYP 6
  #define L_CSTDISCACC_PRIORITY 6
  #define L_CSTDISCACC_KDAUFTRAGNRSPLIT 11
  #define L_CSTDISCACC_INVOICEPAID 11
  #define N_CSTDISCACC_INVOICEPAID 2
  #define L_CSTDISCACC_PAYMENTARGET 6
  #define L_CSTDISCACC_LFDNR 11

/* Length/Count-Define of CSTDISCACC *****************************************/

  #define LS_CSTDISCACC_BRANCHNO 5 + 1
  #define LS_CSTDISCACC_CUSTOMERNO 10 + 1
  #define LS_CSTDISCACC_MAINCSTNO 10 + 1
  #define LS_CSTDISCACC_BALANCE 11 + 2
  #define LS_CSTDISCACC_KDAUFTRAGNR 10 + 1
  #define LS_CSTDISCACC_DATE 10 + 1
  #define LS_CSTDISCACC_INVOICENUMBER 15 + 1
  #define LS_CSTDISCACC_INVOICEAMOUNT 11 + 2
  #define LS_CSTDISCACC_VOUCHERTYP 2 + 1
  #define LS_CSTDISCACC_PREIS_TYP 5 + 1
  #define LS_CSTDISCACC_PRIORITY 5 + 1
  #define LS_CSTDISCACC_KDAUFTRAGNRSPLIT 10 + 1
  #define LS_CSTDISCACC_INVOICEPAID 11 + 2
  #define LS_CSTDISCACC_PAYMENTARGET 5 + 1
  #define LS_CSTDISCACC_LFDNR 10 + 1

  #define CSTDISCACCBRANCHNO 0
  #define CSTDISCACCCUSTOMERNO 1
  #define CSTDISCACCMAINCSTNO 2
  #define CSTDISCACCBALANCE 3
  #define CSTDISCACCKDAUFTRAGNR 4
  #define CSTDISCACCDATE 5
  #define CSTDISCACCINVOICENUMBER 6
  #define CSTDISCACCINVOICEAMOUNT 7
  #define CSTDISCACCVOUCHERTYP 8
  #define CSTDISCACCPREIS_TYP 9
  #define CSTDISCACCPRIORITY 10
  #define CSTDISCACCKDAUFTRAGNRSPLIT 11
  #define CSTDISCACCINVOICEPAID 12
  #define CSTDISCACCPAYMENTARGET 13
  #define CSTDISCACCLFDNR 14

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CSTDISCACC_H
 #define CSTDISCACC_ANZ ( sizeof(CSTDISCACC_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSTDISCACC ***************************************************/

 #define CSTDISCACC_LISTE \
         CSTDISCACC.BRANCHNO,\
         CSTDISCACC.CUSTOMERNO,\
         CSTDISCACC.MAINCSTNO,\
         CSTDISCACC.BALANCE,\
         CSTDISCACC.KDAUFTRAGNR,\
         CSTDISCACC.DATE,\
         CSTDISCACC.INVOICENUMBER,\
         CSTDISCACC.INVOICEAMOUNT,\
         CSTDISCACC.VOUCHERTYP,\
         CSTDISCACC.PREIS_TYP,\
         CSTDISCACC.PRIORITY,\
         CSTDISCACC.KDAUFTRAGNRSPLIT,\
         CSTDISCACC.INVOICEPAID,\
         CSTDISCACC.PAYMENTARGET,\
         CSTDISCACC.LFDNR

 #define CSTDISCACC_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         MAINCSTNO,\
         BALANCE,\
         KDAUFTRAGNR,\
         DATE,\
         INVOICENUMBER,\
         INVOICEAMOUNT,\
         VOUCHERTYP,\
         PREIS_TYP,\
         PRIORITY,\
         KDAUFTRAGNRSPLIT,\
         INVOICEPAID,\
         PAYMENTARGET,\
         LFDNR

 #define CSTDISCACC_PLISTE \
         "CSTDISCACC.BRANCHNO,"\
         "CSTDISCACC.CUSTOMERNO,"\
         "CSTDISCACC.MAINCSTNO,"\
         "CSTDISCACC.BALANCE,"\
         "CSTDISCACC.KDAUFTRAGNR,"\
         "CSTDISCACC.DATE,"\
         "CSTDISCACC.INVOICENUMBER,"\
         "CSTDISCACC.INVOICEAMOUNT,"\
         "CSTDISCACC.VOUCHERTYP,"\
         "CSTDISCACC.PREIS_TYP,"\
         "CSTDISCACC.PRIORITY,"\
         "CSTDISCACC.KDAUFTRAGNRSPLIT,"\
         "CSTDISCACC.INVOICEPAID,"\
         "CSTDISCACC.PAYMENTARGET,"\
         "CSTDISCACC.LFDNR"

 #define CSTDISCACC_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "MAINCSTNO,"\
         "BALANCE,"\
         "KDAUFTRAGNR,"\
         "DATE,"\
         "INVOICENUMBER,"\
         "INVOICEAMOUNT,"\
         "VOUCHERTYP,"\
         "PREIS_TYP,"\
         "PRIORITY,"\
         "KDAUFTRAGNRSPLIT,"\
         "INVOICEPAID,"\
         "PAYMENTARGET,"\
         "LFDNR"

 #define CSTDISCACC_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "MAINCSTNO=?,"\
         "BALANCE=?,"\
         "KDAUFTRAGNR=?,"\
         "DATE=?,"\
         "INVOICENUMBER=?,"\
         "INVOICEAMOUNT=?,"\
         "VOUCHERTYP=?,"\
         "PREIS_TYP=?,"\
         "PRIORITY=?,"\
         "KDAUFTRAGNRSPLIT=?,"\
         "INVOICEPAID=?,"\
         "PAYMENTARGET=?,"\
         "LFDNR=?"

/* SqlMacros-Define of CSTDISCACC ********************************************/

 #define CSTDISCACC_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->MAINCSTNO,\
         :x->BALANCE,\
         :x->KDAUFTRAGNR,\
         :x->DATE,\
         :x->INVOICENUMBER,\
         :x->INVOICEAMOUNT,\
         :x->VOUCHERTYP,\
         :x->PREIS_TYP,\
         :x->PRIORITY,\
         :x->KDAUFTRAGNRSPLIT,\
         :x->INVOICEPAID,\
         :x->PAYMENTARGET,\
         :x->LFDNR

 #define CSTDISCACC_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->MAINCSTNO,\
         :x->BALANCE,\
         :x->KDAUFTRAGNR,\
         :x->DATE,\
         :x->INVOICENUMBER,\
         :x->INVOICEAMOUNT,\
         :x->VOUCHERTYP,\
         :x->PREIS_TYP,\
         :x->PRIORITY,\
         :x->KDAUFTRAGNRSPLIT,\
         :x->INVOICEPAID,\
         :x->PAYMENTARGET,\
         :x->LFDNR

 #define CSTDISCACC_UPDATE(x) \
         CSTDISCACC.BRANCHNO=:x->BRANCHNO,\
         CSTDISCACC.CUSTOMERNO=:x->CUSTOMERNO,\
         CSTDISCACC.MAINCSTNO=:x->MAINCSTNO,\
         CSTDISCACC.BALANCE=:x->BALANCE,\
         CSTDISCACC.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         CSTDISCACC.DATE=:x->DATE,\
         CSTDISCACC.INVOICENUMBER=:x->INVOICENUMBER,\
         CSTDISCACC.INVOICEAMOUNT=:x->INVOICEAMOUNT,\
         CSTDISCACC.VOUCHERTYP=:x->VOUCHERTYP,\
         CSTDISCACC.PREIS_TYP=:x->PREIS_TYP,\
         CSTDISCACC.PRIORITY=:x->PRIORITY,\
         CSTDISCACC.KDAUFTRAGNRSPLIT=:x->KDAUFTRAGNRSPLIT,\
         CSTDISCACC.INVOICEPAID=:x->INVOICEPAID,\
         CSTDISCACC.PAYMENTARGET=:x->PAYMENTARGET,\
         CSTDISCACC.LFDNR=:x->LFDNR

/* SqlMacros390-Define of CSTDISCACC *****************************************/

 #define CSTDISCACC_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :MAINCSTNO,\
         :BALANCE,\
         :KDAUFTRAGNR,\
         :DATE,\
         :INVOICENUMBER,\
         :INVOICEAMOUNT,\
         :VOUCHERTYP,\
         :PREIS_TYP,\
         :PRIORITY,\
         :KDAUFTRAGNRSPLIT,\
         :INVOICEPAID,\
         :PAYMENTARGET,\
         :LFDNR

 #define CSTDISCACC_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         MAINCSTNO=:MAINCSTNO,\
         BALANCE=:BALANCE,\
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         DATE=:DATE,\
         INVOICENUMBER=:INVOICENUMBER,\
         INVOICEAMOUNT=:INVOICEAMOUNT,\
         VOUCHERTYP=:VOUCHERTYP,\
         PREIS_TYP=:PREIS_TYP,\
         PRIORITY=:PRIORITY,\
         KDAUFTRAGNRSPLIT=:KDAUFTRAGNRSPLIT,\
         INVOICEPAID=:INVOICEPAID,\
         PAYMENTARGET=:PAYMENTARGET,\
         LFDNR=:LFDNR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CSTDISCACC ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_CSTDISCACC {
         short BRANCHNO;
         long CUSTOMERNO;
         long MAINCSTNO;
         double BALANCE;
         long KDAUFTRAGNR;
         long DATE;
         char INVOICENUMBER[16];
         double INVOICEAMOUNT;
         char VOUCHERTYP[3];
         short PREIS_TYP;
         short PRIORITY;
         long KDAUFTRAGNRSPLIT;
         double INVOICEPAID;
         short PAYMENTARGET;
         long LFDNR;
        } tcstdiscaccS;
 #else /*TRANSCLASS*/
 typedef struct N_CSTDISCACC {
         short BRANCHNO;
         long CUSTOMERNO;
         long MAINCSTNO;
         double BALANCE;
         long KDAUFTRAGNR;
         long DATE;
         char INVOICENUMBER[16];
         double INVOICEAMOUNT;
         char VOUCHERTYP[3];
         short PREIS_TYP;
         short PRIORITY;
         long KDAUFTRAGNRSPLIT;
         double INVOICEPAID;
         short PAYMENTARGET;
         long LFDNR;

			bool operator==(const N_CSTDISCACC& right) const {
			return(
				BRANCHNO == right.BRANCHNO &&
				CUSTOMERNO == right.CUSTOMERNO &&
				MAINCSTNO == right.MAINCSTNO &&
				BALANCE == right.BALANCE &&
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				DATE == right.DATE &&
				!strcmp(INVOICENUMBER, right.INVOICENUMBER) &&
				INVOICEAMOUNT == right.INVOICEAMOUNT &&
				!strcmp(VOUCHERTYP, right.VOUCHERTYP) &&
				PREIS_TYP == right.PREIS_TYP &&
				PRIORITY == right.PRIORITY &&
				KDAUFTRAGNRSPLIT == right.KDAUFTRAGNRSPLIT &&
				INVOICEPAID == right.INVOICEPAID &&
				PAYMENTARGET == right.PAYMENTARGET &&
				LFDNR == right.LFDNR
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				BRANCHNO = 0;
				CUSTOMERNO = 0;
				MAINCSTNO = 0;
				BALANCE = 0;
				KDAUFTRAGNR = 0;
				DATE = 0;
				strcpy(INVOICENUMBER, " " );
				INVOICEAMOUNT = 0;
				strcpy(VOUCHERTYP, " " );
				PREIS_TYP = 0;
				PRIORITY = 0;
				KDAUFTRAGNRSPLIT = 0;
				INVOICEPAID = 0;
				PAYMENTARGET = 0;
				LFDNR = 0;
#endif
			}
         } tcstdiscaccS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSTDISCACC ***************************************/

 struct S_CSTDISCACC {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char MAINCSTNO[11];
         char BALANCE[11 + 2];
         char KDAUFTRAGNR[11];
         char DATE[11];
         char INVOICENUMBER[15 + 1];
         char INVOICEAMOUNT[11 + 2];
         char VOUCHERTYP[2 + 1];
         char PREIS_TYP[7];
         char PRIORITY[7];
         char KDAUFTRAGNRSPLIT[11];
         char INVOICEPAID[11 + 2];
         char PAYMENTARGET[7];
         char LFDNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSTDISCACC **********************/

 struct O_CSTDISCACC {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char MAINCSTNO[11];
         char BALANCE[11];
         char KDAUFTRAGNR[11];
         char DATE[11];
         char INVOICENUMBER[15];
         char INVOICEAMOUNT[11];
         char VOUCHERTYP[2];
         char PREIS_TYP[7];
         char PRIORITY[7];
         char KDAUFTRAGNRSPLIT[11];
         char INVOICEPAID[11];
         char PAYMENTARGET[7];
         char LFDNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSTDISCACC *********************************/

 struct C_CSTDISCACC {
         short BRANCHNO;
         long CUSTOMERNO;
         long MAINCSTNO;
         double BALANCE;
         long KDAUFTRAGNR;
         long DATE;
         char INVOICENUMBER[16];
         double INVOICEAMOUNT;
         char VOUCHERTYP[3];
         short PREIS_TYP;
         short PRIORITY;
         long KDAUFTRAGNRSPLIT;
         double INVOICEPAID;
         short PAYMENTARGET;
         long LFDNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSTDISCACC *******************************/

 struct I_CSTDISCACC {
         short BRANCHNO;
         short CUSTOMERNO;
         short MAINCSTNO;
         short BALANCE;
         short KDAUFTRAGNR;
         short DATE;
         short INVOICENUMBER;
         short INVOICEAMOUNT;
         short VOUCHERTYP;
         short PREIS_TYP;
         short PRIORITY;
         short KDAUFTRAGNRSPLIT;
         short INVOICEPAID;
         short PAYMENTARGET;
         short LFDNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSTDISCACC *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc CSTDISCACC_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_D, 11, 2 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CSTDISCACC_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_D, 11, 2 },
   { TYP_C, 2, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of CSTDISCACC ***********************************/

 #define CSTDISCACC_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long MAINCSTNO; \
         double BALANCE; \
         long KDAUFTRAGNR; \
         long DATE; \
         char INVOICENUMBER[16]; \
         double INVOICEAMOUNT; \
         char VOUCHERTYP[3]; \
         short PREIS_TYP; \
         short PRIORITY; \
         long KDAUFTRAGNRSPLIT; \
         double INVOICEPAID; \
         short PAYMENTARGET; \
         long LFDNR; \



/* Copy-Function Struct to single Data CSTDISCACC ****************************/

 #define CSTDISCACC_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         MAINCSTNO=_x_->MAINCSTNO;\
         BALANCE=_x_->BALANCE;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         DATE=_x_->DATE;\
          strcpy(INVOICENUMBER,_x_->INVOICENUMBER);\
         INVOICEAMOUNT=_x_->INVOICEAMOUNT;\
          strcpy(VOUCHERTYP,_x_->VOUCHERTYP);\
         PREIS_TYP=_x_->PREIS_TYP;\
         PRIORITY=_x_->PRIORITY;\
         KDAUFTRAGNRSPLIT=_x_->KDAUFTRAGNRSPLIT;\
         INVOICEPAID=_x_->INVOICEPAID;\
         PAYMENTARGET=_x_->PAYMENTARGET;\
         LFDNR=_x_->LFDNR;\

 #define CSTDISCACC_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->MAINCSTNO=MAINCSTNO;\
          _x_->BALANCE=BALANCE;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->DATE=DATE;\
          strcpy(_x_->INVOICENUMBER,INVOICENUMBER);\
          _x_->INVOICEAMOUNT=INVOICEAMOUNT;\
          strcpy(_x_->VOUCHERTYP,VOUCHERTYP);\
          _x_->PREIS_TYP=PREIS_TYP;\
          _x_->PRIORITY=PRIORITY;\
          _x_->KDAUFTRAGNRSPLIT=KDAUFTRAGNRSPLIT;\
          _x_->INVOICEPAID=INVOICEPAID;\
          _x_->PAYMENTARGET=PAYMENTARGET;\
          _x_->LFDNR=LFDNR;\



/* FunctionNumber-Define of tCstDiscAcc ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of tCstDiscAcc ***********************************/


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

class CCSTDISCACC : public ppDadeVirtual
{
	//data members
	public:
		tcstdiscaccS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<tcstdiscaccS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<tcstdiscaccS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<tcstdiscaccS>; Strip(s); tcstdiscaccS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<tcstdiscaccS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<tcstdiscaccS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<tcstdiscaccS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetBranchno() const	{ return s.BRANCHNO; }
		long		GetCustomerno() const	{ return s.CUSTOMERNO; }
		long		GetMaincstno() const	{ return s.MAINCSTNO; }
		double		GetBalance() const	{ return s.BALANCE; }
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		long		GetDate() const	{ return s.DATE; }
		const char*	GetInvoicenumber(ppString& t) const 	{ t = s.INVOICENUMBER; t.erasespace(ppString::END); return t.c_str(); }
		double		GetInvoiceamount() const	{ return s.INVOICEAMOUNT; }
		const char*	GetVouchertyp(ppString& t) const 	{ t = s.VOUCHERTYP; t.erasespace(ppString::END); return t.c_str(); }
		short		GetPreis_typ() const	{ return s.PREIS_TYP; }
		short		GetPriority() const	{ return s.PRIORITY; }
		long		GetKdauftragnrsplit() const	{ return s.KDAUFTRAGNRSPLIT; }
		double		GetInvoicepaid() const	{ return s.INVOICEPAID; }
		short		GetPaymentarget() const	{ return s.PAYMENTARGET; }
		long		GetLfdnr() const	{ return s.LFDNR; }
		const tcstdiscaccS& GetStruct() const { return s; }
		void 		SetBranchno(short t) { s.BRANCHNO = t; }
		void 		SetCustomerno(long t) { s.CUSTOMERNO = t; }
		void 		SetMaincstno(long t) { s.MAINCSTNO = t; }
		void 		SetBalance(double t) { s.BALANCE = t; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetDate(long t) { s.DATE = t; }
		void 		SetInvoicenumber(const ppString& t) { ppGStrCopy(s.INVOICENUMBER,t.c_str() ,L_CSTDISCACC_INVOICENUMBER); }
		void 		SetInvoiceamount(double t) { s.INVOICEAMOUNT = t; }
		void 		SetVouchertyp(const ppString& t) { ppGStrCopy(s.VOUCHERTYP,t.c_str() ,L_CSTDISCACC_VOUCHERTYP); }
		void 		SetPreis_typ(short t) { s.PREIS_TYP = t; }
		void 		SetPriority(short t) { s.PRIORITY = t; }
		void 		SetKdauftragnrsplit(long t) { s.KDAUFTRAGNRSPLIT = t; }
		void 		SetInvoicepaid(double t) { s.INVOICEPAID = t; }
		void 		SetPaymentarget(short t) { s.PAYMENTARGET = t; }
		void 		SetLfdnr(long t) { s.LFDNR = t; }
		void 		SetStruct(const tcstdiscaccS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CCSTDISCACC()  //constructor
		{
			::buf_default((void *)&s, CSTDISCACC_BES, CSTDISCACC_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CCSTDISCACC()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, CSTDISCACC_BES, CSTDISCACC_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSTDISCACC_BES, CSTDISCACC_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, CSTDISCACC_BES, CSTDISCACC_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_CSTDISCACC& d)
		{
#ifdef WIN32
			ppGStripLast(d.INVOICENUMBER);
			ppGStripLast(d.VOUCHERTYP);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, CSTDISCACC_BES, CSTDISCACC_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of CSTDISCACC ******************************************/

 #define CSTDISCACC_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         MAINCSTNO integer default 0 not null,\
         BALANCE decimal(11,2) default 0 not null,\
         KDAUFTRAGNR integer default 0 not null,\
         DATE integer default 0 not null,\
         INVOICENUMBER char(15) default " " not null,\
         INVOICEAMOUNT decimal(11,2) default 0 not null,\
         VOUCHERTYP char(2) default " " not null,\
         PREIS_TYP smallint default 0 not null,\
         PRIORITY smallint default 0 not null,\
         KDAUFTRAGNRSPLIT integer default 0 not null,\
         INVOICEPAID decimal(11,2) default 0 not null,\
         PAYMENTARGET smallint default 0 not null,\
         LFDNR integer default 0 not null) extent size 40 next size 8 lock mode row;



/* CreateIndexStatement of CSTDISCACC ****************************************/

 #define CSTDISCACC_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_cstdiscacc_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              date,\
              InvoiceNumber,\
              VoucherTyp );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_cstdiscacc_2 on _X_(\
              MainCstNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_cstdiscacc_3 on _X_(\
              kdauftragnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSTDISCACC ****************************************/

 #define CSTDISCACC_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_cstdiscacc_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_cstdiscacc_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_cstdiscacc_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

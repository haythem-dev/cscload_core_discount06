#ifndef __PP_KDAUFTRAGPOSREFUND_H_
#define __PP_KDAUFTRAGPOSREFUND_H_

/******************************************************************************/
/* c:\temp\kdauftragposrefund *************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGPOSREFUND ****************************************/

  #define L_KDAUFTRAGPOSREFUND_KDAUFTRAGNR 11
  #define L_KDAUFTRAGPOSREFUND_POSNR 11
  #define L_KDAUFTRAGPOSREFUND_REFUNDVALUE 9
  #define N_KDAUFTRAGPOSREFUND_REFUNDVALUE 2
  #define L_KDAUFTRAGPOSREFUND_REFUNDSRC 6
  #define L_KDAUFTRAGPOSREFUND_PROMOTION_NO 6

/* Length/Count-Define of KDAUFTRAGPOSREFUND **********************************/

  #define LS_KDAUFTRAGPOSREFUND_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGPOSREFUND_POSNR 10 + 1
  #define LS_KDAUFTRAGPOSREFUND_REFUNDVALUE 9 + 2
  #define LS_KDAUFTRAGPOSREFUND_REFUNDSRC 5 + 1
  #define LS_KDAUFTRAGPOSREFUND_PROMOTION_NO 5 + 1

  #define KDAUFTRAGPOSREFUNDKDAUFTRAGNR 0
  #define KDAUFTRAGPOSREFUNDPOSNR 1
  #define KDAUFTRAGPOSREFUNDREFUNDVALUE 2
  #define KDAUFTRAGPOSREFUNDREFUNDSRC 3
  #define KDAUFTRAGPOSREFUNDPROMOTION_NO 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGPOSREFUND_H
 #define KDAUFTRAGPOSREFUND_ANZ ( sizeof(KDAUFTRAGPOSREFUND_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPOSREFUND ********************************************/

 #define KDAUFTRAGPOSREFUND_LISTE \
         KDAUFTRAGPOSREFUND.KDAUFTRAGNR,\
         KDAUFTRAGPOSREFUND.POSNR,\
         KDAUFTRAGPOSREFUND.REFUNDVALUE,\
         KDAUFTRAGPOSREFUND.REFUNDSRC,\
         KDAUFTRAGPOSREFUND.PROMOTION_NO

 #define KDAUFTRAGPOSREFUND_LISTE_390 \
         KDAUFTRAGNR,\
         POSNR,\
         REFUNDVALUE,\
         REFUNDSRC,\
         PROMOTION_NO

 #define KDAUFTRAGPOSREFUND_PLISTE \
         "KDAUFTRAGPOSREFUND.KDAUFTRAGNR,"\
         "KDAUFTRAGPOSREFUND.POSNR,"\
         "KDAUFTRAGPOSREFUND.REFUNDVALUE,"\
         "KDAUFTRAGPOSREFUND.REFUNDSRC,"\
         "KDAUFTRAGPOSREFUND.PROMOTION_NO"

 #define KDAUFTRAGPOSREFUND_PELISTE \
         "KDAUFTRAGNR,"\
         "POSNR,"\
         "REFUNDVALUE,"\
         "REFUNDSRC,"\
         "PROMOTION_NO"

 #define KDAUFTRAGPOSREFUND_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "POSNR=?,"\
         "REFUNDVALUE=?,"\
         "REFUNDSRC=?,"\
         "PROMOTION_NO=?"

/* SqlMacros-Define of KDAUFTRAGPOSREFUND *************************************/

 #define KDAUFTRAGPOSREFUND_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->REFUNDVALUE,\
         :x->REFUNDSRC,\
         :x->PROMOTION_NO

 #define KDAUFTRAGPOSREFUND_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->REFUNDVALUE,\
         :x->REFUNDSRC,\
         :x->PROMOTION_NO

 #define KDAUFTRAGPOSREFUND_UPDATE(x) \
         KDAUFTRAGPOSREFUND.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGPOSREFUND.POSNR=:x->POSNR,\
         KDAUFTRAGPOSREFUND.REFUNDVALUE=:x->REFUNDVALUE,\
         KDAUFTRAGPOSREFUND.REFUNDSRC=:x->REFUNDSRC,\
         KDAUFTRAGPOSREFUND.PROMOTION_NO=:x->PROMOTION_NO

/* SqlMacros390-Define of KDAUFTRAGPOSREFUND **********************************/

 #define KDAUFTRAGPOSREFUND_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :POSNR,\
         :REFUNDVALUE,\
         :REFUNDSRC,\
         :PROMOTION_NO

 #define KDAUFTRAGPOSREFUND_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         POSNR=:POSNR,\
         REFUNDVALUE=:REFUNDVALUE,\
         REFUNDSRC=:REFUNDSRC,\
         PROMOTION_NO=:PROMOTION_NO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGPOSREFUND *************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGPOSREFUND {
         long KDAUFTRAGNR;
         long POSNR;
         double REFUNDVALUE;
         short REFUNDSRC;
         short PROMOTION_NO;
        } kdauftragposrefundS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGPOSREFUND {
         long KDAUFTRAGNR;
         long POSNR;
         double REFUNDVALUE;
         short REFUNDSRC;
         short PROMOTION_NO;

			bool operator==(const N_KDAUFTRAGPOSREFUND& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				POSNR == right.POSNR &&
				REFUNDVALUE == right.REFUNDVALUE &&
				REFUNDSRC == right.REFUNDSRC &&
				PROMOTION_NO == right.PROMOTION_NO
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				POSNR = 0;
				REFUNDVALUE = 0;
				REFUNDSRC = 0;
				PROMOTION_NO = 0;
#endif
			}
         } kdauftragposrefundS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPOSREFUND ********************************/

 struct S_KDAUFTRAGPOSREFUND {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char REFUNDVALUE[9 + 2];
         char REFUNDSRC[7];
         char PROMOTION_NO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPOSREFUND ***************/

 struct O_KDAUFTRAGPOSREFUND {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char REFUNDVALUE[9];
         char REFUNDSRC[7];
         char PROMOTION_NO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPOSREFUND **************************/

 struct C_KDAUFTRAGPOSREFUND {
         long KDAUFTRAGNR;
         long POSNR;
         double REFUNDVALUE;
         short REFUNDSRC;
         short PROMOTION_NO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPOSREFUND ************************/

 struct I_KDAUFTRAGPOSREFUND {
         short KDAUFTRAGNR;
         short POSNR;
         short REFUNDVALUE;
         short REFUNDSRC;
         short PROMOTION_NO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPOSREFUND **********************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSREFUND_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSREFUND_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGPOSREFUND ****************************/

 #define KDAUFTRAGPOSREFUND_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         double REFUNDVALUE; \
         short REFUNDSRC; \
         short PROMOTION_NO; \



/* Copy-Function Struct to single Data KDAUFTRAGPOSREFUND *********************/

 #define KDAUFTRAGPOSREFUND_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         REFUNDVALUE=_x_->REFUNDVALUE;\
         REFUNDSRC=_x_->REFUNDSRC;\
         PROMOTION_NO=_x_->PROMOTION_NO;\

 #define KDAUFTRAGPOSREFUND_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->REFUNDVALUE=REFUNDVALUE;\
          _x_->REFUNDSRC=REFUNDSRC;\
          _x_->PROMOTION_NO=PROMOTION_NO;\



/* FunctionNumber-Define of kdauftragposrefund ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragposrefund ****************************/


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

class CKDAUFTRAGPOSREFUND : public ppDadeVirtual
{
	//data members
	public:
		kdauftragposrefundS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kdauftragposrefundS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragposrefundS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kdauftragposrefundS>; Strip(s); kdauftragposrefundS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragposrefundS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kdauftragposrefundS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kdauftragposrefundS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		long		GetPosnr() const	{ return s.POSNR; }
		double		GetRefundvalue() const	{ return s.REFUNDVALUE; }
		short		GetRefundsrc() const	{ return s.REFUNDSRC; }
		short		GetPromotion_no() const	{ return s.PROMOTION_NO; }
		const kdauftragposrefundS& GetStruct() const { return s; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetPosnr(long t) { s.POSNR = t; }
		void 		SetRefundvalue(double t) { s.REFUNDVALUE = t; }
		void 		SetRefundsrc(short t) { s.REFUNDSRC = t; }
		void 		SetPromotion_no(short t) { s.PROMOTION_NO = t; }
		void 		SetStruct(const kdauftragposrefundS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CKDAUFTRAGPOSREFUND()  //constructor
		{
			::buf_default((void *)&s, KDAUFTRAGPOSREFUND_BES, KDAUFTRAGPOSREFUND_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CKDAUFTRAGPOSREFUND()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KDAUFTRAGPOSREFUND_BES, KDAUFTRAGPOSREFUND_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPOSREFUND_BES, KDAUFTRAGPOSREFUND_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPOSREFUND_BES, KDAUFTRAGPOSREFUND_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_KDAUFTRAGPOSREFUND& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPOSREFUND_BES, KDAUFTRAGPOSREFUND_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KDAUFTRAGPOSREFUND ***********************************/

 #define KDAUFTRAGPOSREFUND_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         REFUNDVALUE decimal(9,2) default 0 not null,\
         REFUNDSRC smallint default 0 not null,\
         PROMOTION_NO smallint default 0 not null) in ksc extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPOSREFUND *********************************/

 #define KDAUFTRAGPOSREFUND_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_kdaufposrefund_1 on _X_(\
              kdauftragnr,\
              posnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPOSREFUND *********************************/

 #define KDAUFTRAGPOSREFUND_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdaufposrefund_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

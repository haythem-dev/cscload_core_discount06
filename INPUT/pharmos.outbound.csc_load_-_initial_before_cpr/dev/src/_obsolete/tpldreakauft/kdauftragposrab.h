#ifndef __PP_KDAUFTRAGPOSRAB_H_
#define __PP_KDAUFTRAGPOSRAB_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\tpldauftr\kdauftragposrab ***********************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGPOSRAB *******************************************/

  #define L_KDAUFTRAGPOSRAB_KDAUFTRAGNR 11
  #define L_KDAUFTRAGPOSRAB_POSNR 11
  #define L_KDAUFTRAGPOSRAB_DISCOUNTTYPE 6
  #define L_KDAUFTRAGPOSRAB_DISCOUNTVALUEPCT 5
  #define N_KDAUFTRAGPOSRAB_DISCOUNTVALUEPCT 2
  #define L_KDAUFTRAGPOSRAB_PHARMACYGROUPID 3
  #define L_KDAUFTRAGPOSRAB_PAYMENTTARGETNO 6
  #define L_KDAUFTRAGPOSRAB_DISCOUNTVALPCTMAN 5
  #define N_KDAUFTRAGPOSRAB_DISCOUNTVALPCTMAN 2

/* Length/Count-Define of KDAUFTRAGPOSRAB *************************************/

  #define LS_KDAUFTRAGPOSRAB_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGPOSRAB_POSNR 10 + 1
  #define LS_KDAUFTRAGPOSRAB_DISCOUNTTYPE 5 + 1
  #define LS_KDAUFTRAGPOSRAB_DISCOUNTVALUEPCT 5 + 2
  #define LS_KDAUFTRAGPOSRAB_PHARMACYGROUPID 3 + 1
  #define LS_KDAUFTRAGPOSRAB_PAYMENTTARGETNO 5 + 1
  #define LS_KDAUFTRAGPOSRAB_DISCOUNTVALPCTMAN 5 + 2

  #define KDAUFTRAGPOSRABKDAUFTRAGNR 0
  #define KDAUFTRAGPOSRABPOSNR 1
  #define KDAUFTRAGPOSRABDISCOUNTTYPE 2
  #define KDAUFTRAGPOSRABDISCOUNTVALUEPCT 3
  #define KDAUFTRAGPOSRABPHARMACYGROUPID 4
  #define KDAUFTRAGPOSRABPAYMENTTARGETNO 5
  #define KDAUFTRAGPOSRABDISCOUNTVALPCTMAN 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGPOSRAB_H
 #define KDAUFTRAGPOSRAB_ANZ ( sizeof(KDAUFTRAGPOSRAB_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPOSRAB ***********************************************/

 #define KDAUFTRAGPOSRAB_LISTE \
         KDAUFTRAGPOSRAB.KDAUFTRAGNR,\
         KDAUFTRAGPOSRAB.POSNR,\
         KDAUFTRAGPOSRAB.DISCOUNTTYPE,\
         KDAUFTRAGPOSRAB.DISCOUNTVALUEPCT,\
         KDAUFTRAGPOSRAB.PHARMACYGROUPID,\
         KDAUFTRAGPOSRAB.PAYMENTTARGETNO,\
         KDAUFTRAGPOSRAB.DISCOUNTVALPCTMAN

 #define KDAUFTRAGPOSRAB_LISTE_390 \
         KDAUFTRAGNR,\
         POSNR,\
         DISCOUNTTYPE,\
         DISCOUNTVALUEPCT,\
         PHARMACYGROUPID,\
         PAYMENTTARGETNO,\
         DISCOUNTVALPCTMAN

 #define KDAUFTRAGPOSRAB_PLISTE \
         "KDAUFTRAGPOSRAB.KDAUFTRAGNR,"\
         "KDAUFTRAGPOSRAB.POSNR,"\
         "KDAUFTRAGPOSRAB.DISCOUNTTYPE,"\
         "KDAUFTRAGPOSRAB.DISCOUNTVALUEPCT,"\
         "KDAUFTRAGPOSRAB.PHARMACYGROUPID,"\
         "KDAUFTRAGPOSRAB.PAYMENTTARGETNO,"\
         "KDAUFTRAGPOSRAB.DISCOUNTVALPCTMAN"

 #define KDAUFTRAGPOSRAB_PELISTE \
         "KDAUFTRAGNR,"\
         "POSNR,"\
         "DISCOUNTTYPE,"\
         "DISCOUNTVALUEPCT,"\
         "PHARMACYGROUPID,"\
         "PAYMENTTARGETNO,"\
         "DISCOUNTVALPCTMAN"

 #define KDAUFTRAGPOSRAB_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "POSNR=?,"\
         "DISCOUNTTYPE=?,"\
         "DISCOUNTVALUEPCT=?,"\
         "PHARMACYGROUPID=?,"\
         "PAYMENTTARGETNO=?,"\
         "DISCOUNTVALPCTMAN=?"

/* SqlMacros-Define of KDAUFTRAGPOSRAB ****************************************/

 #define KDAUFTRAGPOSRAB_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->DISCOUNTTYPE,\
         :x->DISCOUNTVALUEPCT,\
         :x->PHARMACYGROUPID,\
         :x->PAYMENTTARGETNO,\
         :x->DISCOUNTVALPCTMAN

 #define KDAUFTRAGPOSRAB_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->DISCOUNTTYPE,\
         :x->DISCOUNTVALUEPCT,\
         :x->PHARMACYGROUPID,\
         :x->PAYMENTTARGETNO,\
         :x->DISCOUNTVALPCTMAN

 #define KDAUFTRAGPOSRAB_UPDATE(x) \
         KDAUFTRAGPOSRAB.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGPOSRAB.POSNR=:x->POSNR,\
         KDAUFTRAGPOSRAB.DISCOUNTTYPE=:x->DISCOUNTTYPE,\
         KDAUFTRAGPOSRAB.DISCOUNTVALUEPCT=:x->DISCOUNTVALUEPCT,\
         KDAUFTRAGPOSRAB.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         KDAUFTRAGPOSRAB.PAYMENTTARGETNO=:x->PAYMENTTARGETNO,\
         KDAUFTRAGPOSRAB.DISCOUNTVALPCTMAN=:x->DISCOUNTVALPCTMAN

/* SqlMacros390-Define of KDAUFTRAGPOSRAB *************************************/

 #define KDAUFTRAGPOSRAB_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :POSNR,\
         :DISCOUNTTYPE,\
         :DISCOUNTVALUEPCT,\
         :PHARMACYGROUPID,\
         :PAYMENTTARGETNO,\
         :DISCOUNTVALPCTMAN

 #define KDAUFTRAGPOSRAB_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         POSNR=:POSNR,\
         DISCOUNTTYPE=:DISCOUNTTYPE,\
         DISCOUNTVALUEPCT=:DISCOUNTVALUEPCT,\
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         PAYMENTTARGETNO=:PAYMENTTARGETNO,\
         DISCOUNTVALPCTMAN=:DISCOUNTVALPCTMAN

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGPOSRAB ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGPOSRAB {
         long KDAUFTRAGNR;
         long POSNR;
         short DISCOUNTTYPE;
         double DISCOUNTVALUEPCT;
         char PHARMACYGROUPID[4];
         short PAYMENTTARGETNO;
         double DISCOUNTVALPCTMAN;
        } kdauftragposrabS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGPOSRAB {
         long KDAUFTRAGNR;
         long POSNR;
         short DISCOUNTTYPE;
         double DISCOUNTVALUEPCT;
         char PHARMACYGROUPID[4];
         short PAYMENTTARGETNO;
         double DISCOUNTVALPCTMAN;

			bool operator==(const N_KDAUFTRAGPOSRAB& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				POSNR == right.POSNR &&
				DISCOUNTTYPE == right.DISCOUNTTYPE &&
				DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
				!strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
				PAYMENTTARGETNO == right.PAYMENTTARGETNO &&
				DISCOUNTVALPCTMAN == right.DISCOUNTVALPCTMAN
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				POSNR = 0;
				DISCOUNTTYPE = 0;
				DISCOUNTVALUEPCT = 0;
				strcpy(PHARMACYGROUPID, " " );
				PAYMENTTARGETNO = 0;
				DISCOUNTVALPCTMAN = 0;
#endif
			}
         } kdauftragposrabS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPOSRAB ***********************************/

 struct S_KDAUFTRAGPOSRAB {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char DISCOUNTTYPE[7];
         char DISCOUNTVALUEPCT[5 + 2];
         char PHARMACYGROUPID[3 + 1];
         char PAYMENTTARGETNO[7];
         char DISCOUNTVALPCTMAN[5 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPOSRAB ******************/

 struct O_KDAUFTRAGPOSRAB {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char DISCOUNTTYPE[7];
         char DISCOUNTVALUEPCT[5];
         char PHARMACYGROUPID[3];
         char PAYMENTTARGETNO[7];
         char DISCOUNTVALPCTMAN[5];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPOSRAB *****************************/

 struct C_KDAUFTRAGPOSRAB {
         long KDAUFTRAGNR;
         long POSNR;
         short DISCOUNTTYPE;
         double DISCOUNTVALUEPCT;
         char PHARMACYGROUPID[4];
         short PAYMENTTARGETNO;
         double DISCOUNTVALPCTMAN;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPOSRAB ***************************/

 struct I_KDAUFTRAGPOSRAB {
         short KDAUFTRAGNR;
         short POSNR;
         short DISCOUNTTYPE;
         short DISCOUNTVALUEPCT;
         short PHARMACYGROUPID;
         short PAYMENTTARGETNO;
         short DISCOUNTVALPCTMAN;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPOSRAB *************************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSRAB_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSRAB_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
 };
#endif

/* description for datatypes of KDAUFTRAGPOSRAB *******************************/

 #define KDAUFTRAGPOSRAB_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         short DISCOUNTTYPE; \
         double DISCOUNTVALUEPCT; \
         char PHARMACYGROUPID[4]; \
         short PAYMENTTARGETNO; \
         double DISCOUNTVALPCTMAN; \



/* Copy-Function Struct to single Data KDAUFTRAGPOSRAB ************************/

 #define KDAUFTRAGPOSRAB_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         DISCOUNTTYPE=_x_->DISCOUNTTYPE;\
         DISCOUNTVALUEPCT=_x_->DISCOUNTVALUEPCT;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         PAYMENTTARGETNO=_x_->PAYMENTTARGETNO;\
         DISCOUNTVALPCTMAN=_x_->DISCOUNTVALPCTMAN;\

 #define KDAUFTRAGPOSRAB_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->DISCOUNTTYPE=DISCOUNTTYPE;\
          _x_->DISCOUNTVALUEPCT=DISCOUNTVALUEPCT;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->PAYMENTTARGETNO=PAYMENTTARGETNO;\
          _x_->DISCOUNTVALPCTMAN=DISCOUNTVALPCTMAN;\



/* FunctionNumber-Define of kdauftragposrab ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragposrab *******************************/


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

class CKDAUFTRAGPOSRAB : public ppDadeVirtual
{
	//data members
	public:
		kdauftragposrabS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kdauftragposrabS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragposrabS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kdauftragposrabS>; Strip(s); kdauftragposrabS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragposrabS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kdauftragposrabS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kdauftragposrabS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		long		GetPosnr() const	{ return s.POSNR; }
		short		GetDiscounttype() const	{ return s.DISCOUNTTYPE; }
		double		GetDiscountvaluepct() const	{ return s.DISCOUNTVALUEPCT; }
		const char*	GetPharmacygroupid(ppString& t) const 	{ t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
		short		GetPaymenttargetno() const	{ return s.PAYMENTTARGETNO; }
		double		GetDiscountvalpctman() const	{ return s.DISCOUNTVALPCTMAN; }
		const kdauftragposrabS& GetStruct() const { return s; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetPosnr(long t) { s.POSNR = t; }
		void 		SetDiscounttype(short t) { s.DISCOUNTTYPE = t; }
		void 		SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
		void 		SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_KDAUFTRAGPOSRAB_PHARMACYGROUPID); }
		void 		SetPaymenttargetno(short t) { s.PAYMENTTARGETNO = t; }
		void 		SetDiscountvalpctman(double t) { s.DISCOUNTVALPCTMAN = t; }
		void 		SetStruct(const kdauftragposrabS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CKDAUFTRAGPOSRAB()  //constructor
		{
			::buf_default((void *)&s, KDAUFTRAGPOSRAB_BES, KDAUFTRAGPOSRAB_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CKDAUFTRAGPOSRAB()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KDAUFTRAGPOSRAB_BES, KDAUFTRAGPOSRAB_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPOSRAB_BES, KDAUFTRAGPOSRAB_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPOSRAB_BES, KDAUFTRAGPOSRAB_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_KDAUFTRAGPOSRAB& d)
		{
#ifdef WIN32
			ppGStripLast(d.PHARMACYGROUPID);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPOSRAB_BES, KDAUFTRAGPOSRAB_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KDAUFTRAGPOSRAB **************************************/

 #define KDAUFTRAGPOSRAB_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         DISCOUNTTYPE smallint default 0 not null,\
         DISCOUNTVALUEPCT decimal(5,2) default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         PAYMENTTARGETNO smallint default 0 not null,\
         DISCOUNTVALPCTMAN decimal(5,2) default 0 not null) in ksc extent size 784 next size 80 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPOSRAB ************************************/

 #define KDAUFTRAGPOSRAB_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdaufposrab_1 on _X_(\
              kdauftragnr,\
              posnr,\
              DiscountType,\
              paymenttargetno ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPOSRAB ************************************/

 #define KDAUFTRAGPOSRAB_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdaufposrab_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

#ifndef __PP_CSTCALCAVP_H_
#define __PP_CSTCALCAVP_H_

/******************************************************************************/
/* d:\prj\AS\pxdb\include\CstCalcAvp ******************************************/
/******************************************************************************/

/* Length-Define of CSTCALCAVP ************************************************/

  #define L_CSTCALCAVP_BRANCHNO 6
  #define L_CSTCALCAVP_CUSTOMERNO 11
  #define L_CSTCALCAVP_ABDACODE 5
  #define L_CSTCALCAVP_SURCHARGE_BASIC 6
  #define L_CSTCALCAVP_DEDUCTION_BASIC 6
  #define L_CSTCALCAVP_SURCHARGEPCT 5
  #define N_CSTCALCAVP_SURCHARGEPCT 2
  #define L_CSTCALCAVP_DEDUCTIONPCT 5
  #define N_CSTCALCAVP_DEDUCTIONPCT 2
  #define L_CSTCALCAVP_PRICE_GROUP 6
  #define L_CSTCALCAVP_PREIS_TYP 6

/* Length/Count-Define of CSTCALCAVP ******************************************/

  #define LS_CSTCALCAVP_BRANCHNO 5 + 1
  #define LS_CSTCALCAVP_CUSTOMERNO 10 + 1
  #define LS_CSTCALCAVP_ABDACODE 5 + 1
  #define LS_CSTCALCAVP_SURCHARGE_BASIC 5 + 1
  #define LS_CSTCALCAVP_DEDUCTION_BASIC 5 + 1
  #define LS_CSTCALCAVP_SURCHARGEPCT 5 + 2
  #define LS_CSTCALCAVP_DEDUCTIONPCT 5 + 2
  #define LS_CSTCALCAVP_PRICE_GROUP 5 + 1
  #define LS_CSTCALCAVP_PREIS_TYP 5 + 1

  #define CSTCALCAVPBRANCHNO 0
  #define CSTCALCAVPCUSTOMERNO 1
  #define CSTCALCAVPABDACODE 2
  #define CSTCALCAVPSURCHARGE_BASIC 3
  #define CSTCALCAVPDEDUCTION_BASIC 4
  #define CSTCALCAVPSURCHARGEPCT 5
  #define CSTCALCAVPDEDUCTIONPCT 6
  #define CSTCALCAVPPRICE_GROUP 7
  #define CSTCALCAVPPREIS_TYP 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CSTCALCAVP_H
 #define CSTCALCAVP_ANZ ( sizeof(CSTCALCAVP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSTCALCAVP ****************************************************/

 #define CSTCALCAVP_LISTE \
         CSTCALCAVP.BRANCHNO,\
         CSTCALCAVP.CUSTOMERNO,\
         CSTCALCAVP.ABDACODE,\
         CSTCALCAVP.SURCHARGE_BASIC,\
         CSTCALCAVP.DEDUCTION_BASIC,\
         CSTCALCAVP.SURCHARGEPCT,\
         CSTCALCAVP.DEDUCTIONPCT,\
         CSTCALCAVP.PRICE_GROUP,\
         CSTCALCAVP.PREIS_TYP

 #define CSTCALCAVP_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         ABDACODE,\
         SURCHARGE_BASIC,\
         DEDUCTION_BASIC,\
         SURCHARGEPCT,\
         DEDUCTIONPCT,\
         PRICE_GROUP,\
         PREIS_TYP

 #define CSTCALCAVP_PLISTE \
         "CSTCALCAVP.BRANCHNO,"\
         "CSTCALCAVP.CUSTOMERNO,"\
         "CSTCALCAVP.ABDACODE,"\
         "CSTCALCAVP.SURCHARGE_BASIC,"\
         "CSTCALCAVP.DEDUCTION_BASIC,"\
         "CSTCALCAVP.SURCHARGEPCT,"\
         "CSTCALCAVP.DEDUCTIONPCT,"\
         "CSTCALCAVP.PRICE_GROUP,"\
         "CSTCALCAVP.PREIS_TYP"

 #define CSTCALCAVP_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "ABDACODE,"\
         "SURCHARGE_BASIC,"\
         "DEDUCTION_BASIC,"\
         "SURCHARGEPCT,"\
         "DEDUCTIONPCT,"\
         "PRICE_GROUP,"\
         "PREIS_TYP"

 #define CSTCALCAVP_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "ABDACODE=?,"\
         "SURCHARGE_BASIC=?,"\
         "DEDUCTION_BASIC=?,"\
         "SURCHARGEPCT=?,"\
         "DEDUCTIONPCT=?,"\
         "PRICE_GROUP=?,"\
         "PREIS_TYP=?"

/* SqlMacros-Define of CSTCALCAVP *********************************************/

 #define CSTCALCAVP_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ABDACODE,\
         :x->SURCHARGE_BASIC,\
         :x->DEDUCTION_BASIC,\
         :x->SURCHARGEPCT,\
         :x->DEDUCTIONPCT,\
         :x->PRICE_GROUP,\
         :x->PREIS_TYP

 #define CSTCALCAVP_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ABDACODE,\
         :x->SURCHARGE_BASIC,\
         :x->DEDUCTION_BASIC,\
         :x->SURCHARGEPCT,\
         :x->DEDUCTIONPCT,\
         :x->PRICE_GROUP,\
         :x->PREIS_TYP

 #define CSTCALCAVP_UPDATE(x) \
         CSTCALCAVP.BRANCHNO=:x->BRANCHNO,\
         CSTCALCAVP.CUSTOMERNO=:x->CUSTOMERNO,\
         CSTCALCAVP.ABDACODE=:x->ABDACODE,\
         CSTCALCAVP.SURCHARGE_BASIC=:x->SURCHARGE_BASIC,\
         CSTCALCAVP.DEDUCTION_BASIC=:x->DEDUCTION_BASIC,\
         CSTCALCAVP.SURCHARGEPCT=:x->SURCHARGEPCT,\
         CSTCALCAVP.DEDUCTIONPCT=:x->DEDUCTIONPCT,\
         CSTCALCAVP.PRICE_GROUP=:x->PRICE_GROUP,\
         CSTCALCAVP.PREIS_TYP=:x->PREIS_TYP

/* SqlMacros390-Define of CSTCALCAVP ******************************************/

 #define CSTCALCAVP_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :ABDACODE,\
         :SURCHARGE_BASIC,\
         :DEDUCTION_BASIC,\
         :SURCHARGEPCT,\
         :DEDUCTIONPCT,\
         :PRICE_GROUP,\
         :PREIS_TYP

 #define CSTCALCAVP_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         ABDACODE=:ABDACODE,\
         SURCHARGE_BASIC=:SURCHARGE_BASIC,\
         DEDUCTION_BASIC=:DEDUCTION_BASIC,\
         SURCHARGEPCT=:SURCHARGEPCT,\
         DEDUCTIONPCT=:DEDUCTIONPCT,\
         PRICE_GROUP=:PRICE_GROUP,\
         PREIS_TYP=:PREIS_TYP

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CSTCALCAVP *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_CSTCALCAVP {
         short BRANCHNO;
         long CUSTOMERNO;
         char ABDACODE[6];
         short SURCHARGE_BASIC;
         short DEDUCTION_BASIC;
         double SURCHARGEPCT;
         double DEDUCTIONPCT;
         short PRICE_GROUP;
         short PREIS_TYP;
        } cstcalcavpS;
 #else /*TRANSCLASS*/
 typedef struct N_CSTCALCAVP {
         short BRANCHNO;
         long CUSTOMERNO;
         char ABDACODE[6];
         short SURCHARGE_BASIC;
         short DEDUCTION_BASIC;
         double SURCHARGEPCT;
         double DEDUCTIONPCT;
         short PRICE_GROUP;
         short PREIS_TYP;

			bool operator==(const N_CSTCALCAVP& right) const {
			return(
				BRANCHNO == right.BRANCHNO &&
				CUSTOMERNO == right.CUSTOMERNO &&
				!strcmp(ABDACODE, right.ABDACODE) &&
				SURCHARGE_BASIC == right.SURCHARGE_BASIC &&
				DEDUCTION_BASIC == right.DEDUCTION_BASIC &&
				SURCHARGEPCT == right.SURCHARGEPCT &&
				DEDUCTIONPCT == right.DEDUCTIONPCT &&
				PRICE_GROUP == right.PRICE_GROUP &&
				PREIS_TYP == right.PREIS_TYP
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				BRANCHNO = 0;
				CUSTOMERNO = 0;
				strcpy(ABDACODE, " " );
				SURCHARGE_BASIC = 0;
				DEDUCTION_BASIC = 0;
				SURCHARGEPCT = 0;
				DEDUCTIONPCT = 0;
				PRICE_GROUP = 0;
				PREIS_TYP = 0;
#endif
			}
         } cstcalcavpS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSTCALCAVP ****************************************/

 struct S_CSTCALCAVP {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ABDACODE[5 + 1];
         char SURCHARGE_BASIC[7];
         char DEDUCTION_BASIC[7];
         char SURCHARGEPCT[5 + 2];
         char DEDUCTIONPCT[5 + 2];
         char PRICE_GROUP[7];
         char PREIS_TYP[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSTCALCAVP ***********************/

 struct O_CSTCALCAVP {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ABDACODE[5];
         char SURCHARGE_BASIC[7];
         char DEDUCTION_BASIC[7];
         char SURCHARGEPCT[5];
         char DEDUCTIONPCT[5];
         char PRICE_GROUP[7];
         char PREIS_TYP[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSTCALCAVP **********************************/

 struct C_CSTCALCAVP {
         short BRANCHNO;
         long CUSTOMERNO;
         char ABDACODE[6];
         short SURCHARGE_BASIC;
         short DEDUCTION_BASIC;
         double SURCHARGEPCT;
         double DEDUCTIONPCT;
         short PRICE_GROUP;
         short PREIS_TYP;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSTCALCAVP ********************************/

 struct I_CSTCALCAVP {
         short BRANCHNO;
         short CUSTOMERNO;
         short ABDACODE;
         short SURCHARGE_BASIC;
         short DEDUCTION_BASIC;
         short SURCHARGEPCT;
         short DEDUCTIONPCT;
         short PRICE_GROUP;
         short PREIS_TYP;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSTCALCAVP ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc CSTCALCAVP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 5, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CSTCALCAVP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 5, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of CSTCALCAVP ************************************/

 #define CSTCALCAVP_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         char ABDACODE[6]; \
         short SURCHARGE_BASIC; \
         short DEDUCTION_BASIC; \
         double SURCHARGEPCT; \
         double DEDUCTIONPCT; \
         short PRICE_GROUP; \
         short PREIS_TYP; \



/* Copy-Function Struct to single Data CSTCALCAVP *****************************/

 #define CSTCALCAVP_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
          strcpy(ABDACODE,_x_->ABDACODE);\
         SURCHARGE_BASIC=_x_->SURCHARGE_BASIC;\
         DEDUCTION_BASIC=_x_->DEDUCTION_BASIC;\
         SURCHARGEPCT=_x_->SURCHARGEPCT;\
         DEDUCTIONPCT=_x_->DEDUCTIONPCT;\
         PRICE_GROUP=_x_->PRICE_GROUP;\
         PREIS_TYP=_x_->PREIS_TYP;\

 #define CSTCALCAVP_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          strcpy(_x_->ABDACODE,ABDACODE);\
          _x_->SURCHARGE_BASIC=SURCHARGE_BASIC;\
          _x_->DEDUCTION_BASIC=DEDUCTION_BASIC;\
          _x_->SURCHARGEPCT=SURCHARGEPCT;\
          _x_->DEDUCTIONPCT=DEDUCTIONPCT;\
          _x_->PRICE_GROUP=PRICE_GROUP;\
          _x_->PREIS_TYP=PREIS_TYP;\



/* FunctionNumber-Define of CstCalcAvp ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CstCalcAvp ************************************/


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

class CCSTCALCAVP : public ppDadeVirtual
{
	//data members
	public:
		cstcalcavpS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<cstcalcavpS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstcalcavpS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<cstcalcavpS>; Strip(s); cstcalcavpS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstcalcavpS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<cstcalcavpS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<cstcalcavpS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetBranchno() const	{ return s.BRANCHNO; }
		long		GetCustomerno() const	{ return s.CUSTOMERNO; }
		const char*	GetAbdacode(ppString& t) const 	{ t = s.ABDACODE; t.erasespace(ppString::END); return t.c_str(); }
		short		GetSurcharge_basic() const	{ return s.SURCHARGE_BASIC; }
		short		GetDeduction_basic() const	{ return s.DEDUCTION_BASIC; }
		double		GetSurchargepct() const	{ return s.SURCHARGEPCT; }
		double		GetDeductionpct() const	{ return s.DEDUCTIONPCT; }
		short		GetPrice_group() const	{ return s.PRICE_GROUP; }
		short		GetPreis_typ() const	{ return s.PREIS_TYP; }
		const cstcalcavpS& GetStruct() const { return s; }
		void 		SetBranchno(short t) { s.BRANCHNO = t; }
		void 		SetCustomerno(long t) { s.CUSTOMERNO = t; }
		void 		SetAbdacode(const ppString& t) { ppGStrCopy(s.ABDACODE,t.c_str() ,L_CSTCALCAVP_ABDACODE); }
		void 		SetSurcharge_basic(short t) { s.SURCHARGE_BASIC = t; }
		void 		SetDeduction_basic(short t) { s.DEDUCTION_BASIC = t; }
		void 		SetSurchargepct(double t) { s.SURCHARGEPCT = t; }
		void 		SetDeductionpct(double t) { s.DEDUCTIONPCT = t; }
		void 		SetPrice_group(short t) { s.PRICE_GROUP = t; }
		void 		SetPreis_typ(short t) { s.PREIS_TYP = t; }
		void 		SetStruct(const cstcalcavpS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CCSTCALCAVP()  //constructor
		{
			::buf_default((void *)&s, CSTCALCAVP_BES, CSTCALCAVP_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CCSTCALCAVP()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, CSTCALCAVP_BES, CSTCALCAVP_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSTCALCAVP_BES, CSTCALCAVP_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, CSTCALCAVP_BES, CSTCALCAVP_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_CSTCALCAVP& d)
		{
#ifdef WIN32
			ppGStripLast(d.ABDACODE);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, CSTCALCAVP_BES, CSTCALCAVP_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of CSTCALCAVP *******************************************/

 #define CSTCALCAVP_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ABDACODE char(5) default " " not null,\
         SURCHARGE_BASIC smallint default 0 not null,\
         DEDUCTION_BASIC smallint default 0 not null,\
         SURCHARGEPCT decimal(5,2) default 0 not null,\
         DEDUCTIONPCT decimal(5,2) default 0 not null,\
         PRICE_GROUP smallint default 0 not null,\
         PREIS_TYP smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CSTCALCAVP *****************************************/

 #define CSTCALCAVP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_CstCalcAVP_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              price_group,\
              preis_typ,\
              abdacode ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSTCALCAVP *****************************************/

 #define CSTCALCAVP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_CstCalcAVP_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

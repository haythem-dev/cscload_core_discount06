#ifndef __PP_KDAUFTRPOSRECHART_H_
#define __PP_KDAUFTRPOSRECHART_H_

/******************************************************************************/
/* c:\temp\kdauftrposrechart **************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRPOSRECHART *****************************************/

  #define L_KDAUFTRPOSRECHART_KDAUFTRAGNR 11
  #define L_KDAUFTRPOSRECHART_POSNR 11
  #define L_KDAUFTRPOSRECHART_SURCHARGEPCT 5
  #define N_KDAUFTRPOSRECHART_SURCHARGEPCT 2
  #define L_KDAUFTRPOSRECHART_DEDUCTIONPCT 5
  #define N_KDAUFTRPOSRECHART_DEDUCTIONPCT 2
  #define L_KDAUFTRPOSRECHART_SURCHARGE_CALC 10
  #define N_KDAUFTRPOSRECHART_SURCHARGE_CALC 3
  #define L_KDAUFTRPOSRECHART_CALCAVP 9
  #define N_KDAUFTRPOSRECHART_CALCAVP 2
  #define L_KDAUFTRPOSRECHART_SURCHARGE_CALC_DIS 10
  #define N_KDAUFTRPOSRECHART_SURCHARGE_CALC_DIS 3
  #define L_KDAUFTRPOSRECHART_CALCAVP_DIS 9
  #define N_KDAUFTRPOSRECHART_CALCAVP_DIS 2

/* Length/Count-Define of KDAUFTRPOSRECHART ***********************************/

  #define LS_KDAUFTRPOSRECHART_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRPOSRECHART_POSNR 10 + 1
  #define LS_KDAUFTRPOSRECHART_SURCHARGEPCT 5 + 2
  #define LS_KDAUFTRPOSRECHART_DEDUCTIONPCT 5 + 2
  #define LS_KDAUFTRPOSRECHART_SURCHARGE_CALC 10 + 2
  #define LS_KDAUFTRPOSRECHART_CALCAVP 9 + 2
  #define LS_KDAUFTRPOSRECHART_SURCHARGE_CALC_DIS 10 + 2
  #define LS_KDAUFTRPOSRECHART_CALCAVP_DIS 9 + 2

  #define KDAUFTRPOSRECHARTKDAUFTRAGNR 0
  #define KDAUFTRPOSRECHARTPOSNR 1
  #define KDAUFTRPOSRECHARTSURCHARGEPCT 2
  #define KDAUFTRPOSRECHARTDEDUCTIONPCT 3
  #define KDAUFTRPOSRECHARTSURCHARGE_CALC 4
  #define KDAUFTRPOSRECHARTCALCAVP 5
  #define KDAUFTRPOSRECHARTSURCHARGE_CALC_DIS 6
  #define KDAUFTRPOSRECHARTCALCAVP_DIS 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRPOSRECHART_H
 #define KDAUFTRPOSRECHART_ANZ ( sizeof(KDAUFTRPOSRECHART_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRPOSRECHART *********************************************/

 #define KDAUFTRPOSRECHART_LISTE \
         KDAUFTRPOSRECHART.KDAUFTRAGNR,\
         KDAUFTRPOSRECHART.POSNR,\
         KDAUFTRPOSRECHART.SURCHARGEPCT,\
         KDAUFTRPOSRECHART.DEDUCTIONPCT,\
         KDAUFTRPOSRECHART.SURCHARGE_CALC,\
         KDAUFTRPOSRECHART.CALCAVP,\
         KDAUFTRPOSRECHART.SURCHARGE_CALC_DIS,\
         KDAUFTRPOSRECHART.CALCAVP_DIS

 #define KDAUFTRPOSRECHART_LISTE_390 \
         KDAUFTRAGNR,\
         POSNR,\
         SURCHARGEPCT,\
         DEDUCTIONPCT,\
         SURCHARGE_CALC,\
         CALCAVP,\
         SURCHARGE_CALC_DIS,\
         CALCAVP_DIS

 #define KDAUFTRPOSRECHART_PLISTE \
         "KDAUFTRPOSRECHART.KDAUFTRAGNR,"\
         "KDAUFTRPOSRECHART.POSNR,"\
         "KDAUFTRPOSRECHART.SURCHARGEPCT,"\
         "KDAUFTRPOSRECHART.DEDUCTIONPCT,"\
         "KDAUFTRPOSRECHART.SURCHARGE_CALC,"\
         "KDAUFTRPOSRECHART.CALCAVP,"\
         "KDAUFTRPOSRECHART.SURCHARGE_CALC_DIS,"\
         "KDAUFTRPOSRECHART.CALCAVP_DIS"

 #define KDAUFTRPOSRECHART_PELISTE \
         "KDAUFTRAGNR,"\
         "POSNR,"\
         "SURCHARGEPCT,"\
         "DEDUCTIONPCT,"\
         "SURCHARGE_CALC,"\
         "CALCAVP,"\
         "SURCHARGE_CALC_DIS,"\
         "CALCAVP_DIS"

 #define KDAUFTRPOSRECHART_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "POSNR=?,"\
         "SURCHARGEPCT=?,"\
         "DEDUCTIONPCT=?,"\
         "SURCHARGE_CALC=?,"\
         "CALCAVP=?,"\
         "SURCHARGE_CALC_DIS=?,"\
         "CALCAVP_DIS=?"

/* SqlMacros-Define of KDAUFTRPOSRECHART **************************************/

 #define KDAUFTRPOSRECHART_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->SURCHARGEPCT,\
         :x->DEDUCTIONPCT,\
         :x->SURCHARGE_CALC,\
         :x->CALCAVP,\
         :x->SURCHARGE_CALC_DIS,\
         :x->CALCAVP_DIS

 #define KDAUFTRPOSRECHART_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->SURCHARGEPCT,\
         :x->DEDUCTIONPCT,\
         :x->SURCHARGE_CALC,\
         :x->CALCAVP,\
         :x->SURCHARGE_CALC_DIS,\
         :x->CALCAVP_DIS

 #define KDAUFTRPOSRECHART_UPDATE(x) \
         KDAUFTRPOSRECHART.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRPOSRECHART.POSNR=:x->POSNR,\
         KDAUFTRPOSRECHART.SURCHARGEPCT=:x->SURCHARGEPCT,\
         KDAUFTRPOSRECHART.DEDUCTIONPCT=:x->DEDUCTIONPCT,\
         KDAUFTRPOSRECHART.SURCHARGE_CALC=:x->SURCHARGE_CALC,\
         KDAUFTRPOSRECHART.CALCAVP=:x->CALCAVP,\
         KDAUFTRPOSRECHART.SURCHARGE_CALC_DIS=:x->SURCHARGE_CALC_DIS,\
         KDAUFTRPOSRECHART.CALCAVP_DIS=:x->CALCAVP_DIS

/* SqlMacros390-Define of KDAUFTRPOSRECHART ***********************************/

 #define KDAUFTRPOSRECHART_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :POSNR,\
         :SURCHARGEPCT,\
         :DEDUCTIONPCT,\
         :SURCHARGE_CALC,\
         :CALCAVP,\
         :SURCHARGE_CALC_DIS,\
         :CALCAVP_DIS

 #define KDAUFTRPOSRECHART_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         POSNR=:POSNR,\
         SURCHARGEPCT=:SURCHARGEPCT,\
         DEDUCTIONPCT=:DEDUCTIONPCT,\
         SURCHARGE_CALC=:SURCHARGE_CALC,\
         CALCAVP=:CALCAVP,\
         SURCHARGE_CALC_DIS=:SURCHARGE_CALC_DIS,\
         CALCAVP_DIS=:CALCAVP_DIS

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRPOSRECHART **************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRPOSRECHART {
         long KDAUFTRAGNR;
         long POSNR;
         double SURCHARGEPCT;
         double DEDUCTIONPCT;
         double SURCHARGE_CALC;
         double CALCAVP;
         double SURCHARGE_CALC_DIS;
         double CALCAVP_DIS;
        } kdauftrposrechartS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRPOSRECHART {
         long KDAUFTRAGNR;
         long POSNR;
         double SURCHARGEPCT;
         double DEDUCTIONPCT;
         double SURCHARGE_CALC;
         double CALCAVP;
         double SURCHARGE_CALC_DIS;
         double CALCAVP_DIS;

			bool operator==(const N_KDAUFTRPOSRECHART& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				POSNR == right.POSNR &&
				SURCHARGEPCT == right.SURCHARGEPCT &&
				DEDUCTIONPCT == right.DEDUCTIONPCT &&
				SURCHARGE_CALC == right.SURCHARGE_CALC &&
				CALCAVP == right.CALCAVP &&
				SURCHARGE_CALC_DIS == right.SURCHARGE_CALC_DIS &&
				CALCAVP_DIS == right.CALCAVP_DIS
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				POSNR = 0;
				SURCHARGEPCT = 0;
				DEDUCTIONPCT = 0;
				SURCHARGE_CALC = 0;
				CALCAVP = 0;
				SURCHARGE_CALC_DIS = 0;
				CALCAVP_DIS = 0;
#endif
			}
         } kdauftrposrechartS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRPOSRECHART *********************************/

 struct S_KDAUFTRPOSRECHART {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char SURCHARGEPCT[5 + 2];
         char DEDUCTIONPCT[5 + 2];
         char SURCHARGE_CALC[10 + 2];
         char CALCAVP[9 + 2];
         char SURCHARGE_CALC_DIS[10 + 2];
         char CALCAVP_DIS[9 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRPOSRECHART ****************/

 struct O_KDAUFTRPOSRECHART {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char SURCHARGEPCT[5];
         char DEDUCTIONPCT[5];
         char SURCHARGE_CALC[10];
         char CALCAVP[9];
         char SURCHARGE_CALC_DIS[10];
         char CALCAVP_DIS[9];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRPOSRECHART ***************************/

 struct C_KDAUFTRPOSRECHART {
         long KDAUFTRAGNR;
         long POSNR;
         double SURCHARGEPCT;
         double DEDUCTIONPCT;
         double SURCHARGE_CALC;
         double CALCAVP;
         double SURCHARGE_CALC_DIS;
         double CALCAVP_DIS;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRPOSRECHART *************************/

 struct I_KDAUFTRPOSRECHART {
         short KDAUFTRAGNR;
         short POSNR;
         short SURCHARGEPCT;
         short DEDUCTIONPCT;
         short SURCHARGE_CALC;
         short CALCAVP;
         short SURCHARGE_CALC_DIS;
         short CALCAVP_DIS;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRPOSRECHART ***********************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRPOSRECHART_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 10, 3 },
   { TYP_D, 9, 2 },
   { TYP_D, 10, 3 },
   { TYP_D, 9, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRPOSRECHART_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 10, 3 },
   { TYP_D, 9, 2 },
   { TYP_D, 10, 3 },
   { TYP_D, 9, 2 },
 };
#endif

/* description for datatypes of KDAUFTRPOSRECHART *****************************/

 #define KDAUFTRPOSRECHART_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         double SURCHARGEPCT; \
         double DEDUCTIONPCT; \
         double SURCHARGE_CALC; \
         double CALCAVP; \
         double SURCHARGE_CALC_DIS; \
         double CALCAVP_DIS; \



/* Copy-Function Struct to single Data KDAUFTRPOSRECHART **********************/

 #define KDAUFTRPOSRECHART_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         SURCHARGEPCT=_x_->SURCHARGEPCT;\
         DEDUCTIONPCT=_x_->DEDUCTIONPCT;\
         SURCHARGE_CALC=_x_->SURCHARGE_CALC;\
         CALCAVP=_x_->CALCAVP;\
         SURCHARGE_CALC_DIS=_x_->SURCHARGE_CALC_DIS;\
         CALCAVP_DIS=_x_->CALCAVP_DIS;\

 #define KDAUFTRPOSRECHART_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->SURCHARGEPCT=SURCHARGEPCT;\
          _x_->DEDUCTIONPCT=DEDUCTIONPCT;\
          _x_->SURCHARGE_CALC=SURCHARGE_CALC;\
          _x_->CALCAVP=CALCAVP;\
          _x_->SURCHARGE_CALC_DIS=SURCHARGE_CALC_DIS;\
          _x_->CALCAVP_DIS=CALCAVP_DIS;\



/* FunctionNumber-Define of kdauftrposrechart *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftrposrechart *****************************/


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

class CKDAUFTRPOSRECHART : public ppDadeVirtual
{
	//data members
	public:
		kdauftrposrechartS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kdauftrposrechartS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftrposrechartS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kdauftrposrechartS>; Strip(s); kdauftrposrechartS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftrposrechartS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kdauftrposrechartS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kdauftrposrechartS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		long		GetPosnr() const	{ return s.POSNR; }
		double		GetSurchargepct() const	{ return s.SURCHARGEPCT; }
		double		GetDeductionpct() const	{ return s.DEDUCTIONPCT; }
		double		GetSurcharge_calc() const	{ return s.SURCHARGE_CALC; }
		double		GetCalcavp() const	{ return s.CALCAVP; }
		double		GetSurcharge_calc_dis() const	{ return s.SURCHARGE_CALC_DIS; }
		double		GetCalcavp_dis() const	{ return s.CALCAVP_DIS; }
		const kdauftrposrechartS& GetStruct() const { return s; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetPosnr(long t) { s.POSNR = t; }
		void 		SetSurchargepct(double t) { s.SURCHARGEPCT = t; }
		void 		SetDeductionpct(double t) { s.DEDUCTIONPCT = t; }
		void 		SetSurcharge_calc(double t) { s.SURCHARGE_CALC = t; }
		void 		SetCalcavp(double t) { s.CALCAVP = t; }
		void 		SetSurcharge_calc_dis(double t) { s.SURCHARGE_CALC_DIS = t; }
		void 		SetCalcavp_dis(double t) { s.CALCAVP_DIS = t; }
		void 		SetStruct(const kdauftrposrechartS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CKDAUFTRPOSRECHART()  //constructor
		{
			::buf_default((void *)&s, KDAUFTRPOSRECHART_BES, KDAUFTRPOSRECHART_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CKDAUFTRPOSRECHART()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KDAUFTRPOSRECHART_BES, KDAUFTRPOSRECHART_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRPOSRECHART_BES, KDAUFTRPOSRECHART_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, KDAUFTRPOSRECHART_BES, KDAUFTRPOSRECHART_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_KDAUFTRPOSRECHART& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRPOSRECHART_BES, KDAUFTRPOSRECHART_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KDAUFTRPOSRECHART ************************************/

 #define KDAUFTRPOSRECHART_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         SURCHARGEPCT decimal(5,2) default 0 not null,\
         DEDUCTIONPCT decimal(5,2) default 0 not null,\
         SURCHARGE_CALC decimal(10,3) default 0 not null,\
         CALCAVP decimal(9,2) default 0 not null,\
         SURCHARGE_CALC_DIS decimal(10,3) default 0 not null,\
         CALCAVP_DIS decimal(9,2) default 0 not null) in ksc extent size 940 next size 96 lock mode row;



/* CreateIndexStatement of KDAUFTRPOSRECHART **********************************/

 #define KDAUFTRPOSRECHART_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdaufprechart_1 on _X_(\
              kdauftragnr,\
              posnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRPOSRECHART **********************************/

 #define KDAUFTRPOSRECHART_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdaufprechart_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

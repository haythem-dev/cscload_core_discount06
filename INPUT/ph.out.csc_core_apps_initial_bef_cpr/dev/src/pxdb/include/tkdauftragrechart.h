#ifndef __PP_KDAUFTRAGRECHART_H_
#define __PP_KDAUFTRAGRECHART_H_

/******************************************************************************/
/* c:\temp3\kdauftragrechart **************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGRECHART ******************************************/

  #define L_KDAUFTRAGRECHART_PRINT 6
  #define L_KDAUFTRAGRECHART_DEDUCTION_AEP 6
  #define L_KDAUFTRAGRECHART_DEDUCTION_AVP 6
  #define L_KDAUFTRAGRECHART_WITHCOLUMNNR 6
  #define L_KDAUFTRAGRECHART_BYEMAIL 6
  #define L_KDAUFTRAGRECHART_KDAUFTRAGNR 11

/* Length/Count-Define of KDAUFTRAGRECHART ************************************/

  #define LS_KDAUFTRAGRECHART_PRINT 5 + 1
  #define LS_KDAUFTRAGRECHART_DEDUCTION_AEP 5 + 1
  #define LS_KDAUFTRAGRECHART_DEDUCTION_AVP 5 + 1
  #define LS_KDAUFTRAGRECHART_WITHCOLUMNNR 5 + 1
  #define LS_KDAUFTRAGRECHART_BYEMAIL 5 + 1
  #define LS_KDAUFTRAGRECHART_KDAUFTRAGNR 10 + 1

  #define KDAUFTRAGRECHARTPRINT 0
  #define KDAUFTRAGRECHARTDEDUCTION_AEP 1
  #define KDAUFTRAGRECHARTDEDUCTION_AVP 2
  #define KDAUFTRAGRECHARTWITHCOLUMNNR 3
  #define KDAUFTRAGRECHARTBYEMAIL 4
  #define KDAUFTRAGRECHARTKDAUFTRAGNR 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGRECHART_H
 #define KDAUFTRAGRECHART_ANZ ( sizeof(KDAUFTRAGRECHART_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGRECHART **********************************************/

 #define KDAUFTRAGRECHART_LISTE \
         KDAUFTRAGRECHART.PRINT,\
         KDAUFTRAGRECHART.DEDUCTION_AEP,\
         KDAUFTRAGRECHART.DEDUCTION_AVP,\
         KDAUFTRAGRECHART.WITHCOLUMNNR,\
         KDAUFTRAGRECHART.BYEMAIL,\
         KDAUFTRAGRECHART.KDAUFTRAGNR

 #define KDAUFTRAGRECHART_LISTE_390 \
         PRINT,\
         DEDUCTION_AEP,\
         DEDUCTION_AVP,\
         WITHCOLUMNNR,\
         BYEMAIL,\
         KDAUFTRAGNR

 #define KDAUFTRAGRECHART_PLISTE \
         "KDAUFTRAGRECHART.PRINT,"\
         "KDAUFTRAGRECHART.DEDUCTION_AEP,"\
         "KDAUFTRAGRECHART.DEDUCTION_AVP,"\
         "KDAUFTRAGRECHART.WITHCOLUMNNR,"\
         "KDAUFTRAGRECHART.BYEMAIL,"\
         "KDAUFTRAGRECHART.KDAUFTRAGNR"

 #define KDAUFTRAGRECHART_PELISTE \
         "PRINT,"\
         "DEDUCTION_AEP,"\
         "DEDUCTION_AVP,"\
         "WITHCOLUMNNR,"\
         "BYEMAIL,"\
         "KDAUFTRAGNR"

 #define KDAUFTRAGRECHART_UPDLISTE \
         "PRINT=?,"\
         "DEDUCTION_AEP=?,"\
         "DEDUCTION_AVP=?,"\
         "WITHCOLUMNNR=?,"\
         "BYEMAIL=?,"\
         "KDAUFTRAGNR=?"

/* SqlMacros-Define of KDAUFTRAGRECHART ***************************************/

 #define KDAUFTRAGRECHART_ZEIGER(x) \
         :x->PRINT,\
         :x->DEDUCTION_AEP,\
         :x->DEDUCTION_AVP,\
         :x->WITHCOLUMNNR,\
         :x->BYEMAIL,\
         :x->KDAUFTRAGNR

 #define KDAUFTRAGRECHART_ZEIGERSEL(x) \
         :x->PRINT,\
         :x->DEDUCTION_AEP,\
         :x->DEDUCTION_AVP,\
         :x->WITHCOLUMNNR,\
         :x->BYEMAIL,\
         :x->KDAUFTRAGNR

 #define KDAUFTRAGRECHART_UPDATE(x) \
         KDAUFTRAGRECHART.PRINT=:x->PRINT,\
         KDAUFTRAGRECHART.DEDUCTION_AEP=:x->DEDUCTION_AEP,\
         KDAUFTRAGRECHART.DEDUCTION_AVP=:x->DEDUCTION_AVP,\
         KDAUFTRAGRECHART.WITHCOLUMNNR=:x->WITHCOLUMNNR,\
         KDAUFTRAGRECHART.BYEMAIL=:x->BYEMAIL,\
         KDAUFTRAGRECHART.KDAUFTRAGNR=:x->KDAUFTRAGNR

/* SqlMacros390-Define of KDAUFTRAGRECHART ************************************/

 #define KDAUFTRAGRECHART_ZEIGER_390 \
         :PRINT,\
         :DEDUCTION_AEP,\
         :DEDUCTION_AVP,\
         :WITHCOLUMNNR,\
         :BYEMAIL,\
         :KDAUFTRAGNR

 #define KDAUFTRAGRECHART_UPDATE_390 \
         PRINT=:PRINT,\
         DEDUCTION_AEP=:DEDUCTION_AEP,\
         DEDUCTION_AVP=:DEDUCTION_AVP,\
         WITHCOLUMNNR=:WITHCOLUMNNR,\
         BYEMAIL=:BYEMAIL,\
         KDAUFTRAGNR=:KDAUFTRAGNR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGRECHART ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGRECHART {
         short PRINT;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short WITHCOLUMNNR;
         short BYEMAIL;
         long KDAUFTRAGNR;
        } kdauftragrechartS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGRECHART {
         short PRINT;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short WITHCOLUMNNR;
         short BYEMAIL;
         long KDAUFTRAGNR;

			bool operator==(const N_KDAUFTRAGRECHART& right) const {
			return(
				PRINT == right.PRINT &&
				DEDUCTION_AEP == right.DEDUCTION_AEP &&
				DEDUCTION_AVP == right.DEDUCTION_AVP &&
				WITHCOLUMNNR == right.WITHCOLUMNNR &&
				BYEMAIL == right.BYEMAIL &&
				KDAUFTRAGNR == right.KDAUFTRAGNR
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				PRINT = 0;
				DEDUCTION_AEP = 0;
				DEDUCTION_AVP = 0;
				WITHCOLUMNNR = 0;
				BYEMAIL = 0;
				KDAUFTRAGNR = 0;
#endif
			}
         } kdauftragrechartS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGRECHART **********************************/

 struct S_KDAUFTRAGRECHART {
         char PRINT[7];
         char DEDUCTION_AEP[7];
         char DEDUCTION_AVP[7];
         char WITHCOLUMNNR[7];
         char BYEMAIL[7];
         char KDAUFTRAGNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGRECHART *****************/

 struct O_KDAUFTRAGRECHART {
         char PRINT[7];
         char DEDUCTION_AEP[7];
         char DEDUCTION_AVP[7];
         char WITHCOLUMNNR[7];
         char BYEMAIL[7];
         char KDAUFTRAGNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGRECHART ****************************/

 struct C_KDAUFTRAGRECHART {
         short PRINT;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short WITHCOLUMNNR;
         short BYEMAIL;
         long KDAUFTRAGNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGRECHART **************************/

 struct I_KDAUFTRAGRECHART {
         short PRINT;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short WITHCOLUMNNR;
         short BYEMAIL;
         short KDAUFTRAGNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGRECHART ************************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGRECHART_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGRECHART_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGRECHART ******************************/

 #define KDAUFTRAGRECHART_S390 \
         short PRINT; \
         short DEDUCTION_AEP; \
         short DEDUCTION_AVP; \
         short WITHCOLUMNNR; \
         short BYEMAIL; \
         long KDAUFTRAGNR; \



/* Copy-Function Struct to single Data KDAUFTRAGRECHART ***********************/

 #define KDAUFTRAGRECHART_S390_COPY_TO_SINGLE(_x_) \
         PRINT=_x_->PRINT;\
         DEDUCTION_AEP=_x_->DEDUCTION_AEP;\
         DEDUCTION_AVP=_x_->DEDUCTION_AVP;\
         WITHCOLUMNNR=_x_->WITHCOLUMNNR;\
         BYEMAIL=_x_->BYEMAIL;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\

 #define KDAUFTRAGRECHART_S390_COPY_TO_STRUCT(_x_) \
          _x_->PRINT=PRINT;\
          _x_->DEDUCTION_AEP=DEDUCTION_AEP;\
          _x_->DEDUCTION_AVP=DEDUCTION_AVP;\
          _x_->WITHCOLUMNNR=WITHCOLUMNNR;\
          _x_->BYEMAIL=BYEMAIL;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\



/* FunctionNumber-Define of kdauftragrechart **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragrechart ******************************/


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

class CKDAUFTRAGRECHART : public ppDadeVirtual
{
	//data members
	public:
		kdauftragrechartS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kdauftragrechartS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragrechartS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kdauftragrechartS>; Strip(s); kdauftragrechartS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragrechartS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kdauftragrechartS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kdauftragrechartS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetPrint() const	{ return s.PRINT; }
		short		GetDeduction_aep() const	{ return s.DEDUCTION_AEP; }
		short		GetDeduction_avp() const	{ return s.DEDUCTION_AVP; }
		short		GetWithcolumnnr() const	{ return s.WITHCOLUMNNR; }
		short		GetByemail() const	{ return s.BYEMAIL; }
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		const kdauftragrechartS& GetStruct() const { return s; }
		void 		SetPrint(short t) { s.PRINT = t; }
		void 		SetDeduction_aep(short t) { s.DEDUCTION_AEP = t; }
		void 		SetDeduction_avp(short t) { s.DEDUCTION_AVP = t; }
		void 		SetWithcolumnnr(short t) { s.WITHCOLUMNNR = t; }
		void 		SetByemail(short t) { s.BYEMAIL = t; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetStruct(const kdauftragrechartS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CKDAUFTRAGRECHART()  //constructor
		{
			::buf_default((void *)&s, KDAUFTRAGRECHART_BES, KDAUFTRAGRECHART_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CKDAUFTRAGRECHART()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KDAUFTRAGRECHART_BES, KDAUFTRAGRECHART_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGRECHART_BES, KDAUFTRAGRECHART_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGRECHART_BES, KDAUFTRAGRECHART_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_KDAUFTRAGRECHART& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGRECHART_BES, KDAUFTRAGRECHART_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KDAUFTRAGRECHART *************************************/

 #define KDAUFTRAGRECHART_CREATE(x) exec sql create table x (\
         PRINT smallint default 0 not null,\
         DEDUCTION_AEP smallint default 0 not null,\
         DEDUCTION_AVP smallint default 0 not null,\
         WITHCOLUMNNR smallint default 0 not null,\
         BYEMAIL smallint default 0 not null,\
         KDAUFTRAGNR integer default 0 not null) in ksc extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of KDAUFTRAGRECHART ***********************************/

 #define KDAUFTRAGRECHART_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdauftrechart_1 on _X_(\
              kdauftragnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGRECHART ***********************************/

 #define KDAUFTRAGRECHART_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdauftrechart_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

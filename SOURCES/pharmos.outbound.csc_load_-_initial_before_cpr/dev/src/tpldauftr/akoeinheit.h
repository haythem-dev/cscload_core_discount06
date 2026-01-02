#ifndef __PP_AKOEINHEIT_H_
#define __PP_AKOEINHEIT_H_

/******************************************************************************/
/* c:\prj\df\unix\tpldauftr\akoeinheit ****************************************/
/******************************************************************************/

/* Length-Define of AKOEINHEIT ************************************************/

  #define L_AKOEINHEIT_DATUM 11
  #define L_AKOEINHEIT_AUFTRAGNRKO 11
  #define L_AKOEINHEIT_KDAUFTRAGNR 11
  #define L_AKOEINHEIT_KOBEHAELTNR 11

/* Length/Count-Define of AKOEINHEIT ******************************************/

  #define LS_AKOEINHEIT_DATUM 10 + 1
  #define LS_AKOEINHEIT_AUFTRAGNRKO 10 + 1
  #define LS_AKOEINHEIT_KDAUFTRAGNR 10 + 1
  #define LS_AKOEINHEIT_KOBEHAELTNR 10 + 1

  #define AKOEINHEITDATUM 0
  #define AKOEINHEITAUFTRAGNRKO 1
  #define AKOEINHEITKDAUFTRAGNR 2
  #define AKOEINHEITKOBEHAELTNR 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define AKOEINHEIT_H
 #define AKOEINHEIT_ANZ ( sizeof(AKOEINHEIT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of AKOEINHEIT ****************************************************/

 #define AKOEINHEIT_LISTE \
         AKOEINHEIT.DATUM,\
         AKOEINHEIT.AUFTRAGNRKO,\
         AKOEINHEIT.KDAUFTRAGNR,\
         AKOEINHEIT.KOBEHAELTNR

 #define AKOEINHEIT_LISTE_390 \
         DATUM,\
         AUFTRAGNRKO,\
         KDAUFTRAGNR,\
         KOBEHAELTNR

 #define AKOEINHEIT_PLISTE \
         "AKOEINHEIT.DATUM,"\
         "AKOEINHEIT.AUFTRAGNRKO,"\
         "AKOEINHEIT.KDAUFTRAGNR,"\
         "AKOEINHEIT.KOBEHAELTNR"

 #define AKOEINHEIT_PELISTE \
         "DATUM,"\
         "AUFTRAGNRKO,"\
         "KDAUFTRAGNR,"\
         "KOBEHAELTNR"

 #define AKOEINHEIT_UPDLISTE \
         "DATUM=?,"\
         "AUFTRAGNRKO=?,"\
         "KDAUFTRAGNR=?,"\
         "KOBEHAELTNR=?"

/* SqlMacros-Define of AKOEINHEIT *********************************************/

 #define AKOEINHEIT_ZEIGER(x) \
         :x->DATUM,\
         :x->AUFTRAGNRKO,\
         :x->KDAUFTRAGNR,\
         :x->KOBEHAELTNR

 #define AKOEINHEIT_UPDATE(x) \
         AKOEINHEIT.DATUM=:x->DATUM,\
         AKOEINHEIT.AUFTRAGNRKO=:x->AUFTRAGNRKO,\
         AKOEINHEIT.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         AKOEINHEIT.KOBEHAELTNR=:x->KOBEHAELTNR

/* SqlMacros390-Define of AKOEINHEIT ******************************************/

 #define AKOEINHEIT_ZEIGER_390 \
         :DATUM,\
         :AUFTRAGNRKO,\
         :KDAUFTRAGNR,\
         :KOBEHAELTNR

 #define AKOEINHEIT_UPDATE_390 \
         DATUM=:DATUM,\
         AUFTRAGNRKO=:AUFTRAGNRKO,\
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         KOBEHAELTNR=:KOBEHAELTNR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of AKOEINHEIT *********************************************/

 typedef struct N_AKOEINHEIT {
         long DATUM;
         long AUFTRAGNRKO;
         long KDAUFTRAGNR;
         long KOBEHAELTNR;
         } akoeinheitS;

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of AKOEINHEIT ****************************************/

 struct S_AKOEINHEIT {
         char DATUM[11];
         char AUFTRAGNRKO[11];
         char KDAUFTRAGNR[11];
         char KOBEHAELTNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of AKOEINHEIT ***********************/

 struct O_AKOEINHEIT {
         char DATUM[11];
         char AUFTRAGNRKO[11];
         char KDAUFTRAGNR[11];
         char KOBEHAELTNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of AKOEINHEIT ***********************************/

 struct C_AKOEINHEIT {
         long DATUM;
         long AUFTRAGNRKO;
         long KDAUFTRAGNR;
         long KOBEHAELTNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of AKOEINHEIT *********************************/

 struct I_AKOEINHEIT {
         short DATUM;
         short AUFTRAGNRKO;
         short KDAUFTRAGNR;
         short KOBEHAELTNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of AKOEINHEIT ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc AKOEINHEIT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc AKOEINHEIT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of AKOEINHEIT ************************************/

 #define AKOEINHEIT_S390 \
         long DATUM; \
         long AUFTRAGNRKO; \
         long KDAUFTRAGNR; \
         long KOBEHAELTNR; \



/* Copy-Function Struct to single Data AKOEINHEIT *****************************/

 #define AKOEINHEIT_S390_COPY_TO_SINGLE(_x_) \
         DATUM=_x_->DATUM;\
         AUFTRAGNRKO=_x_->AUFTRAGNRKO;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         KOBEHAELTNR=_x_->KOBEHAELTNR;\

 #define AKOEINHEIT_S390_COPY_TO_STRUCT(_x_) \
          _x_->DATUM=DATUM;\
          _x_->AUFTRAGNRKO=AUFTRAGNRKO;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->KOBEHAELTNR=KOBEHAELTNR;\



/* FunctionNumber-Define of akoeinheit ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of akoeinheit ************************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS
#include<vector>
using namespace std;

class CAKOEINHEIT
{
	//data members
	public:
		akoeinheitS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<akoeinheitS> *pl; // pointer to class list

	//functions
	public:

		vector<akoeinheitS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<akoeinheitS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetDatum()	{ return s.DATUM; }
		long		GetAuftragnrko()	{ return s.AUFTRAGNRKO; }
		long		GetKdauftragnr()	{ return s.KDAUFTRAGNR; }
		long		GetKobehaeltnr()	{ return s.KOBEHAELTNR; }

		void 		SetDatum(long t) { s.DATUM = t; }
		void 		SetAuftragnrko(long t) { s.AUFTRAGNRKO = t; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetKobehaeltnr(long t) { s.KOBEHAELTNR = t; }


		CAKOEINHEIT()  //constructor
		{
			::buf_default((void *)&s,AKOEINHEIT_BES,AKOEINHEIT_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			pl = NULL;
		}

		~CAKOEINHEIT()  //destructor
		{
			if(pl) delete pl;
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, AKOEINHEIT_BES, AKOEINHEIT_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		int UniqueServerCall(int FncNr,int pos=0)
		{
			rc=::ServerNr(pos,FncNr,(void *)&s,AKOEINHEIT_BES,AKOEINHEIT_ANZ, error_msg);
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of AKOEINHEIT *******************************************/

 #define AKOEINHEIT_CREATE(x) exec sql create table x (\
         DATUM integer default 0 not null,\
         AUFTRAGNRKO integer default 0 not null,\
         KDAUFTRAGNR integer default 0 not null,\
         KOBEHAELTNR integer default 0 not null) extent size 12086 lock mode row;



/* CreateIndexStatement of AKOEINHEIT *****************************************/

 #define AKOEINHEIT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_akoeinheit_1 on _X_(\
              datum,\
              auftragnrko,\
              kobehaeltnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of AKOEINHEIT *****************************************/

 #define AKOEINHEIT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_akoeinheit_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\


#endif

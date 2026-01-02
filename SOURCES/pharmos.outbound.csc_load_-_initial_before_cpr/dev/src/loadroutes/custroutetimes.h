#ifndef __PP_CUSTROUTETIMES_H_
#define __PP_CUSTROUTETIMES_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadroutes\custroutetimes ***********************************/
/******************************************************************************/

/* Length-Define of CUSTROUTETIMES ********************************************/

  #define L_CUSTROUTETIMES_VERTRIEBSZENTRUMNR 6
  #define L_CUSTROUTETIMES_KUNDENNR 11
  #define L_CUSTROUTETIMES_TOURID 6
  #define L_CUSTROUTETIMES_DATUMKOMMI 11
  #define L_CUSTROUTETIMES_CONSTIME 11
  #define L_CUSTROUTETIMES_PROCESSSTATE 1

/* Length/Count-Define of CUSTROUTETIMES **************************************/

  #define LS_CUSTROUTETIMES_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_CUSTROUTETIMES_KUNDENNR 10 + 1
  #define LS_CUSTROUTETIMES_TOURID 6 + 1
  #define LS_CUSTROUTETIMES_DATUMKOMMI 10 + 1
  #define LS_CUSTROUTETIMES_CONSTIME 10 + 1
  #define LS_CUSTROUTETIMES_PROCESSSTATE 1 + 1

  #define CUSTROUTETIMESVERTRIEBSZENTRUMNR 0
  #define CUSTROUTETIMESKUNDENNR 1
  #define CUSTROUTETIMESTOURID 2
  #define CUSTROUTETIMESDATUMKOMMI 3
  #define CUSTROUTETIMESCONSTIME 4
  #define CUSTROUTETIMESPROCESSSTATE 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CUSTROUTETIMES_H
 #define CUSTROUTETIMES_ANZ ( sizeof(CUSTROUTETIMES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTROUTETIMES ************************************************/

 #define CUSTROUTETIMES_LISTE \
         TOURPLANCONSTIME.VERTRIEBSZENTRUMNR,\
         TOURPLANCONSTIME.KUNDENNR,\
         TOURPLANCONSTIME.TOURID,\
         TOURPLANCONSTIME.DATUMKOMMI,\
         TOURPLANCONSTIME.CONSTIME,\
         TOURPLANCONSTIME.PROCESSSTATE

 #define CUSTROUTETIMES_LISTE_390 \
         VERTRIEBSZENTRUMNR,\
         KUNDENNR,\
         TOURID,\
         DATUMKOMMI,\
         CONSTIME,\
         PROCESSSTATE

 #define CUSTROUTETIMES_PLISTE \
         "TOURPLANCONSTIME.VERTRIEBSZENTRUMNR,"\
         "TOURPLANCONSTIME.KUNDENNR,"\
         "TOURPLANCONSTIME.TOURID,"\
         "TOURPLANCONSTIME.DATUMKOMMI,"\
         "TOURPLANCONSTIME.CONSTIME,"\
         "TOURPLANCONSTIME.PROCESSSTATE"

 #define CUSTROUTETIMES_PELISTE \
         "VERTRIEBSZENTRUMNR,"\
         "KUNDENNR,"\
         "TOURID,"\
         "DATUMKOMMI,"\
         "CONSTIME,"\
         "PROCESSSTATE"

 #define CUSTROUTETIMES_UPDLISTE \
         "VERTRIEBSZENTRUMNR=?,"\
         "KUNDENNR=?,"\
         "TOURID=?,"\
         "DATUMKOMMI=?,"\
         "CONSTIME=?,"\
         "PROCESSSTATE=?"

/* SqlMacros-Define of CUSTROUTETIMES *****************************************/

 #define CUSTROUTETIMES_ZEIGER(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TOURID,\
         :x->DATUMKOMMI,\
         :x->CONSTIME,\
         :x->PROCESSSTATE

 #define CUSTROUTETIMES_ZEIGERSEL(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TOURID,\
         :x->DATUMKOMMI,\
         :x->CONSTIME,\
         :x->PROCESSSTATE

 #define CUSTROUTETIMES_UPDATE(x) \
         TOURPLANCONSTIME.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         TOURPLANCONSTIME.KUNDENNR=:x->KUNDENNR,\
         TOURPLANCONSTIME.TOURID=:x->TOURID,\
         TOURPLANCONSTIME.DATUMKOMMI=:x->DATUMKOMMI,\
         TOURPLANCONSTIME.CONSTIME=:x->CONSTIME,\
         TOURPLANCONSTIME.PROCESSSTATE=:x->PROCESSSTATE

/* SqlMacros390-Define of CUSTROUTETIMES **************************************/

 #define CUSTROUTETIMES_ZEIGER_390 \
         :VERTRIEBSZENTRUMNR,\
         :KUNDENNR,\
         :TOURID,\
         :DATUMKOMMI,\
         :CONSTIME,\
         :PROCESSSTATE

 #define CUSTROUTETIMES_UPDATE_390 \
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         KUNDENNR=:KUNDENNR,\
         TOURID=:TOURID,\
         DATUMKOMMI=:DATUMKOMMI,\
         CONSTIME=:CONSTIME,\
         PROCESSSTATE=:PROCESSSTATE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CUSTROUTETIMES *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_CUSTROUTETIMES {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE[2];
        } custroutetimesS;
 #else /*TRANSCLASS*/
 typedef struct N_CUSTROUTETIMES {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE[2];

			bool operator==(const N_CUSTROUTETIMES& right) const {
			return(
				VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
				KUNDENNR == right.KUNDENNR &&
				!strcmp(TOURID, right.TOURID) &&
				DATUMKOMMI == right.DATUMKOMMI &&
				CONSTIME == right.CONSTIME &&
				!strcmp(PROCESSSTATE, right.PROCESSSTATE)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				VERTRIEBSZENTRUMNR = 0;
				KUNDENNR = 0;
				strcpy(TOURID, " " );
				DATUMKOMMI = 0;
				CONSTIME = 0;
				strcpy(PROCESSSTATE, " " );
#endif
			}
         } custroutetimesS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTROUTETIMES ************************************/

 struct S_CUSTROUTETIMES {
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char TOURID[6 + 1];
         char DATUMKOMMI[11];
         char CONSTIME[11];
         char PROCESSSTATE[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTROUTETIMES *******************/

 struct O_CUSTROUTETIMES {
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char TOURID[6];
         char DATUMKOMMI[11];
         char CONSTIME[11];
         char PROCESSSTATE[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTROUTETIMES ******************************/

 struct C_CUSTROUTETIMES {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTROUTETIMES ****************************/

 struct I_CUSTROUTETIMES {
         short VERTRIEBSZENTRUMNR;
         short KUNDENNR;
         short TOURID;
         short DATUMKOMMI;
         short CONSTIME;
         short PROCESSSTATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTROUTETIMES **************************************/

#if defined (BUF_DESC)
 static struct buf_desc CUSTROUTETIMES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CUSTROUTETIMES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of CUSTROUTETIMES ********************************/

 #define CUSTROUTETIMES_S390 \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         char TOURID[7]; \
         long DATUMKOMMI; \
         long CONSTIME; \
         char PROCESSSTATE; \



/* Copy-Function Struct to single Data CUSTROUTETIMES *************************/

 #define CUSTROUTETIMES_S390_COPY_TO_SINGLE(_x_) \
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
          strcpy(TOURID,_x_->TOURID);\
         DATUMKOMMI=_x_->DATUMKOMMI;\
         CONSTIME=_x_->CONSTIME;\
         PROCESSSTATE=_x_->PROCESSSTATE;\

 #define CUSTROUTETIMES_S390_COPY_TO_STRUCT(_x_) \
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->DATUMKOMMI=DATUMKOMMI;\
          _x_->CONSTIME=CONSTIME;\
          _x_->PROCESSSTATE=PROCESSSTATE;\



/* FunctionNumber-Define of custroutetimes ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of custroutetimes ********************************/


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

class CCUSTROUTETIMES : public ppDadeVirtual
{
	//data members
	public:
		custroutetimesS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<custroutetimesS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<custroutetimesS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<custroutetimesS>; Strip(s); custroutetimesS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<custroutetimesS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<custroutetimesS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<custroutetimesS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetVertriebszentrumnr() const	{ return s.VERTRIEBSZENTRUMNR; }
		long		GetKundennr() const	{ return s.KUNDENNR; }
		const char*	GetTourid(ppString& t) const 	{ t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
		long		GetDatumkommi() const	{ return s.DATUMKOMMI; }
		long		GetConstime() const	{ return s.CONSTIME; }
		char		GetProcessstate() const	{ return s.PROCESSSTATE[0]; }
		const custroutetimesS& GetStruct() const { return s; }
		void 		SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
		void 		SetKundennr(long t) { s.KUNDENNR = t; }
		void 		SetTourid(const ppString& t) { ppGStrCopy(s.TOURID,t.c_str() ,L_CUSTROUTETIMES_TOURID); }
		void 		SetDatumkommi(long t) { s.DATUMKOMMI = t; }
		void 		SetConstime(long t) { s.CONSTIME = t; }
		void 		SetProcessstate(char t) { s.PROCESSSTATE[0] = t; s.PROCESSSTATE[1] = '\0';}
		void 		SetStruct(const custroutetimesS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CCUSTROUTETIMES()  //constructor
		{
			::buf_default((void *)&s, CUSTROUTETIMES_BES, CUSTROUTETIMES_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CCUSTROUTETIMES()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, CUSTROUTETIMES_BES, CUSTROUTETIMES_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTROUTETIMES_BES, CUSTROUTETIMES_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, CUSTROUTETIMES_BES, CUSTROUTETIMES_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_CUSTROUTETIMES& d)
		{
#ifdef WIN32
			ppGStripLast(d.TOURID);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTROUTETIMES_BES, CUSTROUTETIMES_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of CUSTROUTETIMES ***************************************/

 #define CUSTROUTETIMES_CREATE(x) exec sql create table x (\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         TOURID char(6) default " " not null,\
         DATUMKOMMI integer default 0 not null,\
         CONSTIME integer default 0 not null,\
         PROCESSSTATE char(1) default " " not null) extent size 1568 next size 160 lock mode row;



/* CreateIndexStatement of CUSTROUTETIMES *************************************/

 #define CUSTROUTETIMES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_tourplancons_1 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              tourid,\
              datumkommi );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTROUTETIMES *************************************/

 #define CUSTROUTETIMES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_tourplancons_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

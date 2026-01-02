#ifndef __PP_ROUTETIMES_H_
#define __PP_ROUTETIMES_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadroutes\routetimes ***************************************/
/******************************************************************************/

/* Length-Define of ROUTETIMES ************************************************/

  #define L_ROUTETIMES_FILIALNR 6
  #define L_ROUTETIMES_TOURID 6
  #define L_ROUTETIMES_DATUMKOMMI 11
  #define L_ROUTETIMES_CONSTIME 11
  #define L_ROUTETIMES_PROCESSSTATE 1

/* Length/Count-Define of ROUTETIMES ******************************************/

  #define LS_ROUTETIMES_FILIALNR 5 + 1
  #define LS_ROUTETIMES_TOURID 6 + 1
  #define LS_ROUTETIMES_DATUMKOMMI 10 + 1
  #define LS_ROUTETIMES_CONSTIME 10 + 1
  #define LS_ROUTETIMES_PROCESSSTATE 1 + 1

  #define ROUTETIMESFILIALNR 0
  #define ROUTETIMESTOURID 1
  #define ROUTETIMESDATUMKOMMI 2
  #define ROUTETIMESCONSTIME 3
  #define ROUTETIMESPROCESSSTATE 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ROUTETIMES_H
 #define ROUTETIMES_ANZ ( sizeof(ROUTETIMES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ROUTETIMES ****************************************************/

 #define ROUTETIMES_LISTE \
         TOURCONSTIME.FILIALNR,\
         TOURCONSTIME.TOURID,\
         TOURCONSTIME.DATUMKOMMI,\
         TOURCONSTIME.CONSTIME,\
         TOURCONSTIME.PROCESSSTATE

 #define ROUTETIMES_LISTE_390 \
         FILIALNR,\
         TOURID,\
         DATUMKOMMI,\
         CONSTIME,\
         PROCESSSTATE

 #define ROUTETIMES_PLISTE \
         "TOURCONSTIME.FILIALNR,"\
         "TOURCONSTIME.TOURID,"\
         "TOURCONSTIME.DATUMKOMMI,"\
         "TOURCONSTIME.CONSTIME,"\
         "TOURCONSTIME.PROCESSSTATE"

 #define ROUTETIMES_PELISTE \
         "FILIALNR,"\
         "TOURID,"\
         "DATUMKOMMI,"\
         "CONSTIME,"\
         "PROCESSSTATE"

 #define ROUTETIMES_UPDLISTE \
         "FILIALNR=?,"\
         "TOURID=?,"\
         "DATUMKOMMI=?,"\
         "CONSTIME=?,"\
         "PROCESSSTATE=?"

/* SqlMacros-Define of ROUTETIMES *********************************************/

 #define ROUTETIMES_ZEIGER(x) \
         :x->FILIALNR,\
         :x->TOURID,\
         :x->DATUMKOMMI,\
         :x->CONSTIME,\
         :x->PROCESSSTATE

 #define ROUTETIMES_ZEIGERSEL(x) \
         :x->FILIALNR,\
         :x->TOURID,\
         :x->DATUMKOMMI,\
         :x->CONSTIME,\
         :x->PROCESSSTATE

 #define ROUTETIMES_UPDATE(x) \
         TOURCONSTIME.FILIALNR=:x->FILIALNR,\
         TOURCONSTIME.TOURID=:x->TOURID,\
         TOURCONSTIME.DATUMKOMMI=:x->DATUMKOMMI,\
         TOURCONSTIME.CONSTIME=:x->CONSTIME,\
         TOURCONSTIME.PROCESSSTATE=:x->PROCESSSTATE

/* SqlMacros390-Define of ROUTETIMES ******************************************/

 #define ROUTETIMES_ZEIGER_390 \
         :FILIALNR,\
         :TOURID,\
         :DATUMKOMMI,\
         :CONSTIME,\
         :PROCESSSTATE

 #define ROUTETIMES_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         TOURID=:TOURID,\
         DATUMKOMMI=:DATUMKOMMI,\
         CONSTIME=:CONSTIME,\
         PROCESSSTATE=:PROCESSSTATE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ROUTETIMES *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ROUTETIMES {
         short FILIALNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE[2];
        } routetimesS;
 #else /*TRANSCLASS*/
 typedef struct N_ROUTETIMES {
         short FILIALNR;
         char TOURID[7];
         long DATUMKOMMI;
         long CONSTIME;
         char PROCESSSTATE[2];

			bool operator==(const N_ROUTETIMES& right) const {
			return(
				FILIALNR == right.FILIALNR &&
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
				FILIALNR = 0;
				strcpy(TOURID, " " );
				DATUMKOMMI = 0;
				CONSTIME = 0;
				strcpy(PROCESSSTATE, " " );
#endif
			}
         } routetimesS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ROUTETIMES ****************************************/

 struct S_ROUTETIMES {
         char FILIALNR[7];
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

/* Stringbuffer (without strend) Structur of ROUTETIMES ***********************/

 struct O_ROUTETIMES {
         char FILIALNR[7];
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

/* Structur with real chartype of ROUTETIMES **********************************/

 struct C_ROUTETIMES {
         short FILIALNR;
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

/* Sizetype  Structur (buf_desc) of ROUTETIMES ********************************/

 struct I_ROUTETIMES {
         short FILIALNR;
         short TOURID;
         short DATUMKOMMI;
         short CONSTIME;
         short PROCESSSTATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ROUTETIMES ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc ROUTETIMES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ROUTETIMES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of ROUTETIMES ************************************/

 #define ROUTETIMES_S390 \
         short FILIALNR; \
         char TOURID[7]; \
         long DATUMKOMMI; \
         long CONSTIME; \
         char PROCESSSTATE; \



/* Copy-Function Struct to single Data ROUTETIMES *****************************/

 #define ROUTETIMES_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
          strcpy(TOURID,_x_->TOURID);\
         DATUMKOMMI=_x_->DATUMKOMMI;\
         CONSTIME=_x_->CONSTIME;\
         PROCESSSTATE=_x_->PROCESSSTATE;\

 #define ROUTETIMES_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          strcpy(_x_->TOURID,TOURID);\
          _x_->DATUMKOMMI=DATUMKOMMI;\
          _x_->CONSTIME=CONSTIME;\
          _x_->PROCESSSTATE=PROCESSSTATE;\



/* FunctionNumber-Define of routetimes ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of routetimes ************************************/


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

class CROUTETIMES : public ppDadeVirtual
{
	//data members
	public:
		routetimesS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<routetimesS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<routetimesS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<routetimesS>; Strip(s); routetimesS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<routetimesS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<routetimesS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<routetimesS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetFilialnr() const	{ return s.FILIALNR; }
		const char*	GetTourid(ppString& t) const 	{ t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
		long		GetDatumkommi() const	{ return s.DATUMKOMMI; }
		long		GetConstime() const	{ return s.CONSTIME; }
		char		GetProcessstate() const	{ return s.PROCESSSTATE[0]; }
		const routetimesS& GetStruct() const { return s; }
		void 		SetFilialnr(short t) { s.FILIALNR = t; }
		void 		SetTourid(const ppString& t) { ppGStrCopy(s.TOURID,t.c_str() ,L_ROUTETIMES_TOURID); }
		void 		SetDatumkommi(long t) { s.DATUMKOMMI = t; }
		void 		SetConstime(long t) { s.CONSTIME = t; }
		void 		SetProcessstate(char t) { s.PROCESSSTATE[0] = t; s.PROCESSSTATE[1] = '\0';}
		void 		SetStruct(const routetimesS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CROUTETIMES()  //constructor
		{
			::buf_default((void *)&s, ROUTETIMES_BES, ROUTETIMES_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CROUTETIMES()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ROUTETIMES_BES, ROUTETIMES_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, ROUTETIMES_BES, ROUTETIMES_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, ROUTETIMES_BES, ROUTETIMES_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_ROUTETIMES& d)
		{
#ifdef WIN32
			ppGStripLast(d.TOURID);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, ROUTETIMES_BES, ROUTETIMES_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of ROUTETIMES *******************************************/

 #define ROUTETIMES_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         TOURID char(6) default " " not null,\
         DATUMKOMMI integer default 0 not null,\
         CONSTIME integer default 0 not null,\
         PROCESSSTATE char(1) default " " not null) extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of ROUTETIMES *****************************************/

 #define ROUTETIMES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_tourcons_1 on _X_(\
              filialnr,\
              tourid,\
              datumkommi );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ROUTETIMES *****************************************/

 #define ROUTETIMES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_tourcons_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

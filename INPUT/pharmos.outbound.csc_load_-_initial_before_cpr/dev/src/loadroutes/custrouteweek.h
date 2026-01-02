#ifndef __PP_CUSTROUTEWEEK_H_
#define __PP_CUSTROUTEWEEK_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadroutes\custrouteweek ************************************/
/******************************************************************************/

/* Length-Define of CUSTROUTEWEEK *********************************************/

  #define L_CUSTROUTEWEEK_VERTRIEBSZENTRUMNR 6
  #define L_CUSTROUTEWEEK_KUNDENNR 11
  #define L_CUSTROUTEWEEK_TOURID 6
  #define L_CUSTROUTEWEEK_TAGESTYP 6
  #define L_CUSTROUTEWEEK_KZUPD 1
  #define L_CUSTROUTEWEEK_WEEKDAY 6

/* Length/Count-Define of CUSTROUTEWEEK ***************************************/

  #define LS_CUSTROUTEWEEK_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_CUSTROUTEWEEK_KUNDENNR 10 + 1
  #define LS_CUSTROUTEWEEK_TOURID 6 + 1
  #define LS_CUSTROUTEWEEK_TAGESTYP 6 + 1
  #define LS_CUSTROUTEWEEK_KZUPD 1 + 1
  #define LS_CUSTROUTEWEEK_WEEKDAY 5 + 1

  #define CUSTROUTEWEEKVERTRIEBSZENTRUMNR 0
  #define CUSTROUTEWEEKKUNDENNR 1
  #define CUSTROUTEWEEKTOURID 2
  #define CUSTROUTEWEEKTAGESTYP 3
  #define CUSTROUTEWEEKKZUPD 4
  #define CUSTROUTEWEEKWEEKDAY 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CUSTROUTEWEEK_H
 #define CUSTROUTEWEEK_ANZ ( sizeof(CUSTROUTEWEEK_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTROUTEWEEK *************************************************/

 #define CUSTROUTEWEEK_LISTE \
         TOURPLANTAGWOCHE.VERTRIEBSZENTRUMNR,\
         TOURPLANTAGWOCHE.KUNDENNR,\
         TOURPLANTAGWOCHE.TOURID,\
         TOURPLANTAGWOCHE.TAGESTYP,\
         TOURPLANTAGWOCHE.KZUPD,\
         TOURPLANTAGWOCHE.WEEKDAY

 #define CUSTROUTEWEEK_LISTE_390 \
         VERTRIEBSZENTRUMNR,\
         KUNDENNR,\
         TOURID,\
         TAGESTYP,\
         KZUPD,\
         WEEKDAY

 #define CUSTROUTEWEEK_PLISTE \
         "TOURPLANTAGWOCHE.VERTRIEBSZENTRUMNR,"\
         "TOURPLANTAGWOCHE.KUNDENNR,"\
         "TOURPLANTAGWOCHE.TOURID,"\
         "TOURPLANTAGWOCHE.TAGESTYP,"\
         "TOURPLANTAGWOCHE.KZUPD,"\
         "TOURPLANTAGWOCHE.WEEKDAY"

 #define CUSTROUTEWEEK_PELISTE \
         "VERTRIEBSZENTRUMNR,"\
         "KUNDENNR,"\
         "TOURID,"\
         "TAGESTYP,"\
         "KZUPD,"\
         "WEEKDAY"

 #define CUSTROUTEWEEK_UPDLISTE \
         "VERTRIEBSZENTRUMNR=?,"\
         "KUNDENNR=?,"\
         "TOURID=?,"\
         "TAGESTYP=?,"\
         "KZUPD=?,"\
         "WEEKDAY=?"

/* SqlMacros-Define of CUSTROUTEWEEK ******************************************/

 #define CUSTROUTEWEEK_ZEIGER(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TOURID,\
         :x->TAGESTYP,\
         :x->KZUPD,\
         :x->WEEKDAY

 #define CUSTROUTEWEEK_ZEIGERSEL(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TOURID,\
         :x->TAGESTYP,\
         :x->KZUPD,\
         :x->WEEKDAY

 #define CUSTROUTEWEEK_UPDATE(x) \
         TOURPLANTAGWOCHE.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         TOURPLANTAGWOCHE.KUNDENNR=:x->KUNDENNR,\
         TOURPLANTAGWOCHE.TOURID=:x->TOURID,\
         TOURPLANTAGWOCHE.TAGESTYP=:x->TAGESTYP,\
         TOURPLANTAGWOCHE.KZUPD=:x->KZUPD,\
         TOURPLANTAGWOCHE.WEEKDAY=:x->WEEKDAY

/* SqlMacros390-Define of CUSTROUTEWEEK ***************************************/

 #define CUSTROUTEWEEK_ZEIGER_390 \
         :VERTRIEBSZENTRUMNR,\
         :KUNDENNR,\
         :TOURID,\
         :TAGESTYP,\
         :KZUPD,\
         :WEEKDAY

 #define CUSTROUTEWEEK_UPDATE_390 \
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         KUNDENNR=:KUNDENNR,\
         TOURID=:TOURID,\
         TAGESTYP=:TAGESTYP,\
         KZUPD=:KZUPD,\
         WEEKDAY=:WEEKDAY

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CUSTROUTEWEEK ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_CUSTROUTEWEEK {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         char TAGESTYP[7];
         char KZUPD[2];
         short WEEKDAY;
        } custrouteweekS;
 #else /*TRANSCLASS*/
 typedef struct N_CUSTROUTEWEEK {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         char TAGESTYP[7];
         char KZUPD[2];
         short WEEKDAY;

			bool operator==(const N_CUSTROUTEWEEK& right) const {
			return(
				VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
				KUNDENNR == right.KUNDENNR &&
				!strcmp(TOURID, right.TOURID) &&
				!strcmp(TAGESTYP, right.TAGESTYP) &&
				!strcmp(KZUPD, right.KZUPD) &&
				WEEKDAY == right.WEEKDAY
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				VERTRIEBSZENTRUMNR = 0;
				KUNDENNR = 0;
				strcpy(TOURID, " " );
				strcpy(TAGESTYP, " " );
				strcpy(KZUPD, " " );
				WEEKDAY = 0;
#endif
			}
         } custrouteweekS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTROUTEWEEK *************************************/

 struct S_CUSTROUTEWEEK {
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char TOURID[6 + 1];
         char TAGESTYP[6 + 1];
         char KZUPD[1 + 1];
         char WEEKDAY[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTROUTEWEEK ********************/

 struct O_CUSTROUTEWEEK {
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char TOURID[6];
         char TAGESTYP[6];
         char KZUPD[1];
         char WEEKDAY[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTROUTEWEEK *******************************/

 struct C_CUSTROUTEWEEK {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         char TAGESTYP[7];
         char KZUPD;
         short WEEKDAY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTROUTEWEEK *****************************/

 struct I_CUSTROUTEWEEK {
         short VERTRIEBSZENTRUMNR;
         short KUNDENNR;
         short TOURID;
         short TAGESTYP;
         short KZUPD;
         short WEEKDAY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTROUTEWEEK ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc CUSTROUTEWEEK_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CUSTROUTEWEEK_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of CUSTROUTEWEEK *********************************/

 #define CUSTROUTEWEEK_S390 \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         char TOURID[7]; \
         char TAGESTYP[7]; \
         char KZUPD; \
         short WEEKDAY; \



/* Copy-Function Struct to single Data CUSTROUTEWEEK **************************/

 #define CUSTROUTEWEEK_S390_COPY_TO_SINGLE(_x_) \
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
          strcpy(TOURID,_x_->TOURID);\
          strcpy(TAGESTYP,_x_->TAGESTYP);\
         KZUPD=_x_->KZUPD;\
         WEEKDAY=_x_->WEEKDAY;\

 #define CUSTROUTEWEEK_S390_COPY_TO_STRUCT(_x_) \
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          strcpy(_x_->TOURID,TOURID);\
          strcpy(_x_->TAGESTYP,TAGESTYP);\
          _x_->KZUPD=KZUPD;\
          _x_->WEEKDAY=WEEKDAY;\



/* FunctionNumber-Define of custrouteweek *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of custrouteweek *********************************/


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

class CCUSTROUTEWEEK : public ppDadeVirtual
{
	//data members
	public:
		custrouteweekS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<custrouteweekS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<custrouteweekS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<custrouteweekS>; Strip(s); custrouteweekS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<custrouteweekS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<custrouteweekS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<custrouteweekS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetVertriebszentrumnr() const	{ return s.VERTRIEBSZENTRUMNR; }
		long		GetKundennr() const	{ return s.KUNDENNR; }
		const char*	GetTourid(ppString& t) const 	{ t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetTagestyp(ppString& t) const 	{ t = s.TAGESTYP; t.erasespace(ppString::END); return t.c_str(); }
		char		GetKzupd() const	{ return s.KZUPD[0]; }
		short		GetWeekday() const	{ return s.WEEKDAY; }
		const custrouteweekS& GetStruct() const { return s; }
		void 		SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
		void 		SetKundennr(long t) { s.KUNDENNR = t; }
		void 		SetTourid(const ppString& t) { ppGStrCopy(s.TOURID,t.c_str() ,L_CUSTROUTEWEEK_TOURID); }
		void 		SetTagestyp(const ppString& t) { ppGStrCopy(s.TAGESTYP,t.c_str() ,L_CUSTROUTEWEEK_TAGESTYP); }
		void 		SetKzupd(char t) { s.KZUPD[0] = t; s.KZUPD[1] = '\0';}
		void 		SetWeekday(short t) { s.WEEKDAY = t; }
		void 		SetStruct(const custrouteweekS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CCUSTROUTEWEEK()  //constructor
		{
			::buf_default((void *)&s, CUSTROUTEWEEK_BES, CUSTROUTEWEEK_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CCUSTROUTEWEEK()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, CUSTROUTEWEEK_BES, CUSTROUTEWEEK_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTROUTEWEEK_BES, CUSTROUTEWEEK_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, CUSTROUTEWEEK_BES, CUSTROUTEWEEK_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_CUSTROUTEWEEK& d)
		{
#ifdef WIN32
			ppGStripLast(d.TOURID);
			ppGStripLast(d.TAGESTYP);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTROUTEWEEK_BES, CUSTROUTEWEEK_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of CUSTROUTEWEEK ****************************************/

 #define CUSTROUTEWEEK_CREATE(x) exec sql create table x (\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         TOURID char(6) default " " not null,\
         TAGESTYP char(6) default " " not null,\
         KZUPD char(1) default " " not null,\
         WEEKDAY smallint default 0 not null) extent size 5492 next size 552 lock mode row;



/* CreateIndexStatement of CUSTROUTEWEEK **************************************/

 #define CUSTROUTEWEEK_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_tourtagwoche_1 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              tagestyp,\
              tourid );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTROUTEWEEK **************************************/

 #define CUSTROUTEWEEK_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_tourtagwoche_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

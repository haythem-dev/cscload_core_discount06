#ifndef __PP_TOURPLANTAGWOCHE_H_
#define __PP_TOURPLANTAGWOCHE_H_

/******************************************************************************/
/* u:\tourplantagwoche ********************************************************/
/******************************************************************************/

/* Length-Define of TOURPLANTAGWOCHE ******************************************/

  #define L_TOURPLANTAGWOCHE_VERTRIEBSZENTRUMNR 6
  #define L_TOURPLANTAGWOCHE_KUNDENNR 11
  #define L_TOURPLANTAGWOCHE_TOURID 6
  #define L_TOURPLANTAGWOCHE_TAGESTYP 6
  #define L_TOURPLANTAGWOCHE_WEEKDAY 6
  #define L_TOURPLANTAGWOCHE_ISTVERBUNDTOUR 1
  #define L_TOURPLANTAGWOCHE_KDAUFTRAGART 2
  #define L_TOURPLANTAGWOCHE_FAHRTZEIT 11

/* Length/Count-Define of TOURPLANTAGWOCHE ************************************/

  #define LS_TOURPLANTAGWOCHE_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_TOURPLANTAGWOCHE_KUNDENNR 10 + 1
  #define LS_TOURPLANTAGWOCHE_TOURID 6 + 1
  #define LS_TOURPLANTAGWOCHE_TAGESTYP 6 + 1
  #define LS_TOURPLANTAGWOCHE_WEEKDAY 5 + 1
  #define LS_TOURPLANTAGWOCHE_ISTVERBUNDTOUR 1 + 1
  #define LS_TOURPLANTAGWOCHE_KDAUFTRAGART 2 + 1
  #define LS_TOURPLANTAGWOCHE_FAHRTZEIT 10 + 1

  #define TOURPLANTAGWOCHEVERTRIEBSZENTRUMNR 0
  #define TOURPLANTAGWOCHEKUNDENNR 1
  #define TOURPLANTAGWOCHETOURID 2
  #define TOURPLANTAGWOCHETAGESTYP 3
  #define TOURPLANTAGWOCHEWEEKDAY 4
  #define TOURPLANTAGWOCHEISTVERBUNDTOUR 5
  #define TOURPLANTAGWOCHEKDAUFTRAGART 6
  #define TOURPLANTAGWOCHEFAHRTZEIT 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define TOURPLANTAGWOCHE_H
 #define TOURPLANTAGWOCHE_ANZ ( sizeof(TOURPLANTAGWOCHE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TOURPLANTAGWOCHE **********************************************/

 #define TOURPLANTAGWOCHE_LISTE \
         TOURPLANTAGWOCHE.VERTRIEBSZENTRUMNR,\
         TOURPLANTAGWOCHE.KUNDENNR,\
         TOURPLANTAGWOCHE.TOURID,\
         TOURPLANTAGWOCHE.TAGESTYP,\
         TOURPLANTAGWOCHE.WEEKDAY,\
         TOURPLANTAGWOCHE.ISTVERBUNDTOUR,\
         TOURPLANTAGWOCHE.KDAUFTRAGART,\
         TOURPLANTAGWOCHE.FAHRTZEIT

 #define TOURPLANTAGWOCHE_LISTE_390 \
         VERTRIEBSZENTRUMNR,\
         KUNDENNR,\
         TOURID,\
         TAGESTYP,\
         WEEKDAY,\
         ISTVERBUNDTOUR,\
         KDAUFTRAGART,\
         FAHRTZEIT

 #define TOURPLANTAGWOCHE_PLISTE \
         "TOURPLANTAGWOCHE.VERTRIEBSZENTRUMNR,"\
         "TOURPLANTAGWOCHE.KUNDENNR,"\
         "TOURPLANTAGWOCHE.TOURID,"\
         "TOURPLANTAGWOCHE.TAGESTYP,"\
         "TOURPLANTAGWOCHE.WEEKDAY,"\
         "TOURPLANTAGWOCHE.ISTVERBUNDTOUR,"\
         "TOURPLANTAGWOCHE.KDAUFTRAGART,"\
         "TOURPLANTAGWOCHE.FAHRTZEIT"

 #define TOURPLANTAGWOCHE_PELISTE \
         "VERTRIEBSZENTRUMNR,"\
         "KUNDENNR,"\
         "TOURID,"\
         "TAGESTYP,"\
         "WEEKDAY,"\
         "ISTVERBUNDTOUR,"\
         "KDAUFTRAGART,"\
         "FAHRTZEIT"

 #define TOURPLANTAGWOCHE_UPDLISTE \
         "VERTRIEBSZENTRUMNR=?,"\
         "KUNDENNR=?,"\
         "TOURID=?,"\
         "TAGESTYP=?,"\
         "WEEKDAY=?,"\
         "ISTVERBUNDTOUR=?,"\
         "KDAUFTRAGART=?,"\
         "FAHRTZEIT=?"

/* SqlMacros-Define of TOURPLANTAGWOCHE ***************************************/

 #define TOURPLANTAGWOCHE_ZEIGER(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TOURID,\
         :x->TAGESTYP,\
         :x->WEEKDAY,\
         :x->ISTVERBUNDTOUR,\
         :x->KDAUFTRAGART,\
         :x->FAHRTZEIT

 #define TOURPLANTAGWOCHE_ZEIGERSEL(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TOURID,\
         :x->TAGESTYP,\
         :x->WEEKDAY,\
         :x->ISTVERBUNDTOUR,\
         :x->KDAUFTRAGART,\
         :x->FAHRTZEIT

 #define TOURPLANTAGWOCHE_UPDATE(x) \
         TOURPLANTAGWOCHE.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         TOURPLANTAGWOCHE.KUNDENNR=:x->KUNDENNR,\
         TOURPLANTAGWOCHE.TOURID=:x->TOURID,\
         TOURPLANTAGWOCHE.TAGESTYP=:x->TAGESTYP,\
         TOURPLANTAGWOCHE.WEEKDAY=:x->WEEKDAY,\
         TOURPLANTAGWOCHE.ISTVERBUNDTOUR=:x->ISTVERBUNDTOUR,\
         TOURPLANTAGWOCHE.KDAUFTRAGART=:x->KDAUFTRAGART,\
         TOURPLANTAGWOCHE.FAHRTZEIT=:x->FAHRTZEIT

/* SqlMacros390-Define of TOURPLANTAGWOCHE ************************************/

 #define TOURPLANTAGWOCHE_ZEIGER_390 \
         :VERTRIEBSZENTRUMNR,\
         :KUNDENNR,\
         :TOURID,\
         :TAGESTYP,\
         :WEEKDAY,\
         :ISTVERBUNDTOUR,\
         :KDAUFTRAGART,\
         :FAHRTZEIT

 #define TOURPLANTAGWOCHE_UPDATE_390 \
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         KUNDENNR=:KUNDENNR,\
         TOURID=:TOURID,\
         TAGESTYP=:TAGESTYP,\
         WEEKDAY=:WEEKDAY,\
         ISTVERBUNDTOUR=:ISTVERBUNDTOUR,\
         KDAUFTRAGART=:KDAUFTRAGART,\
         FAHRTZEIT=:FAHRTZEIT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of TOURPLANTAGWOCHE ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_TOURPLANTAGWOCHE {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         char TAGESTYP[7];
         short WEEKDAY;
         char ISTVERBUNDTOUR[2];
         char KDAUFTRAGART[3];
         long FAHRTZEIT;
        } tourplantagwocheS;
 #else /*TRANSCLASS*/
 typedef struct N_TOURPLANTAGWOCHE {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         char TAGESTYP[7];
         short WEEKDAY;
         char ISTVERBUNDTOUR[2];
         char KDAUFTRAGART[3];
         long FAHRTZEIT;

			bool operator==(const N_TOURPLANTAGWOCHE& right) const {
			return(
				VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
				KUNDENNR == right.KUNDENNR &&
				!strcmp(TOURID, right.TOURID) &&
				!strcmp(TAGESTYP, right.TAGESTYP) &&
				WEEKDAY == right.WEEKDAY &&
				!strcmp(ISTVERBUNDTOUR, right.ISTVERBUNDTOUR) &&
				!strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
				FAHRTZEIT == right.FAHRTZEIT
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
				WEEKDAY = 0;
				strcpy(ISTVERBUNDTOUR, " " );
				strcpy(KDAUFTRAGART, " " );
				FAHRTZEIT = 0;
#endif
			}
         } tourplantagwocheS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TOURPLANTAGWOCHE **********************************/

 struct S_TOURPLANTAGWOCHE {
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char TOURID[6 + 1];
         char TAGESTYP[6 + 1];
         char WEEKDAY[7];
         char ISTVERBUNDTOUR[1 + 1];
         char KDAUFTRAGART[2 + 1];
         char FAHRTZEIT[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TOURPLANTAGWOCHE *****************/

 struct O_TOURPLANTAGWOCHE {
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char TOURID[6];
         char TAGESTYP[6];
         char WEEKDAY[7];
         char ISTVERBUNDTOUR[1];
         char KDAUFTRAGART[2];
         char FAHRTZEIT[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TOURPLANTAGWOCHE ****************************/

 struct C_TOURPLANTAGWOCHE {
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         char TOURID[7];
         char TAGESTYP[7];
         short WEEKDAY;
         char ISTVERBUNDTOUR;
         char KDAUFTRAGART[3];
         long FAHRTZEIT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TOURPLANTAGWOCHE **************************/

 struct I_TOURPLANTAGWOCHE {
         short VERTRIEBSZENTRUMNR;
         short KUNDENNR;
         short TOURID;
         short TAGESTYP;
         short WEEKDAY;
         short ISTVERBUNDTOUR;
         short KDAUFTRAGART;
         short FAHRTZEIT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TOURPLANTAGWOCHE ************************************/

#if defined (BUF_DESC)
 static struct buf_desc TOURPLANTAGWOCHE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TOURPLANTAGWOCHE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 6, 0 },
   { TYP_C, 6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of TOURPLANTAGWOCHE ******************************/

 #define TOURPLANTAGWOCHE_S390 \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         char TOURID[7]; \
         char TAGESTYP[7]; \
         short WEEKDAY; \
         char ISTVERBUNDTOUR; \
         char KDAUFTRAGART[3]; \
         long FAHRTZEIT; \



/* Copy-Function Struct to single Data TOURPLANTAGWOCHE ***********************/

 #define TOURPLANTAGWOCHE_S390_COPY_TO_SINGLE(_x_) \
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
          strcpy(TOURID,_x_->TOURID);\
          strcpy(TAGESTYP,_x_->TAGESTYP);\
         WEEKDAY=_x_->WEEKDAY;\
         ISTVERBUNDTOUR=_x_->ISTVERBUNDTOUR;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         FAHRTZEIT=_x_->FAHRTZEIT;\

 #define TOURPLANTAGWOCHE_S390_COPY_TO_STRUCT(_x_) \
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          strcpy(_x_->TOURID,TOURID);\
          strcpy(_x_->TAGESTYP,TAGESTYP);\
          _x_->WEEKDAY=WEEKDAY;\
          _x_->ISTVERBUNDTOUR=ISTVERBUNDTOUR;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->FAHRTZEIT=FAHRTZEIT;\



/* FunctionNumber-Define of tourplantagwoche **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of tourplantagwoche ******************************/


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

class CTOURPLANTAGWOCHE : public ppDadeVirtual
{
	//data members
	public:
		tourplantagwocheS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<tourplantagwocheS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<tourplantagwocheS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<tourplantagwocheS>; Strip(s); tourplantagwocheS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<tourplantagwocheS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<tourplantagwocheS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<tourplantagwocheS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetVertriebszentrumnr() const	{ return s.VERTRIEBSZENTRUMNR; }
		long		GetKundennr() const	{ return s.KUNDENNR; }
		const char*	GetTourid(ppString& t) const 	{ t = s.TOURID; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetTagestyp(ppString& t) const 	{ t = s.TAGESTYP; t.erasespace(ppString::END); return t.c_str(); }
		short		GetWeekday() const	{ return s.WEEKDAY; }
		char		GetIstverbundtour() const	{ return s.ISTVERBUNDTOUR[0]; }
		const char*	GetKdauftragart(ppString& t) const 	{ t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
		long		GetFahrtzeit() const	{ return s.FAHRTZEIT; }
		const tourplantagwocheS& GetStruct() const { return s; }
		void 		SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
		void 		SetKundennr(long t) { s.KUNDENNR = t; }
		void 		SetTourid(const ppString& t) { ppGStrCopy(s.TOURID,t.c_str() ,L_TOURPLANTAGWOCHE_TOURID); }
		void 		SetTagestyp(const ppString& t) { ppGStrCopy(s.TAGESTYP,t.c_str() ,L_TOURPLANTAGWOCHE_TAGESTYP); }
		void 		SetWeekday(short t) { s.WEEKDAY = t; }
		void 		SetIstverbundtour(char t) { s.ISTVERBUNDTOUR[0] = t; s.ISTVERBUNDTOUR[1] = '\0';}
		void 		SetKdauftragart(const ppString& t) { ppGStrCopy(s.KDAUFTRAGART,t.c_str() ,L_TOURPLANTAGWOCHE_KDAUFTRAGART); }
		void 		SetFahrtzeit(long t) { s.FAHRTZEIT = t; }
		void 		SetStruct(const tourplantagwocheS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CTOURPLANTAGWOCHE()  //constructor
		{
			::buf_default((void *)&s, TOURPLANTAGWOCHE_BES, TOURPLANTAGWOCHE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CTOURPLANTAGWOCHE()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, TOURPLANTAGWOCHE_BES, TOURPLANTAGWOCHE_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, TOURPLANTAGWOCHE_BES, TOURPLANTAGWOCHE_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, TOURPLANTAGWOCHE_BES, TOURPLANTAGWOCHE_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_TOURPLANTAGWOCHE& d)
		{
#ifdef WIN32
			ppGStripLast(d.TOURID);
			ppGStripLast(d.TAGESTYP);
			ppGStripLast(d.KDAUFTRAGART);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, TOURPLANTAGWOCHE_BES, TOURPLANTAGWOCHE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of TOURPLANTAGWOCHE *************************************/

 #define TOURPLANTAGWOCHE_CREATE(x) exec sql create table x (\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         TOURID char(6) default " " not null,\
         TAGESTYP char(6) default " " not null,\
         WEEKDAY smallint default 0 not null,\
         ISTVERBUNDTOUR char(1) default " " not null,\
         KDAUFTRAGART char(2) default " " not null,\
         FAHRTZEIT integer default 0 not null) in ksc extent size 5492 next size 552 lock mode row;



/* CreateIndexStatement of TOURPLANTAGWOCHE ***********************************/

 #define TOURPLANTAGWOCHE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_tourtagwoche_1 on _X_(\
              VertriebszentrumNr,\
              KundenNr,\
              weekday,\
              tourid ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TOURPLANTAGWOCHE ***********************************/

 #define TOURPLANTAGWOCHE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_tourtagwoche_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

#ifndef __PP_TLAGREV_H_
#define __PP_TLAGREV_H_

/******************************************************************************/
/* u:tlagrev ******************************************************************/
/******************************************************************************/

/* Length-Define of LAGERREVISION *********************************************/

  #define L_LAGERREVISION_FILIALNR 6
  #define L_LAGERREVISION_ARTIKEL_NR 11
  #define L_LAGERREVISION_DATUM 11
  #define L_LAGERREVISION_UHRZEIT 11
  #define L_LAGERREVISION_BESTANDKSC 11
  #define L_LAGERREVISION_BESTANDVSE 11

/* Length/Count-Define of LAGERREVISION ***************************************/

  #define LS_LAGERREVISION_FILIALNR 5 + 1
  #define LS_LAGERREVISION_ARTIKEL_NR 10 + 1
  #define LS_LAGERREVISION_DATUM 10 + 1
  #define LS_LAGERREVISION_UHRZEIT 10 + 1
  #define LS_LAGERREVISION_BESTANDKSC 10 + 1
  #define LS_LAGERREVISION_BESTANDVSE 10 + 1

  #define LAGERREVISIONFILIALNR 0
  #define LAGERREVISIONARTIKEL_NR 1
  #define LAGERREVISIONDATUM 2
  #define LAGERREVISIONUHRZEIT 3
  #define LAGERREVISIONBESTANDKSC 4
  #define LAGERREVISIONBESTANDVSE 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define LAGERREVISION_H
 #define LAGERREVISION_ANZ ( sizeof(LAGERREVISION_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of LAGERREVISION *************************************************/

 #define LAGERREVISION_LISTE \
         LAGERREVISION.FILIALNR,\
         LAGERREVISION.ARTIKEL_NR,\
         LAGERREVISION.DATUM,\
         LAGERREVISION.UHRZEIT,\
         LAGERREVISION.BESTANDKSC,\
         LAGERREVISION.BESTANDVSE

 #define LAGERREVISION_LISTE_390 \
         FILIALNR,\
         ARTIKEL_NR,\
         DATUM,\
         UHRZEIT,\
         BESTANDKSC,\
         BESTANDVSE

 #define LAGERREVISION_PLISTE \
         "LAGERREVISION.FILIALNR,"\
         "LAGERREVISION.ARTIKEL_NR,"\
         "LAGERREVISION.DATUM,"\
         "LAGERREVISION.UHRZEIT,"\
         "LAGERREVISION.BESTANDKSC,"\
         "LAGERREVISION.BESTANDVSE"

 #define LAGERREVISION_PELISTE \
         "FILIALNR,"\
         "ARTIKEL_NR,"\
         "DATUM,"\
         "UHRZEIT,"\
         "BESTANDKSC,"\
         "BESTANDVSE"

 #define LAGERREVISION_UPDLISTE \
         "FILIALNR=?,"\
         "ARTIKEL_NR=?,"\
         "DATUM=?,"\
         "UHRZEIT=?,"\
         "BESTANDKSC=?,"\
         "BESTANDVSE=?"

/* SqlMacros-Define of LAGERREVISION ******************************************/

 #define LAGERREVISION_ZEIGER(x) \
         :x->FILIALNR,\
         :x->ARTIKEL_NR,\
         :x->DATUM,\
         :x->UHRZEIT,\
         :x->BESTANDKSC,\
         :x->BESTANDVSE

 #define LAGERREVISION_ZEIGERSEL(x) \
         :x->FILIALNR,\
         :x->ARTIKEL_NR,\
         :x->DATUM,\
         :x->UHRZEIT,\
         :x->BESTANDKSC,\
         :x->BESTANDVSE

 #define LAGERREVISION_UPDATE(x) \
         LAGERREVISION.FILIALNR=:x->FILIALNR,\
         LAGERREVISION.ARTIKEL_NR=:x->ARTIKEL_NR,\
         LAGERREVISION.DATUM=:x->DATUM,\
         LAGERREVISION.UHRZEIT=:x->UHRZEIT,\
         LAGERREVISION.BESTANDKSC=:x->BESTANDKSC,\
         LAGERREVISION.BESTANDVSE=:x->BESTANDVSE

/* SqlMacros390-Define of LAGERREVISION ***************************************/

 #define LAGERREVISION_ZEIGER_390 \
         :FILIALNR,\
         :ARTIKEL_NR,\
         :DATUM,\
         :UHRZEIT,\
         :BESTANDKSC,\
         :BESTANDVSE

 #define LAGERREVISION_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         ARTIKEL_NR=:ARTIKEL_NR,\
         DATUM=:DATUM,\
         UHRZEIT=:UHRZEIT,\
         BESTANDKSC=:BESTANDKSC,\
         BESTANDVSE=:BESTANDVSE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of LAGERREVISION ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_LAGERREVISION {
         short FILIALNR;
         long ARTIKEL_NR;
         long DATUM;
         long UHRZEIT;
         long BESTANDKSC;
         long BESTANDVSE;
        } lagerrevisionS;
 #else /*TRANSCLASS*/
 typedef struct N_LAGERREVISION {
         short FILIALNR;
         long ARTIKEL_NR;
         long DATUM;
         long UHRZEIT;
         long BESTANDKSC;
         long BESTANDVSE;

			bool operator==(const N_LAGERREVISION& right) const {
			return(
				FILIALNR == right.FILIALNR &&
				ARTIKEL_NR == right.ARTIKEL_NR &&
				DATUM == right.DATUM &&
				UHRZEIT == right.UHRZEIT &&
				BESTANDKSC == right.BESTANDKSC &&
				BESTANDVSE == right.BESTANDVSE
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				FILIALNR = 0;
				ARTIKEL_NR = 0;
				DATUM = 0;
				UHRZEIT = 0;
				BESTANDKSC = 0;
				BESTANDVSE = 0;
#endif
			}
         } lagerrevisionS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of LAGERREVISION *************************************/

 struct S_LAGERREVISION {
         char FILIALNR[7];
         char ARTIKEL_NR[11];
         char DATUM[11];
         char UHRZEIT[11];
         char BESTANDKSC[11];
         char BESTANDVSE[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of LAGERREVISION ********************/

 struct O_LAGERREVISION {
         char FILIALNR[7];
         char ARTIKEL_NR[11];
         char DATUM[11];
         char UHRZEIT[11];
         char BESTANDKSC[11];
         char BESTANDVSE[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of LAGERREVISION ********************************/

 struct C_LAGERREVISION {
         short FILIALNR;
         long ARTIKEL_NR;
         long DATUM;
         long UHRZEIT;
         long BESTANDKSC;
         long BESTANDVSE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of LAGERREVISION ******************************/

 struct I_LAGERREVISION {
         short FILIALNR;
         short ARTIKEL_NR;
         short DATUM;
         short UHRZEIT;
         short BESTANDKSC;
         short BESTANDVSE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of LAGERREVISION ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc LAGERREVISION_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc LAGERREVISION_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of LAGERREVISION *********************************/

 #define LAGERREVISION_S390 \
         short FILIALNR; \
         long ARTIKEL_NR; \
         long DATUM; \
         long UHRZEIT; \
         long BESTANDKSC; \
         long BESTANDVSE; \



/* Copy-Function Struct to single Data LAGERREVISION **************************/

 #define LAGERREVISION_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         DATUM=_x_->DATUM;\
         UHRZEIT=_x_->UHRZEIT;\
         BESTANDKSC=_x_->BESTANDKSC;\
         BESTANDVSE=_x_->BESTANDVSE;\

 #define LAGERREVISION_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->DATUM=DATUM;\
          _x_->UHRZEIT=UHRZEIT;\
          _x_->BESTANDKSC=BESTANDKSC;\
          _x_->BESTANDVSE=BESTANDVSE;\



/* FunctionNumber-Define of lagerrevision *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of lagerrevision *********************************/


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
		virtual int SelList(int FetchRel = 1,int pos=0)	{ return 1; }
		virtual int SelListHist(int FetchRel = 1,int pos=0)	{ return 1; }
		virtual int SelListFuture(int FetchRel = 1,int pos=0)	{ return 1; }
};
#endif

class CLAGERREVISION : public ppDadeVirtual
{
	//data members
	public:
		lagerrevisionS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<lagerrevisionS> *pl; // pointer to class list

	//functions
	public:

		const int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) {	if (GetSize() <= i)	return false; vector<lagerrevisionS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<lagerrevisionS>; Strip(s); lagerrevisionS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<lagerrevisionS>::iterator itPtr = pl->begin() + i; if ( itPtr ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<lagerrevisionS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<lagerrevisionS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const short		GetFilialnr() const	{ return s.FILIALNR; }
		const long		GetArtikel_nr() const	{ return s.ARTIKEL_NR; }
		const long		GetDatum() const	{ return s.DATUM; }
		const long		GetUhrzeit() const	{ return s.UHRZEIT; }
		const long		GetBestandksc() const	{ return s.BESTANDKSC; }
		const long		GetBestandvse() const	{ return s.BESTANDVSE; }
		const lagerrevisionS& GetStruct() const { return s; }
		void 		SetFilialnr(short t) { s.FILIALNR = t; }
		void 		SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
		void 		SetDatum(long t) { s.DATUM = t; }
		void 		SetUhrzeit(long t) { s.UHRZEIT = t; }
		void 		SetBestandksc(long t) { s.BESTANDKSC = t; }
		void 		SetBestandvse(long t) { s.BESTANDVSE = t; }
		void 		SetStruct(const lagerrevisionS& t) { s = t; }

		CLAGERREVISION()  //constructor
		{
			::buf_default((void *)&s,LAGERREVISION_BES,LAGERREVISION_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		~CLAGERREVISION()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, LAGERREVISION_BES, LAGERREVISION_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_LAGERREVISION& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,LAGERREVISION_BES,LAGERREVISION_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of LAGERREVISION ****************************************/

 #define LAGERREVISION_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         ARTIKEL_NR integer default 0 not null,\
         DATUM integer default 0 not null,\
         UHRZEIT integer default 0 not null,\
         BESTANDKSC integer default 0 not null,\
         BESTANDVSE integer default 0 not null) in zp extent size 8 lock mode row;



/* CreateIndexStatement of LAGERREVISION **************************************/

 #define LAGERREVISION_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_LagerRevision_1 on _X_(\
              filialnr,\
              artikel_nr ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of LAGERREVISION **************************************/

 #define LAGERREVISION_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_LagerRevision_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

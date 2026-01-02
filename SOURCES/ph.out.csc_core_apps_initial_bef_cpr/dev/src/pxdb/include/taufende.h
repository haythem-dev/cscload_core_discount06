#ifndef __PP_TAUFENDE_H_
#define __PP_TAUFENDE_H_

/******************************************************************************/
/* c:\phosix\taufende *********************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGENDEZEIT *****************************************/

  #define L_KDAUFTRAGENDEZEIT_FILIALNR 6
  #define L_KDAUFTRAGENDEZEIT_BATCHSCHREIBEN 11
  #define L_KDAUFTRAGENDEZEIT_HERKUNFTSFILIALNR 6
  #define L_KDAUFTRAGENDEZEIT_ABSCHLUSSMODUS 6
  #define L_KDAUFTRAGENDEZEIT_ABSCHLUSSZEIT 11

/* Length/Count-Define of KDAUFTRAGENDEZEIT ***********************************/

  #define LS_KDAUFTRAGENDEZEIT_FILIALNR 5 + 1
  #define LS_KDAUFTRAGENDEZEIT_BATCHSCHREIBEN 10 + 1
  #define LS_KDAUFTRAGENDEZEIT_HERKUNFTSFILIALNR 5 + 1
  #define LS_KDAUFTRAGENDEZEIT_ABSCHLUSSMODUS 5 + 1
  #define LS_KDAUFTRAGENDEZEIT_ABSCHLUSSZEIT 10 + 1

  #define KDAUFTRAGENDEZEITFILIALNR 0
  #define KDAUFTRAGENDEZEITBATCHSCHREIBEN 1
  #define KDAUFTRAGENDEZEITHERKUNFTSFILIALNR 2
  #define KDAUFTRAGENDEZEITABSCHLUSSMODUS 3
  #define KDAUFTRAGENDEZEITABSCHLUSSZEIT 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGENDEZEIT_H
 #define KDAUFTRAGENDEZEIT_ANZ ( sizeof(KDAUFTRAGENDEZEIT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGENDEZEIT *********************************************/

 #define KDAUFTRAGENDEZEIT_LISTE \
         KDAUFTRAGENDEZEIT.FILIALNR,\
         KDAUFTRAGENDEZEIT.BATCHSCHREIBEN,\
         KDAUFTRAGENDEZEIT.HERKUNFTSFILIALNR,\
         KDAUFTRAGENDEZEIT.ABSCHLUSSMODUS,\
         KDAUFTRAGENDEZEIT.ABSCHLUSSZEIT

 #define KDAUFTRAGENDEZEIT_LISTE_390 \
         FILIALNR,\
         BATCHSCHREIBEN,\
         HERKUNFTSFILIALNR,\
         ABSCHLUSSMODUS,\
         ABSCHLUSSZEIT

 #define KDAUFTRAGENDEZEIT_PLISTE \
         "KDAUFTRAGENDEZEIT.FILIALNR,"\
         "KDAUFTRAGENDEZEIT.BATCHSCHREIBEN,"\
         "KDAUFTRAGENDEZEIT.HERKUNFTSFILIALNR,"\
         "KDAUFTRAGENDEZEIT.ABSCHLUSSMODUS,"\
         "KDAUFTRAGENDEZEIT.ABSCHLUSSZEIT"

 #define KDAUFTRAGENDEZEIT_PELISTE \
         "FILIALNR,"\
         "BATCHSCHREIBEN,"\
         "HERKUNFTSFILIALNR,"\
         "ABSCHLUSSMODUS,"\
         "ABSCHLUSSZEIT"

 #define KDAUFTRAGENDEZEIT_UPDLISTE \
         "FILIALNR=?,"\
         "BATCHSCHREIBEN=?,"\
         "HERKUNFTSFILIALNR=?,"\
         "ABSCHLUSSMODUS=?,"\
         "ABSCHLUSSZEIT=?"

/* SqlMacros-Define of KDAUFTRAGENDEZEIT **************************************/

 #define KDAUFTRAGENDEZEIT_ZEIGER(x) \
         :x->FILIALNR,\
         :x->BATCHSCHREIBEN,\
         :x->HERKUNFTSFILIALNR,\
         :x->ABSCHLUSSMODUS,\
         :x->ABSCHLUSSZEIT

 #define KDAUFTRAGENDEZEIT_UPDATE(x) \
         KDAUFTRAGENDEZEIT.FILIALNR=:x->FILIALNR,\
         KDAUFTRAGENDEZEIT.BATCHSCHREIBEN=:x->BATCHSCHREIBEN,\
         KDAUFTRAGENDEZEIT.HERKUNFTSFILIALNR=:x->HERKUNFTSFILIALNR,\
         KDAUFTRAGENDEZEIT.ABSCHLUSSMODUS=:x->ABSCHLUSSMODUS,\
         KDAUFTRAGENDEZEIT.ABSCHLUSSZEIT=:x->ABSCHLUSSZEIT

/* SqlMacros390-Define of KDAUFTRAGENDEZEIT ***********************************/

 #define KDAUFTRAGENDEZEIT_ZEIGER_390 \
         :FILIALNR,\
         :BATCHSCHREIBEN,\
         :HERKUNFTSFILIALNR,\
         :ABSCHLUSSMODUS,\
         :ABSCHLUSSZEIT

 #define KDAUFTRAGENDEZEIT_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         BATCHSCHREIBEN=:BATCHSCHREIBEN,\
         HERKUNFTSFILIALNR=:HERKUNFTSFILIALNR,\
         ABSCHLUSSMODUS=:ABSCHLUSSMODUS,\
         ABSCHLUSSZEIT=:ABSCHLUSSZEIT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGENDEZEIT **************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGENDEZEIT {
         short FILIALNR;
         long BATCHSCHREIBEN;
         short HERKUNFTSFILIALNR;
         short ABSCHLUSSMODUS;
         long ABSCHLUSSZEIT;
        } kdauftragendezeitS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGENDEZEIT {
         short FILIALNR;
         long BATCHSCHREIBEN;
         short HERKUNFTSFILIALNR;
         short ABSCHLUSSMODUS;
         long ABSCHLUSSZEIT;

			bool operator==(const N_KDAUFTRAGENDEZEIT& right) const {
			return(
				FILIALNR == right.FILIALNR &&
				BATCHSCHREIBEN == right.BATCHSCHREIBEN &&
				HERKUNFTSFILIALNR == right.HERKUNFTSFILIALNR &&
				ABSCHLUSSMODUS == right.ABSCHLUSSMODUS &&
				ABSCHLUSSZEIT == right.ABSCHLUSSZEIT
				);
			}
			void clear() { memset((char*)this,0,sizeof(*this)); }
         } kdauftragendezeitS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGENDEZEIT *********************************/

 struct S_KDAUFTRAGENDEZEIT {
         char FILIALNR[7];
         char BATCHSCHREIBEN[11];
         char HERKUNFTSFILIALNR[7];
         char ABSCHLUSSMODUS[7];
         char ABSCHLUSSZEIT[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGENDEZEIT ****************/

 struct O_KDAUFTRAGENDEZEIT {
         char FILIALNR[7];
         char BATCHSCHREIBEN[11];
         char HERKUNFTSFILIALNR[7];
         char ABSCHLUSSMODUS[7];
         char ABSCHLUSSZEIT[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of KDAUFTRAGENDEZEIT ****************************/

 struct C_KDAUFTRAGENDEZEIT {
         short FILIALNR;
         long BATCHSCHREIBEN;
         short HERKUNFTSFILIALNR;
         short ABSCHLUSSMODUS;
         long ABSCHLUSSZEIT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of KDAUFTRAGENDEZEIT **************************/

 struct I_KDAUFTRAGENDEZEIT {
         short FILIALNR;
         short BATCHSCHREIBEN;
         short HERKUNFTSFILIALNR;
         short ABSCHLUSSMODUS;
         short ABSCHLUSSZEIT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGENDEZEIT ***********************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGENDEZEIT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGENDEZEIT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGENDEZEIT *****************************/

 #define KDAUFTRAGENDEZEIT_S390 \
         short FILIALNR; \
         long BATCHSCHREIBEN; \
         short HERKUNFTSFILIALNR; \
         short ABSCHLUSSMODUS; \
         long ABSCHLUSSZEIT; \



/* Copy-Function Struct to single Data KDAUFTRAGENDEZEIT **********************/

 #define KDAUFTRAGENDEZEIT_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
         BATCHSCHREIBEN=_x_->BATCHSCHREIBEN;\
         HERKUNFTSFILIALNR=_x_->HERKUNFTSFILIALNR;\
         ABSCHLUSSMODUS=_x_->ABSCHLUSSMODUS;\
         ABSCHLUSSZEIT=_x_->ABSCHLUSSZEIT;\

 #define KDAUFTRAGENDEZEIT_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          _x_->BATCHSCHREIBEN=BATCHSCHREIBEN;\
          _x_->HERKUNFTSFILIALNR=HERKUNFTSFILIALNR;\
          _x_->ABSCHLUSSMODUS=ABSCHLUSSMODUS;\
          _x_->ABSCHLUSSZEIT=ABSCHLUSSZEIT;\



/* FunctionNumber-Define of kdauftragendezeit *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragendezeit *****************************/


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

class CKDAUFTRAGENDEZEIT : public ppDadeVirtual
{
	//data members
	public:
		kdauftragendezeitS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kdauftragendezeitS> *pl; // pointer to class list

	//functions
	public:

		const int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) {	if (GetSize() <= i)	return false; vector<kdauftragendezeitS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kdauftragendezeitS>; Strip(s); kdauftragendezeitS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragendezeitS>::iterator itPtr = pl->begin() + i; if ( itPtr ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kdauftragendezeitS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kdauftragendezeitS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const short&		GetFilialnr() const	{ return s.FILIALNR; }
		const long&		GetBatchschreiben() const	{ return s.BATCHSCHREIBEN; }
		const short&		GetHerkunftsfilialnr() const	{ return s.HERKUNFTSFILIALNR; }
		const short&		GetAbschlussmodus() const	{ return s.ABSCHLUSSMODUS; }
		const long&		GetAbschlusszeit() const	{ return s.ABSCHLUSSZEIT; }
		const kdauftragendezeitS& GetStruct() const { return s; }
		void 		SetFilialnr(short t) { s.FILIALNR = t; }
		void 		SetBatchschreiben(long t) { s.BATCHSCHREIBEN = t; }
		void 		SetHerkunftsfilialnr(short t) { s.HERKUNFTSFILIALNR = t; }
		void 		SetAbschlussmodus(short t) { s.ABSCHLUSSMODUS = t; }
		void 		SetAbschlusszeit(long t) { s.ABSCHLUSSZEIT = t; }
		void 		SetStruct(const kdauftragendezeitS& t) { s = t; }

		CKDAUFTRAGENDEZEIT()  //constructor
		{
			::buf_default((void *)&s,KDAUFTRAGENDEZEIT_BES,KDAUFTRAGENDEZEIT_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		~CKDAUFTRAGENDEZEIT()  //destructor
		{
			if(pl) delete pl;
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KDAUFTRAGENDEZEIT_BES, KDAUFTRAGENDEZEIT_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_KDAUFTRAGENDEZEIT& d)
		{
		}

		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,KDAUFTRAGENDEZEIT_BES,KDAUFTRAGENDEZEIT_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KDAUFTRAGENDEZEIT ************************************/

 #define KDAUFTRAGENDEZEIT_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         BATCHSCHREIBEN integer default 0 not null,\
         HERKUNFTSFILIALNR smallint default 0 not null,\
         ABSCHLUSSMODUS smallint default 0 not null,\
         ABSCHLUSSZEIT integer default 0 not null) in zp extent size 8 lock mode row;



/* CreateIndexStatement of KDAUFTRAGENDEZEIT **********************************/

 #define KDAUFTRAGENDEZEIT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;
/* DeleteIndexStatement of KDAUFTRAGENDEZEIT **********************************/

 #define KDAUFTRAGENDEZEIT_DELETE_INDEX(_X_)\
              _X_ = 0;
#endif

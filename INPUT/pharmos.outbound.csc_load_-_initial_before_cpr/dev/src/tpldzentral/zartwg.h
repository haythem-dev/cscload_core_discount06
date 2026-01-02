#ifndef __PP_ZARTWG_H_
#define __PP_ZARTWG_H_

/******************************************************************************/
/* d:\prj\df\unix\tpldzentral\zartwg ******************************************/
/******************************************************************************/

/* Length-Define of ZARTWG ****************************************************/

  #define L_ZARTWG_ARTIKEL_NR 11
  #define L_ZARTWG_ART 1
  #define L_ZARTWG_WARENGRUPPE 5

/* Length/Count-Define of ZARTWG **********************************************/

  #define LS_ZARTWG_ARTIKEL_NR 10 + 1
  #define LS_ZARTWG_ART 1 + 1
  #define LS_ZARTWG_WARENGRUPPE 5 + 1

  #define ZARTWGARTIKEL_NR 0
  #define ZARTWGART 1
  #define ZARTWGWARENGRUPPE 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ZARTWG_H
 #define ZARTWG_ANZ ( sizeof(ZARTWG_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ZARTWG ********************************************************/

 #define ZARTWG_LISTE \
         ZARTWG.ARTIKEL_NR,\
         ZARTWG.ART,\
         ZARTWG.WARENGRUPPE

 #define ZARTWG_LISTE_390 \
         ARTIKEL_NR,\
         ART,\
         WARENGRUPPE

 #define ZARTWG_PLISTE \
         "ZARTWG.ARTIKEL_NR,"\
         "ZARTWG.ART,"\
         "ZARTWG.WARENGRUPPE"

 #define ZARTWG_PELISTE \
         "ARTIKEL_NR,"\
         "ART,"\
         "WARENGRUPPE"

 #define ZARTWG_UPDLISTE \
         "ARTIKEL_NR=?,"\
         "ART=?,"\
         "WARENGRUPPE=?"

/* SqlMacros-Define of ZARTWG *************************************************/

 #define ZARTWG_ZEIGER(x) \
         :x->ARTIKEL_NR,\
         :x->ART,\
         :x->WARENGRUPPE

 #define ZARTWG_ZEIGERSEL(x) \
         :x->ARTIKEL_NR,\
         :x->ART,\
         :x->WARENGRUPPE

 #define ZARTWG_UPDATE(x) \
         ZARTWG.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ZARTWG.ART=:x->ART,\
         ZARTWG.WARENGRUPPE=:x->WARENGRUPPE

/* SqlMacros390-Define of ZARTWG **********************************************/

 #define ZARTWG_ZEIGER_390 \
         :ARTIKEL_NR,\
         :ART,\
         :WARENGRUPPE

 #define ZARTWG_UPDATE_390 \
         ARTIKEL_NR=:ARTIKEL_NR,\
         ART=:ART,\
         WARENGRUPPE=:WARENGRUPPE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ZARTWG *************************************************/

 #ifndef TRANSCLASS
 typedef struct N_ZARTWG {
         long ARTIKEL_NR;
         char ART[2];
         char WARENGRUPPE[6];
        } zartwgS;
 #else /*TRANSCLASS*/
 typedef struct N_ZARTWG {
         long ARTIKEL_NR;
         char ART[2];
         char WARENGRUPPE[6];

			bool operator==(const N_ZARTWG& right) const {
			return(
				ARTIKEL_NR == right.ARTIKEL_NR &&
				!strcmp(ART, right.ART) &&
				!strcmp(WARENGRUPPE, right.WARENGRUPPE)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				ARTIKEL_NR = 0;
				strcpy(ART, " " );
				strcpy(WARENGRUPPE, " " );
#endif
			}
         } zartwgS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ZARTWG ********************************************/

 struct S_ZARTWG {
         char ARTIKEL_NR[11];
         char ART[1 + 1];
         char WARENGRUPPE[5 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ZARTWG ***************************/

 struct O_ZARTWG {
         char ARTIKEL_NR[11];
         char ART[1];
         char WARENGRUPPE[5];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of ZARTWG ***************************************/

 struct C_ZARTWG {
         long ARTIKEL_NR;
         char ART;
         char WARENGRUPPE[6];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of ZARTWG *************************************/

 struct I_ZARTWG {
         short ARTIKEL_NR;
         short ART;
         short WARENGRUPPE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ZARTWG **********************************************/

#if defined (BUF_DESC)
 static struct buf_desc ZARTWG_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 5, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ZARTWG_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 5, 0 },
 };
#endif

/* description for datatypes of ZARTWG ****************************************/

 #define ZARTWG_S390 \
         long ARTIKEL_NR; \
         char ART; \
         char WARENGRUPPE[6]; \



/* Copy-Function Struct to single Data ZARTWG *********************************/

 #define ZARTWG_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         ART=_x_->ART;\
          strcpy(WARENGRUPPE,_x_->WARENGRUPPE);\

 #define ZARTWG_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->ART=ART;\
          strcpy(_x_->WARENGRUPPE,WARENGRUPPE);\



/* FunctionNumber-Define of zartwg ********************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of zartwg ****************************************/


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
		virtual int SelList(int FetchRel = 1,int pos=0) = 0;
		virtual int SelListHist(int FetchRel = 1,int pos=0) = 0;
		virtual int SelListFuture(int FetchRel = 1,int pos=0) = 0;
		virtual int Load(int pos=0) = 0;
 		virtual int Delete(int pos=0) = 0;
		virtual int Save(int pos=0) = 0;
};
#endif

class CZARTWG : public ppDadeVirtual
{
	//data members
	public:
		zartwgS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<zartwgS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<zartwgS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<zartwgS>; Strip(s); zartwgS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<zartwgS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<zartwgS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<zartwgS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetArtikel_nr() const	{ return s.ARTIKEL_NR; }
		char		GetArt() const	{ return s.ART[0]; }
		const char*	GetWarengruppe(ppString& t) const 	{ t = s.WARENGRUPPE; t.erasespace(ppString::END); return t.c_str(); }
		const zartwgS& GetStruct() const { return s; }
		void 		SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
		void 		SetArt(char t) { s.ART[0] = t; s.ART[1] = '\0';}
		void 		SetWarengruppe(const ppString& t) { ppGStrCopy(s.WARENGRUPPE,t.c_str() ,L_ZARTWG_WARENGRUPPE); }
		void 		SetStruct(const zartwgS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CZARTWG()  //constructor
		{
			::buf_default((void *)&s,ZARTWG_BES,ZARTWG_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CZARTWG()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ZARTWG_BES, ZARTWG_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc=::ServerNr(pos, fkt_nr, (void *)&s,ZARTWG_BES,ZARTWG_ANZ, error_msg);
			#else
			rc=::Server(fkt_nr, (void *)&s,ZARTWG_BES,ZARTWG_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_ZARTWG& d)
		{
#ifdef WIN32
			ppGStripLast(d.WARENGRUPPE);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,ZARTWG_BES,ZARTWG_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of ZARTWG ***********************************************/

 #define ZARTWG_CREATE(x) exec sql create table x (\
         ARTIKEL_NR integer default 0 not null,\
         ART char(1) default " " not null,\
         WARENGRUPPE char(5) default " " not null) in phosix extent size 7844 next size 788 lock mode row;



/* CreateIndexStatement of ZARTWG *********************************************/

 #define ZARTWG_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_zartwg_1 on _X_(\
              artikel_nr,\
              art ) in phosix1;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_zartwg_3 on _X_(\
              art,\
              warengruppe ) in phosix1;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ZARTWG *********************************************/

 #define ZARTWG_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_zartwg_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_zartwg_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

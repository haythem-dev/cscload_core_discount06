#ifndef __PP_KDAUFTRAGPOSCHANGE_H_
#define __PP_KDAUFTRAGPOSCHANGE_H_

/******************************************************************************/
/* u:\kdauftragposchange ******************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGPOSCHANGE ****************************************/

  #define L_KDAUFTRAGPOSCHANGE_KDAUFTRAGNR 11
  #define L_KDAUFTRAGPOSCHANGE_POSNR 11
  #define L_KDAUFTRAGPOSCHANGE_MENGEBESTELLT 11
  #define L_KDAUFTRAGPOSCHANGE_MENGEBESTAETIGT 11
  #define L_KDAUFTRAGPOSCHANGE_MENGE_ALT 11
  #define L_KDAUFTRAGPOSCHANGE_SWCHECKED 1

/* Length/Count-Define of KDAUFTRAGPOSCHANGE **********************************/

  #define LS_KDAUFTRAGPOSCHANGE_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGPOSCHANGE_POSNR 10 + 1
  #define LS_KDAUFTRAGPOSCHANGE_MENGEBESTELLT 10 + 1
  #define LS_KDAUFTRAGPOSCHANGE_MENGEBESTAETIGT 10 + 1
  #define LS_KDAUFTRAGPOSCHANGE_MENGE_ALT 10 + 1
  #define LS_KDAUFTRAGPOSCHANGE_SWCHECKED 1 + 1

  #define KDAUFTRAGPOSCHANGEKDAUFTRAGNR 0
  #define KDAUFTRAGPOSCHANGEPOSNR 1
  #define KDAUFTRAGPOSCHANGEMENGEBESTELLT 2
  #define KDAUFTRAGPOSCHANGEMENGEBESTAETIGT 3
  #define KDAUFTRAGPOSCHANGEMENGE_ALT 4
  #define KDAUFTRAGPOSCHANGESWCHECKED 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGPOSCHANGE_H
 #define KDAUFTRAGPOSCHANGE_ANZ ( sizeof(KDAUFTRAGPOSCHANGE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPOSCHANGE ********************************************/

 #define KDAUFTRAGPOSCHANGE_LISTE \
         KDAUFTRAGPOSCHANGE.KDAUFTRAGNR,\
         KDAUFTRAGPOSCHANGE.POSNR,\
         KDAUFTRAGPOSCHANGE.MENGEBESTELLT,\
         KDAUFTRAGPOSCHANGE.MENGEBESTAETIGT,\
         KDAUFTRAGPOSCHANGE.MENGE_ALT,\
         KDAUFTRAGPOSCHANGE.SWCHECKED

 #define KDAUFTRAGPOSCHANGE_LISTE_390 \
         KDAUFTRAGNR,\
         POSNR,\
         MENGEBESTELLT,\
         MENGEBESTAETIGT,\
         MENGE_ALT,\
         SWCHECKED

 #define KDAUFTRAGPOSCHANGE_PLISTE \
         "KDAUFTRAGPOSCHANGE.KDAUFTRAGNR,"\
         "KDAUFTRAGPOSCHANGE.POSNR,"\
         "KDAUFTRAGPOSCHANGE.MENGEBESTELLT,"\
         "KDAUFTRAGPOSCHANGE.MENGEBESTAETIGT,"\
         "KDAUFTRAGPOSCHANGE.MENGE_ALT,"\
         "KDAUFTRAGPOSCHANGE.SWCHECKED"

 #define KDAUFTRAGPOSCHANGE_PELISTE \
         "KDAUFTRAGNR,"\
         "POSNR,"\
         "MENGEBESTELLT,"\
         "MENGEBESTAETIGT,"\
         "MENGE_ALT,"\
         "SWCHECKED"

 #define KDAUFTRAGPOSCHANGE_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "POSNR=?,"\
         "MENGEBESTELLT=?,"\
         "MENGEBESTAETIGT=?,"\
         "MENGE_ALT=?,"\
         "SWCHECKED=?"

/* SqlMacros-Define of KDAUFTRAGPOSCHANGE *************************************/

 #define KDAUFTRAGPOSCHANGE_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->MENGEBESTELLT,\
         :x->MENGEBESTAETIGT,\
         :x->MENGE_ALT,\
         :x->SWCHECKED

 #define KDAUFTRAGPOSCHANGE_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->MENGEBESTELLT,\
         :x->MENGEBESTAETIGT,\
         :x->MENGE_ALT,\
         :x->SWCHECKED

 #define KDAUFTRAGPOSCHANGE_UPDATE(x) \
         KDAUFTRAGPOSCHANGE.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGPOSCHANGE.POSNR=:x->POSNR,\
         KDAUFTRAGPOSCHANGE.MENGEBESTELLT=:x->MENGEBESTELLT,\
         KDAUFTRAGPOSCHANGE.MENGEBESTAETIGT=:x->MENGEBESTAETIGT,\
         KDAUFTRAGPOSCHANGE.MENGE_ALT=:x->MENGE_ALT,\
         KDAUFTRAGPOSCHANGE.SWCHECKED=:x->SWCHECKED

/* SqlMacros390-Define of KDAUFTRAGPOSCHANGE **********************************/

 #define KDAUFTRAGPOSCHANGE_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :POSNR,\
         :MENGEBESTELLT,\
         :MENGEBESTAETIGT,\
         :MENGE_ALT,\
         :SWCHECKED

 #define KDAUFTRAGPOSCHANGE_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         POSNR=:POSNR,\
         MENGEBESTELLT=:MENGEBESTELLT,\
         MENGEBESTAETIGT=:MENGEBESTAETIGT,\
         MENGE_ALT=:MENGE_ALT,\
         SWCHECKED=:SWCHECKED

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGPOSCHANGE *************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGPOSCHANGE {
         long KDAUFTRAGNR;
         long POSNR;
         long MENGEBESTELLT;
         long MENGEBESTAETIGT;
         long MENGE_ALT;
         char SWCHECKED[2];
        } kdauftragposchangeS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGPOSCHANGE {
         long KDAUFTRAGNR;
         long POSNR;
         long MENGEBESTELLT;
         long MENGEBESTAETIGT;
         long MENGE_ALT;
         char SWCHECKED[2];

			bool operator==(const N_KDAUFTRAGPOSCHANGE& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				POSNR == right.POSNR &&
				MENGEBESTELLT == right.MENGEBESTELLT &&
				MENGEBESTAETIGT == right.MENGEBESTAETIGT &&
				MENGE_ALT == right.MENGE_ALT &&
				!strcmp(SWCHECKED, right.SWCHECKED)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				POSNR = 0;
				MENGEBESTELLT = 0;
				MENGEBESTAETIGT = 0;
				MENGE_ALT = 0;
				strcpy(SWCHECKED, " " );
#endif
			}
         } kdauftragposchangeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPOSCHANGE ********************************/

 struct S_KDAUFTRAGPOSCHANGE {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char MENGEBESTELLT[11];
         char MENGEBESTAETIGT[11];
         char MENGE_ALT[11];
         char SWCHECKED[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPOSCHANGE ***************/

 struct O_KDAUFTRAGPOSCHANGE {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char MENGEBESTELLT[11];
         char MENGEBESTAETIGT[11];
         char MENGE_ALT[11];
         char SWCHECKED[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPOSCHANGE **************************/

 struct C_KDAUFTRAGPOSCHANGE {
         long KDAUFTRAGNR;
         long POSNR;
         long MENGEBESTELLT;
         long MENGEBESTAETIGT;
         long MENGE_ALT;
         char SWCHECKED;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPOSCHANGE ************************/

 struct I_KDAUFTRAGPOSCHANGE {
         short KDAUFTRAGNR;
         short POSNR;
         short MENGEBESTELLT;
         short MENGEBESTAETIGT;
         short MENGE_ALT;
         short SWCHECKED;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPOSCHANGE **********************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSCHANGE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSCHANGE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGPOSCHANGE ****************************/

 #define KDAUFTRAGPOSCHANGE_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         long MENGEBESTELLT; \
         long MENGEBESTAETIGT; \
         long MENGE_ALT; \
         char SWCHECKED; \



/* Copy-Function Struct to single Data KDAUFTRAGPOSCHANGE *********************/

 #define KDAUFTRAGPOSCHANGE_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         MENGEBESTELLT=_x_->MENGEBESTELLT;\
         MENGEBESTAETIGT=_x_->MENGEBESTAETIGT;\
         MENGE_ALT=_x_->MENGE_ALT;\
         SWCHECKED=_x_->SWCHECKED;\

 #define KDAUFTRAGPOSCHANGE_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->MENGEBESTELLT=MENGEBESTELLT;\
          _x_->MENGEBESTAETIGT=MENGEBESTAETIGT;\
          _x_->MENGE_ALT=MENGE_ALT;\
          _x_->SWCHECKED=SWCHECKED;\



/* FunctionNumber-Define of kdauftragposchange ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragposchange ****************************/


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

class CKDAUFTRAGPOSCHANGE : public ppDadeVirtual
{
	//data members
	public:
		kdauftragposchangeS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kdauftragposchangeS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragposchangeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kdauftragposchangeS>; Strip(s); kdauftragposchangeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragposchangeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kdauftragposchangeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kdauftragposchangeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		long		GetPosnr() const	{ return s.POSNR; }
		long		GetMengebestellt() const	{ return s.MENGEBESTELLT; }
		long		GetMengebestaetigt() const	{ return s.MENGEBESTAETIGT; }
		long		GetMenge_alt() const	{ return s.MENGE_ALT; }
		char		GetSwchecked() const	{ return s.SWCHECKED[0]; }
		const kdauftragposchangeS& GetStruct() const { return s; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetPosnr(long t) { s.POSNR = t; }
		void 		SetMengebestellt(long t) { s.MENGEBESTELLT = t; }
		void 		SetMengebestaetigt(long t) { s.MENGEBESTAETIGT = t; }
		void 		SetMenge_alt(long t) { s.MENGE_ALT = t; }
		void 		SetSwchecked(char t) { s.SWCHECKED[0] = t; s.SWCHECKED[1] = '\0';}
		void 		SetStruct(const kdauftragposchangeS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CKDAUFTRAGPOSCHANGE()  //constructor
		{
			::buf_default((void *)&s, KDAUFTRAGPOSCHANGE_BES, KDAUFTRAGPOSCHANGE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CKDAUFTRAGPOSCHANGE()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KDAUFTRAGPOSCHANGE_BES, KDAUFTRAGPOSCHANGE_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPOSCHANGE_BES, KDAUFTRAGPOSCHANGE_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPOSCHANGE_BES, KDAUFTRAGPOSCHANGE_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_KDAUFTRAGPOSCHANGE& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPOSCHANGE_BES, KDAUFTRAGPOSCHANGE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KDAUFTRAGPOSCHANGE ***********************************/

 #define KDAUFTRAGPOSCHANGE_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         MENGEBESTELLT integer default 0 not null,\
         MENGEBESTAETIGT integer default 0 not null,\
         MENGE_ALT integer default 0 not null,\
         SWCHECKED char(1) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPOSCHANGE *********************************/

 #define KDAUFTRAGPOSCHANGE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdaufposchange_1 on _X_(\
              kdauftragnr,\
              posnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPOSCHANGE *********************************/

 #define KDAUFTRAGPOSCHANGE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdaufposchange_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

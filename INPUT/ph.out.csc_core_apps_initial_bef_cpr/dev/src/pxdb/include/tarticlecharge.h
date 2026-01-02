#ifndef __PP_ARTICLECHARGE_H_
#define __PP_ARTICLECHARGE_H_

/******************************************************************************/
/* u:\ArticleCharge ***********************************************************/
/******************************************************************************/

/* Length-Define of ARTICLECHARGE *********************************************/

  #define L_ARTICLECHARGE_BRANCHNO 6
  #define L_ARTICLECHARGE_ARTICLENO 11
  #define L_ARTICLECHARGE_EXPIRYDATE 11
  #define L_ARTICLECHARGE_CHARGENNR 25
  #define L_ARTICLECHARGE_STOCK 11
  #define L_ARTICLECHARGE_STATECHARGE 1

/* Length/Count-Define of ARTICLECHARGE ***************************************/

  #define LS_ARTICLECHARGE_BRANCHNO 5 + 1
  #define LS_ARTICLECHARGE_ARTICLENO 10 + 1
  #define LS_ARTICLECHARGE_EXPIRYDATE 10 + 1
  #define LS_ARTICLECHARGE_CHARGENNR 25 + 1
  #define LS_ARTICLECHARGE_STOCK 10 + 1
  #define LS_ARTICLECHARGE_STATECHARGE 1 + 1

  #define ARTICLECHARGEBRANCHNO 0
  #define ARTICLECHARGEARTICLENO 1
  #define ARTICLECHARGEEXPIRYDATE 2
  #define ARTICLECHARGECHARGENNR 3
  #define ARTICLECHARGESTOCK 4
  #define ARTICLECHARGESTATECHARGE 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTICLECHARGE_H
 #define ARTICLECHARGE_ANZ ( sizeof(ARTICLECHARGE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLECHARGE *************************************************/

 #define ARTICLECHARGE_LISTE \
         ARTICLECHARGE.BRANCHNO,\
         ARTICLECHARGE.ARTICLENO,\
         ARTICLECHARGE.EXPIRYDATE,\
         ARTICLECHARGE.CHARGENNR,\
         ARTICLECHARGE.STOCK,\
         ARTICLECHARGE.STATECHARGE

 #define ARTICLECHARGE_LISTE_390 \
         BRANCHNO,\
         ARTICLENO,\
         EXPIRYDATE,\
         CHARGENNR,\
         STOCK,\
         STATECHARGE

 #define ARTICLECHARGE_PLISTE \
         "ARTICLECHARGE.BRANCHNO,"\
         "ARTICLECHARGE.ARTICLENO,"\
         "ARTICLECHARGE.EXPIRYDATE,"\
         "ARTICLECHARGE.CHARGENNR,"\
         "ARTICLECHARGE.STOCK,"\
         "ARTICLECHARGE.STATECHARGE"

 #define ARTICLECHARGE_PELISTE \
         "BRANCHNO,"\
         "ARTICLENO,"\
         "EXPIRYDATE,"\
         "CHARGENNR,"\
         "STOCK,"\
         "STATECHARGE"

 #define ARTICLECHARGE_UPDLISTE \
         "BRANCHNO=?,"\
         "ARTICLENO=?,"\
         "EXPIRYDATE=?,"\
         "CHARGENNR=?,"\
         "STOCK=?,"\
         "STATECHARGE=?"

/* SqlMacros-Define of ARTICLECHARGE ******************************************/

 #define ARTICLECHARGE_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->EXPIRYDATE,\
         :x->CHARGENNR,\
         :x->STOCK,\
         :x->STATECHARGE

 #define ARTICLECHARGE_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->EXPIRYDATE,\
         :x->CHARGENNR,\
         :x->STOCK,\
         :x->STATECHARGE

 #define ARTICLECHARGE_UPDATE(x) \
         ARTICLECHARGE.BRANCHNO=:x->BRANCHNO,\
         ARTICLECHARGE.ARTICLENO=:x->ARTICLENO,\
         ARTICLECHARGE.EXPIRYDATE=:x->EXPIRYDATE,\
         ARTICLECHARGE.CHARGENNR=:x->CHARGENNR,\
         ARTICLECHARGE.STOCK=:x->STOCK,\
         ARTICLECHARGE.STATECHARGE=:x->STATECHARGE

/* SqlMacros390-Define of ARTICLECHARGE ***************************************/

 #define ARTICLECHARGE_ZEIGER_390 \
         :BRANCHNO,\
         :ARTICLENO,\
         :EXPIRYDATE,\
         :CHARGENNR,\
         :STOCK,\
         :STATECHARGE

 #define ARTICLECHARGE_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         ARTICLENO=:ARTICLENO,\
         EXPIRYDATE=:EXPIRYDATE,\
         CHARGENNR=:CHARGENNR,\
         STOCK=:STOCK,\
         STATECHARGE=:STATECHARGE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTICLECHARGE ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTICLECHARGE {
         short BRANCHNO;
         long ARTICLENO;
         long EXPIRYDATE;
         char CHARGENNR[26];
         long STOCK;
         char STATECHARGE[2];
        } articlechargeS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTICLECHARGE {
         short BRANCHNO;
         long ARTICLENO;
         long EXPIRYDATE;
         char CHARGENNR[26];
         long STOCK;
         char STATECHARGE[2];

			bool operator==(const N_ARTICLECHARGE& right) const {
			return(
				BRANCHNO == right.BRANCHNO &&
				ARTICLENO == right.ARTICLENO &&
				EXPIRYDATE == right.EXPIRYDATE &&
				!strcmp(CHARGENNR, right.CHARGENNR) &&
				STOCK == right.STOCK &&
				!strcmp(STATECHARGE, right.STATECHARGE)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				BRANCHNO = 0;
				ARTICLENO = 0;
				EXPIRYDATE = 0;
				strcpy(CHARGENNR, " " );
				STOCK = 0;
				strcpy(STATECHARGE, " " );
#endif
			}
         } articlechargeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLECHARGE *************************************/

 struct S_ARTICLECHARGE {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char EXPIRYDATE[11];
         char CHARGENNR[25 + 1];
         char STOCK[11];
         char STATECHARGE[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLECHARGE ********************/

 struct O_ARTICLECHARGE {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char EXPIRYDATE[11];
         char CHARGENNR[25];
         char STOCK[11];
         char STATECHARGE[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLECHARGE *******************************/

 struct C_ARTICLECHARGE {
         short BRANCHNO;
         long ARTICLENO;
         long EXPIRYDATE;
         char CHARGENNR[26];
         long STOCK;
         char STATECHARGE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLECHARGE *****************************/

 struct I_ARTICLECHARGE {
         short BRANCHNO;
         short ARTICLENO;
         short EXPIRYDATE;
         short CHARGENNR;
         short STOCK;
         short STATECHARGE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLECHARGE ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTICLECHARGE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTICLECHARGE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 25, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of ARTICLECHARGE *********************************/

 #define ARTICLECHARGE_S390 \
         short BRANCHNO; \
         long ARTICLENO; \
         long EXPIRYDATE; \
         char CHARGENNR[26]; \
         long STOCK; \
         char STATECHARGE; \



/* Copy-Function Struct to single Data ARTICLECHARGE **************************/

 #define ARTICLECHARGE_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         ARTICLENO=_x_->ARTICLENO;\
         EXPIRYDATE=_x_->EXPIRYDATE;\
          strcpy(CHARGENNR,_x_->CHARGENNR);\
         STOCK=_x_->STOCK;\
         STATECHARGE=_x_->STATECHARGE;\

 #define ARTICLECHARGE_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->EXPIRYDATE=EXPIRYDATE;\
          strcpy(_x_->CHARGENNR,CHARGENNR);\
          _x_->STOCK=STOCK;\
          _x_->STATECHARGE=STATECHARGE;\



/* FunctionNumber-Define of ArticleCharge *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleCharge *********************************/


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

class CARTICLECHARGE : public ppDadeVirtual
{
	//data members
	public:
		articlechargeS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<articlechargeS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlechargeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<articlechargeS>; Strip(s); articlechargeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlechargeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<articlechargeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<articlechargeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetBranchno() const	{ return s.BRANCHNO; }
		long		GetArticleno() const	{ return s.ARTICLENO; }
		long		GetExpirydate() const	{ return s.EXPIRYDATE; }
		const char*	GetChargennr(ppString& t) const 	{ t = s.CHARGENNR; t.erasespace(ppString::END); return t.c_str(); }
		long		GetStock() const	{ return s.STOCK; }
		char		GetStatecharge() const	{ return s.STATECHARGE[0]; }
		const articlechargeS& GetStruct() const { return s; }
		void 		SetBranchno(short t) { s.BRANCHNO = t; }
		void 		SetArticleno(long t) { s.ARTICLENO = t; }
		void 		SetExpirydate(long t) { s.EXPIRYDATE = t; }
		void 		SetChargennr(const ppString& t) { ppGStrCopy(s.CHARGENNR,t.c_str() ,L_ARTICLECHARGE_CHARGENNR); }
		void 		SetStock(long t) { s.STOCK = t; }
		void 		SetStatecharge(char t) { s.STATECHARGE[0] = t; s.STATECHARGE[1] = '\0';}
		void 		SetStruct(const articlechargeS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CARTICLECHARGE()  //constructor
		{
			::buf_default((void *)&s, ARTICLECHARGE_BES, ARTICLECHARGE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CARTICLECHARGE()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ARTICLECHARGE_BES, ARTICLECHARGE_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLECHARGE_BES, ARTICLECHARGE_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, ARTICLECHARGE_BES, ARTICLECHARGE_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_ARTICLECHARGE& d)
		{
#ifdef WIN32
			ppGStripLast(d.CHARGENNR);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLECHARGE_BES, ARTICLECHARGE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of ARTICLECHARGE ****************************************/

 #define ARTICLECHARGE_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         ARTICLENO integer default 0 not null,\
         EXPIRYDATE integer default 0 not null,\
         CHARGENNR char(25) default " " not null,\
         STOCK integer default 0 not null,\
         STATECHARGE char(1) default " " not null) in ksc extent size 31372 next size 3140 lock mode row;



/* CreateIndexStatement of ARTICLECHARGE **************************************/

 #define ARTICLECHARGE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_articlecharge_1 on _X_(\
              BranchNo,\
              ArticleNo,\
              ChargenNr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLECHARGE **************************************/

 #define ARTICLECHARGE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_articlecharge_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

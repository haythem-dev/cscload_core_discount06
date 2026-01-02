#ifndef __PP_DRIVERLIST_H_
#define __PP_DRIVERLIST_H_


/******************************************************************************/
/* d:\prj\DF\UNIX\loaddrivers\driverlist **************************************/
/******************************************************************************/

/* Length-Define of DRIVERLIST ************************************************/

  #define L_DRIVERLIST_BRANCHNO 6
  #define L_DRIVERLIST_DRIVERID 11
  #define L_DRIVERLIST_DRIVERNAME 30

/* Length/Count-Define of DRIVERLIST ******************************************/

  #define LS_DRIVERLIST_BRANCHNO 5 + 1
  #define LS_DRIVERLIST_DRIVERID 10 + 1
  #define LS_DRIVERLIST_DRIVERNAME 30 + 1

  #define DRIVERLISTBRANCHNO 0
  #define DRIVERLISTDRIVERID 1
  #define DRIVERLISTDRIVERNAME 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DRIVERLIST_H
 #define DRIVERLIST_ANZ ( sizeof(DRIVERLIST_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DRIVERLIST ****************************************************/

 #define DRIVERLIST_LISTE \
         DRIVERLIST.BRANCHNO,\
         DRIVERLIST.DRIVERID,\
         DRIVERLIST.DRIVERNAME

 #define DRIVERLIST_LISTE_390 \
         BRANCHNO,\
         DRIVERID,\
         DRIVERNAME

 #define DRIVERLIST_PLISTE \
         "DRIVERLIST.BRANCHNO,"\
         "DRIVERLIST.DRIVERID,"\
         "DRIVERLIST.DRIVERNAME"

 #define DRIVERLIST_PELISTE \
         "BRANCHNO,"\
         "DRIVERID,"\
         "DRIVERNAME"

 #define DRIVERLIST_UPDLISTE \
         "BRANCHNO=?,"\
         "DRIVERID=?,"\
         "DRIVERNAME=?"

/* SqlMacros-Define of DRIVERLIST *********************************************/

 #define DRIVERLIST_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->DRIVERID,\
         :x->DRIVERNAME

 #define DRIVERLIST_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->DRIVERID,\
         :x->DRIVERNAME

 #define DRIVERLIST_UPDATE(x) \
         DRIVERLIST.BRANCHNO=:x->BRANCHNO,\
         DRIVERLIST.DRIVERID=:x->DRIVERID,\
         DRIVERLIST.DRIVERNAME=:x->DRIVERNAME

/* SqlMacros390-Define of DRIVERLIST ******************************************/

 #define DRIVERLIST_ZEIGER_390 \
         :BRANCHNO,\
         :DRIVERID,\
         :DRIVERNAME

 #define DRIVERLIST_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         DRIVERID=:DRIVERID,\
         DRIVERNAME=:DRIVERNAME

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of DRIVERLIST *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_DRIVERLIST {
         short BRANCHNO;
         long DRIVERID;
         char DRIVERNAME[31];
        } driverlistS;
 #else /*TRANSCLASS*/
 typedef struct N_DRIVERLIST {
         short BRANCHNO;
         long DRIVERID;
         char DRIVERNAME[31];

			bool operator==(const N_DRIVERLIST& right) const {
			return(
				BRANCHNO == right.BRANCHNO &&
				DRIVERID == right.DRIVERID &&
				!strcmp(DRIVERNAME, right.DRIVERNAME)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				BRANCHNO = 0;
				DRIVERID = 0;
				strcpy(DRIVERNAME, " " );
#endif
			}
         } driverlistS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DRIVERLIST ****************************************/

 struct S_DRIVERLIST {
         char BRANCHNO[7];
         char DRIVERID[11];
         char DRIVERNAME[30 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DRIVERLIST ***********************/

 struct O_DRIVERLIST {
         char BRANCHNO[7];
         char DRIVERID[11];
         char DRIVERNAME[30];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DRIVERLIST **********************************/

 struct C_DRIVERLIST {
         short BRANCHNO;
         long DRIVERID;
         char DRIVERNAME[31];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DRIVERLIST ********************************/

 struct I_DRIVERLIST {
         short BRANCHNO;
         short DRIVERID;
         short DRIVERNAME;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DRIVERLIST ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc DRIVERLIST_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DRIVERLIST_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
 };
#endif

/* description for datatypes of DRIVERLIST ************************************/

 #define DRIVERLIST_S390 \
         short BRANCHNO; \
         long DRIVERID; \
         char DRIVERNAME[31]; \



/* Copy-Function Struct to single Data DRIVERLIST *****************************/

 #define DRIVERLIST_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         DRIVERID=_x_->DRIVERID;\
          strcpy(DRIVERNAME,_x_->DRIVERNAME);\

 #define DRIVERLIST_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->DRIVERID=DRIVERID;\
          strcpy(_x_->DRIVERNAME,DRIVERNAME);\



/* FunctionNumber-Define of driverlist ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of driverlist ************************************/


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

class CDRIVERLIST : public ppDadeVirtual
{
	//data members
	public:
		driverlistS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<driverlistS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<driverlistS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<driverlistS>; Strip(s); driverlistS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<driverlistS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<driverlistS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<driverlistS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetBranchno() const	{ return s.BRANCHNO; }
		long		GetDriverid() const	{ return s.DRIVERID; }
		const char*	GetDrivername(ppString& t) const 	{ t = s.DRIVERNAME; t.erasespace(ppString::END); return t.c_str(); }
		const driverlistS& GetStruct() const { return s; }
		void 		SetBranchno(short t) { s.BRANCHNO = t; }
		void 		SetDriverid(long t) { s.DRIVERID = t; }
		void 		SetDrivername(const ppString& t) { ppGStrCopy(s.DRIVERNAME,t.c_str() ,L_DRIVERLIST_DRIVERNAME); }
		void 		SetStruct(const driverlistS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CDRIVERLIST()  //constructor
		{
			::buf_default((void *)&s, DRIVERLIST_BES, DRIVERLIST_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CDRIVERLIST()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, DRIVERLIST_BES, DRIVERLIST_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, DRIVERLIST_BES, DRIVERLIST_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, DRIVERLIST_BES, DRIVERLIST_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_DRIVERLIST& d)
		{
#ifdef WIN32
			ppGStripLast(d.DRIVERNAME);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, DRIVERLIST_BES, DRIVERLIST_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of DRIVERLIST *******************************************/

 #define DRIVERLIST_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         DRIVERID integer default 0 not null,\
         DRIVERNAME char(30) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DRIVERLIST *****************************************/

 #define DRIVERLIST_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_driverlist_1 on _X_(\
              BranchNo,\
              DriverID ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of DRIVERLIST *****************************************/

 #define DRIVERLIST_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_driverlist_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

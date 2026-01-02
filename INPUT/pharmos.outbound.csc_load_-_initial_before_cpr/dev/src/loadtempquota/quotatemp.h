#ifndef __PP_QUOTATEMP_H_
#define __PP_QUOTATEMP_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadtempquota\QuotaTemp *************************************/
/******************************************************************************/

/* Length-Define of QUOTATEMP *************************************************/

  #define L_QUOTATEMP_ARTICLENO 11
  #define L_QUOTATEMP_QUOTA 11
  #define L_QUOTATEMP_DATEFROM 11
  #define L_QUOTATEMP_DATETO 11

/* Length/Count-Define of QUOTATEMP *******************************************/

  #define LS_QUOTATEMP_ARTICLENO 10 + 1
  #define LS_QUOTATEMP_QUOTA 10 + 1
  #define LS_QUOTATEMP_DATEFROM 10 + 1
  #define LS_QUOTATEMP_DATETO 10 + 1

  #define QUOTATEMPARTICLENO 0
  #define QUOTATEMPQUOTA 1
  #define QUOTATEMPDATEFROM 2
  #define QUOTATEMPDATETO 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define QUOTATEMP_H
 #define QUOTATEMP_ANZ ( sizeof(QUOTATEMP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of QUOTATEMP *****************************************************/

 #define QUOTATEMP_LISTE \
         ARTICLEQUOTATEMP.ARTICLENO,\
         ARTICLEQUOTATEMP.QUOTA,\
         ARTICLEQUOTATEMP.DATEFROM,\
         ARTICLEQUOTATEMP.DATETO

 #define QUOTATEMP_LISTE_390 \
         ARTICLENO,\
         QUOTA,\
         DATEFROM,\
         DATETO

 #define QUOTATEMP_PLISTE \
         "ARTICLEQUOTATEMP.ARTICLENO,"\
         "ARTICLEQUOTATEMP.QUOTA,"\
         "ARTICLEQUOTATEMP.DATEFROM,"\
         "ARTICLEQUOTATEMP.DATETO"

 #define QUOTATEMP_PELISTE \
         "ARTICLENO,"\
         "QUOTA,"\
         "DATEFROM,"\
         "DATETO"

 #define QUOTATEMP_UPDLISTE \
         "ARTICLENO=?,"\
         "QUOTA=?,"\
         "DATEFROM=?,"\
         "DATETO=?"

/* SqlMacros-Define of QUOTATEMP **********************************************/

 #define QUOTATEMP_ZEIGER(x) \
         :x->ARTICLENO,\
         :x->QUOTA,\
         :x->DATEFROM,\
         :x->DATETO

 #define QUOTATEMP_ZEIGERSEL(x) \
         :x->ARTICLENO,\
         :x->QUOTA,\
         :x->DATEFROM,\
         :x->DATETO

 #define QUOTATEMP_UPDATE(x) \
         ARTICLEQUOTATEMP.ARTICLENO=:x->ARTICLENO,\
         ARTICLEQUOTATEMP.QUOTA=:x->QUOTA,\
         ARTICLEQUOTATEMP.DATEFROM=:x->DATEFROM,\
         ARTICLEQUOTATEMP.DATETO=:x->DATETO

/* SqlMacros390-Define of QUOTATEMP *******************************************/

 #define QUOTATEMP_ZEIGER_390 \
         :ARTICLENO,\
         :QUOTA,\
         :DATEFROM,\
         :DATETO

 #define QUOTATEMP_UPDATE_390 \
         ARTICLENO=:ARTICLENO,\
         QUOTA=:QUOTA,\
         DATEFROM=:DATEFROM,\
         DATETO=:DATETO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of QUOTATEMP **********************************************/

 #ifndef TRANSCLASS
 typedef struct N_QUOTATEMP {
         long ARTICLENO;
         long QUOTA;
         long DATEFROM;
         long DATETO;
        } quotatempS;
 #else /*TRANSCLASS*/
 typedef struct N_QUOTATEMP {
         long ARTICLENO;
         long QUOTA;
         long DATEFROM;
         long DATETO;

			bool operator==(const N_QUOTATEMP& right) const {
			return(
				ARTICLENO == right.ARTICLENO &&
				QUOTA == right.QUOTA &&
				DATEFROM == right.DATEFROM &&
				DATETO == right.DATETO
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				ARTICLENO = 0;
				QUOTA = 0;
				DATEFROM = 0;
				DATETO = 0;
#endif
			}
         } quotatempS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of QUOTATEMP *****************************************/

 struct S_QUOTATEMP {
         char ARTICLENO[11];
         char QUOTA[11];
         char DATEFROM[11];
         char DATETO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of QUOTATEMP ************************/

 struct O_QUOTATEMP {
         char ARTICLENO[11];
         char QUOTA[11];
         char DATEFROM[11];
         char DATETO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of QUOTATEMP ***********************************/

 struct C_QUOTATEMP {
         long ARTICLENO;
         long QUOTA;
         long DATEFROM;
         long DATETO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of QUOTATEMP *********************************/

 struct I_QUOTATEMP {
         short ARTICLENO;
         short QUOTA;
         short DATEFROM;
         short DATETO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of QUOTATEMP *******************************************/

#if defined (BUF_DESC)
 static struct buf_desc QUOTATEMP_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc QUOTATEMP_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of QUOTATEMP *************************************/

 #define QUOTATEMP_S390 \
         long ARTICLENO; \
         long QUOTA; \
         long DATEFROM; \
         long DATETO; \



/* Copy-Function Struct to single Data QUOTATEMP ******************************/

 #define QUOTATEMP_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         QUOTA=_x_->QUOTA;\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\

 #define QUOTATEMP_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->QUOTA=QUOTA;\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\



/* FunctionNumber-Define of QuotaTemp *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of QuotaTemp *************************************/


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

class CQUOTATEMP : public ppDadeVirtual
{
	//data members
	public:
		quotatempS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<quotatempS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<quotatempS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<quotatempS>; Strip(s); quotatempS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<quotatempS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<quotatempS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<quotatempS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetArticleno() const	{ return s.ARTICLENO; }
		long		GetQuota() const	{ return s.QUOTA; }
		long		GetDatefrom() const	{ return s.DATEFROM; }
		long		GetDateto() const	{ return s.DATETO; }
		const quotatempS& GetStruct() const { return s; }
		void 		SetArticleno(long t) { s.ARTICLENO = t; }
		void 		SetQuota(long t) { s.QUOTA = t; }
		void 		SetDatefrom(long t) { s.DATEFROM = t; }
		void 		SetDateto(long t) { s.DATETO = t; }
		void 		SetStruct(const quotatempS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CQUOTATEMP()  //constructor
		{
			::buf_default((void *)&s, QUOTATEMP_BES, QUOTATEMP_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CQUOTATEMP()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, QUOTATEMP_BES, QUOTATEMP_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, QUOTATEMP_BES, QUOTATEMP_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, QUOTATEMP_BES, QUOTATEMP_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_QUOTATEMP& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, QUOTATEMP_BES, QUOTATEMP_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of QUOTATEMP ********************************************/

 #define QUOTATEMP_CREATE(x) exec sql create table x (\
         ARTICLENO integer default 0 not null,\
         QUOTA integer default 0 not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null) extent size 116 next size 12 lock mode row;



/* CreateIndexStatement of QUOTATEMP ******************************************/

 #define QUOTATEMP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_quotatemp_1 on _X_(\
              ArticleNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of QUOTATEMP ******************************************/

 #define QUOTATEMP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_quotatemp_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

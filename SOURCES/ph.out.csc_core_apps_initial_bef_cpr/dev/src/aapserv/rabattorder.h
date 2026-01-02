#ifndef __PP_RABATTORDER_H_
#define __PP_RABATTORDER_H_

/******************************************************************************/
/* d:\prj\AA\WIN32\AE\RabattOrder *********************************************/
/******************************************************************************/

/* Length-Define of RABATTORDER ***********************************************/

  #define L_RABATTORDER_SWCHAIN 6
  #define L_RABATTORDER_DATEFROM 11
  #define L_RABATTORDER_DATETO 11

/* Length/Count-Define of RABATTORDER *****************************************/

  #define LS_RABATTORDER_SWCHAIN 5 + 1
  #define LS_RABATTORDER_DATEFROM 10 + 1
  #define LS_RABATTORDER_DATETO 10 + 1

  #define RABATTORDERSWCHAIN 0
  #define RABATTORDERDATEFROM 1
  #define RABATTORDERDATETO 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define RABATTORDER_H
 #define RABATTORDER_ANZ (int) ( sizeof(RABATTORDER_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of RABATTORDER ***************************************************/

 #define RABATTORDER_LISTE \
         KDAUFTRAGDISCACC.SWCHAIN,\
         KDAUFTRAGDISCACC.DATEFROM,\
         KDAUFTRAGDISCACC.DATETO

 #define RABATTORDER_LISTE_390 \
         SWCHAIN,\
         DATEFROM,\
         DATETO

 #define RABATTORDER_PLISTE \
         "KDAUFTRAGDISCACC.SWCHAIN,"\
         "KDAUFTRAGDISCACC.DATEFROM,"\
         "KDAUFTRAGDISCACC.DATETO"

 #define RABATTORDER_PELISTE \
         "SWCHAIN,"\
         "DATEFROM,"\
         "DATETO"

 #define RABATTORDER_UPDLISTE \
         "SWCHAIN=?,"\
         "DATEFROM=?,"\
         "DATETO=?"

/* SqlMacros-Define of RABATTORDER ********************************************/

 #define RABATTORDER_ZEIGER(x) \
         :x->SWCHAIN,\
         :x->DATEFROM,\
         :x->DATETO

 #define RABATTORDER_ZEIGERSEL(x) \
         :x->SWCHAIN,\
         :x->DATEFROM,\
         :x->DATETO

 #define RABATTORDER_UPDATE(x) \
         KDAUFTRAGDISCACC.SWCHAIN=:x->SWCHAIN,\
         KDAUFTRAGDISCACC.DATEFROM=:x->DATEFROM,\
         KDAUFTRAGDISCACC.DATETO=:x->DATETO

/* SqlMacros390-Define of RABATTORDER *****************************************/

 #define RABATTORDER_ZEIGER_390 \
         :SWCHAIN,\
         :DATEFROM,\
         :DATETO

 #define RABATTORDER_UPDATE_390 \
         SWCHAIN=:SWCHAIN,\
         DATEFROM=:DATEFROM,\
         DATETO=:DATETO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of RABATTORDER ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_RABATTORDER {
         short SWCHAIN;
         long DATEFROM;
         long DATETO;
        } rabattorderS;
 #else /*TRANSCLASS*/
 typedef struct N_RABATTORDER {
         short SWCHAIN;
         long DATEFROM;
         long DATETO;

			bool operator==(const N_RABATTORDER& right) const {
			return(
				SWCHAIN == right.SWCHAIN &&
				DATEFROM == right.DATEFROM &&
				DATETO == right.DATETO
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				SWCHAIN = 0;
				DATEFROM = 0;
				DATETO = 0;
#endif
			}
         } rabattorderS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of RABATTORDER ***************************************/

 struct S_RABATTORDER {
         char SWCHAIN[7];
         char DATEFROM[11];
         char DATETO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of RABATTORDER **********************/

 struct O_RABATTORDER {
         char SWCHAIN[7];
         char DATEFROM[11];
         char DATETO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of RABATTORDER *********************************/

 struct C_RABATTORDER {
         short SWCHAIN;
         long DATEFROM;
         long DATETO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of RABATTORDER *******************************/

 struct I_RABATTORDER {
         short SWCHAIN;
         short DATEFROM;
         short DATETO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of RABATTORDER *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc RABATTORDER_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc RABATTORDER_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of RABATTORDER ***********************************/

 #define RABATTORDER_S390 \
         short SWCHAIN; \
         long DATEFROM; \
         long DATETO; \



/* Copy-Function Struct to single Data RABATTORDER ****************************/

 #define RABATTORDER_S390_COPY_TO_SINGLE(_x_) \
         SWCHAIN=_x_->SWCHAIN;\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\

 #define RABATTORDER_S390_COPY_TO_STRUCT(_x_) \
          _x_->SWCHAIN=SWCHAIN;\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\



/* FunctionNumber-Define of RabattOrder ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of RabattOrder ***********************************/


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

class CRABATTORDER : public ppDadeVirtual
{
	//data members
	public:
		rabattorderS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<rabattorderS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<rabattorderS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<rabattorderS>; Strip(s); rabattorderS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<rabattorderS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<rabattorderS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<rabattorderS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetSwchain() const	{ return s.SWCHAIN; }
		long		GetDatefrom() const	{ return s.DATEFROM; }
		long		GetDateto() const	{ return s.DATETO; }
		const rabattorderS& GetStruct() const { return s; }
		void 		SetSwchain(short t) { s.SWCHAIN = t; }
		void 		SetDatefrom(long t) { s.DATEFROM = t; }
		void 		SetDateto(long t) { s.DATETO = t; }
		void 		SetStruct(const rabattorderS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CRABATTORDER()  //constructor
		{
			::buf_default((void *)&s, RABATTORDER_BES, RABATTORDER_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CRABATTORDER()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, RABATTORDER_BES, RABATTORDER_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, RABATTORDER_BES, RABATTORDER_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, RABATTORDER_BES, RABATTORDER_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_RABATTORDER& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, RABATTORDER_BES, RABATTORDER_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of RABATTORDER ******************************************/

 #define RABATTORDER_CREATE(x) exec sql create table x (\
         SWCHAIN smallint default 0 not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of RABATTORDER ****************************************/

 #define RABATTORDER_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdaufdiscacc_1 on _X_(\
              BranchNo,\
              kdauftragnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of RABATTORDER ****************************************/

 #define RABATTORDER_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdaufdiscacc_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

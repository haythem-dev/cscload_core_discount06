#ifndef __PP_CUSTOMERSURCHARGE_H_
#define __PP_CUSTOMERSURCHARGE_H_

/******************************************************************************/
/* u:\CustomerSurcharge *******************************************************/
/******************************************************************************/

/* Length-Define of CUSTOMERSURCHARGE *****************************************/

  #define L_CUSTOMERSURCHARGE_BRANCHNO 6
  #define L_CUSTOMERSURCHARGE_CUSTOMERNO 11
  #define L_CUSTOMERSURCHARGE_MANUFACTURERNO 11
  #define L_CUSTOMERSURCHARGE_SURCHARGEPCT 5
  #define N_CUSTOMERSURCHARGE_SURCHARGEPCT 2

/* Length/Count-Define of CUSTOMERSURCHARGE ***********************************/

  #define LS_CUSTOMERSURCHARGE_BRANCHNO 5 + 1
  #define LS_CUSTOMERSURCHARGE_CUSTOMERNO 10 + 1
  #define LS_CUSTOMERSURCHARGE_MANUFACTURERNO 10 + 1
  #define LS_CUSTOMERSURCHARGE_SURCHARGEPCT 5 + 2

  #define CUSTOMERSURCHARGEBRANCHNO 0
  #define CUSTOMERSURCHARGECUSTOMERNO 1
  #define CUSTOMERSURCHARGEMANUFACTURERNO 2
  #define CUSTOMERSURCHARGESURCHARGEPCT 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CUSTOMERSURCHARGE_H
 #define CUSTOMERSURCHARGE_ANZ ( sizeof(CUSTOMERSURCHARGE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTOMERSURCHARGE *********************************************/

 #define CUSTOMERSURCHARGE_LISTE \
         CUSTOMERSURCHARGE.BRANCHNO,\
         CUSTOMERSURCHARGE.CUSTOMERNO,\
         CUSTOMERSURCHARGE.MANUFACTURERNO,\
         CUSTOMERSURCHARGE.SURCHARGEPCT

 #define CUSTOMERSURCHARGE_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         MANUFACTURERNO,\
         SURCHARGEPCT

 #define CUSTOMERSURCHARGE_PLISTE \
         "CUSTOMERSURCHARGE.BRANCHNO,"\
         "CUSTOMERSURCHARGE.CUSTOMERNO,"\
         "CUSTOMERSURCHARGE.MANUFACTURERNO,"\
         "CUSTOMERSURCHARGE.SURCHARGEPCT"

 #define CUSTOMERSURCHARGE_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "MANUFACTURERNO,"\
         "SURCHARGEPCT"

 #define CUSTOMERSURCHARGE_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "MANUFACTURERNO=?,"\
         "SURCHARGEPCT=?"

/* SqlMacros-Define of CUSTOMERSURCHARGE **************************************/

 #define CUSTOMERSURCHARGE_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->MANUFACTURERNO,\
         :x->SURCHARGEPCT

 #define CUSTOMERSURCHARGE_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->MANUFACTURERNO,\
         :x->SURCHARGEPCT

 #define CUSTOMERSURCHARGE_UPDATE(x) \
         CUSTOMERSURCHARGE.BRANCHNO=:x->BRANCHNO,\
         CUSTOMERSURCHARGE.CUSTOMERNO=:x->CUSTOMERNO,\
         CUSTOMERSURCHARGE.MANUFACTURERNO=:x->MANUFACTURERNO,\
         CUSTOMERSURCHARGE.SURCHARGEPCT=:x->SURCHARGEPCT

/* SqlMacros390-Define of CUSTOMERSURCHARGE ***********************************/

 #define CUSTOMERSURCHARGE_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :MANUFACTURERNO,\
         :SURCHARGEPCT

 #define CUSTOMERSURCHARGE_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         MANUFACTURERNO=:MANUFACTURERNO,\
         SURCHARGEPCT=:SURCHARGEPCT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CUSTOMERSURCHARGE **************************************/

 #ifndef TRANSCLASS
 typedef struct N_CUSTOMERSURCHARGE {
         short BRANCHNO;
         long CUSTOMERNO;
         long MANUFACTURERNO;
         double SURCHARGEPCT;
        } customersurchargeS;
 #else /*TRANSCLASS*/
 typedef struct N_CUSTOMERSURCHARGE {
         short BRANCHNO;
         long CUSTOMERNO;
         long MANUFACTURERNO;
         double SURCHARGEPCT;

			bool operator==(const N_CUSTOMERSURCHARGE& right) const {
			return(
				BRANCHNO == right.BRANCHNO &&
				CUSTOMERNO == right.CUSTOMERNO &&
				MANUFACTURERNO == right.MANUFACTURERNO &&
				SURCHARGEPCT == right.SURCHARGEPCT
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				BRANCHNO = 0;
				CUSTOMERNO = 0;
				MANUFACTURERNO = 0;
				SURCHARGEPCT = 0;
#endif
			}
         } customersurchargeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTOMERSURCHARGE *********************************/

 struct S_CUSTOMERSURCHARGE {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char MANUFACTURERNO[11];
         char SURCHARGEPCT[5 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTOMERSURCHARGE ****************/

 struct O_CUSTOMERSURCHARGE {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char MANUFACTURERNO[11];
         char SURCHARGEPCT[5];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CUSTOMERSURCHARGE ***************************/

 struct C_CUSTOMERSURCHARGE {
         short BRANCHNO;
         long CUSTOMERNO;
         long MANUFACTURERNO;
         double SURCHARGEPCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CUSTOMERSURCHARGE *************************/

 struct I_CUSTOMERSURCHARGE {
         short BRANCHNO;
         short CUSTOMERNO;
         short MANUFACTURERNO;
         short SURCHARGEPCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTOMERSURCHARGE ***********************************/

#if defined (BUF_DESC)
 static struct buf_desc CUSTOMERSURCHARGE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CUSTOMERSURCHARGE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
 };
#endif

/* description for datatypes of CUSTOMERSURCHARGE *****************************/

 #define CUSTOMERSURCHARGE_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         long MANUFACTURERNO; \
         double SURCHARGEPCT; \



/* Copy-Function Struct to single Data CUSTOMERSURCHARGE **********************/

 #define CUSTOMERSURCHARGE_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         MANUFACTURERNO=_x_->MANUFACTURERNO;\
         SURCHARGEPCT=_x_->SURCHARGEPCT;\

 #define CUSTOMERSURCHARGE_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->MANUFACTURERNO=MANUFACTURERNO;\
          _x_->SURCHARGEPCT=SURCHARGEPCT;\



/* FunctionNumber-Define of CustomerSurcharge *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CustomerSurcharge *****************************/


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

class CCUSTOMERSURCHARGE : public ppDadeVirtual
{
	//data members
	public:
		customersurchargeS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<customersurchargeS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<customersurchargeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<customersurchargeS>; Strip(s); customersurchargeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<customersurchargeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<customersurchargeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<customersurchargeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetBranchno() const	{ return s.BRANCHNO; }
		long		GetCustomerno() const	{ return s.CUSTOMERNO; }
		long		GetManufacturerno() const	{ return s.MANUFACTURERNO; }
		double		GetSurchargepct() const	{ return s.SURCHARGEPCT; }
		const customersurchargeS& GetStruct() const { return s; }
		void 		SetBranchno(short t) { s.BRANCHNO = t; }
		void 		SetCustomerno(long t) { s.CUSTOMERNO = t; }
		void 		SetManufacturerno(long t) { s.MANUFACTURERNO = t; }
		void 		SetSurchargepct(double t) { s.SURCHARGEPCT = t; }
		void 		SetStruct(const customersurchargeS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CCUSTOMERSURCHARGE()  //constructor
		{
			::buf_default((void *)&s, CUSTOMERSURCHARGE_BES, CUSTOMERSURCHARGE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CCUSTOMERSURCHARGE()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, CUSTOMERSURCHARGE_BES, CUSTOMERSURCHARGE_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, CUSTOMERSURCHARGE_BES, CUSTOMERSURCHARGE_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, CUSTOMERSURCHARGE_BES, CUSTOMERSURCHARGE_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_CUSTOMERSURCHARGE& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, CUSTOMERSURCHARGE_BES, CUSTOMERSURCHARGE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of CUSTOMERSURCHARGE ************************************/

 #define CUSTOMERSURCHARGE_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         MANUFACTURERNO integer default 0 not null,\
         SURCHARGEPCT decimal(5,2) default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CUSTOMERSURCHARGE **********************************/

 #define CUSTOMERSURCHARGE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_cstsurcharge_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              manufacturerno ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTOMERSURCHARGE **********************************/

 #define CUSTOMERSURCHARGE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_cstsurcharge_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

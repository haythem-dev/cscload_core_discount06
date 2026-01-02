#ifndef __PP_CSTPRINT_H_
#define __PP_CSTPRINT_H_

/******************************************************************************/
/* c:\temp3\CstPrint **********************************************************/
/******************************************************************************/

/* Length-Define of CSTPRINT **************************************************/

  #define L_CSTPRINT_BRANCHNO 6
  #define L_CSTPRINT_CUSTOMERNO 11
  #define L_CSTPRINT_PREIS_TYP 6
  #define L_CSTPRINT_DEDUCTION_AEP 6
  #define L_CSTPRINT_DEDUCTION_AVP 6
  #define L_CSTPRINT_PRINT 6

/* Length/Count-Define of CSTPRINT ********************************************/

  #define LS_CSTPRINT_BRANCHNO 5 + 1
  #define LS_CSTPRINT_CUSTOMERNO 10 + 1
  #define LS_CSTPRINT_PREIS_TYP 5 + 1
  #define LS_CSTPRINT_DEDUCTION_AEP 5 + 1
  #define LS_CSTPRINT_DEDUCTION_AVP 5 + 1
  #define LS_CSTPRINT_PRINT 5 + 1

  #define CSTPRINTBRANCHNO 0
  #define CSTPRINTCUSTOMERNO 1
  #define CSTPRINTPREIS_TYP 2
  #define CSTPRINTDEDUCTION_AEP 3
  #define CSTPRINTDEDUCTION_AVP 4
  #define CSTPRINTPRINT 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CSTPRINT_H
 #define CSTPRINT_ANZ ( sizeof(CSTPRINT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSTPRINT ******************************************************/

 #define CSTPRINT_LISTE \
         CSTPRINT.BRANCHNO,\
         CSTPRINT.CUSTOMERNO,\
         CSTPRINT.PREIS_TYP,\
         CSTPRINT.DEDUCTION_AEP,\
         CSTPRINT.DEDUCTION_AVP,\
         CSTPRINT.PRINT

 #define CSTPRINT_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         PREIS_TYP,\
         DEDUCTION_AEP,\
         DEDUCTION_AVP,\
         PRINT

 #define CSTPRINT_PLISTE \
         "CSTPRINT.BRANCHNO,"\
         "CSTPRINT.CUSTOMERNO,"\
         "CSTPRINT.PREIS_TYP,"\
         "CSTPRINT.DEDUCTION_AEP,"\
         "CSTPRINT.DEDUCTION_AVP,"\
         "CSTPRINT.PRINT"

 #define CSTPRINT_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "PREIS_TYP,"\
         "DEDUCTION_AEP,"\
         "DEDUCTION_AVP,"\
         "PRINT"

 #define CSTPRINT_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "PREIS_TYP=?,"\
         "DEDUCTION_AEP=?,"\
         "DEDUCTION_AVP=?,"\
         "PRINT=?"

/* SqlMacros-Define of CSTPRINT ***********************************************/

 #define CSTPRINT_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->PREIS_TYP,\
         :x->DEDUCTION_AEP,\
         :x->DEDUCTION_AVP,\
         :x->PRINT

 #define CSTPRINT_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->PREIS_TYP,\
         :x->DEDUCTION_AEP,\
         :x->DEDUCTION_AVP,\
         :x->PRINT

 #define CSTPRINT_UPDATE(x) \
         CSTPRINT.BRANCHNO=:x->BRANCHNO,\
         CSTPRINT.CUSTOMERNO=:x->CUSTOMERNO,\
         CSTPRINT.PREIS_TYP=:x->PREIS_TYP,\
         CSTPRINT.DEDUCTION_AEP=:x->DEDUCTION_AEP,\
         CSTPRINT.DEDUCTION_AVP=:x->DEDUCTION_AVP,\
         CSTPRINT.PRINT=:x->PRINT

/* SqlMacros390-Define of CSTPRINT ********************************************/

 #define CSTPRINT_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :PREIS_TYP,\
         :DEDUCTION_AEP,\
         :DEDUCTION_AVP,\
         :PRINT

 #define CSTPRINT_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         PREIS_TYP=:PREIS_TYP,\
         DEDUCTION_AEP=:DEDUCTION_AEP,\
         DEDUCTION_AVP=:DEDUCTION_AVP,\
         PRINT=:PRINT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CSTPRINT ***********************************************/

 #ifndef TRANSCLASS
 typedef struct N_CSTPRINT {
         short BRANCHNO;
         long CUSTOMERNO;
         short PREIS_TYP;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short PRINT;
        } cstprintS;
 #else /*TRANSCLASS*/
 typedef struct N_CSTPRINT {
         short BRANCHNO;
         long CUSTOMERNO;
         short PREIS_TYP;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short PRINT;

			bool operator==(const N_CSTPRINT& right) const {
			return(
				BRANCHNO == right.BRANCHNO &&
				CUSTOMERNO == right.CUSTOMERNO &&
				PREIS_TYP == right.PREIS_TYP &&
				DEDUCTION_AEP == right.DEDUCTION_AEP &&
				DEDUCTION_AVP == right.DEDUCTION_AVP &&
				PRINT == right.PRINT
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				BRANCHNO = 0;
				CUSTOMERNO = 0;
				PREIS_TYP = 0;
				DEDUCTION_AEP = 0;
				DEDUCTION_AVP = 0;
				PRINT = 0;
#endif
			}
         } cstprintS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSTPRINT ******************************************/

 struct S_CSTPRINT {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char PREIS_TYP[7];
         char DEDUCTION_AEP[7];
         char DEDUCTION_AVP[7];
         char PRINT[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSTPRINT *************************/

 struct O_CSTPRINT {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char PREIS_TYP[7];
         char DEDUCTION_AEP[7];
         char DEDUCTION_AVP[7];
         char PRINT[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSTPRINT ************************************/

 struct C_CSTPRINT {
         short BRANCHNO;
         long CUSTOMERNO;
         short PREIS_TYP;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short PRINT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSTPRINT **********************************/

 struct I_CSTPRINT {
         short BRANCHNO;
         short CUSTOMERNO;
         short PREIS_TYP;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short PRINT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSTPRINT ********************************************/

#if defined (BUF_DESC)
 static struct buf_desc CSTPRINT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CSTPRINT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of CSTPRINT **************************************/

 #define CSTPRINT_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         short PREIS_TYP; \
         short DEDUCTION_AEP; \
         short DEDUCTION_AVP; \
         short PRINT; \



/* Copy-Function Struct to single Data CSTPRINT *******************************/

 #define CSTPRINT_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         PREIS_TYP=_x_->PREIS_TYP;\
         DEDUCTION_AEP=_x_->DEDUCTION_AEP;\
         DEDUCTION_AVP=_x_->DEDUCTION_AVP;\
         PRINT=_x_->PRINT;\

 #define CSTPRINT_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->PREIS_TYP=PREIS_TYP;\
          _x_->DEDUCTION_AEP=DEDUCTION_AEP;\
          _x_->DEDUCTION_AVP=DEDUCTION_AVP;\
          _x_->PRINT=PRINT;\



/* FunctionNumber-Define of CstPrint ******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CstPrint **************************************/


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

class CCSTPRINT : public ppDadeVirtual
{
	//data members
	public:
		cstprintS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<cstprintS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstprintS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<cstprintS>; Strip(s); cstprintS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstprintS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<cstprintS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<cstprintS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetBranchno() const	{ return s.BRANCHNO; }
		long		GetCustomerno() const	{ return s.CUSTOMERNO; }
		short		GetPreis_typ() const	{ return s.PREIS_TYP; }
		short		GetDeduction_aep() const	{ return s.DEDUCTION_AEP; }
		short		GetDeduction_avp() const	{ return s.DEDUCTION_AVP; }
		short		GetPrint() const	{ return s.PRINT; }
		const cstprintS& GetStruct() const { return s; }
		void 		SetBranchno(short t) { s.BRANCHNO = t; }
		void 		SetCustomerno(long t) { s.CUSTOMERNO = t; }
		void 		SetPreis_typ(short t) { s.PREIS_TYP = t; }
		void 		SetDeduction_aep(short t) { s.DEDUCTION_AEP = t; }
		void 		SetDeduction_avp(short t) { s.DEDUCTION_AVP = t; }
		void 		SetPrint(short t) { s.PRINT = t; }
		void 		SetStruct(const cstprintS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CCSTPRINT()  //constructor
		{
			::buf_default((void *)&s, CSTPRINT_BES, CSTPRINT_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CCSTPRINT()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, CSTPRINT_BES, CSTPRINT_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSTPRINT_BES, CSTPRINT_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, CSTPRINT_BES, CSTPRINT_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_CSTPRINT& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, CSTPRINT_BES, CSTPRINT_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of CSTPRINT *********************************************/

 #define CSTPRINT_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         PREIS_TYP smallint default 0 not null,\
         DEDUCTION_AEP smallint default 0 not null,\
         DEDUCTION_AVP smallint default 0 not null,\
         PRINT smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of CSTPRINT *******************************************/

 #define CSTPRINT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_cstprint_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              preis_typ ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CSTPRINT *******************************************/

 #define CSTPRINT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_cstprint_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

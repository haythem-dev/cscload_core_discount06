#ifndef __PP_INVOICESETTINGS_H_
#define __PP_INVOICESETTINGS_H_

/******************************************************************************/
/* d:\prj\AA\UNIX\AAPSERV\InvoiceSettings *************************************/
/******************************************************************************/

/* Length-Define of INVOICESETTINGS *******************************************/

  #define L_INVOICESETTINGS_PREIS_TYP 6
  #define L_INVOICESETTINGS_PRINT 6
  #define L_INVOICESETTINGS_DEDUCTION_AEP 6
  #define L_INVOICESETTINGS_DEDUCTION_AVP 6
  #define L_INVOICESETTINGS_WITHCOLUMNNR 6
  #define L_INVOICESETTINGS_BYEMAIL 6
  #define L_INVOICESETTINGS_KDAUFTRAGNR 11

/* Length/Count-Define of INVOICESETTINGS *************************************/

  #define LS_INVOICESETTINGS_PREIS_TYP 5 + 1
  #define LS_INVOICESETTINGS_PRINT 5 + 1
  #define LS_INVOICESETTINGS_DEDUCTION_AEP 5 + 1
  #define LS_INVOICESETTINGS_DEDUCTION_AVP 5 + 1
  #define LS_INVOICESETTINGS_WITHCOLUMNNR 5 + 1
  #define LS_INVOICESETTINGS_BYEMAIL 5 + 1
  #define LS_INVOICESETTINGS_KDAUFTRAGNR 10 + 1

  #define INVOICESETTINGSPREIS_TYP 0
  #define INVOICESETTINGSPRINT 1
  #define INVOICESETTINGSDEDUCTION_AEP 2
  #define INVOICESETTINGSDEDUCTION_AVP 3
  #define INVOICESETTINGSWITHCOLUMNNR 4
  #define INVOICESETTINGSBYEMAIL 5
  #define INVOICESETTINGSKDAUFTRAGNR 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define INVOICESETTINGS_H
 #define INVOICESETTINGS_ANZ (int) ( sizeof(INVOICESETTINGS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of INVOICESETTINGS ***********************************************/

 #define INVOICESETTINGS_LISTE \
         CSTPRINT.PREIS_TYP,\
         KDAUFTRAGRECHART.PRINT,\
         KDAUFTRAGRECHART.DEDUCTION_AEP,\
         KDAUFTRAGRECHART.DEDUCTION_AVP,\
         KDAUFTRAGRECHART.WITHCOLUMNNR,\
         KDAUFTRAGRECHART.BYEMAIL,\
         KDAUFTRAGRECHART.KDAUFTRAGNR

 #define INVOICESETTINGS_LISTE_390 \
         PREIS_TYP,\
         PRINT,\
         DEDUCTION_AEP,\
         DEDUCTION_AVP,\
         WITHCOLUMNNR,\
         BYEMAIL,\
         KDAUFTRAGNR

 #define INVOICESETTINGS_PLISTE \
         "CSTPRINT.PREIS_TYP,"\
         "KDAUFTRAGRECHART.PRINT,"\
         "KDAUFTRAGRECHART.DEDUCTION_AEP,"\
         "KDAUFTRAGRECHART.DEDUCTION_AVP,"\
         "KDAUFTRAGRECHART.WITHCOLUMNNR,"\
         "KDAUFTRAGRECHART.BYEMAIL,"\
         "KDAUFTRAGRECHART.KDAUFTRAGNR"

 #define INVOICESETTINGS_PELISTE \
         "PREIS_TYP,"\
         "PRINT,"\
         "DEDUCTION_AEP,"\
         "DEDUCTION_AVP,"\
         "WITHCOLUMNNR,"\
         "BYEMAIL,"\
         "KDAUFTRAGNR"

 #define INVOICESETTINGS_UPDLISTE \
         "PREIS_TYP=?,"\
         "PRINT=?,"\
         "DEDUCTION_AEP=?,"\
         "DEDUCTION_AVP=?,"\
         "WITHCOLUMNNR=?,"\
         "BYEMAIL=?,"\
         "KDAUFTRAGNR=?"

/* SqlMacros-Define of INVOICESETTINGS ****************************************/

 #define INVOICESETTINGS_ZEIGER(x) \
         :x->PREIS_TYP,\
         :x->PRINT,\
         :x->DEDUCTION_AEP,\
         :x->DEDUCTION_AVP,\
         :x->WITHCOLUMNNR,\
         :x->BYEMAIL,\
         :x->KDAUFTRAGNR

 #define INVOICESETTINGS_ZEIGERSEL(x) \
         :x->PREIS_TYP,\
         :x->PRINT,\
         :x->DEDUCTION_AEP,\
         :x->DEDUCTION_AVP,\
         :x->WITHCOLUMNNR,\
         :x->BYEMAIL,\
         :x->KDAUFTRAGNR

 #define INVOICESETTINGS_UPDATE(x) \
         CSTPRINT.PREIS_TYP=:x->PREIS_TYP,\
         KDAUFTRAGRECHART.PRINT=:x->PRINT,\
         KDAUFTRAGRECHART.DEDUCTION_AEP=:x->DEDUCTION_AEP,\
         KDAUFTRAGRECHART.DEDUCTION_AVP=:x->DEDUCTION_AVP,\
         KDAUFTRAGRECHART.WITHCOLUMNNR=:x->WITHCOLUMNNR,\
         KDAUFTRAGRECHART.BYEMAIL=:x->BYEMAIL,\
         KDAUFTRAGRECHART.KDAUFTRAGNR=:x->KDAUFTRAGNR

/* SqlMacros390-Define of INVOICESETTINGS *************************************/

 #define INVOICESETTINGS_ZEIGER_390 \
         :PREIS_TYP,\
         :PRINT,\
         :DEDUCTION_AEP,\
         :DEDUCTION_AVP,\
         :WITHCOLUMNNR,\
         :BYEMAIL,\
         :KDAUFTRAGNR

 #define INVOICESETTINGS_UPDATE_390 \
         PREIS_TYP=:PREIS_TYP,\
         PRINT=:PRINT,\
         DEDUCTION_AEP=:DEDUCTION_AEP,\
         DEDUCTION_AVP=:DEDUCTION_AVP,\
         WITHCOLUMNNR=:WITHCOLUMNNR,\
         BYEMAIL=:BYEMAIL,\
         KDAUFTRAGNR=:KDAUFTRAGNR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of INVOICESETTINGS ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_INVOICESETTINGS {
         short PREIS_TYP;
         short PRINT;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short WITHCOLUMNNR;
         short BYEMAIL;
         long KDAUFTRAGNR;
        } invoicesettingsS;
 #else /*TRANSCLASS*/
 typedef struct N_INVOICESETTINGS {
         short PREIS_TYP;
         short PRINT;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short WITHCOLUMNNR;
         short BYEMAIL;
         long KDAUFTRAGNR;

			bool operator==(const N_INVOICESETTINGS& right) const {
			return(
				PREIS_TYP == right.PREIS_TYP &&
				PRINT == right.PRINT &&
				DEDUCTION_AEP == right.DEDUCTION_AEP &&
				DEDUCTION_AVP == right.DEDUCTION_AVP &&
				WITHCOLUMNNR == right.WITHCOLUMNNR &&
				BYEMAIL == right.BYEMAIL &&
				KDAUFTRAGNR == right.KDAUFTRAGNR
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				PREIS_TYP = 0;
				PRINT = 0;
				DEDUCTION_AEP = 0;
				DEDUCTION_AVP = 0;
				WITHCOLUMNNR = 0;
				BYEMAIL = 0;
				KDAUFTRAGNR = 0;
#endif
			}
         } invoicesettingsS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of INVOICESETTINGS ***********************************/

 struct S_INVOICESETTINGS {
         char PREIS_TYP[7];
         char PRINT[7];
         char DEDUCTION_AEP[7];
         char DEDUCTION_AVP[7];
         char WITHCOLUMNNR[7];
         char BYEMAIL[7];
         char KDAUFTRAGNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of INVOICESETTINGS ******************/

 struct O_INVOICESETTINGS {
         char PREIS_TYP[7];
         char PRINT[7];
         char DEDUCTION_AEP[7];
         char DEDUCTION_AVP[7];
         char WITHCOLUMNNR[7];
         char BYEMAIL[7];
         char KDAUFTRAGNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of INVOICESETTINGS *****************************/

 struct C_INVOICESETTINGS {
         short PREIS_TYP;
         short PRINT;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short WITHCOLUMNNR;
         short BYEMAIL;
         long KDAUFTRAGNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of INVOICESETTINGS ***************************/

 struct I_INVOICESETTINGS {
         short PREIS_TYP;
         short PRINT;
         short DEDUCTION_AEP;
         short DEDUCTION_AVP;
         short WITHCOLUMNNR;
         short BYEMAIL;
         short KDAUFTRAGNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of INVOICESETTINGS *************************************/

#if defined (BUF_DESC)
 static struct buf_desc INVOICESETTINGS_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc INVOICESETTINGS_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of INVOICESETTINGS *******************************/

 #define INVOICESETTINGS_S390 \
         short PREIS_TYP; \
         short PRINT; \
         short DEDUCTION_AEP; \
         short DEDUCTION_AVP; \
         short WITHCOLUMNNR; \
         short BYEMAIL; \
         long KDAUFTRAGNR; \



/* Copy-Function Struct to single Data INVOICESETTINGS ************************/

 #define INVOICESETTINGS_S390_COPY_TO_SINGLE(_x_) \
         PREIS_TYP=_x_->PREIS_TYP;\
         PRINT=_x_->PRINT;\
         DEDUCTION_AEP=_x_->DEDUCTION_AEP;\
         DEDUCTION_AVP=_x_->DEDUCTION_AVP;\
         WITHCOLUMNNR=_x_->WITHCOLUMNNR;\
         BYEMAIL=_x_->BYEMAIL;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\

 #define INVOICESETTINGS_S390_COPY_TO_STRUCT(_x_) \
          _x_->PREIS_TYP=PREIS_TYP;\
          _x_->PRINT=PRINT;\
          _x_->DEDUCTION_AEP=DEDUCTION_AEP;\
          _x_->DEDUCTION_AVP=DEDUCTION_AVP;\
          _x_->WITHCOLUMNNR=WITHCOLUMNNR;\
          _x_->BYEMAIL=BYEMAIL;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\



/* FunctionNumber-Define of InvoiceSettings ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of InvoiceSettings *******************************/


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

class CINVOICESETTINGS : public ppDadeVirtual
{
	//data members
	public:
		invoicesettingsS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<invoicesettingsS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<invoicesettingsS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<invoicesettingsS>; Strip(s); invoicesettingsS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<invoicesettingsS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<invoicesettingsS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<invoicesettingsS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetPreis_typ() const	{ return s.PREIS_TYP; }
		short		GetPrint() const	{ return s.PRINT; }
		short		GetDeduction_aep() const	{ return s.DEDUCTION_AEP; }
		short		GetDeduction_avp() const	{ return s.DEDUCTION_AVP; }
		short		GetWithcolumnnr() const	{ return s.WITHCOLUMNNR; }
		short		GetByemail() const	{ return s.BYEMAIL; }
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		const invoicesettingsS& GetStruct() const { return s; }
		void 		SetPreis_typ(short t) { s.PREIS_TYP = t; }
		void 		SetPrint(short t) { s.PRINT = t; }
		void 		SetDeduction_aep(short t) { s.DEDUCTION_AEP = t; }
		void 		SetDeduction_avp(short t) { s.DEDUCTION_AVP = t; }
		void 		SetWithcolumnnr(short t) { s.WITHCOLUMNNR = t; }
		void 		SetByemail(short t) { s.BYEMAIL = t; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetStruct(const invoicesettingsS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CINVOICESETTINGS()  //constructor
		{
			::buf_default((void *)&s, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CINVOICESETTINGS()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_INVOICESETTINGS& d)
		{
#ifdef WIN32
#endif
		}

		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, INVOICESETTINGS_BES, INVOICESETTINGS_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of INVOICESETTINGS **************************************/

 #define INVOICESETTINGS_CREATE(x) exec sql create table x (\
         PREIS_TYP smallint default 0 not null,\
         PRINT smallint default 0 not null,\
         DEDUCTION_AEP smallint default 0 not null,\
         DEDUCTION_AVP smallint default 0 not null,\
         WITHCOLUMNNR smallint default 0 not null,\
         BYEMAIL smallint default 0 not null,\
         KDAUFTRAGNR integer default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of INVOICESETTINGS ************************************/

 #define INVOICESETTINGS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_cstprint_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              preis_typ );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of INVOICESETTINGS ************************************/

 #define INVOICESETTINGS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_cstprint_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

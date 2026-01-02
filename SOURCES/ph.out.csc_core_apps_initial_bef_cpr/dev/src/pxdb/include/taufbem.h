#ifndef __PP_TAUFBEM_H_
#define __PP_TAUFBEM_H_

/******************************************************************************/
/* c:\phosix\taufbem **********************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGBEM **********************************************/

  #define L_KDAUFTRAGBEM_KDAUFTRAGNR 11
  #define L_KDAUFTRAGBEM_BEMERKUNGSART 6
  #define L_KDAUFTRAGBEM_BEMERKUNGSNR 6
  #define L_KDAUFTRAGBEM_BEMERKUNGEN 240

/* Length/Count-Define of KDAUFTRAGBEM ****************************************/

  #define LS_KDAUFTRAGBEM_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGBEM_BEMERKUNGSART 5 + 1
  #define LS_KDAUFTRAGBEM_BEMERKUNGSNR 5 + 1
  #define LS_KDAUFTRAGBEM_BEMERKUNGEN 240 + 1

  #define KDAUFTRAGBEMKDAUFTRAGNR 0
  #define KDAUFTRAGBEMBEMERKUNGSART 1
  #define KDAUFTRAGBEMBEMERKUNGSNR 2
  #define KDAUFTRAGBEMBEMERKUNGEN 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGBEM_H
 #define KDAUFTRAGBEM_ANZ ( sizeof(KDAUFTRAGBEM_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGBEM **************************************************/

 #define KDAUFTRAGBEM_LISTE \
         KDAUFTRAGBEM.KDAUFTRAGNR,\
         KDAUFTRAGBEM.BEMERKUNGSART,\
         KDAUFTRAGBEM.BEMERKUNGSNR,\
         KDAUFTRAGBEM.BEMERKUNGEN

 #define KDAUFTRAGBEM_LISTE_390 \
         KDAUFTRAGNR,\
         BEMERKUNGSART,\
         BEMERKUNGSNR,\
         BEMERKUNGEN

 #define KDAUFTRAGBEM_PLISTE \
         "KDAUFTRAGBEM.KDAUFTRAGNR,"\
         "KDAUFTRAGBEM.BEMERKUNGSART,"\
         "KDAUFTRAGBEM.BEMERKUNGSNR,"\
         "KDAUFTRAGBEM.BEMERKUNGEN"

 #define KDAUFTRAGBEM_PELISTE \
         "KDAUFTRAGNR,"\
         "BEMERKUNGSART,"\
         "BEMERKUNGSNR,"\
         "BEMERKUNGEN"

 #define KDAUFTRAGBEM_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "BEMERKUNGSART=?,"\
         "BEMERKUNGSNR=?,"\
         "BEMERKUNGEN=?"

/* SqlMacros-Define of KDAUFTRAGBEM *******************************************/

 #define KDAUFTRAGBEM_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->BEMERKUNGSART,\
         :x->BEMERKUNGSNR,\
         :x->BEMERKUNGEN

 #define KDAUFTRAGBEM_UPDATE(x) \
         KDAUFTRAGBEM.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGBEM.BEMERKUNGSART=:x->BEMERKUNGSART,\
         KDAUFTRAGBEM.BEMERKUNGSNR=:x->BEMERKUNGSNR,\
         KDAUFTRAGBEM.BEMERKUNGEN=:x->BEMERKUNGEN

/* SqlMacros390-Define of KDAUFTRAGBEM ****************************************/

 #define KDAUFTRAGBEM_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :BEMERKUNGSART,\
         :BEMERKUNGSNR,\
         :BEMERKUNGEN

 #define KDAUFTRAGBEM_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         BEMERKUNGSART=:BEMERKUNGSART,\
         BEMERKUNGSNR=:BEMERKUNGSNR,\
         BEMERKUNGEN=:BEMERKUNGEN

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGBEM *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGBEM {
         long KDAUFTRAGNR;
         short BEMERKUNGSART;
         short BEMERKUNGSNR;
         char BEMERKUNGEN[241];
        } kdauftragbemS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGBEM {
         long KDAUFTRAGNR;
         short BEMERKUNGSART;
         short BEMERKUNGSNR;
         char BEMERKUNGEN[241];

			bool operator==(const N_KDAUFTRAGBEM& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				BEMERKUNGSART == right.BEMERKUNGSART &&
				BEMERKUNGSNR == right.BEMERKUNGSNR &&
				!strcmp(BEMERKUNGEN, right.BEMERKUNGEN)
				);
			}
			void clear() { memset((char*)this,0,sizeof(*this)); }
         } kdauftragbemS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGBEM **************************************/

 struct S_KDAUFTRAGBEM {
         char KDAUFTRAGNR[11];
         char BEMERKUNGSART[7];
         char BEMERKUNGSNR[7];
         char BEMERKUNGEN[240 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGBEM *********************/

 struct O_KDAUFTRAGBEM {
         char KDAUFTRAGNR[11];
         char BEMERKUNGSART[7];
         char BEMERKUNGSNR[7];
         char BEMERKUNGEN[240];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of KDAUFTRAGBEM *********************************/

 struct C_KDAUFTRAGBEM {
         long KDAUFTRAGNR;
         short BEMERKUNGSART;
         short BEMERKUNGSNR;
         char BEMERKUNGEN[241];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of KDAUFTRAGBEM *******************************/

 struct I_KDAUFTRAGBEM {
         short KDAUFTRAGNR;
         short BEMERKUNGSART;
         short BEMERKUNGSNR;
         short BEMERKUNGEN;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGBEM ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGBEM_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGBEM_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGBEM **********************************/

 #define KDAUFTRAGBEM_S390 \
         long KDAUFTRAGNR; \
         short BEMERKUNGSART; \
         short BEMERKUNGSNR; \
         char BEMERKUNGEN[241]; \



/* Copy-Function Struct to single Data KDAUFTRAGBEM ***************************/

 #define KDAUFTRAGBEM_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         BEMERKUNGSART=_x_->BEMERKUNGSART;\
         BEMERKUNGSNR=_x_->BEMERKUNGSNR;\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\

 #define KDAUFTRAGBEM_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->BEMERKUNGSART=BEMERKUNGSART;\
          _x_->BEMERKUNGSNR=BEMERKUNGSNR;\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\



/* FunctionNumber-Define of kdauftragbem **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragbem **********************************/


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

class CKDAUFTRAGBEM : public ppDadeVirtual
{
	//data members
	public:
		kdauftragbemS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kdauftragbemS> *pl; // pointer to class list

	//functions
	public:

		const int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) {	if (GetSize() <= i)	return false; vector<kdauftragbemS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kdauftragbemS>; Strip(s); kdauftragbemS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragbemS>::iterator itPtr = pl->begin() + i; if ( itPtr ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kdauftragbemS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kdauftragbemS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const long&		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		const short&		GetBemerkungsart() const	{ return s.BEMERKUNGSART; }
		const short&		GetBemerkungsnr() const	{ return s.BEMERKUNGSNR; }
		const char*	GetBemerkungen(ppString& t) const 	{ t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
		const kdauftragbemS& GetStruct() const { return s; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetBemerkungsart(short t) { s.BEMERKUNGSART = t; }
		void 		SetBemerkungsnr(short t) { s.BEMERKUNGSNR = t; }
		void 		SetBemerkungen(const ppString& t) { ppGStrCopy(s.BEMERKUNGEN,t.c_str() ,L_KDAUFTRAGBEM_BEMERKUNGEN); }
		void 		SetStruct(const kdauftragbemS& t) { s = t; }

		CKDAUFTRAGBEM()  //constructor
		{
			::buf_default((void *)&s,KDAUFTRAGBEM_BES,KDAUFTRAGBEM_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		~CKDAUFTRAGBEM()  //destructor
		{
			if(pl) delete pl;
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KDAUFTRAGBEM_BES, KDAUFTRAGBEM_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_KDAUFTRAGBEM& d)
		{
			ppGStripLast(d.BEMERKUNGEN);
		}

		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,KDAUFTRAGBEM_BES,KDAUFTRAGBEM_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KDAUFTRAGBEM *****************************************/

 #define KDAUFTRAGBEM_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         BEMERKUNGSART smallint default 0 not null,\
         BEMERKUNGSNR smallint default 0 not null,\
         BEMERKUNGEN varchar(240,0) default " " not null) in zp extent size 271 lock mode row;



/* CreateIndexStatement of KDAUFTRAGBEM ***************************************/

 #define KDAUFTRAGBEM_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdauftragbem_1 on _X_(\
              kdauftragnr,\
              bemerkungsart,\
              bemerkungsnr ) in zpidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGBEM ***************************************/

 #define KDAUFTRAGBEM_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdauftragbem_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\


#endif

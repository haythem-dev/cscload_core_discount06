#ifndef __PP_TASKCONTROL_H_
#define __PP_TASKCONTROL_H_

/******************************************************************************/
/* u:tTaskControl *************************************************************/
/******************************************************************************/

/* Length-Define of TASKCONTROL **********************************************/

  #define L_TASKCONTROL_VERTRIEBSZENTRUMNR 6
  #define L_TASKCONTROL_ZEITUNIX 11
  #define L_TASKCONTROL_PROGRAMMNAME 15

/* Length/Count-Define of TASKCONTROL ****************************************/

  #define LS_TASKCONTROL_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_TASKCONTROL_ZEITUNIX 10 + 1
  #define LS_TASKCONTROL_PROGRAMMNAME 15 + 1

  #define TASKCONTROLVERTRIEBSZENTRUMNR 0
  #define TASKCONTROLZEITUNIX 1
  #define TASKCONTROLPROGRAMMNAME 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define TASKCONTROL_H
 #define TASKCONTROL_ANZ ( sizeof(TASKCONTROL_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TASKCONTROL **************************************************/

 #define TASKCONTROL_LISTE \
         TASKCONTROL.VERTRIEBSZENTRUMNR,\
         TASKCONTROL.ZEITUNIX,\
         TASKCONTROL.PROGRAMMNAME

 #define TASKCONTROL_LISTE_390 \
         VERTRIEBSZENTRUMNR,\
         ZEITUNIX,\
         PROGRAMMNAME

 #define TASKCONTROL_PLISTE \
         "TASKCONTROL.VERTRIEBSZENTRUMNR,"\
         "TASKCONTROL.ZEITUNIX,"\
         "TASKCONTROL.PROGRAMMNAME"

 #define TASKCONTROL_PELISTE \
         "VERTRIEBSZENTRUMNR,"\
         "ZEITUNIX,"\
         "PROGRAMMNAME"

 #define TASKCONTROL_UPDLISTE \
         "VERTRIEBSZENTRUMNR=?,"\
         "ZEITUNIX=?,"\
         "PROGRAMMNAME=?"

/* SqlMacros-Define of TASKCONTROL *******************************************/

 #define TASKCONTROL_ZEIGER(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->ZEITUNIX,\
         :x->PROGRAMMNAME

 #define TASKCONTROL_ZEIGERSEL(x) \
         :x->VERTRIEBSZENTRUMNR,\
         :x->ZEITUNIX,\
         :x->PROGRAMMNAME

 #define TASKCONTROL_UPDATE(x) \
         TASKCONTROL.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         TASKCONTROL.ZEITUNIX=:x->ZEITUNIX,\
         TASKCONTROL.PROGRAMMNAME=:x->PROGRAMMNAME

/* SqlMacros390-Define of TASKCONTROL ****************************************/

 #define TASKCONTROL_ZEIGER_390 \
         :VERTRIEBSZENTRUMNR,\
         :ZEITUNIX,\
         :PROGRAMMNAME

 #define TASKCONTROL_UPDATE_390 \
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         ZEITUNIX=:ZEITUNIX,\
         PROGRAMMNAME=:PROGRAMMNAME

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of TASKCONTROL *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_TASKCONTROL {
         short VERTRIEBSZENTRUMNR;
         long ZEITUNIX;
         char PROGRAMMNAME[16];
         long FETCH_REL;
        } ttaskcontrolS;
 #else /*TRANSCLASS*/
 typedef struct N_TASKCONTROL {
         short VERTRIEBSZENTRUMNR;
         long ZEITUNIX;
         char PROGRAMMNAME[16];
         long FETCH_REL;
			bool operator==(const N_TASKCONTROL& right) const {
			return(
				VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
				ZEITUNIX == right.ZEITUNIX &&
				!strcmp(PROGRAMMNAME, right.PROGRAMMNAME)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				VERTRIEBSZENTRUMNR = 0;
				ZEITUNIX = 0;
				strcpy(PROGRAMMNAME, " " );
#endif
			}
         } ttaskcontrolS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TASKCONTROL **************************************/

 struct S_TASKCONTROL {
         char VERTRIEBSZENTRUMNR[7];
         char ZEITUNIX[11];
         char PROGRAMMNAME[15 + 1];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TASKCONTROL *********************/

 struct O_TASKCONTROL {
         char VERTRIEBSZENTRUMNR[7];
         char ZEITUNIX[11];
         char PROGRAMMNAME[15];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of TASKCONTROL *********************************/

 struct C_TASKCONTROL {
         short VERTRIEBSZENTRUMNR;
         long ZEITUNIX;
         char PROGRAMMNAME[16];
         long FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of TASKCONTROL *******************************/

 struct I_TASKCONTROL {
         short VERTRIEBSZENTRUMNR;
         short ZEITUNIX;
         short PROGRAMMNAME;
         short FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TASKCONTROL ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc TASKCONTROL_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TASKCONTROL_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 15, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of TASKCONTROL **********************************/

 #define TASKCONTROL_S390 \
         short VERTRIEBSZENTRUMNR; \
         long ZEITUNIX; \
         char PROGRAMMNAME[16]; \
         long FETCH_REL;



/* Copy-Function Struct to single Data TASKCONTROL ***************************/

 #define TASKCONTROL_S390_COPY_TO_SINGLE(_x_) \
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         ZEITUNIX=_x_->ZEITUNIX;\
          strcpy(PROGRAMMNAME,_x_->PROGRAMMNAME);\
          FETCH_REL=_x_->FETCH_REL;\

 #define TASKCONTROL_S390_COPY_TO_STRUCT(_x_) \
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->ZEITUNIX=ZEITUNIX;\
          strcpy(_x_->PROGRAMMNAME,PROGRAMMNAME);\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of tTaskControl **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of tTaskControl **********************************/


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
		virtual const int SelList(int FetchRel = 1,int pos=0) = 0;
		virtual const int SelListHist(int FetchRel = 1,int pos=0) = 0;
		virtual const int SelListFuture(int FetchRel = 1,int pos=0) = 0;
		virtual const int Load(int pos=0) = 0;
 		virtual const int Delete(int pos=0) = 0;
		virtual const int Save(int pos=0) = 0;
};
#endif

class CTASKCONTROL : public ppDadeVirtual
{
	//data members
	public:
		ttaskcontrolS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<ttaskcontrolS> *pl; // pointer to class list

	//functions
	public:

		const int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		const bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		const bool 		SetList(const unsigned int i) {	if (GetSize() <= i)	return false; vector<ttaskcontrolS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		const bool 		InsList() { if ( !pl ) pl = new vector<ttaskcontrolS>; Strip(s); ttaskcontrolS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		const bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<ttaskcontrolS>::iterator itPtr = pl->begin() + i; if ( itPtr ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<ttaskcontrolS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<ttaskcontrolS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const short		GetVertriebszentrumnr() const	{ return s.VERTRIEBSZENTRUMNR; }
		const long		GetZeitunix() const	{ return s.ZEITUNIX; }
		const char*	GetProgrammname(ppString& t) const 	{ t = s.PROGRAMMNAME; t.erasespace(ppString::END); return t.c_str(); }
		const ttaskcontrolS& GetStruct() const { return s; }
		const long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
		void 		SetZeitunix(long t) { s.ZEITUNIX = t; }
		void 		SetProgrammname(const ppString& t) { ppGStrCopy(s.PROGRAMMNAME,t.c_str() ,L_TASKCONTROL_PROGRAMMNAME); }
		void 		SetStruct(const ttaskcontrolS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }

	//virtual functions
	public:

		const int	Load(int pos=0) { return 1; }
		const int	Save(int pos=0) { return 1; }
		const int	Delete(int pos=0) { return 1; }
		const int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		const int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		const int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CTASKCONTROL()  //constructor
		{
			::buf_default((void *)&s,TASKCONTROL_BES,TASKCONTROL_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		~CTASKCONTROL()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, TASKCONTROL_BES, TASKCONTROL_ANZ );
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNumber, (void *)&s,TASKCONTROL_BES,TASKCONTROL_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			bOpenCursor = false;
			bEndOfSelect = false;
			FncNumber = 0;
			CursorPos = 0;
			AnzPos = 0;
			if(pl)
			{
				delete pl;
				pl = NULL;
			}
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_TASKCONTROL& d)
		{
#ifdef WIN32
			ppGStripLast(d.PROGRAMMNAME);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,TASKCONTROL_BES,TASKCONTROL_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int CursorServerCall(int FncNr,int FetchRel = 1, int pos=0)
		{
			if		( FetchRel == 0 ) return CloseCursor(pos);
			else if	( FetchRel == 1 ) return GetNext(pos,FncNr);
			else if	( FetchRel <  0 ) return ChangeCursor(FetchRel);
			else
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
		}

		int GetNext(int pos, int FncNr)
		{
			CTASKCONTROL c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber = FncNr;
				AnzPos = 0;
				if ( pl ) delete pl;
				pl = new vector<ttaskcontrolS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNumber, (void *)&s,TASKCONTROL_BES,TASKCONTROL_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			if (rc==0)
			{
				Strip(s);
				c.s = s;
				pl->insert(pl->end(),c.s);
				bEndOfSelect = false;
				CursorPos++;
				AnzPos++;
			}
			else if (rc==1) bEndOfSelect = true;
			else if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

		int ChangeCursor(int FetchRel) // FetchRel is a negative value
		{
			CursorPos = CursorPos + FetchRel < 0 ? 0 : CursorPos + FetchRel - 1;
			if ( CursorPos >= AnzPos )
			{
				FehlerBehandlung( -1, "False cursor position!" );
				return -1;
			}
			s = pl->at(CursorPos);
			CursorPos++;
			rc = 0;
			return 0;
		}

};

#endif

/* CreateSqlStatement of TASKCONTROL *****************************************/

 #define TASKCONTROL_CREATE(x) exec sql create table x (\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         ZEITUNIX integer default 0 not null,\
         PROGRAMMNAME char(15) default " " not null) extent size 12 lock mode row;



/* CreateIndexStatement of TASKCONTROL ***************************************/

 #define TASKCONTROL_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_taskcontrol1 on _X_(\
              VertriebszentrumNr,\
              ProgrammName );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TASKCONTROL ***************************************/

 #define TASKCONTROL_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_taskcontrol1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

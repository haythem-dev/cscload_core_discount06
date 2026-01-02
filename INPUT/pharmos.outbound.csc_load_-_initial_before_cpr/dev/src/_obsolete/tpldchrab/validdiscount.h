#ifndef __PP_VALIDDISCOUNT_H_
#define __PP_VALIDDISCOUNT_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadrebates\ValidDiscount ***********************************/
/******************************************************************************/

/* Length-Define of VALIDDISCOUNT *********************************************/

  #define L_VALIDDISCOUNT_BRANCHNO 6
  #define L_VALIDDISCOUNT_ARTICLENO 11
  #define L_VALIDDISCOUNT_PHARMACYGROUPID 3
  #define L_VALIDDISCOUNT_DATEFROM 11
  #define L_VALIDDISCOUNT_DATETO 11
  #define L_VALIDDISCOUNT_TYPEOFDISCOUNT 1
  #define L_VALIDDISCOUNT_BASEQTY 11
  #define L_VALIDDISCOUNT_DISCOUNTVALUE 11
  #define L_VALIDDISCOUNT_TYPEOFVALUE 2
  #define L_VALIDDISCOUNT_KINDOFVALUE 2
  #define L_VALIDDISCOUNT_CUSTOMERNO 11

/* Length/Count-Define of VALIDDISCOUNT ***************************************/

  #define LS_VALIDDISCOUNT_BRANCHNO 5 + 1
  #define LS_VALIDDISCOUNT_ARTICLENO 10 + 1
  #define LS_VALIDDISCOUNT_PHARMACYGROUPID 3 + 1
  #define LS_VALIDDISCOUNT_DATEFROM 10 + 1
  #define LS_VALIDDISCOUNT_DATETO 10 + 1
  #define LS_VALIDDISCOUNT_TYPEOFDISCOUNT 1 + 1
  #define LS_VALIDDISCOUNT_BASEQTY 10 + 1
  #define LS_VALIDDISCOUNT_DISCOUNTVALUE 10 + 1
  #define LS_VALIDDISCOUNT_TYPEOFVALUE 2 + 1
  #define LS_VALIDDISCOUNT_KINDOFVALUE 2 + 1
  #define LS_VALIDDISCOUNT_CUSTOMERNO 10 + 1

  #define VALIDDISCOUNTBRANCHNO 0
  #define VALIDDISCOUNTARTICLENO 1
  #define VALIDDISCOUNTPHARMACYGROUPID 2
  #define VALIDDISCOUNTDATEFROM 3
  #define VALIDDISCOUNTDATETO 4
  #define VALIDDISCOUNTTYPEOFDISCOUNT 5
  #define VALIDDISCOUNTBASEQTY 6
  #define VALIDDISCOUNTDISCOUNTVALUE 7
  #define VALIDDISCOUNTTYPEOFVALUE 8
  #define VALIDDISCOUNTKINDOFVALUE 9
  #define VALIDDISCOUNTCUSTOMERNO 10

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define VALIDDISCOUNT_H
 #define VALIDDISCOUNT_ANZ ( sizeof(VALIDDISCOUNT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of VALIDDISCOUNT *************************************************/

 #define VALIDDISCOUNT_LISTE \
         VALIDDISCOUNTINFO.BRANCHNO,\
         VALIDDISCOUNTINFO.ARTICLENO,\
         VALIDDISCOUNTINFO.PHARMACYGROUPID,\
         VALIDDISCOUNTINFO.DATEFROM,\
         VALIDDISCOUNTINFO.DATETO,\
         VALIDDISCOUNTINFO.TYPEOFDISCOUNT,\
         VALIDDISCOUNTINFO.BASEQTY,\
         VALIDDISCOUNTINFO.DISCOUNTVALUE,\
         VALIDDISCOUNTINFO.TYPEOFVALUE,\
         VALIDDISCOUNTINFO.KINDOFVALUE,\
         VALIDDISCOUNTINFO.CUSTOMERNO

 #define VALIDDISCOUNT_LISTE_390 \
         BRANCHNO,\
         ARTICLENO,\
         PHARMACYGROUPID,\
         DATEFROM,\
         DATETO,\
         TYPEOFDISCOUNT,\
         BASEQTY,\
         DISCOUNTVALUE,\
         TYPEOFVALUE,\
         KINDOFVALUE,\
         CUSTOMERNO

 #define VALIDDISCOUNT_PLISTE \
         "VALIDDISCOUNTINFO.BRANCHNO,"\
         "VALIDDISCOUNTINFO.ARTICLENO,"\
         "VALIDDISCOUNTINFO.PHARMACYGROUPID,"\
         "VALIDDISCOUNTINFO.DATEFROM,"\
         "VALIDDISCOUNTINFO.DATETO,"\
         "VALIDDISCOUNTINFO.TYPEOFDISCOUNT,"\
         "VALIDDISCOUNTINFO.BASEQTY,"\
         "VALIDDISCOUNTINFO.DISCOUNTVALUE,"\
         "VALIDDISCOUNTINFO.TYPEOFVALUE,"\
         "VALIDDISCOUNTINFO.KINDOFVALUE,"\
         "VALIDDISCOUNTINFO.CUSTOMERNO"

 #define VALIDDISCOUNT_PELISTE \
         "BRANCHNO,"\
         "ARTICLENO,"\
         "PHARMACYGROUPID,"\
         "DATEFROM,"\
         "DATETO,"\
         "TYPEOFDISCOUNT,"\
         "BASEQTY,"\
         "DISCOUNTVALUE,"\
         "TYPEOFVALUE,"\
         "KINDOFVALUE,"\
         "CUSTOMERNO"

 #define VALIDDISCOUNT_UPDLISTE \
         "BRANCHNO=?,"\
         "ARTICLENO=?,"\
         "PHARMACYGROUPID=?,"\
         "DATEFROM=?,"\
         "DATETO=?,"\
         "TYPEOFDISCOUNT=?,"\
         "BASEQTY=?,"\
         "DISCOUNTVALUE=?,"\
         "TYPEOFVALUE=?,"\
         "KINDOFVALUE=?,"\
         "CUSTOMERNO=?"

/* SqlMacros-Define of VALIDDISCOUNT ******************************************/

 #define VALIDDISCOUNT_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->PHARMACYGROUPID,\
         :x->DATEFROM,\
         :x->DATETO,\
         :x->TYPEOFDISCOUNT,\
         :x->BASEQTY,\
         :x->DISCOUNTVALUE,\
         :x->TYPEOFVALUE,\
         :x->KINDOFVALUE,\
         :x->CUSTOMERNO

 #define VALIDDISCOUNT_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->PHARMACYGROUPID,\
         :x->DATEFROM,\
         :x->DATETO,\
         :x->TYPEOFDISCOUNT,\
         :x->BASEQTY,\
         :x->DISCOUNTVALUE,\
         :x->TYPEOFVALUE,\
         :x->KINDOFVALUE,\
         :x->CUSTOMERNO

 #define VALIDDISCOUNT_UPDATE(x) \
         VALIDDISCOUNTINFO.BRANCHNO=:x->BRANCHNO,\
         VALIDDISCOUNTINFO.ARTICLENO=:x->ARTICLENO,\
         VALIDDISCOUNTINFO.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         VALIDDISCOUNTINFO.DATEFROM=:x->DATEFROM,\
         VALIDDISCOUNTINFO.DATETO=:x->DATETO,\
         VALIDDISCOUNTINFO.TYPEOFDISCOUNT=:x->TYPEOFDISCOUNT,\
         VALIDDISCOUNTINFO.BASEQTY=:x->BASEQTY,\
         VALIDDISCOUNTINFO.DISCOUNTVALUE=:x->DISCOUNTVALUE,\
         VALIDDISCOUNTINFO.TYPEOFVALUE=:x->TYPEOFVALUE,\
         VALIDDISCOUNTINFO.KINDOFVALUE=:x->KINDOFVALUE,\
         VALIDDISCOUNTINFO.CUSTOMERNO=:x->CUSTOMERNO

/* SqlMacros390-Define of VALIDDISCOUNT ***************************************/

 #define VALIDDISCOUNT_ZEIGER_390 \
         :BRANCHNO,\
         :ARTICLENO,\
         :PHARMACYGROUPID,\
         :DATEFROM,\
         :DATETO,\
         :TYPEOFDISCOUNT,\
         :BASEQTY,\
         :DISCOUNTVALUE,\
         :TYPEOFVALUE,\
         :KINDOFVALUE,\
         :CUSTOMERNO

 #define VALIDDISCOUNT_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         ARTICLENO=:ARTICLENO,\
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         DATEFROM=:DATEFROM,\
         DATETO=:DATETO,\
         TYPEOFDISCOUNT=:TYPEOFDISCOUNT,\
         BASEQTY=:BASEQTY,\
         DISCOUNTVALUE=:DISCOUNTVALUE,\
         TYPEOFVALUE=:TYPEOFVALUE,\
         KINDOFVALUE=:KINDOFVALUE,\
         CUSTOMERNO=:CUSTOMERNO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of VALIDDISCOUNT ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_VALIDDISCOUNT {
         short BRANCHNO;
         long ARTICLENO;
         char PHARMACYGROUPID[4];
         long DATEFROM;
         long DATETO;
         char TYPEOFDISCOUNT[2];
         long BASEQTY;
         long DISCOUNTVALUE;
         char TYPEOFVALUE[3];
         char KINDOFVALUE[3];
         long CUSTOMERNO;
         long FETCH_REL;
        } validdiscountS;
 #else /*TRANSCLASS*/
 typedef struct N_VALIDDISCOUNT {
         short BRANCHNO;
         long ARTICLENO;
         char PHARMACYGROUPID[4];
         long DATEFROM;
         long DATETO;
         char TYPEOFDISCOUNT[2];
         long BASEQTY;
         long DISCOUNTVALUE;
         char TYPEOFVALUE[3];
         char KINDOFVALUE[3];
         long CUSTOMERNO;
         long FETCH_REL;
			bool operator==(const N_VALIDDISCOUNT& right) const {
			return(
				BRANCHNO == right.BRANCHNO &&
				ARTICLENO == right.ARTICLENO &&
				!strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
				DATEFROM == right.DATEFROM &&
				DATETO == right.DATETO &&
				!strcmp(TYPEOFDISCOUNT, right.TYPEOFDISCOUNT) &&
				BASEQTY == right.BASEQTY &&
				DISCOUNTVALUE == right.DISCOUNTVALUE &&
				!strcmp(TYPEOFVALUE, right.TYPEOFVALUE) &&
				!strcmp(KINDOFVALUE, right.KINDOFVALUE) &&
				CUSTOMERNO == right.CUSTOMERNO
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				BRANCHNO = 0;
				ARTICLENO = 0;
				strcpy(PHARMACYGROUPID, " " );
				DATEFROM = 0;
				DATETO = 0;
				strcpy(TYPEOFDISCOUNT, " " );
				BASEQTY = 0;
				DISCOUNTVALUE = 0;
				strcpy(TYPEOFVALUE, " " );
				strcpy(KINDOFVALUE, " " );
				CUSTOMERNO = 0;
#endif
			}
         } validdiscountS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of VALIDDISCOUNT *************************************/

 struct S_VALIDDISCOUNT {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char PHARMACYGROUPID[3 + 1];
         char DATEFROM[11];
         char DATETO[11];
         char TYPEOFDISCOUNT[1 + 1];
         char BASEQTY[11];
         char DISCOUNTVALUE[11];
         char TYPEOFVALUE[2 + 1];
         char KINDOFVALUE[2 + 1];
         char CUSTOMERNO[11];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of VALIDDISCOUNT ********************/

 struct O_VALIDDISCOUNT {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char PHARMACYGROUPID[3];
         char DATEFROM[11];
         char DATETO[11];
         char TYPEOFDISCOUNT[1];
         char BASEQTY[11];
         char DISCOUNTVALUE[11];
         char TYPEOFVALUE[2];
         char KINDOFVALUE[2];
         char CUSTOMERNO[11];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of VALIDDISCOUNT *******************************/

 struct C_VALIDDISCOUNT {
         short BRANCHNO;
         long ARTICLENO;
         char PHARMACYGROUPID[4];
         long DATEFROM;
         long DATETO;
         char TYPEOFDISCOUNT;
         long BASEQTY;
         long DISCOUNTVALUE;
         char TYPEOFVALUE[3];
         char KINDOFVALUE[3];
         long CUSTOMERNO;
         long FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of VALIDDISCOUNT *****************************/

 struct I_VALIDDISCOUNT {
         short BRANCHNO;
         short ARTICLENO;
         short PHARMACYGROUPID;
         short DATEFROM;
         short DATETO;
         short TYPEOFDISCOUNT;
         short BASEQTY;
         short DISCOUNTVALUE;
         short TYPEOFVALUE;
         short KINDOFVALUE;
         short CUSTOMERNO;
         short FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of VALIDDISCOUNT ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc VALIDDISCOUNT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc VALIDDISCOUNT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of VALIDDISCOUNT *********************************/

 #define VALIDDISCOUNT_S390 \
         short BRANCHNO; \
         long ARTICLENO; \
         char PHARMACYGROUPID[4]; \
         long DATEFROM; \
         long DATETO; \
         char TYPEOFDISCOUNT; \
         long BASEQTY; \
         long DISCOUNTVALUE; \
         char TYPEOFVALUE[3]; \
         char KINDOFVALUE[3]; \
         long CUSTOMERNO; \
         long FETCH_REL;



/* Copy-Function Struct to single Data VALIDDISCOUNT **************************/

 #define VALIDDISCOUNT_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         ARTICLENO=_x_->ARTICLENO;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\
         TYPEOFDISCOUNT=_x_->TYPEOFDISCOUNT;\
         BASEQTY=_x_->BASEQTY;\
         DISCOUNTVALUE=_x_->DISCOUNTVALUE;\
          strcpy(TYPEOFVALUE,_x_->TYPEOFVALUE);\
          strcpy(KINDOFVALUE,_x_->KINDOFVALUE);\
         CUSTOMERNO=_x_->CUSTOMERNO;\
          FETCH_REL=_x_->FETCH_REL;\

 #define VALIDDISCOUNT_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->ARTICLENO=ARTICLENO;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\
          _x_->TYPEOFDISCOUNT=TYPEOFDISCOUNT;\
          _x_->BASEQTY=BASEQTY;\
          _x_->DISCOUNTVALUE=DISCOUNTVALUE;\
          strcpy(_x_->TYPEOFVALUE,TYPEOFVALUE);\
          strcpy(_x_->KINDOFVALUE,KINDOFVALUE);\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of ValidDiscount *************************************/

  #define VALIDDISCOUNT_SELLIST 1351
  #define VALIDDISCOUNT_SELLISTKND 1352

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ValidDiscount *********************************/

  #define SelList 1351
  #define SelListKnd 1352

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

class CVALIDDISCOUNT : public ppDadeVirtual
{
	//data members
	public:
		validdiscountS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<validdiscountS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<validdiscountS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<validdiscountS>; Strip(s); validdiscountS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<validdiscountS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<validdiscountS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<validdiscountS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetBranchno() const	{ return s.BRANCHNO; }
		long		GetArticleno() const	{ return s.ARTICLENO; }
		const char*	GetPharmacygroupid(ppString& t) const 	{ t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
		long		GetDatefrom() const	{ return s.DATEFROM; }
		long		GetDateto() const	{ return s.DATETO; }
		char		GetTypeofdiscount() const	{ return s.TYPEOFDISCOUNT[0]; }
		long		GetBaseqty() const	{ return s.BASEQTY; }
		long		GetDiscountvalue() const	{ return s.DISCOUNTVALUE; }
		const char*	GetTypeofvalue(ppString& t) const 	{ t = s.TYPEOFVALUE; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetKindofvalue(ppString& t) const 	{ t = s.KINDOFVALUE; t.erasespace(ppString::END); return t.c_str(); }
		long		GetCustomerno() const	{ return s.CUSTOMERNO; }
		const validdiscountS& GetStruct() const { return s; }
		long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetBranchno(short t) { s.BRANCHNO = t; }
		void 		SetArticleno(long t) { s.ARTICLENO = t; }
		void 		SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_VALIDDISCOUNT_PHARMACYGROUPID); }
		void 		SetDatefrom(long t) { s.DATEFROM = t; }
		void 		SetDateto(long t) { s.DATETO = t; }
		void 		SetTypeofdiscount(char t) { s.TYPEOFDISCOUNT[0] = t; s.TYPEOFDISCOUNT[1] = '\0';}
		void 		SetBaseqty(long t) { s.BASEQTY = t; }
		void 		SetDiscountvalue(long t) { s.DISCOUNTVALUE = t; }
		void 		SetTypeofvalue(const ppString& t) { ppGStrCopy(s.TYPEOFVALUE,t.c_str() ,L_VALIDDISCOUNT_TYPEOFVALUE); }
		void 		SetKindofvalue(const ppString& t) { ppGStrCopy(s.KINDOFVALUE,t.c_str() ,L_VALIDDISCOUNT_KINDOFVALUE); }
		void 		SetCustomerno(long t) { s.CUSTOMERNO = t; }
		void 		SetStruct(const validdiscountS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }
		int 		SelList(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1351,FetchRel,pos); return rc;}
		int 		SelListKnd(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1352,FetchRel,pos); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CVALIDDISCOUNT()  //constructor
		{
			::buf_default((void *)&s, VALIDDISCOUNT_BES, VALIDDISCOUNT_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CVALIDDISCOUNT()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, VALIDDISCOUNT_BES, VALIDDISCOUNT_ANZ);
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s,VALIDDISCOUNT_BES,VALIDDISCOUNT_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			bOpenCursor  = false;
			bEndOfSelect = false;
			FncNumber    = 0;
			CursorPos    = 0;
			AnzPos       = 0;
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
			if( fkt_nr == 1351 ) 	return CursorServerCall(1351,s.FETCH_REL,pos);
			if( fkt_nr == 1352 ) 	return CursorServerCall(1352,s.FETCH_REL,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_VALIDDISCOUNT& d)
		{
#ifdef WIN32
			ppGStripLast(d.PHARMACYGROUPID);
			ppGStripLast(d.TYPEOFVALUE);
			ppGStripLast(d.KINDOFVALUE);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, VALIDDISCOUNT_BES, VALIDDISCOUNT_ANZ, error_msg);
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
			CVALIDDISCOUNT c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber   = FncNr;
				AnzPos      = 0;
				if ( pl ) delete pl;
				pl = new vector<validdiscountS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s, VALIDDISCOUNT_BES, VALIDDISCOUNT_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
			#endif
			if (rc == 0)
			{
				Strip(s);
				c.s = s;
				pl->insert(pl->end(),c.s);
				bEndOfSelect = false;
				CursorPos++;
				AnzPos++;
			}
			else if (rc == 1) bEndOfSelect = true;
			else if (rc < 0) FehlerBehandlung( rc, error_msg );
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

/* CreateSqlStatement of VALIDDISCOUNT ****************************************/

 #define VALIDDISCOUNT_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         ARTICLENO integer default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null,\
         TYPEOFDISCOUNT char(1) default " " not null,\
         BASEQTY integer default 0 not null,\
         DISCOUNTVALUE integer default 0 not null,\
         TYPEOFVALUE char(2) default " " not null,\
         KINDOFVALUE char(2) default " " not null,\
         CUSTOMERNO integer default 0 not null) extent size 312 next size 32 lock mode row;



/* CreateIndexStatement of VALIDDISCOUNT **************************************/

 #define VALIDDISCOUNT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_discountinfo_1 on _X_(\
              BranchNo,\
              ArticleNo,\
              TypeOfDiscount,\
              PharmacyGroupId,\
              DateFrom,\
              DateTo,\
              BaseQty,\
              CustomerNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of VALIDDISCOUNT **************************************/

 #define VALIDDISCOUNT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_discountinfo_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

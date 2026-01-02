#ifndef __PP_PRICEHIST_H_
#define __PP_PRICEHIST_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadpricehistory\PriceHist **********************************/
/******************************************************************************/

/* Length-Define of PRICEHIST *************************************************/

  #define L_PRICEHIST_ARTIKEL_NR 11
  #define L_PRICEHIST_DATUMGUELTIGAB 11
  #define L_PRICEHIST_GROSSO 9
  #define N_PRICEHIST_GROSSO 2
  #define L_PRICEHIST_AEP 9
  #define N_PRICEHIST_AEP 2
  #define L_PRICEHIST_AVP 9
  #define N_PRICEHIST_AVP 2

/* Length/Count-Define of PRICEHIST *******************************************/

  #define LS_PRICEHIST_ARTIKEL_NR 10 + 1
  #define LS_PRICEHIST_DATUMGUELTIGAB 10 + 1
  #define LS_PRICEHIST_GROSSO 9 + 2
  #define LS_PRICEHIST_AEP 9 + 2
  #define LS_PRICEHIST_AVP 9 + 2

  #define PRICEHISTARTIKEL_NR 0
  #define PRICEHISTDATUMGUELTIGAB 1
  #define PRICEHISTGROSSO 2
  #define PRICEHISTAEP 3
  #define PRICEHISTAVP 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define PRICEHIST_H
 #define PRICEHIST_ANZ ( sizeof(PRICEHIST_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PRICEHIST *****************************************************/

 #define PRICEHIST_LISTE \
         PRICEHISTORY.ARTIKEL_NR,\
         PRICEHISTORY.DATUMGUELTIGAB,\
         PRICEHISTORY.GROSSO,\
         PRICEHISTORY.AEP,\
         PRICEHISTORY.AVP

 #define PRICEHIST_LISTE_390 \
         ARTIKEL_NR,\
         DATUMGUELTIGAB,\
         GROSSO,\
         AEP,\
         AVP

 #define PRICEHIST_PLISTE \
         "PRICEHISTORY.ARTIKEL_NR,"\
         "PRICEHISTORY.DATUMGUELTIGAB,"\
         "PRICEHISTORY.GROSSO,"\
         "PRICEHISTORY.AEP,"\
         "PRICEHISTORY.AVP"

 #define PRICEHIST_PELISTE \
         "ARTIKEL_NR,"\
         "DATUMGUELTIGAB,"\
         "GROSSO,"\
         "AEP,"\
         "AVP"

 #define PRICEHIST_UPDLISTE \
         "ARTIKEL_NR=?,"\
         "DATUMGUELTIGAB=?,"\
         "GROSSO=?,"\
         "AEP=?,"\
         "AVP=?"

/* SqlMacros-Define of PRICEHIST **********************************************/

 #define PRICEHIST_ZEIGER(x) \
         :x->ARTIKEL_NR,\
         :x->DATUMGUELTIGAB,\
         :x->GROSSO,\
         :x->AEP,\
         :x->AVP

 #define PRICEHIST_ZEIGERSEL(x) \
         :x->ARTIKEL_NR,\
         :x->DATUMGUELTIGAB,\
         :x->GROSSO,\
         :x->AEP,\
         :x->AVP

 #define PRICEHIST_UPDATE(x) \
         PRICEHISTORY.ARTIKEL_NR=:x->ARTIKEL_NR,\
         PRICEHISTORY.DATUMGUELTIGAB=:x->DATUMGUELTIGAB,\
         PRICEHISTORY.GROSSO=:x->GROSSO,\
         PRICEHISTORY.AEP=:x->AEP,\
         PRICEHISTORY.AVP=:x->AVP

/* SqlMacros390-Define of PRICEHIST *******************************************/

 #define PRICEHIST_ZEIGER_390 \
         :ARTIKEL_NR,\
         :DATUMGUELTIGAB,\
         :GROSSO,\
         :AEP,\
         :AVP

 #define PRICEHIST_UPDATE_390 \
         ARTIKEL_NR=:ARTIKEL_NR,\
         DATUMGUELTIGAB=:DATUMGUELTIGAB,\
         GROSSO=:GROSSO,\
         AEP=:AEP,\
         AVP=:AVP

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of PRICEHIST **********************************************/

 #ifndef TRANSCLASS
 typedef struct N_PRICEHIST {
         long ARTIKEL_NR;
         long DATUMGUELTIGAB;
         double GROSSO;
         double AEP;
         double AVP;
         long FETCH_REL;
        } pricehistS;
 #else /*TRANSCLASS*/
 typedef struct N_PRICEHIST {
         long ARTIKEL_NR;
         long DATUMGUELTIGAB;
         double GROSSO;
         double AEP;
         double AVP;
         long FETCH_REL;
			bool operator==(const N_PRICEHIST& right) const {
			return(
				ARTIKEL_NR == right.ARTIKEL_NR &&
				DATUMGUELTIGAB == right.DATUMGUELTIGAB &&
				GROSSO == right.GROSSO &&
				AEP == right.AEP &&
				AVP == right.AVP
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				ARTIKEL_NR = 0;
				DATUMGUELTIGAB = 0;
				GROSSO = 0;
				AEP = 0;
				AVP = 0;
#endif
			}
         } pricehistS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PRICEHIST *****************************************/

 struct S_PRICEHIST {
         char ARTIKEL_NR[11];
         char DATUMGUELTIGAB[11];
         char GROSSO[9 + 2];
         char AEP[9 + 2];
         char AVP[9 + 2];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PRICEHIST ************************/

 struct O_PRICEHIST {
         char ARTIKEL_NR[11];
         char DATUMGUELTIGAB[11];
         char GROSSO[9];
         char AEP[9];
         char AVP[9];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PRICEHIST ***********************************/

 struct C_PRICEHIST {
         long ARTIKEL_NR;
         long DATUMGUELTIGAB;
         double GROSSO;
         double AEP;
         double AVP;
         long FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PRICEHIST *********************************/

 struct I_PRICEHIST {
         short ARTIKEL_NR;
         short DATUMGUELTIGAB;
         short GROSSO;
         short AEP;
         short AVP;
         short FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PRICEHIST *******************************************/

#if defined (BUF_DESC)
 static struct buf_desc PRICEHIST_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc PRICEHIST_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of PRICEHIST *************************************/

 #define PRICEHIST_S390 \
         long ARTIKEL_NR; \
         long DATUMGUELTIGAB; \
         double GROSSO; \
         double AEP; \
         double AVP; \
         long FETCH_REL;



/* Copy-Function Struct to single Data PRICEHIST ******************************/

 #define PRICEHIST_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         DATUMGUELTIGAB=_x_->DATUMGUELTIGAB;\
         GROSSO=_x_->GROSSO;\
         AEP=_x_->AEP;\
         AVP=_x_->AVP;\
          FETCH_REL=_x_->FETCH_REL;\

 #define PRICEHIST_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->DATUMGUELTIGAB=DATUMGUELTIGAB;\
          _x_->GROSSO=GROSSO;\
          _x_->AEP=AEP;\
          _x_->AVP=AVP;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of PriceHist *****************************************/

  #define PRICEHIST_SEL 1443

#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of PriceHist *************************************/

  #define Sel 1443

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

class CPRICEHIST : public ppDadeVirtual
{
	//data members
	public:
		pricehistS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<pricehistS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<pricehistS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<pricehistS>; Strip(s); pricehistS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<pricehistS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<pricehistS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<pricehistS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetArtikel_nr() const	{ return s.ARTIKEL_NR; }
		long		GetDatumgueltigab() const	{ return s.DATUMGUELTIGAB; }
		double		GetGrosso() const	{ return s.GROSSO; }
		double		GetAep() const	{ return s.AEP; }
		double		GetAvp() const	{ return s.AVP; }
		const pricehistS& GetStruct() const { return s; }
		long		GetFetch_rel() const { return s.FETCH_REL; }
		void 		SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
		void 		SetDatumgueltigab(long t) { s.DATUMGUELTIGAB = t; }
		void 		SetGrosso(double t) { s.GROSSO = t; }
		void 		SetAep(double t) { s.AEP = t; }
		void 		SetAvp(double t) { s.AVP = t; }
		void 		SetStruct(const pricehistS& t) { s = t; }
		void 		SetFetch_rel(const long t) { s.FETCH_REL = t; }
		int 		Sel(int FetchRel = 1,int pos=0)	{ int rc = CursorServerCall(1443,FetchRel,pos); return rc;}

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CPRICEHIST()  //constructor
		{
			::buf_default((void *)&s, PRICEHIST_BES, PRICEHIST_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CPRICEHIST()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
			CloseCursor();
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, PRICEHIST_BES, PRICEHIST_ANZ);
		}

		int CloseCursor(int pos = 0)  //close db cursor
		{
			if( !bOpenCursor ) return 0;
			s.FETCH_REL = 0;
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s,PRICEHIST_BES,PRICEHIST_ANZ, error_msg);
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
			if( fkt_nr == 1443 ) 	return CursorServerCall(1443,s.FETCH_REL,pos);
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_PRICEHIST& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, PRICEHIST_BES, PRICEHIST_ANZ, error_msg);
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
			CPRICEHIST c;
			if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
			if( bOpenCursor ) s.FETCH_REL = 1;
			else
			{
				s.FETCH_REL = 2;
				bOpenCursor = true;
				FncNumber   = FncNr;
				AnzPos      = 0;
				if ( pl ) delete pl;
				pl = new vector<pricehistS>;
			}
			if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
			else if( CursorPos < AnzPos )
			{
				s = pl->at(CursorPos);
				CursorPos++;
				return 0;
			}
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNumber, (void *)&s, PRICEHIST_BES, PRICEHIST_ANZ, error_msg);
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

/* CreateSqlStatement of PRICEHIST ********************************************/

 #define PRICEHIST_CREATE(x) exec sql create table x (\
         ARTIKEL_NR integer default 0 not null,\
         DATUMGUELTIGAB integer default 0 not null,\
         GROSSO decimal(9,2) default 0 not null,\
         AEP decimal(9,2) default 0 not null,\
         AVP decimal(9,2) default 0 not null) extent size 39216 next size 3924 lock mode row;



/* CreateIndexStatement of PRICEHIST ******************************************/

 #define PRICEHIST_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_pricehist_1 on _X_(\
              artikel_nr,\
              datumgueltigab );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PRICEHIST ******************************************/

 #define PRICEHIST_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_pricehist_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

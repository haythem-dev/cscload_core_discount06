#ifndef __PP_TAXTAB_H_
#define __PP_TAXTAB_H_

/******************************************************************************/
/* c:\temp\taxtab *************************************************************/
/******************************************************************************/

/* Length-Define of TAXTAB ****************************************************/

  #define L_TAXTAB_TAX_ART 1
  #define L_TAXTAB_TAX_VON_DM 11
  #define L_TAXTAB_TAX_PROZ 11
  #define L_TAXTAB_TAX_BETRAG 11
  #define L_TAXTAB_TAX_FIXPREIS 11
  #define L_TAXTAB_TAX_MAX_BETRAG 11

/* Length/Count-Define of TAXTAB **********************************************/

  #define LS_TAXTAB_TAX_ART 1 + 1
  #define LS_TAXTAB_TAX_VON_DM 10 + 1
  #define LS_TAXTAB_TAX_PROZ 10 + 1
  #define LS_TAXTAB_TAX_BETRAG 10 + 1
  #define LS_TAXTAB_TAX_FIXPREIS 10 + 1
  #define LS_TAXTAB_TAX_MAX_BETRAG 10 + 1

  #define TAXTABTAX_ART 0
  #define TAXTABTAX_VON_DM 1
  #define TAXTABTAX_PROZ 2
  #define TAXTABTAX_BETRAG 3
  #define TAXTABTAX_FIXPREIS 4
  #define TAXTABTAX_MAX_BETRAG 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define TAXTAB_H
 #define TAXTAB_ANZ ( sizeof(TAXTAB_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of TAXTAB ********************************************************/

 #define TAXTAB_LISTE \
         TAXTAB.TAX_ART,\
         TAXTAB.TAX_VON_DM,\
         TAXTAB.TAX_PROZ,\
         TAXTAB.TAX_BETRAG,\
         TAXTAB.TAX_FIXPREIS,\
         TAXTAB.TAX_MAX_BETRAG

 #define TAXTAB_LISTE_390 \
         TAX_ART,\
         TAX_VON_DM,\
         TAX_PROZ,\
         TAX_BETRAG,\
         TAX_FIXPREIS,\
         TAX_MAX_BETRAG

 #define TAXTAB_PLISTE \
         "TAXTAB.TAX_ART,"\
         "TAXTAB.TAX_VON_DM,"\
         "TAXTAB.TAX_PROZ,"\
         "TAXTAB.TAX_BETRAG,"\
         "TAXTAB.TAX_FIXPREIS,"\
         "TAXTAB.TAX_MAX_BETRAG"

 #define TAXTAB_PELISTE \
         "TAX_ART,"\
         "TAX_VON_DM,"\
         "TAX_PROZ,"\
         "TAX_BETRAG,"\
         "TAX_FIXPREIS,"\
         "TAX_MAX_BETRAG"

 #define TAXTAB_UPDLISTE \
         "TAX_ART=?,"\
         "TAX_VON_DM=?,"\
         "TAX_PROZ=?,"\
         "TAX_BETRAG=?,"\
         "TAX_FIXPREIS=?,"\
         "TAX_MAX_BETRAG=?"

/* SqlMacros-Define of TAXTAB *************************************************/

 #define TAXTAB_ZEIGER(x) \
         :x->TAX_ART,\
         :x->TAX_VON_DM,\
         :x->TAX_PROZ,\
         :x->TAX_BETRAG,\
         :x->TAX_FIXPREIS,\
         :x->TAX_MAX_BETRAG

 #define TAXTAB_ZEIGERSEL(x) \
         :x->TAX_ART,\
         :x->TAX_VON_DM,\
         :x->TAX_PROZ,\
         :x->TAX_BETRAG,\
         :x->TAX_FIXPREIS,\
         :x->TAX_MAX_BETRAG

 #define TAXTAB_UPDATE(x) \
         TAXTAB.TAX_ART=:x->TAX_ART,\
         TAXTAB.TAX_VON_DM=:x->TAX_VON_DM,\
         TAXTAB.TAX_PROZ=:x->TAX_PROZ,\
         TAXTAB.TAX_BETRAG=:x->TAX_BETRAG,\
         TAXTAB.TAX_FIXPREIS=:x->TAX_FIXPREIS,\
         TAXTAB.TAX_MAX_BETRAG=:x->TAX_MAX_BETRAG

/* SqlMacros390-Define of TAXTAB **********************************************/

 #define TAXTAB_ZEIGER_390 \
         :TAX_ART,\
         :TAX_VON_DM,\
         :TAX_PROZ,\
         :TAX_BETRAG,\
         :TAX_FIXPREIS,\
         :TAX_MAX_BETRAG

 #define TAXTAB_UPDATE_390 \
         TAX_ART=:TAX_ART,\
         TAX_VON_DM=:TAX_VON_DM,\
         TAX_PROZ=:TAX_PROZ,\
         TAX_BETRAG=:TAX_BETRAG,\
         TAX_FIXPREIS=:TAX_FIXPREIS,\
         TAX_MAX_BETRAG=:TAX_MAX_BETRAG

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of TAXTAB *************************************************/

 #ifndef TRANSCLASS
 typedef struct N_TAXTAB {
         char TAX_ART[2];
         long TAX_VON_DM;
         long TAX_PROZ;
         long TAX_BETRAG;
         long TAX_FIXPREIS;
         long TAX_MAX_BETRAG;
        } taxtabS;
 #else /*TRANSCLASS*/
 typedef struct N_TAXTAB {
         char TAX_ART[2];
         long TAX_VON_DM;
         long TAX_PROZ;
         long TAX_BETRAG;
         long TAX_FIXPREIS;
         long TAX_MAX_BETRAG;

			bool operator==(const N_TAXTAB& right) const {
			return(
				!strcmp(TAX_ART, right.TAX_ART) &&
				TAX_VON_DM == right.TAX_VON_DM &&
				TAX_PROZ == right.TAX_PROZ &&
				TAX_BETRAG == right.TAX_BETRAG &&
				TAX_FIXPREIS == right.TAX_FIXPREIS &&
				TAX_MAX_BETRAG == right.TAX_MAX_BETRAG
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				strcpy(TAX_ART, " " );
				TAX_VON_DM = 0;
				TAX_PROZ = 0;
				TAX_BETRAG = 0;
				TAX_FIXPREIS = 0;
				TAX_MAX_BETRAG = 0;
#endif
			}
         } taxtabS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of TAXTAB ********************************************/

 struct S_TAXTAB {
         char TAX_ART[1 + 1];
         char TAX_VON_DM[11];
         char TAX_PROZ[11];
         char TAX_BETRAG[11];
         char TAX_FIXPREIS[11];
         char TAX_MAX_BETRAG[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of TAXTAB ***************************/

 struct O_TAXTAB {
         char TAX_ART[1];
         char TAX_VON_DM[11];
         char TAX_PROZ[11];
         char TAX_BETRAG[11];
         char TAX_FIXPREIS[11];
         char TAX_MAX_BETRAG[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of TAXTAB **************************************/

 struct C_TAXTAB {
         char TAX_ART;
         long TAX_VON_DM;
         long TAX_PROZ;
         long TAX_BETRAG;
         long TAX_FIXPREIS;
         long TAX_MAX_BETRAG;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of TAXTAB ************************************/

 struct I_TAXTAB {
         short TAX_ART;
         short TAX_VON_DM;
         short TAX_PROZ;
         short TAX_BETRAG;
         short TAX_FIXPREIS;
         short TAX_MAX_BETRAG;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of TAXTAB **********************************************/

#if defined (BUF_DESC)
 static struct buf_desc TAXTAB_BES [] =
 {
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc TAXTAB_BES [] =
 {
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of TAXTAB ****************************************/

 #define TAXTAB_S390 \
         char TAX_ART; \
         long TAX_VON_DM; \
         long TAX_PROZ; \
         long TAX_BETRAG; \
         long TAX_FIXPREIS; \
         long TAX_MAX_BETRAG; \



/* Copy-Function Struct to single Data TAXTAB *********************************/

 #define TAXTAB_S390_COPY_TO_SINGLE(_x_) \
         TAX_ART=_x_->TAX_ART;\
         TAX_VON_DM=_x_->TAX_VON_DM;\
         TAX_PROZ=_x_->TAX_PROZ;\
         TAX_BETRAG=_x_->TAX_BETRAG;\
         TAX_FIXPREIS=_x_->TAX_FIXPREIS;\
         TAX_MAX_BETRAG=_x_->TAX_MAX_BETRAG;\

 #define TAXTAB_S390_COPY_TO_STRUCT(_x_) \
          _x_->TAX_ART=TAX_ART;\
          _x_->TAX_VON_DM=TAX_VON_DM;\
          _x_->TAX_PROZ=TAX_PROZ;\
          _x_->TAX_BETRAG=TAX_BETRAG;\
          _x_->TAX_FIXPREIS=TAX_FIXPREIS;\
          _x_->TAX_MAX_BETRAG=TAX_MAX_BETRAG;\



/* FunctionNumber-Define of taxtab ********************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of taxtab ****************************************/


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

class CTAXTAB : public ppDadeVirtual
{
	//data members
	public:
		taxtabS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<taxtabS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<taxtabS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<taxtabS>; Strip(s); taxtabS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<taxtabS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<taxtabS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<taxtabS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		char		GetTax_art() const	{ return s.TAX_ART[0]; }
		long		GetTax_von_dm() const	{ return s.TAX_VON_DM; }
		long		GetTax_proz() const	{ return s.TAX_PROZ; }
		long		GetTax_betrag() const	{ return s.TAX_BETRAG; }
		long		GetTax_fixpreis() const	{ return s.TAX_FIXPREIS; }
		long		GetTax_max_betrag() const	{ return s.TAX_MAX_BETRAG; }
		const taxtabS& GetStruct() const { return s; }
		void 		SetTax_art(char t) { s.TAX_ART[0] = t; s.TAX_ART[1] = '\0';}
		void 		SetTax_von_dm(long t) { s.TAX_VON_DM = t; }
		void 		SetTax_proz(long t) { s.TAX_PROZ = t; }
		void 		SetTax_betrag(long t) { s.TAX_BETRAG = t; }
		void 		SetTax_fixpreis(long t) { s.TAX_FIXPREIS = t; }
		void 		SetTax_max_betrag(long t) { s.TAX_MAX_BETRAG = t; }
		void 		SetStruct(const taxtabS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CTAXTAB()  //constructor
		{
			::buf_default((void *)&s, TAXTAB_BES, TAXTAB_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CTAXTAB()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, TAXTAB_BES, TAXTAB_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, TAXTAB_BES, TAXTAB_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, TAXTAB_BES, TAXTAB_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_TAXTAB& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, TAXTAB_BES, TAXTAB_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of TAXTAB ***********************************************/

 #define TAXTAB_CREATE(x) exec sql create table x (\
         TAX_ART char(1) default " " not null,\
         TAX_VON_DM integer default 0 not null,\
         TAX_PROZ integer default 0 not null,\
         TAX_BETRAG integer default 0 not null,\
         TAX_FIXPREIS integer default 0 not null,\
         TAX_MAX_BETRAG integer default 0 not null) in phosix extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of TAXTAB *********************************************/

 #define TAXTAB_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_taxtab_1 on _X_(\
              tax_art,\
              tax_von_dm ) in phosix1;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of TAXTAB *********************************************/

 #define TAXTAB_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_taxtab_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

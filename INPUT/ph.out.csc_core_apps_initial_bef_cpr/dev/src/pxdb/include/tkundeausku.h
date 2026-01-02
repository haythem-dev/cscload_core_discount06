#ifndef __PP_KNDAUSKU_H_
#define __PP_KNDAUSKU_H_

/******************************************************************************/
/* u:\kundeausku **************************************************************/
/******************************************************************************/

/* Length-Define of KNDAUSKU ************************************************/

  #define L_KNDAUSKU_EILBOTENZUSCHLAG 5
  #define N_KNDAUSKU_EILBOTENZUSCHLAG 2
  #define L_KNDAUSKU_KUNDENNR 11
  #define L_KNDAUSKU_VERTRIEBSZENTRUMNR 6
  #define L_KNDAUSKU_DISPOGEBUEHR 5
  #define N_KNDAUSKU_DISPOGEBUEHR 2
  #define L_KNDAUSKU_BTMGEBUEHR 5
  #define N_KNDAUSKU_BTMGEBUEHR 2
  #define L_KNDAUSKU_DOKUGEBUEHR 5
  #define N_KNDAUSKU_DOKUGEBUEHR 2
  #define L_KNDAUSKU_LOGISTIKAUFSCHLAG 5
  #define N_KNDAUSKU_LOGISTIKAUFSCHLAG 2

/* Length/Count-Define of KNDAUSKU ******************************************/

  #define LS_KNDAUSKU_EILBOTENZUSCHLAG 5 + 2
  #define LS_KNDAUSKU_KUNDENNR 10 + 1
  #define LS_KNDAUSKU_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_KNDAUSKU_DISPOGEBUEHR 5 + 2
  #define LS_KNDAUSKU_BTMGEBUEHR 5 + 2
  #define LS_KNDAUSKU_DOKUGEBUEHR 5 + 2
  #define LS_KNDAUSKU_LOGISTIKAUFSCHLAG 5 + 2

  #define KNDAUSKUEILBOTENZUSCHLAG 0
  #define KNDAUSKUKUNDENNR 1
  #define KNDAUSKUVERTRIEBSZENTRUMNR 2
  #define KNDAUSKUDISPOGEBUEHR 3
  #define KNDAUSKUBTMGEBUEHR 4
  #define KNDAUSKUDOKUGEBUEHR 5
  #define KNDAUSKULOGISTIKAUFSCHLAG 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KNDAUSKU_H
 #define KNDAUSKU_ANZ ( sizeof(KNDAUSKU_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KNDAUSKU ****************************************************/

 #define KNDAUSKU_LISTE \
         KNDAUSKU.EILBOTENZUSCHLAG,\
         KNDAUSKU.KUNDENNR,\
         KNDAUSKU.VERTRIEBSZENTRUMNR,\
         KNDAUSKU.DISPOGEBUEHR,\
         KNDAUSKU.BTMGEBUEHR,\
         KNDAUSKU.DOKUGEBUEHR,\
         KNDAUSKU.LOGISTIKAUFSCHLAG

 #define KNDAUSKU_LISTE_390 \
         EILBOTENZUSCHLAG,\
         KUNDENNR,\
         VERTRIEBSZENTRUMNR,\
         DISPOGEBUEHR,\
         BTMGEBUEHR,\
         DOKUGEBUEHR,\
         LOGISTIKAUFSCHLAG

 #define KNDAUSKU_PLISTE \
         "KNDAUSKU.EILBOTENZUSCHLAG,"\
         "KNDAUSKU.KUNDENNR,"\
         "KNDAUSKU.VERTRIEBSZENTRUMNR,"\
         "KNDAUSKU.DISPOGEBUEHR,"\
         "KNDAUSKU.BTMGEBUEHR,"\
         "KNDAUSKU.DOKUGEBUEHR,"\
         "KNDAUSKU.LOGISTIKAUFSCHLAG"

 #define KNDAUSKU_PELISTE \
         "EILBOTENZUSCHLAG,"\
         "KUNDENNR,"\
         "VERTRIEBSZENTRUMNR,"\
         "DISPOGEBUEHR,"\
         "BTMGEBUEHR,"\
         "DOKUGEBUEHR,"\
         "LOGISTIKAUFSCHLAG"

 #define KNDAUSKU_UPDLISTE \
         "EILBOTENZUSCHLAG=?,"\
         "KUNDENNR=?,"\
         "VERTRIEBSZENTRUMNR=?,"\
         "DISPOGEBUEHR=?,"\
         "BTMGEBUEHR=?,"\
         "DOKUGEBUEHR=?,"\
         "LOGISTIKAUFSCHLAG=?"

/* SqlMacros-Define of KNDAUSKU *********************************************/

 #define KNDAUSKU_ZEIGER(x) \
         :x->EILBOTENZUSCHLAG,\
         :x->KUNDENNR,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->DISPOGEBUEHR,\
         :x->BTMGEBUEHR,\
         :x->DOKUGEBUEHR,\
         :x->LOGISTIKAUFSCHLAG

 #define KNDAUSKU_ZEIGERSEL(x) \
         :x->EILBOTENZUSCHLAG,\
         :x->KUNDENNR,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->DISPOGEBUEHR,\
         :x->BTMGEBUEHR,\
         :x->DOKUGEBUEHR,\
         :x->LOGISTIKAUFSCHLAG

 #define KNDAUSKU_UPDATE(x) \
         KNDAUSKU.EILBOTENZUSCHLAG=:x->EILBOTENZUSCHLAG,\
         KNDAUSKU.KUNDENNR=:x->KUNDENNR,\
         KNDAUSKU.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         KNDAUSKU.DISPOGEBUEHR=:x->DISPOGEBUEHR,\
         KNDAUSKU.BTMGEBUEHR=:x->BTMGEBUEHR,\
         KNDAUSKU.DOKUGEBUEHR=:x->DOKUGEBUEHR,\
         KNDAUSKU.LOGISTIKAUFSCHLAG=:x->LOGISTIKAUFSCHLAG

/* SqlMacros390-Define of KNDAUSKU ******************************************/

 #define KNDAUSKU_ZEIGER_390 \
         :EILBOTENZUSCHLAG,\
         :KUNDENNR,\
         :VERTRIEBSZENTRUMNR,\
         :DISPOGEBUEHR,\
         :BTMGEBUEHR,\
         :DOKUGEBUEHR,\
         :LOGISTIKAUFSCHLAG

 #define KNDAUSKU_UPDATE_390 \
         EILBOTENZUSCHLAG=:EILBOTENZUSCHLAG,\
         KUNDENNR=:KUNDENNR,\
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         DISPOGEBUEHR=:DISPOGEBUEHR,\
         BTMGEBUEHR=:BTMGEBUEHR,\
         DOKUGEBUEHR=:DOKUGEBUEHR,\
         LOGISTIKAUFSCHLAG=:LOGISTIKAUFSCHLAG

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KNDAUSKU *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_KNDAUSKU {
         double EILBOTENZUSCHLAG;
         long KUNDENNR;
         short VERTRIEBSZENTRUMNR;
         double DISPOGEBUEHR;
         double BTMGEBUEHR;
         double DOKUGEBUEHR;
         double LOGISTIKAUFSCHLAG;
        } kundeauskuS;
 #else /*TRANSCLASS*/
 typedef struct N_KNDAUSKU {
         double EILBOTENZUSCHLAG;
         long KUNDENNR;
         short VERTRIEBSZENTRUMNR;
         double DISPOGEBUEHR;
         double BTMGEBUEHR;
         double DOKUGEBUEHR;
         double LOGISTIKAUFSCHLAG;

			bool operator==(const N_KNDAUSKU& right) const {
			return(
				EILBOTENZUSCHLAG == right.EILBOTENZUSCHLAG &&
				KUNDENNR == right.KUNDENNR &&
				VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
				DISPOGEBUEHR == right.DISPOGEBUEHR &&
				BTMGEBUEHR == right.BTMGEBUEHR &&
				DOKUGEBUEHR == right.DOKUGEBUEHR &&
				LOGISTIKAUFSCHLAG == right.LOGISTIKAUFSCHLAG
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				EILBOTENZUSCHLAG = 0;
				KUNDENNR = 0;
				VERTRIEBSZENTRUMNR = 0;
				DISPOGEBUEHR = 0;
				BTMGEBUEHR = 0;
				DOKUGEBUEHR = 0;
				LOGISTIKAUFSCHLAG = 0;
#endif
			}
         } kundeauskuS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KNDAUSKU ****************************************/

 struct S_KNDAUSKU {
         char EILBOTENZUSCHLAG[5 + 2];
         char KUNDENNR[11];
         char VERTRIEBSZENTRUMNR[7];
         char DISPOGEBUEHR[5 + 2];
         char BTMGEBUEHR[5 + 2];
         char DOKUGEBUEHR[5 + 2];
         char LOGISTIKAUFSCHLAG[5 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KNDAUSKU ***********************/

 struct O_KNDAUSKU {
         char EILBOTENZUSCHLAG[5];
         char KUNDENNR[11];
         char VERTRIEBSZENTRUMNR[7];
         char DISPOGEBUEHR[5];
         char BTMGEBUEHR[5];
         char DOKUGEBUEHR[5];
         char LOGISTIKAUFSCHLAG[5];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KNDAUSKU **********************************/

 struct C_KNDAUSKU {
         double EILBOTENZUSCHLAG;
         long KUNDENNR;
         short VERTRIEBSZENTRUMNR;
         double DISPOGEBUEHR;
         double BTMGEBUEHR;
         double DOKUGEBUEHR;
         double LOGISTIKAUFSCHLAG;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KNDAUSKU ********************************/

 struct I_KNDAUSKU {
         short EILBOTENZUSCHLAG;
         short KUNDENNR;
         short VERTRIEBSZENTRUMNR;
         short DISPOGEBUEHR;
         short BTMGEBUEHR;
         short DOKUGEBUEHR;
         short LOGISTIKAUFSCHLAG;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KNDAUSKU ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc KNDAUSKU_BES [] =
 {
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KNDAUSKU_BES [] =
 {
   { TYP_D, 5, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
 };
#endif

/* description for datatypes of KNDAUSKU ************************************/

 #define KNDAUSKU_S390 \
         double EILBOTENZUSCHLAG; \
         long KUNDENNR; \
         short VERTRIEBSZENTRUMNR; \
         double DISPOGEBUEHR; \
         double BTMGEBUEHR; \
         double DOKUGEBUEHR; \
         double LOGISTIKAUFSCHLAG; \



/* Copy-Function Struct to single Data KNDAUSKU *****************************/

 #define KNDAUSKU_S390_COPY_TO_SINGLE(_x_) \
         EILBOTENZUSCHLAG=_x_->EILBOTENZUSCHLAG;\
         KUNDENNR=_x_->KUNDENNR;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         DISPOGEBUEHR=_x_->DISPOGEBUEHR;\
         BTMGEBUEHR=_x_->BTMGEBUEHR;\
         DOKUGEBUEHR=_x_->DOKUGEBUEHR;\
         LOGISTIKAUFSCHLAG=_x_->LOGISTIKAUFSCHLAG;\

 #define KNDAUSKU_S390_COPY_TO_STRUCT(_x_) \
          _x_->EILBOTENZUSCHLAG=EILBOTENZUSCHLAG;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->DISPOGEBUEHR=DISPOGEBUEHR;\
          _x_->BTMGEBUEHR=BTMGEBUEHR;\
          _x_->DOKUGEBUEHR=DOKUGEBUEHR;\
          _x_->LOGISTIKAUFSCHLAG=LOGISTIKAUFSCHLAG;\



/* FunctionNumber-Define of kundeausku ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kundeausku ************************************/


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

class CKNDAUSKU : public ppDadeVirtual
{
	//data members
	public:
		kundeauskuS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kundeauskuS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kundeauskuS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kundeauskuS>; Strip(s); kundeauskuS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kundeauskuS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kundeauskuS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kundeauskuS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		double		GetEilbotenzuschlag() const	{ return s.EILBOTENZUSCHLAG; }
		long		GetKundennr() const	{ return s.KUNDENNR; }
		short		GetVertriebszentrumnr() const	{ return s.VERTRIEBSZENTRUMNR; }
		double		GetDispogebuehr() const	{ return s.DISPOGEBUEHR; }
		double		GetBtmgebuehr() const	{ return s.BTMGEBUEHR; }
		double		GetDokugebuehr() const	{ return s.DOKUGEBUEHR; }
		double		GetLogistikaufschlag() const	{ return s.LOGISTIKAUFSCHLAG; }
		const kundeauskuS& GetStruct() const { return s; }
		void 		SetEilbotenzuschlag(double t) { s.EILBOTENZUSCHLAG = t; }
		void 		SetKundennr(long t) { s.KUNDENNR = t; }
		void 		SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
		void 		SetDispogebuehr(double t) { s.DISPOGEBUEHR = t; }
		void 		SetBtmgebuehr(double t) { s.BTMGEBUEHR = t; }
		void 		SetDokugebuehr(double t) { s.DOKUGEBUEHR = t; }
		void 		SetLogistikaufschlag(double t) { s.LOGISTIKAUFSCHLAG = t; }
		void 		SetStruct(const kundeauskuS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CKNDAUSKU()  //constructor
		{
			::buf_default((void *)&s, KNDAUSKU_BES, KNDAUSKU_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CKNDAUSKU()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KNDAUSKU_BES, KNDAUSKU_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, KNDAUSKU_BES, KNDAUSKU_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, KNDAUSKU_BES, KNDAUSKU_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_KNDAUSKU& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, KNDAUSKU_BES, KNDAUSKU_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KNDAUSKU *******************************************/

 #define KNDAUSKU_CREATE(x) exec sql create table x (\
         EILBOTENZUSCHLAG decimal(5,2) default 0 not null,\
         KUNDENNR integer default 0 not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         DISPOGEBUEHR decimal(5,2) default 0 not null,\
         BTMGEBUEHR decimal(5,2) default 0 not null,\
         DOKUGEBUEHR decimal(5,2) default 0 not null,\
         LOGISTIKAUFSCHLAG decimal(5,2) default 0 not null) extent size 392 next size 40 lock mode row;



/* CreateIndexStatement of KNDAUSKU *****************************************/

 #define KNDAUSKU_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_kndausku_1 on _X_(\
              idfnr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create unique index i_kndausku_2 on _X_(\
              VertriebszentrumNr,\
              KundenNr );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KNDAUSKU *****************************************/

 #define KNDAUSKU_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kndausku_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_kndausku_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

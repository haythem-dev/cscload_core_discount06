#ifndef __PP_ZAPFLEGE_H_
#define __PP_ZAPFLEGE_H_

/******************************************************************************/
/* d:\prj\df\unix\tpldzentral\zapflege ****************************************/
/******************************************************************************/

/* Length-Define of ZAPFLEGE **************************************************/

  #define L_ZAPFLEGE_ARTIKEL_NR 11
  #define L_ZAPFLEGE_DATUM 11

/* Length/Count-Define of ZAPFLEGE ********************************************/

  #define LS_ZAPFLEGE_ARTIKEL_NR 10 + 1
  #define LS_ZAPFLEGE_DATUM 10 + 1

  #define ZAPFLEGEARTIKEL_NR 0
  #define ZAPFLEGEDATUM 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ZAPFLEGE_H
 #define ZAPFLEGE_ANZ ( sizeof(ZAPFLEGE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ZAPFLEGE ******************************************************/

 #define ZAPFLEGE_LISTE \
         ZAPFLEGE.ARTIKEL_NR,\
         ZAPFLEGE.DATUM

 #define ZAPFLEGE_LISTE_390 \
         ARTIKEL_NR,\
         DATUM

 #define ZAPFLEGE_PLISTE \
         "ZAPFLEGE.ARTIKEL_NR,"\
         "ZAPFLEGE.DATUM"

 #define ZAPFLEGE_PELISTE \
         "ARTIKEL_NR,"\
         "DATUM"

 #define ZAPFLEGE_UPDLISTE \
         "ARTIKEL_NR=?,"\
         "DATUM=?"

/* SqlMacros-Define of ZAPFLEGE ***********************************************/

 #define ZAPFLEGE_ZEIGER(x) \
         :x->ARTIKEL_NR,\
         :x->DATUM

 #define ZAPFLEGE_ZEIGERSEL(x) \
         :x->ARTIKEL_NR,\
         :x->DATUM

 #define ZAPFLEGE_UPDATE(x) \
         ZAPFLEGE.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ZAPFLEGE.DATUM=:x->DATUM

/* SqlMacros390-Define of ZAPFLEGE ********************************************/

 #define ZAPFLEGE_ZEIGER_390 \
         :ARTIKEL_NR,\
         :DATUM

 #define ZAPFLEGE_UPDATE_390 \
         ARTIKEL_NR=:ARTIKEL_NR,\
         DATUM=:DATUM

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ZAPFLEGE ***********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ZAPFLEGE {
         long ARTIKEL_NR;
         long DATUM;
        } zapflegeS;
 #else /*TRANSCLASS*/
 typedef struct N_ZAPFLEGE {
         long ARTIKEL_NR;
         long DATUM;

			bool operator==(const N_ZAPFLEGE& right) const {
			return(
				ARTIKEL_NR == right.ARTIKEL_NR &&
				DATUM == right.DATUM
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				ARTIKEL_NR = 0;
				DATUM = 0;
#endif
			}
         } zapflegeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ZAPFLEGE ******************************************/

 struct S_ZAPFLEGE {
         char ARTIKEL_NR[11];
         char DATUM[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ZAPFLEGE *************************/

 struct O_ZAPFLEGE {
         char ARTIKEL_NR[11];
         char DATUM[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of ZAPFLEGE *************************************/

 struct C_ZAPFLEGE {
         long ARTIKEL_NR;
         long DATUM;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of ZAPFLEGE ***********************************/

 struct I_ZAPFLEGE {
         short ARTIKEL_NR;
         short DATUM;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ZAPFLEGE ********************************************/

#if defined (BUF_DESC)
 static struct buf_desc ZAPFLEGE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ZAPFLEGE_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of ZAPFLEGE **************************************/

 #define ZAPFLEGE_S390 \
         long ARTIKEL_NR; \
         long DATUM; \



/* Copy-Function Struct to single Data ZAPFLEGE *******************************/

 #define ZAPFLEGE_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         DATUM=_x_->DATUM;\

 #define ZAPFLEGE_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->DATUM=DATUM;\



/* FunctionNumber-Define of zapflege ******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of zapflege **************************************/


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
		virtual int SelList(int FetchRel = 1,int pos=0) = 0;
		virtual int SelListHist(int FetchRel = 1,int pos=0) = 0;
		virtual int SelListFuture(int FetchRel = 1,int pos=0) = 0;
		virtual int Load(int pos=0) = 0;
 		virtual int Delete(int pos=0) = 0;
		virtual int Save(int pos=0) = 0;
};
#endif

class CZAPFLEGE : public ppDadeVirtual
{
	//data members
	public:
		zapflegeS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<zapflegeS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<zapflegeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<zapflegeS>; Strip(s); zapflegeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<zapflegeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<zapflegeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<zapflegeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetArtikel_nr() const	{ return s.ARTIKEL_NR; }
		long		GetDatum() const	{ return s.DATUM; }
		const zapflegeS& GetStruct() const { return s; }
		void 		SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
		void 		SetDatum(long t) { s.DATUM = t; }
		void 		SetStruct(const zapflegeS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CZAPFLEGE()  //constructor
		{
			::buf_default((void *)&s,ZAPFLEGE_BES,ZAPFLEGE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CZAPFLEGE()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ZAPFLEGE_BES, ZAPFLEGE_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc=::ServerNr(pos, fkt_nr, (void *)&s,ZAPFLEGE_BES,ZAPFLEGE_ANZ, error_msg);
			#else
			rc=::Server(fkt_nr, (void *)&s,ZAPFLEGE_BES,ZAPFLEGE_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_ZAPFLEGE& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,ZAPFLEGE_BES,ZAPFLEGE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of ZAPFLEGE *********************************************/

 #define ZAPFLEGE_CREATE(x) exec sql create table x (\
         ARTIKEL_NR integer default 0 not null,\
         DATUM integer default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ZAPFLEGE *******************************************/

 #define ZAPFLEGE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_zapflege_1 on _X_(\
              artikel_nr,\
              datum );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ZAPFLEGE *******************************************/

 #define ZAPFLEGE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_zapflege_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

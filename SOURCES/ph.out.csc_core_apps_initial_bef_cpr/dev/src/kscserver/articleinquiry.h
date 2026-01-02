#ifndef __PP_ARTICLEINQUIRY_H_
#define __PP_ARTICLEINQUIRY_H_

/******************************************************************************/
/* d:\prj\orderentry\kscserver\ArticleInquiry *********************************/
/******************************************************************************/

/* Length-Define of ARTICLEINQUIRY ********************************************/

  #define L_ARTICLEINQUIRY_INFOBLOCK 4001

/* Length/Count-Define of ARTICLEINQUIRY **************************************/

  #define LS_ARTICLEINQUIRY_INFOBLOCK 4001 + 1

  #define ARTICLEINQUIRYINFOBLOCK 0

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTICLEINQUIRY_H
 #define ARTICLEINQUIRY_ANZ ( sizeof(ARTICLEINQUIRY_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLEINQUIRY ************************************************/

 #define ARTICLEINQUIRY_LISTE \
         KSCDUMMY.INFOBLOCK

 #define ARTICLEINQUIRY_LISTE_390 \
         INFOBLOCK

 #define ARTICLEINQUIRY_PLISTE \
         "KSCDUMMY.INFOBLOCK"

 #define ARTICLEINQUIRY_PELISTE \
         "INFOBLOCK"

 #define ARTICLEINQUIRY_UPDLISTE \
         "INFOBLOCK=?"

/* SqlMacros-Define of ARTICLEINQUIRY *****************************************/

 #define ARTICLEINQUIRY_ZEIGER(x) \
         :x->INFOBLOCK

 #define ARTICLEINQUIRY_ZEIGERSEL(x) \
         :x->INFOBLOCK

 #define ARTICLEINQUIRY_UPDATE(x) \
         KSCDUMMY.INFOBLOCK=:x->INFOBLOCK

/* SqlMacros390-Define of ARTICLEINQUIRY **************************************/

 #define ARTICLEINQUIRY_ZEIGER_390 \
         :INFOBLOCK

 #define ARTICLEINQUIRY_UPDATE_390 \
         INFOBLOCK=:INFOBLOCK

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTICLEINQUIRY *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTICLEINQUIRY {
         char INFOBLOCK[4002];
        } articleinquiryS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTICLEINQUIRY {
         char INFOBLOCK[4002];

			bool operator==(const N_ARTICLEINQUIRY& right) const {
			return(
				!strcmp(INFOBLOCK, right.INFOBLOCK)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				strcpy(INFOBLOCK, " " );
#endif
			}
         } articleinquiryS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLEINQUIRY ************************************/

 struct S_ARTICLEINQUIRY {
         char INFOBLOCK[4001 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLEINQUIRY *******************/

 struct O_ARTICLEINQUIRY {
         char INFOBLOCK[4001];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLEINQUIRY ******************************/

 struct C_ARTICLEINQUIRY {
         char INFOBLOCK[4002];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLEINQUIRY ****************************/

 struct I_ARTICLEINQUIRY {
         short INFOBLOCK;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLEINQUIRY **************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTICLEINQUIRY_BES [] =
 {
   { TYP_C, 4001, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTICLEINQUIRY_BES [] =
 {
   { TYP_C, 4001, 0 },
 };
#endif

/* description for datatypes of ARTICLEINQUIRY ********************************/

 #define ARTICLEINQUIRY_S390 \
         char INFOBLOCK[4002]; \



/* Copy-Function Struct to single Data ARTICLEINQUIRY *************************/

 #define ARTICLEINQUIRY_S390_COPY_TO_SINGLE(_x_) \
          strcpy(INFOBLOCK,_x_->INFOBLOCK);\

 #define ARTICLEINQUIRY_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->INFOBLOCK,INFOBLOCK);\



/* FunctionNumber-Define of ArticleInquiry ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleInquiry ********************************/


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

class CARTICLEINQUIRY : public ppDadeVirtual
{
	//data members
	public:
		articleinquiryS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<articleinquiryS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<articleinquiryS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<articleinquiryS>; Strip(s); articleinquiryS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<articleinquiryS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<articleinquiryS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<articleinquiryS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const char*	GetInfoblock(ppString& t) const 	{ t = s.INFOBLOCK; t.erasespace(ppString::END); return t.c_str(); }
		const articleinquiryS& GetStruct() const { return s; }
		void 		SetInfoblock(const ppString& t) { ppGStrCopy(s.INFOBLOCK,t.c_str() ,L_ARTICLEINQUIRY_INFOBLOCK); }
		void 		SetStruct(const articleinquiryS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CARTICLEINQUIRY()  //constructor
		{
			::buf_default((void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CARTICLEINQUIRY()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_ARTICLEINQUIRY& d)
		{
#ifdef WIN32
			ppGStripLast(d.INFOBLOCK);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of ARTICLEINQUIRY ***************************************/

 #define ARTICLEINQUIRY_CREATE(x) exec sql create table x (\
         INFOBLOCK char(4001) default " " not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ARTICLEINQUIRY *************************************/

 #define ARTICLEINQUIRY_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of ARTICLEINQUIRY *************************************/

 #define ARTICLEINQUIRY_DELETE_INDEX(_X_)\
              _X_ = 0;\

#endif

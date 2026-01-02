#ifndef __PP_KDAUFTRAGPOSXML_H_
#define __PP_KDAUFTRAGPOSXML_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\tpldauftr\kdauftragposxml ***********************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGPOSXML *******************************************/

  #define L_KDAUFTRAGPOSXML_KDAUFTRAGNR 11
  #define L_KDAUFTRAGPOSXML_POSNR 11
  #define L_KDAUFTRAGPOSXML_XMLORDERREF 40

/* Length/Count-Define of KDAUFTRAGPOSXML *************************************/

  #define LS_KDAUFTRAGPOSXML_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGPOSXML_POSNR 10 + 1
  #define LS_KDAUFTRAGPOSXML_XMLORDERREF 40 + 1

  #define KDAUFTRAGPOSXMLKDAUFTRAGNR 0
  #define KDAUFTRAGPOSXMLPOSNR 1
  #define KDAUFTRAGPOSXMLXMLORDERREF 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGPOSXML_H
 #define KDAUFTRAGPOSXML_ANZ ( sizeof(KDAUFTRAGPOSXML_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPOSXML ***********************************************/

 #define KDAUFTRAGPOSXML_LISTE \
         KDAUFTRAGPOSXML.KDAUFTRAGNR,\
         KDAUFTRAGPOSXML.POSNR,\
         KDAUFTRAGPOSXML.XMLORDERREF

 #define KDAUFTRAGPOSXML_LISTE_390 \
         KDAUFTRAGNR,\
         POSNR,\
         XMLORDERREF

 #define KDAUFTRAGPOSXML_PLISTE \
         "KDAUFTRAGPOSXML.KDAUFTRAGNR,"\
         "KDAUFTRAGPOSXML.POSNR,"\
         "KDAUFTRAGPOSXML.XMLORDERREF"

 #define KDAUFTRAGPOSXML_PELISTE \
         "KDAUFTRAGNR,"\
         "POSNR,"\
         "XMLORDERREF"

 #define KDAUFTRAGPOSXML_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "POSNR=?,"\
         "XMLORDERREF=?"

/* SqlMacros-Define of KDAUFTRAGPOSXML ****************************************/

 #define KDAUFTRAGPOSXML_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->XMLORDERREF

 #define KDAUFTRAGPOSXML_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->XMLORDERREF

 #define KDAUFTRAGPOSXML_UPDATE(x) \
         KDAUFTRAGPOSXML.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGPOSXML.POSNR=:x->POSNR,\
         KDAUFTRAGPOSXML.XMLORDERREF=:x->XMLORDERREF

/* SqlMacros390-Define of KDAUFTRAGPOSXML *************************************/

 #define KDAUFTRAGPOSXML_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :POSNR,\
         :XMLORDERREF

 #define KDAUFTRAGPOSXML_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         POSNR=:POSNR,\
         XMLORDERREF=:XMLORDERREF

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGPOSXML ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGPOSXML {
         long KDAUFTRAGNR;
         long POSNR;
         char XMLORDERREF[41];
        } kdauftragposxmlS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGPOSXML {
         long KDAUFTRAGNR;
         long POSNR;
         char XMLORDERREF[41];

			bool operator==(const N_KDAUFTRAGPOSXML& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				POSNR == right.POSNR &&
				!strcmp(XMLORDERREF, right.XMLORDERREF)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				POSNR = 0;
				strcpy(XMLORDERREF, " " );
#endif
			}
         } kdauftragposxmlS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPOSXML ***********************************/

 struct S_KDAUFTRAGPOSXML {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char XMLORDERREF[40 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPOSXML ******************/

 struct O_KDAUFTRAGPOSXML {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char XMLORDERREF[40];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPOSXML *****************************/

 struct C_KDAUFTRAGPOSXML {
         long KDAUFTRAGNR;
         long POSNR;
         char XMLORDERREF[41];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPOSXML ***************************/

 struct I_KDAUFTRAGPOSXML {
         short KDAUFTRAGNR;
         short POSNR;
         short XMLORDERREF;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPOSXML *************************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSXML_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSXML_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 40, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGPOSXML *******************************/

 #define KDAUFTRAGPOSXML_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         char XMLORDERREF[41]; \



/* Copy-Function Struct to single Data KDAUFTRAGPOSXML ************************/

 #define KDAUFTRAGPOSXML_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
          strcpy(XMLORDERREF,_x_->XMLORDERREF);\

 #define KDAUFTRAGPOSXML_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          strcpy(_x_->XMLORDERREF,XMLORDERREF);\



/* FunctionNumber-Define of kdauftragposxml ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragposxml *******************************/


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

class CKDAUFTRAGPOSXML : public ppDadeVirtual
{
	//data members
	public:
		kdauftragposxmlS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kdauftragposxmlS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragposxmlS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kdauftragposxmlS>; Strip(s); kdauftragposxmlS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragposxmlS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kdauftragposxmlS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kdauftragposxmlS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		long		GetPosnr() const	{ return s.POSNR; }
		const char*	GetXmlorderref(ppString& t) const 	{ t = s.XMLORDERREF; t.erasespace(ppString::END); return t.c_str(); }
		const kdauftragposxmlS& GetStruct() const { return s; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetPosnr(long t) { s.POSNR = t; }
		void 		SetXmlorderref(const ppString& t) { ppGStrCopy(s.XMLORDERREF,t.c_str() ,L_KDAUFTRAGPOSXML_XMLORDERREF); }
		void 		SetStruct(const kdauftragposxmlS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CKDAUFTRAGPOSXML()  //constructor
		{
			::buf_default((void *)&s, KDAUFTRAGPOSXML_BES, KDAUFTRAGPOSXML_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CKDAUFTRAGPOSXML()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KDAUFTRAGPOSXML_BES, KDAUFTRAGPOSXML_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPOSXML_BES, KDAUFTRAGPOSXML_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPOSXML_BES, KDAUFTRAGPOSXML_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_KDAUFTRAGPOSXML& d)
		{
#ifdef WIN32
			ppGStripLast(d.XMLORDERREF);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPOSXML_BES, KDAUFTRAGPOSXML_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KDAUFTRAGPOSXML **************************************/

 #define KDAUFTRAGPOSXML_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         XMLORDERREF varchar(40,0) default " " not null) in ksc extent size 3136 next size 316 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPOSXML ************************************/

 #define KDAUFTRAGPOSXML_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_posxml_1 on _X_(\
              kdauftragnr,\
              posnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPOSXML ************************************/

 #define KDAUFTRAGPOSXML_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_posxml_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

#ifndef __PP_SERVICETYPES_H_
#define __PP_SERVICETYPES_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadservices\ServiceTypes ***********************************/
/******************************************************************************/

/* Length-Define of SERVICETYPES **********************************************/

  #define L_SERVICETYPES_SERVICETYPENO 6
  #define L_SERVICETYPES_NAME 30
  #define L_SERVICETYPES_ORDER_TYPE 2

/* Length/Count-Define of SERVICETYPES ****************************************/

  #define LS_SERVICETYPES_SERVICETYPENO 5 + 1
  #define LS_SERVICETYPES_NAME 30 + 1
  #define LS_SERVICETYPES_ORDER_TYPE 2 + 1

  #define SERVICETYPESSERVICETYPENO 0
  #define SERVICETYPESNAME 1
  #define SERVICETYPESORDER_TYPE 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define SERVICETYPES_H
 #define SERVICETYPES_ANZ ( sizeof(SERVICETYPES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of SERVICETYPES **************************************************/

 #define SERVICETYPES_LISTE \
         SERVICETYPES.SERVICETYPENO,\
         SERVICETYPES.NAME,\
         SERVICETYPES.ORDER_TYPE

 #define SERVICETYPES_LISTE_390 \
         SERVICETYPENO,\
         NAME,\
         ORDER_TYPE

 #define SERVICETYPES_PLISTE \
         "SERVICETYPES.SERVICETYPENO,"\
         "SERVICETYPES.NAME,"\
         "SERVICETYPES.ORDER_TYPE"

 #define SERVICETYPES_PELISTE \
         "SERVICETYPENO,"\
         "NAME,"\
         "ORDER_TYPE"

 #define SERVICETYPES_UPDLISTE \
         "SERVICETYPENO=?,"\
         "NAME=?,"\
         "ORDER_TYPE=?"

/* SqlMacros-Define of SERVICETYPES *******************************************/

 #define SERVICETYPES_ZEIGER(x) \
         :x->SERVICETYPENO,\
         :x->NAME,\
         :x->ORDER_TYPE

 #define SERVICETYPES_ZEIGERSEL(x) \
         :x->SERVICETYPENO,\
         :x->NAME,\
         :x->ORDER_TYPE

 #define SERVICETYPES_UPDATE(x) \
         SERVICETYPES.SERVICETYPENO=:x->SERVICETYPENO,\
         SERVICETYPES.NAME=:x->NAME,\
         SERVICETYPES.ORDER_TYPE=:x->ORDER_TYPE

/* SqlMacros390-Define of SERVICETYPES ****************************************/

 #define SERVICETYPES_ZEIGER_390 \
         :SERVICETYPENO,\
         :NAME,\
         :ORDER_TYPE

 #define SERVICETYPES_UPDATE_390 \
         SERVICETYPENO=:SERVICETYPENO,\
         NAME=:NAME,\
         ORDER_TYPE=:ORDER_TYPE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of SERVICETYPES *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_SERVICETYPES {
         short SERVICETYPENO;
         char NAME[31];
         char ORDER_TYPE[3];
        } servicetypesS;
 #else /*TRANSCLASS*/
 typedef struct N_SERVICETYPES {
         short SERVICETYPENO;
         char NAME[31];
         char ORDER_TYPE[3];

			bool operator==(const N_SERVICETYPES& right) const {
			return(
				SERVICETYPENO == right.SERVICETYPENO &&
				!strcmp(NAME, right.NAME) &&
				!strcmp(ORDER_TYPE, right.ORDER_TYPE)
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				SERVICETYPENO = 0;
				strcpy(NAME, " " );
				strcpy(ORDER_TYPE, " " );
#endif
			}
         } servicetypesS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of SERVICETYPES **************************************/

 struct S_SERVICETYPES {
         char SERVICETYPENO[7];
         char NAME[30 + 1];
         char ORDER_TYPE[2 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of SERVICETYPES *********************/

 struct O_SERVICETYPES {
         char SERVICETYPENO[7];
         char NAME[30];
         char ORDER_TYPE[2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of SERVICETYPES ********************************/

 struct C_SERVICETYPES {
         short SERVICETYPENO;
         char NAME[31];
         char ORDER_TYPE[3];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of SERVICETYPES ******************************/

 struct I_SERVICETYPES {
         short SERVICETYPENO;
         short NAME;
         short ORDER_TYPE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of SERVICETYPES ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc SERVICETYPES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 2, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc SERVICETYPES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 2, 0 },
 };
#endif

/* description for datatypes of SERVICETYPES **********************************/

 #define SERVICETYPES_S390 \
         short SERVICETYPENO; \
         char NAME[31]; \
         char ORDER_TYPE[3]; \



/* Copy-Function Struct to single Data SERVICETYPES ***************************/

 #define SERVICETYPES_S390_COPY_TO_SINGLE(_x_) \
         SERVICETYPENO=_x_->SERVICETYPENO;\
          strcpy(NAME,_x_->NAME);\
          strcpy(ORDER_TYPE,_x_->ORDER_TYPE);\

 #define SERVICETYPES_S390_COPY_TO_STRUCT(_x_) \
          _x_->SERVICETYPENO=SERVICETYPENO;\
          strcpy(_x_->NAME,NAME);\
          strcpy(_x_->ORDER_TYPE,ORDER_TYPE);\



/* FunctionNumber-Define of ServiceTypes **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ServiceTypes **********************************/


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

class CSERVICETYPES : public ppDadeVirtual
{
	//data members
	public:
		servicetypesS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<servicetypesS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<servicetypesS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<servicetypesS>; Strip(s); servicetypesS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<servicetypesS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<servicetypesS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<servicetypesS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetServicetypeno() const	{ return s.SERVICETYPENO; }
		const char*	GetName(ppString& t) const 	{ t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetOrder_type(ppString& t) const 	{ t = s.ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
		const servicetypesS& GetStruct() const { return s; }
		void 		SetServicetypeno(short t) { s.SERVICETYPENO = t; }
		void 		SetName(const ppString& t) { ppGStrCopy(s.NAME,t.c_str() ,L_SERVICETYPES_NAME); }
		void 		SetOrder_type(const ppString& t) { ppGStrCopy(s.ORDER_TYPE,t.c_str() ,L_SERVICETYPES_ORDER_TYPE); }
		void 		SetStruct(const servicetypesS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CSERVICETYPES()  //constructor
		{
			::buf_default((void *)&s, SERVICETYPES_BES, SERVICETYPES_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CSERVICETYPES()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, SERVICETYPES_BES, SERVICETYPES_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, SERVICETYPES_BES, SERVICETYPES_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, SERVICETYPES_BES, SERVICETYPES_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_SERVICETYPES& d)
		{
#ifdef WIN32
			ppGStripLast(d.NAME);
			ppGStripLast(d.ORDER_TYPE);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, SERVICETYPES_BES, SERVICETYPES_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of SERVICETYPES *****************************************/

 #define SERVICETYPES_CREATE(x) exec sql create table x (\
         SERVICETYPENO smallint default 0 not null,\
         NAME char(30) default " " not null,\
         ORDER_TYPE char(2) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of SERVICETYPES ***************************************/

 #define SERVICETYPES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_servicetypes_1 on _X_(\
              servicetypeno ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of SERVICETYPES ***************************************/

 #define SERVICETYPES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_servicetypes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

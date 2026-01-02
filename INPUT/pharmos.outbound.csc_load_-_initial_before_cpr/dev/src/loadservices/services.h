#ifndef __PP_SERVICES_H_
#define __PP_SERVICES_H_

/******************************************************************************/
/* d:\prj\DF\UNIX\loadservices\Services ***************************************/
/******************************************************************************/

/* Length-Define of SERVICES **************************************************/

  #define L_SERVICES_SERVICE_NO 6
  #define L_SERVICES_NAME 30
  #define L_SERVICES_SERVICETYPENO 6

/* Length/Count-Define of SERVICES ********************************************/

  #define LS_SERVICES_SERVICE_NO 5 + 1
  #define LS_SERVICES_NAME 30 + 1
  #define LS_SERVICES_SERVICETYPENO 5 + 1

  #define SERVICESSERVICE_NO 0
  #define SERVICESNAME 1
  #define SERVICESSERVICETYPENO 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define SERVICES_H
 #define SERVICES_ANZ ( sizeof(SERVICES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of SERVICES ******************************************************/

 #define SERVICES_LISTE \
         SERVICES.SERVICE_NO,\
         SERVICES.NAME,\
         SERVICES.SERVICETYPENO

 #define SERVICES_LISTE_390 \
         SERVICE_NO,\
         NAME,\
         SERVICETYPENO

 #define SERVICES_PLISTE \
         "SERVICES.SERVICE_NO,"\
         "SERVICES.NAME,"\
         "SERVICES.SERVICETYPENO"

 #define SERVICES_PELISTE \
         "SERVICE_NO,"\
         "NAME,"\
         "SERVICETYPENO"

 #define SERVICES_UPDLISTE \
         "SERVICE_NO=?,"\
         "NAME=?,"\
         "SERVICETYPENO=?"

/* SqlMacros-Define of SERVICES ***********************************************/

 #define SERVICES_ZEIGER(x) \
         :x->SERVICE_NO,\
         :x->NAME,\
         :x->SERVICETYPENO

 #define SERVICES_ZEIGERSEL(x) \
         :x->SERVICE_NO,\
         :x->NAME,\
         :x->SERVICETYPENO

 #define SERVICES_UPDATE(x) \
         SERVICES.SERVICE_NO=:x->SERVICE_NO,\
         SERVICES.NAME=:x->NAME,\
         SERVICES.SERVICETYPENO=:x->SERVICETYPENO

/* SqlMacros390-Define of SERVICES ********************************************/

 #define SERVICES_ZEIGER_390 \
         :SERVICE_NO,\
         :NAME,\
         :SERVICETYPENO

 #define SERVICES_UPDATE_390 \
         SERVICE_NO=:SERVICE_NO,\
         NAME=:NAME,\
         SERVICETYPENO=:SERVICETYPENO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of SERVICES ***********************************************/

 #ifndef TRANSCLASS
 typedef struct N_SERVICES {
         short SERVICE_NO;
         char NAME[31];
         short SERVICETYPENO;
        } servicesS;
 #else /*TRANSCLASS*/
 typedef struct N_SERVICES {
         short SERVICE_NO;
         char NAME[31];
         short SERVICETYPENO;

			bool operator==(const N_SERVICES& right) const {
			return(
				SERVICE_NO == right.SERVICE_NO &&
				!strcmp(NAME, right.NAME) &&
				SERVICETYPENO == right.SERVICETYPENO
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				SERVICE_NO = 0;
				strcpy(NAME, " " );
				SERVICETYPENO = 0;
#endif
			}
         } servicesS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of SERVICES ******************************************/

 struct S_SERVICES {
         char SERVICE_NO[7];
         char NAME[30 + 1];
         char SERVICETYPENO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of SERVICES *************************/

 struct O_SERVICES {
         char SERVICE_NO[7];
         char NAME[30];
         char SERVICETYPENO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of SERVICES ************************************/

 struct C_SERVICES {
         short SERVICE_NO;
         char NAME[31];
         short SERVICETYPENO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of SERVICES **********************************/

 struct I_SERVICES {
         short SERVICE_NO;
         short NAME;
         short SERVICETYPENO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of SERVICES ********************************************/

#if defined (BUF_DESC)
 static struct buf_desc SERVICES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc SERVICES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of SERVICES **************************************/

 #define SERVICES_S390 \
         short SERVICE_NO; \
         char NAME[31]; \
         short SERVICETYPENO; \



/* Copy-Function Struct to single Data SERVICES *******************************/

 #define SERVICES_S390_COPY_TO_SINGLE(_x_) \
         SERVICE_NO=_x_->SERVICE_NO;\
          strcpy(NAME,_x_->NAME);\
         SERVICETYPENO=_x_->SERVICETYPENO;\

 #define SERVICES_S390_COPY_TO_STRUCT(_x_) \
          _x_->SERVICE_NO=SERVICE_NO;\
          strcpy(_x_->NAME,NAME);\
          _x_->SERVICETYPENO=SERVICETYPENO;\



/* FunctionNumber-Define of Services ******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Services **************************************/


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

class CSERVICES : public ppDadeVirtual
{
	//data members
	public:
		servicesS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<servicesS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<servicesS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<servicesS>; Strip(s); servicesS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<servicesS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<servicesS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<servicesS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetService_no() const	{ return s.SERVICE_NO; }
		const char*	GetName(ppString& t) const 	{ t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
		short		GetServicetypeno() const	{ return s.SERVICETYPENO; }
		const servicesS& GetStruct() const { return s; }
		void 		SetService_no(short t) { s.SERVICE_NO = t; }
		void 		SetName(const ppString& t) { ppGStrCopy(s.NAME,t.c_str() ,L_SERVICES_NAME); }
		void 		SetServicetypeno(short t) { s.SERVICETYPENO = t; }
		void 		SetStruct(const servicesS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CSERVICES()  //constructor
		{
			::buf_default((void *)&s, SERVICES_BES, SERVICES_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CSERVICES()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, SERVICES_BES, SERVICES_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, SERVICES_BES, SERVICES_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, SERVICES_BES, SERVICES_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_SERVICES& d)
		{
#ifdef WIN32
			ppGStripLast(d.NAME);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, SERVICES_BES, SERVICES_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of SERVICES *********************************************/

 #define SERVICES_CREATE(x) exec sql create table x (\
         SERVICE_NO smallint default 0 not null,\
         NAME char(30) default " " not null,\
         SERVICETYPENO smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of SERVICES *******************************************/

 #define SERVICES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_services_1 on _X_(\
              service_no ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of SERVICES *******************************************/

 #define SERVICES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_services_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

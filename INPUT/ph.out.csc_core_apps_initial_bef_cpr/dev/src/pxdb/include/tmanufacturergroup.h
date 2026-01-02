#ifndef __PP_MANUFACTURERGROUP_H_
#define __PP_MANUFACTURERGROUP_H_

/******************************************************************************/
/* d:\prj\AS\pxdb\include\ManufacturerGroup ***********************************/
/******************************************************************************/

/* Length-Define of MANUFACTURERGROUP *****************************************/

  #define L_MANUFACTURERGROUP_PHARMACYGROUPID 3
  #define L_MANUFACTURERGROUP_KONSIG_PARTNER_NR 11

/* Length/Count-Define of MANUFACTURERGROUP ***********************************/

  #define LS_MANUFACTURERGROUP_PHARMACYGROUPID 3 + 1
  #define LS_MANUFACTURERGROUP_KONSIG_PARTNER_NR 10 + 1

  #define MANUFACTURERGROUPPHARMACYGROUPID 0
  #define MANUFACTURERGROUPKONSIG_PARTNER_NR 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define MANUFACTURERGROUP_H
 #define MANUFACTURERGROUP_ANZ ( sizeof(MANUFACTURERGROUP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of MANUFACTURERGROUP *********************************************/

 #define MANUFACTURERGROUP_LISTE \
         MANUFACTURERGROUP.PHARMACYGROUPID,\
         MANUFACTURERGROUP.KONSIG_PARTNER_NR

 #define MANUFACTURERGROUP_LISTE_390 \
         PHARMACYGROUPID,\
         KONSIG_PARTNER_NR

 #define MANUFACTURERGROUP_PLISTE \
         "MANUFACTURERGROUP.PHARMACYGROUPID,"\
         "MANUFACTURERGROUP.KONSIG_PARTNER_NR"

 #define MANUFACTURERGROUP_PELISTE \
         "PHARMACYGROUPID,"\
         "KONSIG_PARTNER_NR"

 #define MANUFACTURERGROUP_UPDLISTE \
         "PHARMACYGROUPID=?,"\
         "KONSIG_PARTNER_NR=?"

/* SqlMacros-Define of MANUFACTURERGROUP **************************************/

 #define MANUFACTURERGROUP_ZEIGER(x) \
         :x->PHARMACYGROUPID,\
         :x->KONSIG_PARTNER_NR

 #define MANUFACTURERGROUP_ZEIGERSEL(x) \
         :x->PHARMACYGROUPID,\
         :x->KONSIG_PARTNER_NR

 #define MANUFACTURERGROUP_UPDATE(x) \
         MANUFACTURERGROUP.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         MANUFACTURERGROUP.KONSIG_PARTNER_NR=:x->KONSIG_PARTNER_NR

/* SqlMacros390-Define of MANUFACTURERGROUP ***********************************/

 #define MANUFACTURERGROUP_ZEIGER_390 \
         :PHARMACYGROUPID,\
         :KONSIG_PARTNER_NR

 #define MANUFACTURERGROUP_UPDATE_390 \
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         KONSIG_PARTNER_NR=:KONSIG_PARTNER_NR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of MANUFACTURERGROUP **************************************/

 #ifndef TRANSCLASS
 typedef struct N_MANUFACTURERGROUP {
         char PHARMACYGROUPID[4];
         long KONSIG_PARTNER_NR;
        } manufacturergroupS;
 #else /*TRANSCLASS*/
 typedef struct N_MANUFACTURERGROUP {
         char PHARMACYGROUPID[4];
         long KONSIG_PARTNER_NR;

			bool operator==(const N_MANUFACTURERGROUP& right) const {
			return(
				!strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
				KONSIG_PARTNER_NR == right.KONSIG_PARTNER_NR
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				strcpy(PHARMACYGROUPID, " " );
				KONSIG_PARTNER_NR = 0;
#endif
			}
         } manufacturergroupS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of MANUFACTURERGROUP *********************************/

 struct S_MANUFACTURERGROUP {
         char PHARMACYGROUPID[3 + 1];
         char KONSIG_PARTNER_NR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of MANUFACTURERGROUP ****************/

 struct O_MANUFACTURERGROUP {
         char PHARMACYGROUPID[3];
         char KONSIG_PARTNER_NR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of MANUFACTURERGROUP ***************************/

 struct C_MANUFACTURERGROUP {
         char PHARMACYGROUPID[4];
         long KONSIG_PARTNER_NR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of MANUFACTURERGROUP *************************/

 struct I_MANUFACTURERGROUP {
         short PHARMACYGROUPID;
         short KONSIG_PARTNER_NR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of MANUFACTURERGROUP ***********************************/

#if defined (BUF_DESC)
 static struct buf_desc MANUFACTURERGROUP_BES [] =
 {
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc MANUFACTURERGROUP_BES [] =
 {
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of MANUFACTURERGROUP *****************************/

 #define MANUFACTURERGROUP_S390 \
         char PHARMACYGROUPID[4]; \
         long KONSIG_PARTNER_NR; \



/* Copy-Function Struct to single Data MANUFACTURERGROUP **********************/

 #define MANUFACTURERGROUP_S390_COPY_TO_SINGLE(_x_) \
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         KONSIG_PARTNER_NR=_x_->KONSIG_PARTNER_NR;\

 #define MANUFACTURERGROUP_S390_COPY_TO_STRUCT(_x_) \
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->KONSIG_PARTNER_NR=KONSIG_PARTNER_NR;\



/* FunctionNumber-Define of ManufacturerGroup *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ManufacturerGroup *****************************/


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

class CMANUFACTURERGROUP : public ppDadeVirtual
{
	//data members
	public:
		manufacturergroupS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<manufacturergroupS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<manufacturergroupS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<manufacturergroupS>; Strip(s); manufacturergroupS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<manufacturergroupS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<manufacturergroupS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<manufacturergroupS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const char*	GetPharmacygroupid(ppString& t) const 	{ t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
		long		GetKonsig_partner_nr() const	{ return s.KONSIG_PARTNER_NR; }
		const manufacturergroupS& GetStruct() const { return s; }
		void 		SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_MANUFACTURERGROUP_PHARMACYGROUPID); }
		void 		SetKonsig_partner_nr(long t) { s.KONSIG_PARTNER_NR = t; }
		void 		SetStruct(const manufacturergroupS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CMANUFACTURERGROUP()  //constructor
		{
			::buf_default((void *)&s, MANUFACTURERGROUP_BES, MANUFACTURERGROUP_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CMANUFACTURERGROUP()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, MANUFACTURERGROUP_BES, MANUFACTURERGROUP_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, MANUFACTURERGROUP_BES, MANUFACTURERGROUP_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, MANUFACTURERGROUP_BES, MANUFACTURERGROUP_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_MANUFACTURERGROUP& d)
		{
#ifdef WIN32
			ppGStripLast(d.PHARMACYGROUPID);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, MANUFACTURERGROUP_BES, MANUFACTURERGROUP_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of MANUFACTURERGROUP ************************************/

 #define MANUFACTURERGROUP_CREATE(x) exec sql create table x (\
         PHARMACYGROUPID char(3) default " " not null,\
         KONSIG_PARTNER_NR integer default 0 not null) in ksc extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of MANUFACTURERGROUP **********************************/

 #define MANUFACTURERGROUP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of MANUFACTURERGROUP **********************************/

 #define MANUFACTURERGROUP_DELETE_INDEX(_X_)\
              _X_ = 0;\

#endif

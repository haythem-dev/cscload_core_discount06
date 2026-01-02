#ifndef __PP_KUNDELAGERINFO_H_
#define __PP_KUNDELAGERINFO_H_

/******************************************************************************/
/* c:\prj\df\unix\tpldknd\kundelagerinfo **************************************/
/******************************************************************************/

/* Length-Define of KUNDELAGERINFO ********************************************/

  #define L_KUNDELAGERINFO_FILIALNR 6
  #define L_KUNDELAGERINFO_VERTRIEBSZENTRUMNR 6
  #define L_KUNDELAGERINFO_KUNDENNR 11
  #define L_KUNDELAGERINFO_ENTFERNUNGINKM 6
  #define L_KUNDELAGERINFO_KZUPD 1

/* Length/Count-Define of KUNDELAGERINFO **************************************/

  #define LS_KUNDELAGERINFO_FILIALNR 5 + 1
  #define LS_KUNDELAGERINFO_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_KUNDELAGERINFO_KUNDENNR 10 + 1
  #define LS_KUNDELAGERINFO_ENTFERNUNGINKM 5 + 1
  #define LS_KUNDELAGERINFO_KZUPD 1 + 1

  #define KUNDELAGERINFOFILIALNR 0
  #define KUNDELAGERINFOVERTRIEBSZENTRUMNR 1
  #define KUNDELAGERINFOKUNDENNR 2
  #define KUNDELAGERINFOENTFERNUNGINKM 3
  #define KUNDELAGERINFOKZUPD 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KUNDELAGERINFO_H
 #define KUNDELAGERINFO_ANZ ( sizeof(KUNDELAGERINFO_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KUNDELAGERINFO ************************************************/

 #define KUNDELAGERINFO_LISTE \
         KUNDELAGERINFO.FILIALNR,\
         KUNDELAGERINFO.VERTRIEBSZENTRUMNR,\
         KUNDELAGERINFO.KUNDENNR,\
         KUNDELAGERINFO.ENTFERNUNGINKM,\
         KUNDELAGERINFO.KZUPD

 #define KUNDELAGERINFO_LISTE_390 \
         FILIALNR,\
         VERTRIEBSZENTRUMNR,\
         KUNDENNR,\
         ENTFERNUNGINKM,\
         KZUPD

 #define KUNDELAGERINFO_PLISTE \
         "KUNDELAGERINFO.FILIALNR,"\
         "KUNDELAGERINFO.VERTRIEBSZENTRUMNR,"\
         "KUNDELAGERINFO.KUNDENNR,"\
         "KUNDELAGERINFO.ENTFERNUNGINKM,"\
         "KUNDELAGERINFO.KZUPD"

 #define KUNDELAGERINFO_PELISTE \
         "FILIALNR,"\
         "VERTRIEBSZENTRUMNR,"\
         "KUNDENNR,"\
         "ENTFERNUNGINKM,"\
         "KZUPD"

 #define KUNDELAGERINFO_UPDLISTE \
         "FILIALNR=?,"\
         "VERTRIEBSZENTRUMNR=?,"\
         "KUNDENNR=?,"\
         "ENTFERNUNGINKM=?,"\
         "KZUPD=?"

/* SqlMacros-Define of KUNDELAGERINFO *****************************************/

 #define KUNDELAGERINFO_ZEIGER(x) \
         :x->FILIALNR,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->ENTFERNUNGINKM,\
         :x->KZUPD

 #define KUNDELAGERINFO_UPDATE(x) \
         KUNDELAGERINFO.FILIALNR=:x->FILIALNR,\
         KUNDELAGERINFO.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         KUNDELAGERINFO.KUNDENNR=:x->KUNDENNR,\
         KUNDELAGERINFO.ENTFERNUNGINKM=:x->ENTFERNUNGINKM,\
         KUNDELAGERINFO.KZUPD=:x->KZUPD

/* SqlMacros390-Define of KUNDELAGERINFO **************************************/

 #define KUNDELAGERINFO_ZEIGER_390 \
         :FILIALNR,\
         :VERTRIEBSZENTRUMNR,\
         :KUNDENNR,\
         :ENTFERNUNGINKM,\
         :KZUPD

 #define KUNDELAGERINFO_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         KUNDENNR=:KUNDENNR,\
         ENTFERNUNGINKM=:ENTFERNUNGINKM,\
         KZUPD=:KZUPD

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KUNDELAGERINFO *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_KUNDELAGERINFO {
         short FILIALNR;
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         short ENTFERNUNGINKM;
         char KZUPD[2];
        } kundelagerinfoS;
 #else /*TRANSCLASS*/
 typedef struct N_KUNDELAGERINFO {
         short FILIALNR;
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         short ENTFERNUNGINKM;
         char KZUPD[2];

			bool operator==(const N_KUNDELAGERINFO& right) const {
			return(
				FILIALNR == right.FILIALNR &&
				VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
				KUNDENNR == right.KUNDENNR &&
				ENTFERNUNGINKM == right.ENTFERNUNGINKM &&
				!strcmp(KZUPD, right.KZUPD)
				);
			}
			void clear() { memset((char*)this,0,sizeof(*this)); }
         } kundelagerinfoS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KUNDELAGERINFO ************************************/

 struct S_KUNDELAGERINFO {
         char FILIALNR[7];
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char ENTFERNUNGINKM[7];
         char KZUPD[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KUNDELAGERINFO *******************/

 struct O_KUNDELAGERINFO {
         char FILIALNR[7];
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char ENTFERNUNGINKM[7];
         char KZUPD[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of KUNDELAGERINFO *******************************/

 struct C_KUNDELAGERINFO {
         short FILIALNR;
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         short ENTFERNUNGINKM;
         char KZUPD;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of KUNDELAGERINFO *****************************/

 struct I_KUNDELAGERINFO {
         short FILIALNR;
         short VERTRIEBSZENTRUMNR;
         short KUNDENNR;
         short ENTFERNUNGINKM;
         short KZUPD;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KUNDELAGERINFO **************************************/

#if defined (BUF_DESC)
 static struct buf_desc KUNDELAGERINFO_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KUNDELAGERINFO_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of KUNDELAGERINFO ********************************/

 #define KUNDELAGERINFO_S390 \
         short FILIALNR; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         short ENTFERNUNGINKM; \
         char KZUPD; \



/* Copy-Function Struct to single Data KUNDELAGERINFO *************************/

 #define KUNDELAGERINFO_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         ENTFERNUNGINKM=_x_->ENTFERNUNGINKM;\
         KZUPD=_x_->KZUPD;\

 #define KUNDELAGERINFO_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->ENTFERNUNGINKM=ENTFERNUNGINKM;\
          _x_->KZUPD=KZUPD;\



/* FunctionNumber-Define of kundelagerinfo ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kundelagerinfo ********************************/


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
		virtual int SelList(int FetchRel = 1,int pos=0)	{ return 1; }
		virtual int SelListHist(int FetchRel = 1,int pos=0)	{ return 1; }
		virtual int SelListFuture(int FetchRel = 1,int pos=0)	{ return 1; }
};
#endif

class CKUNDELAGERINFO : public ppDadeVirtual
{
	//data members
	public:
		kundelagerinfoS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kundelagerinfoS> *pl; // pointer to class list

	//functions
	public:

		const int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) {	if (GetSize() <= i)	return false; vector<kundelagerinfoS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<kundelagerinfoS>; Strip(s); kundelagerinfoS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kundelagerinfoS>::iterator itPtr = pl->begin() + i; if ( itPtr ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kundelagerinfoS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kundelagerinfoS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const short&		GetFilialnr() const	{ return s.FILIALNR; }
		const short&		GetVertriebszentrumnr() const	{ return s.VERTRIEBSZENTRUMNR; }
		const long&		GetKundennr() const	{ return s.KUNDENNR; }
		const short&		GetEntfernunginkm() const	{ return s.ENTFERNUNGINKM; }
		const char&		GetKzupd() const	{ return s.KZUPD[0]; }
		const kundelagerinfoS& GetStruct() const { return s; }
		void 		SetFilialnr(short t) { s.FILIALNR = t; }
		void 		SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
		void 		SetKundennr(long t) { s.KUNDENNR = t; }
		void 		SetEntfernunginkm(short t) { s.ENTFERNUNGINKM = t; }
		void 		SetKzupd(char t) { s.KZUPD[0] = t; s.KZUPD[1] = '\0';}
		void 		SetStruct(const kundelagerinfoS& t) { s = t; }

		CKUNDELAGERINFO()  //constructor
		{
			::buf_default((void *)&s,KUNDELAGERINFO_BES,KUNDELAGERINFO_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		~CKUNDELAGERINFO()  //destructor
		{
			if(pl) delete pl;
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KUNDELAGERINFO_BES, KUNDELAGERINFO_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_KUNDELAGERINFO& d)
		{
		}

		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,KUNDELAGERINFO_BES,KUNDELAGERINFO_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KUNDELAGERINFO ***************************************/

 #define KUNDELAGERINFO_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         ENTFERNUNGINKM smallint default 0 not null,\
         KZUPD char(1) default " " not null) in phosix extent size 8 lock mode row;



/* CreateIndexStatement of KUNDELAGERINFO *************************************/

 #define KUNDELAGERINFO_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_KundeLagerInfo_1 on _X_(\
              filialnr,\
              VertriebszentrumNr,\
              KundenNr ) in phosix1;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KUNDELAGERINFO *************************************/

 #define KUNDELAGERINFO_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_KundeLagerInfo_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\


#endif

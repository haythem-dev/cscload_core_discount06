#ifndef __PP_TCUSTPHG_H_
#define __PP_TCUSTPHG_H_

/******************************************************************************/
/* v:/nordat/CustomerPharmacyGr ***********************************************/
/******************************************************************************/

/* Length-Define of CUSTOMERPHARMACYGR ****************************************/

  #define L_CUSTOMERPHARMACYGR_CUSTOMERNO 11
  #define L_CUSTOMERPHARMACYGR_BRANCHNO 6
  #define L_CUSTOMERPHARMACYGR_PHARMACYGROUPID 3
  #define L_CUSTOMERPHARMACYGR_RANKING 6

/* Length/Count-Define of CUSTOMERPHARMACYGR **********************************/

  #define LS_CUSTOMERPHARMACYGR_CUSTOMERNO 10 + 1
  #define LS_CUSTOMERPHARMACYGR_BRANCHNO 5 + 1
  #define LS_CUSTOMERPHARMACYGR_PHARMACYGROUPID 3 + 1
  #define LS_CUSTOMERPHARMACYGR_RANKING 5 + 1

  #define CUSTOMERPHARMACYGRCUSTOMERNO 0
  #define CUSTOMERPHARMACYGRBRANCHNO 1
  #define CUSTOMERPHARMACYGRPHARMACYGROUPID 2
  #define CUSTOMERPHARMACYGRRANKING 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CUSTOMERPHARMACYGR_H
 #define CUSTOMERPHARMACYGR_ANZ ( sizeof(CUSTOMERPHARMACYGR_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CUSTOMERPHARMACYGR ********************************************/

 #define CUSTOMERPHARMACYGR_LISTE \
         CUSTOMERPHARMACYGR.CUSTOMERNO,\
         CUSTOMERPHARMACYGR.BRANCHNO,\
         CUSTOMERPHARMACYGR.PHARMACYGROUPID,\
         CUSTOMERPHARMACYGR.RANKING

 #define CUSTOMERPHARMACYGR_LISTE_390 \
         CUSTOMERNO,\
         BRANCHNO,\
         PHARMACYGROUPID,\
         RANKING

 #define CUSTOMERPHARMACYGR_PLISTE \
         "CUSTOMERPHARMACYGR.CUSTOMERNO,"\
         "CUSTOMERPHARMACYGR.BRANCHNO,"\
         "CUSTOMERPHARMACYGR.PHARMACYGROUPID,"\
         "CUSTOMERPHARMACYGR.RANKING"

 #define CUSTOMERPHARMACYGR_PELISTE \
         "CUSTOMERNO,"\
         "BRANCHNO,"\
         "PHARMACYGROUPID,"\
         "RANKING"

 #define CUSTOMERPHARMACYGR_UPDLISTE \
         "CUSTOMERNO=?,"\
         "BRANCHNO=?,"\
         "PHARMACYGROUPID=?,"\
         "RANKING=?"

/* SqlMacros-Define of CUSTOMERPHARMACYGR *************************************/

 #define CUSTOMERPHARMACYGR_ZEIGER(x) \
         :x->CUSTOMERNO,\
         :x->BRANCHNO,\
         :x->PHARMACYGROUPID,\
         :x->RANKING

 #define CUSTOMERPHARMACYGR_ZEIGERSEL(x) \
         :x->CUSTOMERNO,\
         :x->BRANCHNO,\
         :x->PHARMACYGROUPID,\
         :x->RANKING

 #define CUSTOMERPHARMACYGR_UPDATE(x) \
         CUSTOMERPHARMACYGR.CUSTOMERNO=:x->CUSTOMERNO,\
         CUSTOMERPHARMACYGR.BRANCHNO=:x->BRANCHNO,\
         CUSTOMERPHARMACYGR.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         CUSTOMERPHARMACYGR.RANKING=:x->RANKING

/* SqlMacros390-Define of CUSTOMERPHARMACYGR **********************************/

 #define CUSTOMERPHARMACYGR_ZEIGER_390 \
         :CUSTOMERNO,\
         :BRANCHNO,\
         :PHARMACYGROUPID,\
         :RANKING

 #define CUSTOMERPHARMACYGR_UPDATE_390 \
         CUSTOMERNO=:CUSTOMERNO,\
         BRANCHNO=:BRANCHNO,\
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         RANKING=:RANKING

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CUSTOMERPHARMACYGR *************************************/

 #ifndef TRANSCLASS
 typedef struct N_CUSTOMERPHARMACYGR {
         long CUSTOMERNO;
         short BRANCHNO;
         char PHARMACYGROUPID[4];
         short RANKING;
        } customerpharmacygrS;
 #else /*TRANSCLASS*/
 typedef struct N_CUSTOMERPHARMACYGR {
         long CUSTOMERNO;
         short BRANCHNO;
         char PHARMACYGROUPID[4];
         short RANKING;

                        bool operator==(const N_CUSTOMERPHARMACYGR& right) const {
                        return(
                                CUSTOMERNO == right.CUSTOMERNO &&
                                BRANCHNO == right.BRANCHNO &&
                                !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
                                RANKING == right.RANKING
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                CUSTOMERNO = 0;
                                BRANCHNO = 0;
                                strcpy(PHARMACYGROUPID, " " );
                                RANKING = 0;
#endif
                        }
         } customerpharmacygrS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CUSTOMERPHARMACYGR ********************************/

 struct S_CUSTOMERPHARMACYGR {
         char CUSTOMERNO[11];
         char BRANCHNO[7];
         char PHARMACYGROUPID[3 + 1];
         char RANKING[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CUSTOMERPHARMACYGR ***************/

 struct O_CUSTOMERPHARMACYGR {
         char CUSTOMERNO[11];
         char BRANCHNO[7];
         char PHARMACYGROUPID[3];
         char RANKING[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of CUSTOMERPHARMACYGR ***************************/

 struct C_CUSTOMERPHARMACYGR {
         long CUSTOMERNO;
         short BRANCHNO;
         char PHARMACYGROUPID[4];
         short RANKING;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of CUSTOMERPHARMACYGR *************************/

 struct I_CUSTOMERPHARMACYGR {
         short CUSTOMERNO;
         short BRANCHNO;
         short PHARMACYGROUPID;
         short RANKING;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CUSTOMERPHARMACYGR **********************************/

#if defined (BUF_DESC)
 static struct buf_desc CUSTOMERPHARMACYGR_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CUSTOMERPHARMACYGR_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 3, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of CUSTOMERPHARMACYGR ****************************/

 #define CUSTOMERPHARMACYGR_S390 \
         long CUSTOMERNO; \
         short BRANCHNO; \
         char PHARMACYGROUPID[4]; \
         short RANKING; \



/* Copy-Function Struct to single Data CUSTOMERPHARMACYGR *********************/

 #define CUSTOMERPHARMACYGR_S390_COPY_TO_SINGLE(_x_) \
         CUSTOMERNO=_x_->CUSTOMERNO;\
         BRANCHNO=_x_->BRANCHNO;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         RANKING=_x_->RANKING;\

 #define CUSTOMERPHARMACYGR_S390_COPY_TO_STRUCT(_x_) \
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->BRANCHNO=BRANCHNO;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->RANKING=RANKING;\



/* FunctionNumber-Define of CustomerPharmacyGr ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CustomerPharmacyGr ****************************/


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

class CCUSTOMERPHARMACYGR : public ppDadeVirtual
{
        //data members
        public:
                customerpharmacygrS s;
                int rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<customerpharmacygrS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<customerpharmacygrS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<customerpharmacygrS>; Strip(s); customerpharmacygrS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<customerpharmacygrS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<customerpharmacygrS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<customerpharmacygrS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                short           GetBranchno() const     { return s.BRANCHNO; }
                const char*     GetPharmacygroupid(ppString& t) const   { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
                short           GetRanking() const      { return s.RANKING; }
                const customerpharmacygrS& GetStruct() const { return s; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_CUSTOMERPHARMACYGR_PHARMACYGROUPID); }
                void            SetRanking(short t) { s.RANKING = t; }
                void            SetStruct(const customerpharmacygrS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CCUSTOMERPHARMACYGR()  //constructor
                {
                        ::buf_default((void *)&s,CUSTOMERPHARMACYGR_BES,CUSTOMERPHARMACYGR_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CCUSTOMERPHARMACYGR()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, CUSTOMERPHARMACYGR_BES, CUSTOMERPHARMACYGR_ANZ );
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc=::ServerNr(pos, fkt_nr, (void *)&s,CUSTOMERPHARMACYGR_BES,CUSTOMERPHARMACYGR_ANZ, error_msg);
                        #else
                        rc=::Server(fkt_nr, (void *)&s,CUSTOMERPHARMACYGR_BES,CUSTOMERPHARMACYGR_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_CUSTOMERPHARMACYGR& d)
                {
#ifdef WIN32
                        ppGStripLast(d.PHARMACYGROUPID);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNr, (void *)&s,CUSTOMERPHARMACYGR_BES,CUSTOMERPHARMACYGR_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of CUSTOMERPHARMACYGR ***********************************/

 #define CUSTOMERPHARMACYGR_CREATE(x) exec sql create table x (\
         CUSTOMERNO integer default 0 not null,\
         BRANCHNO smallint default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         RANKING smallint default 0 not null) in ksc extent size 16 next size 8 lock mode row;



/* CreateIndexStatement of CUSTOMERPHARMACYGR *********************************/

 #define CUSTOMERPHARMACYGR_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_custpharmgr_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              PharmacyGroupId ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of CUSTOMERPHARMACYGR *********************************/

 #define CUSTOMERPHARMACYGR_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_custpharmgr_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

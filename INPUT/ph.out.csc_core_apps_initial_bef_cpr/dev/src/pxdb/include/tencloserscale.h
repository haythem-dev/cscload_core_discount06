#ifndef __PP_ENCLOSERSCALE_H_
#define __PP_ENCLOSERSCALE_H_

/******************************************************************************/
/* u:\EncloserScale ***********************************************************/
/******************************************************************************/

/* Length-Define of ENCLOSERSCALE *********************************************/

  #define L_ENCLOSERSCALE_BRANCHNO 6
  #define L_ENCLOSERSCALE_CUSTOMERNO 11
  #define L_ENCLOSERSCALE_TIMEDIFF 6
  #define L_ENCLOSERSCALE_MAXPOSITIONS 6

/* Length/Count-Define of ENCLOSERSCALE ***************************************/

  #define LS_ENCLOSERSCALE_BRANCHNO 5 + 1
  #define LS_ENCLOSERSCALE_CUSTOMERNO 10 + 1
  #define LS_ENCLOSERSCALE_TIMEDIFF 5 + 1
  #define LS_ENCLOSERSCALE_MAXPOSITIONS 5 + 1

  #define ENCLOSERSCALEBRANCHNO 0
  #define ENCLOSERSCALECUSTOMERNO 1
  #define ENCLOSERSCALETIMEDIFF 2
  #define ENCLOSERSCALEMAXPOSITIONS 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ENCLOSERSCALE_H
 #define ENCLOSERSCALE_ANZ ( sizeof(ENCLOSERSCALE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ENCLOSERSCALE *************************************************/

 #define ENCLOSERSCALE_LISTE \
         ENCLOSERSCALE.BRANCHNO,\
         ENCLOSERSCALE.CUSTOMERNO,\
         ENCLOSERSCALE.TIMEDIFF,\
         ENCLOSERSCALE.MAXPOSITIONS

 #define ENCLOSERSCALE_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         TIMEDIFF,\
         MAXPOSITIONS

 #define ENCLOSERSCALE_PLISTE \
         "ENCLOSERSCALE.BRANCHNO,"\
         "ENCLOSERSCALE.CUSTOMERNO,"\
         "ENCLOSERSCALE.TIMEDIFF,"\
         "ENCLOSERSCALE.MAXPOSITIONS"

 #define ENCLOSERSCALE_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "TIMEDIFF,"\
         "MAXPOSITIONS"

 #define ENCLOSERSCALE_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "TIMEDIFF=?,"\
         "MAXPOSITIONS=?"

/* SqlMacros-Define of ENCLOSERSCALE ******************************************/

 #define ENCLOSERSCALE_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->TIMEDIFF,\
         :x->MAXPOSITIONS

 #define ENCLOSERSCALE_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->TIMEDIFF,\
         :x->MAXPOSITIONS

 #define ENCLOSERSCALE_UPDATE(x) \
         ENCLOSERSCALE.BRANCHNO=:x->BRANCHNO,\
         ENCLOSERSCALE.CUSTOMERNO=:x->CUSTOMERNO,\
         ENCLOSERSCALE.TIMEDIFF=:x->TIMEDIFF,\
         ENCLOSERSCALE.MAXPOSITIONS=:x->MAXPOSITIONS

/* SqlMacros390-Define of ENCLOSERSCALE ***************************************/

 #define ENCLOSERSCALE_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :TIMEDIFF,\
         :MAXPOSITIONS

 #define ENCLOSERSCALE_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         TIMEDIFF=:TIMEDIFF,\
         MAXPOSITIONS=:MAXPOSITIONS

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ENCLOSERSCALE ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_ENCLOSERSCALE {
         short BRANCHNO;
         long CUSTOMERNO;
         short TIMEDIFF;
         short MAXPOSITIONS;
        } encloserscaleS;
 #else /*TRANSCLASS*/
 typedef struct N_ENCLOSERSCALE {
         short BRANCHNO;
         long CUSTOMERNO;
         short TIMEDIFF;
         short MAXPOSITIONS;

                        bool operator==(const N_ENCLOSERSCALE& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                TIMEDIFF == right.TIMEDIFF &&
                                MAXPOSITIONS == right.MAXPOSITIONS
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                CUSTOMERNO = 0;
                                TIMEDIFF = 0;
                                MAXPOSITIONS = 0;
#endif
                        }
         } encloserscaleS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ENCLOSERSCALE *************************************/

 struct S_ENCLOSERSCALE {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char TIMEDIFF[7];
         char MAXPOSITIONS[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ENCLOSERSCALE ********************/

 struct O_ENCLOSERSCALE {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char TIMEDIFF[7];
         char MAXPOSITIONS[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ENCLOSERSCALE *******************************/

 struct C_ENCLOSERSCALE {
         short BRANCHNO;
         long CUSTOMERNO;
         short TIMEDIFF;
         short MAXPOSITIONS;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ENCLOSERSCALE *****************************/

 struct I_ENCLOSERSCALE {
         short BRANCHNO;
         short CUSTOMERNO;
         short TIMEDIFF;
         short MAXPOSITIONS;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ENCLOSERSCALE ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc ENCLOSERSCALE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ENCLOSERSCALE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of ENCLOSERSCALE *********************************/

 #define ENCLOSERSCALE_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         short TIMEDIFF; \
         short MAXPOSITIONS; \



/* Copy-Function Struct to single Data ENCLOSERSCALE **************************/

 #define ENCLOSERSCALE_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         TIMEDIFF=_x_->TIMEDIFF;\
         MAXPOSITIONS=_x_->MAXPOSITIONS;\

 #define ENCLOSERSCALE_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->TIMEDIFF=TIMEDIFF;\
          _x_->MAXPOSITIONS=MAXPOSITIONS;\



/* FunctionNumber-Define of EncloserScale *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of EncloserScale *********************************/


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

class CENCLOSERSCALE : public ppDadeVirtual
{
        //data members
        public:
                encloserscaleS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<encloserscaleS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<encloserscaleS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<encloserscaleS>; Strip(s); encloserscaleS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<encloserscaleS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<encloserscaleS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<encloserscaleS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                short           GetTimediff() const     { return s.TIMEDIFF; }
                short           GetMaxpositions() const { return s.MAXPOSITIONS; }
                const encloserscaleS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetTimediff(short t) { s.TIMEDIFF = t; }
                void            SetMaxpositions(short t) { s.MAXPOSITIONS = t; }
                void            SetStruct(const encloserscaleS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CENCLOSERSCALE()  //constructor
                {
                        ::buf_default((void *)&s, ENCLOSERSCALE_BES, ENCLOSERSCALE_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CENCLOSERSCALE()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ENCLOSERSCALE_BES, ENCLOSERSCALE_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ENCLOSERSCALE_BES, ENCLOSERSCALE_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ENCLOSERSCALE_BES, ENCLOSERSCALE_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ENCLOSERSCALE& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ENCLOSERSCALE_BES, ENCLOSERSCALE_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ENCLOSERSCALE ****************************************/

 #define ENCLOSERSCALE_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         TIMEDIFF smallint default 0 not null,\
         MAXPOSITIONS smallint default 0 not null) in ksc extent size 312 next size 32 lock mode row;



/* CreateIndexStatement of ENCLOSERSCALE **************************************/

 #define ENCLOSERSCALE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_encloserscale_1 on _X_(\
              BranchNo,\
              CustomerNo,\
              MaxPositions ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ENCLOSERSCALE **************************************/

 #define ENCLOSERSCALE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_encloserscale_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

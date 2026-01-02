#ifndef __PP_KDAUFTRAGDISCACC_H_
#define __PP_KDAUFTRAGDISCACC_H_

/******************************************************************************/
/* u:\kdauftragdiscacc ********************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGDISCACC ******************************************/

  #define L_KDAUFTRAGDISCACC_KDAUFTRAGNR 11
  #define L_KDAUFTRAGDISCACC_SWCHAIN 6
  #define L_KDAUFTRAGDISCACC_DATEFROM 11
  #define L_KDAUFTRAGDISCACC_DATETO 11
  #define L_KDAUFTRAGDISCACC_BRANCHNO 6

/* Length/Count-Define of KDAUFTRAGDISCACC ************************************/

  #define LS_KDAUFTRAGDISCACC_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGDISCACC_SWCHAIN 5 + 1
  #define LS_KDAUFTRAGDISCACC_DATEFROM 10 + 1
  #define LS_KDAUFTRAGDISCACC_DATETO 10 + 1
  #define LS_KDAUFTRAGDISCACC_BRANCHNO 5 + 1

  #define KDAUFTRAGDISCACCKDAUFTRAGNR 0
  #define KDAUFTRAGDISCACCSWCHAIN 1
  #define KDAUFTRAGDISCACCDATEFROM 2
  #define KDAUFTRAGDISCACCDATETO 3
  #define KDAUFTRAGDISCACCBRANCHNO 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGDISCACC_H
 #define KDAUFTRAGDISCACC_ANZ ( sizeof(KDAUFTRAGDISCACC_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGDISCACC **********************************************/

 #define KDAUFTRAGDISCACC_LISTE \
         KDAUFTRAGDISCACC.KDAUFTRAGNR,\
         KDAUFTRAGDISCACC.SWCHAIN,\
         KDAUFTRAGDISCACC.DATEFROM,\
         KDAUFTRAGDISCACC.DATETO,\
         KDAUFTRAGDISCACC.BRANCHNO

 #define KDAUFTRAGDISCACC_LISTE_390 \
         KDAUFTRAGNR,\
         SWCHAIN,\
         DATEFROM,\
         DATETO,\
         BRANCHNO

 #define KDAUFTRAGDISCACC_PLISTE \
         "KDAUFTRAGDISCACC.KDAUFTRAGNR,"\
         "KDAUFTRAGDISCACC.SWCHAIN,"\
         "KDAUFTRAGDISCACC.DATEFROM,"\
         "KDAUFTRAGDISCACC.DATETO,"\
         "KDAUFTRAGDISCACC.BRANCHNO"

 #define KDAUFTRAGDISCACC_PELISTE \
         "KDAUFTRAGNR,"\
         "SWCHAIN,"\
         "DATEFROM,"\
         "DATETO,"\
         "BRANCHNO"

 #define KDAUFTRAGDISCACC_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "SWCHAIN=?,"\
         "DATEFROM=?,"\
         "DATETO=?,"\
         "BRANCHNO=?"

/* SqlMacros-Define of KDAUFTRAGDISCACC ***************************************/

 #define KDAUFTRAGDISCACC_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->SWCHAIN,\
         :x->DATEFROM,\
         :x->DATETO,\
         :x->BRANCHNO

 #define KDAUFTRAGDISCACC_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->SWCHAIN,\
         :x->DATEFROM,\
         :x->DATETO,\
         :x->BRANCHNO

 #define KDAUFTRAGDISCACC_UPDATE(x) \
         KDAUFTRAGDISCACC.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGDISCACC.SWCHAIN=:x->SWCHAIN,\
         KDAUFTRAGDISCACC.DATEFROM=:x->DATEFROM,\
         KDAUFTRAGDISCACC.DATETO=:x->DATETO,\
         KDAUFTRAGDISCACC.BRANCHNO=:x->BRANCHNO

/* SqlMacros390-Define of KDAUFTRAGDISCACC ************************************/

 #define KDAUFTRAGDISCACC_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :SWCHAIN,\
         :DATEFROM,\
         :DATETO,\
         :BRANCHNO

 #define KDAUFTRAGDISCACC_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         SWCHAIN=:SWCHAIN,\
         DATEFROM=:DATEFROM,\
         DATETO=:DATETO,\
         BRANCHNO=:BRANCHNO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGDISCACC ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGDISCACC {
         long KDAUFTRAGNR;
         short SWCHAIN;
         long DATEFROM;
         long DATETO;
         short BRANCHNO;
        } kdauftragdiscaccS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGDISCACC {
         long KDAUFTRAGNR;
         short SWCHAIN;
         long DATEFROM;
         long DATETO;
         short BRANCHNO;

                        bool operator==(const N_KDAUFTRAGDISCACC& right) const {
                        return(
                                KDAUFTRAGNR == right.KDAUFTRAGNR &&
                                SWCHAIN == right.SWCHAIN &&
                                DATEFROM == right.DATEFROM &&
                                DATETO == right.DATETO &&
                                BRANCHNO == right.BRANCHNO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                KDAUFTRAGNR = 0;
                                SWCHAIN = 0;
                                DATEFROM = 0;
                                DATETO = 0;
                                BRANCHNO = 0;
#endif
                        }
         } kdauftragdiscaccS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGDISCACC **********************************/

 struct S_KDAUFTRAGDISCACC {
         char KDAUFTRAGNR[11];
         char SWCHAIN[7];
         char DATEFROM[11];
         char DATETO[11];
         char BRANCHNO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGDISCACC *****************/

 struct O_KDAUFTRAGDISCACC {
         char KDAUFTRAGNR[11];
         char SWCHAIN[7];
         char DATEFROM[11];
         char DATETO[11];
         char BRANCHNO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGDISCACC ****************************/

 struct C_KDAUFTRAGDISCACC {
         long KDAUFTRAGNR;
         short SWCHAIN;
         long DATEFROM;
         long DATETO;
         short BRANCHNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGDISCACC **************************/

 struct I_KDAUFTRAGDISCACC {
         short KDAUFTRAGNR;
         short SWCHAIN;
         short DATEFROM;
         short DATETO;
         short BRANCHNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGDISCACC ************************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGDISCACC_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGDISCACC_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGDISCACC ******************************/

 #define KDAUFTRAGDISCACC_S390 \
         long KDAUFTRAGNR; \
         short SWCHAIN; \
         long DATEFROM; \
         long DATETO; \
         short BRANCHNO; \



/* Copy-Function Struct to single Data KDAUFTRAGDISCACC ***********************/

 #define KDAUFTRAGDISCACC_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         SWCHAIN=_x_->SWCHAIN;\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\
         BRANCHNO=_x_->BRANCHNO;\

 #define KDAUFTRAGDISCACC_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->SWCHAIN=SWCHAIN;\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\
          _x_->BRANCHNO=BRANCHNO;\



/* FunctionNumber-Define of kdauftragdiscacc **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragdiscacc ******************************/


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

class CKDAUFTRAGDISCACC : public ppDadeVirtual
{
        //data members
        public:
                kdauftragdiscaccS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<kdauftragdiscaccS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragdiscaccS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<kdauftragdiscaccS>; Strip(s); kdauftragdiscaccS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragdiscaccS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<kdauftragdiscaccS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<kdauftragdiscaccS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetKdauftragnr() const  { return s.KDAUFTRAGNR; }
                short           GetSwchain() const      { return s.SWCHAIN; }
                long            GetDatefrom() const     { return s.DATEFROM; }
                long            GetDateto() const       { return s.DATETO; }
                short           GetBranchno() const     { return s.BRANCHNO; }
                const kdauftragdiscaccS& GetStruct() const { return s; }
                void            SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
                void            SetSwchain(short t) { s.SWCHAIN = t; }
                void            SetDatefrom(long t) { s.DATEFROM = t; }
                void            SetDateto(long t) { s.DATETO = t; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetStruct(const kdauftragdiscaccS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CKDAUFTRAGDISCACC()  //constructor
                {
                        ::buf_default((void *)&s, KDAUFTRAGDISCACC_BES, KDAUFTRAGDISCACC_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CKDAUFTRAGDISCACC()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, KDAUFTRAGDISCACC_BES, KDAUFTRAGDISCACC_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGDISCACC_BES, KDAUFTRAGDISCACC_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGDISCACC_BES, KDAUFTRAGDISCACC_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_KDAUFTRAGDISCACC& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGDISCACC_BES, KDAUFTRAGDISCACC_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of KDAUFTRAGDISCACC *************************************/

 #define KDAUFTRAGDISCACC_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         SWCHAIN smallint default 0 not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null,\
         BRANCHNO smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of KDAUFTRAGDISCACC ***********************************/

 #define KDAUFTRAGDISCACC_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdaufdiscacc_1 on _X_(\
              BranchNo,\
              kdauftragnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGDISCACC ***********************************/

 #define KDAUFTRAGDISCACC_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdaufdiscacc_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

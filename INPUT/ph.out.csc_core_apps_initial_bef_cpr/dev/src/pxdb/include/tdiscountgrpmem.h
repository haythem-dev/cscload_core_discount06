#ifndef __PP_DISCOUNTGRPMEM_H_
#define __PP_DISCOUNTGRPMEM_H_

/******************************************************************************/
/* u:\DiscountGrpMem **********************************************************/
/******************************************************************************/

/* Length-Define of DISCOUNTGRPMEM ********************************************/

  #define L_DISCOUNTGRPMEM_BRANCHNO 6
  #define L_DISCOUNTGRPMEM_DISCOUNTGRPNO 11
  #define L_DISCOUNTGRPMEM_ARTICLENO 11
  #define L_DISCOUNTGRPMEM_DISCOUNTCONDITION 6
  #define L_DISCOUNTGRPMEM_MANUFACTURERNO 11

/* Length/Count-Define of DISCOUNTGRPMEM **************************************/

  #define LS_DISCOUNTGRPMEM_BRANCHNO 5 + 1
  #define LS_DISCOUNTGRPMEM_DISCOUNTGRPNO 10 + 1
  #define LS_DISCOUNTGRPMEM_ARTICLENO 10 + 1
  #define LS_DISCOUNTGRPMEM_DISCOUNTCONDITION 5 + 1
  #define LS_DISCOUNTGRPMEM_MANUFACTURERNO 10 + 1

  #define DISCOUNTGRPMEMBRANCHNO 0
  #define DISCOUNTGRPMEMDISCOUNTGRPNO 1
  #define DISCOUNTGRPMEMARTICLENO 2
  #define DISCOUNTGRPMEMDISCOUNTCONDITION 3
  #define DISCOUNTGRPMEMMANUFACTURERNO 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DISCOUNTGRPMEM_H
 #define DISCOUNTGRPMEM_ANZ ( sizeof(DISCOUNTGRPMEM_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DISCOUNTGRPMEM ************************************************/

 #define DISCOUNTGRPMEM_LISTE \
         DISCOUNTGRPMEM.BRANCHNO,\
         DISCOUNTGRPMEM.DISCOUNTGRPNO,\
         DISCOUNTGRPMEM.ARTICLENO,\
         DISCOUNTGRPMEM.DISCOUNTCONDITION,\
         DISCOUNTGRPMEM.MANUFACTURERNO

 #define DISCOUNTGRPMEM_LISTE_390 \
         BRANCHNO,\
         DISCOUNTGRPNO,\
         ARTICLENO,\
         DISCOUNTCONDITION,\
         MANUFACTURERNO

 #define DISCOUNTGRPMEM_PLISTE \
         "DISCOUNTGRPMEM.BRANCHNO,"\
         "DISCOUNTGRPMEM.DISCOUNTGRPNO,"\
         "DISCOUNTGRPMEM.ARTICLENO,"\
         "DISCOUNTGRPMEM.DISCOUNTCONDITION,"\
         "DISCOUNTGRPMEM.MANUFACTURERNO"

 #define DISCOUNTGRPMEM_PELISTE \
         "BRANCHNO,"\
         "DISCOUNTGRPNO,"\
         "ARTICLENO,"\
         "DISCOUNTCONDITION,"\
         "MANUFACTURERNO"

 #define DISCOUNTGRPMEM_UPDLISTE \
         "BRANCHNO=?,"\
         "DISCOUNTGRPNO=?,"\
         "ARTICLENO=?,"\
         "DISCOUNTCONDITION=?,"\
         "MANUFACTURERNO=?"

/* SqlMacros-Define of DISCOUNTGRPMEM *****************************************/

 #define DISCOUNTGRPMEM_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->DISCOUNTGRPNO,\
         :x->ARTICLENO,\
         :x->DISCOUNTCONDITION,\
         :x->MANUFACTURERNO

 #define DISCOUNTGRPMEM_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->DISCOUNTGRPNO,\
         :x->ARTICLENO,\
         :x->DISCOUNTCONDITION,\
         :x->MANUFACTURERNO

 #define DISCOUNTGRPMEM_UPDATE(x) \
         DISCOUNTGRPMEM.BRANCHNO=:x->BRANCHNO,\
         DISCOUNTGRPMEM.DISCOUNTGRPNO=:x->DISCOUNTGRPNO,\
         DISCOUNTGRPMEM.ARTICLENO=:x->ARTICLENO,\
         DISCOUNTGRPMEM.DISCOUNTCONDITION=:x->DISCOUNTCONDITION,\
         DISCOUNTGRPMEM.MANUFACTURERNO=:x->MANUFACTURERNO

/* SqlMacros390-Define of DISCOUNTGRPMEM **************************************/

 #define DISCOUNTGRPMEM_ZEIGER_390 \
         :BRANCHNO,\
         :DISCOUNTGRPNO,\
         :ARTICLENO,\
         :DISCOUNTCONDITION,\
         :MANUFACTURERNO

 #define DISCOUNTGRPMEM_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         DISCOUNTGRPNO=:DISCOUNTGRPNO,\
         ARTICLENO=:ARTICLENO,\
         DISCOUNTCONDITION=:DISCOUNTCONDITION,\
         MANUFACTURERNO=:MANUFACTURERNO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of DISCOUNTGRPMEM *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_DISCOUNTGRPMEM {
         short BRANCHNO;
         long DISCOUNTGRPNO;
         long ARTICLENO;
         short DISCOUNTCONDITION;
         long MANUFACTURERNO;
        } discountgrpmemS;
 #else /*TRANSCLASS*/
 typedef struct N_DISCOUNTGRPMEM {
         short BRANCHNO;
         long DISCOUNTGRPNO;
         long ARTICLENO;
         short DISCOUNTCONDITION;
         long MANUFACTURERNO;

                        bool operator==(const N_DISCOUNTGRPMEM& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                DISCOUNTGRPNO == right.DISCOUNTGRPNO &&
                                ARTICLENO == right.ARTICLENO &&
                                DISCOUNTCONDITION == right.DISCOUNTCONDITION &&
                                MANUFACTURERNO == right.MANUFACTURERNO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                DISCOUNTGRPNO = 0;
                                ARTICLENO = 0;
                                DISCOUNTCONDITION = 0;
                                MANUFACTURERNO = 0;
#endif
                        }
         } discountgrpmemS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DISCOUNTGRPMEM ************************************/

 struct S_DISCOUNTGRPMEM {
         char BRANCHNO[7];
         char DISCOUNTGRPNO[11];
         char ARTICLENO[11];
         char DISCOUNTCONDITION[7];
         char MANUFACTURERNO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DISCOUNTGRPMEM *******************/

 struct O_DISCOUNTGRPMEM {
         char BRANCHNO[7];
         char DISCOUNTGRPNO[11];
         char ARTICLENO[11];
         char DISCOUNTCONDITION[7];
         char MANUFACTURERNO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DISCOUNTGRPMEM ******************************/

 struct C_DISCOUNTGRPMEM {
         short BRANCHNO;
         long DISCOUNTGRPNO;
         long ARTICLENO;
         short DISCOUNTCONDITION;
         long MANUFACTURERNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DISCOUNTGRPMEM ****************************/

 struct I_DISCOUNTGRPMEM {
         short BRANCHNO;
         short DISCOUNTGRPNO;
         short ARTICLENO;
         short DISCOUNTCONDITION;
         short MANUFACTURERNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DISCOUNTGRPMEM **************************************/

#if defined (BUF_DESC)
 static struct buf_desc DISCOUNTGRPMEM_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DISCOUNTGRPMEM_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of DISCOUNTGRPMEM ********************************/

 #define DISCOUNTGRPMEM_S390 \
         short BRANCHNO; \
         long DISCOUNTGRPNO; \
         long ARTICLENO; \
         short DISCOUNTCONDITION; \
         long MANUFACTURERNO; \



/* Copy-Function Struct to single Data DISCOUNTGRPMEM *************************/

 #define DISCOUNTGRPMEM_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         DISCOUNTGRPNO=_x_->DISCOUNTGRPNO;\
         ARTICLENO=_x_->ARTICLENO;\
         DISCOUNTCONDITION=_x_->DISCOUNTCONDITION;\
         MANUFACTURERNO=_x_->MANUFACTURERNO;\

 #define DISCOUNTGRPMEM_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->DISCOUNTGRPNO=DISCOUNTGRPNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->DISCOUNTCONDITION=DISCOUNTCONDITION;\
          _x_->MANUFACTURERNO=MANUFACTURERNO;\



/* FunctionNumber-Define of DiscountGrpMem ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of DiscountGrpMem ********************************/


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

class CDISCOUNTGRPMEM : public ppDadeVirtual
{
        //data members
        public:
                discountgrpmemS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<discountgrpmemS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountgrpmemS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<discountgrpmemS>; Strip(s); discountgrpmemS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountgrpmemS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<discountgrpmemS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<discountgrpmemS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetDiscountgrpno() const        { return s.DISCOUNTGRPNO; }
                long            GetArticleno() const    { return s.ARTICLENO; }
                short           GetDiscountcondition() const    { return s.DISCOUNTCONDITION; }
                long            GetManufacturerno() const       { return s.MANUFACTURERNO; }
                const discountgrpmemS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetDiscountgrpno(long t) { s.DISCOUNTGRPNO = t; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetDiscountcondition(short t) { s.DISCOUNTCONDITION = t; }
                void            SetManufacturerno(long t) { s.MANUFACTURERNO = t; }
                void            SetStruct(const discountgrpmemS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CDISCOUNTGRPMEM()  //constructor
                {
                        ::buf_default((void *)&s, DISCOUNTGRPMEM_BES, DISCOUNTGRPMEM_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CDISCOUNTGRPMEM()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, DISCOUNTGRPMEM_BES, DISCOUNTGRPMEM_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DISCOUNTGRPMEM_BES, DISCOUNTGRPMEM_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, DISCOUNTGRPMEM_BES, DISCOUNTGRPMEM_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_DISCOUNTGRPMEM& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, DISCOUNTGRPMEM_BES, DISCOUNTGRPMEM_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of DISCOUNTGRPMEM ***************************************/

 #define DISCOUNTGRPMEM_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         DISCOUNTGRPNO integer default 0 not null,\
         ARTICLENO integer default 0 not null,\
         DISCOUNTCONDITION smallint default 0 not null,\
         MANUFACTURERNO integer default 0 not null) in ksc extent size 40 next size 8 lock mode row;



/* CreateIndexStatement of DISCOUNTGRPMEM *************************************/

 #define DISCOUNTGRPMEM_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_discountmem_1 on _X_(\
              BranchNo,\
              DiscountGrpNo,\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of DISCOUNTGRPMEM *************************************/

 #define DISCOUNTGRPMEM_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_discountmem_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

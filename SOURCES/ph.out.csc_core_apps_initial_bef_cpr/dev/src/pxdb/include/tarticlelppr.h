#ifndef __PP_ARTICLELPPR_H_
#define __PP_ARTICLELPPR_H_

/******************************************************************************/
/* u:\ArticleLPPR *************************************************************/
/******************************************************************************/

/* Length-Define of ARTICLELPPR ***********************************************/

  #define L_ARTICLELPPR_ARTICLENO 11
  #define L_ARTICLELPPR_REIMBURSEMENT_TYPE 1
  #define L_ARTICLELPPR_REIMBURSEMENTPRICE 9
  #define N_ARTICLELPPR_REIMBURSEMENTPRICE 3

/* Length/Count-Define of ARTICLELPPR *****************************************/

  #define LS_ARTICLELPPR_ARTICLENO 10 + 1
  #define LS_ARTICLELPPR_REIMBURSEMENT_TYPE 1 + 1
  #define LS_ARTICLELPPR_REIMBURSEMENTPRICE 9 + 2

  #define ARTICLELPPRARTICLENO 0
  #define ARTICLELPPRREIMBURSEMENT_TYPE 1
  #define ARTICLELPPRREIMBURSEMENTPRICE 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTICLELPPR_H
 #define ARTICLELPPR_ANZ ( sizeof(ARTICLELPPR_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLELPPR ***************************************************/

 #define ARTICLELPPR_LISTE \
         ARTICLELPPR.ARTICLENO,\
         ARTICLELPPR.REIMBURSEMENT_TYPE,\
         ARTICLELPPR.REIMBURSEMENTPRICE

 #define ARTICLELPPR_LISTE_390 \
         ARTICLENO,\
         REIMBURSEMENT_TYPE,\
         REIMBURSEMENTPRICE

 #define ARTICLELPPR_PLISTE \
         "ARTICLELPPR.ARTICLENO,"\
         "ARTICLELPPR.REIMBURSEMENT_TYPE,"\
         "ARTICLELPPR.REIMBURSEMENTPRICE"

 #define ARTICLELPPR_PELISTE \
         "ARTICLENO,"\
         "REIMBURSEMENT_TYPE,"\
         "REIMBURSEMENTPRICE"

 #define ARTICLELPPR_UPDLISTE \
         "ARTICLENO=?,"\
         "REIMBURSEMENT_TYPE=?,"\
         "REIMBURSEMENTPRICE=?"

/* SqlMacros-Define of ARTICLELPPR ********************************************/

 #define ARTICLELPPR_ZEIGER(x) \
         :x->ARTICLENO,\
         :x->REIMBURSEMENT_TYPE,\
         :x->REIMBURSEMENTPRICE

 #define ARTICLELPPR_ZEIGERSEL(x) \
         :x->ARTICLENO,\
         :x->REIMBURSEMENT_TYPE,\
         :x->REIMBURSEMENTPRICE

 #define ARTICLELPPR_UPDATE(x) \
         ARTICLELPPR.ARTICLENO=:x->ARTICLENO,\
         ARTICLELPPR.REIMBURSEMENT_TYPE=:x->REIMBURSEMENT_TYPE,\
         ARTICLELPPR.REIMBURSEMENTPRICE=:x->REIMBURSEMENTPRICE

/* SqlMacros390-Define of ARTICLELPPR *****************************************/

 #define ARTICLELPPR_ZEIGER_390 \
         :ARTICLENO,\
         :REIMBURSEMENT_TYPE,\
         :REIMBURSEMENTPRICE

 #define ARTICLELPPR_UPDATE_390 \
         ARTICLENO=:ARTICLENO,\
         REIMBURSEMENT_TYPE=:REIMBURSEMENT_TYPE,\
         REIMBURSEMENTPRICE=:REIMBURSEMENTPRICE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTICLELPPR ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTICLELPPR {
         long ARTICLENO;
         char REIMBURSEMENT_TYPE[2];
         double REIMBURSEMENTPRICE;
        } articlelpprS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTICLELPPR {
         long ARTICLENO;
         char REIMBURSEMENT_TYPE[2];
         double REIMBURSEMENTPRICE;

                        bool operator==(const N_ARTICLELPPR& right) const {
                        return(
                                ARTICLENO == right.ARTICLENO &&
                                !strcmp(REIMBURSEMENT_TYPE, right.REIMBURSEMENT_TYPE) &&
                                REIMBURSEMENTPRICE == right.REIMBURSEMENTPRICE
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTICLENO = 0;
                                strcpy(REIMBURSEMENT_TYPE, " " );
                                REIMBURSEMENTPRICE = 0;
#endif
                        }
         } articlelpprS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLELPPR ***************************************/

 struct S_ARTICLELPPR {
         char ARTICLENO[11];
         char REIMBURSEMENT_TYPE[1 + 1];
         char REIMBURSEMENTPRICE[9 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLELPPR **********************/

 struct O_ARTICLELPPR {
         char ARTICLENO[11];
         char REIMBURSEMENT_TYPE[1];
         char REIMBURSEMENTPRICE[9];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLELPPR *********************************/

 struct C_ARTICLELPPR {
         long ARTICLENO;
         char REIMBURSEMENT_TYPE;
         double REIMBURSEMENTPRICE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLELPPR *******************************/

 struct I_ARTICLELPPR {
         short ARTICLENO;
         short REIMBURSEMENT_TYPE;
         short REIMBURSEMENTPRICE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLELPPR *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTICLELPPR_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 9, 3 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTICLELPPR_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 9, 3 },
 };
#endif

/* description for datatypes of ARTICLELPPR ***********************************/

 #define ARTICLELPPR_S390 \
         long ARTICLENO; \
         char REIMBURSEMENT_TYPE; \
         double REIMBURSEMENTPRICE; \



/* Copy-Function Struct to single Data ARTICLELPPR ****************************/

 #define ARTICLELPPR_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         REIMBURSEMENT_TYPE=_x_->REIMBURSEMENT_TYPE;\
         REIMBURSEMENTPRICE=_x_->REIMBURSEMENTPRICE;\

 #define ARTICLELPPR_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->REIMBURSEMENT_TYPE=REIMBURSEMENT_TYPE;\
          _x_->REIMBURSEMENTPRICE=REIMBURSEMENTPRICE;\



/* FunctionNumber-Define of ArticleLPPR ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleLPPR ***********************************/


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

class CARTICLELPPR : public ppDadeVirtual
{
        //data members
        public:
                articlelpprS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<articlelpprS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlelpprS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<articlelpprS>; Strip(s); articlelpprS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlelpprS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<articlelpprS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<articlelpprS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArticleno() const    { return s.ARTICLENO; }
                char            GetReimbursement_type() const   { return s.REIMBURSEMENT_TYPE[0]; }
                double          GetReimbursementprice() const   { return s.REIMBURSEMENTPRICE; }
                const articlelpprS& GetStruct() const { return s; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetReimbursement_type(char t) { s.REIMBURSEMENT_TYPE[0] = t; s.REIMBURSEMENT_TYPE[1] = '\0';}
                void            SetReimbursementprice(double t) { s.REIMBURSEMENTPRICE = t; }
                void            SetStruct(const articlelpprS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTICLELPPR()  //constructor
                {
                        ::buf_default((void *)&s, ARTICLELPPR_BES, ARTICLELPPR_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTICLELPPR()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTICLELPPR_BES, ARTICLELPPR_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLELPPR_BES, ARTICLELPPR_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTICLELPPR_BES, ARTICLELPPR_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTICLELPPR& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLELPPR_BES, ARTICLELPPR_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTICLELPPR ******************************************/

 #define ARTICLELPPR_CREATE(x) exec sql create table x (\
         ARTICLENO integer default 0 not null,\
         REIMBURSEMENT_TYPE char(1) default " " not null,\
         REIMBURSEMENTPRICE decimal(9,3) default 0 not null) in ksc extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of ARTICLELPPR ****************************************/

 #define ARTICLELPPR_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_articlelppr_1 on _X_(\
              ArticleNo,\
              reimbursement_type ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLELPPR ****************************************/

 #define ARTICLELPPR_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_articlelppr_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

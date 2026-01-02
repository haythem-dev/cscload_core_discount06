#ifndef __PP_ARTICLEOLDPRICE_H_
#define __PP_ARTICLEOLDPRICE_H_

/******************************************************************************/
/* v:\ArticleOldPrice *********************************************************/
/******************************************************************************/

/* Length-Define of ARTICLEOLDPRICE *******************************************/

  #define L_ARTICLEOLDPRICE_BRANCHNO 6
  #define L_ARTICLEOLDPRICE_ARTICLENO 11
  #define L_ARTICLEOLDPRICE_PREISEKAPO 9
  #define N_ARTICLEOLDPRICE_PREISEKAPO 2
  #define L_ARTICLEOLDPRICE_PREISEKGROSSO 9
  #define N_ARTICLEOLDPRICE_PREISEKGROSSO 2
  #define L_ARTICLEOLDPRICE_PREISEKGROSSONA 9
  #define N_ARTICLEOLDPRICE_PREISEKGROSSONA 2
  #define L_ARTICLEOLDPRICE_PREISVKAPO 9
  #define N_ARTICLEOLDPRICE_PREISVKAPO 2

/* Length/Count-Define of ARTICLEOLDPRICE *************************************/

  #define LS_ARTICLEOLDPRICE_BRANCHNO 5 + 1
  #define LS_ARTICLEOLDPRICE_ARTICLENO 10 + 1
  #define LS_ARTICLEOLDPRICE_PREISEKAPO 9 + 2
  #define LS_ARTICLEOLDPRICE_PREISEKGROSSO 9 + 2
  #define LS_ARTICLEOLDPRICE_PREISEKGROSSONA 9 + 2
  #define LS_ARTICLEOLDPRICE_PREISVKAPO 9 + 2

  #define ARTICLEOLDPRICEBRANCHNO 0
  #define ARTICLEOLDPRICEARTICLENO 1
  #define ARTICLEOLDPRICEPREISEKAPO 2
  #define ARTICLEOLDPRICEPREISEKGROSSO 3
  #define ARTICLEOLDPRICEPREISEKGROSSONA 4
  #define ARTICLEOLDPRICEPREISVKAPO 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTICLEOLDPRICE_H
 #define ARTICLEOLDPRICE_ANZ ( sizeof(ARTICLEOLDPRICE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLEOLDPRICE ***********************************************/

 #define ARTICLEOLDPRICE_LISTE \
         ARTICLEOLDPRICE.BRANCHNO,\
         ARTICLEOLDPRICE.ARTICLENO,\
         ARTICLEOLDPRICE.PREISEKAPO,\
         ARTICLEOLDPRICE.PREISEKGROSSO,\
         ARTICLEOLDPRICE.PREISEKGROSSONA,\
         ARTICLEOLDPRICE.PREISVKAPO

 #define ARTICLEOLDPRICE_LISTE_390 \
         BRANCHNO,\
         ARTICLENO,\
         PREISEKAPO,\
         PREISEKGROSSO,\
         PREISEKGROSSONA,\
         PREISVKAPO

 #define ARTICLEOLDPRICE_PLISTE \
         "ARTICLEOLDPRICE.BRANCHNO,"\
         "ARTICLEOLDPRICE.ARTICLENO,"\
         "ARTICLEOLDPRICE.PREISEKAPO,"\
         "ARTICLEOLDPRICE.PREISEKGROSSO,"\
         "ARTICLEOLDPRICE.PREISEKGROSSONA,"\
         "ARTICLEOLDPRICE.PREISVKAPO"

 #define ARTICLEOLDPRICE_PELISTE \
         "BRANCHNO,"\
         "ARTICLENO,"\
         "PREISEKAPO,"\
         "PREISEKGROSSO,"\
         "PREISEKGROSSONA,"\
         "PREISVKAPO"

 #define ARTICLEOLDPRICE_UPDLISTE \
         "BRANCHNO=?,"\
         "ARTICLENO=?,"\
         "PREISEKAPO=?,"\
         "PREISEKGROSSO=?,"\
         "PREISEKGROSSONA=?,"\
         "PREISVKAPO=?"

/* SqlMacros-Define of ARTICLEOLDPRICE ****************************************/

 #define ARTICLEOLDPRICE_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->PREISEKAPO,\
         :x->PREISEKGROSSO,\
         :x->PREISEKGROSSONA,\
         :x->PREISVKAPO

 #define ARTICLEOLDPRICE_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->PREISEKAPO,\
         :x->PREISEKGROSSO,\
         :x->PREISEKGROSSONA,\
         :x->PREISVKAPO

 #define ARTICLEOLDPRICE_UPDATE(x) \
         ARTICLEOLDPRICE.BRANCHNO=:x->BRANCHNO,\
         ARTICLEOLDPRICE.ARTICLENO=:x->ARTICLENO,\
         ARTICLEOLDPRICE.PREISEKAPO=:x->PREISEKAPO,\
         ARTICLEOLDPRICE.PREISEKGROSSO=:x->PREISEKGROSSO,\
         ARTICLEOLDPRICE.PREISEKGROSSONA=:x->PREISEKGROSSONA,\
         ARTICLEOLDPRICE.PREISVKAPO=:x->PREISVKAPO

/* SqlMacros390-Define of ARTICLEOLDPRICE *************************************/

 #define ARTICLEOLDPRICE_ZEIGER_390 \
         :BRANCHNO,\
         :ARTICLENO,\
         :PREISEKAPO,\
         :PREISEKGROSSO,\
         :PREISEKGROSSONA,\
         :PREISVKAPO

 #define ARTICLEOLDPRICE_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         ARTICLENO=:ARTICLENO,\
         PREISEKAPO=:PREISEKAPO,\
         PREISEKGROSSO=:PREISEKGROSSO,\
         PREISEKGROSSONA=:PREISEKGROSSONA,\
         PREISVKAPO=:PREISVKAPO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTICLEOLDPRICE ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTICLEOLDPRICE {
         short BRANCHNO;
         long ARTICLENO;
         double PREISEKAPO;
         double PREISEKGROSSO;
         double PREISEKGROSSONA;
         double PREISVKAPO;
        } articleoldpriceS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTICLEOLDPRICE {
         short BRANCHNO;
         long ARTICLENO;
         double PREISEKAPO;
         double PREISEKGROSSO;
         double PREISEKGROSSONA;
         double PREISVKAPO;

                        bool operator==(const N_ARTICLEOLDPRICE& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                ARTICLENO == right.ARTICLENO &&
                                PREISEKAPO == right.PREISEKAPO &&
                                PREISEKGROSSO == right.PREISEKGROSSO &&
                                PREISEKGROSSONA == right.PREISEKGROSSONA &&
                                PREISVKAPO == right.PREISVKAPO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                ARTICLENO = 0;
                                PREISEKAPO = 0;
                                PREISEKGROSSO = 0;
                                PREISEKGROSSONA = 0;
                                PREISVKAPO = 0;
#endif
                        }
         } articleoldpriceS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLEOLDPRICE ***********************************/

 struct S_ARTICLEOLDPRICE {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char PREISEKAPO[9 + 2];
         char PREISEKGROSSO[9 + 2];
         char PREISEKGROSSONA[9 + 2];
         char PREISVKAPO[9 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLEOLDPRICE ******************/

 struct O_ARTICLEOLDPRICE {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char PREISEKAPO[9];
         char PREISEKGROSSO[9];
         char PREISEKGROSSONA[9];
         char PREISVKAPO[9];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLEOLDPRICE *****************************/

 struct C_ARTICLEOLDPRICE {
         short BRANCHNO;
         long ARTICLENO;
         double PREISEKAPO;
         double PREISEKGROSSO;
         double PREISEKGROSSONA;
         double PREISVKAPO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLEOLDPRICE ***************************/

 struct I_ARTICLEOLDPRICE {
         short BRANCHNO;
         short ARTICLENO;
         short PREISEKAPO;
         short PREISEKGROSSO;
         short PREISEKGROSSONA;
         short PREISVKAPO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLEOLDPRICE *************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTICLEOLDPRICE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTICLEOLDPRICE_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
 };
#endif

/* description for datatypes of ARTICLEOLDPRICE *******************************/

 #define ARTICLEOLDPRICE_S390 \
         short BRANCHNO; \
         long ARTICLENO; \
         double PREISEKAPO; \
         double PREISEKGROSSO; \
         double PREISEKGROSSONA; \
         double PREISVKAPO; \



/* Copy-Function Struct to single Data ARTICLEOLDPRICE ************************/

 #define ARTICLEOLDPRICE_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         ARTICLENO=_x_->ARTICLENO;\
         PREISEKAPO=_x_->PREISEKAPO;\
         PREISEKGROSSO=_x_->PREISEKGROSSO;\
         PREISEKGROSSONA=_x_->PREISEKGROSSONA;\
         PREISVKAPO=_x_->PREISVKAPO;\

 #define ARTICLEOLDPRICE_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->PREISEKAPO=PREISEKAPO;\
          _x_->PREISEKGROSSO=PREISEKGROSSO;\
          _x_->PREISEKGROSSONA=PREISEKGROSSONA;\
          _x_->PREISVKAPO=PREISVKAPO;\



/* FunctionNumber-Define of ArticleOldPrice ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleOldPrice *******************************/


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

class CARTICLEOLDPRICE : public ppDadeVirtual
{
        //data members
        public:
                articleoldpriceS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<articleoldpriceS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<articleoldpriceS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<articleoldpriceS>; Strip(s); articleoldpriceS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<articleoldpriceS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<articleoldpriceS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<articleoldpriceS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetArticleno() const    { return s.ARTICLENO; }
                double          GetPreisekapo() const   { return s.PREISEKAPO; }
                double          GetPreisekgrosso() const        { return s.PREISEKGROSSO; }
                double          GetPreisekgrossona() const      { return s.PREISEKGROSSONA; }
                double          GetPreisvkapo() const   { return s.PREISVKAPO; }
                const articleoldpriceS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetPreisekapo(double t) { s.PREISEKAPO = t; }
                void            SetPreisekgrosso(double t) { s.PREISEKGROSSO = t; }
                void            SetPreisekgrossona(double t) { s.PREISEKGROSSONA = t; }
                void            SetPreisvkapo(double t) { s.PREISVKAPO = t; }
                void            SetStruct(const articleoldpriceS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTICLEOLDPRICE()  //constructor
                {
                        ::buf_default((void *)&s, ARTICLEOLDPRICE_BES, ARTICLEOLDPRICE_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTICLEOLDPRICE()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTICLEOLDPRICE_BES, ARTICLEOLDPRICE_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLEOLDPRICE_BES, ARTICLEOLDPRICE_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTICLEOLDPRICE_BES, ARTICLEOLDPRICE_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTICLEOLDPRICE& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLEOLDPRICE_BES, ARTICLEOLDPRICE_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTICLEOLDPRICE **************************************/

 #define ARTICLEOLDPRICE_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         ARTICLENO integer default 0 not null,\
         PREISEKAPO decimal(9,2) default 0 not null,\
         PREISEKGROSSO decimal(9,2) default 0 not null,\
         PREISEKGROSSONA decimal(9,2) default 0 not null,\
         PREISVKAPO decimal(9,2) default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ARTICLEOLDPRICE ************************************/

 #define ARTICLEOLDPRICE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_articleold_1 on _X_(\
              BranchNo,\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLEOLDPRICE ************************************/

 #define ARTICLEOLDPRICE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_articleold_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

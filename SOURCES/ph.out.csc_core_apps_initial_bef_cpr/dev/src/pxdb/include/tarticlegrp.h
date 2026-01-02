#ifndef __PP_ARTICLEGRP_H_
#define __PP_ARTICLEGRP_H_

/******************************************************************************/
/* u:\ArticleGrp **************************************************************/
/******************************************************************************/

/* Length-Define of ARTICLEGRP ************************************************/

  #define L_ARTICLEGRP_ARTICLENO 11
  #define L_ARTICLEGRP_ARTCATEGORYNO 11

/* Length/Count-Define of ARTICLEGRP ******************************************/

  #define LS_ARTICLEGRP_ARTICLENO 10 + 1
  #define LS_ARTICLEGRP_ARTCATEGORYNO 10 + 1

  #define ARTICLEGRPARTICLENO 0
  #define ARTICLEGRPARTCATEGORYNO 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTICLEGRP_H
 #define ARTICLEGRP_ANZ ( sizeof(ARTICLEGRP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLEGRP ****************************************************/

 #define ARTICLEGRP_LISTE \
         ARTICLEGROUP.ARTICLENO,\
         ARTICLEGROUP.ARTCATEGORYNO

 #define ARTICLEGRP_LISTE_390 \
         ARTICLENO,\
         ARTCATEGORYNO

 #define ARTICLEGRP_PLISTE \
         "ARTICLEGROUP.ARTICLENO,"\
         "ARTICLEGROUP.ARTCATEGORYNO"

 #define ARTICLEGRP_PELISTE \
         "ARTICLENO,"\
         "ARTCATEGORYNO"

 #define ARTICLEGRP_UPDLISTE \
         "ARTICLENO=?,"\
         "ARTCATEGORYNO=?"

/* SqlMacros-Define of ARTICLEGRP *********************************************/

 #define ARTICLEGRP_ZEIGER(x) \
         :x->ARTICLENO,\
         :x->ARTCATEGORYNO

 #define ARTICLEGRP_ZEIGERSEL(x) \
         :x->ARTICLENO,\
         :x->ARTCATEGORYNO

 #define ARTICLEGRP_UPDATE(x) \
         ARTICLEGROUP.ARTICLENO=:x->ARTICLENO,\
         ARTICLEGROUP.ARTCATEGORYNO=:x->ARTCATEGORYNO

/* SqlMacros390-Define of ARTICLEGRP ******************************************/

 #define ARTICLEGRP_ZEIGER_390 \
         :ARTICLENO,\
         :ARTCATEGORYNO

 #define ARTICLEGRP_UPDATE_390 \
         ARTICLENO=:ARTICLENO,\
         ARTCATEGORYNO=:ARTCATEGORYNO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTICLEGRP *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTICLEGRP {
         long ARTICLENO;
         long ARTCATEGORYNO;
        } articlegrpS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTICLEGRP {
         long ARTICLENO;
         long ARTCATEGORYNO;

                        bool operator==(const N_ARTICLEGRP& right) const {
                        return(
                                ARTICLENO == right.ARTICLENO &&
                                ARTCATEGORYNO == right.ARTCATEGORYNO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTICLENO = 0;
                                ARTCATEGORYNO = 0;
#endif
                        }
         } articlegrpS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLEGRP ****************************************/

 struct S_ARTICLEGRP {
         char ARTICLENO[11];
         char ARTCATEGORYNO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLEGRP ***********************/

 struct O_ARTICLEGRP {
         char ARTICLENO[11];
         char ARTCATEGORYNO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLEGRP **********************************/

 struct C_ARTICLEGRP {
         long ARTICLENO;
         long ARTCATEGORYNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLEGRP ********************************/

 struct I_ARTICLEGRP {
         short ARTICLENO;
         short ARTCATEGORYNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLEGRP ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTICLEGRP_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTICLEGRP_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of ARTICLEGRP ************************************/

 #define ARTICLEGRP_S390 \
         long ARTICLENO; \
         long ARTCATEGORYNO; \



/* Copy-Function Struct to single Data ARTICLEGRP *****************************/

 #define ARTICLEGRP_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         ARTCATEGORYNO=_x_->ARTCATEGORYNO;\

 #define ARTICLEGRP_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->ARTCATEGORYNO=ARTCATEGORYNO;\



/* FunctionNumber-Define of ArticleGrp ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleGrp ************************************/


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

class CARTICLEGRP : public ppDadeVirtual
{
        //data members
        public:
                articlegrpS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<articlegrpS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlegrpS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<articlegrpS>; Strip(s); articlegrpS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlegrpS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<articlegrpS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<articlegrpS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArticleno() const    { return s.ARTICLENO; }
                long            GetArtcategoryno() const        { return s.ARTCATEGORYNO; }
                const articlegrpS& GetStruct() const { return s; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetArtcategoryno(long t) { s.ARTCATEGORYNO = t; }
                void            SetStruct(const articlegrpS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTICLEGRP()  //constructor
                {
                        ::buf_default((void *)&s, ARTICLEGRP_BES, ARTICLEGRP_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTICLEGRP()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTICLEGRP_BES, ARTICLEGRP_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLEGRP_BES, ARTICLEGRP_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTICLEGRP_BES, ARTICLEGRP_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTICLEGRP& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLEGRP_BES, ARTICLEGRP_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTICLEGRP *******************************************/

 #define ARTICLEGRP_CREATE(x) exec sql create table x (\
         ARTICLENO integer default 0 not null,\
         ARTCATEGORYNO integer default 0 not null) extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of ARTICLEGRP *****************************************/

 #define ARTICLEGRP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_articlegrp_1 on _X_(\
              ArticleNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLEGRP *****************************************/

 #define ARTICLEGRP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_articlegrp_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

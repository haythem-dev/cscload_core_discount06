#ifndef __PP_ARTICLECODES_H_
#define __PP_ARTICLECODES_H_

/******************************************************************************/
/* u:\ArticleCodes ************************************************************/
/******************************************************************************/

/* Length-Define of ARTICLECODES **********************************************/

  #define L_ARTICLECODES_ARTICLENO 11
  #define L_ARTICLECODES_CODE_TYPE 6
  #define L_ARTICLECODES_ARTICLE_CODE 25
  #define L_ARTICLECODES_PREFERRED_FLAG 6

/* Length/Count-Define of ARTICLECODES ****************************************/

  #define LS_ARTICLECODES_ARTICLENO 10 + 1
  #define LS_ARTICLECODES_CODE_TYPE 5 + 1
  #define LS_ARTICLECODES_ARTICLE_CODE 25 + 1
  #define LS_ARTICLECODES_PREFERRED_FLAG 5 + 1

  #define ARTICLECODESARTICLENO 0
  #define ARTICLECODESCODE_TYPE 1
  #define ARTICLECODESARTICLE_CODE 2
  #define ARTICLECODESPREFERRED_FLAG 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTICLECODES_H
 #define ARTICLECODES_ANZ ( sizeof(ARTICLECODES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLECODES **************************************************/

 #define ARTICLECODES_LISTE \
         ARTICLECODES.ARTICLENO,\
         ARTICLECODES.CODE_TYPE,\
         ARTICLECODES.ARTICLE_CODE,\
         ARTICLECODES.PREFERRED_FLAG

 #define ARTICLECODES_LISTE_390 \
         ARTICLENO,\
         CODE_TYPE,\
         ARTICLE_CODE,\
         PREFERRED_FLAG

 #define ARTICLECODES_PLISTE \
         "ARTICLECODES.ARTICLENO,"\
         "ARTICLECODES.CODE_TYPE,"\
         "ARTICLECODES.ARTICLE_CODE,"\
         "ARTICLECODES.PREFERRED_FLAG"

 #define ARTICLECODES_PELISTE \
         "ARTICLENO,"\
         "CODE_TYPE,"\
         "ARTICLE_CODE,"\
         "PREFERRED_FLAG"

 #define ARTICLECODES_UPDLISTE \
         "ARTICLENO=?,"\
         "CODE_TYPE=?,"\
         "ARTICLE_CODE=?,"\
         "PREFERRED_FLAG=?"

/* SqlMacros-Define of ARTICLECODES *******************************************/

 #define ARTICLECODES_ZEIGER(x) \
         :x->ARTICLENO,\
         :x->CODE_TYPE,\
         :x->ARTICLE_CODE,\
         :x->PREFERRED_FLAG

 #define ARTICLECODES_ZEIGERSEL(x) \
         :x->ARTICLENO,\
         :x->CODE_TYPE,\
         :x->ARTICLE_CODE,\
         :x->PREFERRED_FLAG

 #define ARTICLECODES_UPDATE(x) \
         ARTICLECODES.ARTICLENO=:x->ARTICLENO,\
         ARTICLECODES.CODE_TYPE=:x->CODE_TYPE,\
         ARTICLECODES.ARTICLE_CODE=:x->ARTICLE_CODE,\
         ARTICLECODES.PREFERRED_FLAG=:x->PREFERRED_FLAG

/* SqlMacros390-Define of ARTICLECODES ****************************************/

 #define ARTICLECODES_ZEIGER_390 \
         :ARTICLENO,\
         :CODE_TYPE,\
         :ARTICLE_CODE,\
         :PREFERRED_FLAG

 #define ARTICLECODES_UPDATE_390 \
         ARTICLENO=:ARTICLENO,\
         CODE_TYPE=:CODE_TYPE,\
         ARTICLE_CODE=:ARTICLE_CODE,\
         PREFERRED_FLAG=:PREFERRED_FLAG

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTICLECODES *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTICLECODES {
         long ARTICLENO;
         short CODE_TYPE;
         char ARTICLE_CODE[26];
         short PREFERRED_FLAG;
        } articlecodesS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTICLECODES {
         long ARTICLENO;
         short CODE_TYPE;
         char ARTICLE_CODE[26];
         short PREFERRED_FLAG;

                        bool operator==(const N_ARTICLECODES& right) const {
                        return(
                                ARTICLENO == right.ARTICLENO &&
                                CODE_TYPE == right.CODE_TYPE &&
                                !strcmp(ARTICLE_CODE, right.ARTICLE_CODE) &&
                                PREFERRED_FLAG == right.PREFERRED_FLAG
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTICLENO = 0;
                                CODE_TYPE = 0;
                                strcpy(ARTICLE_CODE, " " );
                                PREFERRED_FLAG = 0;
#endif
                        }
         } articlecodesS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLECODES **************************************/

 struct S_ARTICLECODES {
         char ARTICLENO[11];
         char CODE_TYPE[7];
         char ARTICLE_CODE[25 + 1];
         char PREFERRED_FLAG[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLECODES *********************/

 struct O_ARTICLECODES {
         char ARTICLENO[11];
         char CODE_TYPE[7];
         char ARTICLE_CODE[25];
         char PREFERRED_FLAG[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLECODES ********************************/

 struct C_ARTICLECODES {
         long ARTICLENO;
         short CODE_TYPE;
         char ARTICLE_CODE[26];
         short PREFERRED_FLAG;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLECODES ******************************/

 struct I_ARTICLECODES {
         short ARTICLENO;
         short CODE_TYPE;
         short ARTICLE_CODE;
         short PREFERRED_FLAG;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLECODES ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTICLECODES_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 25, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTICLECODES_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 25, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of ARTICLECODES **********************************/

 #define ARTICLECODES_S390 \
         long ARTICLENO; \
         short CODE_TYPE; \
         char ARTICLE_CODE[26]; \
         short PREFERRED_FLAG; \



/* Copy-Function Struct to single Data ARTICLECODES ***************************/

 #define ARTICLECODES_S390_COPY_TO_SINGLE(_x_) \
         ARTICLENO=_x_->ARTICLENO;\
         CODE_TYPE=_x_->CODE_TYPE;\
          strcpy(ARTICLE_CODE,_x_->ARTICLE_CODE);\
         PREFERRED_FLAG=_x_->PREFERRED_FLAG;\

 #define ARTICLECODES_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLENO=ARTICLENO;\
          _x_->CODE_TYPE=CODE_TYPE;\
          strcpy(_x_->ARTICLE_CODE,ARTICLE_CODE);\
          _x_->PREFERRED_FLAG=PREFERRED_FLAG;\



/* FunctionNumber-Define of ArticleCodes **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleCodes **********************************/


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

class CARTICLECODES : public ppDadeVirtual
{
        //data members
        public:
                articlecodesS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<articlecodesS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlecodesS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<articlecodesS>; Strip(s); articlecodesS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlecodesS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<articlecodesS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<articlecodesS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArticleno() const    { return s.ARTICLENO; }
                short           GetCode_type() const    { return s.CODE_TYPE; }
                const char*     GetArticle_code(ppString& t) const      { t = s.ARTICLE_CODE; t.erasespace(ppString::END); return t.c_str(); }
                short           GetPreferred_flag() const       { return s.PREFERRED_FLAG; }
                const articlecodesS& GetStruct() const { return s; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetCode_type(short t) { s.CODE_TYPE = t; }
                void            SetArticle_code(const ppString& t) { ppGStrCopy(s.ARTICLE_CODE,t.c_str() ,L_ARTICLECODES_ARTICLE_CODE); }
                void            SetPreferred_flag(short t) { s.PREFERRED_FLAG = t; }
                void            SetStruct(const articlecodesS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTICLECODES()  //constructor
                {
                        ::buf_default((void *)&s, ARTICLECODES_BES, ARTICLECODES_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTICLECODES()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTICLECODES_BES, ARTICLECODES_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLECODES_BES, ARTICLECODES_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTICLECODES_BES, ARTICLECODES_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTICLECODES& d)
                {
#ifdef WIN32
                        ppGStripLast(d.ARTICLE_CODE);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLECODES_BES, ARTICLECODES_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTICLECODES *****************************************/

 #define ARTICLECODES_CREATE(x) exec sql create table x (\
         ARTICLENO integer default 0 not null,\
         CODE_TYPE smallint default 0 not null,\
         ARTICLE_CODE char(25) default " " not null,\
         PREFERRED_FLAG smallint default 0 not null) in ksc extent size 7844 next size 788 lock mode row;



/* CreateIndexStatement of ARTICLECODES ***************************************/

 #define ARTICLECODES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_artcodes_1 on _X_(\
              article_code ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_artcodes_2 on _X_(\
              ArticleNo,\
              preferred_flag ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLECODES ***************************************/

 #define ARTICLECODES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_artcodes_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_artcodes_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

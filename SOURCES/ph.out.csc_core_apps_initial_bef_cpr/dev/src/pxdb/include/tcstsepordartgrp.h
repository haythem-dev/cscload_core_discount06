#ifndef __PP_CSTSEPORDERARTGRP_H_
#define __PP_CSTSEPORDERARTGRP_H_

/******************************************************************************/
/* v:\CstSepOrderArtGrp *******************************************************/
/******************************************************************************/

/* Length-Define of CSTSEPORDERARTGRP *****************************************/

  #define L_CSTSEPORDERARTGRP_BRANCHNO 6
  #define L_CSTSEPORDERARTGRP_CUSTOMERNO 11
  #define L_CSTSEPORDERARTGRP_ARTGRP 6
  #define L_CSTSEPORDERARTGRP_KDAUFTRAGART 2
  #define L_CSTSEPORDERARTGRP_KOART 1
  #define L_CSTSEPORDERARTGRP_BUCHART 1
  #define L_CSTSEPORDERARTGRP_DEFERORDER 1

/* Length/Count-Define of CSTSEPORDERARTGRP ***********************************/

  #define LS_CSTSEPORDERARTGRP_BRANCHNO 5 + 1
  #define LS_CSTSEPORDERARTGRP_CUSTOMERNO 10 + 1
  #define LS_CSTSEPORDERARTGRP_ARTGRP 5 + 1
  #define LS_CSTSEPORDERARTGRP_KDAUFTRAGART 2 + 1
  #define LS_CSTSEPORDERARTGRP_KOART 1 + 1
  #define LS_CSTSEPORDERARTGRP_BUCHART 1 + 1
  #define LS_CSTSEPORDERARTGRP_DEFERORDER 1 + 1

  #define CSTSEPORDERARTGRPBRANCHNO 0
  #define CSTSEPORDERARTGRPCUSTOMERNO 1
  #define CSTSEPORDERARTGRPARTGRP 2
  #define CSTSEPORDERARTGRPKDAUFTRAGART 3
  #define CSTSEPORDERARTGRPKOART 4
  #define CSTSEPORDERARTGRPBUCHART 5
  #define CSTSEPORDERARTGRPDEFERORDER 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define CSTSEPORDERARTGRP_H
 #define CSTSEPORDERARTGRP_ANZ ( sizeof(CSTSEPORDERARTGRP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of CSTSEPORDERARTGRP *********************************************/

 #define CSTSEPORDERARTGRP_LISTE \
         CSTSEPORDERARTGRP.BRANCHNO,\
         CSTSEPORDERARTGRP.CUSTOMERNO,\
         CSTSEPORDERARTGRP.ARTGRP,\
         CSTSEPORDERARTGRP.KDAUFTRAGART,\
         CSTSEPORDERARTGRP.KOART,\
         CSTSEPORDERARTGRP.BUCHART,\
         CSTSEPORDERARTGRP.DEFERORDER

 #define CSTSEPORDERARTGRP_LISTE_390 \
         BRANCHNO,\
         CUSTOMERNO,\
         ARTGRP,\
         KDAUFTRAGART,\
         KOART,\
         BUCHART,\
         DEFERORDER

 #define CSTSEPORDERARTGRP_PLISTE \
         "CSTSEPORDERARTGRP.BRANCHNO,"\
         "CSTSEPORDERARTGRP.CUSTOMERNO,"\
         "CSTSEPORDERARTGRP.ARTGRP,"\
         "CSTSEPORDERARTGRP.KDAUFTRAGART,"\
         "CSTSEPORDERARTGRP.KOART,"\
         "CSTSEPORDERARTGRP.BUCHART,"\
         "CSTSEPORDERARTGRP.DEFERORDER"

 #define CSTSEPORDERARTGRP_PELISTE \
         "BRANCHNO,"\
         "CUSTOMERNO,"\
         "ARTGRP,"\
         "KDAUFTRAGART,"\
         "KOART,"\
         "BUCHART,"\
         "DEFERORDER"

 #define CSTSEPORDERARTGRP_UPDLISTE \
         "BRANCHNO=?,"\
         "CUSTOMERNO=?,"\
         "ARTGRP=?,"\
         "KDAUFTRAGART=?,"\
         "KOART=?,"\
         "BUCHART=?,"\
         "DEFERORDER=?"

/* SqlMacros-Define of CSTSEPORDERARTGRP **************************************/

 #define CSTSEPORDERARTGRP_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ARTGRP,\
         :x->KDAUFTRAGART,\
         :x->KOART,\
         :x->BUCHART,\
         :x->DEFERORDER

 #define CSTSEPORDERARTGRP_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->CUSTOMERNO,\
         :x->ARTGRP,\
         :x->KDAUFTRAGART,\
         :x->KOART,\
         :x->BUCHART,\
         :x->DEFERORDER

 #define CSTSEPORDERARTGRP_UPDATE(x) \
         CSTSEPORDERARTGRP.BRANCHNO=:x->BRANCHNO,\
         CSTSEPORDERARTGRP.CUSTOMERNO=:x->CUSTOMERNO,\
         CSTSEPORDERARTGRP.ARTGRP=:x->ARTGRP,\
         CSTSEPORDERARTGRP.KDAUFTRAGART=:x->KDAUFTRAGART,\
         CSTSEPORDERARTGRP.KOART=:x->KOART,\
         CSTSEPORDERARTGRP.BUCHART=:x->BUCHART,\
         CSTSEPORDERARTGRP.DEFERORDER=:x->DEFERORDER

/* SqlMacros390-Define of CSTSEPORDERARTGRP ***********************************/

 #define CSTSEPORDERARTGRP_ZEIGER_390 \
         :BRANCHNO,\
         :CUSTOMERNO,\
         :ARTGRP,\
         :KDAUFTRAGART,\
         :KOART,\
         :BUCHART,\
         :DEFERORDER

 #define CSTSEPORDERARTGRP_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         CUSTOMERNO=:CUSTOMERNO,\
         ARTGRP=:ARTGRP,\
         KDAUFTRAGART=:KDAUFTRAGART,\
         KOART=:KOART,\
         BUCHART=:BUCHART,\
         DEFERORDER=:DEFERORDER

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of CSTSEPORDERARTGRP **************************************/

 #ifndef TRANSCLASS
 typedef struct N_CSTSEPORDERARTGRP {
         short BRANCHNO;
         long CUSTOMERNO;
         short ARTGRP;
         char KDAUFTRAGART[3];
         char KOART[2];
         char BUCHART[2];
         char DEFERORDER[2];
        } cstseporderartgrpS;
 #else /*TRANSCLASS*/
 typedef struct N_CSTSEPORDERARTGRP {
         short BRANCHNO;
         long CUSTOMERNO;
         short ARTGRP;
         char KDAUFTRAGART[3];
         char KOART[2];
         char BUCHART[2];
         char DEFERORDER[2];

                        bool operator==(const N_CSTSEPORDERARTGRP& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                ARTGRP == right.ARTGRP &&
                                !strcmp(KDAUFTRAGART, right.KDAUFTRAGART) &&
                                !strcmp(KOART, right.KOART) &&
                                !strcmp(BUCHART, right.BUCHART) &&
                                !strcmp(DEFERORDER, right.DEFERORDER)
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                CUSTOMERNO = 0;
                                ARTGRP = 0;
                                strcpy(KDAUFTRAGART, " " );
                                strcpy(KOART, " " );
                                strcpy(BUCHART, " " );
                                strcpy(DEFERORDER, " " );
#endif
                        }
         } cstseporderartgrpS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of CSTSEPORDERARTGRP *********************************/

 struct S_CSTSEPORDERARTGRP {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ARTGRP[7];
         char KDAUFTRAGART[2 + 1];
         char KOART[1 + 1];
         char BUCHART[1 + 1];
         char DEFERORDER[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of CSTSEPORDERARTGRP ****************/

 struct O_CSTSEPORDERARTGRP {
         char BRANCHNO[7];
         char CUSTOMERNO[11];
         char ARTGRP[7];
         char KDAUFTRAGART[2];
         char KOART[1];
         char BUCHART[1];
         char DEFERORDER[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of CSTSEPORDERARTGRP ***************************/

 struct C_CSTSEPORDERARTGRP {
         short BRANCHNO;
         long CUSTOMERNO;
         short ARTGRP;
         char KDAUFTRAGART[3];
         char KOART;
         char BUCHART;
         char DEFERORDER;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of CSTSEPORDERARTGRP *************************/

 struct I_CSTSEPORDERARTGRP {
         short BRANCHNO;
         short CUSTOMERNO;
         short ARTGRP;
         short KDAUFTRAGART;
         short KOART;
         short BUCHART;
         short DEFERORDER;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of CSTSEPORDERARTGRP ***********************************/

#if defined (BUF_DESC)
 static struct buf_desc CSTSEPORDERARTGRP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc CSTSEPORDERARTGRP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of CSTSEPORDERARTGRP *****************************/

 #define CSTSEPORDERARTGRP_S390 \
         short BRANCHNO; \
         long CUSTOMERNO; \
         short ARTGRP; \
         char KDAUFTRAGART[3]; \
         char KOART; \
         char BUCHART; \
         char DEFERORDER; \



/* Copy-Function Struct to single Data CSTSEPORDERARTGRP **********************/

 #define CSTSEPORDERARTGRP_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         ARTGRP=_x_->ARTGRP;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\
         KOART=_x_->KOART;\
         BUCHART=_x_->BUCHART;\
         DEFERORDER=_x_->DEFERORDER;\

 #define CSTSEPORDERARTGRP_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->ARTGRP=ARTGRP;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\
          _x_->KOART=KOART;\
          _x_->BUCHART=BUCHART;\
          _x_->DEFERORDER=DEFERORDER;\



/* FunctionNumber-Define of CstSepOrderArtGrp *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CstSepOrderArtGrp *****************************/


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

class CCSTSEPORDERARTGRP : public ppDadeVirtual
{
        //data members
        public:
                cstseporderartgrpS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<cstseporderartgrpS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstseporderartgrpS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<cstseporderartgrpS>; Strip(s); cstseporderartgrpS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<cstseporderartgrpS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<cstseporderartgrpS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<cstseporderartgrpS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                short           GetArtgrp() const       { return s.ARTGRP; }
                const char*     GetKdauftragart(ppString& t) const      { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
                char            GetKoart() const        { return s.KOART[0]; }
                char            GetBuchart() const      { return s.BUCHART[0]; }
                char            GetDeferorder() const   { return s.DEFERORDER[0]; }
                const cstseporderartgrpS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetArtgrp(short t) { s.ARTGRP = t; }
                void            SetKdauftragart(const ppString& t) { ppGStrCopy(s.KDAUFTRAGART,t.c_str() ,L_CSTSEPORDERARTGRP_KDAUFTRAGART); }
                void            SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}
                void            SetBuchart(char t) { s.BUCHART[0] = t; s.BUCHART[1] = '\0';}
                void            SetDeferorder(char t) { s.DEFERORDER[0] = t; s.DEFERORDER[1] = '\0';}
                void            SetStruct(const cstseporderartgrpS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CCSTSEPORDERARTGRP()  //constructor
                {
                        ::buf_default((void *)&s, CSTSEPORDERARTGRP_BES, CSTSEPORDERARTGRP_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CCSTSEPORDERARTGRP()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, CSTSEPORDERARTGRP_BES, CSTSEPORDERARTGRP_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, CSTSEPORDERARTGRP_BES, CSTSEPORDERARTGRP_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, CSTSEPORDERARTGRP_BES, CSTSEPORDERARTGRP_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_CSTSEPORDERARTGRP& d)
                {
#ifdef WIN32
                        ppGStripLast(d.KDAUFTRAGART);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, CSTSEPORDERARTGRP_BES, CSTSEPORDERARTGRP_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of CSTSEPORDERARTGRP ************************************/

 #define CSTSEPORDERARTGRP_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         ARTGRP smallint default 0 not null,\
         KDAUFTRAGART char(2) default " " not null,\
         KOART char(1) default " " not null,\
         BUCHART char(1) default " " not null,\
         DEFERORDER char(1) default " " not null) in ksc extent size 40 next size 8 lock mode row;



/* CreateIndexStatement of CSTSEPORDERARTGRP **********************************/

 #define CSTSEPORDERARTGRP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of CSTSEPORDERARTGRP **********************************/

 #define CSTSEPORDERARTGRP_DELETE_INDEX(_X_)\
              _X_ = 0;\

#endif

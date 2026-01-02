#ifndef __PP_BUCHUNGSART_H_
#define __PP_BUCHUNGSART_H_

/******************************************************************************/
/* v:\nordat\buchungsart ******************************************************/
/******************************************************************************/

/* Length-Define of BUCHUNGSART ***********************************************/

  #define L_BUCHUNGSART_BUCHART 1
  #define L_BUCHUNGSART_BUCHMETHODE 11
  #define L_BUCHUNGSART_BEZEICHNUNG 30
  #define L_BUCHUNGSART_BRANCHNO 6

/* Length/Count-Define of BUCHUNGSART *****************************************/

  #define LS_BUCHUNGSART_BUCHART 1 + 1
  #define LS_BUCHUNGSART_BUCHMETHODE 10 + 1
  #define LS_BUCHUNGSART_BEZEICHNUNG 30 + 1
  #define LS_BUCHUNGSART_BRANCHNO 5 + 1

  #define BUCHUNGSARTBUCHART 0
  #define BUCHUNGSARTBUCHMETHODE 1
  #define BUCHUNGSARTBEZEICHNUNG 2
  #define BUCHUNGSARTBRANCHNO 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define BUCHUNGSART_H
 #define BUCHUNGSART_ANZ ( sizeof(BUCHUNGSART_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of BUCHUNGSART ***************************************************/

 #define BUCHUNGSART_LISTE \
         BUCHUNGSART.BUCHART,\
         BUCHUNGSART.BUCHMETHODE,\
         BUCHUNGSART.BEZEICHNUNG,\
         BUCHUNGSART.BRANCHNO

 #define BUCHUNGSART_LISTE_390 \
         BUCHART,\
         BUCHMETHODE,\
         BEZEICHNUNG,\
         BRANCHNO

 #define BUCHUNGSART_PLISTE \
         "BUCHUNGSART.BUCHART,"\
         "BUCHUNGSART.BUCHMETHODE,"\
         "BUCHUNGSART.BEZEICHNUNG,"\
         "BUCHUNGSART.BRANCHNO"

 #define BUCHUNGSART_PELISTE \
         "BUCHART,"\
         "BUCHMETHODE,"\
         "BEZEICHNUNG,"\
         "BRANCHNO"

 #define BUCHUNGSART_UPDLISTE \
         "BUCHART=?,"\
         "BUCHMETHODE=?,"\
         "BEZEICHNUNG=?,"\
         "BRANCHNO=?"

/* SqlMacros-Define of BUCHUNGSART ********************************************/

 #define BUCHUNGSART_ZEIGER(x) \
         :x->BUCHART,\
         :x->BUCHMETHODE,\
         :x->BEZEICHNUNG,\
         :x->BRANCHNO

 #define BUCHUNGSART_ZEIGERSEL(x) \
         :x->BUCHART,\
         :x->BUCHMETHODE,\
         :x->BEZEICHNUNG,\
         :x->BRANCHNO

 #define BUCHUNGSART_UPDATE(x) \
         BUCHUNGSART.BUCHART=:x->BUCHART,\
         BUCHUNGSART.BUCHMETHODE=:x->BUCHMETHODE,\
         BUCHUNGSART.BEZEICHNUNG=:x->BEZEICHNUNG,\
         BUCHUNGSART.BRANCHNO=:x->BRANCHNO

/* SqlMacros390-Define of BUCHUNGSART *****************************************/

 #define BUCHUNGSART_ZEIGER_390 \
         :BUCHART,\
         :BUCHMETHODE,\
         :BEZEICHNUNG,\
         :BRANCHNO

 #define BUCHUNGSART_UPDATE_390 \
         BUCHART=:BUCHART,\
         BUCHMETHODE=:BUCHMETHODE,\
         BEZEICHNUNG=:BEZEICHNUNG,\
         BRANCHNO=:BRANCHNO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of BUCHUNGSART ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_BUCHUNGSART {
         char BUCHART[2];
         long BUCHMETHODE;
         char BEZEICHNUNG[31];
         short BRANCHNO;
        } buchungsartS;
 #else /*TRANSCLASS*/
 typedef struct N_BUCHUNGSART {
         char BUCHART[2];
         long BUCHMETHODE;
         char BEZEICHNUNG[31];
         short BRANCHNO;

                        bool operator==(const N_BUCHUNGSART& right) const {
                        return(
                                !strcmp(BUCHART, right.BUCHART) &&
                                BUCHMETHODE == right.BUCHMETHODE &&
                                !strcmp(BEZEICHNUNG, right.BEZEICHNUNG) &&
                                BRANCHNO == right.BRANCHNO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                strcpy(BUCHART, " " );
                                BUCHMETHODE = 0;
                                strcpy(BEZEICHNUNG, " " );
                                BRANCHNO = 0;
#endif
                        }
         } buchungsartS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of BUCHUNGSART ***************************************/

 struct S_BUCHUNGSART {
         char BUCHART[1 + 1];
         char BUCHMETHODE[11];
         char BEZEICHNUNG[30 + 1];
         char BRANCHNO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of BUCHUNGSART **********************/

 struct O_BUCHUNGSART {
         char BUCHART[1];
         char BUCHMETHODE[11];
         char BEZEICHNUNG[30];
         char BRANCHNO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of BUCHUNGSART *********************************/

 struct C_BUCHUNGSART {
         char BUCHART;
         long BUCHMETHODE;
         char BEZEICHNUNG[31];
         short BRANCHNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of BUCHUNGSART *******************************/

 struct I_BUCHUNGSART {
         short BUCHART;
         short BUCHMETHODE;
         short BEZEICHNUNG;
         short BRANCHNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of BUCHUNGSART *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc BUCHUNGSART_BES [] =
 {
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc BUCHUNGSART_BES [] =
 {
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of BUCHUNGSART ***********************************/

 #define BUCHUNGSART_S390 \
         char BUCHART; \
         long BUCHMETHODE; \
         char BEZEICHNUNG[31]; \
         short BRANCHNO; \



/* Copy-Function Struct to single Data BUCHUNGSART ****************************/

 #define BUCHUNGSART_S390_COPY_TO_SINGLE(_x_) \
         BUCHART=_x_->BUCHART;\
         BUCHMETHODE=_x_->BUCHMETHODE;\
          strcpy(BEZEICHNUNG,_x_->BEZEICHNUNG);\
         BRANCHNO=_x_->BRANCHNO;\

 #define BUCHUNGSART_S390_COPY_TO_STRUCT(_x_) \
          _x_->BUCHART=BUCHART;\
          _x_->BUCHMETHODE=BUCHMETHODE;\
          strcpy(_x_->BEZEICHNUNG,BEZEICHNUNG);\
          _x_->BRANCHNO=BRANCHNO;\



/* FunctionNumber-Define of buchungsart ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of buchungsart ***********************************/


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

class CBUCHUNGSART : public ppDadeVirtual
{
        //data members
        public:
                buchungsartS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<buchungsartS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<buchungsartS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<buchungsartS>; Strip(s); buchungsartS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<buchungsartS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<buchungsartS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<buchungsartS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                char            GetBuchart() const      { return s.BUCHART[0]; }
                long            GetBuchmethode() const  { return s.BUCHMETHODE; }
                const char*     GetBezeichnung(ppString& t) const       { t = s.BEZEICHNUNG; t.erasespace(ppString::END); return t.c_str(); }
                short           GetBranchno() const     { return s.BRANCHNO; }
                const buchungsartS& GetStruct() const { return s; }
                void            SetBuchart(char t) { s.BUCHART[0] = t; s.BUCHART[1] = '\0';}
                void            SetBuchmethode(long t) { s.BUCHMETHODE = t; }
                void            SetBezeichnung(const ppString& t) { ppGStrCopy(s.BEZEICHNUNG,t.c_str() ,L_BUCHUNGSART_BEZEICHNUNG); }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetStruct(const buchungsartS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CBUCHUNGSART()  //constructor
                {
                        ::buf_default((void *)&s, BUCHUNGSART_BES, BUCHUNGSART_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CBUCHUNGSART()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, BUCHUNGSART_BES, BUCHUNGSART_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, BUCHUNGSART_BES, BUCHUNGSART_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, BUCHUNGSART_BES, BUCHUNGSART_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_BUCHUNGSART& d)
                {
#ifdef WIN32
                        ppGStripLast(d.BEZEICHNUNG);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, BUCHUNGSART_BES, BUCHUNGSART_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of BUCHUNGSART ******************************************/

 #define BUCHUNGSART_CREATE(x) exec sql create table x (\
         BUCHART char(1) default " " not null,\
         BUCHMETHODE integer default 0 not null,\
         BEZEICHNUNG char(30) default " " not null,\
         BRANCHNO smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of BUCHUNGSART ****************************************/

 #define BUCHUNGSART_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_buchungsart_1 on _X_(\
              BranchNo,\
              buchart ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of BUCHUNGSART ****************************************/

 #define BUCHUNGSART_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_buchungsart_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

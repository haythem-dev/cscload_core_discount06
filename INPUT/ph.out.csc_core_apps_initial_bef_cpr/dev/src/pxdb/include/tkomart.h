#ifndef __PP_KOMMIARTEN_H_
#define __PP_KOMMIARTEN_H_

/******************************************************************************/
/* v:\nordat\kommiarten *******************************************************/
/******************************************************************************/

/* Length-Define of KOMMIARTEN ************************************************/

  #define L_KOMMIARTEN_KOART 1
  #define L_KOMMIARTEN_KOMETHODE 11
  #define L_KOMMIARTEN_BEZEICHNUNG 30
  #define L_KOMMIARTEN_BRANCHNO 6

/* Length/Count-Define of KOMMIARTEN ******************************************/

  #define LS_KOMMIARTEN_KOART 1 + 1
  #define LS_KOMMIARTEN_KOMETHODE 10 + 1
  #define LS_KOMMIARTEN_BEZEICHNUNG 30 + 1
  #define LS_KOMMIARTEN_BRANCHNO 5 + 1

  #define KOMMIARTENKOART 0
  #define KOMMIARTENKOMETHODE 1
  #define KOMMIARTENBEZEICHNUNG 2
  #define KOMMIARTENBRANCHNO 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KOMMIARTEN_H
 #define KOMMIARTEN_ANZ ( sizeof(KOMMIARTEN_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KOMMIARTEN ****************************************************/

 #define KOMMIARTEN_LISTE \
         KOMMIARTEN.KOART,\
         KOMMIARTEN.KOMETHODE,\
         KOMMIARTEN.BEZEICHNUNG,\
         KOMMIARTEN.BRANCHNO

 #define KOMMIARTEN_LISTE_390 \
         KOART,\
         KOMETHODE,\
         BEZEICHNUNG,\
         BRANCHNO

 #define KOMMIARTEN_PLISTE \
         "KOMMIARTEN.KOART,"\
         "KOMMIARTEN.KOMETHODE,"\
         "KOMMIARTEN.BEZEICHNUNG,"\
         "KOMMIARTEN.BRANCHNO"

 #define KOMMIARTEN_PELISTE \
         "KOART,"\
         "KOMETHODE,"\
         "BEZEICHNUNG,"\
         "BRANCHNO"

 #define KOMMIARTEN_UPDLISTE \
         "KOART=?,"\
         "KOMETHODE=?,"\
         "BEZEICHNUNG=?,"\
         "BRANCHNO=?"

/* SqlMacros-Define of KOMMIARTEN *********************************************/

 #define KOMMIARTEN_ZEIGER(x) \
         :x->KOART,\
         :x->KOMETHODE,\
         :x->BEZEICHNUNG,\
         :x->BRANCHNO

 #define KOMMIARTEN_ZEIGERSEL(x) \
         :x->KOART,\
         :x->KOMETHODE,\
         :x->BEZEICHNUNG,\
         :x->BRANCHNO

 #define KOMMIARTEN_UPDATE(x) \
         KOMMIARTEN.KOART=:x->KOART,\
         KOMMIARTEN.KOMETHODE=:x->KOMETHODE,\
         KOMMIARTEN.BEZEICHNUNG=:x->BEZEICHNUNG,\
         KOMMIARTEN.BRANCHNO=:x->BRANCHNO

/* SqlMacros390-Define of KOMMIARTEN ******************************************/

 #define KOMMIARTEN_ZEIGER_390 \
         :KOART,\
         :KOMETHODE,\
         :BEZEICHNUNG,\
         :BRANCHNO

 #define KOMMIARTEN_UPDATE_390 \
         KOART=:KOART,\
         KOMETHODE=:KOMETHODE,\
         BEZEICHNUNG=:BEZEICHNUNG,\
         BRANCHNO=:BRANCHNO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KOMMIARTEN *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_KOMMIARTEN {
         char KOART[2];
         long KOMETHODE;
         char BEZEICHNUNG[31];
         short BRANCHNO;
        } kommiartenS;
 #else /*TRANSCLASS*/
 typedef struct N_KOMMIARTEN {
         char KOART[2];
         long KOMETHODE;
         char BEZEICHNUNG[31];
         short BRANCHNO;

                        bool operator==(const N_KOMMIARTEN& right) const {
                        return(
                                !strcmp(KOART, right.KOART) &&
                                KOMETHODE == right.KOMETHODE &&
                                !strcmp(BEZEICHNUNG, right.BEZEICHNUNG) &&
                                BRANCHNO == right.BRANCHNO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                strcpy(KOART, " " );
                                KOMETHODE = 0;
                                strcpy(BEZEICHNUNG, " " );
                                BRANCHNO = 0;
#endif
                        }
         } kommiartenS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KOMMIARTEN ****************************************/

 struct S_KOMMIARTEN {
         char KOART[1 + 1];
         char KOMETHODE[11];
         char BEZEICHNUNG[30 + 1];
         char BRANCHNO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KOMMIARTEN ***********************/

 struct O_KOMMIARTEN {
         char KOART[1];
         char KOMETHODE[11];
         char BEZEICHNUNG[30];
         char BRANCHNO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KOMMIARTEN **********************************/

 struct C_KOMMIARTEN {
         char KOART;
         long KOMETHODE;
         char BEZEICHNUNG[31];
         short BRANCHNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KOMMIARTEN ********************************/

 struct I_KOMMIARTEN {
         short KOART;
         short KOMETHODE;
         short BEZEICHNUNG;
         short BRANCHNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KOMMIARTEN ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc KOMMIARTEN_BES [] =
 {
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KOMMIARTEN_BES [] =
 {
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 30, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of KOMMIARTEN ************************************/

 #define KOMMIARTEN_S390 \
         char KOART; \
         long KOMETHODE; \
         char BEZEICHNUNG[31]; \
         short BRANCHNO; \



/* Copy-Function Struct to single Data KOMMIARTEN *****************************/

 #define KOMMIARTEN_S390_COPY_TO_SINGLE(_x_) \
         KOART=_x_->KOART;\
         KOMETHODE=_x_->KOMETHODE;\
          strcpy(BEZEICHNUNG,_x_->BEZEICHNUNG);\
         BRANCHNO=_x_->BRANCHNO;\

 #define KOMMIARTEN_S390_COPY_TO_STRUCT(_x_) \
          _x_->KOART=KOART;\
          _x_->KOMETHODE=KOMETHODE;\
          strcpy(_x_->BEZEICHNUNG,BEZEICHNUNG);\
          _x_->BRANCHNO=BRANCHNO;\



/* FunctionNumber-Define of kommiarten ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kommiarten ************************************/


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

class CKOMMIARTEN : public ppDadeVirtual
{
        //data members
        public:
                kommiartenS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<kommiartenS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kommiartenS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<kommiartenS>; Strip(s); kommiartenS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kommiartenS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<kommiartenS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<kommiartenS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                char            GetKoart() const        { return s.KOART[0]; }
                long            GetKomethode() const    { return s.KOMETHODE; }
                const char*     GetBezeichnung(ppString& t) const       { t = s.BEZEICHNUNG; t.erasespace(ppString::END); return t.c_str(); }
                short           GetBranchno() const     { return s.BRANCHNO; }
                const kommiartenS& GetStruct() const { return s; }
                void            SetKoart(char t) { s.KOART[0] = t; s.KOART[1] = '\0';}
                void            SetKomethode(long t) { s.KOMETHODE = t; }
                void            SetBezeichnung(const ppString& t) { ppGStrCopy(s.BEZEICHNUNG,t.c_str() ,L_KOMMIARTEN_BEZEICHNUNG); }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetStruct(const kommiartenS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CKOMMIARTEN()  //constructor
                {
                        ::buf_default((void *)&s, KOMMIARTEN_BES, KOMMIARTEN_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CKOMMIARTEN()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, KOMMIARTEN_BES, KOMMIARTEN_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KOMMIARTEN_BES, KOMMIARTEN_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, KOMMIARTEN_BES, KOMMIARTEN_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_KOMMIARTEN& d)
                {
#ifdef WIN32
                        ppGStripLast(d.BEZEICHNUNG);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, KOMMIARTEN_BES, KOMMIARTEN_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of KOMMIARTEN *******************************************/

 #define KOMMIARTEN_CREATE(x) exec sql create table x (\
         KOART char(1) default " " not null,\
         KOMETHODE integer default 0 not null,\
         BEZEICHNUNG char(30) default " " not null,\
         BRANCHNO smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of KOMMIARTEN *****************************************/

 #define KOMMIARTEN_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kommiarten_1 on _X_(\
              BranchNo,\
              koart ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KOMMIARTEN *****************************************/

 #define KOMMIARTEN_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kommiarten_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

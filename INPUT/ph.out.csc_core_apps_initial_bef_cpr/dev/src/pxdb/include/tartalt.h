#ifndef __PP_TARTALT_H_
#define __PP_TARTALT_H_

/******************************************************************************/
/* u:artikelaltern ************************************************************/
/******************************************************************************/

/* Length-Define of ARTIKELALTERN *********************************************/

  #define L_ARTIKELALTERN_ARTIKEL_NR 11
  #define L_ARTIKELALTERN_ARTIKEL_NR_ALTERN 11
  #define L_ARTIKELALTERN_BEMERKUNGEN 240
  #define L_ARTIKELALTERN_FILIALNR 6

/* Length/Count-Define of ARTIKELALTERN ***************************************/

  #define LS_ARTIKELALTERN_ARTIKEL_NR 10 + 1
  #define LS_ARTIKELALTERN_ARTIKEL_NR_ALTERN 10 + 1
  #define LS_ARTIKELALTERN_BEMERKUNGEN 240 + 1
  #define LS_ARTIKELALTERN_FILIALNR 5 + 1

  #define ARTIKELALTERNARTIKEL_NR 0
  #define ARTIKELALTERNARTIKEL_NR_ALTERN 1
  #define ARTIKELALTERNBEMERKUNGEN 2
  #define ARTIKELALTERNFILIALNR 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTIKELALTERN_H
 #define ARTIKELALTERN_ANZ ( sizeof(ARTIKELALTERN_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTIKELALTERN *************************************************/

 #define ARTIKELALTERN_LISTE \
         ARTIKELALTERN.ARTIKEL_NR,\
         ARTIKELALTERN.ARTIKEL_NR_ALTERN,\
         ARTIKELALTERN.BEMERKUNGEN,\
         ARTIKELALTERN.FILIALNR

 #define ARTIKELALTERN_LISTE_390 \
         ARTIKEL_NR,\
         ARTIKEL_NR_ALTERN,\
         BEMERKUNGEN,\
         FILIALNR

 #define ARTIKELALTERN_PLISTE \
         "ARTIKELALTERN.ARTIKEL_NR,"\
         "ARTIKELALTERN.ARTIKEL_NR_ALTERN,"\
         "ARTIKELALTERN.BEMERKUNGEN,"\
         "ARTIKELALTERN.FILIALNR"

 #define ARTIKELALTERN_PELISTE \
         "ARTIKEL_NR,"\
         "ARTIKEL_NR_ALTERN,"\
         "BEMERKUNGEN,"\
         "FILIALNR"

 #define ARTIKELALTERN_UPDLISTE \
         "ARTIKEL_NR=?,"\
         "ARTIKEL_NR_ALTERN=?,"\
         "BEMERKUNGEN=?,"\
         "FILIALNR=?"

/* SqlMacros-Define of ARTIKELALTERN ******************************************/

 #define ARTIKELALTERN_ZEIGER(x) \
         :x->ARTIKEL_NR,\
         :x->ARTIKEL_NR_ALTERN,\
         :x->BEMERKUNGEN,\
         :x->FILIALNR

 #define ARTIKELALTERN_ZEIGERSEL(x) \
         :x->ARTIKEL_NR,\
         :x->ARTIKEL_NR_ALTERN,\
         :x->BEMERKUNGEN,\
         :x->FILIALNR

 #define ARTIKELALTERN_UPDATE(x) \
         ARTIKELALTERN.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ARTIKELALTERN.ARTIKEL_NR_ALTERN=:x->ARTIKEL_NR_ALTERN,\
         ARTIKELALTERN.BEMERKUNGEN=:x->BEMERKUNGEN,\
         ARTIKELALTERN.FILIALNR=:x->FILIALNR

/* SqlMacros390-Define of ARTIKELALTERN ***************************************/

 #define ARTIKELALTERN_ZEIGER_390 \
         :ARTIKEL_NR,\
         :ARTIKEL_NR_ALTERN,\
         :BEMERKUNGEN,\
         :FILIALNR

 #define ARTIKELALTERN_UPDATE_390 \
         ARTIKEL_NR=:ARTIKEL_NR,\
         ARTIKEL_NR_ALTERN=:ARTIKEL_NR_ALTERN,\
         BEMERKUNGEN=:BEMERKUNGEN,\
         FILIALNR=:FILIALNR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTIKELALTERN ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTIKELALTERN {
         long ARTIKEL_NR;
         long ARTIKEL_NR_ALTERN;
         char BEMERKUNGEN[241];
         short FILIALNR;
        } artikelalternS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTIKELALTERN {
         long ARTIKEL_NR;
         long ARTIKEL_NR_ALTERN;
         char BEMERKUNGEN[241];
         short FILIALNR;

                        bool operator==(const N_ARTIKELALTERN& right) const {
                        return(
                                ARTIKEL_NR == right.ARTIKEL_NR &&
                                ARTIKEL_NR_ALTERN == right.ARTIKEL_NR_ALTERN &&
                                !strcmp(BEMERKUNGEN, right.BEMERKUNGEN) &&
                                FILIALNR == right.FILIALNR
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTIKEL_NR = 0;
                                ARTIKEL_NR_ALTERN = 0;
                                strcpy(BEMERKUNGEN, " " );
                                FILIALNR = 0;
#endif
                        }
         } artikelalternS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTIKELALTERN *************************************/

 struct S_ARTIKELALTERN {
         char ARTIKEL_NR[11];
         char ARTIKEL_NR_ALTERN[11];
         char BEMERKUNGEN[240 + 1];
         char FILIALNR[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTIKELALTERN ********************/

 struct O_ARTIKELALTERN {
         char ARTIKEL_NR[11];
         char ARTIKEL_NR_ALTERN[11];
         char BEMERKUNGEN[240];
         char FILIALNR[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of ARTIKELALTERN ********************************/

 struct C_ARTIKELALTERN {
         long ARTIKEL_NR;
         long ARTIKEL_NR_ALTERN;
         char BEMERKUNGEN[241];
         short FILIALNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of ARTIKELALTERN ******************************/

 struct I_ARTIKELALTERN {
         short ARTIKEL_NR;
         short ARTIKEL_NR_ALTERN;
         short BEMERKUNGEN;
         short FILIALNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTIKELALTERN ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTIKELALTERN_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELALTERN_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 240, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of ARTIKELALTERN *********************************/

 #define ARTIKELALTERN_S390 \
         long ARTIKEL_NR; \
         long ARTIKEL_NR_ALTERN; \
         char BEMERKUNGEN[241]; \
         short FILIALNR; \



/* Copy-Function Struct to single Data ARTIKELALTERN **************************/

 #define ARTIKELALTERN_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         ARTIKEL_NR_ALTERN=_x_->ARTIKEL_NR_ALTERN;\
          strcpy(BEMERKUNGEN,_x_->BEMERKUNGEN);\
         FILIALNR=_x_->FILIALNR;\

 #define ARTIKELALTERN_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->ARTIKEL_NR_ALTERN=ARTIKEL_NR_ALTERN;\
          strcpy(_x_->BEMERKUNGEN,BEMERKUNGEN);\
          _x_->FILIALNR=FILIALNR;\



/* FunctionNumber-Define of artikelaltern *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of artikelaltern *********************************/


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
                virtual int SelList(int FetchRel = 1,int pos=0) = 0;
                virtual int SelListHist(int FetchRel = 1,int pos=0) = 0;
                virtual int SelListFuture(int FetchRel = 1,int pos=0) = 0;
                virtual int Load(int pos=0) = 0;
                virtual int Delete(int pos=0) = 0;
                virtual int Save(int pos=0) = 0;
};
#endif

class CARTIKELALTERN : public ppDadeVirtual
{
        //data members
        public:
                artikelalternS s;
                int rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<artikelalternS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelalternS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<artikelalternS>; Strip(s); artikelalternS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelalternS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<artikelalternS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<artikelalternS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArtikel_nr() const   { return s.ARTIKEL_NR; }
                long            GetArtikel_nr_altern() const    { return s.ARTIKEL_NR_ALTERN; }
                const char*     GetBemerkungen(ppString& t) const       { t = s.BEMERKUNGEN; t.erasespace(ppString::END); return t.c_str(); }
                short           GetFilialnr() const     { return s.FILIALNR; }
                const artikelalternS& GetStruct() const { return s; }
                void            SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
                void            SetArtikel_nr_altern(long t) { s.ARTIKEL_NR_ALTERN = t; }
                void            SetBemerkungen(const ppString& t) { ppGStrCopy(s.BEMERKUNGEN,t.c_str() ,L_ARTIKELALTERN_BEMERKUNGEN); }
                void            SetFilialnr(short t) { s.FILIALNR = t; }
                void            SetStruct(const artikelalternS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTIKELALTERN()  //constructor
                {
                        ::buf_default((void *)&s,ARTIKELALTERN_BES,ARTIKELALTERN_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTIKELALTERN()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTIKELALTERN_BES, ARTIKELALTERN_ANZ );
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc=::ServerNr(pos, fkt_nr, (void *)&s,ARTIKELALTERN_BES,ARTIKELALTERN_ANZ, error_msg);
                        #else
                        rc=::Server(fkt_nr, (void *)&s,ARTIKELALTERN_BES,ARTIKELALTERN_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTIKELALTERN& d)
                {
#ifdef WIN32
                        ppGStripLast(d.BEMERKUNGEN);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNr, (void *)&s,ARTIKELALTERN_BES,ARTIKELALTERN_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTIKELALTERN ****************************************/

 #define ARTIKELALTERN_CREATE(x) exec sql create table x (\
         ARTIKEL_NR integer default 0 not null,\
         ARTIKEL_NR_ALTERN integer default 0 not null,\
         BEMERKUNGEN varchar(240,0) default " " not null,\
         FILIALNR smallint default 0 not null) in ksc extent size 312 next size 32 lock mode row;



/* CreateIndexStatement of ARTIKELALTERN **************************************/

 #define ARTIKELALTERN_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index artikelalternx on _X_(\
              artikel_nr,\
              artikel_nr_altern ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create unique index i_artaltern_1 on _X_(\
              filialnr,\
              artikel_nr,\
              artikel_nr_altern ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTIKELALTERN **************************************/

 #define ARTIKELALTERN_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index artikelalternx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_artaltern_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

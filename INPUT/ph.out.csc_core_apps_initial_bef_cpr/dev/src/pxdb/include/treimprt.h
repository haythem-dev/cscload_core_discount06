#ifndef __PP_TREIMPRT_H_
#define __PP_TREIMPRT_H_

/******************************************************************************/
/* u:\artikelreimport *********************************************************/
/******************************************************************************/

/* Length-Define of ARTIKELREIMPORT *******************************************/

  #define L_ARTIKELREIMPORT_FILIALNR 6
  #define L_ARTIKELREIMPORT_ARTIKEL_NR 11
  #define L_ARTIKELREIMPORT_ARTIKEL_NR_ALTERN 11
  #define L_ARTIKELREIMPORT_KZUPD 1
  #define L_ARTIKELREIMPORT_KZAKTIVPASSIV 1
  #define L_ARTIKELREIMPORT_REIHENFOLGE 6

/* Length/Count-Define of ARTIKELREIMPORT *************************************/

  #define LS_ARTIKELREIMPORT_FILIALNR 5 + 1
  #define LS_ARTIKELREIMPORT_ARTIKEL_NR 10 + 1
  #define LS_ARTIKELREIMPORT_ARTIKEL_NR_ALTERN 10 + 1
  #define LS_ARTIKELREIMPORT_KZUPD 1 + 1
  #define LS_ARTIKELREIMPORT_KZAKTIVPASSIV 1 + 1
  #define LS_ARTIKELREIMPORT_REIHENFOLGE 5 + 1

  #define ARTIKELREIMPORTFILIALNR 0
  #define ARTIKELREIMPORTARTIKEL_NR 1
  #define ARTIKELREIMPORTARTIKEL_NR_ALTERN 2
  #define ARTIKELREIMPORTKZUPD 3
  #define ARTIKELREIMPORTKZAKTIVPASSIV 4
  #define ARTIKELREIMPORTREIHENFOLGE 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTIKELREIMPORT_H
 #define ARTIKELREIMPORT_ANZ ( sizeof(ARTIKELREIMPORT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTIKELREIMPORT ***********************************************/

 #define ARTIKELREIMPORT_LISTE \
         ARTIKELREIMPORT.FILIALNR,\
         ARTIKELREIMPORT.ARTIKEL_NR,\
         ARTIKELREIMPORT.ARTIKEL_NR_ALTERN,\
         ARTIKELREIMPORT.KZUPD,\
         ARTIKELREIMPORT.KZAKTIVPASSIV,\
         ARTIKELREIMPORT.REIHENFOLGE

 #define ARTIKELREIMPORT_LISTE_390 \
         FILIALNR,\
         ARTIKEL_NR,\
         ARTIKEL_NR_ALTERN,\
         KZUPD,\
         KZAKTIVPASSIV,\
         REIHENFOLGE

 #define ARTIKELREIMPORT_PLISTE \
         "ARTIKELREIMPORT.FILIALNR,"\
         "ARTIKELREIMPORT.ARTIKEL_NR,"\
         "ARTIKELREIMPORT.ARTIKEL_NR_ALTERN,"\
         "ARTIKELREIMPORT.KZUPD,"\
         "ARTIKELREIMPORT.KZAKTIVPASSIV,"\
         "ARTIKELREIMPORT.REIHENFOLGE"

 #define ARTIKELREIMPORT_PELISTE \
         "FILIALNR,"\
         "ARTIKEL_NR,"\
         "ARTIKEL_NR_ALTERN,"\
         "KZUPD,"\
         "KZAKTIVPASSIV,"\
         "REIHENFOLGE"

 #define ARTIKELREIMPORT_UPDLISTE \
         "FILIALNR=?,"\
         "ARTIKEL_NR=?,"\
         "ARTIKEL_NR_ALTERN=?,"\
         "KZUPD=?,"\
         "KZAKTIVPASSIV=?,"\
         "REIHENFOLGE=?"

/* SqlMacros-Define of ARTIKELREIMPORT ****************************************/

 #define ARTIKELREIMPORT_ZEIGER(x) \
         :x->FILIALNR,\
         :x->ARTIKEL_NR,\
         :x->ARTIKEL_NR_ALTERN,\
         :x->KZUPD,\
         :x->KZAKTIVPASSIV,\
         :x->REIHENFOLGE

 #define ARTIKELREIMPORT_ZEIGERSEL(x) \
         :x->FILIALNR,\
         :x->ARTIKEL_NR,\
         :x->ARTIKEL_NR_ALTERN,\
         :x->KZUPD,\
         :x->KZAKTIVPASSIV,\
         :x->REIHENFOLGE

 #define ARTIKELREIMPORT_UPDATE(x) \
         ARTIKELREIMPORT.FILIALNR=:x->FILIALNR,\
         ARTIKELREIMPORT.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ARTIKELREIMPORT.ARTIKEL_NR_ALTERN=:x->ARTIKEL_NR_ALTERN,\
         ARTIKELREIMPORT.KZUPD=:x->KZUPD,\
         ARTIKELREIMPORT.KZAKTIVPASSIV=:x->KZAKTIVPASSIV,\
         ARTIKELREIMPORT.REIHENFOLGE=:x->REIHENFOLGE

/* SqlMacros390-Define of ARTIKELREIMPORT *************************************/

 #define ARTIKELREIMPORT_ZEIGER_390 \
         :FILIALNR,\
         :ARTIKEL_NR,\
         :ARTIKEL_NR_ALTERN,\
         :KZUPD,\
         :KZAKTIVPASSIV,\
         :REIHENFOLGE

 #define ARTIKELREIMPORT_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         ARTIKEL_NR=:ARTIKEL_NR,\
         ARTIKEL_NR_ALTERN=:ARTIKEL_NR_ALTERN,\
         KZUPD=:KZUPD,\
         KZAKTIVPASSIV=:KZAKTIVPASSIV,\
         REIHENFOLGE=:REIHENFOLGE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTIKELREIMPORT ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTIKELREIMPORT {
         short FILIALNR;
         long ARTIKEL_NR;
         long ARTIKEL_NR_ALTERN;
         char KZUPD[2];
         char KZAKTIVPASSIV[2];
         short REIHENFOLGE;
        } artikelreimportS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTIKELREIMPORT {
         short FILIALNR;
         long ARTIKEL_NR;
         long ARTIKEL_NR_ALTERN;
         char KZUPD[2];
         char KZAKTIVPASSIV[2];
         short REIHENFOLGE;

                        bool operator==(const N_ARTIKELREIMPORT& right) const {
                        return(
                                FILIALNR == right.FILIALNR &&
                                ARTIKEL_NR == right.ARTIKEL_NR &&
                                ARTIKEL_NR_ALTERN == right.ARTIKEL_NR_ALTERN &&
                                !strcmp(KZUPD, right.KZUPD) &&
                                !strcmp(KZAKTIVPASSIV, right.KZAKTIVPASSIV) &&
                                REIHENFOLGE == right.REIHENFOLGE
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                FILIALNR = 0;
                                ARTIKEL_NR = 0;
                                ARTIKEL_NR_ALTERN = 0;
                                strcpy(KZUPD, " " );
                                strcpy(KZAKTIVPASSIV, " " );
                                REIHENFOLGE = 0;
#endif
                        }
         } artikelreimportS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTIKELREIMPORT ***********************************/

 struct S_ARTIKELREIMPORT {
         char FILIALNR[7];
         char ARTIKEL_NR[11];
         char ARTIKEL_NR_ALTERN[11];
         char KZUPD[1 + 1];
         char KZAKTIVPASSIV[1 + 1];
         char REIHENFOLGE[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTIKELREIMPORT ******************/

 struct O_ARTIKELREIMPORT {
         char FILIALNR[7];
         char ARTIKEL_NR[11];
         char ARTIKEL_NR_ALTERN[11];
         char KZUPD[1];
         char KZAKTIVPASSIV[1];
         char REIHENFOLGE[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of ARTIKELREIMPORT ******************************/

 struct C_ARTIKELREIMPORT {
         short FILIALNR;
         long ARTIKEL_NR;
         long ARTIKEL_NR_ALTERN;
         char KZUPD;
         char KZAKTIVPASSIV;
         short REIHENFOLGE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of ARTIKELREIMPORT ****************************/

 struct I_ARTIKELREIMPORT {
         short FILIALNR;
         short ARTIKEL_NR;
         short ARTIKEL_NR_ALTERN;
         short KZUPD;
         short KZAKTIVPASSIV;
         short REIHENFOLGE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTIKELREIMPORT *************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTIKELREIMPORT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELREIMPORT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of ARTIKELREIMPORT *******************************/

 #define ARTIKELREIMPORT_S390 \
         short FILIALNR; \
         long ARTIKEL_NR; \
         long ARTIKEL_NR_ALTERN; \
         char KZUPD; \
         char KZAKTIVPASSIV; \
         short REIHENFOLGE; \



/* Copy-Function Struct to single Data ARTIKELREIMPORT ************************/

 #define ARTIKELREIMPORT_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         ARTIKEL_NR_ALTERN=_x_->ARTIKEL_NR_ALTERN;\
         KZUPD=_x_->KZUPD;\
         KZAKTIVPASSIV=_x_->KZAKTIVPASSIV;\
         REIHENFOLGE=_x_->REIHENFOLGE;\

 #define ARTIKELREIMPORT_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->ARTIKEL_NR_ALTERN=ARTIKEL_NR_ALTERN;\
          _x_->KZUPD=KZUPD;\
          _x_->KZAKTIVPASSIV=KZAKTIVPASSIV;\
          _x_->REIHENFOLGE=REIHENFOLGE;\



/* FunctionNumber-Define of artikelreimport ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of artikelreimport *******************************/


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

class CARTIKELREIMPORT : public ppDadeVirtual
{
        //data members
        public:
                artikelreimportS s;
                int rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<artikelreimportS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelreimportS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<artikelreimportS>; Strip(s); artikelreimportS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelreimportS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<artikelreimportS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<artikelreimportS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetFilialnr() const     { return s.FILIALNR; }
                long            GetArtikel_nr() const   { return s.ARTIKEL_NR; }
                long            GetArtikel_nr_altern() const    { return s.ARTIKEL_NR_ALTERN; }
                char            GetKzupd() const        { return s.KZUPD[0]; }
                char            GetKzaktivpassiv() const        { return s.KZAKTIVPASSIV[0]; }
                short           GetReihenfolge() const  { return s.REIHENFOLGE; }
                const artikelreimportS& GetStruct() const { return s; }
                void            SetFilialnr(short t) { s.FILIALNR = t; }
                void            SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
                void            SetArtikel_nr_altern(long t) { s.ARTIKEL_NR_ALTERN = t; }
                void            SetKzupd(char t) { s.KZUPD[0] = t; s.KZUPD[1] = '\0';}
                void            SetKzaktivpassiv(char t) { s.KZAKTIVPASSIV[0] = t; s.KZAKTIVPASSIV[1] = '\0';}
                void            SetReihenfolge(short t) { s.REIHENFOLGE = t; }
                void            SetStruct(const artikelreimportS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTIKELREIMPORT()  //constructor
                {
                        ::buf_default((void *)&s,ARTIKELREIMPORT_BES,ARTIKELREIMPORT_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTIKELREIMPORT()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTIKELREIMPORT_BES, ARTIKELREIMPORT_ANZ );
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        FehlerBehandlung( -1, "False function number!" );
                        return -1;
                }

        private:

                void Strip(N_ARTIKELREIMPORT& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNr, (void *)&s,ARTIKELREIMPORT_BES,ARTIKELREIMPORT_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTIKELREIMPORT **************************************/

 #define ARTIKELREIMPORT_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         ARTIKEL_NR integer default 0 not null,\
         ARTIKEL_NR_ALTERN integer default 0 not null,\
         KZUPD char(1) default " " not null,\
         KZAKTIVPASSIV char(1) default " " not null,\
         REIHENFOLGE smallint default 0 not null) in ksc extent size 4024 next size 404 lock mode row;



/* CreateIndexStatement of ARTIKELREIMPORT ************************************/

 #define ARTIKELREIMPORT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index a_artikelreimport1 on _X_(\
              filialnr,\
              artikel_nr,\
              artikel_nr_altern ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTIKELREIMPORT ************************************/

 #define ARTIKELREIMPORT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index a_artikelreimport1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

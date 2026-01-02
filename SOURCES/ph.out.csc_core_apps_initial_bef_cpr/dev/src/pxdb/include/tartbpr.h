#ifndef __PP_ARTIKELPREIS_H_
#define __PP_ARTIKELPREIS_H_

/******************************************************************************/
/* u:\artikelpreis ************************************************************/
/******************************************************************************/

/* Length-Define of ARTIKELPREIS **********************************************/

  #define L_ARTIKELPREIS_ARTIKEL_NR 11
  #define L_ARTIKELPREIS_DATUMGUELTIGAB 11
  #define L_ARTIKELPREIS_DATUMGUELTIGBIS 11
  #define L_ARTIKELPREIS_PREISEKAPO 9
  #define N_ARTIKELPREIS_PREISEKAPO 2
  #define L_ARTIKELPREIS_PREISEKGROSSO 9
  #define N_ARTIKELPREIS_PREISEKGROSSO 2
  #define L_ARTIKELPREIS_PREISEKGROSSONA 9
  #define N_ARTIKELPREIS_PREISEKGROSSONA 2
  #define L_ARTIKELPREIS_PREISVKAPO 9
  #define N_ARTIKELPREIS_PREISVKAPO 2
  #define L_ARTIKELPREIS_RABATTFEST 7
  #define N_ARTIKELPREIS_RABATTFEST 2
  #define L_ARTIKELPREIS_RABATTFESTDM 9
  #define N_ARTIKELPREIS_RABATTFESTDM 2
  #define L_ARTIKELPREIS_PREISFEST 9
  #define N_ARTIKELPREIS_PREISFEST 2
  #define L_ARTIKELPREIS_PREISPROZENT 5
  #define N_ARTIKELPREIS_PREISPROZENT 2
  #define L_ARTIKELPREIS_PREISAGP 9
  #define N_ARTIKELPREIS_PREISAGP 2
  #define L_ARTIKELPREIS_PREIS_TYP 6
  #define L_ARTIKELPREIS_MAXAVP 9
  #define N_ARTIKELPREIS_MAXAVP 2

/* Length/Count-Define of ARTIKELPREIS ****************************************/

  #define LS_ARTIKELPREIS_ARTIKEL_NR 10 + 1
  #define LS_ARTIKELPREIS_DATUMGUELTIGAB 10 + 1
  #define LS_ARTIKELPREIS_DATUMGUELTIGBIS 10 + 1
  #define LS_ARTIKELPREIS_PREISEKAPO 9 + 2
  #define LS_ARTIKELPREIS_PREISEKGROSSO 9 + 2
  #define LS_ARTIKELPREIS_PREISEKGROSSONA 9 + 2
  #define LS_ARTIKELPREIS_PREISVKAPO 9 + 2
  #define LS_ARTIKELPREIS_RABATTFEST 7 + 2
  #define LS_ARTIKELPREIS_RABATTFESTDM 9 + 2
  #define LS_ARTIKELPREIS_PREISFEST 9 + 2
  #define LS_ARTIKELPREIS_PREISPROZENT 5 + 2
  #define LS_ARTIKELPREIS_PREISAGP 9 + 2
  #define LS_ARTIKELPREIS_PREIS_TYP 5 + 1
  #define LS_ARTIKELPREIS_MAXAVP 9 + 2

  #define ARTIKELPREISARTIKEL_NR 0
  #define ARTIKELPREISDATUMGUELTIGAB 1
  #define ARTIKELPREISDATUMGUELTIGBIS 2
  #define ARTIKELPREISPREISEKAPO 3
  #define ARTIKELPREISPREISEKGROSSO 4
  #define ARTIKELPREISPREISEKGROSSONA 5
  #define ARTIKELPREISPREISVKAPO 6
  #define ARTIKELPREISRABATTFEST 7
  #define ARTIKELPREISRABATTFESTDM 8
  #define ARTIKELPREISPREISFEST 9
  #define ARTIKELPREISPREISPROZENT 10
  #define ARTIKELPREISPREISAGP 11
  #define ARTIKELPREISPREIS_TYP 12
  #define ARTIKELPREISMAXAVP 13

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTIKELPREIS_H
 #define ARTIKELPREIS_ANZ ( sizeof(ARTIKELPREIS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTIKELPREIS **************************************************/

 #define ARTIKELPREIS_LISTE \
         ARTIKELPREIS.ARTIKEL_NR,\
         ARTIKELPREIS.DATUMGUELTIGAB,\
         ARTIKELPREIS.DATUMGUELTIGBIS,\
         ARTIKELPREIS.PREISEKAPO,\
         ARTIKELPREIS.PREISEKGROSSO,\
         ARTIKELPREIS.PREISEKGROSSONA,\
         ARTIKELPREIS.PREISVKAPO,\
         ARTIKELPREIS.RABATTFEST,\
         ARTIKELPREIS.RABATTFESTDM,\
         ARTIKELPREIS.PREISFEST,\
         ARTIKELPREIS.PREISPROZENT,\
         ARTIKELPREIS.PREISAGP,\
         ARTIKELPREIS.PREIS_TYP,\
         ARTIKELPREIS.MAXAVP

 #define ARTIKELPREIS_LISTE_390 \
         ARTIKEL_NR,\
         DATUMGUELTIGAB,\
         DATUMGUELTIGBIS,\
         PREISEKAPO,\
         PREISEKGROSSO,\
         PREISEKGROSSONA,\
         PREISVKAPO,\
         RABATTFEST,\
         RABATTFESTDM,\
         PREISFEST,\
         PREISPROZENT,\
         PREISAGP,\
         PREIS_TYP,\
         MAXAVP

 #define ARTIKELPREIS_PLISTE \
         "ARTIKELPREIS.ARTIKEL_NR,"\
         "ARTIKELPREIS.DATUMGUELTIGAB,"\
         "ARTIKELPREIS.DATUMGUELTIGBIS,"\
         "ARTIKELPREIS.PREISEKAPO,"\
         "ARTIKELPREIS.PREISEKGROSSO,"\
         "ARTIKELPREIS.PREISEKGROSSONA,"\
         "ARTIKELPREIS.PREISVKAPO,"\
         "ARTIKELPREIS.RABATTFEST,"\
         "ARTIKELPREIS.RABATTFESTDM,"\
         "ARTIKELPREIS.PREISFEST,"\
         "ARTIKELPREIS.PREISPROZENT,"\
         "ARTIKELPREIS.PREISAGP,"\
         "ARTIKELPREIS.PREIS_TYP,"\
         "ARTIKELPREIS.MAXAVP"

 #define ARTIKELPREIS_PELISTE \
         "ARTIKEL_NR,"\
         "DATUMGUELTIGAB,"\
         "DATUMGUELTIGBIS,"\
         "PREISEKAPO,"\
         "PREISEKGROSSO,"\
         "PREISEKGROSSONA,"\
         "PREISVKAPO,"\
         "RABATTFEST,"\
         "RABATTFESTDM,"\
         "PREISFEST,"\
         "PREISPROZENT,"\
         "PREISAGP,"\
         "PREIS_TYP,"\
         "MAXAVP"

 #define ARTIKELPREIS_UPDLISTE \
         "ARTIKEL_NR=?,"\
         "DATUMGUELTIGAB=?,"\
         "DATUMGUELTIGBIS=?,"\
         "PREISEKAPO=?,"\
         "PREISEKGROSSO=?,"\
         "PREISEKGROSSONA=?,"\
         "PREISVKAPO=?,"\
         "RABATTFEST=?,"\
         "RABATTFESTDM=?,"\
         "PREISFEST=?,"\
         "PREISPROZENT=?,"\
         "PREISAGP=?,"\
         "PREIS_TYP=?,"\
         "MAXAVP=?"

/* SqlMacros-Define of ARTIKELPREIS *******************************************/

 #define ARTIKELPREIS_ZEIGER(x) \
         :x->ARTIKEL_NR,\
         :x->DATUMGUELTIGAB,\
         :x->DATUMGUELTIGBIS,\
         :x->PREISEKAPO,\
         :x->PREISEKGROSSO,\
         :x->PREISEKGROSSONA,\
         :x->PREISVKAPO,\
         :x->RABATTFEST,\
         :x->RABATTFESTDM,\
         :x->PREISFEST,\
         :x->PREISPROZENT,\
         :x->PREISAGP,\
         :x->PREIS_TYP,\
         :x->MAXAVP

 #define ARTIKELPREIS_ZEIGERSEL(x) \
         :x->ARTIKEL_NR,\
         :x->DATUMGUELTIGAB,\
         :x->DATUMGUELTIGBIS,\
         :x->PREISEKAPO,\
         :x->PREISEKGROSSO,\
         :x->PREISEKGROSSONA,\
         :x->PREISVKAPO,\
         :x->RABATTFEST,\
         :x->RABATTFESTDM,\
         :x->PREISFEST,\
         :x->PREISPROZENT,\
         :x->PREISAGP,\
         :x->PREIS_TYP,\
         :x->MAXAVP

 #define ARTIKELPREIS_UPDATE(x) \
         ARTIKELPREIS.ARTIKEL_NR=:x->ARTIKEL_NR,\
         ARTIKELPREIS.DATUMGUELTIGAB=:x->DATUMGUELTIGAB,\
         ARTIKELPREIS.DATUMGUELTIGBIS=:x->DATUMGUELTIGBIS,\
         ARTIKELPREIS.PREISEKAPO=:x->PREISEKAPO,\
         ARTIKELPREIS.PREISEKGROSSO=:x->PREISEKGROSSO,\
         ARTIKELPREIS.PREISEKGROSSONA=:x->PREISEKGROSSONA,\
         ARTIKELPREIS.PREISVKAPO=:x->PREISVKAPO,\
         ARTIKELPREIS.RABATTFEST=:x->RABATTFEST,\
         ARTIKELPREIS.RABATTFESTDM=:x->RABATTFESTDM,\
         ARTIKELPREIS.PREISFEST=:x->PREISFEST,\
         ARTIKELPREIS.PREISPROZENT=:x->PREISPROZENT,\
         ARTIKELPREIS.PREISAGP=:x->PREISAGP,\
         ARTIKELPREIS.PREIS_TYP=:x->PREIS_TYP,\
         ARTIKELPREIS.MAXAVP=:x->MAXAVP

/* SqlMacros390-Define of ARTIKELPREIS ****************************************/

 #define ARTIKELPREIS_ZEIGER_390 \
         :ARTIKEL_NR,\
         :DATUMGUELTIGAB,\
         :DATUMGUELTIGBIS,\
         :PREISEKAPO,\
         :PREISEKGROSSO,\
         :PREISEKGROSSONA,\
         :PREISVKAPO,\
         :RABATTFEST,\
         :RABATTFESTDM,\
         :PREISFEST,\
         :PREISPROZENT,\
         :PREISAGP,\
         :PREIS_TYP,\
         :MAXAVP

 #define ARTIKELPREIS_UPDATE_390 \
         ARTIKEL_NR=:ARTIKEL_NR,\
         DATUMGUELTIGAB=:DATUMGUELTIGAB,\
         DATUMGUELTIGBIS=:DATUMGUELTIGBIS,\
         PREISEKAPO=:PREISEKAPO,\
         PREISEKGROSSO=:PREISEKGROSSO,\
         PREISEKGROSSONA=:PREISEKGROSSONA,\
         PREISVKAPO=:PREISVKAPO,\
         RABATTFEST=:RABATTFEST,\
         RABATTFESTDM=:RABATTFESTDM,\
         PREISFEST=:PREISFEST,\
         PREISPROZENT=:PREISPROZENT,\
         PREISAGP=:PREISAGP,\
         PREIS_TYP=:PREIS_TYP,\
         MAXAVP=:MAXAVP

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTIKELPREIS *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTIKELPREIS {
         long ARTIKEL_NR;
         long DATUMGUELTIGAB;
         long DATUMGUELTIGBIS;
         double PREISEKAPO;
         double PREISEKGROSSO;
         double PREISEKGROSSONA;
         double PREISVKAPO;
         double RABATTFEST;
         double RABATTFESTDM;
         double PREISFEST;
         double PREISPROZENT;
         double PREISAGP;
         short PREIS_TYP;
         double MAXAVP;
        } artikelpreisS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTIKELPREIS {
         long ARTIKEL_NR;
         long DATUMGUELTIGAB;
         long DATUMGUELTIGBIS;
         double PREISEKAPO;
         double PREISEKGROSSO;
         double PREISEKGROSSONA;
         double PREISVKAPO;
         double RABATTFEST;
         double RABATTFESTDM;
         double PREISFEST;
         double PREISPROZENT;
         double PREISAGP;
         short PREIS_TYP;
         double MAXAVP;

                        bool operator==(const N_ARTIKELPREIS& right) const {
                        return(
                                ARTIKEL_NR == right.ARTIKEL_NR &&
                                DATUMGUELTIGAB == right.DATUMGUELTIGAB &&
                                DATUMGUELTIGBIS == right.DATUMGUELTIGBIS &&
                                PREISEKAPO == right.PREISEKAPO &&
                                PREISEKGROSSO == right.PREISEKGROSSO &&
                                PREISEKGROSSONA == right.PREISEKGROSSONA &&
                                PREISVKAPO == right.PREISVKAPO &&
                                RABATTFEST == right.RABATTFEST &&
                                RABATTFESTDM == right.RABATTFESTDM &&
                                PREISFEST == right.PREISFEST &&
                                PREISPROZENT == right.PREISPROZENT &&
                                PREISAGP == right.PREISAGP &&
                                PREIS_TYP == right.PREIS_TYP &&
                                MAXAVP == right.MAXAVP
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTIKEL_NR = 0;
                                DATUMGUELTIGAB = 0;
                                DATUMGUELTIGBIS = 0;
                                PREISEKAPO = 0;
                                PREISEKGROSSO = 0;
                                PREISEKGROSSONA = 0;
                                PREISVKAPO = 0;
                                RABATTFEST = 0;
                                RABATTFESTDM = 0;
                                PREISFEST = 0;
                                PREISPROZENT = 0;
                                PREISAGP = 0;
                                PREIS_TYP = 0;
                                MAXAVP = 0;
#endif
                        }
         } artikelpreisS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTIKELPREIS **************************************/

 struct S_ARTIKELPREIS {
         char ARTIKEL_NR[11];
         char DATUMGUELTIGAB[11];
         char DATUMGUELTIGBIS[11];
         char PREISEKAPO[9 + 2];
         char PREISEKGROSSO[9 + 2];
         char PREISEKGROSSONA[9 + 2];
         char PREISVKAPO[9 + 2];
         char RABATTFEST[7 + 2];
         char RABATTFESTDM[9 + 2];
         char PREISFEST[9 + 2];
         char PREISPROZENT[5 + 2];
         char PREISAGP[9 + 2];
         char PREIS_TYP[7];
         char MAXAVP[9 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTIKELPREIS *********************/

 struct O_ARTIKELPREIS {
         char ARTIKEL_NR[11];
         char DATUMGUELTIGAB[11];
         char DATUMGUELTIGBIS[11];
         char PREISEKAPO[9];
         char PREISEKGROSSO[9];
         char PREISEKGROSSONA[9];
         char PREISVKAPO[9];
         char RABATTFEST[7];
         char RABATTFESTDM[9];
         char PREISFEST[9];
         char PREISPROZENT[5];
         char PREISAGP[9];
         char PREIS_TYP[7];
         char MAXAVP[9];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTIKELPREIS ********************************/

 struct C_ARTIKELPREIS {
         long ARTIKEL_NR;
         long DATUMGUELTIGAB;
         long DATUMGUELTIGBIS;
         double PREISEKAPO;
         double PREISEKGROSSO;
         double PREISEKGROSSONA;
         double PREISVKAPO;
         double RABATTFEST;
         double RABATTFESTDM;
         double PREISFEST;
         double PREISPROZENT;
         double PREISAGP;
         short PREIS_TYP;
         double MAXAVP;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTIKELPREIS ******************************/

 struct I_ARTIKELPREIS {
         short ARTIKEL_NR;
         short DATUMGUELTIGAB;
         short DATUMGUELTIGBIS;
         short PREISEKAPO;
         short PREISEKGROSSO;
         short PREISEKGROSSONA;
         short PREISVKAPO;
         short RABATTFEST;
         short RABATTFESTDM;
         short PREISFEST;
         short PREISPROZENT;
         short PREISAGP;
         short PREIS_TYP;
         short MAXAVP;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTIKELPREIS ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTIKELPREIS_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 7, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTIKELPREIS_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 7, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_D, 9, 2 },
 };
#endif

/* description for datatypes of ARTIKELPREIS **********************************/

 #define ARTIKELPREIS_S390 \
         long ARTIKEL_NR; \
         long DATUMGUELTIGAB; \
         long DATUMGUELTIGBIS; \
         double PREISEKAPO; \
         double PREISEKGROSSO; \
         double PREISEKGROSSONA; \
         double PREISVKAPO; \
         double RABATTFEST; \
         double RABATTFESTDM; \
         double PREISFEST; \
         double PREISPROZENT; \
         double PREISAGP; \
         short PREIS_TYP; \
         double MAXAVP; \



/* Copy-Function Struct to single Data ARTIKELPREIS ***************************/

 #define ARTIKELPREIS_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         DATUMGUELTIGAB=_x_->DATUMGUELTIGAB;\
         DATUMGUELTIGBIS=_x_->DATUMGUELTIGBIS;\
         PREISEKAPO=_x_->PREISEKAPO;\
         PREISEKGROSSO=_x_->PREISEKGROSSO;\
         PREISEKGROSSONA=_x_->PREISEKGROSSONA;\
         PREISVKAPO=_x_->PREISVKAPO;\
         RABATTFEST=_x_->RABATTFEST;\
         RABATTFESTDM=_x_->RABATTFESTDM;\
         PREISFEST=_x_->PREISFEST;\
         PREISPROZENT=_x_->PREISPROZENT;\
         PREISAGP=_x_->PREISAGP;\
         PREIS_TYP=_x_->PREIS_TYP;\
         MAXAVP=_x_->MAXAVP;\

 #define ARTIKELPREIS_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->DATUMGUELTIGAB=DATUMGUELTIGAB;\
          _x_->DATUMGUELTIGBIS=DATUMGUELTIGBIS;\
          _x_->PREISEKAPO=PREISEKAPO;\
          _x_->PREISEKGROSSO=PREISEKGROSSO;\
          _x_->PREISEKGROSSONA=PREISEKGROSSONA;\
          _x_->PREISVKAPO=PREISVKAPO;\
          _x_->RABATTFEST=RABATTFEST;\
          _x_->RABATTFESTDM=RABATTFESTDM;\
          _x_->PREISFEST=PREISFEST;\
          _x_->PREISPROZENT=PREISPROZENT;\
          _x_->PREISAGP=PREISAGP;\
          _x_->PREIS_TYP=PREIS_TYP;\
          _x_->MAXAVP=MAXAVP;\



/* FunctionNumber-Define of artikelpreis **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of artikelpreis **********************************/


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

class CARTIKELPREIS : public ppDadeVirtual
{
        //data members
        public:
                artikelpreisS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<artikelpreisS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelpreisS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<artikelpreisS>; Strip(s); artikelpreisS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artikelpreisS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<artikelpreisS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<artikelpreisS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArtikel_nr() const   { return s.ARTIKEL_NR; }
                long            GetDatumgueltigab() const       { return s.DATUMGUELTIGAB; }
                long            GetDatumgueltigbis() const      { return s.DATUMGUELTIGBIS; }
                double          GetPreisekapo() const   { return s.PREISEKAPO; }
                double          GetPreisekgrosso() const        { return s.PREISEKGROSSO; }
                double          GetPreisekgrossona() const      { return s.PREISEKGROSSONA; }
                double          GetPreisvkapo() const   { return s.PREISVKAPO; }
                double          GetRabattfest() const   { return s.RABATTFEST; }
                double          GetRabattfestdm() const { return s.RABATTFESTDM; }
                double          GetPreisfest() const    { return s.PREISFEST; }
                double          GetPreisprozent() const { return s.PREISPROZENT; }
                double          GetPreisagp() const     { return s.PREISAGP; }
                short           GetPreis_typ() const    { return s.PREIS_TYP; }
                double          GetMaxavp() const       { return s.MAXAVP; }
                const artikelpreisS& GetStruct() const { return s; }
                void            SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
                void            SetDatumgueltigab(long t) { s.DATUMGUELTIGAB = t; }
                void            SetDatumgueltigbis(long t) { s.DATUMGUELTIGBIS = t; }
                void            SetPreisekapo(double t) { s.PREISEKAPO = t; }
                void            SetPreisekgrosso(double t) { s.PREISEKGROSSO = t; }
                void            SetPreisekgrossona(double t) { s.PREISEKGROSSONA = t; }
                void            SetPreisvkapo(double t) { s.PREISVKAPO = t; }
                void            SetRabattfest(double t) { s.RABATTFEST = t; }
                void            SetRabattfestdm(double t) { s.RABATTFESTDM = t; }
                void            SetPreisfest(double t) { s.PREISFEST = t; }
                void            SetPreisprozent(double t) { s.PREISPROZENT = t; }
                void            SetPreisagp(double t) { s.PREISAGP = t; }
                void            SetPreis_typ(short t) { s.PREIS_TYP = t; }
                void            SetMaxavp(double t) { s.MAXAVP = t; }
                void            SetStruct(const artikelpreisS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTIKELPREIS()  //constructor
                {
                        ::buf_default((void *)&s, ARTIKELPREIS_BES, ARTIKELPREIS_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTIKELPREIS()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTIKELPREIS_BES, ARTIKELPREIS_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTIKELPREIS_BES, ARTIKELPREIS_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTIKELPREIS_BES, ARTIKELPREIS_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTIKELPREIS& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTIKELPREIS_BES, ARTIKELPREIS_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTIKELPREIS *****************************************/

 #define ARTIKELPREIS_CREATE(x) exec sql create table x (\
         ARTIKEL_NR integer default 0 not null,\
         DATUMGUELTIGAB integer default 0 not null,\
         DATUMGUELTIGBIS integer default 0 not null,\
         PREISEKAPO decimal(9,2) default 0 not null,\
         PREISEKGROSSO decimal(9,2) default 0 not null,\
         PREISEKGROSSONA decimal(9,2) default 0 not null,\
         PREISVKAPO decimal(9,2) default 0 not null,\
         RABATTFEST decimal(7,2) default 0 not null,\
         RABATTFESTDM decimal(9,2) default 0 not null,\
         PREISFEST decimal(9,2) default 0 not null,\
         PREISPROZENT decimal(5,2) default 0 not null,\
         PREISAGP decimal(9,2) default 0 not null,\
         PREIS_TYP smallint default 0 not null,\
         MAXAVP decimal(9,2) default 0 not null) in ksc extent size 4080 next size 408 lock mode row;



/* CreateIndexStatement of ARTIKELPREIS ***************************************/

 #define ARTIKELPREIS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index artikelpreisx on _X_(\
              artikel_nr,\
              datumgueltigab,\
              preis_typ ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTIKELPREIS ***************************************/

 #define ARTIKELPREIS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index artikelpreisx;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

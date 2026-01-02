#ifndef __PP_NACHLIEFPROT_H_
#define __PP_NACHLIEFPROT_H_

/******************************************************************************/
/* u:\nachliefprot ************************************************************/
/******************************************************************************/

/* Length-Define of NACHLIEFPROT **********************************************/

  #define L_NACHLIEFPROT_ARTIKEL_NR 11
  #define L_NACHLIEFPROT_IDFNR 11
  #define L_NACHLIEFPROT_NL_MENGE_ALT 11
  #define L_NACHLIEFPROT_AENDTYP 6
  #define L_NACHLIEFPROT_POSTYP 6
  #define L_NACHLIEFPROT_DATUM 11
  #define L_NACHLIEFPROT_POSNR 11
  #define L_NACHLIEFPROT_KDAUFTRAGNR 11
  #define L_NACHLIEFPROT_ZEIT_NEU 11
  #define L_NACHLIEFPROT_DATUM_NEU 11
  #define L_NACHLIEFPROT_KDAUFTRAG_NR_NEU 11
  #define L_NACHLIEFPROT_NL_MENGE_AKTUELL 11
  #define L_NACHLIEFPROT_NL_MENGE_GELIEFER 11
  #define L_NACHLIEFPROT_NL_MENGE_NEU 11
  #define L_NACHLIEFPROT_UID 11
  #define L_NACHLIEFPROT_USERBRANCHNO 6

/* Length/Count-Define of NACHLIEFPROT ****************************************/

  #define LS_NACHLIEFPROT_ARTIKEL_NR 10 + 1
  #define LS_NACHLIEFPROT_IDFNR 10 + 1
  #define LS_NACHLIEFPROT_NL_MENGE_ALT 10 + 1
  #define LS_NACHLIEFPROT_AENDTYP 5 + 1
  #define LS_NACHLIEFPROT_POSTYP 5 + 1
  #define LS_NACHLIEFPROT_DATUM 10 + 1
  #define LS_NACHLIEFPROT_POSNR 10 + 1
  #define LS_NACHLIEFPROT_KDAUFTRAGNR 10 + 1
  #define LS_NACHLIEFPROT_ZEIT_NEU 10 + 1
  #define LS_NACHLIEFPROT_DATUM_NEU 10 + 1
  #define LS_NACHLIEFPROT_KDAUFTRAG_NR_NEU 10 + 1
  #define LS_NACHLIEFPROT_NL_MENGE_AKTUELL 10 + 1
  #define LS_NACHLIEFPROT_NL_MENGE_GELIEFER 10 + 1
  #define LS_NACHLIEFPROT_NL_MENGE_NEU 10 + 1
  #define LS_NACHLIEFPROT_UID 10 + 1
  #define LS_NACHLIEFPROT_USERBRANCHNO 5 + 1

  #define NACHLIEFPROTARTIKEL_NR 0
  #define NACHLIEFPROTIDFNR 1
  #define NACHLIEFPROTNL_MENGE_ALT 2
  #define NACHLIEFPROTAENDTYP 3
  #define NACHLIEFPROTPOSTYP 4
  #define NACHLIEFPROTDATUM 5
  #define NACHLIEFPROTPOSNR 6
  #define NACHLIEFPROTKDAUFTRAGNR 7
  #define NACHLIEFPROTZEIT_NEU 8
  #define NACHLIEFPROTDATUM_NEU 9
  #define NACHLIEFPROTKDAUFTRAG_NR_NEU 10
  #define NACHLIEFPROTNL_MENGE_AKTUELL 11
  #define NACHLIEFPROTNL_MENGE_GELIEFER 12
  #define NACHLIEFPROTNL_MENGE_NEU 13
  #define NACHLIEFPROTUID 14
  #define NACHLIEFPROTUSERBRANCHNO 15

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define NACHLIEFPROT_H
 #define NACHLIEFPROT_ANZ ( sizeof(NACHLIEFPROT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of NACHLIEFPROT **************************************************/

 #define NACHLIEFPROT_LISTE \
         NACHLIEFPROT.ARTIKEL_NR,\
         NACHLIEFPROT.IDFNR,\
         NACHLIEFPROT.NL_MENGE_ALT,\
         NACHLIEFPROT.AENDTYP,\
         NACHLIEFPROT.POSTYP,\
         NACHLIEFPROT.DATUM,\
         NACHLIEFPROT.POSNR,\
         NACHLIEFPROT.KDAUFTRAGNR,\
         NACHLIEFPROT.ZEIT_NEU,\
         NACHLIEFPROT.DATUM_NEU,\
         NACHLIEFPROT.KDAUFTRAG_NR_NEU,\
         NACHLIEFPROT.NL_MENGE_AKTUELL,\
         NACHLIEFPROT.NL_MENGE_GELIEFER,\
         NACHLIEFPROT.NL_MENGE_NEU,\
         NACHLIEFPROT.UID,\
         NACHLIEFPROT.USERBRANCHNO

 #define NACHLIEFPROT_LISTE_390 \
         ARTIKEL_NR,\
         IDFNR,\
         NL_MENGE_ALT,\
         AENDTYP,\
         POSTYP,\
         DATUM,\
         POSNR,\
         KDAUFTRAGNR,\
         ZEIT_NEU,\
         DATUM_NEU,\
         KDAUFTRAG_NR_NEU,\
         NL_MENGE_AKTUELL,\
         NL_MENGE_GELIEFER,\
         NL_MENGE_NEU,\
         UID,\
         USERBRANCHNO

 #define NACHLIEFPROT_PLISTE \
         "NACHLIEFPROT.ARTIKEL_NR,"\
         "NACHLIEFPROT.IDFNR,"\
         "NACHLIEFPROT.NL_MENGE_ALT,"\
         "NACHLIEFPROT.AENDTYP,"\
         "NACHLIEFPROT.POSTYP,"\
         "NACHLIEFPROT.DATUM,"\
         "NACHLIEFPROT.POSNR,"\
         "NACHLIEFPROT.KDAUFTRAGNR,"\
         "NACHLIEFPROT.ZEIT_NEU,"\
         "NACHLIEFPROT.DATUM_NEU,"\
         "NACHLIEFPROT.KDAUFTRAG_NR_NEU,"\
         "NACHLIEFPROT.NL_MENGE_AKTUELL,"\
         "NACHLIEFPROT.NL_MENGE_GELIEFER,"\
         "NACHLIEFPROT.NL_MENGE_NEU,"\
         "NACHLIEFPROT.UID,"\
         "NACHLIEFPROT.USERBRANCHNO"

 #define NACHLIEFPROT_PELISTE \
         "ARTIKEL_NR,"\
         "IDFNR,"\
         "NL_MENGE_ALT,"\
         "AENDTYP,"\
         "POSTYP,"\
         "DATUM,"\
         "POSNR,"\
         "KDAUFTRAGNR,"\
         "ZEIT_NEU,"\
         "DATUM_NEU,"\
         "KDAUFTRAG_NR_NEU,"\
         "NL_MENGE_AKTUELL,"\
         "NL_MENGE_GELIEFER,"\
         "NL_MENGE_NEU,"\
         "UID,"\
         "USERBRANCHNO"

 #define NACHLIEFPROT_UPDLISTE \
         "ARTIKEL_NR=?,"\
         "IDFNR=?,"\
         "NL_MENGE_ALT=?,"\
         "AENDTYP=?,"\
         "POSTYP=?,"\
         "DATUM=?,"\
         "POSNR=?,"\
         "KDAUFTRAGNR=?,"\
         "ZEIT_NEU=?,"\
         "DATUM_NEU=?,"\
         "KDAUFTRAG_NR_NEU=?,"\
         "NL_MENGE_AKTUELL=?,"\
         "NL_MENGE_GELIEFER=?,"\
         "NL_MENGE_NEU=?,"\
         "UID=?,"\
         "USERBRANCHNO=?"

/* SqlMacros-Define of NACHLIEFPROT *******************************************/

 #define NACHLIEFPROT_ZEIGER(x) \
         :x->ARTIKEL_NR,\
         :x->IDFNR,\
         :x->NL_MENGE_ALT,\
         :x->AENDTYP,\
         :x->POSTYP,\
         :x->DATUM,\
         :x->POSNR,\
         :x->KDAUFTRAGNR,\
         :x->ZEIT_NEU,\
         :x->DATUM_NEU,\
         :x->KDAUFTRAG_NR_NEU,\
         :x->NL_MENGE_AKTUELL,\
         :x->NL_MENGE_GELIEFER,\
         :x->NL_MENGE_NEU,\
         :x->UID,\
         :x->USERBRANCHNO

 #define NACHLIEFPROT_ZEIGERSEL(x) \
         :x->ARTIKEL_NR,\
         :x->IDFNR,\
         :x->NL_MENGE_ALT,\
         :x->AENDTYP,\
         :x->POSTYP,\
         :x->DATUM,\
         :x->POSNR,\
         :x->KDAUFTRAGNR,\
         :x->ZEIT_NEU,\
         :x->DATUM_NEU,\
         :x->KDAUFTRAG_NR_NEU,\
         :x->NL_MENGE_AKTUELL,\
         :x->NL_MENGE_GELIEFER,\
         :x->NL_MENGE_NEU,\
         :x->UID,\
         :x->USERBRANCHNO

 #define NACHLIEFPROT_UPDATE(x) \
         NACHLIEFPROT.ARTIKEL_NR=:x->ARTIKEL_NR,\
         NACHLIEFPROT.IDFNR=:x->IDFNR,\
         NACHLIEFPROT.NL_MENGE_ALT=:x->NL_MENGE_ALT,\
         NACHLIEFPROT.AENDTYP=:x->AENDTYP,\
         NACHLIEFPROT.POSTYP=:x->POSTYP,\
         NACHLIEFPROT.DATUM=:x->DATUM,\
         NACHLIEFPROT.POSNR=:x->POSNR,\
         NACHLIEFPROT.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         NACHLIEFPROT.ZEIT_NEU=:x->ZEIT_NEU,\
         NACHLIEFPROT.DATUM_NEU=:x->DATUM_NEU,\
         NACHLIEFPROT.KDAUFTRAG_NR_NEU=:x->KDAUFTRAG_NR_NEU,\
         NACHLIEFPROT.NL_MENGE_AKTUELL=:x->NL_MENGE_AKTUELL,\
         NACHLIEFPROT.NL_MENGE_GELIEFER=:x->NL_MENGE_GELIEFER,\
         NACHLIEFPROT.NL_MENGE_NEU=:x->NL_MENGE_NEU,\
         NACHLIEFPROT.UID=:x->UID,\
         NACHLIEFPROT.USERBRANCHNO=:x->USERBRANCHNO

/* SqlMacros390-Define of NACHLIEFPROT ****************************************/

 #define NACHLIEFPROT_ZEIGER_390 \
         :ARTIKEL_NR,\
         :IDFNR,\
         :NL_MENGE_ALT,\
         :AENDTYP,\
         :POSTYP,\
         :DATUM,\
         :POSNR,\
         :KDAUFTRAGNR,\
         :ZEIT_NEU,\
         :DATUM_NEU,\
         :KDAUFTRAG_NR_NEU,\
         :NL_MENGE_AKTUELL,\
         :NL_MENGE_GELIEFER,\
         :NL_MENGE_NEU,\
         :UID,\
         :USERBRANCHNO

 #define NACHLIEFPROT_UPDATE_390 \
         ARTIKEL_NR=:ARTIKEL_NR,\
         IDFNR=:IDFNR,\
         NL_MENGE_ALT=:NL_MENGE_ALT,\
         AENDTYP=:AENDTYP,\
         POSTYP=:POSTYP,\
         DATUM=:DATUM,\
         POSNR=:POSNR,\
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         ZEIT_NEU=:ZEIT_NEU,\
         DATUM_NEU=:DATUM_NEU,\
         KDAUFTRAG_NR_NEU=:KDAUFTRAG_NR_NEU,\
         NL_MENGE_AKTUELL=:NL_MENGE_AKTUELL,\
         NL_MENGE_GELIEFER=:NL_MENGE_GELIEFER,\
         NL_MENGE_NEU=:NL_MENGE_NEU,\
         UID=:UID,\
         USERBRANCHNO=:USERBRANCHNO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of NACHLIEFPROT *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_NACHLIEFPROT {
         long ARTIKEL_NR;
         long IDFNR;
         long NL_MENGE_ALT;
         short AENDTYP;
         short POSTYP;
         long DATUM;
         long POSNR;
         long KDAUFTRAGNR;
         long ZEIT_NEU;
         long DATUM_NEU;
         long KDAUFTRAG_NR_NEU;
         long NL_MENGE_AKTUELL;
         long NL_MENGE_GELIEFER;
         long NL_MENGE_NEU;
         long UID;
         short USERBRANCHNO;
        } nachliefprotS;
 #else /*TRANSCLASS*/
 typedef struct N_NACHLIEFPROT {
         long ARTIKEL_NR;
         long IDFNR;
         long NL_MENGE_ALT;
         short AENDTYP;
         short POSTYP;
         long DATUM;
         long POSNR;
         long KDAUFTRAGNR;
         long ZEIT_NEU;
         long DATUM_NEU;
         long KDAUFTRAG_NR_NEU;
         long NL_MENGE_AKTUELL;
         long NL_MENGE_GELIEFER;
         long NL_MENGE_NEU;
         long UID;
         short USERBRANCHNO;

                        bool operator==(const N_NACHLIEFPROT& right) const {
                        return(
                                ARTIKEL_NR == right.ARTIKEL_NR &&
                                IDFNR == right.IDFNR &&
                                NL_MENGE_ALT == right.NL_MENGE_ALT &&
                                AENDTYP == right.AENDTYP &&
                                POSTYP == right.POSTYP &&
                                DATUM == right.DATUM &&
                                POSNR == right.POSNR &&
                                KDAUFTRAGNR == right.KDAUFTRAGNR &&
                                ZEIT_NEU == right.ZEIT_NEU &&
                                DATUM_NEU == right.DATUM_NEU &&
                                KDAUFTRAG_NR_NEU == right.KDAUFTRAG_NR_NEU &&
                                NL_MENGE_AKTUELL == right.NL_MENGE_AKTUELL &&
                                NL_MENGE_GELIEFER == right.NL_MENGE_GELIEFER &&
                                NL_MENGE_NEU == right.NL_MENGE_NEU &&
                                UID == right.UID &&
                                USERBRANCHNO == right.USERBRANCHNO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTIKEL_NR = 0;
                                IDFNR = 0;
                                NL_MENGE_ALT = 0;
                                AENDTYP = 0;
                                POSTYP = 0;
                                DATUM = 0;
                                POSNR = 0;
                                KDAUFTRAGNR = 0;
                                ZEIT_NEU = 0;
                                DATUM_NEU = 0;
                                KDAUFTRAG_NR_NEU = 0;
                                NL_MENGE_AKTUELL = 0;
                                NL_MENGE_GELIEFER = 0;
                                NL_MENGE_NEU = 0;
                                UID = 0;
                                USERBRANCHNO = 0;
#endif
                        }
         } nachliefprotS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of NACHLIEFPROT **************************************/

 struct S_NACHLIEFPROT {
         char ARTIKEL_NR[11];
         char IDFNR[11];
         char NL_MENGE_ALT[11];
         char AENDTYP[7];
         char POSTYP[7];
         char DATUM[11];
         char POSNR[11];
         char KDAUFTRAGNR[11];
         char ZEIT_NEU[11];
         char DATUM_NEU[11];
         char KDAUFTRAG_NR_NEU[11];
         char NL_MENGE_AKTUELL[11];
         char NL_MENGE_GELIEFER[11];
         char NL_MENGE_NEU[11];
         char UID[11];
         char USERBRANCHNO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of NACHLIEFPROT *********************/

 struct O_NACHLIEFPROT {
         char ARTIKEL_NR[11];
         char IDFNR[11];
         char NL_MENGE_ALT[11];
         char AENDTYP[7];
         char POSTYP[7];
         char DATUM[11];
         char POSNR[11];
         char KDAUFTRAGNR[11];
         char ZEIT_NEU[11];
         char DATUM_NEU[11];
         char KDAUFTRAG_NR_NEU[11];
         char NL_MENGE_AKTUELL[11];
         char NL_MENGE_GELIEFER[11];
         char NL_MENGE_NEU[11];
         char UID[11];
         char USERBRANCHNO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of NACHLIEFPROT ********************************/

 struct C_NACHLIEFPROT {
         long ARTIKEL_NR;
         long IDFNR;
         long NL_MENGE_ALT;
         short AENDTYP;
         short POSTYP;
         long DATUM;
         long POSNR;
         long KDAUFTRAGNR;
         long ZEIT_NEU;
         long DATUM_NEU;
         long KDAUFTRAG_NR_NEU;
         long NL_MENGE_AKTUELL;
         long NL_MENGE_GELIEFER;
         long NL_MENGE_NEU;
         long UID;
         short USERBRANCHNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of NACHLIEFPROT ******************************/

 struct I_NACHLIEFPROT {
         short ARTIKEL_NR;
         short IDFNR;
         short NL_MENGE_ALT;
         short AENDTYP;
         short POSTYP;
         short DATUM;
         short POSNR;
         short KDAUFTRAGNR;
         short ZEIT_NEU;
         short DATUM_NEU;
         short KDAUFTRAG_NR_NEU;
         short NL_MENGE_AKTUELL;
         short NL_MENGE_GELIEFER;
         short NL_MENGE_NEU;
         short UID;
         short USERBRANCHNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of NACHLIEFPROT ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc NACHLIEFPROT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc NACHLIEFPROT_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of NACHLIEFPROT **********************************/

 #define NACHLIEFPROT_S390 \
         long ARTIKEL_NR; \
         long IDFNR; \
         long NL_MENGE_ALT; \
         short AENDTYP; \
         short POSTYP; \
         long DATUM; \
         long POSNR; \
         long KDAUFTRAGNR; \
         long ZEIT_NEU; \
         long DATUM_NEU; \
         long KDAUFTRAG_NR_NEU; \
         long NL_MENGE_AKTUELL; \
         long NL_MENGE_GELIEFER; \
         long NL_MENGE_NEU; \
         long UID; \
         short USERBRANCHNO; \



/* Copy-Function Struct to single Data NACHLIEFPROT ***************************/

 #define NACHLIEFPROT_S390_COPY_TO_SINGLE(_x_) \
         ARTIKEL_NR=_x_->ARTIKEL_NR;\
         IDFNR=_x_->IDFNR;\
         NL_MENGE_ALT=_x_->NL_MENGE_ALT;\
         AENDTYP=_x_->AENDTYP;\
         POSTYP=_x_->POSTYP;\
         DATUM=_x_->DATUM;\
         POSNR=_x_->POSNR;\
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         ZEIT_NEU=_x_->ZEIT_NEU;\
         DATUM_NEU=_x_->DATUM_NEU;\
         KDAUFTRAG_NR_NEU=_x_->KDAUFTRAG_NR_NEU;\
         NL_MENGE_AKTUELL=_x_->NL_MENGE_AKTUELL;\
         NL_MENGE_GELIEFER=_x_->NL_MENGE_GELIEFER;\
         NL_MENGE_NEU=_x_->NL_MENGE_NEU;\
         UID=_x_->UID;\
         USERBRANCHNO=_x_->USERBRANCHNO;\

 #define NACHLIEFPROT_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTIKEL_NR=ARTIKEL_NR;\
          _x_->IDFNR=IDFNR;\
          _x_->NL_MENGE_ALT=NL_MENGE_ALT;\
          _x_->AENDTYP=AENDTYP;\
          _x_->POSTYP=POSTYP;\
          _x_->DATUM=DATUM;\
          _x_->POSNR=POSNR;\
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->ZEIT_NEU=ZEIT_NEU;\
          _x_->DATUM_NEU=DATUM_NEU;\
          _x_->KDAUFTRAG_NR_NEU=KDAUFTRAG_NR_NEU;\
          _x_->NL_MENGE_AKTUELL=NL_MENGE_AKTUELL;\
          _x_->NL_MENGE_GELIEFER=NL_MENGE_GELIEFER;\
          _x_->NL_MENGE_NEU=NL_MENGE_NEU;\
          _x_->UID=UID;\
          _x_->USERBRANCHNO=USERBRANCHNO;\



/* FunctionNumber-Define of nachliefprot **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of nachliefprot **********************************/


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

class CNACHLIEFPROT : public ppDadeVirtual
{
        //data members
        public:
                nachliefprotS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<nachliefprotS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<nachliefprotS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<nachliefprotS>; Strip(s); nachliefprotS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<nachliefprotS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<nachliefprotS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<nachliefprotS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArtikel_nr() const   { return s.ARTIKEL_NR; }
                long            GetIdfnr() const        { return s.IDFNR; }
                long            GetNl_menge_alt() const { return s.NL_MENGE_ALT; }
                short           GetAendtyp() const      { return s.AENDTYP; }
                short           GetPostyp() const       { return s.POSTYP; }
                long            GetDatum() const        { return s.DATUM; }
                long            GetPosnr() const        { return s.POSNR; }
                long            GetKdauftragnr() const  { return s.KDAUFTRAGNR; }
                long            GetZeit_neu() const     { return s.ZEIT_NEU; }
                long            GetDatum_neu() const    { return s.DATUM_NEU; }
                long            GetKdauftrag_nr_neu() const     { return s.KDAUFTRAG_NR_NEU; }
                long            GetNl_menge_aktuell() const     { return s.NL_MENGE_AKTUELL; }
                long            GetNl_menge_geliefer() const    { return s.NL_MENGE_GELIEFER; }
                long            GetNl_menge_neu() const { return s.NL_MENGE_NEU; }
                long            GetUid() const  { return s.UID; }
                short           GetUserbranchno() const { return s.USERBRANCHNO; }
                const nachliefprotS& GetStruct() const { return s; }
                void            SetArtikel_nr(long t) { s.ARTIKEL_NR = t; }
                void            SetIdfnr(long t) { s.IDFNR = t; }
                void            SetNl_menge_alt(long t) { s.NL_MENGE_ALT = t; }
                void            SetAendtyp(short t) { s.AENDTYP = t; }
                void            SetPostyp(short t) { s.POSTYP = t; }
                void            SetDatum(long t) { s.DATUM = t; }
                void            SetPosnr(long t) { s.POSNR = t; }
                void            SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
                void            SetZeit_neu(long t) { s.ZEIT_NEU = t; }
                void            SetDatum_neu(long t) { s.DATUM_NEU = t; }
                void            SetKdauftrag_nr_neu(long t) { s.KDAUFTRAG_NR_NEU = t; }
                void            SetNl_menge_aktuell(long t) { s.NL_MENGE_AKTUELL = t; }
                void            SetNl_menge_geliefer(long t) { s.NL_MENGE_GELIEFER = t; }
                void            SetNl_menge_neu(long t) { s.NL_MENGE_NEU = t; }
                void            SetUid(long t) { s.UID = t; }
                void            SetUserbranchno(short t) { s.USERBRANCHNO = t; }
                void            SetStruct(const nachliefprotS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CNACHLIEFPROT()  //constructor
                {
                        ::buf_default((void *)&s, NACHLIEFPROT_BES, NACHLIEFPROT_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CNACHLIEFPROT()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, NACHLIEFPROT_BES, NACHLIEFPROT_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, NACHLIEFPROT_BES, NACHLIEFPROT_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, NACHLIEFPROT_BES, NACHLIEFPROT_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_NACHLIEFPROT& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, NACHLIEFPROT_BES, NACHLIEFPROT_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of NACHLIEFPROT *****************************************/

 #define NACHLIEFPROT_CREATE(x) exec sql create table x (\
         ARTIKEL_NR integer default 0 not null,\
         IDFNR integer default 0 not null,\
         NL_MENGE_ALT integer default 0 not null,\
         AENDTYP smallint default 0 not null,\
         POSTYP smallint default 0 not null,\
         DATUM integer default 0 not null,\
         POSNR integer default 0 not null,\
         KDAUFTRAGNR integer default 0 not null,\
         ZEIT_NEU integer default 0 not null,\
         DATUM_NEU integer default 0 not null,\
         KDAUFTRAG_NR_NEU integer default 0 not null,\
         NL_MENGE_AKTUELL integer default 0 not null,\
         NL_MENGE_GELIEFER integer default 0 not null,\
         NL_MENGE_NEU integer default 0 not null,\
         UID integer default 0 not null,\
         USERBRANCHNO smallint default 0 not null) in ksc extent size 1568 next size 160 lock mode row;



/* CreateIndexStatement of NACHLIEFPROT ***************************************/

 #define NACHLIEFPROT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_nachlieferprot_i on _X_(\
              artikel_nr,\
              idfnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of NACHLIEFPROT ***************************************/

 #define NACHLIEFPROT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_nachlieferprot_i;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

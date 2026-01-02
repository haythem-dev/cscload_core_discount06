#ifndef __PP_KDAUFTRAGINFO_H_
#define __PP_KDAUFTRAGINFO_H_

/******************************************************************************/
/* v:\nordat\kdauftraginfo ****************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGINFO *********************************************/

  #define L_KDAUFTRAGINFO_KDAUFTRAGNR 11
  #define L_KDAUFTRAGINFO_KDAUFTRAGBESTELLNR 9
  #define L_KDAUFTRAGINFO_IDFNRINTERN 11
  #define L_KDAUFTRAGINFO_APOTOURID 10
  #define L_KDAUFTRAGINFO_VERSANDART 2
  #define L_KDAUFTRAGINFO_PROCESSNR 11
  #define L_KDAUFTRAGINFO_EDILIEFERSCHEIN 1
  #define L_KDAUFTRAGINFO_BATCHAUFTRAGNR 11

/* Length/Count-Define of KDAUFTRAGINFO ***************************************/

  #define LS_KDAUFTRAGINFO_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGINFO_KDAUFTRAGBESTELLNR 9 + 1
  #define LS_KDAUFTRAGINFO_IDFNRINTERN 10 + 1
  #define LS_KDAUFTRAGINFO_APOTOURID 10 + 1
  #define LS_KDAUFTRAGINFO_VERSANDART 2 + 1
  #define LS_KDAUFTRAGINFO_PROCESSNR 10 + 1
  #define LS_KDAUFTRAGINFO_EDILIEFERSCHEIN 1 + 1
  #define LS_KDAUFTRAGINFO_BATCHAUFTRAGNR 10 + 1

  #define KDAUFTRAGINFOKDAUFTRAGNR 0
  #define KDAUFTRAGINFOKDAUFTRAGBESTELLNR 1
  #define KDAUFTRAGINFOIDFNRINTERN 2
  #define KDAUFTRAGINFOAPOTOURID 3
  #define KDAUFTRAGINFOVERSANDART 4
  #define KDAUFTRAGINFOPROCESSNR 5
  #define KDAUFTRAGINFOEDILIEFERSCHEIN 6
  #define KDAUFTRAGINFOBATCHAUFTRAGNR 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGINFO_H
 #define KDAUFTRAGINFO_ANZ ( sizeof(KDAUFTRAGINFO_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGINFO *************************************************/

 #define KDAUFTRAGINFO_LISTE \
         KDAUFTRAGINFO.KDAUFTRAGNR,\
         KDAUFTRAGINFO.KDAUFTRAGBESTELLNR,\
         KDAUFTRAGINFO.IDFNRINTERN,\
         KDAUFTRAGINFO.APOTOURID,\
         KDAUFTRAGINFO.VERSANDART,\
         KDAUFTRAGINFO.PROCESSNR,\
         KDAUFTRAGINFO.EDILIEFERSCHEIN,\
         KDAUFTRAGINFO.BATCHAUFTRAGNR

 #define KDAUFTRAGINFO_LISTE_390 \
         KDAUFTRAGNR,\
         KDAUFTRAGBESTELLNR,\
         IDFNRINTERN,\
         APOTOURID,\
         VERSANDART,\
         PROCESSNR,\
         EDILIEFERSCHEIN,\
         BATCHAUFTRAGNR

 #define KDAUFTRAGINFO_PLISTE \
         "KDAUFTRAGINFO.KDAUFTRAGNR,"\
         "KDAUFTRAGINFO.KDAUFTRAGBESTELLNR,"\
         "KDAUFTRAGINFO.IDFNRINTERN,"\
         "KDAUFTRAGINFO.APOTOURID,"\
         "KDAUFTRAGINFO.VERSANDART,"\
         "KDAUFTRAGINFO.PROCESSNR,"\
         "KDAUFTRAGINFO.EDILIEFERSCHEIN,"\
         "KDAUFTRAGINFO.BATCHAUFTRAGNR"

 #define KDAUFTRAGINFO_PELISTE \
         "KDAUFTRAGNR,"\
         "KDAUFTRAGBESTELLNR,"\
         "IDFNRINTERN,"\
         "APOTOURID,"\
         "VERSANDART,"\
         "PROCESSNR,"\
         "EDILIEFERSCHEIN,"\
         "BATCHAUFTRAGNR"

 #define KDAUFTRAGINFO_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "KDAUFTRAGBESTELLNR=?,"\
         "IDFNRINTERN=?,"\
         "APOTOURID=?,"\
         "VERSANDART=?,"\
         "PROCESSNR=?,"\
         "EDILIEFERSCHEIN=?,"\
         "BATCHAUFTRAGNR=?"

/* SqlMacros-Define of KDAUFTRAGINFO ******************************************/

 #define KDAUFTRAGINFO_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->KDAUFTRAGBESTELLNR,\
         :x->IDFNRINTERN,\
         :x->APOTOURID,\
         :x->VERSANDART,\
         :x->PROCESSNR,\
         :x->EDILIEFERSCHEIN,\
         :x->BATCHAUFTRAGNR

 #define KDAUFTRAGINFO_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->KDAUFTRAGBESTELLNR,\
         :x->IDFNRINTERN,\
         :x->APOTOURID,\
         :x->VERSANDART,\
         :x->PROCESSNR,\
         :x->EDILIEFERSCHEIN,\
         :x->BATCHAUFTRAGNR

 #define KDAUFTRAGINFO_UPDATE(x) \
         KDAUFTRAGINFO.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGINFO.KDAUFTRAGBESTELLNR=:x->KDAUFTRAGBESTELLNR,\
         KDAUFTRAGINFO.IDFNRINTERN=:x->IDFNRINTERN,\
         KDAUFTRAGINFO.APOTOURID=:x->APOTOURID,\
         KDAUFTRAGINFO.VERSANDART=:x->VERSANDART,\
         KDAUFTRAGINFO.PROCESSNR=:x->PROCESSNR,\
         KDAUFTRAGINFO.EDILIEFERSCHEIN=:x->EDILIEFERSCHEIN,\
         KDAUFTRAGINFO.BATCHAUFTRAGNR=:x->BATCHAUFTRAGNR

/* SqlMacros390-Define of KDAUFTRAGINFO ***************************************/

 #define KDAUFTRAGINFO_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :KDAUFTRAGBESTELLNR,\
         :IDFNRINTERN,\
         :APOTOURID,\
         :VERSANDART,\
         :PROCESSNR,\
         :EDILIEFERSCHEIN,\
         :BATCHAUFTRAGNR

 #define KDAUFTRAGINFO_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         KDAUFTRAGBESTELLNR=:KDAUFTRAGBESTELLNR,\
         IDFNRINTERN=:IDFNRINTERN,\
         APOTOURID=:APOTOURID,\
         VERSANDART=:VERSANDART,\
         PROCESSNR=:PROCESSNR,\
         EDILIEFERSCHEIN=:EDILIEFERSCHEIN,\
         BATCHAUFTRAGNR=:BATCHAUFTRAGNR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGINFO ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGINFO {
         long KDAUFTRAGNR;
         char KDAUFTRAGBESTELLNR[10];
         long IDFNRINTERN;
         char APOTOURID[11];
         char VERSANDART[3];
         long PROCESSNR;
         char EDILIEFERSCHEIN[2];
         long BATCHAUFTRAGNR;
        } kdauftraginfoS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGINFO {
         long KDAUFTRAGNR;
         char KDAUFTRAGBESTELLNR[10];
         long IDFNRINTERN;
         char APOTOURID[11];
         char VERSANDART[3];
         long PROCESSNR;
         char EDILIEFERSCHEIN[2];
         long BATCHAUFTRAGNR;

                        bool operator==(const N_KDAUFTRAGINFO& right) const {
                        return(
                                KDAUFTRAGNR == right.KDAUFTRAGNR &&
                                !strcmp(KDAUFTRAGBESTELLNR, right.KDAUFTRAGBESTELLNR) &&
                                IDFNRINTERN == right.IDFNRINTERN &&
                                !strcmp(APOTOURID, right.APOTOURID) &&
                                !strcmp(VERSANDART, right.VERSANDART) &&
                                PROCESSNR == right.PROCESSNR &&
                                !strcmp(EDILIEFERSCHEIN, right.EDILIEFERSCHEIN) &&
                                BATCHAUFTRAGNR == right.BATCHAUFTRAGNR
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                KDAUFTRAGNR = 0;
                                strcpy(KDAUFTRAGBESTELLNR, " " );
                                IDFNRINTERN = 0;
                                strcpy(APOTOURID, " " );
                                strcpy(VERSANDART, " " );
                                PROCESSNR = 0;
                                strcpy(EDILIEFERSCHEIN, " " );
                                BATCHAUFTRAGNR = 0;
#endif
                        }
         } kdauftraginfoS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGINFO *************************************/

 struct S_KDAUFTRAGINFO {
         char KDAUFTRAGNR[11];
         char KDAUFTRAGBESTELLNR[9 + 1];
         char IDFNRINTERN[11];
         char APOTOURID[10 + 1];
         char VERSANDART[2 + 1];
         char PROCESSNR[11];
         char EDILIEFERSCHEIN[1 + 1];
         char BATCHAUFTRAGNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGINFO ********************/

 struct O_KDAUFTRAGINFO {
         char KDAUFTRAGNR[11];
         char KDAUFTRAGBESTELLNR[9];
         char IDFNRINTERN[11];
         char APOTOURID[10];
         char VERSANDART[2];
         char PROCESSNR[11];
         char EDILIEFERSCHEIN[1];
         char BATCHAUFTRAGNR[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGINFO *******************************/

 struct C_KDAUFTRAGINFO {
         long KDAUFTRAGNR;
         char KDAUFTRAGBESTELLNR[10];
         long IDFNRINTERN;
         char APOTOURID[11];
         char VERSANDART[3];
         long PROCESSNR;
         char EDILIEFERSCHEIN;
         long BATCHAUFTRAGNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGINFO *****************************/

 struct I_KDAUFTRAGINFO {
         short KDAUFTRAGNR;
         short KDAUFTRAGBESTELLNR;
         short IDFNRINTERN;
         short APOTOURID;
         short VERSANDART;
         short PROCESSNR;
         short EDILIEFERSCHEIN;
         short BATCHAUFTRAGNR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGINFO ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGINFO_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 9, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGINFO_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_C, 9, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 10, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGINFO *********************************/

 #define KDAUFTRAGINFO_S390 \
         long KDAUFTRAGNR; \
         char KDAUFTRAGBESTELLNR[10]; \
         long IDFNRINTERN; \
         char APOTOURID[11]; \
         char VERSANDART[3]; \
         long PROCESSNR; \
         char EDILIEFERSCHEIN; \
         long BATCHAUFTRAGNR; \



/* Copy-Function Struct to single Data KDAUFTRAGINFO **************************/

 #define KDAUFTRAGINFO_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
          strcpy(KDAUFTRAGBESTELLNR,_x_->KDAUFTRAGBESTELLNR);\
         IDFNRINTERN=_x_->IDFNRINTERN;\
          strcpy(APOTOURID,_x_->APOTOURID);\
          strcpy(VERSANDART,_x_->VERSANDART);\
         PROCESSNR=_x_->PROCESSNR;\
         EDILIEFERSCHEIN=_x_->EDILIEFERSCHEIN;\
         BATCHAUFTRAGNR=_x_->BATCHAUFTRAGNR;\

 #define KDAUFTRAGINFO_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          strcpy(_x_->KDAUFTRAGBESTELLNR,KDAUFTRAGBESTELLNR);\
          _x_->IDFNRINTERN=IDFNRINTERN;\
          strcpy(_x_->APOTOURID,APOTOURID);\
          strcpy(_x_->VERSANDART,VERSANDART);\
          _x_->PROCESSNR=PROCESSNR;\
          _x_->EDILIEFERSCHEIN=EDILIEFERSCHEIN;\
          _x_->BATCHAUFTRAGNR=BATCHAUFTRAGNR;\



/* FunctionNumber-Define of kdauftraginfo *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftraginfo *********************************/


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

class CKDAUFTRAGINFO : public ppDadeVirtual
{
        //data members
        public:
                kdauftraginfoS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<kdauftraginfoS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftraginfoS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<kdauftraginfoS>; Strip(s); kdauftraginfoS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftraginfoS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<kdauftraginfoS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<kdauftraginfoS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetKdauftragnr() const  { return s.KDAUFTRAGNR; }
                const char*     GetKdauftragbestellnr(ppString& t) const        { t = s.KDAUFTRAGBESTELLNR; t.erasespace(ppString::END); return t.c_str(); }
                long            GetIdfnrintern() const  { return s.IDFNRINTERN; }
                const char*     GetApotourid(ppString& t) const         { t = s.APOTOURID; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetVersandart(ppString& t) const        { t = s.VERSANDART; t.erasespace(ppString::END); return t.c_str(); }
                long            GetProcessnr() const    { return s.PROCESSNR; }
                char            GetEdilieferschein() const      { return s.EDILIEFERSCHEIN[0]; }
                long            GetBatchauftragnr() const       { return s.BATCHAUFTRAGNR; }
                const kdauftraginfoS& GetStruct() const { return s; }
                void            SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
                void            SetKdauftragbestellnr(const ppString& t) { ppGStrCopy(s.KDAUFTRAGBESTELLNR,t.c_str() ,L_KDAUFTRAGINFO_KDAUFTRAGBESTELLNR); }
                void            SetIdfnrintern(long t) { s.IDFNRINTERN = t; }
                void            SetApotourid(const ppString& t) { ppGStrCopy(s.APOTOURID,t.c_str() ,L_KDAUFTRAGINFO_APOTOURID); }
                void            SetVersandart(const ppString& t) { ppGStrCopy(s.VERSANDART,t.c_str() ,L_KDAUFTRAGINFO_VERSANDART); }
                void            SetProcessnr(long t) { s.PROCESSNR = t; }
                void            SetEdilieferschein(char t) { s.EDILIEFERSCHEIN[0] = t; s.EDILIEFERSCHEIN[1] = '\0';}
                void            SetBatchauftragnr(long t) { s.BATCHAUFTRAGNR = t; }
                void            SetStruct(const kdauftraginfoS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CKDAUFTRAGINFO()  //constructor
                {
                        ::buf_default((void *)&s, KDAUFTRAGINFO_BES, KDAUFTRAGINFO_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CKDAUFTRAGINFO()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, KDAUFTRAGINFO_BES, KDAUFTRAGINFO_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGINFO_BES, KDAUFTRAGINFO_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGINFO_BES, KDAUFTRAGINFO_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_KDAUFTRAGINFO& d)
                {
#ifdef WIN32
                        ppGStripLast(d.KDAUFTRAGBESTELLNR);
                        ppGStripLast(d.APOTOURID);
                        ppGStripLast(d.VERSANDART);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGINFO_BES, KDAUFTRAGINFO_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of KDAUFTRAGINFO ****************************************/

 #define KDAUFTRAGINFO_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         KDAUFTRAGBESTELLNR char(9) default " " not null,\
         IDFNRINTERN integer default 0 not null,\
         APOTOURID char(10) default " " not null,\
         VERSANDART char(2) default " " not null,\
         PROCESSNR integer default 0 not null,\
         EDILIEFERSCHEIN char(1) default " " not null,\
         BATCHAUFTRAGNR integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of KDAUFTRAGINFO **************************************/

 #define KDAUFTRAGINFO_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index I_kdaufinf_1 on _X_(\
              kdauftragnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGINFO **************************************/

 #define KDAUFTRAGINFO_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index I_kdaufinf_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

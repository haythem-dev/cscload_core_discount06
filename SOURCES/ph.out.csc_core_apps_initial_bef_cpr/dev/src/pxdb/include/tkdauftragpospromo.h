#ifndef __PP_KDAUFTRAGPOSPROMO_H_
#define __PP_KDAUFTRAGPOSPROMO_H_

/******************************************************************************/
/* u:\kdauftragpospromo *******************************************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGPOSPROMO *****************************************/

  #define L_KDAUFTRAGPOSPROMO_KDAUFTRAGNR 11
  #define L_KDAUFTRAGPOSPROMO_POSNR 11
  #define L_KDAUFTRAGPOSPROMO_DISCOUNTGRPNO 11
  #define L_KDAUFTRAGPOSPROMO_PHARMACYGROUPID 3
  #define L_KDAUFTRAGPOSPROMO_BASEQTY 11
  #define L_KDAUFTRAGPOSPROMO_BASE_VALUE 10
  #define N_KDAUFTRAGPOSPROMO_BASE_VALUE 2
  #define L_KDAUFTRAGPOSPROMO_CUSTOMERNO 11
  #define L_KDAUFTRAGPOSPROMO_PROMOTION_NO 6
  #define L_KDAUFTRAGPOSPROMO_INTERNALDISCOUNT 1
  #define L_KDAUFTRAGPOSPROMO_DISCOUNTVALUEPCT 5
  #define N_KDAUFTRAGPOSPROMO_DISCOUNTVALUEPCT 2

/* Length/Count-Define of KDAUFTRAGPOSPROMO ***********************************/

  #define LS_KDAUFTRAGPOSPROMO_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGPOSPROMO_POSNR 10 + 1
  #define LS_KDAUFTRAGPOSPROMO_DISCOUNTGRPNO 10 + 1
  #define LS_KDAUFTRAGPOSPROMO_PHARMACYGROUPID 3 + 1
  #define LS_KDAUFTRAGPOSPROMO_BASEQTY 10 + 1
  #define LS_KDAUFTRAGPOSPROMO_BASE_VALUE 10 + 2
  #define LS_KDAUFTRAGPOSPROMO_CUSTOMERNO 10 + 1
  #define LS_KDAUFTRAGPOSPROMO_PROMOTION_NO 5 + 1
  #define LS_KDAUFTRAGPOSPROMO_INTERNALDISCOUNT 1 + 1
  #define LS_KDAUFTRAGPOSPROMO_DISCOUNTVALUEPCT 5 + 2

  #define KDAUFTRAGPOSPROMOKDAUFTRAGNR 0
  #define KDAUFTRAGPOSPROMOPOSNR 1
  #define KDAUFTRAGPOSPROMODISCOUNTGRPNO 2
  #define KDAUFTRAGPOSPROMOPHARMACYGROUPID 3
  #define KDAUFTRAGPOSPROMOBASEQTY 4
  #define KDAUFTRAGPOSPROMOBASE_VALUE 5
  #define KDAUFTRAGPOSPROMOCUSTOMERNO 6
  #define KDAUFTRAGPOSPROMOPROMOTION_NO 7
  #define KDAUFTRAGPOSPROMOINTERNALDISCOUNT 8
  #define KDAUFTRAGPOSPROMODISCOUNTVALUEPCT 9

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGPOSPROMO_H
 #define KDAUFTRAGPOSPROMO_ANZ ( sizeof(KDAUFTRAGPOSPROMO_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGPOSPROMO *********************************************/

 #define KDAUFTRAGPOSPROMO_LISTE \
         KDAUFTRAGPOSPROMO.KDAUFTRAGNR,\
         KDAUFTRAGPOSPROMO.POSNR,\
         KDAUFTRAGPOSPROMO.DISCOUNTGRPNO,\
         KDAUFTRAGPOSPROMO.PHARMACYGROUPID,\
         KDAUFTRAGPOSPROMO.BASEQTY,\
         KDAUFTRAGPOSPROMO.BASE_VALUE,\
         KDAUFTRAGPOSPROMO.CUSTOMERNO,\
         KDAUFTRAGPOSPROMO.PROMOTION_NO,\
         KDAUFTRAGPOSPROMO.INTERNALDISCOUNT,\
         KDAUFTRAGPOSPROMO.DISCOUNTVALUEPCT

 #define KDAUFTRAGPOSPROMO_LISTE_390 \
         KDAUFTRAGNR,\
         POSNR,\
         DISCOUNTGRPNO,\
         PHARMACYGROUPID,\
         BASEQTY,\
         BASE_VALUE,\
         CUSTOMERNO,\
         PROMOTION_NO,\
         INTERNALDISCOUNT,\
         DISCOUNTVALUEPCT

 #define KDAUFTRAGPOSPROMO_PLISTE \
         "KDAUFTRAGPOSPROMO.KDAUFTRAGNR,"\
         "KDAUFTRAGPOSPROMO.POSNR,"\
         "KDAUFTRAGPOSPROMO.DISCOUNTGRPNO,"\
         "KDAUFTRAGPOSPROMO.PHARMACYGROUPID,"\
         "KDAUFTRAGPOSPROMO.BASEQTY,"\
         "KDAUFTRAGPOSPROMO.BASE_VALUE,"\
         "KDAUFTRAGPOSPROMO.CUSTOMERNO,"\
         "KDAUFTRAGPOSPROMO.PROMOTION_NO,"\
         "KDAUFTRAGPOSPROMO.INTERNALDISCOUNT,"\
         "KDAUFTRAGPOSPROMO.DISCOUNTVALUEPCT"

 #define KDAUFTRAGPOSPROMO_PELISTE \
         "KDAUFTRAGNR,"\
         "POSNR,"\
         "DISCOUNTGRPNO,"\
         "PHARMACYGROUPID,"\
         "BASEQTY,"\
         "BASE_VALUE,"\
         "CUSTOMERNO,"\
         "PROMOTION_NO,"\
         "INTERNALDISCOUNT,"\
         "DISCOUNTVALUEPCT"

 #define KDAUFTRAGPOSPROMO_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "POSNR=?,"\
         "DISCOUNTGRPNO=?,"\
         "PHARMACYGROUPID=?,"\
         "BASEQTY=?,"\
         "BASE_VALUE=?,"\
         "CUSTOMERNO=?,"\
         "PROMOTION_NO=?,"\
         "INTERNALDISCOUNT=?,"\
         "DISCOUNTVALUEPCT=?"

/* SqlMacros-Define of KDAUFTRAGPOSPROMO **************************************/

 #define KDAUFTRAGPOSPROMO_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->DISCOUNTGRPNO,\
         :x->PHARMACYGROUPID,\
         :x->BASEQTY,\
         :x->BASE_VALUE,\
         :x->CUSTOMERNO,\
         :x->PROMOTION_NO,\
         :x->INTERNALDISCOUNT,\
         :x->DISCOUNTVALUEPCT

 #define KDAUFTRAGPOSPROMO_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->POSNR,\
         :x->DISCOUNTGRPNO,\
         :x->PHARMACYGROUPID,\
         :x->BASEQTY,\
         :x->BASE_VALUE,\
         :x->CUSTOMERNO,\
         :x->PROMOTION_NO,\
         :x->INTERNALDISCOUNT,\
         :x->DISCOUNTVALUEPCT

 #define KDAUFTRAGPOSPROMO_UPDATE(x) \
         KDAUFTRAGPOSPROMO.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGPOSPROMO.POSNR=:x->POSNR,\
         KDAUFTRAGPOSPROMO.DISCOUNTGRPNO=:x->DISCOUNTGRPNO,\
         KDAUFTRAGPOSPROMO.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         KDAUFTRAGPOSPROMO.BASEQTY=:x->BASEQTY,\
         KDAUFTRAGPOSPROMO.BASE_VALUE=:x->BASE_VALUE,\
         KDAUFTRAGPOSPROMO.CUSTOMERNO=:x->CUSTOMERNO,\
         KDAUFTRAGPOSPROMO.PROMOTION_NO=:x->PROMOTION_NO,\
         KDAUFTRAGPOSPROMO.INTERNALDISCOUNT=:x->INTERNALDISCOUNT,\
         KDAUFTRAGPOSPROMO.DISCOUNTVALUEPCT=:x->DISCOUNTVALUEPCT

/* SqlMacros390-Define of KDAUFTRAGPOSPROMO ***********************************/

 #define KDAUFTRAGPOSPROMO_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :POSNR,\
         :DISCOUNTGRPNO,\
         :PHARMACYGROUPID,\
         :BASEQTY,\
         :BASE_VALUE,\
         :CUSTOMERNO,\
         :PROMOTION_NO,\
         :INTERNALDISCOUNT,\
         :DISCOUNTVALUEPCT

 #define KDAUFTRAGPOSPROMO_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         POSNR=:POSNR,\
         DISCOUNTGRPNO=:DISCOUNTGRPNO,\
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         BASEQTY=:BASEQTY,\
         BASE_VALUE=:BASE_VALUE,\
         CUSTOMERNO=:CUSTOMERNO,\
         PROMOTION_NO=:PROMOTION_NO,\
         INTERNALDISCOUNT=:INTERNALDISCOUNT,\
         DISCOUNTVALUEPCT=:DISCOUNTVALUEPCT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGPOSPROMO **************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGPOSPROMO {
         long KDAUFTRAGNR;
         long POSNR;
         long DISCOUNTGRPNO;
         char PHARMACYGROUPID[4];
         long BASEQTY;
         double BASE_VALUE;
         long CUSTOMERNO;
         short PROMOTION_NO;
         char INTERNALDISCOUNT[2];
         double DISCOUNTVALUEPCT;
        } kdauftragpospromoS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGPOSPROMO {
         long KDAUFTRAGNR;
         long POSNR;
         long DISCOUNTGRPNO;
         char PHARMACYGROUPID[4];
         long BASEQTY;
         double BASE_VALUE;
         long CUSTOMERNO;
         short PROMOTION_NO;
         char INTERNALDISCOUNT[2];
         double DISCOUNTVALUEPCT;

                        bool operator==(const N_KDAUFTRAGPOSPROMO& right) const {
                        return(
                                KDAUFTRAGNR == right.KDAUFTRAGNR &&
                                POSNR == right.POSNR &&
                                DISCOUNTGRPNO == right.DISCOUNTGRPNO &&
                                !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
                                BASEQTY == right.BASEQTY &&
                                BASE_VALUE == right.BASE_VALUE &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                PROMOTION_NO == right.PROMOTION_NO &&
                                !strcmp(INTERNALDISCOUNT, right.INTERNALDISCOUNT) &&
                                DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                KDAUFTRAGNR = 0;
                                POSNR = 0;
                                DISCOUNTGRPNO = 0;
                                strcpy(PHARMACYGROUPID, " " );
                                BASEQTY = 0;
                                BASE_VALUE = 0;
                                CUSTOMERNO = 0;
                                PROMOTION_NO = 0;
                                strcpy(INTERNALDISCOUNT, " " );
                                DISCOUNTVALUEPCT = 0;
#endif
                        }
         } kdauftragpospromoS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGPOSPROMO *********************************/

 struct S_KDAUFTRAGPOSPROMO {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char DISCOUNTGRPNO[11];
         char PHARMACYGROUPID[3 + 1];
         char BASEQTY[11];
         char BASE_VALUE[10 + 2];
         char CUSTOMERNO[11];
         char PROMOTION_NO[7];
         char INTERNALDISCOUNT[1 + 1];
         char DISCOUNTVALUEPCT[5 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGPOSPROMO ****************/

 struct O_KDAUFTRAGPOSPROMO {
         char KDAUFTRAGNR[11];
         char POSNR[11];
         char DISCOUNTGRPNO[11];
         char PHARMACYGROUPID[3];
         char BASEQTY[11];
         char BASE_VALUE[10];
         char CUSTOMERNO[11];
         char PROMOTION_NO[7];
         char INTERNALDISCOUNT[1];
         char DISCOUNTVALUEPCT[5];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of KDAUFTRAGPOSPROMO ***************************/

 struct C_KDAUFTRAGPOSPROMO {
         long KDAUFTRAGNR;
         long POSNR;
         long DISCOUNTGRPNO;
         char PHARMACYGROUPID[4];
         long BASEQTY;
         double BASE_VALUE;
         long CUSTOMERNO;
         short PROMOTION_NO;
         char INTERNALDISCOUNT;
         double DISCOUNTVALUEPCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of KDAUFTRAGPOSPROMO *************************/

 struct I_KDAUFTRAGPOSPROMO {
         short KDAUFTRAGNR;
         short POSNR;
         short DISCOUNTGRPNO;
         short PHARMACYGROUPID;
         short BASEQTY;
         short BASE_VALUE;
         short CUSTOMERNO;
         short PROMOTION_NO;
         short INTERNALDISCOUNT;
         short DISCOUNTVALUEPCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGPOSPROMO ***********************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSPROMO_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 10, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGPOSPROMO_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 10, 2 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 5, 2 },
 };
#endif

/* description for datatypes of KDAUFTRAGPOSPROMO *****************************/

 #define KDAUFTRAGPOSPROMO_S390 \
         long KDAUFTRAGNR; \
         long POSNR; \
         long DISCOUNTGRPNO; \
         char PHARMACYGROUPID[4]; \
         long BASEQTY; \
         double BASE_VALUE; \
         long CUSTOMERNO; \
         short PROMOTION_NO; \
         char INTERNALDISCOUNT; \
         double DISCOUNTVALUEPCT; \



/* Copy-Function Struct to single Data KDAUFTRAGPOSPROMO **********************/

 #define KDAUFTRAGPOSPROMO_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         POSNR=_x_->POSNR;\
         DISCOUNTGRPNO=_x_->DISCOUNTGRPNO;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         BASEQTY=_x_->BASEQTY;\
         BASE_VALUE=_x_->BASE_VALUE;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         PROMOTION_NO=_x_->PROMOTION_NO;\
         INTERNALDISCOUNT=_x_->INTERNALDISCOUNT;\
         DISCOUNTVALUEPCT=_x_->DISCOUNTVALUEPCT;\

 #define KDAUFTRAGPOSPROMO_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->POSNR=POSNR;\
          _x_->DISCOUNTGRPNO=DISCOUNTGRPNO;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->BASEQTY=BASEQTY;\
          _x_->BASE_VALUE=BASE_VALUE;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->PROMOTION_NO=PROMOTION_NO;\
          _x_->INTERNALDISCOUNT=INTERNALDISCOUNT;\
          _x_->DISCOUNTVALUEPCT=DISCOUNTVALUEPCT;\



/* FunctionNumber-Define of kdauftragpospromo *********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragpospromo *****************************/


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

class CKDAUFTRAGPOSPROMO : public ppDadeVirtual
{
        //data members
        public:
                kdauftragpospromoS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<kdauftragpospromoS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragpospromoS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<kdauftragpospromoS>; Strip(s); kdauftragpospromoS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragpospromoS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<kdauftragpospromoS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<kdauftragpospromoS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetKdauftragnr() const  { return s.KDAUFTRAGNR; }
                long            GetPosnr() const        { return s.POSNR; }
                long            GetDiscountgrpno() const        { return s.DISCOUNTGRPNO; }
                const char*     GetPharmacygroupid(ppString& t) const   { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
                long            GetBaseqty() const      { return s.BASEQTY; }
                double          GetBase_value() const   { return s.BASE_VALUE; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                short           GetPromotion_no() const { return s.PROMOTION_NO; }
                char            GetInternaldiscount() const     { return s.INTERNALDISCOUNT[0]; }
                double          GetDiscountvaluepct() const     { return s.DISCOUNTVALUEPCT; }
                const kdauftragpospromoS& GetStruct() const { return s; }
                void            SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
                void            SetPosnr(long t) { s.POSNR = t; }
                void            SetDiscountgrpno(long t) { s.DISCOUNTGRPNO = t; }
                void            SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_KDAUFTRAGPOSPROMO_PHARMACYGROUPID); }
                void            SetBaseqty(long t) { s.BASEQTY = t; }
                void            SetBase_value(double t) { s.BASE_VALUE = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetPromotion_no(short t) { s.PROMOTION_NO = t; }
                void            SetInternaldiscount(char t) { s.INTERNALDISCOUNT[0] = t; s.INTERNALDISCOUNT[1] = '\0';}
                void            SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
                void            SetStruct(const kdauftragpospromoS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CKDAUFTRAGPOSPROMO()  //constructor
                {
                        ::buf_default((void *)&s, KDAUFTRAGPOSPROMO_BES, KDAUFTRAGPOSPROMO_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CKDAUFTRAGPOSPROMO()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, KDAUFTRAGPOSPROMO_BES, KDAUFTRAGPOSPROMO_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, KDAUFTRAGPOSPROMO_BES, KDAUFTRAGPOSPROMO_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, KDAUFTRAGPOSPROMO_BES, KDAUFTRAGPOSPROMO_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_KDAUFTRAGPOSPROMO& d)
                {
#ifdef WIN32
                        ppGStripLast(d.PHARMACYGROUPID);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, KDAUFTRAGPOSPROMO_BES, KDAUFTRAGPOSPROMO_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of KDAUFTRAGPOSPROMO ************************************/

 #define KDAUFTRAGPOSPROMO_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         POSNR integer default 0 not null,\
         DISCOUNTGRPNO integer default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         BASEQTY integer default 0 not null,\
         BASE_VALUE decimal(10,2) default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         PROMOTION_NO smallint default 0 not null,\
         INTERNALDISCOUNT char(1) default " " not null,\
         DISCOUNTVALUEPCT decimal(5,2) default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of KDAUFTRAGPOSPROMO **********************************/

 #define KDAUFTRAGPOSPROMO_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdauftragpromo_1 on _X_(\
              kdauftragnr,\
              posnr,\
              promotion_no ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGPOSPROMO **********************************/

 #define KDAUFTRAGPOSPROMO_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdauftragpromo_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

#ifndef __PP_ORDERCRITERIA_H_
#define __PP_ORDERCRITERIA_H_

/******************************************************************************/
/* u:\OrderCriteria ***********************************************************/
/******************************************************************************/

/* Length-Define of ORDERCRITERIA *********************************************/

  #define L_ORDERCRITERIA_BRANCHNO 6
  #define L_ORDERCRITERIA_ARTICLENO 11
  #define L_ORDERCRITERIA_MANUFACTURERNO 11
  #define L_ORDERCRITERIA_PHARMACYGROUPID 3
  #define L_ORDERCRITERIA_CUSTOMERNO 11
  #define L_ORDERCRITERIA_ORDER_TYPE 2
  #define L_ORDERCRITERIA_MINORDERQTY 11
  #define L_ORDERCRITERIA_MINORDERVALUE 9
  #define N_ORDERCRITERIA_MINORDERVALUE 2
  #define L_ORDERCRITERIA_LIMIT_ACTION 2
  #define L_ORDERCRITERIA_ACTION_RESTRICTION 2
  #define L_ORDERCRITERIA_ADDONCHARGEARTNO 11
  #define L_ORDERCRITERIA_ADDONCHARGEPCT 5
  #define N_ORDERCRITERIA_ADDONCHARGEPCT 2

/* Length/Count-Define of ORDERCRITERIA ***************************************/

  #define LS_ORDERCRITERIA_BRANCHNO 5 + 1
  #define LS_ORDERCRITERIA_ARTICLENO 10 + 1
  #define LS_ORDERCRITERIA_MANUFACTURERNO 10 + 1
  #define LS_ORDERCRITERIA_PHARMACYGROUPID 3 + 1
  #define LS_ORDERCRITERIA_CUSTOMERNO 10 + 1
  #define LS_ORDERCRITERIA_ORDER_TYPE 2 + 1
  #define LS_ORDERCRITERIA_MINORDERQTY 10 + 1
  #define LS_ORDERCRITERIA_MINORDERVALUE 9 + 2
  #define LS_ORDERCRITERIA_LIMIT_ACTION 2 + 1
  #define LS_ORDERCRITERIA_ACTION_RESTRICTION 2 + 1
  #define LS_ORDERCRITERIA_ADDONCHARGEARTNO 10 + 1
  #define LS_ORDERCRITERIA_ADDONCHARGEPCT 5 + 2

  #define ORDERCRITERIABRANCHNO 0
  #define ORDERCRITERIAARTICLENO 1
  #define ORDERCRITERIAMANUFACTURERNO 2
  #define ORDERCRITERIAPHARMACYGROUPID 3
  #define ORDERCRITERIACUSTOMERNO 4
  #define ORDERCRITERIAORDER_TYPE 5
  #define ORDERCRITERIAMINORDERQTY 6
  #define ORDERCRITERIAMINORDERVALUE 7
  #define ORDERCRITERIALIMIT_ACTION 8
  #define ORDERCRITERIAACTION_RESTRICTION 9
  #define ORDERCRITERIAADDONCHARGEARTNO 10
  #define ORDERCRITERIAADDONCHARGEPCT 11

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ORDERCRITERIA_H
 #define ORDERCRITERIA_ANZ ( sizeof(ORDERCRITERIA_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ORDERCRITERIA *************************************************/

 #define ORDERCRITERIA_LISTE \
         ORDERCRITERIA.BRANCHNO,\
         ORDERCRITERIA.ARTICLENO,\
         ORDERCRITERIA.MANUFACTURERNO,\
         ORDERCRITERIA.PHARMACYGROUPID,\
         ORDERCRITERIA.CUSTOMERNO,\
         ORDERCRITERIA.ORDER_TYPE,\
         ORDERCRITERIA.MINORDERQTY,\
         ORDERCRITERIA.MINORDERVALUE,\
         ORDERCRITERIA.LIMIT_ACTION,\
         ORDERCRITERIA.ACTION_RESTRICTION,\
         ORDERCRITERIA.ADDONCHARGEARTNO,\
         ORDERCRITERIA.ADDONCHARGEPCT

 #define ORDERCRITERIA_LISTE_390 \
         BRANCHNO,\
         ARTICLENO,\
         MANUFACTURERNO,\
         PHARMACYGROUPID,\
         CUSTOMERNO,\
         ORDER_TYPE,\
         MINORDERQTY,\
         MINORDERVALUE,\
         LIMIT_ACTION,\
         ACTION_RESTRICTION,\
         ADDONCHARGEARTNO,\
         ADDONCHARGEPCT

 #define ORDERCRITERIA_PLISTE \
         "ORDERCRITERIA.BRANCHNO,"\
         "ORDERCRITERIA.ARTICLENO,"\
         "ORDERCRITERIA.MANUFACTURERNO,"\
         "ORDERCRITERIA.PHARMACYGROUPID,"\
         "ORDERCRITERIA.CUSTOMERNO,"\
         "ORDERCRITERIA.ORDER_TYPE,"\
         "ORDERCRITERIA.MINORDERQTY,"\
         "ORDERCRITERIA.MINORDERVALUE,"\
         "ORDERCRITERIA.LIMIT_ACTION,"\
         "ORDERCRITERIA.ACTION_RESTRICTION,"\
         "ORDERCRITERIA.ADDONCHARGEARTNO,"\
         "ORDERCRITERIA.ADDONCHARGEPCT"

 #define ORDERCRITERIA_PELISTE \
         "BRANCHNO,"\
         "ARTICLENO,"\
         "MANUFACTURERNO,"\
         "PHARMACYGROUPID,"\
         "CUSTOMERNO,"\
         "ORDER_TYPE,"\
         "MINORDERQTY,"\
         "MINORDERVALUE,"\
         "LIMIT_ACTION,"\
         "ACTION_RESTRICTION,"\
         "ADDONCHARGEARTNO,"\
         "ADDONCHARGEPCT"

 #define ORDERCRITERIA_UPDLISTE \
         "BRANCHNO=?,"\
         "ARTICLENO=?,"\
         "MANUFACTURERNO=?,"\
         "PHARMACYGROUPID=?,"\
         "CUSTOMERNO=?,"\
         "ORDER_TYPE=?,"\
         "MINORDERQTY=?,"\
         "MINORDERVALUE=?,"\
         "LIMIT_ACTION=?,"\
         "ACTION_RESTRICTION=?,"\
         "ADDONCHARGEARTNO=?,"\
         "ADDONCHARGEPCT=?"

/* SqlMacros-Define of ORDERCRITERIA ******************************************/

 #define ORDERCRITERIA_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->MANUFACTURERNO,\
         :x->PHARMACYGROUPID,\
         :x->CUSTOMERNO,\
         :x->ORDER_TYPE,\
         :x->MINORDERQTY,\
         :x->MINORDERVALUE,\
         :x->LIMIT_ACTION,\
         :x->ACTION_RESTRICTION,\
         :x->ADDONCHARGEARTNO,\
         :x->ADDONCHARGEPCT

 #define ORDERCRITERIA_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->MANUFACTURERNO,\
         :x->PHARMACYGROUPID,\
         :x->CUSTOMERNO,\
         :x->ORDER_TYPE,\
         :x->MINORDERQTY,\
         :x->MINORDERVALUE,\
         :x->LIMIT_ACTION,\
         :x->ACTION_RESTRICTION,\
         :x->ADDONCHARGEARTNO,\
         :x->ADDONCHARGEPCT

 #define ORDERCRITERIA_UPDATE(x) \
         ORDERCRITERIA.BRANCHNO=:x->BRANCHNO,\
         ORDERCRITERIA.ARTICLENO=:x->ARTICLENO,\
         ORDERCRITERIA.MANUFACTURERNO=:x->MANUFACTURERNO,\
         ORDERCRITERIA.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         ORDERCRITERIA.CUSTOMERNO=:x->CUSTOMERNO,\
         ORDERCRITERIA.ORDER_TYPE=:x->ORDER_TYPE,\
         ORDERCRITERIA.MINORDERQTY=:x->MINORDERQTY,\
         ORDERCRITERIA.MINORDERVALUE=:x->MINORDERVALUE,\
         ORDERCRITERIA.LIMIT_ACTION=:x->LIMIT_ACTION,\
         ORDERCRITERIA.ACTION_RESTRICTION=:x->ACTION_RESTRICTION,\
         ORDERCRITERIA.ADDONCHARGEARTNO=:x->ADDONCHARGEARTNO,\
         ORDERCRITERIA.ADDONCHARGEPCT=:x->ADDONCHARGEPCT

/* SqlMacros390-Define of ORDERCRITERIA ***************************************/

 #define ORDERCRITERIA_ZEIGER_390 \
         :BRANCHNO,\
         :ARTICLENO,\
         :MANUFACTURERNO,\
         :PHARMACYGROUPID,\
         :CUSTOMERNO,\
         :ORDER_TYPE,\
         :MINORDERQTY,\
         :MINORDERVALUE,\
         :LIMIT_ACTION,\
         :ACTION_RESTRICTION,\
         :ADDONCHARGEARTNO,\
         :ADDONCHARGEPCT

 #define ORDERCRITERIA_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         ARTICLENO=:ARTICLENO,\
         MANUFACTURERNO=:MANUFACTURERNO,\
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         CUSTOMERNO=:CUSTOMERNO,\
         ORDER_TYPE=:ORDER_TYPE,\
         MINORDERQTY=:MINORDERQTY,\
         MINORDERVALUE=:MINORDERVALUE,\
         LIMIT_ACTION=:LIMIT_ACTION,\
         ACTION_RESTRICTION=:ACTION_RESTRICTION,\
         ADDONCHARGEARTNO=:ADDONCHARGEARTNO,\
         ADDONCHARGEPCT=:ADDONCHARGEPCT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ORDERCRITERIA ******************************************/

 #ifndef TRANSCLASS
 typedef struct N_ORDERCRITERIA {
         short BRANCHNO;
         long ARTICLENO;
         long MANUFACTURERNO;
         char PHARMACYGROUPID[4];
         long CUSTOMERNO;
         char ORDER_TYPE[3];
         long MINORDERQTY;
         double MINORDERVALUE;
         char LIMIT_ACTION[3];
         char ACTION_RESTRICTION[3];
         long ADDONCHARGEARTNO;
         double ADDONCHARGEPCT;
        } ordercriteriaS;
 #else /*TRANSCLASS*/
 typedef struct N_ORDERCRITERIA {
         short BRANCHNO;
         long ARTICLENO;
         long MANUFACTURERNO;
         char PHARMACYGROUPID[4];
         long CUSTOMERNO;
         char ORDER_TYPE[3];
         long MINORDERQTY;
         double MINORDERVALUE;
         char LIMIT_ACTION[3];
         char ACTION_RESTRICTION[3];
         long ADDONCHARGEARTNO;
         double ADDONCHARGEPCT;

                        bool operator==(const N_ORDERCRITERIA& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                ARTICLENO == right.ARTICLENO &&
                                MANUFACTURERNO == right.MANUFACTURERNO &&
                                !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                !strcmp(ORDER_TYPE, right.ORDER_TYPE) &&
                                MINORDERQTY == right.MINORDERQTY &&
                                MINORDERVALUE == right.MINORDERVALUE &&
                                !strcmp(LIMIT_ACTION, right.LIMIT_ACTION) &&
                                !strcmp(ACTION_RESTRICTION, right.ACTION_RESTRICTION) &&
                                ADDONCHARGEARTNO == right.ADDONCHARGEARTNO &&
                                ADDONCHARGEPCT == right.ADDONCHARGEPCT
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                ARTICLENO = 0;
                                MANUFACTURERNO = 0;
                                strcpy(PHARMACYGROUPID, " " );
                                CUSTOMERNO = 0;
                                strcpy(ORDER_TYPE, " " );
                                MINORDERQTY = 0;
                                MINORDERVALUE = 0;
                                strcpy(LIMIT_ACTION, " " );
                                strcpy(ACTION_RESTRICTION, " " );
                                ADDONCHARGEARTNO = 0;
                                ADDONCHARGEPCT = 0;
#endif
                        }
         } ordercriteriaS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ORDERCRITERIA *************************************/

 struct S_ORDERCRITERIA {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char MANUFACTURERNO[11];
         char PHARMACYGROUPID[3 + 1];
         char CUSTOMERNO[11];
         char ORDER_TYPE[2 + 1];
         char MINORDERQTY[11];
         char MINORDERVALUE[9 + 2];
         char LIMIT_ACTION[2 + 1];
         char ACTION_RESTRICTION[2 + 1];
         char ADDONCHARGEARTNO[11];
         char ADDONCHARGEPCT[5 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ORDERCRITERIA ********************/

 struct O_ORDERCRITERIA {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char MANUFACTURERNO[11];
         char PHARMACYGROUPID[3];
         char CUSTOMERNO[11];
         char ORDER_TYPE[2];
         char MINORDERQTY[11];
         char MINORDERVALUE[9];
         char LIMIT_ACTION[2];
         char ACTION_RESTRICTION[2];
         char ADDONCHARGEARTNO[11];
         char ADDONCHARGEPCT[5];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ORDERCRITERIA *******************************/

 struct C_ORDERCRITERIA {
         short BRANCHNO;
         long ARTICLENO;
         long MANUFACTURERNO;
         char PHARMACYGROUPID[4];
         long CUSTOMERNO;
         char ORDER_TYPE[3];
         long MINORDERQTY;
         double MINORDERVALUE;
         char LIMIT_ACTION[3];
         char ACTION_RESTRICTION[3];
         long ADDONCHARGEARTNO;
         double ADDONCHARGEPCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ORDERCRITERIA *****************************/

 struct I_ORDERCRITERIA {
         short BRANCHNO;
         short ARTICLENO;
         short MANUFACTURERNO;
         short PHARMACYGROUPID;
         short CUSTOMERNO;
         short ORDER_TYPE;
         short MINORDERQTY;
         short MINORDERVALUE;
         short LIMIT_ACTION;
         short ACTION_RESTRICTION;
         short ADDONCHARGEARTNO;
         short ADDONCHARGEPCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ORDERCRITERIA ***************************************/

#if defined (BUF_DESC)
 static struct buf_desc ORDERCRITERIA_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_C, 2, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ORDERCRITERIA_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_C, 2, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
 };
#endif

/* description for datatypes of ORDERCRITERIA *********************************/

 #define ORDERCRITERIA_S390 \
         short BRANCHNO; \
         long ARTICLENO; \
         long MANUFACTURERNO; \
         char PHARMACYGROUPID[4]; \
         long CUSTOMERNO; \
         char ORDER_TYPE[3]; \
         long MINORDERQTY; \
         double MINORDERVALUE; \
         char LIMIT_ACTION[3]; \
         char ACTION_RESTRICTION[3]; \
         long ADDONCHARGEARTNO; \
         double ADDONCHARGEPCT; \



/* Copy-Function Struct to single Data ORDERCRITERIA **************************/

 #define ORDERCRITERIA_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         ARTICLENO=_x_->ARTICLENO;\
         MANUFACTURERNO=_x_->MANUFACTURERNO;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         CUSTOMERNO=_x_->CUSTOMERNO;\
          strcpy(ORDER_TYPE,_x_->ORDER_TYPE);\
         MINORDERQTY=_x_->MINORDERQTY;\
         MINORDERVALUE=_x_->MINORDERVALUE;\
          strcpy(LIMIT_ACTION,_x_->LIMIT_ACTION);\
          strcpy(ACTION_RESTRICTION,_x_->ACTION_RESTRICTION);\
         ADDONCHARGEARTNO=_x_->ADDONCHARGEARTNO;\
         ADDONCHARGEPCT=_x_->ADDONCHARGEPCT;\

 #define ORDERCRITERIA_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->MANUFACTURERNO=MANUFACTURERNO;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          strcpy(_x_->ORDER_TYPE,ORDER_TYPE);\
          _x_->MINORDERQTY=MINORDERQTY;\
          _x_->MINORDERVALUE=MINORDERVALUE;\
          strcpy(_x_->LIMIT_ACTION,LIMIT_ACTION);\
          strcpy(_x_->ACTION_RESTRICTION,ACTION_RESTRICTION);\
          _x_->ADDONCHARGEARTNO=ADDONCHARGEARTNO;\
          _x_->ADDONCHARGEPCT=ADDONCHARGEPCT;\



/* FunctionNumber-Define of OrderCriteria *************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of OrderCriteria *********************************/


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

class CORDERCRITERIA : public ppDadeVirtual
{
        //data members
        public:
                ordercriteriaS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<ordercriteriaS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<ordercriteriaS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<ordercriteriaS>; Strip(s); ordercriteriaS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<ordercriteriaS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<ordercriteriaS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<ordercriteriaS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetArticleno() const    { return s.ARTICLENO; }
                long            GetManufacturerno() const       { return s.MANUFACTURERNO; }
                const char*     GetPharmacygroupid(ppString& t) const   { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                const char*     GetOrder_type(ppString& t) const        { t = s.ORDER_TYPE; t.erasespace(ppString::END); return t.c_str(); }
                long            GetMinorderqty() const  { return s.MINORDERQTY; }
                double          GetMinordervalue() const        { return s.MINORDERVALUE; }
                const char*     GetLimit_action(ppString& t) const      { t = s.LIMIT_ACTION; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetAction_restriction(ppString& t) const        { t = s.ACTION_RESTRICTION; t.erasespace(ppString::END); return t.c_str(); }
                long            GetAddonchargeartno() const     { return s.ADDONCHARGEARTNO; }
                double          GetAddonchargepct() const       { return s.ADDONCHARGEPCT; }
                const ordercriteriaS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetManufacturerno(long t) { s.MANUFACTURERNO = t; }
                void            SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_ORDERCRITERIA_PHARMACYGROUPID); }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetOrder_type(const ppString& t) { ppGStrCopy(s.ORDER_TYPE,t.c_str() ,L_ORDERCRITERIA_ORDER_TYPE); }
                void            SetMinorderqty(long t) { s.MINORDERQTY = t; }
                void            SetMinordervalue(double t) { s.MINORDERVALUE = t; }
                void            SetLimit_action(const ppString& t) { ppGStrCopy(s.LIMIT_ACTION,t.c_str() ,L_ORDERCRITERIA_LIMIT_ACTION); }
                void            SetAction_restriction(const ppString& t) { ppGStrCopy(s.ACTION_RESTRICTION,t.c_str() ,L_ORDERCRITERIA_ACTION_RESTRICTION); }
                void            SetAddonchargeartno(long t) { s.ADDONCHARGEARTNO = t; }
                void            SetAddonchargepct(double t) { s.ADDONCHARGEPCT = t; }
                void            SetStruct(const ordercriteriaS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CORDERCRITERIA()  //constructor
                {
                        ::buf_default((void *)&s, ORDERCRITERIA_BES, ORDERCRITERIA_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CORDERCRITERIA()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ORDERCRITERIA_BES, ORDERCRITERIA_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ORDERCRITERIA_BES, ORDERCRITERIA_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ORDERCRITERIA_BES, ORDERCRITERIA_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ORDERCRITERIA& d)
                {
#ifdef WIN32
                        ppGStripLast(d.PHARMACYGROUPID);
                        ppGStripLast(d.ORDER_TYPE);
                        ppGStripLast(d.LIMIT_ACTION);
                        ppGStripLast(d.ACTION_RESTRICTION);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ORDERCRITERIA_BES, ORDERCRITERIA_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ORDERCRITERIA ****************************************/

 #define ORDERCRITERIA_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         ARTICLENO integer default 0 not null,\
         MANUFACTURERNO integer default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         CUSTOMERNO integer default 0 not null,\
         ORDER_TYPE char(2) default " " not null,\
         MINORDERQTY integer default 0 not null,\
         MINORDERVALUE decimal(9,2) default 0 not null,\
         LIMIT_ACTION char(2) default " " not null,\
         ACTION_RESTRICTION char(2) default " " not null,\
         ADDONCHARGEARTNO integer default 0 not null,\
         ADDONCHARGEPCT decimal(5,2) default 0 not null) in ksc extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of ORDERCRITERIA **************************************/

 #define ORDERCRITERIA_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_ordercrit_1 on _X_(\
              BranchNo,\
              ArticleNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_ordercrit_2 on _X_(\
              BranchNo,\
              manufacturerno,\
              PharmacyGroupId ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_ordercrit_3 on _X_(\
              BranchNo,\
              CustomerNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ORDERCRITERIA **************************************/

 #define ORDERCRITERIA_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_ordercrit_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_ordercrit_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_ordercrit_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

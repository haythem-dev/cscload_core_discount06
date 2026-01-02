#ifndef __PP_DISCOUNTGRP_H_
#define __PP_DISCOUNTGRP_H_

/******************************************************************************/
/* u:\DiscountGrp *************************************************************/
/******************************************************************************/

/* Length-Define of DISCOUNTGRP ***********************************************/

  #define L_DISCOUNTGRP_BRANCHNO 6
  #define L_DISCOUNTGRP_DISCOUNTGRPNO 11
  #define L_DISCOUNTGRP_DESCRIPTION 254
  #define L_DISCOUNTGRP_DISCOUNTGRPTYPE 6
  #define L_DISCOUNTGRP_CUSTOMERNO 11

/* Length/Count-Define of DISCOUNTGRP *****************************************/

  #define LS_DISCOUNTGRP_BRANCHNO 5 + 1
  #define LS_DISCOUNTGRP_DISCOUNTGRPNO 10 + 1
  #define LS_DISCOUNTGRP_DESCRIPTION 254 + 1
  #define LS_DISCOUNTGRP_DISCOUNTGRPTYPE 5 + 1
  #define LS_DISCOUNTGRP_CUSTOMERNO 10 + 1

  #define DISCOUNTGRPBRANCHNO 0
  #define DISCOUNTGRPDISCOUNTGRPNO 1
  #define DISCOUNTGRPDESCRIPTION 2
  #define DISCOUNTGRPDISCOUNTGRPTYPE 3
  #define DISCOUNTGRPCUSTOMERNO 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DISCOUNTGRP_H
 #define DISCOUNTGRP_ANZ ( sizeof(DISCOUNTGRP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DISCOUNTGRP ***************************************************/

 #define DISCOUNTGRP_LISTE \
         DISCOUNTGRP.BRANCHNO,\
         DISCOUNTGRP.DISCOUNTGRPNO,\
         DISCOUNTGRP.DESCRIPTION,\
         DISCOUNTGRP.DISCOUNTGRPTYPE,\
         DISCOUNTGRP.CUSTOMERNO

 #define DISCOUNTGRP_LISTE_390 \
         BRANCHNO,\
         DISCOUNTGRPNO,\
         DESCRIPTION,\
         DISCOUNTGRPTYPE,\
         CUSTOMERNO

 #define DISCOUNTGRP_PLISTE \
         "DISCOUNTGRP.BRANCHNO,"\
         "DISCOUNTGRP.DISCOUNTGRPNO,"\
         "DISCOUNTGRP.DESCRIPTION,"\
         "DISCOUNTGRP.DISCOUNTGRPTYPE,"\
         "DISCOUNTGRP.CUSTOMERNO"

 #define DISCOUNTGRP_PELISTE \
         "BRANCHNO,"\
         "DISCOUNTGRPNO,"\
         "DESCRIPTION,"\
         "DISCOUNTGRPTYPE,"\
         "CUSTOMERNO"

 #define DISCOUNTGRP_UPDLISTE \
         "BRANCHNO=?,"\
         "DISCOUNTGRPNO=?,"\
         "DESCRIPTION=?,"\
         "DISCOUNTGRPTYPE=?,"\
         "CUSTOMERNO=?"

/* SqlMacros-Define of DISCOUNTGRP ********************************************/

 #define DISCOUNTGRP_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->DISCOUNTGRPNO,\
         :x->DESCRIPTION,\
         :x->DISCOUNTGRPTYPE,\
         :x->CUSTOMERNO

 #define DISCOUNTGRP_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->DISCOUNTGRPNO,\
         :x->DESCRIPTION,\
         :x->DISCOUNTGRPTYPE,\
         :x->CUSTOMERNO

 #define DISCOUNTGRP_UPDATE(x) \
         DISCOUNTGRP.BRANCHNO=:x->BRANCHNO,\
         DISCOUNTGRP.DISCOUNTGRPNO=:x->DISCOUNTGRPNO,\
         DISCOUNTGRP.DESCRIPTION=:x->DESCRIPTION,\
         DISCOUNTGRP.DISCOUNTGRPTYPE=:x->DISCOUNTGRPTYPE,\
         DISCOUNTGRP.CUSTOMERNO=:x->CUSTOMERNO

/* SqlMacros390-Define of DISCOUNTGRP *****************************************/

 #define DISCOUNTGRP_ZEIGER_390 \
         :BRANCHNO,\
         :DISCOUNTGRPNO,\
         :DESCRIPTION,\
         :DISCOUNTGRPTYPE,\
         :CUSTOMERNO

 #define DISCOUNTGRP_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         DISCOUNTGRPNO=:DISCOUNTGRPNO,\
         DESCRIPTION=:DESCRIPTION,\
         DISCOUNTGRPTYPE=:DISCOUNTGRPTYPE,\
         CUSTOMERNO=:CUSTOMERNO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of DISCOUNTGRP ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_DISCOUNTGRP {
         short BRANCHNO;
         long DISCOUNTGRPNO;
         char DESCRIPTION[255];
         short DISCOUNTGRPTYPE;
         long CUSTOMERNO;
        } discountgrpS;
 #else /*TRANSCLASS*/
 typedef struct N_DISCOUNTGRP {
         short BRANCHNO;
         long DISCOUNTGRPNO;
         char DESCRIPTION[255];
         short DISCOUNTGRPTYPE;
         long CUSTOMERNO;

                        bool operator==(const N_DISCOUNTGRP& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                DISCOUNTGRPNO == right.DISCOUNTGRPNO &&
                                !strcmp(DESCRIPTION, right.DESCRIPTION) &&
                                DISCOUNTGRPTYPE == right.DISCOUNTGRPTYPE &&
                                CUSTOMERNO == right.CUSTOMERNO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                DISCOUNTGRPNO = 0;
                                strcpy(DESCRIPTION, " " );
                                DISCOUNTGRPTYPE = 0;
                                CUSTOMERNO = 0;
#endif
                        }
         } discountgrpS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DISCOUNTGRP ***************************************/

 struct S_DISCOUNTGRP {
         char BRANCHNO[7];
         char DISCOUNTGRPNO[11];
         char DESCRIPTION[254 + 1];
         char DISCOUNTGRPTYPE[7];
         char CUSTOMERNO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DISCOUNTGRP **********************/

 struct O_DISCOUNTGRP {
         char BRANCHNO[7];
         char DISCOUNTGRPNO[11];
         char DESCRIPTION[254];
         char DISCOUNTGRPTYPE[7];
         char CUSTOMERNO[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DISCOUNTGRP *********************************/

 struct C_DISCOUNTGRP {
         short BRANCHNO;
         long DISCOUNTGRPNO;
         char DESCRIPTION[255];
         short DISCOUNTGRPTYPE;
         long CUSTOMERNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DISCOUNTGRP *******************************/

 struct I_DISCOUNTGRP {
         short BRANCHNO;
         short DISCOUNTGRPNO;
         short DESCRIPTION;
         short DISCOUNTGRPTYPE;
         short CUSTOMERNO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DISCOUNTGRP *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc DISCOUNTGRP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DISCOUNTGRP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of DISCOUNTGRP ***********************************/

 #define DISCOUNTGRP_S390 \
         short BRANCHNO; \
         long DISCOUNTGRPNO; \
         char DESCRIPTION[255]; \
         short DISCOUNTGRPTYPE; \
         long CUSTOMERNO; \



/* Copy-Function Struct to single Data DISCOUNTGRP ****************************/

 #define DISCOUNTGRP_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         DISCOUNTGRPNO=_x_->DISCOUNTGRPNO;\
          strcpy(DESCRIPTION,_x_->DESCRIPTION);\
         DISCOUNTGRPTYPE=_x_->DISCOUNTGRPTYPE;\
         CUSTOMERNO=_x_->CUSTOMERNO;\

 #define DISCOUNTGRP_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->DISCOUNTGRPNO=DISCOUNTGRPNO;\
          strcpy(_x_->DESCRIPTION,DESCRIPTION);\
          _x_->DISCOUNTGRPTYPE=DISCOUNTGRPTYPE;\
          _x_->CUSTOMERNO=CUSTOMERNO;\



/* FunctionNumber-Define of DiscountGrp ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of DiscountGrp ***********************************/


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

class CDISCOUNTGRP : public ppDadeVirtual
{
        //data members
        public:
                discountgrpS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<discountgrpS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountgrpS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<discountgrpS>; Strip(s); discountgrpS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountgrpS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<discountgrpS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<discountgrpS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetDiscountgrpno() const        { return s.DISCOUNTGRPNO; }
                const char*     GetDescription(ppString& t) const       { t = s.DESCRIPTION; t.erasespace(ppString::END); return t.c_str(); }
                short           GetDiscountgrptype() const      { return s.DISCOUNTGRPTYPE; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                const discountgrpS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetDiscountgrpno(long t) { s.DISCOUNTGRPNO = t; }
                void            SetDescription(const ppString& t) { ppGStrCopy(s.DESCRIPTION,t.c_str() ,L_DISCOUNTGRP_DESCRIPTION); }
                void            SetDiscountgrptype(short t) { s.DISCOUNTGRPTYPE = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetStruct(const discountgrpS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CDISCOUNTGRP()  //constructor
                {
                        ::buf_default((void *)&s, DISCOUNTGRP_BES, DISCOUNTGRP_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CDISCOUNTGRP()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, DISCOUNTGRP_BES, DISCOUNTGRP_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DISCOUNTGRP_BES, DISCOUNTGRP_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, DISCOUNTGRP_BES, DISCOUNTGRP_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_DISCOUNTGRP& d)
                {
#ifdef WIN32
                        ppGStripLast(d.DESCRIPTION);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, DISCOUNTGRP_BES, DISCOUNTGRP_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of DISCOUNTGRP ******************************************/

 #define DISCOUNTGRP_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         DISCOUNTGRPNO integer default 0 not null,\
         DESCRIPTION varchar(254,0) default " " not null,\
         DISCOUNTGRPTYPE smallint default 0 not null,\
         CUSTOMERNO integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DISCOUNTGRP ****************************************/

 #define DISCOUNTGRP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_discountgrp_1 on _X_(\
              BranchNo,\
              DiscountGrpNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of DISCOUNTGRP ****************************************/

 #define DISCOUNTGRP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_discountgrp_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

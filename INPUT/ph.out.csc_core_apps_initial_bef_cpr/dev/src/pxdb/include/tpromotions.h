#ifndef __PP_PROMOTIONS_H_
#define __PP_PROMOTIONS_H_

/******************************************************************************/
/* u:\Promotions **************************************************************/
/******************************************************************************/

/* Length-Define of PROMOTIONS ************************************************/

  #define L_PROMOTIONS_PROMOTION_NO 6
  #define L_PROMOTIONS_NAME 30
  #define L_PROMOTIONS_DESCRIPTION 254
  #define L_PROMOTIONS_PROMOTION_TYPE 6
  #define L_PROMOTIONS_ADDONPROMODISCOK 1
  #define L_PROMOTIONS_ADDONSTDDISCOK 1
  #define L_PROMOTIONS_PRIORITY 6
  #define L_PROMOTIONS_SNOTBYSALESEWEB 1

/* Length/Count-Define of PROMOTIONS ******************************************/

  #define LS_PROMOTIONS_PROMOTION_NO 5 + 1
  #define LS_PROMOTIONS_NAME 30 + 1
  #define LS_PROMOTIONS_DESCRIPTION 254 + 1
  #define LS_PROMOTIONS_PROMOTION_TYPE 5 + 1
  #define LS_PROMOTIONS_ADDONPROMODISCOK 1 + 1
  #define LS_PROMOTIONS_ADDONSTDDISCOK 1 + 1
  #define LS_PROMOTIONS_PRIORITY 5 + 1
  #define LS_PROMOTIONS_SNOTBYSALESEWEB 1 + 1

  #define PROMOTIONSPROMOTION_NO 0
  #define PROMOTIONSNAME 1
  #define PROMOTIONSDESCRIPTION 2
  #define PROMOTIONSPROMOTION_TYPE 3
  #define PROMOTIONSADDONPROMODISCOK 4
  #define PROMOTIONSADDONSTDDISCOK 5
  #define PROMOTIONSPRIORITY 6
  #define PROMOTIONSSNOTBYSALESEWEB 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define PROMOTIONS_H
 #define PROMOTIONS_ANZ ( sizeof(PROMOTIONS_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PROMOTIONS ****************************************************/

 #define PROMOTIONS_LISTE \
         PROMOTIONS.PROMOTION_NO,\
         PROMOTIONS.NAME,\
         PROMOTIONS.DESCRIPTION,\
         PROMOTIONS.PROMOTION_TYPE,\
         PROMOTIONS.ADDONPROMODISCOK,\
         PROMOTIONS.ADDONSTDDISCOK,\
         PROMOTIONS.PRIORITY,\
         PROMOTIONS.SNOTBYSALESEWEB

 #define PROMOTIONS_LISTE_390 \
         PROMOTION_NO,\
         NAME,\
         DESCRIPTION,\
         PROMOTION_TYPE,\
         ADDONPROMODISCOK,\
         ADDONSTDDISCOK,\
         PRIORITY,\
         SNOTBYSALESEWEB

 #define PROMOTIONS_PLISTE \
         "PROMOTIONS.PROMOTION_NO,"\
         "PROMOTIONS.NAME,"\
         "PROMOTIONS.DESCRIPTION,"\
         "PROMOTIONS.PROMOTION_TYPE,"\
         "PROMOTIONS.ADDONPROMODISCOK,"\
         "PROMOTIONS.ADDONSTDDISCOK,"\
         "PROMOTIONS.PRIORITY,"\
         "PROMOTIONS.SNOTBYSALESEWEB"

 #define PROMOTIONS_PELISTE \
         "PROMOTION_NO,"\
         "NAME,"\
         "DESCRIPTION,"\
         "PROMOTION_TYPE,"\
         "ADDONPROMODISCOK,"\
         "ADDONSTDDISCOK,"\
         "PRIORITY,"\
         "SNOTBYSALESEWEB"

 #define PROMOTIONS_UPDLISTE \
         "PROMOTION_NO=?,"\
         "NAME=?,"\
         "DESCRIPTION=?,"\
         "PROMOTION_TYPE=?,"\
         "ADDONPROMODISCOK=?,"\
         "ADDONSTDDISCOK=?,"\
         "PRIORITY=?,"\
         "SNOTBYSALESEWEB=?"

/* SqlMacros-Define of PROMOTIONS *********************************************/

 #define PROMOTIONS_ZEIGER(x) \
         :x->PROMOTION_NO,\
         :x->NAME,\
         :x->DESCRIPTION,\
         :x->PROMOTION_TYPE,\
         :x->ADDONPROMODISCOK,\
         :x->ADDONSTDDISCOK,\
         :x->PRIORITY,\
         :x->SNOTBYSALESEWEB

 #define PROMOTIONS_ZEIGERSEL(x) \
         :x->PROMOTION_NO,\
         :x->NAME,\
         :x->DESCRIPTION,\
         :x->PROMOTION_TYPE,\
         :x->ADDONPROMODISCOK,\
         :x->ADDONSTDDISCOK,\
         :x->PRIORITY,\
         :x->SNOTBYSALESEWEB

 #define PROMOTIONS_UPDATE(x) \
         PROMOTIONS.PROMOTION_NO=:x->PROMOTION_NO,\
         PROMOTIONS.NAME=:x->NAME,\
         PROMOTIONS.DESCRIPTION=:x->DESCRIPTION,\
         PROMOTIONS.PROMOTION_TYPE=:x->PROMOTION_TYPE,\
         PROMOTIONS.ADDONPROMODISCOK=:x->ADDONPROMODISCOK,\
         PROMOTIONS.ADDONSTDDISCOK=:x->ADDONSTDDISCOK,\
         PROMOTIONS.PRIORITY=:x->PRIORITY,\
         PROMOTIONS.SNOTBYSALESEWEB=:x->SNOTBYSALESEWEB

/* SqlMacros390-Define of PROMOTIONS ******************************************/

 #define PROMOTIONS_ZEIGER_390 \
         :PROMOTION_NO,\
         :NAME,\
         :DESCRIPTION,\
         :PROMOTION_TYPE,\
         :ADDONPROMODISCOK,\
         :ADDONSTDDISCOK,\
         :PRIORITY,\
         :SNOTBYSALESEWEB

 #define PROMOTIONS_UPDATE_390 \
         PROMOTION_NO=:PROMOTION_NO,\
         NAME=:NAME,\
         DESCRIPTION=:DESCRIPTION,\
         PROMOTION_TYPE=:PROMOTION_TYPE,\
         ADDONPROMODISCOK=:ADDONPROMODISCOK,\
         ADDONSTDDISCOK=:ADDONSTDDISCOK,\
         PRIORITY=:PRIORITY,\
         SNOTBYSALESEWEB=:SNOTBYSALESEWEB

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of PROMOTIONS *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_PROMOTIONS {
         short PROMOTION_NO;
         char NAME[31];
         char DESCRIPTION[255];
         short PROMOTION_TYPE;
         char ADDONPROMODISCOK[2];
         char ADDONSTDDISCOK[2];
         short PRIORITY;
         char SNOTBYSALESEWEB[2];
        } promotionsS;
 #else /*TRANSCLASS*/
 typedef struct N_PROMOTIONS {
         short PROMOTION_NO;
         char NAME[31];
         char DESCRIPTION[255];
         short PROMOTION_TYPE;
         char ADDONPROMODISCOK[2];
         char ADDONSTDDISCOK[2];
         short PRIORITY;
         char SNOTBYSALESEWEB[2];

                        bool operator==(const N_PROMOTIONS& right) const {
                        return(
                                PROMOTION_NO == right.PROMOTION_NO &&
                                !strcmp(NAME, right.NAME) &&
                                !strcmp(DESCRIPTION, right.DESCRIPTION) &&
                                PROMOTION_TYPE == right.PROMOTION_TYPE &&
                                !strcmp(ADDONPROMODISCOK, right.ADDONPROMODISCOK) &&
                                !strcmp(ADDONSTDDISCOK, right.ADDONSTDDISCOK) &&
                                PRIORITY == right.PRIORITY &&
                                !strcmp(SNOTBYSALESEWEB, right.SNOTBYSALESEWEB)
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                PROMOTION_NO = 0;
                                strcpy(NAME, " " );
                                strcpy(DESCRIPTION, " " );
                                PROMOTION_TYPE = 0;
                                strcpy(ADDONPROMODISCOK, " " );
                                strcpy(ADDONSTDDISCOK, " " );
                                PRIORITY = 0;
                                strcpy(SNOTBYSALESEWEB, " " );
#endif
                        }
         } promotionsS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PROMOTIONS ****************************************/

 struct S_PROMOTIONS {
         char PROMOTION_NO[7];
         char NAME[30 + 1];
         char DESCRIPTION[254 + 1];
         char PROMOTION_TYPE[7];
         char ADDONPROMODISCOK[1 + 1];
         char ADDONSTDDISCOK[1 + 1];
         char PRIORITY[7];
         char SNOTBYSALESEWEB[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PROMOTIONS ***********************/

 struct O_PROMOTIONS {
         char PROMOTION_NO[7];
         char NAME[30];
         char DESCRIPTION[254];
         char PROMOTION_TYPE[7];
         char ADDONPROMODISCOK[1];
         char ADDONSTDDISCOK[1];
         char PRIORITY[7];
         char SNOTBYSALESEWEB[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of PROMOTIONS **********************************/

 struct C_PROMOTIONS {
         short PROMOTION_NO;
         char NAME[31];
         char DESCRIPTION[255];
         short PROMOTION_TYPE;
         char ADDONPROMODISCOK;
         char ADDONSTDDISCOK;
         short PRIORITY;
         char SNOTBYSALESEWEB;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of PROMOTIONS ********************************/

 struct I_PROMOTIONS {
         short PROMOTION_NO;
         short NAME;
         short DESCRIPTION;
         short PROMOTION_TYPE;
         short ADDONPROMODISCOK;
         short ADDONSTDDISCOK;
         short PRIORITY;
         short SNOTBYSALESEWEB;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PROMOTIONS ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc PROMOTIONS_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc PROMOTIONS_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 254, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of PROMOTIONS ************************************/

 #define PROMOTIONS_S390 \
         short PROMOTION_NO; \
         char NAME[31]; \
         char DESCRIPTION[255]; \
         short PROMOTION_TYPE; \
         char ADDONPROMODISCOK; \
         char ADDONSTDDISCOK; \
         short PRIORITY; \
         char SNOTBYSALESEWEB; \



/* Copy-Function Struct to single Data PROMOTIONS *****************************/

 #define PROMOTIONS_S390_COPY_TO_SINGLE(_x_) \
         PROMOTION_NO=_x_->PROMOTION_NO;\
          strcpy(NAME,_x_->NAME);\
          strcpy(DESCRIPTION,_x_->DESCRIPTION);\
         PROMOTION_TYPE=_x_->PROMOTION_TYPE;\
         ADDONPROMODISCOK=_x_->ADDONPROMODISCOK;\
         ADDONSTDDISCOK=_x_->ADDONSTDDISCOK;\
         PRIORITY=_x_->PRIORITY;\
         SNOTBYSALESEWEB=_x_->SNOTBYSALESEWEB;\

 #define PROMOTIONS_S390_COPY_TO_STRUCT(_x_) \
          _x_->PROMOTION_NO=PROMOTION_NO;\
          strcpy(_x_->NAME,NAME);\
          strcpy(_x_->DESCRIPTION,DESCRIPTION);\
          _x_->PROMOTION_TYPE=PROMOTION_TYPE;\
          _x_->ADDONPROMODISCOK=ADDONPROMODISCOK;\
          _x_->ADDONSTDDISCOK=ADDONSTDDISCOK;\
          _x_->PRIORITY=PRIORITY;\
          _x_->SNOTBYSALESEWEB=SNOTBYSALESEWEB;\



/* FunctionNumber-Define of Promotions ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Promotions ************************************/


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

class CPROMOTIONS : public ppDadeVirtual
{
        //data members
        public:
                promotionsS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<promotionsS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<promotionsS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<promotionsS>; Strip(s); promotionsS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<promotionsS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<promotionsS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<promotionsS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetPromotion_no() const { return s.PROMOTION_NO; }
                const char*     GetName(ppString& t) const      { t = s.NAME; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetDescription(ppString& t) const       { t = s.DESCRIPTION; t.erasespace(ppString::END); return t.c_str(); }
                short           GetPromotion_type() const       { return s.PROMOTION_TYPE; }
                char            GetAddonpromodiscok() const     { return s.ADDONPROMODISCOK[0]; }
                char            GetAddonstddiscok() const       { return s.ADDONSTDDISCOK[0]; }
                short           GetPriority() const     { return s.PRIORITY; }
                char            GetSnotbysaleseweb() const      { return s.SNOTBYSALESEWEB[0]; }
                const promotionsS& GetStruct() const { return s; }
                void            SetPromotion_no(short t) { s.PROMOTION_NO = t; }
                void            SetName(const ppString& t) { ppGStrCopy(s.NAME,t.c_str() ,L_PROMOTIONS_NAME); }
                void            SetDescription(const ppString& t) { ppGStrCopy(s.DESCRIPTION,t.c_str() ,L_PROMOTIONS_DESCRIPTION); }
                void            SetPromotion_type(short t) { s.PROMOTION_TYPE = t; }
                void            SetAddonpromodiscok(char t) { s.ADDONPROMODISCOK[0] = t; s.ADDONPROMODISCOK[1] = '\0';}
                void            SetAddonstddiscok(char t) { s.ADDONSTDDISCOK[0] = t; s.ADDONSTDDISCOK[1] = '\0';}
                void            SetPriority(short t) { s.PRIORITY = t; }
                void            SetSnotbysaleseweb(char t) { s.SNOTBYSALESEWEB[0] = t; s.SNOTBYSALESEWEB[1] = '\0';}
                void            SetStruct(const promotionsS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CPROMOTIONS()  //constructor
                {
                        ::buf_default((void *)&s, PROMOTIONS_BES, PROMOTIONS_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CPROMOTIONS()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, PROMOTIONS_BES, PROMOTIONS_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, PROMOTIONS_BES, PROMOTIONS_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, PROMOTIONS_BES, PROMOTIONS_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_PROMOTIONS& d)
                {
#ifdef WIN32
                        ppGStripLast(d.NAME);
                        ppGStripLast(d.DESCRIPTION);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, PROMOTIONS_BES, PROMOTIONS_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of PROMOTIONS *******************************************/

 #define PROMOTIONS_CREATE(x) exec sql create table x (\
         PROMOTION_NO smallint default 0 not null,\
         NAME char(30) default " " not null,\
         DESCRIPTION varchar(254,0) default " " not null,\
         PROMOTION_TYPE smallint default 0 not null,\
         ADDONPROMODISCOK char(1) default " " not null,\
         ADDONSTDDISCOK char(1) default " " not null,\
         PRIORITY smallint default 0 not null,\
         SNOTBYSALESEWEB char(1) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of PROMOTIONS *****************************************/

 #define PROMOTIONS_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_promotions_1 on _X_(\
              promotion_no ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PROMOTIONS *****************************************/

 #define PROMOTIONS_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_promotions_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif
